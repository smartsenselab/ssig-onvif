#ifndef ONVIFCLIENTPTZ_HPP
#define ONVIFCLIENTPTZ_HPP

#include "OnvifClientDevice.hpp"
#include "onvif/soapPTZBindingProxy.h"
#include <vector>
#include <string>

class OnvifClientPTZ : public OnvifClientDevice{
public:
	OnvifClientPTZ(std::string url, std::string user, std::string password);
	~OnvifClientPTZ();

public:
	//get all PTZ configurations and sets the vector PTZConfigurationsTokens
	void getConfigurations();
	//get the PTZ Status and sets the vector position
	void getStatus(std::string profileToken);
	//absolute move
	void absoluteMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed);
	//relative move
	void relativeMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed);
	//continuous move
	void continuousMove(std::string profileToken, float panSpeed, float tiltSpeed, float zoomSpeed);
	//stop movement
	void stop(std::string profileToken, bool panTilt, bool zoom);
	//setHomePosition
	void setHomePosition(std::string profileToken);
	//goToHomePosition
	void goToHomePosition(std::string profileToken);
	//Get configuration and print it
	void getConfiguration(std::string configurationToken);


	//pan to the left n Degress
	void panLeft(std::string profileToken, int nDegrees);
	//pan to the right n Degrees
	void panRight(std::string profileToken, int nDegrees);

	//tilt down
	void tiltDown(std::string profileToken, int nDegrees);
	//tilt up
	void tiltUp(std::string profileToken, int nDegrees);

	//zoom in
	void zoomIn(std::string profileToken);
	//zoom out
	void zoomOut(std::string profileToken);

	//getter for _PTZConfigurationsTokens
	std::vector<std::string> getPTZConfigurationsTokens();

	//getter for _positon
    std::vector<float> getPosition();

	
private:

	//vector containing the exixting PTZConfigurations Tokens on the device
	std::vector<std::string> _PTZConfigurationsTokens;

	//PTZ camera position, values of PAN, TILT and ZOOM respectively
    std::vector<float> _position;

	PTZBindingProxy proxyPTZ;
};

#endif
