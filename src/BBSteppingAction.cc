#include "BBSteppingAction.hh"

#include "BBEventAction.hh"
#include "BBDetectorConstruction.hh"
#include "BBData.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"
#include "G4VProcess.hh"

void BBSteppingAction::UserSteppingAction(const G4Step* step)
{
//  G4cout << "BBSteppingAction::UserSteppingAction" << G4endl;

  // Get event action pointer (so we can send data)
  const G4UserEventAction* constUserEventAction
  = G4RunManager::GetRunManager()->GetUserEventAction();
  G4UserEventAction* userEventAction
  = const_cast<G4UserEventAction*>(constUserEventAction);
  BBEventAction* eventAction
  = static_cast<BBEventAction*>(userEventAction);

  // Get detector construction pointer (so we can access volume data)
  const G4VUserDetectorConstruction* constUserDetectorConstruction
  = G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  G4VUserDetectorConstruction* userDetectorConstruction
  = const_cast<G4VUserDetectorConstruction*>(constUserDetectorConstruction);
  BBDetectorConstruction* detectorConstruction
  = static_cast<BBDetectorConstruction*>(userDetectorConstruction);

  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4StepPoint* postStepPoint = step->GetPostStepPoint();

  G4double eDep = step->GetTotalEnergyDeposit();

  G4VPhysicalVolume* prePV = preStepPoint->GetPhysicalVolume();
  G4VPhysicalVolume* postPV = postStepPoint->GetPhysicalVolume();

  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particleDefinition = track->GetDefinition();
  const G4VProcess* creatorProcess = track->GetCreatorProcess();

  const G4VProcess* processDefinedStep = postStepPoint->GetProcessDefinedStep();

  if (prePV == detectorConstruction->fpCubePV) {
    // Mark event as having a track in specified volume
    eventAction->fCubeEncountered = true;
    // Accumulate energy deposit
    eventAction->fEDepEvent += eDep;
  }

  // Always use a lock when writing a file in MT mode
  G4AutoLock lock(&BB::outFileMutex);
  static G4bool first = true;
  if (first) {
    first = false;
    // Write header
    BB::outFile
    << "#,TrackID,name,prePV,copyNo,postPV,copyNo"
    ",creatorProcess,processDefinedStep,eDep/MeV"
    << std::endl;
  }
  BB::outFile
  << ',' << track->GetTrackID()
  << ',' << particleDefinition->GetParticleName()
  << ',' << (prePV? prePV->GetName(): "none")
  << ',' << (prePV? prePV->GetCopyNo(): 0)
  << ',' << (postPV? postPV->GetName(): "none")
  << ',' << (postPV? postPV->GetCopyNo(): 0)
  << ',' << (creatorProcess? creatorProcess->GetProcessName(): "none")
  << ',' << (processDefinedStep? processDefinedStep->GetProcessName(): "none")
  << ',' << eDep/MeV
  << std::endl;

  return;
}
