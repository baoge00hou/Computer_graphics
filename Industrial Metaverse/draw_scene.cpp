#include"draw_scene.h"
#include"texture.h"
#include<math.h>
#define M_PI 3.1415926

//Ground
void Ground::draw() {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);  
    glPushMatrix();
    glTranslatef(m_center_x, m_center_y, m_center_z);
    drawGroundPlane();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);	
}
void Ground::drawGroundPlane()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[10]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPushMatrix();
    glTranslatef(m_center_x, m_center_y, m_center_z);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, m_center_y - height, -length / 2);
    glTexCoord2f(10.0f, 0.0f); glVertex3f(width / 2, m_center_y - height, -length / 2);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(width / 2, m_center_y - height, length / 2);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-width / 2, m_center_y - height, length / 2);
   
    glEnd();
    glPopMatrix();
    // 禁用纹理
    glDisable(GL_TEXTURE_2D);
}

//Circle
void Circle::draw()
{
    if (textureVisible) {
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[17]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glPushMatrix();
        glRotatef(45, 1, 1, 0);
        glTranslatef(m_center_x, m_center_y, m_center_z);

        // 设置材质  在被光照时表面变成红色
        GLfloat matRed[] = { 1.0, 0.0, 0.0, 1.0 };  // 红色材质
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matRed);

        const int slices = 50;
        const int stacks = 50;
        const float radius = 1.0;

        for (int i = 0; i < stacks; ++i) {
            float lat0 = M_PI * (-0.5 + (float)i / stacks);
            float z0 = radius * sin(lat0);
            float zr0 = radius * cos(lat0);

            float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks);
            float z1 = radius * sin(lat1);
            float zr1 = radius * cos(lat1);

            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= slices; ++j) {
                float lng = 2 * M_PI * (float)j / slices;
                float x = cos(lng);
                float y = sin(lng);

                glTexCoord2f((float)j / slices, (float)i / stacks);
                glNormal3f(x * zr0, y * zr0, z0);
                glVertex3f(x * zr0, y * zr0, z0);

                glTexCoord2f((float)j / slices, (float)(i + 1) / stacks);
                glNormal3f(x * zr1, y * zr1, z1);
                glVertex3f(x * zr1, y * zr1, z1);
            }
            glEnd();
        }






        //for (int i = 0; i <= 50; ++i) {
        //    float lat0 = M_PI * (-0.5 + (float)(i - 1) / 50);
        //    float z0 = sin(lat0);
        //    float zr0 = cos(lat0);

        //    float lat1 = M_PI * (-0.5 + (float)i / 50);
        //    float z1 = sin(lat1);
        //    float zr1 = cos(lat1);

        //    glBegin(GL_QUAD_STRIP);
        //    for (int j = 0; j <= 50; ++j) {
        //        float lng = 2 * M_PI * (float)(j - 1) / 50;
        //        float x = cos(lng);
        //        float y = sin(lng);

        //        glColor3f(0, 1, 0);  // 设置颜色
        //        glNormal3f(x * zr0, y * zr0, z0);  // 设置法线
        //        glVertex3f(x * zr0, y * zr0, z0);  // 设置顶点

        //        glNormal3f(x * zr1, y * zr1, z1);
        //        glVertex3f(x * zr1, y * zr1, z1);
        //    }
        //    glEnd();
        //}
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        // 重置为默认的填充模式
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    }
    else {
        // 不使用纹理，只绘制球体（没有纹理）


        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPushMatrix();
        glRotatef(45, 1, 1, 0);
        glTranslatef(m_center_x, m_center_y, m_center_z);



        glColor3f(0.0f, 1.0f, 0.0f);  // 设置绘制颜色为红色
        glutSolidSphere(1.0, 50, 50);  // 绘制半径为1的球体，使用20个纬度和经度切片

        //for (int i = 0; i <= 50; ++i) {
        //    float lat0 = M_PI * (-0.5 + (float)(i - 1) / 50);
        //    float z0 = sin(lat0);
        //    float zr0 = cos(lat0);

        //    float lat1 = M_PI * (-0.5 + (float)i / 50);
        //    float z1 = sin(lat1);
        //    float zr1 = cos(lat1);

        //    glBegin(GL_QUAD_STRIP);
        //    for (int j = 0; j <= 50; ++j) {
        //        float lng = 2 * M_PI * (float)(j - 1) / 50;
        //        float x = cos(lng);
        //        float y = sin(lng);

        //        glColor3f(0, 1, 0);  // 设置颜色
        //        glNormal3f(x * zr0, y * zr0, z0);  // 设置法线
        //        glVertex3f(x * zr0, y * zr0, z0);  // 设置顶点

        //        glNormal3f(x * zr1, y * zr1, z1);
        //        glVertex3f(x * zr1, y * zr1, z1);
        //    }
        //    glEnd();

    }
    glPopMatrix();
    // 重置为默认的填充模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}
