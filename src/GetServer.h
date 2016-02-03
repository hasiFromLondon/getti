#ifndef GETSERVER_H
#define GETSERVER_H

#include "TcpServer.h"
#include "Client.h"


class GetServer: public TcpServer
{

public:
    GetServer(){};
    void Start();

private:
     void NewData(std::shared_ptr<Client>, std::string&);
     void WriteOk(std::shared_ptr<Client>);

private:

};
#endif // GETSERVER_H
