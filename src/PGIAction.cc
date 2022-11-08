// src file describing action initialization (what to make the simulation do)

#include "PGIAction.hh"

// import construction, destruction
PGIAction::PGIAction()
{}
PGIAction::~PGIAction()
{}

//define particle generator build
void PGIAction::Build() const
{
    // generate particles
    PGIGenerator *particleGenerator = new PGIGenerator();
    SetUserAction(particleGenerator);

    PGIRunAction *runAction = new PGIRunAction();
    SetUserAction(runAction);
}
