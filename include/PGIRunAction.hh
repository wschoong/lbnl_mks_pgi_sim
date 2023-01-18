#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>

class PGIRunAction : public G4UserRunAction
{
public:
    // constructor
    PGIRunAction();
    // destructor
    ~PGIRunAction();

    virtual void BeginofRunAction(const G4Run *);
    virtual void EndOfRunAction(const G4Run *);
};

#endif