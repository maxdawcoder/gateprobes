#include <stdexcept>
#include "Gate.h"


namespace
{
	void RaiseError(const char* c) { throw std::runtime_error(c); }
}
void Gate::ConnectInput(int i, Gate* target)
{
	if (m_inGates.find(i) != m_inGates.end())
		throw std::runtime_error("input terminal already connected");
	m_inGates.insert({ i, target });
	target->AddOutput(this);
}

void Gate::AddOutput(Gate* target)
{
	m_outGates.emplace_back(target);
}

void Gate::Probe() noexcept
{
	if (m_probed)
		RaiseError("Gate already probed");
		
	m_probed = true;
}

boost::property_tree::ptree Gate::GetJson()
{
	boost::property_tree::ptree pt;
	pt.add("id", m_name);
	pt.add("table", m_type->GetTruthTableName());
	pt.add("type", m_type->GetType());
	pt.add("probed", m_probed);

	boost::property_tree::ptree inputs, outputs;
	for (auto& [k,v] : m_inGates)
	{
		boost::property_tree::ptree pt;
		pt.put_value(v->GetName());
		inputs.push_back(std::make_pair("", pt));
	}
	pt.add_child("inputs", inputs);
	 
	for (auto& v : m_outGates)
	{
		boost::property_tree::ptree pt;
		pt.put_value(v->GetName());
		outputs.push_back(std::make_pair("", pt));
	}
	pt.add_child("outputs", outputs);
	return pt;
}

int Gate::GetTransitionOutput() const
{
	std::vector<int> inputs;
	for (const auto& [k, v] : m_inGates)
		inputs.emplace_back(v->GetOutput());
	return m_type->GetOutput(inputs);
}

int Gate::GetTransitionTime(int time) const
{
	return time + m_type->GetDelay();
}

void Gate::UndoProbe()
{
	m_probed = false;
}
