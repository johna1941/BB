#ifndef BBEventAction_hh
#define BBEventAction_hh

#include "G4UserEventAction.hh"

#include "globals.hh"

class BBRunAction;
class BBSteppingAction;

class BBEventAction: public G4UserEventAction
{
  friend BBSteppingAction;
public:
  BBEventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
private:
  // Thread local, reset at begin of event
  G4bool fCubeEncountered;
  G4double fEDepEvent;
};

#endif
