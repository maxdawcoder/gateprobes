#pragma once
#include <map>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "GateType.h"

class Gate
{
public:
	Gate() {}
	explicit Gate(std::string name, const GateType* type) : m_name(name), m_type(type) {};
	void ConnectInput(int i, Gate* target);
	void AddOutput(Gate* target);
	void Probe() noexcept;
	bool IsProbed() const noexcept { return m_probed; }
	int GetOutput() const noexcept { return m_output; }
	void SetOutput(int value) noexcept { m_output = value; }
	std::string GetName() const noexcept { return m_name; }
	std::vector<Gate*> GetOutGates() { return m_outGates; }
	int GetTransitionOutput() const;
	int GetTransitionTime(int time) const;
	void UndoProbe();
	boost::property_tree::ptree GetJson();
private:
	const GateType* m_type{};
	std::string m_name;
	std::map<int, Gate*> m_inGates;
	std::vector<Gate*> m_outGates;
	bool m_probed{};
	int m_output{};
	int m_delay{};
};