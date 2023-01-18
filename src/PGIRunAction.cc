// src file describing action initialization (what to make the simulation do)

#include "PGIRunAction.hh"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

// std::ofstream dataOutFile;

extern double dataArray[100000][8];
extern G4int I;
G4int width=20;

// import construction, destruction
PGIRunAction::PGIRunAction()
{}
PGIRunAction::~PGIRunAction()
{}

//define particle generator build
void PGIRunAction::BeginofRunAction(const G4Run *)
{

}

void PGIRunAction::EndOfRunAction(const G4Run*)
{
    // dataOutFile.open("test.txt");
    
    // for (int i=0; i<I;i++){
    //     dataOutFile << std::left << std::setw(width) <<dataArray[0][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[1][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[2][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[3][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[4][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[5][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[6][i];
    //     dataOutFile << std::left << std::setw(width) <<dataArray[7][i];
    //     dataOutFile << std::endl;
    // }
    // dataOutFile.close();

    FILE *dataOutFile;
    dataOutFile = fopen("data.bin","wb");
    for (int i=0; i<I;i++){

        fwrite(dataArray[i],sizeof(G4double),sizeof(dataArray[i])/sizeof(G4double),dataOutFile);
        // G4cout << sizeof(dataArray[i]) << G4endl;
        // G4cout << dataArray[i][0] << " " << dataArray[i][1] << " " << dataArray[i][2] << " " << dataArray[i][3] << " " << dataArray[i][4] << " " << dataArray[i][5] << G4endl;
    }

    fclose(dataOutFile);
    G4cout << "Number of Events: " << I << G4endl;


}
