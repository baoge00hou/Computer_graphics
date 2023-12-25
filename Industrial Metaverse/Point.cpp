#include"Point.h"
void Point::SetPoint(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}
Point Point::operator+(const Point& point)
{
	return Point(this->m_x + point.m_x, this->m_y + point.m_y, this->m_z + point.m_z);
}
Point Point::operator-(const Point& point)
{
	return Point(this->m_x - point.m_x, this->m_y - point.m_y, this->m_z - point.m_z);
}
