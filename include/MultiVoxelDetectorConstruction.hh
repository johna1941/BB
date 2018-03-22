#ifndef MultiVoxelDetectorConstruction_hh
#define MultiVoxelDetectorConstruction_hh 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class MultiVoxelDetectorConstruction : public G4VUserDetectorConstruction
{
  friend class BBSteppingAction;
public:
  MultiVoxelDetectorConstruction() {};
  G4VPhysicalVolume* Construct();
  int GetNumberOfRows() {return fNumberOfRows;}
  int GetNumberOfColumns() {return fNumberOfColumns;}
  void SetNumberOfRows(int n) {fNumberOfRows = n;}
  void SetNumberOfColumns(int n) {fNumberOfColumns = n;}
private:
  std::vector<G4VPhysicalVolume*> fVoxelVolumes;
  std::vector<G4VPhysicalVolume*> fFibreVolumes;
  G4VPhysicalVolume* fWorldVolume;
  int fNumberOfRows, fNumberOfColumns;
};

#endif

