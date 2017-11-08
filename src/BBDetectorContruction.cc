#include "BBDetectorConstruction.hh"

#include "BBData.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
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
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* water_mat = nist->FindOrBuildMaterial("G4_WATER");

  name = "World";
  G4VSolid* world = new G4Box(name,5.*m,5.*m,5.*m);
  G4LogicalVolume* world_log = new G4LogicalVolume(world,world_mat,name);
  world_log->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* physWorld = new G4PVPlacement
  (G4Transform3D(),world_log,name,0,false,0);

  name = "Water";
  G4double waterHalfLength = 1.*m;
  G4VSolid* water = new G4Box(name, waterHalfLength, waterHalfLength, waterHalfLength);
  G4LogicalVolume* water_log = new G4LogicalVolume(water,water_mat,name);
  fpCubePV = new G4PVPlacement
  (G4Transform3D(),water_log,name,world_log,false,0,checkOverlaps);

  return physWorld;
}
