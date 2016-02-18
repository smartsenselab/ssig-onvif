#include "ssigonvif/OnvifClientDevice.hpp"
#include "ssigonvif/OnvifClientPTZ.hpp"
#include "ssigonvif/OnvifClientMedia.hpp"
#include <string>
#include <stdexcept>
#include "onvif/soapRemoteDiscoveryBindingProxy.h"
#include "wsaapi.h"
#include "wsddapi.h"
#include "wsdd.nsmap"

void PTZTest(std::string url){
    /*
    OnvifClientPTZ *PTZ = new OnvifClientPTZ(url, "root", "bbb_william", false);
    OnvifClientMedia *Media = new OnvifClientMedia(url, "root", "bbb_william", false);
    //Media->createProfile("PTZ", "PTZ");
    //Media->getProfiles();
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
    */
}

int main(int argc, char** argv){
    /*    try{
        OnvifClientMedia *fish1Media = new OnvifClientMedia("172.22.22.220", "root", "bbb_william");
        fish1Media->getProfiles();
    }catch(const std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
     */

/*
    OnvifClientPTZ *fish1PTZ = new OnvifClientPTZ("172.22.22.220", "root", "bbb_william");
    //fish1Media->createProfile("PTZ", "PTZ");
    //fish1PTZ->getPTZConfigurations();
    //fish1PTZ->getConfiguration("4");
    //fish1Media->addPTZConfiguration("PTZ", "4");
    //fish1PTZ->getStatus("PTZ");
    //fish1PTZ->tiltUp("PTZ", 5);
    
    initscr();
    noecho();
    int c;
    printw("Use WASD to navigate\nI to zoom in\nO to zoom out\nP to continuous pan\nY to set home position\nH to go to home position\nESPACE to stop movement\nESC to quit");
    while((c=getch()) != 27){
        c = getch();
        if(c==87 || c==119){
            fish1PTZ->tiltUp("PTZ", 5);
        }else if(c == 83 || c==115){
            fish1PTZ->tiltDown("PTZ", 5);
        }else if(c == 65 || c==97){
            fish1PTZ->panLeft("PTZ", 5);
        }else if(c == 68 || c==100){
            fish1PTZ->panRight("PTZ", 5);
        }else if(c == 73 || c==105){
            fish1PTZ->zoomIn("PTZ");
        }else if(c == 79 || c==111){
            fish1PTZ->zoomOut("PTZ");
        }else if(c==80 || c==112 ){
            fish1PTZ->continuousMove("PTZ", 0.2, 0.0, -0.1);
        }else if(c==89 || c==121 ){
            fish1PTZ->setHomePosition("PTZ");
        }else if(c==72 || c==104 ){
            fish1PTZ->goToHomePosition("PTZ");
        }else if(c==32){
            fish1PTZ->stop("PTZ", 1, 1);
        }
    }
    endwin();
 */
/*
     
    struct soap soap;
    soap_init1(&soap, SOAP_IO_UDP);
    soap_register_plugin(&soap, soap_wsa);
    
    int oldFlags = soap.connect_flags;
    soap.connect_flags |= SO_BROADCAST;
    for(int i=0;i<3 ;i++)
        soap_wsdd_Hello(soap, SOAP_WSDD_ADHOC, "soap.udp://239.255.255.250:3702", soap_wsa_rand_uuid(&soap), NULL, l_cameraId, l_types, l_scopes, NULL, l_serviceAddr, 1);
    soap.connect_flags = oldFlags;
 */
/*

    OnvifClientDevice* camera = new OnvifClientDevice("172.22.22.220", "root", "bbb_william");
    camera->getUsers();
    std::vector<std::string> users = camera->getUsernames();
    for(int i = 0; i<users.size(); ++i){
        std::cout << users[i] << std::endl;
    }
   */
    
    OnvifClientMedia* media = new OnvifClientMedia("172.22.22.220", "root", "bbb_william");
    media->getProfiles();
    std::vector<std::string> profiles = media->getProfilesTokens();
    for(int i = 0; i<profiles.size(); ++i){
        std::cout << profiles[i] << std::endl;
    }
    
    media->getStreamURI("profile_1_h264");
    std::string address = media->returnStreamUri();
    std::cout << address << std::endl;
	return 0;
}








