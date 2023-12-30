#include"camera.h"
#include<gl/glut.h>
#include<math.h>
#include<iostream>

Camera::Camera()
{
	mPos.SetPoint(0, 5, 5);
	mViewCenter.SetPoint(0, 0, 0);
	mUP.SetPoint(0, 1, 0);
	mIsWorldView = false;
}

void Camera::Update()
{
	if (!mIsWorldView)
		mPos.SetPoint(characterX, characterY, characterZ);
	else
		mPos.SetPoint(10.0f, 15.0f, 20.0f);		//全局下的视角   

	// 计算相机的观察方向
	float radianDu = du * c;  // 水平旋转角度转为弧度
	float radianH = h * c;    // 垂直旋转角度转为弧度

	mViewCenter.SetPoint(characterX + 100 * cos(radianDu), characterY + 100 * (-sin(radianH))
		, characterZ + 100 * sin(radianDu));

	gluLookAt(mPos.m_x, mPos.m_y, mPos.m_z,  // 相机位置(和人物位置重合)
		mViewCenter.m_x, mViewCenter.m_y, mViewCenter.m_z,  // 观察点位置
		0.0, 1.0, 0.0);            // 上向量
}
