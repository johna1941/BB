#ifndef BBActionInitialization_hh
#define BBActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"

class BBActionInitialization : public G4VUserActionInitialization
{
public:
  virtual void BuildForMaster() const;
  virtual void Build() const;
};

#endif


