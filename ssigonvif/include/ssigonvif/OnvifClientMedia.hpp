#ifndef ONVIFCLIENTMEDIA_HPP
#define ONVIFCLIENTMEDIA_HPP

#include "OnvifClientDevice.hpp"
#include "onvif/soapMediaBindingProxy.h"
#include <vector>
#include <string>

class OnvifClientMedia : public OnvifClientDevice{
public:
	OnvifClientMedia(std::string url, std::string user, std::string password);
	~OnvifClientMedia();

public:
	//create a new profile
	void createProfile(std::string profileName, std::string profileToken);
	//delete profile
	void deleteProfile(std::string profileToken);

	//get a list of all media profiles
	void getProfiles();
	//get one media profile
	void getProfile(std::string profileToken);


	//get all video source configurations
	void getVideoSourceConfigurations();
	//add video source configuration
	void addVideoSourceConfiguration(std::string profileToken, std::string configurationToken);


	//get all video encoder configurations
	void getVideoEncoderConfigurations();
	//add video encoder configuration
	void addVideoEncoderConfiguration(std::string profileToken, std::string configurationToken);
	//get video encoder configuration options
	void getVideoEncoderConfigurationOptions(std::string profileToken, std::string configurationToken);
	//get video encoder configuration from Configuration with std:string configurationToken
	void setVideoEncoderConfiguration(std::string configurationToken);


	//get stream URI
	void getStreamURI(std::string profileToken);


	//add PTZ configuration to media profile
	void  addPTZConfiguration(std::string profileToken, std::string configurationToken);

	std::string getProfileName();
	    
	std::vector<std::string> getProfilesTokens();

	std::vector<std::string> getVideoSourceConfigurationsTokens();

	std::vector<std::string> getVideoEncoderConfigurationsTokens();

	std::string returnStreamUri();

private:

	//name of the profile with profileToken setted by getProfile(profileToken) function
	std::string _profileName;

	//vector containing all profiles tokens of the device, setted by getProfiles() function
	std::vector<std::string> _profilesTokens;

	//vector containing all tokens from the different Video Source Configurations of the device
	std::vector<std::string> _videoSourceConfigurationsTokens;

	//vector containing all tokens from the different Video Encoder Configurations of the device
	std::vector<std::string> _videoEncoderConfigurationsTokens;

	//string containing a Stream URI setted with:
	//StreamType: RTP Unicast
	//TransportProtocol: RTSP
	std::string _streamUri;

	MediaBindingProxy proxyMedia;
};

#endif