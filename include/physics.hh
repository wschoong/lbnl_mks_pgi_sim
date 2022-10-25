// physics list header file

#ifndef PHYSICS_HH
#define PHYSICS_HH

// include all of the physics you will be using
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

// define physics list class
class MyPhysicsList : public G4VModularPhysicsList
{
public:
    // define constructor
    MyPhysicsList();
    // define destructor
    ~MyPhysicsList();
};

#endif