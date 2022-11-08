// src file describing action initialization (what to make the simulation do)

#include "PGIRunAction.hh"

ofstream dataOutFile;

extern G4double dataArray[8][100000];
extern G4int I;
G4int width=20;

// import construction, destruction
PGIRunAction::PGIRunAction()
{}
PGIRunAction::~PGIRunAction()
{}

//define particle generator build
void PGIARunction::BeginofRunAction(const G4Run *)
{

}

void PGIRunAction::EndOfRunAction(const G4Run *);
{
    dataOutFile.open("test.txt")
    
    for (int i=0; i<I;i++){
        dataOutFile << left << setw(width) <<dataArray[0][i];
        dataOutFile << left << setw(width) <<dataArray[1][i];
        dataOutFile << left << setw(width) <<dataArray[2][i];
        dataOutFile << left << setw(width) <<dataArray[3][i];
        dataOutFile << left << setw(width) <<dataArray[4][i];
        dataOutFile << left << setw(width) <<dataArray[5][i];
        dataOutFile << left << setw(width) <<dataArray[6][i];
        dataOutFile << left << setw(width) <<dataArray[7][i];
        dataOutFile << endl;
    }
    dataOutFile.close();

}
