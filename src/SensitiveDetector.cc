#include "SensitiveDetector.hh"

/**
* Basic SensitiveDetector that functions as a Calorimeter.
*/
SensitiveDetector::SensitiveDetector(const G4String& name)
	: G4VSensitiveDetector(name)
{
	fEdepCurrent = 0;
	fEdepRun = 0;
	fEdepSquared = 0;
}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
}

/**
* Register hits within the scoring volume and store the energy deposited.
*/
G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
	G4double edepStep = step->GetTotalEnergyDeposit() * step->GetTrack()->GetWeight();
	fEdepCurrent += edepStep;
	return true;
}

/**
* Signals that the simulation of the current particle has ended.
*/
void SensitiveDetector::EndOfEvent()
{
	fEdepRun += fEdepCurrent;
	fEdepSquared += fEdepCurrent * fEdepCurrent;
	fEdepCurrent = 0;
}

/**
* Ge the energy deposited since the start of the run.
*/
G4double SensitiveDetector::getEnergyDeposited()
{
	return fEdepRun + fEdepCurrent;
}

/**
* Get the sum of squares of energy deposited in each event since the start of the run.
*/
G4double SensitiveDetector::getEnergyDepositedSquared()
{
	return fEdepSquared + fEdepCurrent * fEdepCurrent;
}

/**
* Reset the sensitive detector.
*/
void SensitiveDetector::reset()
{
	fEdepCurrent = 0;
	fEdepRun = 0;
	fEdepSquared = 0;
}
