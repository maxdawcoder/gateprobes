cmake_minimum_required(VERSION 3.17.0)
project(Simulator)
find_package(Boost REQUIRED COMPONENTS regex)
add_executable(Simulator  
    Circuit.cpp
    Gate.cpp
    Simulation.cpp
    Simulator.cpp
    TruthTable.cpp
)
set_property(TARGET Simulator PROPERTY CXX_STANDARD 17)
target_include_directories(Simulator PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(Simulator LINK_PUBLIC ${Boost_LIBRARIES} )