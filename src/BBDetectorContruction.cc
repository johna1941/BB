#include "BBDetectorConstruction.hh"

#include "BBData.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"

G4VPhysicalVolume* BBDetectorConstruction::Construct()
{
  // Useful names
  G4String name, symbol;
  G4bool checkOverlaps = true;

  // Materials
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* air_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* water_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4Material* pipe_mat = nist->FindOrBuildMaterial("G4_GLASS_LEAD");

  // Optical properties
  G4int size = 2;  // Size of following arrays
  G4double energy[] = {2.038*eV, 4.144*eV};
  G4double air_index[] = {1.001, 1.0012};
  G4double water_index[] = {1.35, 1.40};
  G4double pipe_index[] = {1.5, 1.6};
  G4MaterialPropertiesTable* air_MPT = new G4MaterialPropertiesTable();
  air_MPT->AddProperty("RINDEX",energy,air_index,size);
  air_mat->SetMaterialPropertiesTable(air_MPT);
  G4MaterialPropertiesTable* water_MPT = new G4MaterialPropertiesTable();
  water_MPT->AddProperty("RINDEX",energy,water_index,size);
  water_mat->SetMaterialPropertiesTable(water_MPT);
  G4MaterialPropertiesTable* pipe_MPT = new G4MaterialPropertiesTable();
  pipe_MPT->AddProperty("RINDEX",energy,pipe_index,size);
  pipe_mat->SetMaterialPropertiesTable(pipe_MPT);

  name = "World";
  G4VSolid* world = new G4Box(name,5.*m,5.*m,5.*m);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,air_mat,name);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* physWorld = new G4PVPlacement
  (G4Transform3D(),world_log,name,0,false,0);

  name = "Water";
  G4double waterHalfLength = 1.*m;
  G4VSolid* water
  = new G4Box(name, waterHalfLength, waterHalfLength, waterHalfLength);
  G4LogicalVolume* water_log = new G4LogicalVolume(water,water_mat,name);
  fpCubePV = new G4PVPlacement
  (G4Transform3D(),water_log,name,world_log,false,0,checkOverlaps);

  name = "Pipe";
  G4double pipeHalfLength = 1.*m;
  G4VSolid* pipe = new G4Tubs(name, 0., 1.*cm, pipeHalfLength, 0., twopi);
  G4LogicalVolume* pipe_log = new G4LogicalVolume(pipe,pipe_mat,name);
  fpPipePV = new G4PVPlacement
  (G4Translate3D(0., 0., waterHalfLength + pipeHalfLength),
   pipe_log,name,world_log,false,0,checkOverlaps);

  return physWorld;
}
