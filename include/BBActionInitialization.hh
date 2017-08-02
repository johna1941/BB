#ifndef BBActionInitialization_hh
#define BBActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"

class BBActionInitialization : public G4VUserActionInitialization
{
public:
  void BuildForMaster() const;
  void Build() const;
};

#endif


