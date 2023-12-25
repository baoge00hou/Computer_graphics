#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H

class CSkyBox
{
public:
	/** 构造函数 */
	CSkyBox();
	/** 初始化 */
	bool Init();

	/** 渲染天空 */
	void  CreateSkyBox(float x, float y, float z,
		float width, float height, float length);

private:

	const unsigned int MAP_WIDTH = 1024;
	const unsigned int CELL_WIDTH = 16;
	const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;
};

#endif // !SKYBOX_H
