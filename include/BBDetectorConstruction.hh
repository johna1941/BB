#ifndef BBDetectorConstruction_hh
#define BBDetectorConstruction_hh 1

#include "G4VUserDetectorConstruction.hh"

class BBDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  virtual G4VPhysicalVolume* Construct();
};

#endif

