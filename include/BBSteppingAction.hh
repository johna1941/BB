#ifndef BBSteppingAction_hh
#define BBSteppingAction_hh

#include "G4UserSteppingAction.hh"

class BBSteppingAction: public G4UserSteppingAction
{
public:
  BBSteppingAction() {}
  void UserSteppingAction(const G4Step*);
};

#endif
