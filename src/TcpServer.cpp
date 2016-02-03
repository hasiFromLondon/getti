

#include "TcpServer.h"

#include <iostream>
#include <thread>
#include <functional>

TcpServer::TcpServer()
    :m_worker(m_service),
      m_endpoint( boost::asio::ip::tcp::v4(), 2001),
      m_acceptor(m_service, m_endpoint)
{
    Start();
}

void TcpServer::IoServiceThread()
{
    try
    {
        m_service.run();
    }
    catch( std::exception& ex)
    {
        std::cerr << "Exception on " << __PRETTY_FUNCTION__ << ": " << ex.what() << std::endl;
    }
}

void TcpServer::Start()
{
    m_ioServiceThread = std::thread(&TcpServer::IoServiceThread, this);
    // TODO: wait
    StartAccept();
}

void TcpServer::Stop()
{
    m_service.stop();
}


void TcpServer::HandleAccept(socket_ptr sock, const boost::system::error_code & error)
 {
    if ( error)
    {
        std::cout << "Error\n";
        return;
    }

    StartReceive(NewClient(sock));
    StartAccept();
}

void TcpServer::StartReceive(std::shared_ptr<Client> client)
{
    client->m_socket->async_receive(boost::asio::buffer(client->m_readBuffer.data(), client->m_readBuffer.size()),
                                   std::bind(&TcpServer::HandleReceive, this, client, std::placeholders::_1, std::placeholders::_2));
}

void TcpServer::HandleReceive(std::shared_ptr<Client> client,
                              const boost::system::error_code& error,
                              std::size_t bytes_transferred)
{
    if (error)
    {
        Disconnect(client);
        return;
    }
    std::string data(client->m_readBuffer.data(), bytes_transferred);
    NewData(client, data);
    StartReceive(client);
}

void TcpServer::Disconnect(std::shared_ptr<Client> client)
{
    // TODO
}

void TcpServer::StartAccept()
{
    socket_ptr sock(new boost::asio::ip::tcp::socket(m_service));
    m_acceptor.async_accept(*sock, std::bind( &TcpServer::HandleAccept, this, sock, std::placeholders::_1) );
}

std::shared_ptr<Client> TcpServer::NewClient(socket_ptr socket)
{
    const auto& rep = socket->remote_endpoint();
    const auto& lep = socket->local_endpoint();
    std::string addr = lep.address().to_string() + ":" + std::to_string(lep.port()) + " - " +
                       rep.address().to_string() + ":" + std::to_string(rep.port());
    std::shared_ptr<Client> client(new Client(socket));
    m_clients.insert(std::pair<std::string,std::shared_ptr<Client>>(addr, client));
    return client;
}

void TcpServer::Send(std::shared_ptr<Client> client,
          const char* data,
          size_t len)
{
    client->m_socket->async_send(boost::asio::buffer(data, len),
                                   std::bind(&TcpServer::HandleSend, this, client, std::placeholders::_1, std::placeholders::_2));
}

void TcpServer::HandleSend(std::shared_ptr<Client> client,
                              const boost::system::error_code& error,
                              std::size_t bytes_transferred)
{
    if (error)
    {
        Disconnect(client);
        return;
    }

    WriteOk(client);
}
