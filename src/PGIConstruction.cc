#include "PGIConstruction.hh"
#include "rotation.hh"

PGIConstruction::PGIConstruction()
{}
PGIConstruction::~PGIConstruction()
{}

G4VPhysicalVolume *PGIConstruction::Construct() 
{

    G4double det_halfwidth=4.855/2*cm;
    G4double spacing_halfwidth=0.2*cm;
    G4double total_halfwidth=det_halfwidth+spacing_halfwidth;
    G4double pixel_halfwidth=det_halfwidth/12;

    // import materials manager
    G4NistManager *nist = G4NistManager::Instance();

    //create materials new material
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *SiO2 = new G4Material("SiO2",2.65*g/cm3,2);
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

    G4double rindexAerogel[2] = {1.1,1.1};

    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX",energy,rindexAerogel,2);
    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld ->AddProperty("RINDEX",energy,rindexWorld,2);
    worldMat->SetMaterialPropertiesTable(mptWorld);


    // world volume
    G4Box *solidWorld = new G4Box("solidWorld",0.5*m,0.5*m,1.25*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld",0,false,0,true);

    // detector volumes
    // labeled as:
    // [3]  [2]  [1]  [0]
    // [7]  [6]  [5]  [4]
    // [11] [10] [9]  [8]
    // [15] [14] [13] [12]
    //
    // when looking in negative z-direction (from back of detector)

    // pixels ordering goes left-to-right, top-to-bottom (as if you were reading in English) when viewed from the back fo the detector
    
    //all measurements in mm
    //3d vector of corners going from 0-15
    std::vector<std::vector<std::vector<float>>> corners = {{{-90.059,277.138,-78.269},{-99.028,278.919,-30.588},{-99.627,229.54,-78.29}},{{-99.673,279.047,-25.738},{-102.674,279.628,22.715},{-109.241,231.449,-25.76}},{{-102.714,279.634,27.609},{-99.70,279.006,76.061},{-112.282,232.036,27.587}},{{-99.134,278.89,80.921},{-90.152,277.062,128.598},{-108.702,231.292,80.899}},{{-100.242,224.634,-78.293},{-109.37,225.233,-30.612},{-103.542,176.196,-78.316}},{{-110.025,225.275,-25.763},{-113.08,225.46,22.691},{-113.325,176.837,-25.786}},{{-113.121,225.461,27.584},{-110.053,225.229,76.037},{-116.42,177.023,27.561}},{{-109.478,225.187,80.896},{-100.337,224.542,128.574},{-112.777,176.749,80.873}},{{-103.513,171.251,-78.318},{-112.645,170.657,-30.638},{-100.489,122.795,-78.342}},{{-113.301,170.614,-25.789},{-116.357,170.399,22.664},{-110.276,122.158,-25.813}},{{-116.397,170.394,27.558},{-113.329,170.562,76.01},{-113.373,121.939,27.534}},{{-112.753,170.596,80.87},{-103.609,171.143,128.548},{-109.728,122.14,80.846}},{{-99.818,117.895,-78.344},{-108.798,116.119,-30.665},{-90.521,70.244,-78.369}},{{-109.443,115.991,-25.816},{-112.448,115.38,22.637},{-100.146,68.339,-25.84}},{{-112.488,115.369,27.531},{-109.47,115.934,75.984},{-103.19,67.718,27.506}},{{-108.904,116.042,80.843},{-99.912,117.772,128.522},{-99.606,68.39,80.819}}};
    
    G4int detCopyNumber=0;
    for (std::vector<std::vector<float>> x : corners){
        float theta = -xzrot(x);
        float phi = -xyrot(x);
        G4RotationMatrix* rotation=new G4RotationMatrix;
        rotation->rotateY(theta*rad);
        rotation->rotateZ(phi*rad);
        std::vector<float> center = findcenter(x);
        
        G4Box *solidDetectorMother1 = new G4Box("solidDetectorMother1",det_halfwidth,0.25*cm,det_halfwidth);
        G4LogicalVolume *logicDetectorMother1 = new G4LogicalVolume(solidDetectorMother1,worldMat,"logicDetectorMother1");
        G4VPhysicalVolume *physDetectorMother1 = new G4PVPlacement(rotation, G4ThreeVector(center[0]*mm, center[1]*mm, center[2]*mm),
        logicDetectorMother1, "physDetectorMother1",logicWorld ,false,detCopyNumber,true);

        detCopyNumber++;

        G4Box *solidDetector1 = new G4Box("solidDetector1",det_halfwidth/12,0.25*cm,det_halfwidth/12);
        logicDetector1 = new G4LogicalVolume(solidDetector1,worldMat,"logicDetector1");


        // separation between pixels is 0.05 mm total width
        for (G4int i=0;i<12;i++){
            for (G4int j=0;j<12;j++){
                G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0,
                G4ThreeVector((11-2*i)*pixel_halfwidth,0.*m,(11-2*j)*pixel_halfwidth),
                logicDetector1,"physDetector1",logicDetectorMother1,false,j+i*12,true);
            }
        }
        //CALL GSROTM(1,180.,0.,90.,90.,0.);
    }

//    // Detector 0
//
//    G4Box *solidDetectorMother0 = new G4Box("solidDetectorMother0",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother0 = new G4LogicalVolume(solidDetectorMother0,worldMat,"logicDetectorMother0");
//    G4VPhysicalVolume *physDetectorMother0 = new G4PVPlacement(0, G4ThreeVector(-3*total_halfwidth, 3*total_halfwidth, 1.*m),
//    logicDetectorMother0, "physDetectorMother0",logicWorld ,false,0,true);
//
//    G4Box *solidDetector0 = new G4Box("solidDetector0",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector0 = new G4LogicalVolume(solidDetector0,worldMat,"logicDetector0");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector0 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector0,"physDetector0",logicDetectorMother0,false,j+i*12,true);
//        }
//    }
//
//    // Detector 1
//
//    G4Box *solidDetectorMother1 = new G4Box("solidDetectorMother1",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother1 = new G4LogicalVolume(solidDetectorMother1,worldMat,"logicDetectorMother1");
//    G4VPhysicalVolume *physDetectorMother1 = new G4PVPlacement(0, G4ThreeVector(-1*total_halfwidth, 3*total_halfwidth, 1.*m),
//    logicDetectorMother1, "physDetectorMother1",logicWorld ,false,0,true);
//
//    G4Box *solidDetector1 = new G4Box("solidDetector1",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector1 = new G4LogicalVolume(solidDetector1,worldMat,"logicDetector1");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector1,"physDetector1",logicDetectorMother1,false,j+i*12,true);
//        }
//    }
//
//    // Detector 2
//
//    G4Box *solidDetectorMother2 = new G4Box("solidDetectorMother2",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother2 = new G4LogicalVolume(solidDetectorMother2,worldMat,"logicDetectorMother2");
//    G4VPhysicalVolume *physDetectorMother2 = new G4PVPlacement(0, G4ThreeVector(1*total_halfwidth, 3*total_halfwidth, 1.*m),
//    logicDetectorMother2, "physDetectorMother2",logicWorld ,false,0,true);
//
//    G4Box *solidDetector2 = new G4Box("solidDetector2",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector2 = new G4LogicalVolume(solidDetector2,worldMat,"logicDetector2");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector2 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector2,"physDetector2",logicDetectorMother2,false,j+i*12,true);
//        }
//    }
//
//    // Detector 3
//
//    G4Box *solidDetectorMother3 = new G4Box("solidDetectorMother3",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother3 = new G4LogicalVolume(solidDetectorMother3,worldMat,"logicDetectorMother3");
//    G4VPhysicalVolume *physDetectorMother3 = new G4PVPlacement(0, G4ThreeVector(3*total_halfwidth, 3*total_halfwidth, 1.*m),
//    logicDetectorMother3, "physDetectorMother3",logicWorld ,false,0,true);
//
//    G4Box *solidDetector3 = new G4Box("solidDetector3",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector3 = new G4LogicalVolume(solidDetector3,worldMat,"logicDetector3");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector3 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector3,"physDetector3",logicDetectorMother3,false,j+i*12,true);
//        }
//    }
//
//    // Detector 4
//
//    G4Box *solidDetectorMother4 = new G4Box("solidDetectorMother4",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother4 = new G4LogicalVolume(solidDetectorMother4,worldMat,"logicDetectorMother4");
//    G4VPhysicalVolume *physDetectorMother4 = new G4PVPlacement(0, G4ThreeVector(-3*total_halfwidth, 1*total_halfwidth, 1.*m),
//    logicDetectorMother4, "physDetectorMother4",logicWorld ,false,0,true);
//
//    G4Box *solidDetector4 = new G4Box("solidDetector4",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector4 = new G4LogicalVolume(solidDetector4,worldMat,"logicDetector0");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector4 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector4,"physDetector4",logicDetectorMother4,false,j+i*12,true);
//        }
//    }
//
//    // Detector 5
//
//    G4Box *solidDetectorMother5 = new G4Box("solidDetectorMother5",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother5 = new G4LogicalVolume(solidDetectorMother5,worldMat,"logicDetectorMother5");
//    G4VPhysicalVolume *physDetectorMother5 = new G4PVPlacement(0, G4ThreeVector(-1*total_halfwidth, 1*total_halfwidth, 1.*m),
//    logicDetectorMother5, "physDetectorMother5",logicWorld ,false,0,true);
//
//    G4Box *solidDetector5 = new G4Box("solidDetector5",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector5 = new G4LogicalVolume(solidDetector5,worldMat,"logicDetector5");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector5 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector5,"physDetector5",logicDetectorMother5,false,j+i*12,true);
//        }
//    }
//
//    // Detector 6
//
//    G4Box *solidDetectorMother6 = new G4Box("solidDetectorMother6",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother6 = new G4LogicalVolume(solidDetectorMother6,worldMat,"logicDetectorMother6");
//    G4VPhysicalVolume *physDetectorMother6 = new G4PVPlacement(0, G4ThreeVector(1*total_halfwidth, 1*total_halfwidth, 1.*m),
//    logicDetectorMother6, "physDetectorMother6",logicWorld ,false,0,true);
//
//    G4Box *solidDetector6 = new G4Box("solidDetector6",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector6 = new G4LogicalVolume(solidDetector6,worldMat,"logicDetector6");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector6 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector6,"physDetector6",logicDetectorMother6,false,j+i*12,true);
//        }
//    }
//
//    // Detector 7
//
//    G4Box *solidDetectorMother7 = new G4Box("solidDetectorMother7",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother7 = new G4LogicalVolume(solidDetectorMother7,worldMat,"logicDetectorMother7");
//    G4VPhysicalVolume *physDetectorMother7 = new G4PVPlacement(0, G4ThreeVector(3*total_halfwidth, 1*total_halfwidth, 1.*m),
//    logicDetectorMother7, "physDetectorMother7",logicWorld ,false,0,true);
//
//    G4Box *solidDetector7 = new G4Box("solidDetector7",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector7 = new G4LogicalVolume(solidDetector7,worldMat,"logicDetector7");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector7 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector7,"physDetector7",logicDetectorMother7,false,j+i*12,true);
//        }
//    }
//
//    // Detector 8
//
//    G4Box *solidDetectorMother8 = new G4Box("solidDetectorMother8",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother8 = new G4LogicalVolume(solidDetectorMother8,worldMat,"logicDetectorMother8");
//    G4VPhysicalVolume *physDetectorMother8 = new G4PVPlacement(0, G4ThreeVector(-3*total_halfwidth, -1*total_halfwidth, 1.*m),
//    logicDetectorMother8, "physDetectorMother8",logicWorld ,false,0,true);
//
//    G4Box *solidDetector8 = new G4Box("solidDetector8",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector8 = new G4LogicalVolume(solidDetector8,worldMat,"logicDetector8");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector8 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector8,"physDetector8",logicDetectorMother8,false,j+i*12,true);
//        }
//    }
//
//    // Detector 9
//
//    G4Box *solidDetectorMother9 = new G4Box("solidDetectorMother9",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother9 = new G4LogicalVolume(solidDetectorMother9,worldMat,"logicDetectorMother9");
//    G4VPhysicalVolume *physDetectorMother9 = new G4PVPlacement(0, G4ThreeVector(-1*total_halfwidth, -1*total_halfwidth, 1.*m),
//    logicDetectorMother9, "physDetectorMother9",logicWorld ,false,0,true);
//
//    G4Box *solidDetector9 = new G4Box("solidDetector9",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector9 = new G4LogicalVolume(solidDetector9,worldMat,"logicDetector9");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector9 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector9,"physDetector9",logicDetectorMother9,false,j+i*12,true);
//        }
//    }
//
//    // Detector 10
//
//    G4Box *solidDetectorMother10 = new G4Box("solidDetectorMother10",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother10 = new G4LogicalVolume(solidDetectorMother10,worldMat,"logicDetectorMother10");
//    G4VPhysicalVolume *physDetectorMother10 = new G4PVPlacement(0, G4ThreeVector(1*total_halfwidth, -1*total_halfwidth, 1.*m),
//    logicDetectorMother10, "physDetectorMother10",logicWorld ,false,0,true);
//
//    G4Box *solidDetector10 = new G4Box("solidDetector10",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector10 = new G4LogicalVolume(solidDetector10,worldMat,"logicDetector10");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector10 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector10,"physDetector10",logicDetectorMother10,false,j+i*12,true);
//        }
//    }
//
//    // Detector 11
//
//    G4Box *solidDetectorMother11 = new G4Box("solidDetectorMother11",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother11 = new G4LogicalVolume(solidDetectorMother11,worldMat,"logicDetectorMother11");
//    G4VPhysicalVolume *physDetectorMother11 = new G4PVPlacement(0, G4ThreeVector(3*total_halfwidth, -1*total_halfwidth, 1.*m),
//    logicDetectorMother11, "physDetectorMother11",logicWorld ,false,0,true);
//
//    G4Box *solidDetector11 = new G4Box("solidDetector11",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector11 = new G4LogicalVolume(solidDetector11,worldMat,"logicDetector11");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector11 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector11,"physDetector11",logicDetectorMother11,false,j+i*12,true);
//        }
//    }
//
//    // Detector 12
//
//    G4Box *solidDetectorMother12 = new G4Box("solidDetectorMother12",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother12 = new G4LogicalVolume(solidDetectorMother12,worldMat,"logicDetectorMother12");
//    G4VPhysicalVolume *physDetectorMother12 = new G4PVPlacement(0, G4ThreeVector(-3*total_halfwidth, -3*total_halfwidth, 1.*m),
//    logicDetectorMother12, "physDetectorMother12",logicWorld ,false,0,true);
//
//    G4Box *solidDetector12 = new G4Box("solidDetector12",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector12 = new G4LogicalVolume(solidDetector12,worldMat,"logicDetector12");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector12 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector12,"physDetector12",logicDetectorMother12,false,j+i*12,true);
//        }
//    }
//
//    // Detector 13
//
//    G4Box *solidDetectorMother13 = new G4Box("solidDetectorMother13",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother13 = new G4LogicalVolume(solidDetectorMother13,worldMat,"logicDetectorMother13");
//    G4VPhysicalVolume *physDetectorMother13 = new G4PVPlacement(0, G4ThreeVector(-1*total_halfwidth, -3*total_halfwidth, 1.*m),
//    logicDetectorMother13, "physDetectorMother13",logicWorld ,false,0,true);
//
//    G4Box *solidDetector13 = new G4Box("solidDetector13",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector13 = new G4LogicalVolume(solidDetector13,worldMat,"logicDetector13");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector13 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector13,"physDetector13",logicDetectorMother13,false,j+i*12,true);
//        }
//    }
//
//    // Detector 14
//
//    G4Box *solidDetectorMother14 = new G4Box("solidDetectorMother14",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother14 = new G4LogicalVolume(solidDetectorMother14,worldMat,"logicDetectorMother14");
//    G4VPhysicalVolume *physDetectorMother14 = new G4PVPlacement(0, G4ThreeVector(1*total_halfwidth, -3*total_halfwidth, 1.*m),
//    logicDetectorMother14, "physDetectorMother14",logicWorld ,false,0,true);
//
//    G4Box *solidDetector14 = new G4Box("solidDetector14",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector14 = new G4LogicalVolume(solidDetector14,worldMat,"logicDetector14");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector14 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector14,"physDetector14",logicDetectorMother14,false,j+i*12,true);
//        }
//    }
//
//    // Detector 15
//
//    G4Box *solidDetectorMother15 = new G4Box("solidDetectorMother15",det_halfwidth,det_halfwidth,0.25*cm);
//    G4LogicalVolume *logicDetectorMother15 = new G4LogicalVolume(solidDetectorMother15,worldMat,"logicDetectorMother15");
//    G4VPhysicalVolume *physDetectorMother15 = new G4PVPlacement(0, G4ThreeVector(3*total_halfwidth, -3*total_halfwidth, 1.*m),
//    logicDetectorMother15, "physDetectorMother15",logicWorld ,false,0,true);
//
//    G4Box *solidDetector15 = new G4Box("solidDetector15",det_halfwidth/12,det_halfwidth/12,0.25*cm);
//    logicDetector15 = new G4LogicalVolume(solidDetector15,worldMat,"logicDetector15");
//
//    for (G4int i=0;i<12;i++){
//        for (G4int j=0;j<12;j++){
//            G4VPhysicalVolume *physDetector15 = new G4PVPlacement(0,
//            G4ThreeVector((11-2*i)*pixel_halfwidth,(11-2*j)*pixel_halfwidth,0.*m),
//            logicDetector15,"physDetector15",logicDetectorMother15,false,j+i*12,true);
//        }
//    }

    return physWorld;
}

void PGIConstruction::ConstructSDandField()
{
    PGIDetector *sensDet = new PGIDetector("SensitiveDetector");

    // logicDetector0->SetSensitiveDetector(sensDet);
    logicDetector1->SetSensitiveDetector(sensDet);
    // logicDetector2->SetSensitiveDetector(sensDet);
    // logicDetector3->SetSensitiveDetector(sensDet);
    // logicDetector4->SetSensitiveDetector(sensDet);
    // logicDetector5->SetSensitiveDetector(sensDet);
    // logicDetector6->SetSensitiveDetector(sensDet);
    // logicDetector7->SetSensitiveDetector(sensDet);
    // logicDetector8->SetSensitiveDetector(sensDet);
    // logicDetector9->SetSensitiveDetector(sensDet);
    // logicDetector10->SetSensitiveDetector(sensDet);
    // logicDetector11->SetSensitiveDetector(sensDet);
    // logicDetector12->SetSensitiveDetector(sensDet);
    // logicDetector13->SetSensitiveDetector(sensDet);
    // logicDetector14->SetSensitiveDetector(sensDet);
    // logicDetector15->SetSensitiveDetector(sensDet);

}
