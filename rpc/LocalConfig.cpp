#include "LocalConfig.h"
#include "base/Logger.h"
#include <iostream> // TODO : remove

LocalConfig * LocalConfig::_local_config = NULL;
const char * LocalConfig::_config_file = NULL;

bool LocalConfig::SetConfigFile(const char* f){
	if (_config_file == NULL)
	{
		_config_file = f;
		return true;
	}
	return false;
}

LocalConfig* LocalConfig::GetInstance()
{
	if (_local_config == NULL)
	{
		_local_config = new LocalConfig();
	}
	return _local_config;
}

LocalConfig::LocalConfig()
{
	ReadXml();
}

void LocalConfig::ReadXml()
{
	lActionXML.LoadFile(_config_file);
	if (lActionXML.Error())
	{
		std::cout << "read failed !" << std::endl; // TODO : remove
		// LOG_ERROR << "Load XML config file failed !";
		exit(EXIT_FAILURE);
	}
	else
	{
		const TiXmlNode *node = lActionXML.RootElement()->IterateChildren("LocalConfig", NULL);
		const TiXmlNode *tmp_node = NULL;
		if (node != NULL)
		{
			tmp_node = node->IterateChildren("ip", NULL);
			_server_ip = tmp_node->ToElement()->GetText();
			tmp_node = node->IterateChildren("port", NULL);
			_server_port = atoi(tmp_node->ToElement()->GetText());
		}
	}
}

std::string LocalConfig::GetServerIp() const
{
	return _server_ip;
}
unsigned short LocalConfig::GetServerPort() const
{
	return _server_port;
}
