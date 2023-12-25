#pragma once
#ifndef POINT_H
#define POINT_H

//三维点坐标
class Point 
{
public:
	Point(float x = 0, float y = 0, float z = 0)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}
	~Point()
	{
		;	
	}
	void SetPoint(float x,float y, float z);
	Point operator+(const Point& point);		//加法重载
	Point operator-(const Point& point);		//减法重载
	float m_x;
	float m_y;
	float m_z;
};

#endif // !POINT_H
