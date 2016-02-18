#ifndef ONVIFCLIENTDEVICE_HPP
#define ONVIFCLIENTDEVICE_HPP

#include <iostream>
#include "stdio.h"
#include "gsoap/wsseapi.h"
#include <openssl/rsa.h>
#include <stdexcept>
#include <vector>
 
#include "onvif/soapDeviceBindingProxy.h"


class OnvifClientDevice{
public:
	OnvifClientDevice();
	OnvifClientDevice(std::string url, std::string user, std::string password);
	~OnvifClientDevice();

public:
	void getUsers();
	std::vector<std::string> getUsernames();


public:
	bool _hasMedia;
	bool _hasPTZ;

protected:
	std::string _strUrl;
	std::string _user;
	std::string _password;

	std::vector<std::string> _username;

	struct soap *soap;

	DeviceBindingProxy proxyDevice;
};

#endif








