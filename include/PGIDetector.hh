#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include <string>
#include <map>

class PGIDetector : public G4VSensitiveDetector
{
// define constructor, destructor
public:
    PGIDetector(G4String);
    ~PGIDetector();
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif