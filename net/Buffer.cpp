#include "Buffer.h"
#include "SocketOps.h"
// #include "Endian.h"
#include <string.h>
/*#include <sys/uio.h>
#include <iostream>*/

const ssize_t kExtraBufferSize = 20480;

const size_t Buffer::kCheapPrepend;
const size_t Buffer::kInitialSize;

ssize_t Buffer::readFd(int fd, int* savedErrno)
{
  // saved an ioctl()/FIONREAD call to tell how much to read
  char extrabuf[kExtraBufferSize];
  struct iovec vec[2];
  const size_t writable = writableBytes();
  vec[0].iov_base = begin() + m_writerIndex;
  vec[0].iov_len = writable;
  vec[1].iov_base = extrabuf;
  vec[1].iov_len = sizeof(extrabuf);
  // when there is enough space in this buffer, don't read into extrabuf.
  // when extrabuf is used, we read 128k-1 bytes at most.
  const int iovcnt = (writable < sizeof(extrabuf)) ? 2 : 1;
  const ssize_t n = sockets::readv(fd, vec, iovcnt);
    //printf("Buffer::readFd() : len writable %d len %d capcity %d\n", writable, n - writable, internalCapacity());
  if (n < 0)
  {
    *savedErrno = errno;
  }
  else if (static_cast<size_t>(n) <= writable)
  {
    m_writerIndex += n;
  }
  else
  {
    m_writerIndex = m_buffer.size();
    append(extrabuf, n - writable);
  }
  // if (n == writable + sizeof extrabuf)
  // {
  //   goto line_30;
  // }
  return n;
};


int32_t Buffer::peekInt32() const
{
  assert(readableBytes() >= sizeof(int32_t));
  int32_t be32 = 0;
  ::memcpy(&be32, peek(), sizeof(be32));
  return sockets::networkToHost32(be32);
};
