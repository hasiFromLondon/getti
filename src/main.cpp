
#include "GetServer.h"

#include <chrono>
#include <thread>


int main()
{
    GetServer s;
    s.Start();

    std::this_thread::sleep_for(std::chrono::seconds(100));

}
