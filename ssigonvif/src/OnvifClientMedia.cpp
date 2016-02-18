#include "ssigonvif/OnvifClientMedia.hpp"
#include <stdexcept>

OnvifClientMedia::OnvifClientMedia(std::string url, std::string user, std::string password) : OnvifClientDevice(url, user, password){
	if(_hasMedia){
		proxyMedia.soap_endpoint = _strUrl.c_str();
		soap_register_plugin(proxyMedia.soap, soap_wsse);
	}else{
        throw std::runtime_error(std::string("Camera does not implement Media functions"));
	}
}

OnvifClientMedia::~OnvifClientMedia(){
}

void OnvifClientMedia::createProfile(std::string profileName, std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){	
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__CreateProfile *trt__CreateProfile = soap_new__trt__CreateProfile(soap, -1);
	_trt__CreateProfileResponse *trt__CreateProfileResponse = soap_new__trt__CreateProfileResponse(soap, -1);

	trt__CreateProfile->Name = profileName;
	trt__CreateProfile->Token = &profileToken;

	if(SOAP_OK != proxyMedia.CreateProfile(trt__CreateProfile, trt__CreateProfileResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}


	soap_destroy(soap); 
	soap_end(soap);
}
void OnvifClientMedia::deleteProfile(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__DeleteProfile *trt__DeleteProfile = soap_new__trt__DeleteProfile(soap, -1);
	_trt__DeleteProfileResponse *trt__DeleteProfileResponse = soap_new__trt__DeleteProfileResponse(soap, -1);

	trt__DeleteProfile->ProfileToken = profileToken;

	if(SOAP_OK != proxyMedia.DeleteProfile(trt__DeleteProfile, trt__DeleteProfileResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	soap_destroy(soap); 
	soap_end(soap);
}


void OnvifClientMedia::getProfiles(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	if (SOAP_OK != soap_wsse_add_Timestamp(proxyMedia.soap, "Time", 100000)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__GetProfiles *trt__GetProfiles = soap_new__trt__GetProfiles(soap, -1);
	_trt__GetProfilesResponse *trt__GetProfilesResponse = soap_new__trt__GetProfilesResponse(soap, -1);

	if (SOAP_OK != proxyMedia.GetProfiles(trt__GetProfiles, trt__GetProfilesResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
		if(trt__GetProfilesResponse->Profiles.size() > 0){
			for(int i = 0; i < trt__GetProfilesResponse->Profiles.size(); i++){
        	    this->_profilesTokens.push_back(trt__GetProfilesResponse->Profiles[i]->token);
			}
		}else{
			throw std::runtime_error("There are no Media Profiles on the device");
		}
	}
	soap_destroy(soap); 
	soap_end(soap); 
}
void OnvifClientMedia::getProfile(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__GetProfile *trt__GetProfile = soap_new__trt__GetProfile(soap, -1);
	_trt__GetProfileResponse *trt__GetProfileResponse = soap_new__trt__GetProfileResponse(soap, -1);

	trt__GetProfile->ProfileToken = profileToken;

	if(SOAP_OK != proxyMedia.GetProfile(trt__GetProfile, trt__GetProfileResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
		this->_profileName = trt__GetProfileResponse->Profile->Name;
	}

	soap_destroy(soap); 
	soap_end(soap);
}


void OnvifClientMedia::getVideoSourceConfigurations(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations = soap_new__trt__GetVideoSourceConfigurations(soap, -1);
	_trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse = soap_new__trt__GetVideoSourceConfigurationsResponse(soap, -1);

	if(SOAP_OK != proxyMedia.GetVideoSourceConfigurations(trt__GetVideoSourceConfigurations, trt__GetVideoSourceConfigurationsResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
		if(trt__GetVideoSourceConfigurationsResponse->Configurations.size() > 0){
			for(int i = 0; i < trt__GetVideoSourceConfigurationsResponse->Configurations.size(); ++i){
				this->_videoSourceConfigurationsTokens.push_back(trt__GetVideoSourceConfigurationsResponse->Configurations[i]->token);
			}
		}else{
			throw std::runtime_error("There are no Video Source Configurations on the device\n");
		}
	}

	soap_destroy(soap); 
	soap_end(soap);
}
void OnvifClientMedia::addVideoSourceConfiguration(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration = soap_new__trt__AddVideoSourceConfiguration(soap, -1);
	_trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse = soap_new__trt__AddVideoSourceConfigurationResponse(soap, -1);

	trt__AddVideoSourceConfiguration->ProfileToken = profileToken;	
	trt__AddVideoSourceConfiguration->ConfigurationToken = configurationToken;

	if(SOAP_OK != proxyMedia.AddVideoSourceConfiguration(trt__AddVideoSourceConfiguration, trt__AddVideoSourceConfigurationResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	soap_destroy(soap); 
	soap_end(soap);
}


void OnvifClientMedia::getVideoEncoderConfigurations(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations = soap_new__trt__GetVideoEncoderConfigurations(soap, -1);
	_trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse = soap_new__trt__GetVideoEncoderConfigurationsResponse(soap, -1);

	if(SOAP_OK != proxyMedia.GetVideoEncoderConfigurations(trt__GetVideoEncoderConfigurations, trt__GetVideoEncoderConfigurationsResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
		if(trt__GetVideoEncoderConfigurationsResponse->Configurations.size() > 0){
			for(int i = 0; i < trt__GetVideoEncoderConfigurationsResponse->Configurations.size(); ++i){
				this->_videoEncoderConfigurationsTokens.push_back(trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->token);
			}
		}else{
			throw std::runtime_error("There are no Video Source Configurations on the device\n");
		}
	}

	soap_destroy(soap); 
	soap_end(soap);
}
void OnvifClientMedia::addVideoEncoderConfiguration(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration = soap_new__trt__AddVideoEncoderConfiguration(soap, -1);
	_trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse = soap_new__trt__AddVideoEncoderConfigurationResponse(soap, -1);

	trt__AddVideoEncoderConfiguration->ProfileToken =profileToken;	
	trt__AddVideoEncoderConfiguration->ConfigurationToken = configurationToken;

	if(SOAP_OK != proxyMedia.AddVideoEncoderConfiguration(trt__AddVideoEncoderConfiguration, trt__AddVideoEncoderConfigurationResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	soap_destroy(soap); 
	soap_end(soap);
}
void OnvifClientMedia::getVideoEncoderConfigurationOptions(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions = soap_new__trt__GetVideoEncoderConfigurationOptions(soap, -1);
	_trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse = soap_new__trt__GetVideoEncoderConfigurationOptionsResponse(soap, -1);

	if(SOAP_OK != proxyMedia.GetVideoEncoderConfigurationOptions(trt__GetVideoEncoderConfigurationOptions, trt__GetVideoEncoderConfigurationOptionsResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	soap_destroy(soap); 
	soap_end(soap);
}
void OnvifClientMedia::setVideoEncoderConfiguration(std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration = soap_new__trt__SetVideoEncoderConfiguration(soap, -1);
	_trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse = soap_new__trt__SetVideoEncoderConfigurationResponse(soap, -1);

	trt__SetVideoEncoderConfiguration->Configuration = soap_new_tt__VideoEncoderConfiguration(soap, -1);
	trt__SetVideoEncoderConfiguration->Configuration->token = "default_1_jpeg";
	trt__SetVideoEncoderConfiguration->Configuration->Resolution = soap_new_tt__VideoResolution(soap, -1);
	trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width = 704;
	trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height = 408;
	trt__SetVideoEncoderConfiguration->Configuration->Encoding = tt__VideoEncoding__MPEG4;


    if(SOAP_OK != proxyMedia.SetVideoEncoderConfiguration(trt__SetVideoEncoderConfiguration, trt__SetVideoEncoderConfigurationResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	soap_destroy(soap); 
	soap_end(soap);
}


void OnvifClientMedia::getStreamURI(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}
	_trt__GetStreamUri *trt__GetStreamUri = soap_new__trt__GetStreamUri(soap, -1);
	trt__GetStreamUri->StreamSetup = soap_new_tt__StreamSetup(soap, -1);
	trt__GetStreamUri->StreamSetup->Stream = tt__StreamType__RTP_Unicast;
	trt__GetStreamUri->StreamSetup->Transport = soap_new_tt__Transport(soap, -1);
	trt__GetStreamUri->StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;
	trt__GetStreamUri->ProfileToken = profileToken;

	_trt__GetStreamUriResponse *trt__GetStreamUriResponse = soap_new__trt__GetStreamUriResponse(soap, -1);

	if(SOAP_OK != proxyMedia.GetStreamUri(trt__GetStreamUri, trt__GetStreamUriResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
		if(trt__GetStreamUriResponse->MediaUri != NULL){
			this->_streamUri = trt__GetStreamUriResponse->MediaUri->Uri;
		}else{
			throw std::runtime_error("Error");
		}
	}

	soap_destroy(soap); 
	soap_end(soap);
}


void  OnvifClientMedia::addPTZConfiguration(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_trt__AddPTZConfiguration *trt__AddPTZConfiguration = soap_new__trt__AddPTZConfiguration(soap, -1);
	_trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse = soap_new__trt__AddPTZConfigurationResponse(soap, -1);

	trt__AddPTZConfiguration->ProfileToken =profileToken;	
	trt__AddPTZConfiguration->ConfigurationToken = configurationToken;

	if(SOAP_OK != proxyMedia.AddPTZConfiguration(trt__AddPTZConfiguration, trt__AddPTZConfigurationResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

std::string OnvifClientMedia::getProfileName(){
	return _profileName;
}
	    
std::vector<std::string> OnvifClientMedia::getProfilesTokens(){
	return _profilesTokens;
}

std::vector<std::string> OnvifClientMedia::getVideoSourceConfigurationsTokens(){
	return _videoSourceConfigurationsTokens;
}

std::vector<std::string> OnvifClientMedia::getVideoEncoderConfigurationsTokens(){
	return _videoEncoderConfigurationsTokens;
}

std::string OnvifClientMedia::returnStreamUri(){
	return _streamUri;
}
