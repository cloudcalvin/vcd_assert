set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(unit_verilog ../unit_main.cpp)
target_link_libraries(unit_verilog libverilog Catch2::Catch2 fmt::fmt range-v3)
target_compile_definitions(unit_verilog PRIVATE -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}" )
# add_definitions(-DCMAKE_BUILD_DIR="${DIR}")

target_add_warnings(unit_verilog)
add_test(NAME unit_verilog COMMAND unit_verilog)

if (${RUN_ALL_TESTS})
  add_test(NAME unit_verilog_hidden COMMAND unit_verilog "[.]")
endif()

add_subdirectory(ieee1364_2001)



