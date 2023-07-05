#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction)
{
}

/**
* Used to eliminate Tc-99 particles.
*/
void SteppingAction::UserSteppingAction(const G4Step* step)
{
	// Kill the Tc-99m after it decays to Tc-99.
	if (step->GetTrack()->GetParticleDefinition()->GetAtomicNumber() == 43)
	{
		step->GetTrack()->SetTrackStatus(G4TrackStatus::fStopAndKill);
	}
}

