#include "BBRunAction.hh"

#include "BBData.hh"

#include "G4Run.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

BBRunAction* BBRunAction::fpMasterRunAction = nullptr;

BBRunAction::BBRunAction()
{}

BBRunAction::~BBRunAction()
{}

void BBRunAction::BeginOfRunAction(const G4Run*)
{
//  G4cout
//  << "BBRunAction::BeginOfRunAction: Thread: "
//  << G4Threading::G4GetThreadId()
//  << G4endl;

  if (!G4Threading::IsWorkerThread()) {
    fpMasterRunAction = this;
  }

  fNEvents = 0;
  fNEventsWithATrackInCubePV = 0;
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
    << ", " << fNEvents << " events"
    << G4endl;

    // Update master quantities
    // Always use a lock when writing to a location that is shared by threads
    G4AutoLock lock(&mutex);
    fpMasterRunAction->fNEvents += fNEvents;
    fpMasterRunAction->fNEventsWithATrackInCubePV += fNEventsWithATrackInCubePV;

  } else {  // Master thread

    G4cout
    << "BBRunAction::EndOfRunAction: Master thread: "
    << fNEvents << " events"
    << G4endl;
    
    BB::outFile
    << "#,RunId,nEvents,nEventsWithATrackInCubePV"
    << std::endl;
    BB::outFile
    << "#," << run->GetRunID()
    << ',' << fNEvents
    << ',' << fNEventsWithATrackInCubePV
    << std::endl;
  }
}
