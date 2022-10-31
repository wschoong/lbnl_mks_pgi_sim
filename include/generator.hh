// class describing particle generation

#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class generator : public G4VUserPrimaryGeneratorAction
{
public:
    // constructor
    generator();
    // destructor
    ~generator();

    // virtual function to generate primary particles
    virtual void GeneratePrimaries(G4Event*);
    // Particle Gun to shoot out particles, fParticleGun is User-given name
private:
    G4ParticleGun *fParticleGun;


};
#endif