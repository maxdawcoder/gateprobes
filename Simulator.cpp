// Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Simulation.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Simulator.exe <simfile> [json]" << std::endl;
        std::cout << "simulation output is in circuit.jsonp" << std::endl;
        exit(0);
    }
    bool json = (argc >= 3 && "json" == std::string(argv[2]));
    std::ifstream input(argv[1], std::ios::in);
    auto simulation = Simulation::FromFile(input);
    
    if (json)
    {
        simulation->LayoutFromFile(input);
    }
    simulation->ProbeAllGates(); // Fix probe gates on every run
        
    simulation->Run();
    if (json)
        simulation->UndoProbeAllGates();
    if (argc >= 3 && "json" == std::string(argv[2]))
    {
        boost::property_tree::ptree simResult = simulation->GetJson();
        std::ofstream output("circuit.jsonp", std::ios::out);
        std::stringstream ss;
        output << "onJsonp(";
        boost::property_tree::write_json(ss, simResult); // FIX reduce << operation on file stream
        output << ss.str();
        output << ");\n";
    }
    simulation->PrintProbes(std::cout);
}
