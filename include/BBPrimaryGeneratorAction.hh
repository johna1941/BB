#ifndef BBPrimaryGeneratorAction_hh
#define BBPrimaryGeneratorAction_hh 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;

class BBPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  BBPrimaryGeneratorAction();
  virtual ~BBPrimaryGeneratorAction();
  virtual void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* fpParticleGun;
};

#endif
