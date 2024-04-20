#include <stdexcept>
#include "TruthTable.h"


int TruthTable::GetOutput(std::vector<int> inputs) const
{
	if (m_inputCount == 1)
		return m_table[inputs[0]];
	return m_table[inputs[0] * 2 + inputs[1]];
}

