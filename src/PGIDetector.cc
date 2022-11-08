#include "PGIDetector.hh"



G4double dataArray[8][100000]={0};
G4int I=0;

PGIDetector::PGIDetector(G4String name) : 
G4VSensitiveDetector(name)
{}

PGIDetector::~PGIDetector()
{}

G4bool PGIDetector::ProcessHits(G4Step *step, G4TouchableHistory *ROhist)
{
    G4StepPoint *preStepPoint = step->GetPreStepPoint();

    // get incident detector and pixel
    G4VPhysicalVolume *currentVolume = preStepPoint->GetPhysicalVolume();
    G4String currentVolName = currentVolume->GetName();
    G4int detCopyNumber = currentVolume->GetCopyNo();
    G4String detStr = currentVolName.erase(0,12);
    G4int detInt = stoi(detStr);

    // get particle name
    G4Track *pTrack = step->GetTrack();
    G4ParticleDefinition *particleDefinition = pTrack->GetDefinition();
    G4String particleName = particleDefinition->GetParticleName();

    G4double particleEnergy = preStepPoint->GetKineticEnergy();

    G4ThreeVector particlePosition = preStepPoint->GetPosition();
    G4double xPosition = particlePosition.x();
    G4double yPosition = particlePosition.y();
    G4double zPosition = particlePosition.z();

    G4int particleID=0;
    if (particleName == "gamma"){
        particleID=1;
    }

    G4cout << "Particle: " << particleName<<" "<< particleID << " Detector Number: " << detInt << " Pixel Number: " << detCopyNumber << G4endl;
    
    dataArray[0][I]=I;              // Event ID
    dataArray[1][I]=particleID;     // Incident Particle ID (1 if gamma, 0 otherwise)
    dataArray[2][I]=detInt;         // Incident Detector Number
    dataArray[3][I]=detCopyNumber;  // Incident Pixel Number
    dataArray[4][I]=particleEnergy; // Incident Particle Kinetic Energy
    dataArray[5][I]=xPosition;      // Incident Particle X Position
    dataArray[6][I]=yPosition;      // Incident Particle Y Position
    dataArray[7][I]=zPosition;      // Incident Particle Z Position

    I=I+1;


    return true;
}