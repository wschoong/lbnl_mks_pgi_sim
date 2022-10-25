// src file describing action initialization (what to make the simulation do)

#include "action.hh"

// import construction, destruction
MyActionInitialization::MyActionInitialization()
{}
MyActionInitialization::~MyActionInitialization()
{}

//define particle generator build
void MyActionInitialization::Build() const
{
    // generate particles
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
}
