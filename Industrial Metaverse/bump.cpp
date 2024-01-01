#include"bump.h"

bool Bump::bumptest()
{
	//铲车检测
	if (m_x >= 0.5f && m_x <= 4.5f && m_z <= 3.0f && m_z >= 1.0f)
		return true;
	//其他的物体检测

	return false;
}
