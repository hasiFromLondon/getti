#ifndef COMMON_H
#define COMMON_H

#include <boost/asio.hpp>

#define MAX_REQUEST_LEN     1024
#define WRITE_BUFFER_LEN    1024
#define ERROR_STR           "501 (not implemented)"
typedef std::shared_ptr <boost::asio::ip::tcp::socket> socket_ptr;

#endif // COMMON_H
