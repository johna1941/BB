#ifndef BBTrackingAction_hh
#define BBTrackingAction_hh

#include "G4UserTrackingAction.hh"

class BBTrackingAction : public G4UserTrackingAction
{
public:
  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
};

#endif
