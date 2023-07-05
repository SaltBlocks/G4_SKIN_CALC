#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "RunAction.hh"

class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction* runAction);
	~EventAction() override = default;

	void BeginOfEventAction(const G4Event* event) override;
	void EndOfEventAction(const G4Event* event) override;

	void AddEdep(G4double edep) { fEdep += edep; }

private:
	RunAction* fRunAction = nullptr;
	G4double fEdep = 0.;
};
#endif
