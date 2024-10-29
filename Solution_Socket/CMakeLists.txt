project (Solution_Socket)

add_executable (Socket_Server "Server.cpp")
add_executable (Socket_Client "Client.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Socket_Server PROPERTY CXX_STANDARD 20)
  set_property(TARGET Socket_Client PROPERTY CXX_STANDARD 20)
endif()
