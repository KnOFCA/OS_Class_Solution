cmake_minimum_required (VERSION 3.8)

#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

project ("OS_Class_Solution")

add_subdirectory ("Solution1")
add_subdirectory ("Solution2")
add_subdirectory ("Solution3")
add_subdirectory ("Solution4")
add_subdirectory ("Solution_Socket")
add_subdirectory ("Solution_Pipe")
