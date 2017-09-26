#include "BBData.hh"

// Global variables available to all threads
G4Mutex BB::outFileMutex = G4MUTEX_INITIALIZER;
std::ofstream BB::outFile("outFile.csv");
G4VPhysicalVolume* BB::cubePV = 0;
