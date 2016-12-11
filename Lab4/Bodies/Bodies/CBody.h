#pragma once

class CBody
{
public:
	CBody(const std::string& type, double density);

	double GetDensity() const;
	virtual double GetVolume() const = 0;
	double GetMass() const;
	std::string ToString() const;
	
protected:
	double m_density;
	virtual void AddProperties(std::ostream& stream) const = 0;

private:
	std::string m_type;

};