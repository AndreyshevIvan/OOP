#pragma once
#include "stdafx.h"

struct Sportsman
{
	std::string name;
	double weight;
	float height;
};

bool IsWeightLess(Sportsman const& firstPlanet, Sportsman const& secondPlanet)
{
	return (firstPlanet.weight < secondPlanet.weight);
}

bool IsHeightLess(Sportsman const& firstPlanet, Sportsman const& secondPlanet)
{
	return (firstPlanet.height < secondPlanet.height);
}

bool IsNameLess(Sportsman const& firstPlanet, Sportsman const& secondPlanet)
{
	return (firstPlanet.name < secondPlanet.name);
}