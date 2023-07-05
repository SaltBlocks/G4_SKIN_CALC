#pragma once
#include <G4VSensitiveDetector.hh>

class SensitiveDetector : public G4VSensitiveDetector
{
public:
	SensitiveDetector(const G4String& name);
	~SensitiveDetector() override = default;
	void Initialize(G4HCofThisEvent* hce) override;
	G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
	void EndOfEvent();
	G4double getEnergyDeposited();
	G4double getEnergyDepositedSquared();
	void reset();
private:
	G4double fEdepCurrent;
	G4double fEdepRun;
	G4double fEdepSquared;
};