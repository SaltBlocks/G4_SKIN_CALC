#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "SensitiveDetector.hh"
#define _USE_MATH_DEFINES
#include <math.h>

const G4double fluidCylinderRadius = 1.5 * cm;
const G4double fluidCylinderHeight = 6 / pow(fluidCylinderRadius / cm, 2) / M_PI * cm;

class Detector : public G4VUserDetectorConstruction
{
public:
	Detector() = default;
	~Detector() override = default;
	G4VPhysicalVolume* Construct() override;
	SensitiveDetector* GetSensitiveDetector() const { return sensitiveDetector; }
	G4LogicalVolume* GetScoringVolume() const { return scoringVolume; }

protected:
	SensitiveDetector* sensitiveDetector = nullptr;
	G4LogicalVolume* scoringVolume = nullptr;
};
#endif
