// declare class describing action initialization
#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
    // constructor
    MyActionInitialization();
    // destructor
    ~MyActionInitialization();

    // define virtual function Build()
    virtual void Build() const;
};

#endif