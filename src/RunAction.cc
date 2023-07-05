#include "RunAction.hh"

RunAction::RunAction()
{
	// add new units for dose
	const G4double milligray = 1.e-3 * gray;
	const G4double microgray = 1.e-6 * gray;
	const G4double nanogray = 1.e-9 * gray;
	const G4double picogray = 1.e-12 * gray;

	new G4UnitDefinition("milligray", "milliGy", "Dose", milligray);
	new G4UnitDefinition("microgray", "microGy", "Dose", microgray);
	new G4UnitDefinition("nanogray", "nanoGy", "Dose", nanogray);
	new G4UnitDefinition("picogray", "picoGy", "Dose", picogray);
}

/**
* Handle the start of the simulation.
*/
void RunAction::BeginOfRunAction(const G4Run*)
{
	// inform the runManager to save random number seed
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);

	// reset the detector
	const auto detConstruction = static_cast<const Detector*>(
		G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	detConstruction->GetSensitiveDetector()->reset();
}

/**
* Handle the simulation ending.
*/
void RunAction::EndOfRunAction(const G4Run* run)
{
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;

	// Compute dose = total energy deposit in a run and its variance
	const auto detConstruction = static_cast<const Detector*>(
		G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	G4double edep = detConstruction->GetSensitiveDetector()->getEnergyDeposited();
	G4double edep2 = detConstruction->GetSensitiveDetector()->getEnergyDepositedSquared();

	G4double rms = edep2 - edep * edep / nofEvents;
	if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

	
	G4double mass = detConstruction->GetScoringVolume()->GetMass();
	G4double energyPerTransform = edep / nofEvents;
	G4double dose = edep / mass;
	G4double rmsDose = rms / mass;

	// Run conditions
	//  note: There is no primary generator action object for "master"
	//        run manager for multi-threaded mode.
	const auto generatorAction = static_cast<const Generator*>(
		G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
	G4String runCondition;
	if (generatorAction)
	{
		const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
		runCondition += particleGun->GetParticleDefinition()->GetParticleName();
		runCondition += " of ";
		G4double particleEnergy = particleGun->GetParticleEnergy();
		runCondition += G4BestUnit(particleEnergy, "Energy");
	}

	// Print
	//
	if (IsMaster()) {
		G4cout
			<< G4endl
			<< "--------------------End of Global Run-----------------------";
		G4cout
			<< G4endl
			<< " The run consisted of " << nofEvents << " " << runCondition
			<< G4endl
			<< "Dose: "
			<< energyPerTransform / keV << " keV per transformation" << G4endl
			<< G4BestUnit(dose, "Dose") << " rms = " << G4BestUnit(rmsDose, "Dose") << G4endl
			<< "In mass of " << G4BestUnit(mass, "Mass") << G4endl
			<< G4BestUnit((dose / nofEvents) * pow(10, 6) * 60 * 60, "Dose") << " / MBq x h"
			<< G4endl
			<< "------------------------------------------------------------"
			<< G4endl
			<< G4endl;
	}
	
}
