#ifndef ONVIFCLIENTMEDIA_HPP
#define ONVIFCLIENTMEDIA_HPP

#include "OnvifClientDevice.hpp"
#include "onvif/soapMediaBindingProxy.h"

class OnvifClientMedia : public OnvifClientDevice{
public:
	OnvifClientMedia(std::string url, std::string user, std::string password, bool showCapabilities);
	~OnvifClientMedia();

public:
	//create a new profile
	int createProfile(std::string profileName, std::string profileToken);
	//delete profile
	int deleteProfile(std::string profileToken);

	//get a list of all media profiles
	int getProfiles();
	//get one media profile
	int getProfile(std::string profileToken);

	//get all video source configurations
	int getVideoSourceConfigurations();
	//add video source configuration
	int addVideoSourceConfiguration(std::string profileToken, std::string configurationToken);

	//get all video encoder configurations
	int getVideoEncoderConfigurations();
	//add video encoder configuration
	int addVideoEncoderConfiguration(std::string profileToken, std::string configurationToken);

	int setVideoEncoderConfiguration(std::string configurationToken);

	//get stream URI
	int getStreamURI(std::string profileToken);

	//get video encoder configuration options
	int getVideoEncoderConfigurationOptions(std::string profileToken, std::string configurationToken);

	//add PTZ configuration to media profile
	int  addPTZConfiguration(std::string profileToken, std::string configurationToken);

private:
	MediaBindingProxy proxyMedia;
};

#endif