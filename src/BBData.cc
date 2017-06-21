#include "BBData.hh"

// Global variables available to all threads
G4Mutex BB::outFileMutex = G4MUTEX_INITIALIZER;
std::ofstream BB::outFile("outFile.csv");
G4VPhysicalVolume* BB::cubePV = nullptr;

// Thread local, but reset at begin of run
// Run action must initialise a pointers to these quantities so that in MT mode,
// workers can accumulate them (in sequential mode they are not used).
G4ThreadLocal G4int BB::nEvents = 0;
G4int* BB::pMasterNEvents = nullptr;
G4ThreadLocal G4int BB::nEventsWithATrackInCubePV = 0;
G4int* BB::pMasterNEventsWithATrackInCubePV = nullptr;

// Thread local, reset at begin of event
G4ThreadLocal G4bool BB::cubeEncountered = false;
G4ThreadLocal G4double BB::eDepEvent = 0.;
