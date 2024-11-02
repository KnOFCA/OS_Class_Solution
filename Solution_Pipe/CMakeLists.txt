project (Solution_Pipe)

add_executable (Solution_PipeF "Pipe.cpp")
add_executable (Solution_PipeC "Child.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Solution_PipeF PROPERTY CXX_STANDARD 20)
  set_property(TARGET Solution_PipeC PROPERTY CXX_STANDARD 20)
endif()
