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

// define detector construction class
class MyDetectorConstruction : public G4VUserDetectorConstruction 
{
public:
    // define constructor
    MyDetectorConstruction();
    // define destructor
    ~MyDetectorConstruction();

    // define function to create geometry
    //  virtual because defined in class

    virtual G4VPhysicalVolume *Construct();


};

#endif