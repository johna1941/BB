#include "BBActionInitialization.hh"

#include "BBPrimaryGeneratorAction.hh"
#include "BBRunAction.hh"
#include "BBEventAction.hh"
#include "BBTrackingAction.hh"
#include "BBSteppingAction.hh"

void BBActionInitialization::BuildForMaster() const
{
  G4UserRunAction* runAction = new BBRunAction;
  SetUserAction(runAction);
}

void BBActionInitialization::Build() const
{
  G4VUserPrimaryGeneratorAction* primaryGeneratorAction
  = new BBPrimaryGeneratorAction;
  BBRunAction* runAction = new BBRunAction;
  BBEventAction* eventAction = new BBEventAction(runAction);
  G4UserTrackingAction* trackingAction = new BBTrackingAction;
  G4UserSteppingAction* steppingAction = new BBSteppingAction(eventAction);

  SetUserAction(primaryGeneratorAction);
  SetUserAction(runAction);
  SetUserAction(eventAction);
  SetUserAction(trackingAction);
  SetUserAction(steppingAction);
}
