#include "Generator.hh"

/*
* Setup the particle generator. At construction, no particle definition is given because the IonTable has not been initialized at this point.
*/
Generator::Generator()
{
    G4int n_particle = 1;
    // Set up the particle gun
    particleGun = new G4ParticleGun(n_particle);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ThreeVector position(0., 0., 0.);
    G4ThreeVector momentum(0., 0., 1.);
    
    particleGun->SetParticlePosition(position);
    particleGun->SetParticleMomentumDirection(momentum);
    particleGun->SetParticleMomentum(0 * GeV);
    particleGun->SetParticleDefinition(particleTable->FindParticle("geantino")); // Use non-existent geantino particle as placeholder.
}

Generator::~Generator()
{
    delete particleGun;
}

/**
* Generate a Tc-99m particle in the simulator.
*/
void Generator::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleDefinition* particle = particleGun->GetParticleDefinition();
    if (particle == G4Geantino::Geantino())
    {
        G4int Z = 43;
        G4int A = 99;

        G4double charge = 0. * eplus;
        G4double energy = 142.683 * keV;

        G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
        particleGun->SetParticleDefinition(ion);
        particleGun->SetParticleCharge(charge);
    }

    // Generate random coordinates within the Cylinder
    G4double theta = G4UniformRand() * 2.0 * M_PI; // Random angle between 0 and 2pi.
    G4double radius = sqrt(G4UniformRand()) * fluidCylinderRadius; // Radius using square root to distribute points uniformly within the disk

    // Convert spherical coordinates to Cartesian coordinates
    G4double xCoord = radius * cos(theta);
    G4double yCoord = radius * sin(theta);
    G4double zCoord = (2.0 * G4UniformRand() - 1.0) * (fluidCylinderHeight) / 2.0;
    
    particleGun->SetParticlePosition(G4ThreeVector(xCoord, yCoord, zCoord));
    
    // Generate the primary particle and add it to the event
    particleGun->GeneratePrimaryVertex(anEvent);
}
