#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "G4Geantino.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"
#include "Detector.hh"
#define _USE_MATH_DEFINES
#include <math.h>

class Generator : public G4VUserPrimaryGeneratorAction
{
public:
    Generator();
    ~Generator() override;
    void GeneratePrimaries(G4Event* anEvent) override;

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return particleGun; }
private:
    G4ParticleGun* particleGun;
};
#endif
