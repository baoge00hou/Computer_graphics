#include"Forklift.h"
#include<gl/glut.h>
#include<math.h>
#include"texture.h"
#define M_PI 3.1415926
const float tireRadius = 0.3f;  // 轮胎半径
const float thickness = 0.2f;    //轮胎厚度
const int slices = 20;  // 切片数量

void draw_disk()
{
    glBindTexture(GL_TEXTURE_2D, texture[12]);

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, 0.0f, 0.0f); // 圆盘的中心

    for (int i = 0; i <= slices; i++) {
        float angle = 2.0f * M_PI * i / slices;
        float x = tireRadius * cosf(angle);
        float y = tireRadius * sinf(angle);

        glTexCoord2f((cosf(angle) + 1.0f) * 0.5f, (sinf(angle) + 1.0f) * 0.5f);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();
}

void draw_one_wheel()
{
    // 绘制前侧圆盘
    glPushMatrix();
    draw_disk();
    glPopMatrix();
        
    // 绘制圆柱体（轮胎的边缘）
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[11]);
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, tireRadius, tireRadius, thickness, slices, 1);
    gluDeleteQuadric(quadric);
    glPopMatrix();

    // 绘制后侧圆盘
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, thickness); // 向轮胎厚度方向平移
    draw_disk();
    glPopMatrix();
}


void draw_wheel()
{
    glPushMatrix();
    glTranslatef(1.0f, -0.5f, 0.75f); // 前右轮
    draw_one_wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, -0.5f, 0.75f); // 前左轮
    draw_one_wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0f, -0.5f, -0.75f); // 后右轮
    draw_one_wheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, -0.5f, -0.75f); // 后左轮
    draw_one_wheel();
    glPopMatrix();
}

//画一个有纹理的矩形
void draw_rectangle(float x,float y,float z,float box_width,float box_height,float box_length,int texture_number)
{
    glBindTexture(GL_TEXTURE_2D, texture[texture_number]);
    // 矩形的半边长
    float halfWidth = box_width * 0.5f;
    float halfHeight = box_height * 0.5f;
    float halfLength = box_length * 0.5f;

    // 矩形绘制
    glPushMatrix();
    glTranslatef(x, y, z);

    // 绘制背面
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, -halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, halfHeight, -halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, -halfLength);
    glEnd();

    // 绘制前面
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, halfLength);
    glEnd();

    // 绘制底面
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, halfLength);
    glEnd();

    // 绘制顶面
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, halfHeight, -halfLength);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, halfHeight, -halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, halfLength);
    glEnd();

    // 绘制左面
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, -halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-halfWidth, -halfHeight, -halfLength);
    glEnd();

    // 绘制右面
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, -halfLength);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(halfWidth, -halfHeight, halfLength);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(halfWidth, halfHeight, halfLength);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(halfWidth, halfHeight, -halfLength);
    glEnd();

    glPopMatrix();
}

void draw_body()
{
    glPushMatrix();
    draw_rectangle(0, -0.25f, 0.1f, 2.1f, 0.8f, 1.5f, 13);
    glPopMatrix();
}

//上端的Cab
void draw_cab()
{
    glPushMatrix();
    draw_rectangle(0, 0.8f, 0.1f, 1.5f, 1.3f, 1.0f, 14);
    glPopMatrix();
}
//两个fork
void draw_fork()
{
    glPushMatrix();
    draw_rectangle(1.1f, 0.4f, 0.4f, 0.1f, 1.8f, 0.15f, 15);
    draw_rectangle(1.1f, 0.4f, -0.2f, 0.1f, 1.8f, 0.15f, 15);
    glPopMatrix();
    glPushMatrix();
    draw_rectangle(1.6f, -0.45f, 0.4f, 1.0f, 0.1f, 0.15f, 16);
    draw_rectangle(1.6f, -0.45f, -0.2f, 1.0f, 0.1f, 0.15f, 16);
    glPopMatrix();
}

//绘制叉车
void draw_Forklift()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    draw_wheel();
    draw_body();
    draw_cab();
    draw_fork();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}