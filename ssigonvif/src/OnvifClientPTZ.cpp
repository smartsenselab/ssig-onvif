#include "ssigonvif/OnvifClientPTZ.hpp"

OnvifClientPTZ::OnvifClientPTZ(std::string url, std::string user, std::string password) : OnvifClientDevice(url, user, password){
	if(_hasPTZ){
		proxyPTZ.soap_endpoint = _strUrl.c_str();
		soap_register_plugin(proxyPTZ.soap, soap_wsse);
	}else{
		throw "Camera does not implement PTZ functions";
	}
}

OnvifClientPTZ::~OnvifClientPTZ(){
}

void OnvifClientPTZ::getConfigurations(){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_tptz__GetConfigurations *tptz__GetConfigurations = soap_new__tptz__GetConfigurations(soap, -1);
	_tptz__GetConfigurationsResponse *tptz__GetConfigurationsResponse = soap_new__tptz__GetConfigurationsResponse(soap, -1);

	if(SOAP_OK != proxyPTZ.GetConfigurations(tptz__GetConfigurations, tptz__GetConfigurationsResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
		for(int i = 0; i<tptz__GetConfigurationsResponse->PTZConfiguration.size(); ++i){
			this->_PTZConfigurationsTokens.push_back(tptz__GetConfigurationsResponse->PTZConfiguration[i]->token);
		}	
	}

	soap_destroy(soap); 
	soap_end(soap);
}

void OnvifClientPTZ::getStatus(std::string profileToken){
    if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_tptz__GetStatus *tptz__GetStatus = soap_new__tptz__GetStatus(soap, -1);
	_tptz__GetStatusResponse *tptz__GetStatusResponse = soap_new__tptz__GetStatusResponse(soap, -1);

	tptz__GetStatus->ProfileToken = profileToken.c_str();
	
	if(SOAP_OK != proxyPTZ.GetStatus(tptz__GetStatus, tptz__GetStatusResponse)){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}else{
        this->_position.push_back(tptz__GetStatusResponse->PTZStatus->Position->PanTilt->x); //pan value
        this->_position.push_back(tptz__GetStatusResponse->PTZStatus->Position->PanTilt->y); //tilt value
        this->_position.push_back(tptz__GetStatusResponse->PTZStatus->Position->Zoom->x);  //zoom value
	}
	soap_destroy(soap); 
	soap_end(soap);
}

void OnvifClientPTZ::absoluteMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
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

	if(SOAP_OK != proxyPTZ.AbsoluteMove(tptz__AbsoluteMove, tptz__AbsoluteMoveResponse)){
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

void OnvifClientPTZ::relativeMove(std::string profileToken, float pan, float panSpeed, float tilt, float tiltSpeed, float zoom, float zoomSpeed){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
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

	if(SOAP_OK != proxyPTZ.RelativeMove(tptz__RelativeMove, tptz__RelativeMoveResponse)){
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

void  OnvifClientPTZ::continuousMove(std::string profileToken, float panSpeed, float tiltSpeed, float zoomSpeed){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
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

	if(SOAP_OK != proxyPTZ.ContinuousMove(tptz__ContinuousMove, tptz__ContinuousMoveResponse)){
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

void  OnvifClientPTZ::stop(std::string profileToken, bool panTilt, bool zoom){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_tptz__Stop *tptz__Stop = soap_new__tptz__Stop(soap, -1);
	_tptz__StopResponse *tptz__StopResponse = soap_new__tptz__StopResponse(soap, -1);

	tptz__Stop->ProfileToken = profileToken;
	tptz__Stop->PanTilt = &panTilt;
	tptz__Stop->Zoom = &zoom;

	if(SOAP_OK != proxyPTZ.Stop(tptz__Stop, tptz__StopResponse)){
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

void  OnvifClientPTZ::setHomePosition(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_tptz__SetHomePosition *tptz__SetHomePosition = soap_new__tptz__SetHomePosition(soap, -1);
	_tptz__SetHomePositionResponse *tptz__SetHomePositionResponse = soap_new__tptz__SetHomePositionResponse(soap, -1);

	tptz__SetHomePosition->ProfileToken = profileToken;

	if(SOAP_OK != proxyPTZ.SetHomePosition(tptz__SetHomePosition, tptz__SetHomePositionResponse)){
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

void OnvifClientPTZ::goToHomePosition(std::string profileToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_tptz__GotoHomePosition *tptz__GotoHomePosition = soap_new__tptz__GotoHomePosition(soap, -1);
	_tptz__GotoHomePositionResponse *tptz__GotoHomePositionResponse = soap_new__tptz__GotoHomePositionResponse(soap, -1);

	tptz__GotoHomePosition->ProfileToken = profileToken;

	if(SOAP_OK != proxyPTZ.GotoHomePosition(tptz__GotoHomePosition, tptz__GotoHomePositionResponse)){
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

void  OnvifClientPTZ::getConfiguration(std::string configurationToken){
	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyPTZ.soap, NULL, _user.c_str(), _password.c_str())){
		std::string errorDetail;
		errorDetail += "ERROR:\nError Code:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultcode;
		errorDetail += "\nFault:";
		if(soap->fault->faultcode != NULL) errorDetail += soap->fault->faultstring;
		errorDetail + "\n";
		throw std::runtime_error(errorDetail);
	}

	_tptz__GetConfiguration *tptz__GetConfiguration = soap_new__tptz__GetConfiguration(soap,-1);
	_tptz__GetConfigurationResponse *tptz__GetConfigurationResponse = soap_new__tptz__GetConfigurationResponse(soap,-1);

	tptz__GetConfiguration->PTZConfigurationToken = configurationToken;



	if(SOAP_OK != proxyPTZ.GetConfiguration(tptz__GetConfiguration, tptz__GetConfigurationResponse)){
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

void OnvifClientPTZ::panLeft(std::string profileToken, int nDegrees){
	float pan = -nDegrees*0.0027777778;
	return relativeMove(profileToken, pan, 1, 0.0, 0.0, 0.0, 0.0);
}

void OnvifClientPTZ::panRight(std::string profileToken, int nDegrees){
	float pan = nDegrees*0.0027777778;
	return relativeMove(profileToken, pan, 1, 0.0, 0.0, 0.0, 0.0);
}

void OnvifClientPTZ::tiltDown(std::string profileToken, int nDegrees){
	float tilt = -nDegrees*0.0055555556;
	return relativeMove(profileToken, 0.0, 0.0, tilt, 1.0, 0.0, 0.0);
}

void OnvifClientPTZ::tiltUp(std::string profileToken, int nDegrees){
	float tilt = nDegrees*0.0055555556;
	return relativeMove(profileToken, 0.0, 0.0, tilt, 1.0, 0.0, 0.0);
}

void OnvifClientPTZ::zoomIn(std::string profileToken){
	return relativeMove(profileToken, 0.0, 0.0, 0.0, 0.0, 0.05, 1.0);
}

void OnvifClientPTZ::zoomOut(std::string profileToken){
	return relativeMove(profileToken, 0.0, 0.0, 0.0, 0.0, -0.05, 1.0);
}

std::vector<std::string> OnvifClientPTZ::getPTZConfigurationsTokens(){
	return _PTZConfigurationsTokens;
}

std::vector<float> OnvifClientPTZ::getPosition(){
	return _position;
}