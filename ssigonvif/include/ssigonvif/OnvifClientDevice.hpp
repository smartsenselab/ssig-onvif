#ifndef ONVIFCLIENTDEVICE_HPP
#define ONVIFCLIENTDEVICE_HPP

#include <iostream>
#include "stdio.h"
#include "gsoap/wsseapi.h"
#include <openssl/rsa.h>
 
#include "onvif/soapDeviceBindingProxy.h"


class OnvifClientDevice{
public:
	OnvifClientDevice();
	OnvifClientDevice(std::string url, std::string user, std::string password, bool showCapabilities);
	~OnvifClientDevice();

public:
	bool _hasMedia;
	bool _hasPTZ;

protected:
	std::string _strUrl;
	std::string _user;
	std::string _password;

	struct soap *soap;

	DeviceBindingProxy proxyDevice;
};

#endif








