#include "BBEventAction.hh"

#include "BBData.hh"
#include "G4SystemOfUnits.hh"

#include "G4Event.hh"

void BBEventAction::BeginOfEventAction(const G4Event*)
{
//  G4cout << "BBEventAction::BeginOfEventAction" << G4endl;
  BB::cubeEncountered = false;
  BB::eDepEvent = 0.;
}

void BBEventAction::EndOfEventAction(const G4Event* event)
{   
//  G4cout << "BBEventAction::EndOfEventAction" << G4endl;

  ++BB::nEvents;
  if (BB::cubeEncountered) ++BB::nEventsWithATrackInCubePV;

  // Always use a lock when writing a file in MT mode
  G4AutoLock lock(&BB::outFileMutex);
  BB::outFile
  << "#,EventID,eDepEvent/MeV"
  << std::endl;
  BB::outFile
  << "#," << event->GetEventID()
  << ',' << BB::eDepEvent/MeV
  << std::endl;
}
