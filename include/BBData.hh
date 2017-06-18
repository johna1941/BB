#ifndef BBData_hh
#define BBData_hh

#include "globals.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

#include <fstream>

class G4VPhysicalVolume;

// This is a lazy way of sharing memory. To avoid polluting the global
// namespace we define our own distinctive namespace.
namespace BB {
  extern G4Mutex outFileMutex;
  extern std::ofstream outFile;
  extern G4VPhysicalVolume* cubePV;
  extern G4int nMasterEvents;
  extern G4int nMasterEventsWithATrackInCubePV;
  // Worker quantities
  extern G4ThreadLocal G4bool cubeEncountered;
  extern G4ThreadLocal G4int nEvents;
  extern G4ThreadLocal G4int nEventsWithATrackInCubePV;
  extern G4ThreadLocal G4double eDepEvent;
}

#endif
