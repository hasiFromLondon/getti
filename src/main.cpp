
#include "GetServer.h"

#include <chrono>
#include <thread>

struct ICallback

{

virtual void BinaryPacket(const char* data, unsigned int size) = 0;

virtual void TextPacket(const char* data, unsigned int size) = 0;

};


int main()
{
    GetServer s;
    s.Start();

    std::this_thread::sleep_for(std::chrono::seconds(100));

}
