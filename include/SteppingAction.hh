#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "EventAction.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(EventAction* eventAction);
	~SteppingAction() override = default;

	// method from the base class
	void UserSteppingAction(const G4Step*) override;
private:
	EventAction* fEventAction = nullptr;
};
#endif
