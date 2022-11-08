// declare class describing action initialization
#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "PGIGenerator.hh"
#include "PGIRunAction.hh"

class PGIAction : public G4VUserActionInitialization
{
public:
    // constructor
    PGIAction();
    // destructor
    ~PGIAction();

    // define virtual function Build()
    virtual void Build() const;
};

#endif