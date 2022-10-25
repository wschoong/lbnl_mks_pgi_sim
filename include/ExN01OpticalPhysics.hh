//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: ExN01OpticalPhysics.hh,v 1.2 2006/06/29 17:44:43 gunter Exp $
// --------------------------------------------------------------
//
// 09-Oct-2003 Chhange gamma, electron, positorn process T. Koi


#ifndef ExN01OpticalPhysics_h
#define ExN01OpticalPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"

#include "G4Cerenkov.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Scintillation.hh"

class G4Cerenkov;
class G4OpAbsorption;
class G4Scintillation;
class G4OpRayleigh;
class G4OpBoundaryProcess;
class G4OpMieHG;

class ExN01OpticalPhysics : public G4VPhysicsConstructor
{
  public:
    ExN01OpticalPhysics(const G4String& name ="Optical");
    virtual ~ExN01OpticalPhysics();

  public:
    // This method will be invoked in the Construct() method.
    // each particle type will be instantiated
    virtual void ConstructParticle();
	void AddStepMax();

    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type
    virtual void ConstructProcess();
	
	private:
	G4Cerenkov*          theCerenkovProcess;
	G4OpAbsorption*      theAbsorptionProcess;
	G4Scintillation*     theScintillationProcess;
	G4OpRayleigh*        theRayleighScatteringProcess;
	G4OpBoundaryProcess* theBoundaryProcess;
	G4OpMieHG*           theMieHGScatteringProcess;

  protected:

};


#endif
