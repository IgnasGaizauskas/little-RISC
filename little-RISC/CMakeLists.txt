# CMakeList.txt : CMake project for little-RISC, include source and define
# project specific logic here.
#

add_compile_definitions(CPU_REGISTER_WIDTH=${CPU_REGISTER_WIDTH})

# Add source to this project's executable.
add_executable (little-RISC "little-RISC.cpp" "little-RISC.h"  "instructions.h" "core.cpp" "core.h" "memory.h" "memory.cpp" "config.h" "emulator.h" "emulator.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET little-RISC PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
