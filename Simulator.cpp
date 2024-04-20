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
        // probe all gates should only be executed when 
        // json output is on 
        simulation->ProbeAllGates();
    }
        
    simulation->Run();
    if (json)
        simulation->UndoProbeAllGates();
    if (argc >= 3 && "json" == std::string(argv[2]))
    {
        boost::property_tree::ptree simResult = simulation->GetJson();
        std::ofstream output("circuit.jsonp", std::ios::out);
        output << "onJsonp(";
        boost::property_tree::write_json(output, simResult);
        output << ");\n";
    }
    simulation->PrintProbes(std::cout);
}
