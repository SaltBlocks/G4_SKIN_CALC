/**
 * \mainpage notitle
 * Homepage: <http://physino.xyz/gears>
 */
using namespace std;

#include <G4RunManager.hh>
#include <G4PhysListFactory.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4GeneralParticleSource.hh>
#include <G4ParticleGun.hh>
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"
#include "G4VUserActionInitialization.hh"
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <G4UImanager.hh> // needed for g4.10 and above
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include <G4EmParameters.hh>

#include "Detector.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4hIonisation.hh"

/**
 * The main function that calls individual components.
 */
int main(int argc, char** argv)
{
    // construct the default run manager
    G4RunManager* run = new G4RunManager; // Create run control
    
    // Construct the detector.
    run->SetUserInitialization(new Detector);
    
    // Setup the physics
    G4PhysListFactory fFactory;
    G4VModularPhysicsList* phys = fFactory.GetReferencePhysList("QGSP_BIC_EMZ");
    phys->RegisterPhysics(new G4DecayPhysics);
    phys->RegisterPhysics(new G4RadioactiveDecayPhysics);
    phys->SetVerboseLevel(2);
    run->SetUserInitialization(phys);
    
    // Setup ActionList.
    run->SetUserInitialization(new ActionInitialization);
    
    // Setup Visualization
    G4VisManager* vis = new G4VisExecutive("quiet"); // visualization
    vis->Initialize();
   
    // Initialize run manager.
    run->Initialize();

    // Setup verbosity
    G4UImanager::GetUIpointer()->ApplyCommand("/tracking/verbose 0");
    
    // Run
    G4UImanager::GetUIpointer()->ApplyCommand("/run/beamOn 1000000");

    if (argc != 1) { // batch mode
        G4String cmd = "/control/execute ";
        G4UImanager::GetUIpointer()->ApplyCommand(cmd + argv[1]);
    }
    else { // interactive mode
        // check available UI automatically in the order of Qt, tsch, Xm
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        
        // Setup visualization
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/open OGL");
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/drawVolume");
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/set/autoRefresh true");
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/scene/add/trajectories smooth");
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/geometry/set/visibility World ! false");
        G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/set/style surface");
        
        ui->SessionStart();
        delete ui;
    }
    // clean up
    delete vis; delete run;
    return 0;
}
