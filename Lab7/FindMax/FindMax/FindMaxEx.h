#pragma once
#include "stdafx.h"

template <class T, class Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto maxElement = arr.begin();

	for (auto it = arr.begin(); it != arr.end(); it++)
	{
		if (less(*maxElement, *it))
		{
			maxElement = it;
		}
	}
	maxValue = *maxElement;

	return true;
}