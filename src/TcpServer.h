#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "common.h"
#include "Client.h"

#include <boost/asio.hpp>
#include <thread>
#include <unordered_map>

class TcpServer
{

    public:
        TcpServer();
        void Stop();
        void Send(std::shared_ptr<Client> client,
                  const char* data,
                  size_t len);

    private:
        void IoServiceThread();
        void HandleAccept(socket_ptr sock,
                          const boost::system::error_code & err);
        void StartAccept();
        void StartReceive(std::shared_ptr<Client> client);
        void HandleReceive(std::shared_ptr<Client> client,
                           const boost::system::error_code& error,
                           std::size_t bytes_transferred);
        void Disconnect(std::shared_ptr<Client> client);
        void Start();
        void HandleSend(std::shared_ptr<Client> client,
                        const boost::system::error_code& error,
                        std::size_t bytes_transferred);
        std::shared_ptr<Client> NewClient(socket_ptr);

    protected:
        virtual void NewData(std::shared_ptr<Client>, std::string&) = 0;
        virtual void WriteOk(std::shared_ptr<Client>) = 0;

    private:
        boost::asio::io_service m_service;
        boost::asio::io_service::work m_worker;
        std::thread             m_ioServiceThread;
        boost::asio::ip::tcp::endpoint m_endpoint;
        boost::asio::ip::tcp::acceptor m_acceptor;
        socket_ptr m_socket;
        std::unordered_map<std::string, std::shared_ptr<Client>>   m_clients;
};

#endif // TCPSERVER_H
