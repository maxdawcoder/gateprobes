#pragma once
#include <string>
#include <map>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "TruthTable.h"
#include "GateType.h"
#include "Gate.h"

class Circuit
{
public:
	void AddTruthTable(std::string type, std::vector<int> outputs);
	void AddGateType(std::string name, std::string truthTableName, int delay);
	void AddGate(std::string name, std::string typeName, std::vector<std::string> inputNames);
	void AddProbe(std::string gateName);
	Gate* GetGate(std::string gateName) { return &(m_gates[gateName]); }
	std::vector<Gate*> ProbeAllGates();
	boost::property_tree::ptree GetJson();
private:
	std::map<std::string, TruthTable> m_truthTables;
	std::map<std::string, GateType> m_gateTypes;
	std::map<std::string, Gate> m_gates;
};