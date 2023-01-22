#include "PGIGenerator.hh"

// set number of particles to generate
G4int num_particles=1;

PGIGenerator::PGIGenerator()
{
    // set particles per event
    G4int num=1;
    fParticleGun = new G4ParticleGun(num);
}

PGIGenerator::~PGIGenerator()
{
    delete fParticleGun;
}

// create function to define particle properties
void PGIGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // create table to define particle properties
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    // pull in particle data
    G4String particleName="gamma"; 
    G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

    // define location of particle generation
    G4ThreeVector pos(0,0.,0.75*m);
    //define direction of initial particle momentum
    for (G4int i=0;i<num_particles;i++)
    {
        // random isotropic sampling (only in positive z direction)
        G4double xdir=-1;
        G4double ydir=0;
        G4double zdir=0;
        G4ThreeVector mom(xdir,ydir,zdir);

        //give particle parameters
        fParticleGun->SetParticlePosition(pos); 
        fParticleGun->SetParticleMomentumDirection(mom); 
        fParticleGun->SetParticleMomentum(100*GeV); 
        fParticleGun->SetParticleDefinition(particle); 

        // generate vertex of primary particle
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

    

}