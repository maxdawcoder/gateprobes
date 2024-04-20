#pragma once

#include <vector>
#include <string>

// """Truth table representation of the logic inside a gate."""
class TruthTable
{
public:
    TruthTable() {}
    TruthTable(std::string name, std::vector<int> outputs) : m_name(name), m_table(outputs)
    {
        if (outputs.size() != 2 && outputs.size() != 4)
            throw std::runtime_error("Unsupported truth table size");
        if (outputs.size() == 2)
            m_inputCount = 1;
        else
            m_inputCount = 2;
    }
    int GetOutput(std::vector<int> inputs) const;
    std::string GetName() const
    {
        return m_name;
    }
private:
    std::string m_name;
    std::vector<int> m_table;
    int m_inputCount;
};

