// MultiVoxelDetectorConstruction.cc

#include "MultiVoxelDetectorConstruction.hh"

#include "G4PhysicalConstants.hh" // for pi
#include "G4NistManager.hh"
#include "G4Box.hh" // used when building solid volume
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4LogicalVolume.hh" // used when building logical volume
#include "G4PVPlacement.hh" // used when building physical volume
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"

G4VPhysicalVolume* MultiVoxelDetectorConstruction::Construct() {
  // Define variables
  G4String name, symbol;
  G4double density, fractionmass;
  G4int ncomponents;
  G4double world_size = 5*cm;
  G4double voxel_size = 3*mm;
  G4double fibre_half_length = 0.5*cm;
  G4double fibre_radius = 0.3*mm;
  G4double clad_radius = 0.33*mm;
  G4bool checkOverlaps = true;
  G4double BC400_Birks_Constant = 207.*um/MeV;
  G4double BC400_abs_length_val = 1.6*m;

  // Get materials from NIST manager
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* fibre_mat = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  // assumes no impurities in the silica of the fibre
  G4Material* clad_mat = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  G4Element* C = nist->FindOrBuildElement("C");
  G4Element* H = nist->FindOrBuildElement("H");

  // Define air's refractive index
  G4double temp_energies_air[3] = {2.00*eV, 3.00*eV, 5.00*eV};
  G4double ref_air[3] = {1.000277, 1.000277, 1.000277};
  G4MaterialPropertiesTable* air_mpt = new G4MaterialPropertiesTable();
  air_mpt -> AddProperty("RINDEX", temp_energies_air, ref_air, 3)->SetSpline(true);
  world_mat->SetMaterialPropertiesTable(air_mpt);

  // Define optical properties of fibre
  G4double temp_energies[3] = {2.00*eV, 3.00*eV, 5.00*eV};
  G4double fibreRI[3] = {1.4678, 1.4678, 1.4678};
  G4MaterialPropertiesTable* fibre_mpt = new G4MaterialPropertiesTable();
  fibre_mpt->AddProperty("RINDEX", temp_energies, fibreRI, 3)->SetSpline(true);
  fibre_mat->SetMaterialPropertiesTable(fibre_mpt);
  // and of the cladding
  G4double cladRI[3] = {1.4512, 1.4512, 1.4512};
  G4MaterialPropertiesTable* clad_mpt = new G4MaterialPropertiesTable();
  clad_mpt->AddProperty("RINDEX", temp_energies, cladRI, 3)->SetSpline(true);
  clad_mat->SetMaterialPropertiesTable(clad_mpt);
  // define outer surface of cladding
  G4OpticalSurface* casing = new G4OpticalSurface("casing");
  casing->SetType(dielectric_dielectric);
  casing->SetFinish(groundfrontpainted);
  casing->SetModel(unified);
  G4MaterialPropertiesTable* casing_mpt = new G4MaterialPropertiesTable();
  casing_mpt->AddConstProperty("REFLECTIVITY", 1);
  casing->SetMaterialPropertiesTable(casing_mpt);

  // Define material for solid scintillator (SS)
  // Using southern scientific BC-400 until we know what SS is made of
  density = 1.032*g/cm3;
  G4Material* SS = new G4Material("SS", density, ncomponents=2);
  SS->AddElement(C, fractionmass=47.5*perCent);
  SS->AddElement(H, fractionmass=52.5*perCent);

  // Optical properties of EJ-204
  G4double photonEnergyRI[] = {2.00*eV, 3.00*eV, 5.00*eV};
  G4double refractiveIndex[] = {1.58, 1.58, 1.58};
  G4double scintilFast[] = {1.0, 1.0, 1.0};
  // Values from EJ301-em.xls data table. To be incorporated...
  G4double photonEnergySF[] =
  { 3.108*eV, 3.089*eV, 3.069*eV, 3.051*eV,
    3.039*eV, 3.032*eV, 3.022*eV, 3.014*eV,
    2.995*eV, 2.988*eV, 2.981*eV, 2.974*eV,
    2.967*eV, 2.963*eV, 2.960*eV, 2.956*eV,
    2.952*eV, 2.946*eV, 2.939*eV, 2.935*eV,
    2.932*eV, 2.928*eV, 2.925*eV, 2.922*eV,
    2.918*eV, 2.908*eV, 2.891*eV, 2.882*eV,
    2.872*eV, 2.868*eV, 2.865*eV, 2.858*eV,
    2.841*eV, 2.825*eV, 2.820*eV, 2.814*eV,
    2.803*eV, 2.794*eV, 2.781*eV, 2.771*eV,
    2.763*eV, 2.747*eV, 2.732*eV, 2.717*eV,
    2.702*eV, 2.673*eV, 2.645*eV, 2.617*eV,
    2.590*eV, 2.563*eV, 2.537*eV, 2.511*eV,
    2.486*eV, 2.462*eV, 2.438*eV, 2.414*eV,
    2.391*eV }; //57
  // G4double scintilFast[] =
  // { 0.052, 0.078, 0.119, 0.168,
  //   0.210, 0.255, 0.353, 0.455,
  //   0.727, 0.797, 0.853, 0.892,
  //   0.925, 0.936, 0.948, 0.958,
  //   0.967, 0.981, 0.991, 0.996,
  //   1.000, 0.997, 0.993, 0.986,
  //   0.969, 0.895, 0.799, 0.762,
  //   0.729, 0.724, 0.721, 0.711,
  //   0.708, 0.704, 0.701, 0.697,
  //   0.680, 0.662, 0.632, 0.598,
  //   0.554, 0.490, 0.438, 0.401,
  //   0.364, 0.312, 0.273, 0.238,
  //   0.208, 0.183, 0.158, 0.136,
  //   0.119, 0.104, 0.092, 0.080,
  //   0.070 }; //57

  G4double absorption[] =  // Quoted to be 2.5-3m bulk absorption, we'll assume worst case.
  { BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //5
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //10
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //15
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //20
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //25
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //30
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //35
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //40
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //45
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val,//50
    BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, BC400_abs_length_val, //55
    BC400_abs_length_val, BC400_abs_length_val}; //57

  // Properties of liquid scintillator bulk medium
  const G4int nEntriesSF = sizeof(photonEnergySF)/sizeof(G4double);
  const G4int nEntriesRI = sizeof(photonEnergyRI)/sizeof(G4double);
  // Create material properties table and add properties
  G4MaterialPropertiesTable* scint_mpt = new G4MaterialPropertiesTable();
  // Add to material properties table
  scint_mpt->AddProperty("RINDEX",       photonEnergyRI, refractiveIndex, nEntriesRI)
  ->SetSpline(true);
  scint_mpt->AddProperty("ABSLENGTH",    photonEnergySF,   absorption,      nEntriesSF)
  ->SetSpline(true);
  scint_mpt->AddProperty("FASTCOMPONENT",photonEnergyRI,   scintilFast,     nEntriesRI)
  ->SetSpline(true);
  scint_mpt->AddConstProperty("SCINTILLATIONYIELD",11310/MeV);
  scint_mpt->AddConstProperty("RESOLUTIONSCALE",1.0);
  scint_mpt->AddConstProperty("FASTTIMECONSTANT", 2.4*ns); // "Decay time"
  // Associate material properties table with the liquid scintillator material
  SS->SetMaterialPropertiesTable(scint_mpt);

  //Add in Birk's constant for scintillator quenching at high LET
  SS->GetIonisation()->SetBirksConstant (BC400_Birks_Constant);

  // Define aluminium foil as a border surface --------------------------------
  G4OpticalSurface* foil = new G4OpticalSurface("foil");
  foil->SetType(dielectric_metal);
  foil->SetFinish(ground);
  foil->SetModel(unified);
  foil->SetSigmaAlpha(0);

  const G4int NUM = 2;

  G4double pp[NUM] = {2.038*eV, 4.144*eV};
  G4double specularlobe[NUM] = {0, 0};
  G4double specularspike[NUM] = {0, 0};
  G4double backscatter[NUM] = {0, 0};
  G4double reflectivity[NUM] = {0.9, 0.9};

  G4MaterialPropertiesTable* foil_mpt = new G4MaterialPropertiesTable();
  foil_mpt->AddProperty("SPECULARLOBECONSTANT",pp,specularlobe,NUM);
  foil_mpt->AddProperty("SPECULARSPIKECONSTANT",pp,specularspike,NUM);
  foil_mpt->AddProperty("BACKSCATTERCONSTANT",pp,backscatter,NUM);
  foil_mpt->AddProperty("REFLECTIVITY",pp,reflectivity,NUM);

  foil->SetMaterialPropertiesTable(foil_mpt);
  // --------------------------------------------------------------------------
  G4OpticalSurface* scintSurface = new G4OpticalSurface("scintSurface");
  scintSurface->SetType(dielectric_dielectric);
  scintSurface->SetFinish(polished);
  scintSurface->SetModel(unified);

  // Build world
  // Solid volume: volume's shape (geometrical dimensions)
  G4Box* solidWorld =
    new G4Box("World",    // name
      world_size, world_size, world_size); // size (x, y, z)
  // Logical volume: physical characteristics (material, detector elements etc)
  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld, // its solid volume
                        world_mat,  // its material
                        "World");   // its name
  // Physical volume: position
  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                // its rotation
                      G4ThreeVector(),  // its position
                      logicWorld,       // its logical volume
                      "World",          // its name
                      0,                // its mother volume (none for world)
                      false,            // no boolean operation
                      0,                // its copy number
                      checkOverlaps);    // check overlaps

  // Build voxel one
  // only need one logical volume if making repeated identical voxels
  // Solid
  G4Box* solidVoxel = new G4Box("Voxel", voxel_size, voxel_size, voxel_size);
  // Logical
  G4LogicalVolume* logicVoxel = new G4LogicalVolume(solidVoxel, SS, "Voxel");
  // Foil
  new G4LogicalSkinSurface("foil", logicVoxel, foil);

  // Build cladding for fibres
  G4Tubs* solidClad = new G4Tubs("Cladding", 0, clad_radius, fibre_half_length, 0, 2*pi);
  G4LogicalVolume* logicClad = new G4LogicalVolume(solidClad, clad_mat, "Cladding");

  // Build fibre optic cables
  G4Tubs* solidFibre = new G4Tubs("Fibre", 0, fibre_radius, fibre_half_length, 0, 2*pi);
  G4LogicalVolume* logicFibre = new G4LogicalVolume(solidFibre, fibre_mat, "Fibre");

  G4int copyNumber = 0;

  // // loop over array of voxels to create physical volumes
  SetNumberOfRows(2);
  SetNumberOfColumns(2);
  G4PVPlacement* physFibre = new G4PVPlacement(0, G4ThreeVector(), logicFibre, "Fibre", logicClad, false, copyNumber, checkOverlaps);
  fFibreVolumes.push_back(physFibre);
  for (int i =0; i<GetNumberOfRows(); i++) {
    for (int j=0; j<GetNumberOfColumns(); j++) {
      G4PVPlacement* physVoxel = new G4PVPlacement(0, G4ThreeVector(2*voxel_size*i,2*voxel_size*j,0), logicVoxel, "Voxel", logicWorld, false, copyNumber, checkOverlaps);
      G4PVPlacement* physClad = new G4PVPlacement(0, G4ThreeVector(2*voxel_size*i,2*voxel_size*j,fibre_half_length+voxel_size), logicClad, "Cladding", logicWorld, false, copyNumber, checkOverlaps);
      new G4LogicalBorderSurface("casing", physClad, physWorld, casing);
      new G4LogicalBorderSurface("casing", physWorld, physClad, casing);
      new G4LogicalBorderSurface("scintSurface", physVoxel, physFibre, scintSurface);
      new G4LogicalBorderSurface("scintSurface", physFibre, physVoxel, scintSurface);
      fVoxelVolumes.push_back(physVoxel);
      copyNumber++;
    }
  }

  fWorldVolume = physWorld;

  // Have to return physWorld
  return physWorld;
}
