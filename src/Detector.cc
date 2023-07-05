#include "Detector.hh"

/**
* Create a Detector consisting of two stacked cylinders.
* The volume of the bottom cylinder equals 6 cm^3 with a radius of 1.5cm, the material used is water.
* The Top cylinder has a width of 1mm and uses the composition of skin as defined by the ICRP. 
 */
G4VPhysicalVolume* Detector::Construct()
{
	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* MAT_WATER = nist->FindOrBuildMaterial("G4_WATER");
	G4Material* MAT_SKIN = nist->FindOrBuildMaterial("G4_SKIN_ICRP");
	G4Material* MAT_VACUUM = nist->FindOrBuildMaterial("G4_Galactic");

	G4double world_hx = 5 * cm;
	G4double world_hy = 5 * cm;
	G4double world_hz = 5 * cm;
	G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);

	G4Tubs* skinCylinder = new G4Tubs("SkinCylinder", 0, fluidCylinderRadius, 0.5 * mm, 0.0, 2.0 * M_PI);
	G4Tubs* waterCylinder = new G4Tubs("WaterCylinder", 0, fluidCylinderRadius, fluidCylinderHeight / 2.0, 0.0, 2.0 * M_PI);



	G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, MAT_VACUUM, "World");
	G4LogicalVolume* sourceLog = new G4LogicalVolume(waterCylinder, MAT_WATER, "Fluid_Cylinder");
	G4LogicalVolume* trackerLog = new G4LogicalVolume(skinCylinder, MAT_SKIN, "Skin_Cylinder");

	G4Colour blue(0.0, 0.0, 1.0);
	sourceLog->SetVisAttributes(G4VisAttributes(blue));

	G4Colour red(1.0, 0.0, 0.0);
	trackerLog->SetVisAttributes(G4VisAttributes(red));

	G4double pos_x = 0.0 * meter;
	G4double pos_y = 0.0 * meter;
	G4double pos_z = 0.0 * meter;

	G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr,  // no rotation
		G4ThreeVector(),                           // at (0,0,0)
		worldLog,                                // its logical volume
		"World",                                   // its name
		NULL,                                   // its mother  volume
		false,                                     // no boolean operation
		0,                                         // copy number
		true);                            // overlaps checking

	G4VPhysicalVolume* sourcePhys = new G4PVPlacement(nullptr,
		G4ThreeVector(pos_x, pos_y, pos_z),
		sourceLog,
		"Fluid_Cylinder",
		worldLog,
		false,
		0,
		true);

	G4VPhysicalVolume* trackerPhys = new G4PVPlacement(nullptr,
		G4ThreeVector(pos_x, pos_y, pos_z + fluidCylinderHeight / 2 + 0.5 * mm),
		trackerLog,
		"Skin_Detector",
		worldLog,
		false,
		0,
		true);
	scoringVolume = trackerLog;
	sensitiveDetector = new SensitiveDetector("TrackerSensitiveDetector");
	trackerLog->SetSensitiveDetector(sensitiveDetector);
	return physWorld;
}