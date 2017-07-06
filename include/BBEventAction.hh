#ifndef BBEventAction_hh
#define BBEventAction_hh

#include "G4UserEventAction.hh"

#include "globals.hh"

class BBRunAction;

class BBEventAction: public G4UserEventAction
{
public:
  BBEventAction(BBRunAction* runAction);
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
private:
  BBRunAction* fpRunAction;
  // Thread local, reset at begin of event
  G4bool fCubeEncountered;
  G4double fEDepEvent;
};

#endif
