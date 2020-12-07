#ifndef LOCALCONFIG_H
#define LOCALCONFIG_H

#include "submodules/tinyxml/tinyxml.h"
#include <string>

class LocalConfig
{
public:
	// 必须先通过SetConfigFile设置配置文件地址
	static bool SetConfigFile(const char *);
	static LocalConfig* GetInstance();

	std::string GetServerIp()const;
	unsigned short GetServerPort()const;

private:
	LocalConfig();
	void ReadXml();
	LocalConfig(const LocalConfig&) = delete;
	LocalConfig& operator=(const LocalConfig&) = delete;

	TiXmlDocument lActionXML;
	std::string _server_ip;
	unsigned short _server_port; 

	static LocalConfig * _local_config;
	static const char * _config_file;
};

#endif // LOCALCONFIG_H
