#pragma once
#include "stdafx.h"

template <class T, class Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr.front();
	for (T const& element : arr)
	{
		if (less(maxValue, element))
		{
			maxValue = element;
		}
	}

	return true;
}