#include"draw_scene.h"
#include"texture.h"

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