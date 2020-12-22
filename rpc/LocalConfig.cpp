#include "LocalConfig.h"
// #include "base/Logger.h"
#include <iostream> // TODO : remove

LocalConfig * LocalConfig::_local_config = NULL;
const char * LocalConfig::_config_file = NULL;
std::map<std::string, Logger::LogLevel> LocalConfig::_LogLevelHash = {
	{"TRACE", Logger::TRACE}, {"DEBUG", Logger::DEBUG}, {"INFO", Logger::INFO}, 
	{"WARN", Logger::WARN}, {"ERROR", Logger::ERROR}, {"FATAL", Logger::FATAL}};

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
		// std::cout << "read failed !" << std::endl; // TODO : remove
		LOG_ERROR << "Load XML config file failed !";
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

			tmp_node = node->IterateChildren("loglevel", NULL);
			if (tmp_node) {
				std::string log_level = tmp_node->ToElement()->GetText();
				std::map<std::string, Logger::LogLevel>::const_iterator iter = _LogLevelHash.find(log_level);
				_server_log_level = (iter==_LogLevelHash.end()? Logger::INFO : iter->second);
			} else _server_log_level = Logger::INFO;

			tmp_node = node->IterateChildren("workers", NULL);
			int xml_workers_num = 1;
			if (tmp_node) {
				xml_workers_num = atoi(tmp_node->ToElement()->GetText());
			}
			_server_workers_num = xml_workers_num>1? xml_workers_num : 1;
			
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

Logger::LogLevel LocalConfig::GetServerLogLevel() const
{
	return _server_log_level;
}

int LocalConfig::GetServerWorkers() const
{
	return _server_workers_num;
}