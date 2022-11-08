#include "PGIPhysics.hh"

// define constructor
PGIPhysics::PGIPhysics()
{
    // define usable physics here
    // include only physics required, more physics implemented leads to longer simulation times
    RegisterPhysics (new G4EmStandardPhysics()); // E&M Interactions
    RegisterPhysics (new G4OpticalPhysics()); // Optical Interactions

}

PGIPhysics::~PGIPhysics()
{}