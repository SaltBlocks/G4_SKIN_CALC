#include "ActionInitialization.hh"

void ActionInitialization::BuildForMaster() const
{
	RunAction* runAction = new RunAction();
	SetUserAction(runAction);
}

/**
 * Setup actions for Generating particles, registering ending of events and removing Tc-99 particles before further decay occurs.
 */
void ActionInitialization::Build() const
{
	SetUserAction(new Generator());

	RunAction* runAction = new RunAction();
	SetUserAction(runAction);
	
	EventAction* eventAction = new EventAction(runAction);
	SetUserAction(eventAction);

	SetUserAction(new SteppingAction(eventAction));
}
