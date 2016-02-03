#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

#include <boost/asio.hpp>
#include <fstream>

struct Client
{
    enum class State {Open, Close};
    Client(socket_ptr socket)
        :m_socket(socket),
         m_readBuffer(MAX_REQUEST_LEN),
         m_writeBuffer(WRITE_BUFFER_LEN),
         m_state(State::Close){};

    socket_ptr  m_socket;
    std::vector<char> m_readBuffer;
    std::ifstream m_fileStream;
    std::vector<char> m_writeBuffer;
    State m_state;

};
#endif // CLIENT_H
