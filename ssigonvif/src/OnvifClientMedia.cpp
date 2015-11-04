#include "ssigonvif/OnvifClientMedia.hpp"
//#include "MediaBinding.nsmap"


OnvifClientMedia::OnvifClientMedia(std::string url, std::string user, std::string password, bool showCapabilities) : OnvifClientDevice(url, user, password, showCapabilities){
	if(_hasMedia){
		proxyMedia.soap_endpoint = _strUrl.c_str();
		soap_register_plugin(proxyMedia.soap, soap_wsse);
	}else{
		throw "Camera does not implement Media functions";
	}
}

OnvifClientMedia::~OnvifClientMedia(){
}

int OnvifClientMedia::getVideoSourceConfigurations(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations = soap_new__trt__GetVideoSourceConfigurations(soap, -1);
	_trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse = soap_new__trt__GetVideoSourceConfigurationsResponse(soap, -1);

	if(SOAP_OK == proxyMedia.GetVideoSourceConfigurations(trt__GetVideoSourceConfigurations, trt__GetVideoSourceConfigurationsResponse)){
		for(int i = 0; i<trt__GetVideoSourceConfigurationsResponse->Configurations.size(); ++i){
			std::cout << "Name:" << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->Name << std::endl << "UseCount" <<trt__GetVideoSourceConfigurationsResponse->Configurations[i]->UseCount << std::endl << "Token:" << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->token << std::endl <<"SourceToken:" << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->SourceToken << std::endl << "X_bound: " << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->Bounds->x << std::endl << "Y_bound: " << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->Bounds->y << std::endl << "Width_bound::" << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->Bounds->width << std::endl << "Height_bound" << trt__GetVideoSourceConfigurationsResponse->Configurations[i]->Bounds->height << std::endl;
			std::cout << std::endl;

		}

	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);

}

int OnvifClientMedia::getVideoEncoderConfigurations(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations = soap_new__trt__GetVideoEncoderConfigurations(soap, -1);
	_trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse = soap_new__trt__GetVideoEncoderConfigurationsResponse(soap, -1);

	if(SOAP_OK == proxyMedia.GetVideoEncoderConfigurations(trt__GetVideoEncoderConfigurations, trt__GetVideoEncoderConfigurationsResponse)){
		for(int i = 0; i<trt__GetVideoEncoderConfigurationsResponse->Configurations.size(); ++i){
			std::cout << "VideoEncoderToken #" << i << ": " << trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->token << std::endl;
			std::cout << "Name:" <<trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->Name << std::endl << "UseCount: " <<trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->UseCount << std::endl << "Encoding:" << trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->Encoding << std::endl << "Resolution:" <<trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->Resolution->Width << "x" << trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->Resolution->Height << std::endl << "Quality:" <<trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->Quality << std::endl << "FrameRateLimit:" << trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->RateControl->FrameRateLimit << std::endl << "EncodingInterval:" << trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->RateControl->EncodingInterval << std::endl << "BitrateLimit:" << trt__GetVideoEncoderConfigurationsResponse->Configurations[i]->RateControl->BitrateLimit << std::endl;
			std::cout << std::endl;
		}

	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::getVideoEncoderConfigurationOptions(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions = soap_new__trt__GetVideoEncoderConfigurationOptions(soap, -1);
	_trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse = soap_new__trt__GetVideoEncoderConfigurationOptionsResponse(soap, -1);

	if(SOAP_OK == proxyMedia.GetVideoEncoderConfigurationOptions(trt__GetVideoEncoderConfigurationOptions, trt__GetVideoEncoderConfigurationOptionsResponse)){
		std::cout << "Min Quality: " << trt__GetVideoEncoderConfigurationOptionsResponse->Options->QualityRange->Min << std::endl << "Max Quality: " << trt__GetVideoEncoderConfigurationOptionsResponse->Options->QualityRange->Max << std::endl << "JPEG:" << std::endl << std::endl << "     Min Frame Rate: " << trt__GetVideoEncoderConfigurationOptionsResponse->Options->JPEG->FrameRateRange->Min << std::endl << "     Max Frame Rate: " << trt__GetVideoEncoderConfigurationOptionsResponse->Options->JPEG->FrameRateRange->Max <<std::endl << "     Min Encoding Interval:" << trt__GetVideoEncoderConfigurationOptionsResponse->Options->JPEG->EncodingIntervalRange->Min << std::endl << "     Max Encoding Interval:" << trt__GetVideoEncoderConfigurationOptionsResponse->Options->JPEG->EncodingIntervalRange->Max << std::endl << std::endl;
	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::setVideoEncoderConfiguration(std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration = soap_new__trt__SetVideoEncoderConfiguration(soap, -1);
	_trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse = soap_new__trt__SetVideoEncoderConfigurationResponse(soap, -1);

	trt__SetVideoEncoderConfiguration->Configuration = soap_new_tt__VideoEncoderConfiguration(soap, -1);
	trt__SetVideoEncoderConfiguration->Configuration->token = "default_1_jpeg";
	trt__SetVideoEncoderConfiguration->Configuration->Resolution = soap_new_tt__VideoResolution(soap, -1);
	trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width = 704;
	trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height = 408;
	trt__SetVideoEncoderConfiguration->Configuration->Encoding = tt__VideoEncoding__MPEG4;


	if(SOAP_OK == proxyMedia.SetVideoEncoderConfiguration(trt__SetVideoEncoderConfiguration, trt__SetVideoEncoderConfigurationResponse)){

	}else{
		std::cout << "ERROR:" <<std::endl;
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);

}

int OnvifClientMedia::getStreamURI(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}
	_trt__GetStreamUri *trt__GetStreamUri = soap_new__trt__GetStreamUri(soap, -1);
	trt__GetStreamUri->StreamSetup = soap_new_tt__StreamSetup(soap, -1);
	trt__GetStreamUri->StreamSetup->Stream = tt__StreamType__RTP_Unicast;
	trt__GetStreamUri->StreamSetup->Transport = soap_new_tt__Transport(soap, -1);
	trt__GetStreamUri->StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;
	trt__GetStreamUri->ProfileToken = profileToken;

	_trt__GetStreamUriResponse *trt__GetStreamUriResponse = soap_new__trt__GetStreamUriResponse(soap, -1);

	if(SOAP_OK == proxyMedia.GetStreamUri(trt__GetStreamUri, trt__GetStreamUriResponse)){
		std::cout << "StreamURI: " << trt__GetStreamUriResponse->MediaUri->Uri << std::endl;
		std::cout << "InvalidAfterConnect: " << trt__GetStreamUriResponse->MediaUri->InvalidAfterConnect << std::endl;
		std::cout << "InvalidAfterReboot: " << trt__GetStreamUriResponse->MediaUri->InvalidAfterReboot << std::endl;
		std::cout << "Timeout: " << trt__GetStreamUriResponse->MediaUri->Timeout << std::endl;

	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::getProfile(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_trt__GetProfile *trt__GetProfile = soap_new__trt__GetProfile(soap, -1);
	_trt__GetProfileResponse *trt__GetProfileResponse = soap_new__trt__GetProfileResponse(soap, -1);

	trt__GetProfile->ProfileToken = profileToken;

	if(SOAP_OK == proxyMedia.GetProfile(trt__GetProfile, trt__GetProfileResponse)){
		std::cout << "Video Source token: " << trt__GetProfileResponse->Profile->VideoSourceConfiguration->token << std::endl;
		std::cout << "Video Encoder token: " << trt__GetProfileResponse->Profile->VideoEncoderConfiguration->token << std::endl;
	
	}
	else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::createProfile(std::string profileName, std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_trt__CreateProfile *trt__CreateProfile = soap_new__trt__CreateProfile(soap, -1);
	_trt__CreateProfileResponse *trt__CreateProfileResponse = soap_new__trt__CreateProfileResponse(soap, -1);

	trt__CreateProfile->Name = profileName;
	trt__CreateProfile->Token = &profileToken;

	if(SOAP_OK == proxyMedia.CreateProfile(trt__CreateProfile, trt__CreateProfileResponse)){
	}else{
		//PrintErr(proxyMedia.soap);
	}


	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::deleteProfile(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_trt__DeleteProfile *trt__DeleteProfile = soap_new__trt__DeleteProfile(soap, -1);
	_trt__DeleteProfileResponse *trt__DeleteProfileResponse = soap_new__trt__DeleteProfileResponse(soap, -1);

	trt__DeleteProfile->ProfileToken = profileToken;

	if(SOAP_OK == proxyMedia.DeleteProfile(trt__DeleteProfile, trt__DeleteProfileResponse)){

	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int  OnvifClientMedia::addPTZConfiguration(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_trt__AddPTZConfiguration *trt__AddPTZConfiguration = soap_new__trt__AddPTZConfiguration(soap, -1);
	_trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse = soap_new__trt__AddPTZConfigurationResponse(soap, -1);

	trt__AddPTZConfiguration->ProfileToken =profileToken;	
	trt__AddPTZConfiguration->ConfigurationToken = configurationToken;

	if(SOAP_OK == proxyMedia.AddPTZConfiguration(trt__AddPTZConfiguration, trt__AddPTZConfigurationResponse)){
	
	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::addVideoSourceConfiguration(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration = soap_new__trt__AddVideoSourceConfiguration(soap, -1);
	_trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse = soap_new__trt__AddVideoSourceConfigurationResponse(soap, -1);

	trt__AddVideoSourceConfiguration->ProfileToken =profileToken;	
	trt__AddVideoSourceConfiguration->ConfigurationToken = configurationToken;

	if(SOAP_OK == proxyMedia.AddVideoSourceConfiguration(trt__AddVideoSourceConfiguration, trt__AddVideoSourceConfigurationResponse)){
	
	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::addVideoEncoderConfiguration(std::string profileToken, std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration = soap_new__trt__AddVideoEncoderConfiguration(soap, -1);
	_trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse = soap_new__trt__AddVideoEncoderConfigurationResponse(soap, -1);

	trt__AddVideoEncoderConfiguration->ProfileToken =profileToken;	
	trt__AddVideoEncoderConfiguration->ConfigurationToken = configurationToken;

	if(SOAP_OK == proxyMedia.AddVideoEncoderConfiguration(trt__AddVideoEncoderConfiguration, trt__AddVideoEncoderConfigurationResponse)){
	
	}else{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientMedia::getProfiles(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	if (SOAP_OK != soap_wsse_add_Timestamp(proxyMedia.soap, "Time", 100000)) 
	{
		return -1;
	}

	_trt__GetProfiles *trt__GetProfiles = soap_new__trt__GetProfiles(soap, -1);
	_trt__GetProfilesResponse *trt__GetProfilesResponse = soap_new__trt__GetProfilesResponse(soap, -1);

	if (SOAP_OK == proxyMedia.GetProfiles(trt__GetProfiles, trt__GetProfilesResponse))
	{
		_trt__GetStreamUri *trt__GetStreamUri = soap_new__trt__GetStreamUri(soap, -1);
		trt__GetStreamUri->StreamSetup = soap_new_tt__StreamSetup(soap, -1);
		trt__GetStreamUri->StreamSetup->Stream = tt__StreamType__RTP_Unicast;
		trt__GetStreamUri->StreamSetup->Transport = soap_new_tt__Transport(soap, -1);
		trt__GetStreamUri->StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;

		_trt__GetStreamUriResponse *trt__GetStreamUriResponse = soap_new__trt__GetStreamUriResponse(soap, -1);

		//processEventLog(__FILE__, __LINE__, stdout, "-------------------MediaProfiles-------------------");
		for (int i = 0; i < trt__GetProfilesResponse->Profiles.size(); i++)
		{
			/*
			processEventLog(__FILE__, __LINE__, stdout, "profile%d:%s Token:%s\r", i, trt__GetProfilesResponse->Profiles[i]->Name.c_str(), trt__GetProfilesResponse->Profiles[i]->token.c_str());
			trt__GetStreamUri->ProfileToken = trt__GetProfilesResponse->Profiles[i]->token;

			if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyMedia.soap, NULL, _user.c_str(), _password.c_str()))
			{
				return -1;
			}

			if (SOAP_OK == proxyMedia.GetStreamUri(trt__GetStreamUri, trt__GetStreamUriResponse))
			{
				processEventLog(__FILE__, __LINE__, stdout, "RTSP URI:%s", trt__GetStreamUriResponse->MediaUri->Uri.c_str());
			}
			else
			{
				//PrintErr(proxyMedia.soap);
			}
			std::cout << std::endl << std::endl;
			*/
		}
	}
	else
	{
		//PrintErr(proxyMedia.soap);
	}

	soap_destroy(soap); 
	soap_end(soap); 
}