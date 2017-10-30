#ifndef BBData_hh
#define BBData_hh

#include "G4Threading.hh"

#include <fstream>

namespace BB {

  // Global variables available to all threads
  extern G4Mutex outFileMutex;
  extern std::ofstream outFile;

}

#endif
