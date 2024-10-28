project (Solution4)

add_executable (OS_Class_Solution4 "main.cpp" "Solution.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OS_Class_Solution4 PROPERTY CXX_STANDARD 20)
endif()
