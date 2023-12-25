#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include<gl/glut.h>
#include"Point.h"

extern int du, OriX, OriY;   //du是视点和x轴的夹角
extern float r , h;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
extern float c;    //弧度和角度转换参数
extern float characterX;//世界坐标系下向左移动距离
extern float characterY;//世界坐标系下向上移动距离
extern float characterZ;//世界坐标系下向前移动距离

class Camera 
{
public:
	Camera();
	void Update();		//更新摄像头视角
	~Camera() { ; }

	Point mPos;				// 摄像头位置
	Point mViewCenter;		// 视点（看向的位置）
	Point mUP;				// gllookat时最后一个向量
};


#endif // !CAMERA_H
