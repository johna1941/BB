#ifndef BBDetectorConstruction_hh
#define BBDetectorConstruction_hh 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class BBDetectorConstruction : public G4VUserDetectorConstruction
{
  friend class BBSteppingAction;
public:
  BBDetectorConstruction()
  : fpCubePV(0)
  {}
  G4VPhysicalVolume* Construct();
private:
  G4VPhysicalVolume* fpCubePV;
};

#endif

