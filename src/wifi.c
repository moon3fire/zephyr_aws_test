#include <zephyr/logging/log.h>

#define SSID "FastNet 6/5"
#define PSK "karen488030"

#include <zephyr/kernel.h>

#include <zephyr/net/net_if.h>
#include <zephyr/net/net_core.h>
#include <zephyr/net/net_context.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/net/wifi.h>
#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/net/wifi_utils.h>

void connect_to_wifi(void)
{
	struct net_if *iface = net_if_get_default();
	struct wifi_connect_req_params wifi_params = {};

    wifi_params.ssid = SSID;
    wifi_params.psk = PSK;
    wifi_params.ssid_length = strlen(SSID);
    wifi_params.psk_length = strlen(PSK);
    wifi_params.channel = WIFI_CHANNEL_ANY;
    wifi_params.security = WIFI_SECURITY_TYPE_PSK;
    wifi_params.band = WIFI_FREQ_BAND_2_4_GHZ; 
    wifi_params.mfp = WIFI_MFP_OPTIONAL;

	printk("Connecting to SSID: %s\n", wifi_params.ssid);

    if (net_mgmt(NET_REQUEST_WIFI_CONNECT, iface, &wifi_params, sizeof(struct wifi_connect_req_params)))
    {
        printk("WiFi Connection Request Failed\n");
    } else {
		printk("WiFi Connection Request Successful\n");
	}
}

void print_wifi_status(void) 
{
	struct net_if *iface = net_if_get_default();
	enum net_l2_flags flags = net_if_l2(iface)->get_flags(iface);
	bool is_connected = (flags & NET_EVENT_WIFI_CONNECT_RESULT);
	printk("WiFi is %s\n", is_connected ? "connected" : "disconnected");
}
