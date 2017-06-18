#include "BBData.hh"

G4Mutex BB::outFileMutex = G4MUTEX_INITIALIZER;
std::ofstream BB::outFile("outFile.csv");

G4VPhysicalVolume* BB::cubePV = nullptr;
G4int BB::nMasterEvents = 0;
G4int BB::nMasterEventsWithATrackInCubePV = 0;

// Worker quantities
G4ThreadLocal G4int BB::nEvents = 0;
G4ThreadLocal G4bool BB::cubeEncountered = false;
G4ThreadLocal G4int BB::nEventsWithATrackInCubePV = 0;
G4ThreadLocal G4double BB::eDepEvent = 0.;
