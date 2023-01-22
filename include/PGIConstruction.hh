// header file

#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

// include Geant4 Unit packages
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "PGIDetector.hh"

// define detector construction class
class PGIConstruction : public G4VUserDetectorConstruction 
{
public:
    // define constructor
    PGIConstruction();
    // define destructor
    ~PGIConstruction();

    // define function to create geometry

    virtual G4VPhysicalVolume *Construct();
private:
    G4LogicalVolume *logicDetector0;
    G4LogicalVolume *logicDetector1;
    G4LogicalVolume *logicDetector2;
    G4LogicalVolume *logicDetector3;
    G4LogicalVolume *logicDetector4;
    G4LogicalVolume *logicDetector5;
    G4LogicalVolume *logicDetector6;
    G4LogicalVolume *logicDetector7;
    G4LogicalVolume *logicDetector8;
    G4LogicalVolume *logicDetector9;
    G4LogicalVolume *logicDetector10;
    G4LogicalVolume *logicDetector11;
    G4LogicalVolume *logicDetector12;
    G4LogicalVolume *logicDetector13;
    G4LogicalVolume *logicDetector14;
    G4LogicalVolume *logicDetector15;
    virtual void ConstructSDandField();


};

#endif
