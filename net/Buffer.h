#ifndef NET_BUFFER_H
#define NET_BUFFER_H

#include "Endian.h"

#include <algorithm>
#include <vector>
#include <string>

#include <assert.h>
// #include <string.h>
//#include <unistd.h>  // ssize_t

/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +-------------------+------------------+------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
class Buffer
{
public:
  static const size_t kCheapPrepend = 8;
  static const size_t kInitialSize = 4096;

	explicit Buffer(size_t initialSize = kInitialSize)
	: m_buffer(kCheapPrepend + initialSize),
	  m_readerIndex(kCheapPrepend),
	  m_writerIndex(kCheapPrepend)
	  {
	    assert(readableBytes() == 0);
      assert(writableBytes() == initialSize);
      assert(prependableBytes() == kCheapPrepend);
	  }

  size_t readableBytes() const
  { return m_writerIndex - m_readerIndex; }

  size_t writableBytes() const
  { return m_buffer.size() - m_writerIndex; }

  size_t prependableBytes() const //前面预留出来的字节数，(s-(s-rI));
  { return m_readerIndex; }

  const char* peek() const
  { return begin() + m_readerIndex; }

  const char* beginWrite() const
  { return begin() + m_writerIndex; }

  char* beginWrite()
  { return begin() + m_writerIndex; }

  void hasWritten(size_t len)
  {
    assert(len <= writableBytes());
    m_writerIndex += len;
  }

  void unwrite(size_t len)
  {
    assert(len <= readableBytes());
    m_writerIndex -= len;
  }
  
  // retrieve returns void, to prevent
  // string str(retrieve(readableBytes()), readableBytes());
  // the evaluation of two functions are unspecified
  void retrieve(size_t len)
  {
    assert(len <= readableBytes());
    if (len < readableBytes())
    {
      m_readerIndex += len;
    }
    else
    {
      retrieveAll();
    }
  }

  void retrieveAll()
  {
  	m_readerIndex = kCheapPrepend;
  	m_writerIndex = kCheapPrepend;
  }

  std::string retrieveAllAsString()
  {
    return retrieveAsString(readableBytes());
  }

  std::string retrieveAsString(size_t len)
  {
    assert(len <= readableBytes());
    std::string result(peek(), len);
    retrieve(len);
    return result;
  }

  void makeSpace(int len)
  {
    if(writableBytes() + prependableBytes() < len + kCheapPrepend)
    {
      m_buffer.resize(m_writerIndex + len);
    }
    else
    {
      // move readable data to the front, make space inside buffer
      assert(kCheapPrepend < m_readerIndex);
      size_t readable = readableBytes();
      std::copy(begin() + m_readerIndex, begin() + m_writerIndex, begin() + kCheapPrepend);
      m_readerIndex = kCheapPrepend;
      m_writerIndex = m_readerIndex + readable;
      assert(readable == readableBytes());
    }
  }

  void append(const char* data/*restrict data*/, size_t len)
  {
    if (writableBytes() < len)
    {
      makeSpace(len);
    }
    assert(writableBytes() >= len);
    std::copy(data, data+len, beginWrite());
    hasWritten(len);
  }

  void prepend(const void* /*restrict*/ data, size_t len)
  {
    assert(len <= prependableBytes());
    m_readerIndex -= len;
    const char* d = static_cast<const char*>(data);
    std::copy(d, d+len, begin()+m_readerIndex);
  }

  ssize_t readFd(int fd, int* savedErrno);

  size_t internalCapacity() const
  {
    return m_buffer.capacity();
  }

  ///
  /// Peek int32_t from network endian
  ///
  /// Require: buf->readableBytes() >= sizeof(int32_t)
  int32_t peekInt32() const;

private:
  char* begin()
  {return &*m_buffer.begin(); }

  const char* begin() const
  {return &*m_buffer.begin(); }

private:
	std::vector<char> m_buffer;
	size_t m_readerIndex;
	size_t m_writerIndex;
};

#endif  // NET_BUFFER_H
