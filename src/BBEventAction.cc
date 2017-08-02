#include "BBEventAction.hh"

#include "BBData.hh"
#include "BBRunAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4AutoLock.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

BBEventAction::BBEventAction()
: fCubeEncountered(false)
, fEDepEvent(0.)
{}

void BBEventAction::BeginOfEventAction(const G4Event*)
{
//  G4cout << "BBEventAction::BeginOfEventAction" << G4endl;
  fCubeEncountered = false;
  fEDepEvent = 0.;
}

void BBEventAction::EndOfEventAction(const G4Event* event)
{   
//  G4cout << "BBEventAction::EndOfEventAction" << G4endl;

  const G4UserRunAction* constUserRunAction = G4RunManager::GetRunManager()->GetUserRunAction();
  G4UserRunAction* userRunAction = const_cast<G4UserRunAction*>(constUserRunAction);
  BBRunAction* runAction = static_cast<BBRunAction*>(userRunAction);

  ++runAction->fNEvents;
  if (fCubeEncountered) ++runAction->fNEventsWithATrackInCubePV;

  // Always use a lock when writing a file in MT mode.
  // No action in case of sequential mode.
  G4AutoLock lock(&BB::outFileMutex);
  BB::outFile
  << "#,EventID,eDepEvent/MeV"
  << std::endl;
  BB::outFile
  << "#," << event->GetEventID()
  << ',' << fEDepEvent/MeV
  << std::endl;
}
