#include "ssigonvif/OnvifClientPTZ.hpp"

OnvifClientPTZ::OnvifClientPTZ(std::string url, std::string user, std::string password, bool showCapabilities) : OnvifClientDevice(url, user, password, showCapabilities){
	if(_hasPTZ){
		proxyPTZ.soap_endpoint = _strUrl.c_str();
		soap_register_plugin(proxyPTZ.soap, soap_wsse);
	}else{
		throw "Camera does not implement PTZ functions";
	}
}

OnvifClientPTZ::~OnvifClientPTZ(){
}

int OnvifClientPTZ::getPTZConfigurations(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_tptz__GetConfigurations *tptz__GetConfigurations = soap_new__tptz__GetConfigurations(soap, -1);
	_tptz__GetConfigurationsResponse *tptz__GetConfigurationsResponse = soap_new__tptz__GetConfigurationsResponse(soap, -1);

	if(SOAP_OK == proxyPTZ.GetConfigurations(tptz__GetConfigurations, tptz__GetConfigurationsResponse)){
		for(int i = 0; i<tptz__GetConfigurationsResponse->PTZConfiguration.size(); ++i){
			std::cout << "ConfigurationToken #" << i << ": " << tptz__GetConfigurationsResponse->PTZConfiguration[i]->token << std::endl;
		}
	}else{
		//PrintErr(proxyPTZ.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::getStatus(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_tptz__GetStatus *tptz__GetStatus = soap_new__tptz__GetStatus(soap, -1);
	_tptz__GetStatusResponse *tptz__GetStatusResponse = soap_new__tptz__GetStatusResponse(soap, -1);

	tptz__GetStatus->ProfileToken = profileToken.c_str();
	
	if(SOAP_OK == proxyPTZ.GetStatus(tptz__GetStatus, tptz__GetStatusResponse)){
		std::cout << "PAN: " << tptz__GetStatusResponse->PTZStatus->Position->PanTilt->x << std::endl << "TILT: " <<tptz__GetStatusResponse->PTZStatus->Position->PanTilt->y << std::endl;
		std::cout << "ZOOM:" << tptz__GetStatusResponse->PTZStatus->Position->Zoom->x << std::endl;

		//std::cout << "PanTilt:" << tptz__GetStatusResponse->PTZStatus->MoveStatus->PanTilt << std::endl << "ZoomStatus" << tptz__GetStatusResponse->PTZStatus->MoveStatus->Zoom << std::endl << "ERROR: " << tptz__GetStatusResponse->PTZStatus->Error << std::endl << "UtcTime: " << tptz__GetStatusResponse->PTZStatus->UtcTime << std::endl;
	}else{
		//PrintErr(proxyPTZ.soap);
	}
	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::absoluteMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_tptz__AbsoluteMove *tptz__AbsoluteMove = soap_new__tptz__AbsoluteMove(soap, -1);
	_tptz__AbsoluteMoveResponse *tptz__AbsoluteMoveResponse = soap_new__tptz__AbsoluteMoveResponse(soap, -1);

	tptz__AbsoluteMove->ProfileToken = profileToken;

	//setting pan and tilt
	tptz__AbsoluteMove->Position = soap_new_tt__PTZVector(soap, -1);
	tptz__AbsoluteMove->Position->PanTilt = soap_new_tt__Vector2D(soap, -1);
	tptz__AbsoluteMove->Speed = soap_new_tt__PTZSpeed(soap, -1);
	tptz__AbsoluteMove->Speed->PanTilt = soap_new_tt__Vector2D(soap, -1);
	//pan
	tptz__AbsoluteMove->Position->PanTilt->x = pan;
	tptz__AbsoluteMove->Speed->PanTilt->x = panSpeed;
	//tilt
	tptz__AbsoluteMove->Position->PanTilt->y = tilt;
	tptz__AbsoluteMove->Speed->PanTilt->y = tiltSpeed;
	//setting zoom
	tptz__AbsoluteMove->Position->Zoom = soap_new_tt__Vector1D(soap, -1);
	tptz__AbsoluteMove->Speed->Zoom = soap_new_tt__Vector1D(soap, -1);
	tptz__AbsoluteMove->Position->Zoom->x = zoom;
	tptz__AbsoluteMove->Speed->Zoom->x = zoomSpeed;

	if(SOAP_OK == proxyPTZ.AbsoluteMove(tptz__AbsoluteMove, tptz__AbsoluteMoveResponse)){
	
	}else{
		std::cout << "AbsoluteMove ERROR:" << std::endl;
		//PrintErr(proxyPTZ.soap);
		std::cout << std::endl;
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::relativeMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_tptz__RelativeMove *tptz__RelativeMove = soap_new__tptz__RelativeMove(soap, -1);
	_tptz__RelativeMoveResponse *tptz__RelativeMoveResponse = soap_new__tptz__RelativeMoveResponse(soap, -1);

	tptz__RelativeMove->ProfileToken = profileToken;

	//setting pan and tilt
	tptz__RelativeMove->Translation = soap_new_tt__PTZVector(soap, -1);
	tptz__RelativeMove->Translation->PanTilt = soap_new_tt__Vector2D(soap, -1);
	tptz__RelativeMove->Speed = soap_new_tt__PTZSpeed(soap, -1);
	tptz__RelativeMove->Speed->PanTilt = soap_new_tt__Vector2D(soap, -1);
	//pan
	tptz__RelativeMove->Translation->PanTilt->x = pan;
	tptz__RelativeMove->Speed->PanTilt->x = panSpeed;
	//tilt
	tptz__RelativeMove->Translation->PanTilt->y = tilt;
	tptz__RelativeMove->Speed->PanTilt->y = tiltSpeed;
	//setting zoom
	tptz__RelativeMove->Translation->Zoom = soap_new_tt__Vector1D(soap, -1);
	tptz__RelativeMove->Speed->Zoom = soap_new_tt__Vector1D(soap, -1);
	tptz__RelativeMove->Translation->Zoom->x = zoom;
	tptz__RelativeMove->Speed->Zoom->x = zoomSpeed;

	if(SOAP_OK == proxyPTZ.RelativeMove(tptz__RelativeMove, tptz__RelativeMoveResponse)){
	
	}else{
		std::cout << "RelativeMove ERROR:" << std::endl;
		//PrintErr(proxyPTZ.soap);
		std::cout << std::endl;
	}
	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::continuousMove(std::string profileToken, float panSpeed, float tiltSpeed, float zoomSpeed){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_tptz__ContinuousMove *tptz__ContinuousMove = soap_new__tptz__ContinuousMove(soap, -1);
	_tptz__ContinuousMoveResponse *tptz__ContinuousMoveResponse = soap_new__tptz__ContinuousMoveResponse(soap, -1);

	tptz__ContinuousMove->ProfileToken = profileToken;

	//setting pan and tilt speed
	tptz__ContinuousMove->Velocity = soap_new_tt__PTZSpeed(soap, -1);
	tptz__ContinuousMove->Velocity->PanTilt = soap_new_tt__Vector2D(soap, -1);
	tptz__ContinuousMove->Velocity->PanTilt->x = panSpeed;
	tptz__ContinuousMove->Velocity->PanTilt->y = tiltSpeed;

	//setting zoom speed
	tptz__ContinuousMove->Velocity->Zoom = soap_new_tt__Vector1D(soap, -1);
	tptz__ContinuousMove->Velocity->Zoom->x = zoomSpeed;

	long long tempo = 1;
	tptz__ContinuousMove->Timeout = &tempo;

	if(SOAP_OK == proxyPTZ.ContinuousMove(tptz__ContinuousMove, tptz__ContinuousMoveResponse)){

	}else{
		std::cout << "ContinuousMove ERROR:" << std::endl;
		//PrintErr(proxyPTZ.soap);
		std::cout;
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::stop(std::string profileToken, bool panTilt, bool zoom){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str()))
	{
		return -1;
	}

	_tptz__Stop *tptz__Stop= soap_new__tptz__Stop(soap, -1);
	_tptz__StopResponse *tptz__StopResponse = soap_new__tptz__StopResponse(soap, -1);

	tptz__Stop->ProfileToken = profileToken;
	tptz__Stop->PanTilt = &panTilt;
	tptz__Stop->Zoom = &zoom;

	if(SOAP_OK == proxyPTZ.Stop(tptz__Stop, tptz__StopResponse)){

	}else{
		//PrintErr(proxyPTZ.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::setHomePosition(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_tptz__SetHomePosition *tptz__SetHomePosition = soap_new__tptz__SetHomePosition(soap, -1);
	_tptz__SetHomePositionResponse *tptz__SetHomePositionResponse = soap_new__tptz__SetHomePositionResponse(soap, -1);

	tptz__SetHomePosition->ProfileToken = profileToken;

	if(SOAP_OK == proxyPTZ.SetHomePosition(tptz__SetHomePosition, tptz__SetHomePositionResponse)){

	}else{
		//PrintErr(proxyPTZ.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::goToHomePosition(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_tptz__GotoHomePosition *tptz__GotoHomePosition = soap_new__tptz__GotoHomePosition(soap, -1);
	_tptz__GotoHomePositionResponse *tptz__GotoHomePositionResponse = soap_new__tptz__GotoHomePositionResponse(soap, -1);

	tptz__GotoHomePosition->ProfileToken = profileToken;

	if(SOAP_OK == proxyPTZ.GotoHomePosition(tptz__GotoHomePosition, tptz__GotoHomePositionResponse)){

	}else{
		//PrintErr(proxyPTZ.soap);
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::getConfiguration(std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		return -1;
	}

	_tptz__GetConfiguration *tptz__GetConfiguration = soap_new__tptz__GetConfiguration(soap,-1);
	_tptz__GetConfigurationResponse *tptz__GetConfigurationResponse = soap_new__tptz__GetConfigurationResponse(soap,-1);

	tptz__GetConfiguration->PTZConfigurationToken = configurationToken;



	if(SOAP_OK == proxyPTZ.GetConfiguration(tptz__GetConfiguration, tptz__GetConfigurationResponse)){
		std::cout << std::endl;
		std::cout << "Absolute Pan Tilt Position Space: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultAbsolutePantTiltPositionSpace->	c_str() << std::endl;
		std::cout << "Absolute Zoom Position Space: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultAbsoluteZoomPositionSpace->	c_str() << std::endl;
		std::cout << "Relative Pan Tilt Translation Space: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultRelativeZoomTranslationSpace->c_str() << std::endl;
		std::cout << "Relative Zoom Translation Space: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultContinuousPanTiltVelocitySpace->c_str() << std::endl;
		std::cout << "Continuous Pan Tilt Velocity Space: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultContinuousZoomVelocitySpace->c_str() << std::endl;
		std::cout << "Continuous Zoom Velocity Space: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultContinuousZoomVelocitySpace->c_str() << std::endl << std::endl;
		
		printf("Default PTZ Timeout: %ds\n", *tptz__GetConfigurationResponse->PTZConfiguration->DefaultPTZTimeout/1000);

		printf("Pan Min Limit: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->PanTiltLimits->Range->XRange->Min);
		printf("Pan Max Limit: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->PanTiltLimits->Range->XRange->Max);

		printf("Tilt Min limit: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->PanTiltLimits->Range->YRange->Min);
		printf("Tilt Max limit: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->PanTiltLimits->Range->YRange->Max);
		std::cout << "Coordinate System: " << tptz__GetConfigurationResponse->PTZConfiguration->PanTiltLimits->Range->URI.c_str() << std::endl;
		std::cout << std::endl;

		printf("Zoom Min limit: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->ZoomLimits->Range->XRange->Min);
		printf("Zoom Max limit: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->ZoomLimits->Range->XRange->Max);


		printf("Default Pan Speed: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->DefaultPTZSpeed->PanTilt->x);
		printf("Default Tilt Speed: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->DefaultPTZSpeed->PanTilt->y);
		std::cout << "Coordinate System: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultPTZSpeed->PanTilt->space->c_str() << std::endl;
		printf("Default Zoom Speed: %f\n", tptz__GetConfigurationResponse->PTZConfiguration->DefaultPTZSpeed->Zoom->x);
		std::cout << "Coordinate System: " << tptz__GetConfigurationResponse->PTZConfiguration->DefaultPTZSpeed->Zoom->space->c_str() << std::endl;
		std::cout << std::endl << std::endl;
		return 0;
	}else{
		return 1;
	}

	soap_destroy(soap); 
	soap_end(soap);
}

int OnvifClientPTZ::panLeft(std::string profileToken, int nDegrees){
	float pan = -nDegrees*0.0027777778;
	return relativeMove(profileToken, pan, 1, 0.0, 0.0, 0.0, 0.0);
}

int OnvifClientPTZ::panRight(std::string profileToken, int nDegrees){
	float pan = nDegrees*0.0027777778;
	return relativeMove(profileToken, pan, 1, 0.0, 0.0, 0.0, 0.0);
}

int OnvifClientPTZ::tiltDown(std::string profileToken, int nDegrees){
	float tilt = -nDegrees*0.0055555556;
	return relativeMove(profileToken, 0.0, 0.0, tilt, 1.0, 0.0, 0.0);
}

int OnvifClientPTZ::tiltUp(std::string profileToken, int nDegrees){
	float tilt = nDegrees*0.0055555556;
	return relativeMove(profileToken, 0.0, 0.0, tilt, 1.0, 0.0, 0.0);
}

int OnvifClientPTZ::zoomIn(std::string profileToken){
	return relativeMove(profileToken, 0.0, 0.0, 0.0, 0.0, 0.05, 1.0);
}

int OnvifClientPTZ::zoomOut(std::string profileToken){
	return relativeMove(profileToken, 0.0, 0.0, 0.0, 0.0, -0.05, 1.0);
}