#pragma once
#include "Enums.hpp"
#include "IPropertyChangedCallback.hpp"
#include "pal/SystemInformationImpl.hpp"
#include "pal/NetworkInformationImpl.hpp"
#include "pal/DeviceInformationImpl.hpp"

#include <vector>
#include <list>
#include <map>
#include <string>


namespace ARIASDK_NS_BEGIN {

static const std::string NetworkCostNames[] = {
    "Unknown",
    "Unmetered",
    "Metered",
    "Roaming",
    // Reserved network costs
    "Reserved",
    "Reserved",
    "Reserved"
};

static const std::string PowerSourceNames[] = {
    "Unknown",
    "Battery",
    "Charging",
    // Reserved power states
    "Reserved",
    "Reserved",
    "Reserved"
};

class DeviceStateHandler 
    : public PAL::IPropertyChangedCallback
{
public:
	DeviceStateHandler();
    virtual ~DeviceStateHandler();

    void Start();
    void Stop();

    // Callback functions
    // IPropertyChangedCallback::OnChanged from platform on any connectivity, power, device system changes
    virtual void OnChanged(std::string const& propertyName, std::string const& propertyValue) override;

private:

    void _HandleNetworkCallback();
    void _HandlePowerCallback();
    bool _UpdateDeviceCondition();

	static unsigned int _MapNetworkTypeToDefaultCostUInt(NetworkType networkType);
    static unsigned int _MapNetworkCostToUInt(NetworkCost networkCost, NetworkType networkType);
    static unsigned int _MapPowerSourceToUInt(PowerSource powerSource);

private:

    std::mutex                      m_lock_sendEvent;
		
	NetworkType                m_networkType;
    NetworkCost                m_networkCost;
    PowerSource                m_powerSource;
    
	// Platform network, power, device info changes
    PAL::INetworkInformation       *m_networkInformation;
    int                             m_networkInformationToken;

    PAL::IDeviceInformation        *m_deviceInformation;
    int                             m_deviceInformationToken;

};

} ARIASDK_NS_END
