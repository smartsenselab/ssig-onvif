#ifndef ONVIFCLIENTPTZ_HPP
#define ONVIFCLIENTPTZ_HPP

#include "OnvifClientDevice.hpp"
#include "onvif/soapPTZBindingProxy.h"

class OnvifClientPTZ : public OnvifClientDevice{
public:
	OnvifClientPTZ(std::string url, std::string user, std::string password, bool showCapabilities);
	~OnvifClientPTZ();

public:
	//get all PTZ configurations
	int getPTZConfigurations();
	//get and print PTZ Status
	int getStatus(std::string profileToken);
	//absolute move
	int absoluteMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed);
	//relative move
	int relativeMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed);
	//continuous move
	int continuousMove(std::string profileToken, float panSpeed, float tiltSpeed, float zoomSpeed);
	//stop movement
	int stop(std::string profileToken, bool panTilt, bool zoom);
	//setHomePosition
	int setHomePosition(std::string profileToken);
	//goToHomePosition
	int goToHomePosition(std::string profileToken);
	//Get configuration and print it
	int getConfiguration(std::string configurationToken);


	//pan to the left n Degress
	int panLeft(std::string profileToken, int nDegrees);
	//pan to the right n Degrees
	int panRight(std::string profileToken, int nDegrees);

	//tilt down
	int tiltDown(std::string profileToken, int nDegrees);
	//tilt up
	int tiltUp(std::string profileToken, int nDegrees);

	//zoom in
	int zoomIn(std::string profileToken);
	//zoom out
	int zoomOut(std::string profileToken);
	
private:
	PTZBindingProxy proxyPTZ;
};

#endif
