#include "skybox.h"
#include"texture.h"
#include<gl\glut.h>

CSkyBox::CSkyBox() { }

/** 天空盒初始化 */
bool CSkyBox::Init()
{
	return true;
}

/** 构造天空盒 */
void CSkyBox::CreateSkyBox(float x, float y, float z,
    float box_width, float box_height,
    float box_length)
{
    // 保存当前光照状态
    GLboolean lp;
    glGetBooleanv(GL_LIGHTING, &lp);
    glDisable(GL_LIGHTING); // 关闭光照

    // 设置深度测试
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    glEnable(GL_TEXTURE_2D); // 启用纹理

    // 天空盒的半边长
    float halfWidth = box_width * 0.5f;
    float halfHeight = box_height * 0.5f;
    float halfLength = box_length * 0.5f;

    // 开始绘制天空盒
    glPushMatrix();
    glTranslatef(x, y, z);

    // 绘制背面
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, -halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, halfHeight, -halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, -halfLength);
    glEnd();

    // 绘制前面
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, halfLength);
    glEnd();

    // 绘制底面
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, halfLength);
    glEnd();

    // 绘制顶面
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, halfHeight, -halfLength);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, halfHeight, -halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, halfLength);
    glEnd();

    // 绘制左面
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, -halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, -halfLength);
    glEnd();

    // 绘制右面
    glBindTexture(GL_TEXTURE_2D, texture[9]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, halfHeight, -halfLength);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D); // 禁用纹理

    glEnable(GL_LIGHTING); // 开启光照

    glDepthMask(GL_TRUE);  // 恢复深度检测
}