#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "PGIConstruction.hh"
#include "PGIPhysics.hh"
#include "PGIAction.hh"

int main(int argc, char** argv) {

	//// TEMPLATE FOR STARTING GEANT4 PROGRAMS
	
	// always needed, "heart" of Geant4 programs
	// takes care of run actions, event actions, stepping, etc.
	G4RunManager *runManager = new G4RunManager();

	// call user-created geometry
	runManager->SetUserInitialization(new PGIConstruction());
	// call physics list
	runManager->SetUserInitialization(new PGIPhysics());
	// call action initialization
	runManager->SetUserInitialization(new PGIAction());

	//initialize run manager
	runManager->Initialize();

	// user interface
	G4UIExecutive *ui = new G4UIExecutive(argc,argv);

	// visualization manager
	G4VisManager *visManager = new G4VisExecutive();
	// initialize visualization manager
	visManager -> Initialize();
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	////

    // give commands to the UI
	UImanager->ApplyCommand("/vis/open HepRepFile");
	
	UImanager->ApplyCommand("/vis/drawVolume");	
	UImanager->ApplyCommand("/vis/scene/add/trajectories");
	UImanager->ApplyCommand("/vis/scene/endofEventAction accumulate -1");
	UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");

	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set gamma yellow");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set opticalphoton cyan");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e- blue");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set e+ purple");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set GenericIon magenta");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set neutron green");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set proton red");

	UImanager->ApplyCommand("/run/beamOn");

	ui -> SessionStart();


	return 0;

}