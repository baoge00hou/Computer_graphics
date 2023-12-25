#include"camera.h"
#include<gl/glut.h>
#include<math.h>
#include<iostream>

Camera::Camera()
{
	mPos.SetPoint(0, 5, 5);
	mViewCenter.SetPoint(0, 0, 0);
	mUP.SetPoint(0, 1, 0);
}

void Camera::Update()
{	
	//相机坐标系
	gluLookAt(r * cos(c * du) + camera_front_distance * cos(c * du) - camera_left_distance * sin(c * du),
		h + camera_up_distance,
		r * sin(c * du) + camera_front_distance * sin(c * du) + camera_left_distance * cos(c * du),
		camera_front_distance * cos(c * du) - camera_left_distance * sin(c * du),
		camera_up_distance,
		+camera_front_distance * sin(c * du) + camera_left_distance * cos(c * du),
		0, 1.0, 0.0);   //从视点看远点		
}
