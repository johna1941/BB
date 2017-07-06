#ifndef BBRunAction_hh
#define BBRunAction_hh

#include "G4UserRunAction.hh"

class BBEventAction;

class BBRunAction : public G4UserRunAction
{
  friend BBEventAction;
public:
  BBRunAction();
  ~BBRunAction();
  void BeginOfRunAction(const G4Run*);
  void   EndOfRunAction(const G4Run*);
private:
  static BBRunAction* fpMasterRunAction;
  // Thread local, but reset at begin of run
  G4int fNEvents;
  G4int fNEventsWithATrackInCubePV;
};

#endif
