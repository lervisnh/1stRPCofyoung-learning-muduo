#ifndef LOCALCONFIG_H
#define LOCALCONFIG_H

#include "base/Logger.h"
#include "submodules/tinyxml/tinyxml.h"
#include <string>
#include <map>

class LocalConfig
{
public:
	// 必须先通过SetConfigFile设置配置文件地址
	static bool SetConfigFile(const char *);
	static LocalConfig* GetInstance();

	std::string GetServerIp()const;
	unsigned short GetServerPort()const;
	Logger::LogLevel GetServerLogLevel()const;
	int GetServerWorkers()const;

private:
	LocalConfig();
	void ReadXml();
	LocalConfig(const LocalConfig&) = delete;
	LocalConfig& operator=(const LocalConfig&) = delete;

	TiXmlDocument lActionXML;
	std::string _server_ip;
	unsigned short _server_port;
	Logger::LogLevel _server_log_level;
	int _server_workers_num;

	static LocalConfig * _local_config;
	static const char * _config_file;

	static std::map<std::string, Logger::LogLevel> _LogLevelHash;
};

#endif // LOCALCONFIG_H
