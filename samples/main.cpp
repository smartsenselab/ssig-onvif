#include "ssigonvif/OnvifClientDevice.hpp"
#include "ssigonvif/OnvifClientPTZ.hpp"
#include "ssigonvif/OnvifClientMedia.hpp"
#include <ncurses.h>
#include <string>

int main(int argc, char** argv){
    
	OnvifClientPTZ *PTZ = new OnvifClientPTZ(argv[1], "root", "bbb_william", false);
	OnvifClientMedia *Media = new OnvifClientMedia(argv[1], "root", "bbb_william", false);
	Media->createProfile("PTZ", "PTZ");
	Media->getProfiles();
	std::cout << "Configurations:" << std::endl;
	//PTZ->getPTZConfigurations();
    //PTZ->getConfiguration("4");
	//Media->addPTZConfiguration("PTZ", "4");

	initscr();
	noecho();
	int c;
	printw("Use WASD to navigate\nI to zoom in\nO to zoom out\nP to continuous pan\nY to set home position\nH to go to home position\nESPACE to stop movement\nESC to quit");
	while((c=getch()) != 27){
		c = getch();
		if(c==87 || c==119){
			PTZ->tiltUp("PTZ", 5);
		}else if(c == 83 || c==115){
			PTZ->tiltDown("PTZ", 5);
		}else if(c == 65 || c==97){
			PTZ->panLeft("PTZ", 5);
		}else if(c == 68 || c==100){
			PTZ->panRight("PTZ", 5);
		}else if(c == 73 || c==105){
			PTZ->zoomIn("PTZ");
		}else if(c == 79 || c==111){
			PTZ->zoomOut("PTZ");
		}else if(c==80 || c==112 ){
			PTZ->continuousMove("PTZ", 0.2, 0.0, -0.1);
		}else if(c==89 || c==121 ){
			PTZ->setHomePosition("PTZ");
		}else if(c==72 || c==104 ){
			PTZ->goToHomePosition("PTZ");
		}else if(c==32){
			PTZ->stop("PTZ", 1, 1);
		}
	}
	endwin();
    
	return 0;
}