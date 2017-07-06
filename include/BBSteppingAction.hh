#ifndef AnnihilationPhotonsSteppingAction_hh
#define AnnihilationPhotonsSteppingAction_hh

#include "G4UserSteppingAction.hh"

#include "globals.hh"

class BBSteppingAction: public G4UserSteppingAction
{
public:
  virtual void UserSteppingAction(const G4Step*);
private:
  G4bool fCubeEncountered;
  G4double fEDepEvent;
};

#endif
