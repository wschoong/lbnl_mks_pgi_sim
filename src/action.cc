// src file describing action initialization (what to make the simulation do)

#include "action.hh"

// import construction, destruction
action::action()
{}
action::~action()
{}

//define particle generator build
void action::Build() const
{
    // generate particles
    generator *particleGenerator = new generator();
    SetUserAction(particleGenerator);
}
