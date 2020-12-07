
#include "rpc/LocalConfig.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
      std::cout << "No XML File ! " << std::endl;
      return 0;
    }

    LocalConfig::SetConfigFile(argv[1]);
    std::cout << "IP   = " << LocalConfig::GetInstance()->GetServerIp() << std::endl;
    std::cout << "Port = " << LocalConfig::GetInstance()->GetServerPort() << std::endl;
    
    return 0;
}
