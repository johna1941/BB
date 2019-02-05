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
  // Some dimensions
  const G4double worldHalfLength = 10.*m;
  const G4double boreHoleHalflength = worldHalfLength;
  const G4double boreHoleRadius = 10.*cm;
  const G4double neutronDetectorContainerHalflength = 5.*cm;
  const G4double neutronDetectorContainerRadius = 5.*cm;
  const G4double neutronDetectorHalflength = 4.9*cm;
  const G4double neutronDetectorRadius = 4.9*cm;

  // Useful names
  G4String name;
  G4bool checkOverlaps = true;

  // Materials
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4Material* boreHole_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* neutronDetectorContainer_mat = nist->FindOrBuildMaterial("G4_Fe");
  G4Material* neutronDetector_mat = nist->FindOrBuildMaterial("G4_He");

  name = "World";
  G4VSolid* world = new G4Box(name,worldHalfLength,worldHalfLength,worldHalfLength);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,world_mat,name);
  G4VPhysicalVolume* physWorld = new G4PVPlacement
  (G4Transform3D(),world_log,name,0,false,0);

  name = "BoreHole";
  G4VSolid* boreHole = new G4Tubs(name,0.,boreHoleRadius,boreHoleHalflength,0.,twopi);
  G4LogicalVolume* boreHole_log = new G4LogicalVolume(boreHole,boreHole_mat,name);
  new G4PVPlacement
  (G4Transform3D(),boreHole_log,name,world_log,false,0,checkOverlaps);

  name = "NeutronDetectorContainer";
  G4VSolid* neutronDetectorContainer
  = new G4Tubs(name,0.,neutronDetectorContainerRadius,neutronDetectorContainerHalflength,0.,twopi);
  G4LogicalVolume* neutronDetectorContainer_log
  = new G4LogicalVolume(neutronDetectorContainer,neutronDetectorContainer_mat,name);
  new G4PVPlacement
  (G4Translate3D(0.,0.,1.*m),neutronDetectorContainer_log,name,boreHole_log,false,0,checkOverlaps);
  new G4PVPlacement
  (G4Translate3D(0.,0.,0.5*m),neutronDetectorContainer_log,name,boreHole_log,false,1,checkOverlaps);

  name = "NeutronDetector";
  G4VSolid* neutronDetector = new G4Tubs(name,0.,neutronDetectorRadius,neutronDetectorHalflength,0.,twopi);
  G4LogicalVolume* neutronDetector_log = new G4LogicalVolume(neutronDetector,neutronDetector_mat,name);
  new G4PVPlacement
  (G4Transform3D(),neutronDetector_log,name,neutronDetectorContainer_log,false,0,checkOverlaps);

  // Visualaisation attributes
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  return physWorld;
}
