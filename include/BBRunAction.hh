#ifndef BBRunAction_hh
#define BBRunAction_hh

#include "G4UserRunAction.hh"

class BBRunAction : public G4UserRunAction
{
public:
  BBRunAction();
  ~BBRunAction();
  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
};

#endif
