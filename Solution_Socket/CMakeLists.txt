project (Solution_Socket)

file(GLOB IMGUI imgui/*.cpp imgui/*.h)

include_directories(.)
include_directories(GLFW/*.h)
include_directories(GL/*.h)

link_directories(GL)
link_directories(GLFW)

add_executable (Socket_Server "Server.cpp" ${IMGUI})
add_executable (Socket_Client "Client.cpp" ${IMGUI})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Socket_Server PROPERTY CXX_STANDARD 20)
    target_link_libraries(Socket_Server "freeglut.lib" "glfw3.lib" "glfw3dll.lib" "glfw3_mt.lib")
  set_property(TARGET Socket_Client PROPERTY CXX_STANDARD 20)
    target_link_libraries(Socket_Client "freeglut.lib" "glfw3.lib" "glfw3dll.lib" "glfw3_mt.lib")
endif()
