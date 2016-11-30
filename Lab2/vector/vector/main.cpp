//������ ������� ������� ������ ���� ������� �� ����������� ������� ��������� �������

#include "stdafx.h"
#include "processVector.h"
#include <vector>
#include <iostream>
#include <iterator>
#include <boost/range/algorithm/copy.hpp>

using namespace std;

int main()
{
	cout << "Enter double numbers separated by spaces." << "\n";
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	if (numbers.size() == 0)
	{
		cout << "Number not entered." << "\n";
		return 0;
	}
	ProcessVector(numbers);
	sort(numbers.begin(), numbers.end());
	boost::copy(numbers, ostream_iterator<double>(cout, ", "));

	return 0;
}