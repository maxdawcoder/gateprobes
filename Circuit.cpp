#include <stdexcept>
#include "Circuit.h"
/* 
Adds a truth table that can be later attached to gate types.
Args:
	name: A unique string used to identify the truth table.
	output_list: A list of outputs for the truth table.
*/
void Circuit::AddTruthTable(std::string type, std::vector<int> outputs)
{
	if (m_truthTables.find(type) != m_truthTables.end())
		throw std::runtime_error("Truth table name already used");
	m_truthTables.insert({ type, TruthTable(type, outputs) });

}

/* 
 Adds a gate type that can be later attached to gates.

Args:
	name: A unique string used to identify the gate type.
	truth_table_name: The name of the gate's truth table.
	delay: The gate's delay from an input transition to an output
		transition.
*/
void Circuit::AddGateType(std::string name, std::string truthTableName, int delay)
{
	if (m_gateTypes.find(name) != m_gateTypes.end())
		throw std::runtime_error("Gate type name already used");
	if (delay < 0)
		throw std::runtime_error("Invalid delay");
	m_gateTypes.insert({ name, GateType(name, &(m_truthTables[truthTableName]), delay) });
}

/* 
 Adds a gate and connects it to other gates.

Args:
	name: A unique string used to identify the gate.
	type_name: The name of the gate's type.
	input_names: List of the names of gates whose outputs are connected
		to this gate's inputs.

*/
void Circuit::AddGate(std::string name, std::string typeName, std::vector<std::string> inputNames)
{
	if (m_gates.find(name) != m_gates.end())
		throw std::runtime_error("Gate name already used");
	GateType& type = m_gateTypes[typeName];
	auto [pair, _] = m_gates.insert({ name, Gate(name, &type) });
	auto& gate = pair->second;
	for (unsigned i = 0; i < inputNames.size() ; ++i)
	{
		auto& target = m_gates[inputNames[i]];
		gate.ConnectInput(i, &target);
	}
}

void Circuit::AddProbe(std::string gateName)
{
	auto gate = m_gates[gateName];
	gate.Probe();
}

std::vector<Gate*> Circuit::ProbeAllGates()
{
	std::vector<Gate*> probed;
	for (auto& [k, v] : m_gates)
	{
		if (v.IsProbed())
			continue;
		v.Probe();
		probed.emplace_back(&v);
	}
	return probed;
}

boost::property_tree::ptree Circuit::GetJson()
{
	boost::property_tree::ptree pt;
	for (auto& [k, v] : m_gates)
	{
		pt.push_back(std::make_pair("", v.GetJson()));
	}
	boost::property_tree::ptree ret;
	ret.add_child("gates", pt);
	return ret;
}
