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
	{
		return false;
	}

	switch (gear)
	{
	case -1:
		if (m_speed == 0 && (m_gear == Gear::NEUTRAL || m_gear == Gear::FIFTH))
		{
			m_gear = Gear::REAR;
			return true;
		}
		break;
	case 0:
		m_gear = Gear::NEUTRAL;
		return true;
		break;
	case 1:
		if ((m_gear == Gear::REAR && m_speed == 0) ||
			(m_gear == Gear::NEUTRAL && m_direction == Direction::STAY) ||
			(m_direction == Direction::FORWARD && m_speed >= 0 && m_speed <= 30))
		{
			m_gear = Gear::FIRST;
			return true;
		}
		break;
	case 2:
		if (m_speed >= 20 && m_speed <= 50)
		{
			m_gear = Gear::SECOND;
			return true;
		}
		break;
	case 3:
		if (m_speed >= 30 && m_speed <= 60)
		{
			m_gear = Gear::THIRD;
			return true;
		}
		break;
	case 4:
		if (m_speed >= 40 && m_speed <= 90)
		{
			m_gear = Gear::FOURTH;
			return true;
		}
		break;
	case 5:
		if (m_speed >= 50 && m_speed <= 150)
		{
			m_gear = Gear::FIFTH;
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		return false;
	}

	switch (m_gear)
	{
	case Gear::REAR:
		if (speed >= 0 && speed <= 20)
		{
			m_speed = speed;
			(m_speed == 0) ? m_direction = Direction::STAY : m_direction = Direction::BACKWARD;
			return true;
		}
		break;
	case Gear::NEUTRAL:
		if (speed >= 0 && speed <= 150 && (m_speed - speed) >= 0)
		{
			m_speed = speed;
			(m_speed == 0) ? m_direction = Direction::STAY : m_direction = Direction::FORWARD;
			return true;
		}
		break;
	case Gear::FIRST:
		if (speed >= 0 && speed <= 30)
		{
			m_speed = speed;
			(m_speed == 0) ? m_direction = Direction::STAY : m_direction = Direction::FORWARD;
			return true;
		}
		break;
	case Gear::SECOND:
		if (speed >= 20 && speed <= 50)
		{
			m_speed = speed;
			m_direction = Direction::FORWARD;
			return true;
		}
		break;
	case Gear::THIRD:
		if (speed >= 30 && speed <= 60)
		{
			m_speed = speed;
			m_direction = Direction::FORWARD;
			return true;
		}
		break;
	case Gear::FOURTH:
		if (speed >= 40 && speed <= 90)
		{
			m_speed = speed;
			m_direction = Direction::FORWARD;
			return true;
		}
		break;
	case Gear::FIFTH:
		if (speed >= 50 && speed <= 150)
		{
			m_speed = speed;
			m_direction = Direction::FORWARD;
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}