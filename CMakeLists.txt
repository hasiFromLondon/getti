cmake_minimum_required (VERSION 2.6)
 
set (PROJECT 
	getti)
 
set (SOURCES 
        src/main.cpp
        src/TcpServer.cpp
        src/Client.cpp
        src/GetServer.cpp)
 
set (BOOST_COMPONENTS 
	thread
	filesystem
        system
        )
 
set (Boost_USE_STATIC_LIBS ON)
 
set (Boost_USE_MULTITHREADED ON)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project (${PROJECT})
 
find_package (Threads)
 
find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
 
add_executable (${PROJECT} ${SOURCES})
 
target_link_libraries (${PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
