#include "stdafx.h"
#include "processVector.h"

bool SearchMinElement(std::vector<double> const& numbers, double& minElement)
{
	if (!numbers.empty())
	{
		minElement = *std::min_element(numbers.begin(), numbers.end());
		return true;
	}

	return false;
}

void ProcessVector(std::vector<double> &numbers)
{
	if (!numbers.empty())
	{
		double minElement;
		SearchMinElement(numbers, minElement);
		for (size_t i = 0; i < numbers.size(); i++)
		{
			numbers[i] *= minElement;
		}
	}
}