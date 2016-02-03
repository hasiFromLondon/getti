
#include "GetServer.h"
#include <iostream>

#include <boost/filesystem.hpp>

void GetServer::Start()
{

}

void GetServer::NewData(std::shared_ptr<Client> client, std::string& data)
{
    bool error = true;
    do
    {
        auto rn = data.find('\r');
        if ( rn != data.npos )
            data = data.substr(0, rn);
        auto space = data.find(' ');
        if (space == data.npos)
            break;
        auto command = data.substr(0, space);
        auto file = data.substr(space + 1);
        if (command != "GET")
            break;
        boost::filesystem::path p = boost::filesystem::current_path();
        p += + "/";
        p += file;
        boost::system::error_code ec;
        if (!boost::filesystem::exists(p) )
            break;
        client->m_fileStream.open(p.string(), std::ifstream::in|std::ifstream::binary);
        if (!client->m_fileStream.is_open())
            break;
        client->m_state = Client::State::Open;
        WriteOk(client);
    } while(0);
    if (error)
        Send(client, ERROR_STR, sizeof(ERROR_STR));
}

void GetServer::WriteOk(std::shared_ptr<Client> client)
{
    size_t len;
    if (client->m_state == Client::State::Close)
        return;
    client->m_fileStream.read(client->m_writeBuffer.data(), WRITE_BUFFER_LEN);
    if (client->m_fileStream)
    {
        len = WRITE_BUFFER_LEN;
    }
    else
    {
        len = client->m_fileStream.gcount();
        client->m_state = Client::State::Close;
        client->m_fileStream.close();
    }
    Send(client, client->m_writeBuffer.data(), len);
}
