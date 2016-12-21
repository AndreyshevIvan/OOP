#include "stdafx.h"
#include "CCar.h"

using namespace std;

CCar::CCar()
{
	m_isEngineOn = false;
	m_gear = Gear::NEUTRAL;
	m_direction = Direction::STAY;
	m_speed = 0;
}

bool CCar::IsEngineTurnOn()const
{
	return m_isEngineOn;
}

Gear CCar::GetGear()const
{
	return m_gear;
}

Direction CCar::GetDirection()const
{
	return m_direction;
}

int CCar::GetSpeed()const
{
	return m_speed;
}

bool CCar::TurnOnEngine()
{
	if (m_isEngineOn)
	{
		return false;
	}
	
	m_isEngineOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn && m_gear == Gear::NEUTRAL && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool CCar::SetGear(int gear)
{
	if (!m_isEngineOn)
		return false;

	if (((gear == -1) && ((m_speed == 0 && (m_gear == Gear::NEUTRAL || m_gear == Gear::FIFTH)) || (m_gear == Gear::REAR))) ||
		(gear == 0) ||
		((gear == 1) && ((m_gear == Gear::REAR && m_speed == 0) || (m_gear == Gear::NEUTRAL && m_direction == Direction::STAY) ||
		(m_direction == Direction::FORWARD && m_speed >= 0 && m_speed <= 30) || (m_gear == Gear::FIRST))) ||
		((gear == 2) && (m_speed >= 20 && m_speed <= 50)) ||
		((gear == 3) && (m_speed >= 30 && m_speed <= 60)) ||
		((gear == 4) && (m_speed >= 40 && m_speed <= 90)) ||
		((gear == 5) && (m_speed >= 50 && m_speed <= 150)))
	{
		m_gear = Gear(gear);
		return true;
	}
	else
	{
		return false;
	}
}

bool CCar::SetSpeed(int speed)
{
	bool isSpeedChange = false;
	if (!m_isEngineOn)
		return false;

	if (isSpeedChange = ((m_gear == Gear::REAR) && (speed >= 0 && speed <= 20)))
	{
		(speed == 0) ? m_direction = Direction::STAY : m_direction = Direction::BACKWARD;
	}
	else if (isSpeedChange = ((m_gear == Gear::NEUTRAL) && (speed >= 0 && speed <= 150 && (m_speed - speed) >= 0)))
	{
		(speed == 0) ? m_direction = Direction::STAY : m_direction = Direction::FORWARD;
	}
	else if (isSpeedChange = ((m_gear == Gear::FIRST) && (speed >= 0 && speed <= 30)))
	{
		(speed == 0) ? m_direction = Direction::STAY : m_direction = Direction::FORWARD;
	}
	else if (isSpeedChange = ((m_gear == Gear::SECOND) && (speed >= 20 && speed <= 50)))
	{
		m_direction = Direction::FORWARD;
	}
	else if (isSpeedChange = ((m_gear == Gear::THIRD) && (speed >= 30 && speed <= 60)))
	{
		m_direction = Direction::FORWARD;
	}
	else if (isSpeedChange = ((m_gear == Gear::FOURTH) && (speed >= 40 && speed <= 90)))
	{
		m_direction = Direction::FORWARD;
	}
	else if (isSpeedChange = ((m_gear == Gear::FIFTH) && (speed >= 50 && speed <= 150)))
	{
		m_direction = Direction::FORWARD;
	}

	if (isSpeedChange)
		m_speed = speed;
	return isSpeedChange;
}