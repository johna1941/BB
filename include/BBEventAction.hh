#ifndef BBEventAction_hh
#define BBEventAction_hh

#include "G4UserEventAction.hh"

class BBEventAction : public G4UserEventAction
{
public:
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
};

#endif
