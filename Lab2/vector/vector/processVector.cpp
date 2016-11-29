#include "processVector.h"

double SearchMinElement(std::vector<double> const& numbers)
{
	return *std::min_element(numbers.begin(), numbers.end());
}

void ProcessVector(std::vector<double> &numbers)
{	
	double minElement = SearchMinElement(numbers);

	for (size_t i = 0; i < numbers.size(); i++)
	{
		numbers[i] *= minElement;
	}
}