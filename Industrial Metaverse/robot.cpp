#include"robot.h"
#include<gl/glut.h>

void drawHead() {
    // 头部
    glColor3f(0.9f, 0.9f, 0.9f); 
    glPushMatrix();
    glTranslatef(0.0f, 1.25f, 0.0f); 
    glScalef(0.5f, 0.5f, 0.5f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // 眼睛
    glColor3f(0.2f, 0.2f, 0.2f); 
    glPushMatrix();
    glTranslatef(0.125f, 1.35f, -0.25f); 
    glScalef(0.1f, 0.1f, 0.1f); 
    glutSolidSphere(1.0f, 20, 20); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.125f, 1.35f, -0.25f); 
    glScalef(0.1f, 0.1f, 0.1f); 
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();

    // 嘴巴
    glColor3f(0.8f, 0.2f, 0.2f); 
    glPushMatrix();
    glTranslatef(0.0f, 1.10f, -0.25f); 
    glScalef(0.3f, 0.1f, 0.1f); 
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawChest() {
    glColor3f(1.0f, 0.7f, 0.1f); // 设置胸部颜色
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); // 移动到适当位置
    glScalef(1.4f, 2.0f, 0.5f); // 缩放以适应胸部大小
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawArms() {
    // 绘制右上臂
    glColor3f(0.8f, 0.4f, 0.5f);
    glPushMatrix();
    glTranslatef(0.85f, 1.55f, 0.0f); 
    glRotatef(45, 1, 0, 0);
    glScalef(0.3f, 1.6f, 0.4f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // 绘制左上臂
    glPushMatrix();
    glTranslatef(-0.85f, 1.55f, 0.0f); 
    glRotatef(45, 1, 0, 0);
    glScalef(0.3f, 1.6f, 0.4f); 
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawLegs() {
    // 绘制右上腿
    glColor3f(0.5f, 0.8f, 0.3f); 
    glPushMatrix();
    glTranslatef(0.375f, -0.5f, 0.0f); 
    glScalef(0.4f, 1.0f, 0.4f); 
    glutSolidCube(1.0f);
    glPopMatrix();

    // 绘制左上腿
    glPushMatrix();
    glTranslatef(-0.375f, -0.5f, 0.0f); 
    glScalef(0.4f, 1.0f, 0.4f); 
    glutSolidCube(1.0f);
    glPopMatrix();
}

void draw_robot()
{
    glPushMatrix();
    glTranslatef(0, 0, 10.0);
    drawHead();
    drawChest();
    drawArms();
    drawLegs();
    glPopMatrix();
}

