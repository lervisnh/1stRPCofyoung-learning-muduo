
#include <iostream>
#include <string.h>

#include "net/Buffer.h"

int main()
{
  Buffer buffer;

  std::cout << buffer.writableBytes() << std::endl;
  strcpy(buffer.beginWrite(), "123456789");
  std::cout << buffer.writableBytes() << std::endl;
  buffer.hasWritten(9);
  std::cout << buffer.writableBytes() << std::endl;
  buffer.unwrite(4);
  std::cout << buffer.writableBytes() << std::endl;
  strcpy(buffer.beginWrite(), "123456789");
  std::cout << buffer.writableBytes() << std::endl;
  std::cout << buffer.peek() << std::endl;

  buffer.retrieveAll();
  std::cout << buffer.writableBytes() << std::endl;

  buffer.append("123456789", 9);
  std::cout << buffer.writableBytes() << std::endl;
  std::cout << buffer.peek() << std::endl;

  while(1)
  {
    int err = 0;
    buffer.readFd(0, &err);
    std::cout << "--   --   --   --   --   --   --   --   --   --" << std::endl;
    std::cout << "buffer.writableBytes() = " << buffer.writableBytes() << std::endl;
    std::cout << "buffer.peek() = " << buffer.peek() << std::endl;
    std::cout << "buffer.internalCapacity() = " << buffer.internalCapacity() << std::endl;
  }
}