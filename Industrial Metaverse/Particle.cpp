#include "Particle.h"
#include <GL/glut.h> 
#include <iostream>

/** 构造函数 */
CParticle::CParticle()
{
    data = NULL;
    numparticle = 0;

}

/** 析构函数 */
CParticle::~CParticle()
{
    delete[]data;
    data = NULL;
}

/** 创建一个包含num个元素的粒子数组 */
int CParticle::Create(long num)
{
    /** 删除粒子数组 */
    if (data)
        delete[]data;

    /** 创建数组 */
    if (data = new Particle[num])
    {
        memset(data, 0, sizeof(Particle) * numparticle);
        numparticle = num;

        /** 返回粒子个数 */
        return numparticle;
    }
    return 0;
}


/** 设置和获取颜色Color的函数实现 */
int CParticle::SetColor(GLint r, GLint g, GLint b)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].r = r;
        data[index].g = g;
        data[index].b = b;
    }
    return true;
}

int CParticle::SetColor(GLint index, GLint r, GLint g, GLint b)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].r = r;
        data[index].g = g;
        data[index].b = b;
        return true;
    }
    return false;
}

int CParticle::GetColor(GLint index, GLint& r, GLint& g, GLint& b)
{
    if (index >= 0 && index < numparticle)
    {
        r = data[index].r;
        g = data[index].g;
        b = data[index].b;
        return true;
    }
    return false;
}

/** 设置和获取位置Position的函数实现 */
int CParticle::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].x = x;
        data[index].y = y;
        data[index].z = z;
    }
    return true;
}

int CParticle::SetPosition(GLint index, GLfloat x, GLfloat y, GLfloat z)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].x = x;
        data[index].y = y;
        data[index].z = z;
        return true;
    }
    return false;
}

int CParticle::GetPosition(GLint index, GLfloat& x, GLfloat& y, GLfloat& z)
{
    if (index >= 0 && index < numparticle)
    {
        x = data[index].x;
        y = data[index].y;
        z = data[index].z;
        return true;
    }
    return false;
}
/** 设置和获取加速度Acceleration的函数实现 */
int CParticle::SetAcceleration(GLfloat ax, GLfloat ay, GLfloat az)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].ax = ax;
        data[index].ay = ay;
        data[index].az = az;
    }
    return true;
}

int CParticle::SetAcceleration(GLint index, GLfloat ax, GLfloat ay, GLfloat az)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].ax = ax;
        data[index].ay = ay;
        data[index].az = az;
        return true;
    }
    return false;
}


int CParticle::GetAcceletation(GLint index, GLfloat& ax, GLfloat& ay, GLfloat& az)
{
    if (index >= 0 && index < numparticle)
    {
        ax = data[index].ax;
        ay = data[index].ay;
        az = data[index].az;
        return true;
    }
    return false;
}



/** Velocity函数的实现 */
int CParticle::SetVelocity(GLfloat vx, GLfloat vy, GLfloat vz)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].vx = vx;
        data[index].vy = vy;
        data[index].vz = vz;
    }
    return true;
}

int CParticle::SetVelocity(GLint index, GLfloat vx, GLfloat vy, GLfloat vz)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].vx = vx;
        data[index].vy = vy;
        data[index].vz = vz;
        return true;
    }
    return false;
}

int CParticle::GetVelocity(GLint index, GLfloat& vx, GLfloat& vy, GLfloat& vz)
{
    if (index >= 0 && index < numparticle)
    {
        vx = data[index].vx;
        vy = data[index].vy;
        vz = data[index].vz;
        return true;
    }
    return false;
}


/** Size函数的实现 */
int CParticle::SetSize(GLfloat size)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].size = size;
    }
    return true;
}

int CParticle::SetSize(GLint index, GLfloat size)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].size = size;
        return true;
    }
    return false;
}

int CParticle::GetSize(GLint index, GLfloat& size)
{
    if (index >= 0 && index < numparticle)
    {
        size = data[index].size;
        return true;
    }
    return false;
}

/** 消失速度Dec函数 */
int CParticle::SetDec(GLfloat dec)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].dec = dec;
    }
    return true;
}

int CParticle::SetDec(GLint index, GLfloat dec)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].dec = dec;
        return true;
    }
    return false;
}

int CParticle::GetDec(GLint index, GLfloat& dec)
{
    if (index >= 0 && index < numparticle)
    {
        dec = data[index].dec;
        return true;
    }
    return false;
}

/** 设置粒子的lifetime 属性 */
int CParticle::SetLifeTime(GLfloat lifetime)
{
    for (int index = 0; index < numparticle; ++index)
    {
        data[index].lifetime = lifetime;
    }
    return true;
}

int CParticle::SetLifeTime(GLint index, GLfloat lifetime)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].lifetime = lifetime;
        return true;
    }
    return false;
}

/** 获得粒子的lifetime属性 */
int CParticle::GetLifeTime(GLint index, GLfloat& lifetime)
{
    if (index >= 0 && index < numparticle)
    {
        lifetime = data[index].lifetime;
        return true;
    }
    return false;
}

/** 获取粒子的所有属性 */
int CParticle::GetAll(int index, GLint& r, GLint& g, GLint& b,         /**< 粒子的颜色 */
    GLfloat& x, GLfloat& y, GLfloat& z,     /**< 位置 */
    GLfloat& vx, GLfloat& vy, GLfloat& vz,  /**< 速度 */
    GLfloat& ax, GLfloat& ay, GLfloat& az,  /**< 加速度 */
    GLfloat& size,                            /**< 大小 */
    GLfloat& lifetime,                        /**< 生命时间 */
    GLfloat& dec                          /**< 消失速度 */
)
{
    if (index >= 0 && index < numparticle)
    {
        r = data[index].r;
        g = data[index].g;
        b = data[index].b;
        x = data[index].x;
        y = data[index].y;
        z = data[index].z;
        vx = data[index].vx;
        vy = data[index].vy;
        vz = data[index].vz;
        ax = data[index].ax;
        ay = data[index].ay;
        az = data[index].az;
        lifetime = data[index].lifetime;
        size = data[index].size;
        dec = data[index].dec;
        return true;
    }
    return false;
}

/** 设置粒子的所有属性 */
int CParticle::SetAll(int index, GLint r, GLint g, GLint b,        /**< 粒子的颜色 */
    GLfloat x, GLfloat y, GLfloat z,        /**< 位置 */
    GLfloat vx, GLfloat vy, GLfloat vz, /**< 速度 */
    GLfloat ax, GLfloat ay, GLfloat az, /**< 加速度 */
    GLfloat size,                     /**< 大小 */
    GLfloat lifetime,                 /**< 生命时间 */
    GLfloat dec                           /**< 消失速度 */
)
{
    if (index >= 0 && index < numparticle)
    {
        data[index].r = r;
        data[index].g = g;
        data[index].b = b;
        data[index].x = x;
        data[index].y = y;
        data[index].z = z;
        data[index].vx = vx;
        data[index].vy = vy;
        data[index].vz = vz;
        data[index].ax = ax;
        data[index].ay = ay;
        data[index].az = az;
        data[index].lifetime = lifetime;
        data[index].size = size;
        data[index].dec = dec;
        return true;
    }
    return false;
}

/** 用来设置粒子的属性值 */
float x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec;
int R, G, B;
//CParticle Snow;

/** 初始化雪花粒子 */
void InitSnow()
{
    for (int i = 0; i < Snow.GetNumOfParticle(); ++i)
    {
        ///初始化颜色（白色）
        R = 255;
        G = 255;
        B = 255;
        Snow.SetColor(i, R, G, B);

        ///初始化坐标
        x = 0.1f * (rand() % 50) - 2.5f;
        y = 2 + 0.1f * (rand() % 2);
        if ((int)x % 2 == 0)
            z = rand() % 6;
        else
            x = -rand() % 3;
        Snow.SetPosition(i, x, y, z);

        ///初始化速度
        vx = 0.00001 * (rand() % 100);
        vy = 0.0000002 * (rand() % 28000);
        vz = 0;
        Snow.SetVelocity(i, vx, vy, vz);

        ///初始化加速度
        ax = 0;
        ay = 0.000005f;
        az = 0;
        Snow.SetAcceleration(i, ax, ay, az);

        ///初始化生命周期
        lifetime = 100;
        Snow.SetLifeTime(i, lifetime);

        ///消失速度
        dec = 0.005 * (rand() % 50);
        Snow.SetDec(i, dec);

        ///初始化大小
        Snow.SetSize(i, 0.03f);
    }
}

/** 更新粒子 */
void UpdateSnow()
{
    /** 更新位置 */
    x += (vx * 5);
    y -= vy;

    /** 更新速度 */
    vy += ay;

    /** 更新生存时间 */
    lifetime -= dec;

    if (x > 3)
        x = -2;

    /** 如果粒子消失或生命结束 */
    if (y <= -1 || lifetime <= 0)
    {
        /** 初始化位置 */
        x = 0.1f * (rand() % 50) - 2.5f;
        y = 2 + 0.1f * (rand() % 2);
        if ((int)x % 2 == 0)
            z = rand() % 6;
        else
            z = -rand() % 3;

        /** 初始化速度 */
        vx = (float)(0.00001 * (rand() % 100));
        vy = (float)(0.0000002 * (rand() % 28000));
        vz = 0;

        /** 初始化加速度 */
        ax = 0;
        ay = 0.000005f;
        az = 0;
        lifetime = 100;
        dec = 0.005 * (rand() % 50);
    }
}

/** 绘制粒子 */
void DrawParticle()
{
    for (int i = 0; i < Snow.GetNumOfParticle(); ++i)
    {
        /** 获得粒子的所有属性 */
        Snow.GetAll(i, R, G, B, x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -6.0f);
        glColor4ub(R, G, B, 255);
        glNormal3f(0.0f, 0.0f, 1.0f);   /**< 定义法线方向 */
        /** 画出粒子 */
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x - size, y - size, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x - size, y + size, z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y - size, z);
        glEnd();
        glPopMatrix();
        /** 更新粒子属性 */
        UpdateSnow();
        Snow.SetAll(i, R, G, B, x, y, z, vx, vy, vz, ax, ay, az, size, lifetime, dec);
    }
   // glutPostRedisplay();//发送渲染请求
}
