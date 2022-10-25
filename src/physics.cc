#include "physics.hh"

// define constructor
MyPhysicsList::MyPhysicsList()
{
    // define usable physics here
    // include only physics required, more physics implemented leads to longer simulation times
    RegisterPhysics (new G4EmStandardPhysics()); // E&M Interactions
    RegisterPhysics (new G4OpticalPhysics()); // Optical Interactions

}

MyPhysicsList::~MyPhysicsList()
{}