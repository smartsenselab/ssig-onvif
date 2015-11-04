#include "ssigonvif/OnvifClientDevice.hpp"
#include "DeviceBinding.nsmap"


OnvifClientDevice::OnvifClientDevice(){
}

OnvifClientDevice::OnvifClientDevice(std::string url, std::string user, std::string password, bool showCapabilities){
	_strUrl = "http://" + url + "/onvif/services";
	_user = user;
	_password = password;

	_hasMedia = false;
	_hasPTZ = false;

	proxyDevice.soap_endpoint = _strUrl.c_str();
	
	soap_register_plugin(proxyDevice.soap, soap_wsse);
	soap = soap_new();

	if (SOAP_OK != soap_wsse_add_UsernameTokenDigest(proxyDevice.soap, NULL, user.c_str(), password.c_str()))
	{
	}

	_tds__GetCapabilities *tds__GetCapabilities = soap_new__tds__GetCapabilities(soap, -1);
	tds__GetCapabilities->Category.push_back(tt__CapabilityCategory__All);
	_tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse = soap_new__tds__GetCapabilitiesResponse(soap, -1);

	if (SOAP_OK == proxyDevice.GetCapabilities(tds__GetCapabilities, tds__GetCapabilitiesResponse))
	{
		if(showCapabilities){
			if (tds__GetCapabilitiesResponse->Capabilities->Analytics != NULL)
			{/*
				processEventLog(__FILE__, __LINE__, stdout, "-------------------Analytics-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "XAddr:%s", tds__GetCapabilitiesResponse->Capabilities->Analytics->XAddr.c_str());
				processEventLog(__FILE__, __LINE__, stdout, "RuleSupport:%s", (tds__GetCapabilitiesResponse->Capabilities->Analytics->RuleSupport) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "AnalyticsModuleSupport:%s", (tds__GetCapabilitiesResponse->Capabilities->Analytics->AnalyticsModuleSupport) ? "Y" : "N");
			*/
			}

			if (tds__GetCapabilitiesResponse->Capabilities->Device != NULL)
			{
				/*
				processEventLog(__FILE__, __LINE__, stdout, "-------------------Device-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "XAddr:%s", tds__GetCapabilitiesResponse->Capabilities->Device->XAddr.c_str());

				processEventLog(__FILE__, __LINE__, stdout, "-------------------Network-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "IPFilter:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "ZeroConfiguration:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "IPVersion6:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "DynDNS:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS) ? "Y" : "N");

				processEventLog(__FILE__, __LINE__, stdout, "-------------------System-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "DiscoveryResolve:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryResolve) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "DiscoveryBye:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryBye) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "RemoteDiscovery:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->System->RemoteDiscovery) ? "Y" : "N");
				*/
				int iSize = tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions.size();

				if (iSize > 0)
				{/*
					processEventLog(__FILE__, __LINE__, stdout, "SupportedVersions:");

					for (int i = 0; i < iSize; i++)
					{
						processEventLog(__FILE__, __LINE__, stdout, "%d.%d ", tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions[i]->Major,
																			  tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions[i]->Minor);
					}

					processEventLog(__FILE__, __LINE__, stdout, "");
					*/
				}
				/*
				processEventLog(__FILE__, __LINE__, stdout, "SystemBackup:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemBackup) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "FirmwareUpgrade:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->System->FirmwareUpgrade) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "SystemLogging:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemLogging) ? "Y" : "N");

				processEventLog(__FILE__, __LINE__, stdout, "-------------------IO-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "InputConnectors:%d", tds__GetCapabilitiesResponse->Capabilities->Device->IO->InputConnectors);
				processEventLog(__FILE__, __LINE__, stdout, "RelayOutputs:%d", tds__GetCapabilitiesResponse->Capabilities->Device->IO->RelayOutputs);

				processEventLog(__FILE__, __LINE__, stdout, "-------------------Security-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "TLS1.1:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e1) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "TLS1.2:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e2) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "OnboardKeyGeneration:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->OnboardKeyGeneration) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "AccessPolicyConfig:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->AccessPolicyConfig) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "X.509Token:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->X_x002e509Token) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "SAMLToken:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->SAMLToken) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "KerberosToken:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->KerberosToken) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "RELToken:%s", (tds__GetCapabilitiesResponse->Capabilities->Device->Security->RELToken) ? "Y" : "N");
				*/

			}


			if (tds__GetCapabilitiesResponse->Capabilities->Imaging != NULL)
			{
				//processEventLog(__FILE__, __LINE__, stdout, "-------------------Imaging-------------------");
				//processEventLog(__FILE__, __LINE__, stdout, "XAddr:%s", tds__GetCapabilitiesResponse->Capabilities->Imaging->XAddr.c_str());
			}

		}

		if (tds__GetCapabilitiesResponse->Capabilities->Media != NULL){
			_hasMedia = true;

			if(showCapabilities){
				/*
				processEventLog(__FILE__, __LINE__, stdout, "-------------------Media-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "XAddr:%s", tds__GetCapabilitiesResponse->Capabilities->Media->XAddr.c_str());

				processEventLog(__FILE__, __LINE__, stdout, "-------------------streaming-------------------");
				processEventLog(__FILE__, __LINE__, stdout, "RTPMulticast:%s", (tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "RTP_TCP:%s", (tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP) ? "Y" : "N");
				processEventLog(__FILE__, __LINE__, stdout, "RTP_RTSP_TCP:%s", (tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP) ? "Y" : "N");
			`	*/
			}
		}

		if (tds__GetCapabilitiesResponse->Capabilities->PTZ != NULL){
			_hasPTZ = true;
			if(showCapabilities){
				//processEventLog(__FILE__, __LINE__, stdout, "-------------------PTZ-------------------");
				//processEventLog(__FILE__, __LINE__, stdout, "XAddr:%s", tds__GetCapabilitiesResponse->Capabilities->PTZ->XAddr.c_str());
			}
		}
	}
	else
	{
		//PrintErr(proxyDevice.soap);
	}
	
	soap_destroy(soap); 
	soap_end(soap);
}

OnvifClientDevice::~OnvifClientDevice(){
}

