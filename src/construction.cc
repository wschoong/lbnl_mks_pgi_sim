#include "construction.hh"

// import constructor, destructor 
MyDetectorConstruction::MyDetectorConstruction()
{}
MyDetectorConstruction::~MyDetectorConstruction()
{}

// call constrution function
G4VPhysicalVolume *MyDetectorConstruction::Construct() 
{
    // import materials manager
    G4NistManager *nist = G4NistManager::Instance();

    //define new material
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    //define Cherenkov radiator material
    // G4Material *S[material name] = new G4Material("[material name",[density],[number of elements in chemical compound]);
    G4Material *SiO2 = new G4Material("SiO2",2.65*g/cm3,2);
    // [Material Name]->AddElement(nist->FindOrBuildElement("[Geant4 Element Identifier]"),[Amount of element in chemical compound]);
    SiO2->AddElement(nist->FindOrBuildElement("Si"),1);
    SiO2->AddElement(nist->FindOrBuildElement("O"),2);

    G4Material *H2O = new G4Material("H2O",1.00*g/cm3,2);
    H2O->AddElement(nist->FindOrBuildElement("H"),2);
    H2O->AddElement(nist->FindOrBuildElement("O"),1);

    G4Element *C = nist->FindOrBuildElement("C");

    G4Material *Aerogel = new G4Material("Aerogel",0.2*g/cm3,3);
    Aerogel->AddMaterial(SiO2,62.5*perCent);
    Aerogel->AddMaterial(H2O,37.4*perCent);
    Aerogel->AddElement(C,0.1*perCent);

    // add refractive index for air in surrounding environment
    G4double energy[2] ={1.239841939*eV/0.2, 1.239841939*eV/0.9};
    G4double rindexWorld[2] = {1,1};

    //// Tutorial Refractive Index
    G4double rindexAerogel[2] = {1.1,1.1};
    ////

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX",energy,rindexAerogel,2);
    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld ->AddProperty("RINDEX",energy,rindexWorld,2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    // each Geant4 volume needs 3 parts: solid defining volume size;
    // logical volume defining material; physical volume placing the
    // volume in the simulation

    // create solid volume
    // G4Box *[voume name] = new G4Box("[volume name]",[x half-size],[y half-size],[z half-size])
    // m defines units (in this case meters)
    G4Box *solidWorld = new G4Box("solidWorld",1*m,1*m,2.5*m);

    // create logical volume
    // G4LogicalVolume *[logical volume name] = new G4LogicalVolume([solid colume name],[material name],"[logical volume name]");
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"logicWorld");

    // create physical volume
    // G4PhysicalVolume *physWorld = new G4PVPlacement([rotation], G4ThreeVector([volume center x-position],[volume center y-position],[volume center z-position]),[logic volume name],"[physical volume name]",[0 if mother volume, 1 if daughter],[Boolean Operations?],[copy number],[check for overlaps? always set to true]);
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld",0,false,0,true);


    G4double det_halfwidth=2.5*cm;
    G4double pixel_halfwidth=det_halfwidth/12;

    G4Box *solidDetectorMother = new G4Box("solidDetectorMother",det_halfwidth,det_halfwidth,1*cm);
    G4LogicalVolume *logicDetectorMother = new G4LogicalVolume(solidDetectorMother,worldMat,"logicDetectorMother");
    G4VPhysicalVolume *physDetectorMother = new G4PVPlacement(0, G4ThreeVector(0*m, 0., -1.*m), logicDetectorMother, "physDetectorMother",logicWorld ,false,0,true);

    G4Box *solidDetector = new G4Box("solidDetector",det_halfwidth/12,det_halfwidth/12,1*cm);
    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector,worldMat,"logicDetector");



    for (G4int i=0;i<12;i++){
        for (G4int j=0;j<12;j++){
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0,
            G4ThreeVector((2*i-11)*pixel_halfwidth,(2*j-11)*pixel_halfwidth,0.*m),
            logicDetector,"physDetector",logicDetectorMother,false,j+i*12,true);
        }
    }

    return physWorld;

}
