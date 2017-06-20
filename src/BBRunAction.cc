#include "BBRunAction.hh"

#include "BBData.hh"

#include "G4Run.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

BBRunAction::BBRunAction()
{}

BBRunAction::~BBRunAction()
{}

void BBRunAction::BeginOfRunAction(const G4Run*)
{
  G4cout
  << "BBRunAction::BeginOfRunAction: Thread: "
  << G4Threading::G4GetThreadId()
  << G4endl;

  BB::nEvents = 0;
  BB::nEventsWithATrackInCubePV = 0;
  BB::nMasterEvents = 0;
  BB::nMasterEventsWithATrackInCubePV = 0;
}

namespace {
  G4Mutex mutex = G4MUTEX_INITIALIZER;
}

void BBRunAction::EndOfRunAction(const G4Run* run)
{
  if (G4Threading::IsWorkerThread()) {

    G4cout
    << "BBRunAction::EndOfRunAction: Thread: "
    << G4Threading::G4GetThreadId()
    << ", " << BB::nEvents << " events"
    << G4endl;
    
    // Always use a lock when writing to a location that is shared by threads
    G4AutoLock lock(&mutex);
    BB::nMasterEvents += BB::nEvents;
    BB::nMasterEventsWithATrackInCubePV += BB::nEventsWithATrackInCubePV;

  } else {  // Master thread

    G4cout
    << "BBRunAction::EndOfRunAction: Master thread: "
    << BB::nMasterEvents << " events"
    << G4endl;
    
    BB::outFile
    << "#,RunId,nEvents,nEventsWithATrackInCubePV"
    << std::endl;
    BB::outFile
    << "#," << run->GetRunID()
    << ',' << BB::nMasterEvents
    << ',' << BB::nMasterEventsWithATrackInCubePV
    << std::endl;
  }
}
