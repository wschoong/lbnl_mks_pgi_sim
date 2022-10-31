// declare class describing action initialization
#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"

class action : public G4VUserActionInitialization
{
public:
    // constructor
    action();
    // destructor
    ~action();

    // define virtual function Build()
    virtual void Build() const;
};

#endif