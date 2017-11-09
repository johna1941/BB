#ifndef BBSteppingAction_hh
#define BBSteppingAction_hh

#include "G4UserSteppingAction.hh"

class BBDetectorConstruction;
class BBEventAction;

class BBSteppingAction: public G4UserSteppingAction
{
public:
  BBSteppingAction();
  void UserSteppingAction(const G4Step*);
private:
  BBDetectorConstruction* fpDetectorConstruction;
  BBEventAction* fpEventAction;

};

#endif
