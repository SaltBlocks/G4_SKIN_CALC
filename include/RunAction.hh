#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4Run.hh"
#include "G4UserRunAction.hh"
#include "G4RunManager.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Detector.hh"
#include "Generator.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
public:
	RunAction();
	~RunAction() override = default;

	void BeginOfRunAction(const G4Run*) override;
	void EndOfRunAction(const G4Run*) override;
};
#endif
