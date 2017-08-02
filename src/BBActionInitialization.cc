#include "BBActionInitialization.hh"

#include "BBPrimaryGeneratorAction.hh"
#include "BBRunAction.hh"
#include "BBEventAction.hh"
#include "BBTrackingAction.hh"
#include "BBSteppingAction.hh"

void BBActionInitialization::BuildForMaster() const
{
  SetUserAction(new BBRunAction);
}

void BBActionInitialization::Build() const
{
  SetUserAction(new BBPrimaryGeneratorAction);
  SetUserAction(new BBRunAction);
  SetUserAction(new BBEventAction);
  SetUserAction(new BBTrackingAction);
  SetUserAction(new BBSteppingAction);
}
