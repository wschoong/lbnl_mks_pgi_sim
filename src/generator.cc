#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    // set particles per event
    G4int num_particles=1;
    fParticleGun = new G4ParticleGun(num_particles);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

// create function to define particle properties
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // create table to define particle properties
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    // pull in particle data
    G4String particleName="gamma"; // captialized N (don't think it matters?)
    G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

    // define location of particle generation
    G4ThreeVector pos(0,0.,-1*m);
    //define direction of initial particle momentum
    G4ThreeVector mom(0.,0.,1.);

    //give particle gun these parameters
    fParticleGun->SetParticlePosition(pos); // set initial particle position
    fParticleGun->SetParticleMomentumDirection(mom); // set initial particle momentum
    fParticleGun->SetParticleMomentum(100*GeV); // set initial particle momentum magnitude (in units of energy)
    fParticleGun->SetParticleDefinition(particle); // set particle type

    // generate vertex of primary particle
    fParticleGun->GeneratePrimaryVertex(anEvent);

}