#ifndef ACTIONINIT_HH
#define ACTIONINIT_HH

#include "G4VUserActionInitialization.hh"
#include "Generator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
	ActionInitialization() = default;
	~ActionInitialization() = default;

	void BuildForMaster() const ;
	void Build() const;
};
#endif
