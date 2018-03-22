#include "G4MTRunManager.hh"
#include "G4PhysListFactory.hh"
#include "BBDetectorConstruction.hh"
#include "G4OpticalPhysics.hh"
#include "BBActionInitialization.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "MultiVoxelDetectorConstruction.hh"

#include <ctime>

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    // Do this before any other actions to capture all output
    ui = new G4UIExecutive(argc, argv);
  }

  // Use the current time (in seconds) as the random number seed
  G4Random::setTheSeed(time(0));  // Comment out if you want the same sequence

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(8);
#else
  G4RunManager* runManager = new G4RunManager;
#endif

//  runManager->SetUserInitialization(new BBDetectorConstruction);
  runManager->SetUserInitialization(new MultiVoxelDetectorConstruction);

  G4int verbose;
  G4PhysListFactory factory;
  G4VModularPhysicsList* physList = factory.GetReferencePhysList("FTFP_BERT");
  physList->RegisterPhysics(new G4OpticalPhysics);
  physList->SetVerboseLevel(verbose = 1);
  runManager->SetUserInitialization(physList);

  runManager->SetUserInitialization(new BBActionInitialization);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}
