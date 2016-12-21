#pragma once
#include <iostream>

enum struct Gear
{
	REAR = -1,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
};

enum struct Direction
{
	BACKWARD = 1,
	STAY,
	FORWARD,
};

class CCar
{
public:
	CCar();

	bool IsEngineTurnOn()const;
	Gear GetGear()const;
	Direction GetDirection()const;
	int GetSpeed()const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	bool IsCarOnSecondGear(int gear = 0);
	bool IsCarOnThirdGear(int gear = 0);

private:
	Gear m_gear;
	bool m_isEngineOn;
	Direction m_direction;
	int m_speed;
};