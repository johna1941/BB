#include "BBPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

BBPrimaryGeneratorAction::BBPrimaryGeneratorAction()
{
  fpParticleGun  = new G4GeneralParticleSource;
}

BBPrimaryGeneratorAction::~BBPrimaryGeneratorAction()
{
  delete fpParticleGun;
}

void BBPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fpParticleGun->GeneratePrimaryVertex(anEvent);
}
