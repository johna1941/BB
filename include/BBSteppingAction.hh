#ifndef AnnihilationPhotonsSteppingAction_hh
#define AnnihilationPhotonsSteppingAction_hh

#include "G4UserSteppingAction.hh"

#include "BBEventAction.hh"

#include "globals.hh"

class BBSteppingAction: public G4UserSteppingAction
{
public:
  BBSteppingAction(BBEventAction*);
  virtual void UserSteppingAction(const G4Step*);
private:
  BBEventAction* fpEventAction;
};

#endif
