#include "G4MTRunManager.hh"
#include "G4PhysListFactory.hh"
#include "BBDetectorConstruction.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "BBActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include <cstdio>

int main(int argc,char** argv)
{
  // Do this first to capture all output
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  int seed = time(0);
  seed |= 1;  // Make sure it's odd
  //  seed = 1502758967;  // Activate this line with a fixed seed if desired
  CLHEP::HepRandom::setTheSeed(seed);
  G4cout << "Random engine seeded with " << seed << G4endl;

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(8);
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new BBDetectorConstruction);

  G4int verbose;
  G4PhysListFactory factory;
  G4VModularPhysicsList* physList = factory.GetReferencePhysList("FTFP_BERT");
  physList->SetVerboseLevel(verbose = 1);
  physList->ReplacePhysics(new G4EmLivermorePolarizedPhysics);
  runManager->SetUserInitialization(physList);

  runManager->SetUserInitialization(new BBActionInitialization);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/control/execute vis.mac");

  ui->SessionStart();

  delete ui;
  delete visManager;
  delete runManager;
}
