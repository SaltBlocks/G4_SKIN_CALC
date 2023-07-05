#include "EventAction.hh"

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction)
{
}

/**
* Called when a new Tc-99m particle is spawned.
*/
void EventAction::BeginOfEventAction(const G4Event* event)
{
}

/**
* Called when the particle and all daughters have been removed from the simulation.
*/
void EventAction::EndOfEventAction(const G4Event* event)
{
	// Inform the SensitiveDetector that the event has ended.
	static_cast<const Detector*>(
		G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetSensitiveDetector()->EndOfEvent();
}
