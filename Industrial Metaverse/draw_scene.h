#pragma once
#ifndef DRAW_SCENE_H
#define DRAW_SCENE_H
#include<gl/glut.h>

//每个物体的绘制都会利用Base
class Base
{
public:
	Base(GLfloat center_x = 0, GLfloat center_y = 0, GLfloat center_z = 0)
	{
		m_center_x = center_x;
		m_center_y = center_y;
		m_center_z = center_z;
	}
	virtual void draw() = 0;
	virtual ~Base() {}
protected:
	//中心坐标
	GLfloat m_center_x;
	GLfloat m_center_y;
	GLfloat m_center_z;
};


class Ground : public Base {
public:
	Ground(GLfloat x, GLfloat y, GLfloat z) : Base(x, y, z) { width = 40.0f; length = 40.0f; height = 1.0f; }
    ~Ground() {;}
	void draw() override;
private:
	void drawGroundPlane();
	float width;
	float length;
	float height;
};

#endif // !DRAW_SCENE

