#ifndef BBData_hh
#define BBData_hh

// This is a lazy way of sharing memory. To avoid polluting the global
// namespace we define a distinctive namespace.

#include "globals.hh"
#include "G4Threading.hh"

#include <fstream>

class G4VPhysicalVolume;

namespace BB {

  // Global variables available to all threads
  extern G4Mutex outFileMutex;
  extern std::ofstream outFile;
  extern G4VPhysicalVolume* cubePV;

  // Thread local, but reset at begin of run
  // Run action must initialise a pointers to these quantities so that in MT mode,
  // workers can accumulate them (in sequential mode they are not used).
  extern G4ThreadLocal G4int nEvents;
  extern G4int* pMasterNEvents;
  extern G4ThreadLocal G4int nEventsWithATrackInCubePV;
  extern G4int* pMasterNEventsWithATrackInCubePV;

  // Thread local, reset at begin of event
  extern G4ThreadLocal G4bool cubeEncountered;
  extern G4ThreadLocal G4double eDepEvent;
}

#endif
