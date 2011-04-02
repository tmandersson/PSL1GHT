#pragma once

#include <psl1ght/types.h>
#include <sys/types.h>

#define NET_CTL_ETHER_ADDR_LEN          6
#define NET_CTL_BSSID_LEN               6
#define NET_CTL_SSID_LEN                32
#define NET_CTL_WLAN_SECURITY_KEY_LEN   65
#define NET_CTL_AUTH_NAME_LEN           128
#define NET_CTL_AUTH_KEY_LEN            128
#define NET_CTL_DHCP_HOSTNAME_LEN       255
#define NET_CTL_HOSTNAME_LEN            256
#define NET_CTL_IPV4_ADDR_STR_LEN       16

struct net_ctl_ether_addr {
	u8 data[NET_CTL_ETHER_ADDR_LEN];
	u8 padding[2];
};

struct net_ctl_SSID {
	u8 data[NET_CTL_SSID_LEN];
	u8 term;
	u8 padding[3];
};


union net_ctl_info {
	u32 device;
	struct net_ctl_ether_addr ether_addr;
	u32 mtu;
	u32 link;
	u32 link_type;
	struct net_ctl_ether_addr bssid;
	struct net_ctl_SSID ssid;
	u32 wlan_security;
	u32 auth_8021x_type;
	char auth_8021x_auth_name[NET_CTL_AUTH_NAME_LEN];
	u8 rssi;
	u8 channel;
	u32 ip_config;
	char dhcp_hostname[NET_CTL_HOSTNAME_LEN];
	char pppoe_auth_name[NET_CTL_AUTH_NAME_LEN];
	char ip_address[NET_CTL_IPV4_ADDR_STR_LEN];
	char netmask[NET_CTL_IPV4_ADDR_STR_LEN];
	char default_route[NET_CTL_IPV4_ADDR_STR_LEN];
	char primary_dns[NET_CTL_IPV4_ADDR_STR_LEN];
	char secondary_dns[NET_CTL_IPV4_ADDR_STR_LEN];
	u32 http_proxy_config;
	char http_proxy_server[NET_CTL_HOSTNAME_LEN];
	u16 http_proxy_port;
	u32 upnp_config;
};


#define NET_CTL_INFO_DEVICE            1
#define NET_CTL_INFO_ETHER_ADDR        2
#define NET_CTL_INFO_MTU               3
#define NET_CTL_INFO_LINK              4
#define NET_CTL_INFO_LINK_TYPE         5
#define NET_CTL_INFO_BSSID             6
#define NET_CTL_INFO_SSID              7
#define NET_CTL_INFO_WLAN_SECURITY     8
#define NET_CTL_INFO_8021X_TYPE        9
#define NET_CTL_INFO_8021X_AUTH_NAME   10
#define NET_CTL_INFO_RSSI              11
#define NET_CTL_INFO_CHANNEL           12
#define NET_CTL_INFO_IP_CONFIG         13
#define NET_CTL_INFO_DHCP_HOSTNAME     14
#define NET_CTL_INFO_PPPOE_AUTH_NAME   15
#define NET_CTL_INFO_IP_ADDRESS        16
#define NET_CTL_INFO_NETMASK           17
#define NET_CTL_INFO_DEFAULT_ROUTE     18
#define NET_CTL_INFO_PRIMARY_DNS       19
#define NET_CTL_INFO_SECONDARY_DNS     20
#define NET_CTL_INFO_HTTP_PROXY_CONFIG 21
#define NET_CTL_INFO_HTTP_PROXY_SERVER 22
#define NET_CTL_INFO_HTTP_PROXY_PORT   23
#define NET_CTL_INFO_UPNP_CONFIG       24



EXTERN_BEGIN

void netCtlInit(void);
int netCtlGetInfo(int code, union net_ctl_info *info);

EXTERN_END
