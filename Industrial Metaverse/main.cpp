#include"header.h"

#define PI 3.1415926
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 960
int du = 90, OriX = -1, OriY = -1;   //du是视点和x轴的夹角
float r = 4, h = 0.0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
float c = PI / 180.0;    //弧度和角度转换参数
float characterX = 0;	//世界坐标系人物向左移动距离
float characterY = 0;	//相机坐标系人物向上移动距离
float characterZ = 0;	//相机坐标系人物向前移动距离
Camera camera;					//摄像头实例化
CSkyBox skybox;					//天空盒实例化						
LightMaterial lightMaterial;	//光源

//窗口大小
int WindowWidth = WINDOW_WIDTH;	
int WindowHeight = WINDOW_HEIGHT;

void drawGround() {
	Ground* ground = new Ground(0, 0, 0);
	ground->draw();
}

void draw_sky()
{
	/*skybox.CreateSkyBox(camera_front_distance * cos(c * du) - camera_left_distance * sin(c * du),
		camera_up_distance,
		+camera_front_distance * sin(c * du) + camera_left_distance * cos(c * du),50.0,50.0,50.0);*/
	skybox.CreateSkyBox(camera.mPos.m_x, camera.mPos.m_y, camera.mPos.m_z, 50, 50, 50);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除缓冲
	glLoadIdentity();
	camera.Update();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	glPushMatrix();
	glTranslatef(-2.0f, 0, -2.0f);
	glutSolidTeapot(1);
	glPopMatrix();
	draw_sky();
	drawGround();
	glutSwapBuffers();

}

void reshape(int width, int height)
{
	if (height == 0)										
	{
		height = 1;										
	}
	glViewport(0, 0, width, height);						
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									
	float whRatio = (GLfloat)width / (GLfloat)height;
	//may to do 
	gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);							
}

void key(unsigned char k, int x, int y)
{
	float moveSpeed = 0.1;
	float radian = du * PI / 180.0;
	switch (k) {
	case 'W':
	case 'w':
		characterX += moveSpeed * cos(radian); // 向前
		characterZ += moveSpeed * sin(radian);
		break;
	case 'S':
	case 's':
		characterX -= moveSpeed * cos(radian); // 向后
		characterZ -= moveSpeed * sin(radian);
		break;
	case 'D':
	case 'd':
		characterX -= moveSpeed * sin(radian); // 向右
		characterZ += moveSpeed * cos(radian);
		break;
	case 'A':
	case 'a':
		characterX += moveSpeed * sin(radian); // 向左
		characterZ -= moveSpeed * cos(radian);
		break;
	case 'Q':
	case 'q':
		characterY += 0.1;					//向上
		break;
	case 'E':
	case 'e':
		characterY -= 0.1;					//向下
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		OriX = x;
		OriY = y;
	}
	else if (state == GLUT_UP) {
		OriX = -1;
		OriY = -1;
	}
}

void onMouseMove(int x, int y)   //处理鼠标拖动
{
	du += 0.5*(x - OriX); //鼠标在窗口x轴方向上的增量加到视点与x轴的夹角上，就可以左右转
	h += 0.25 * (y - OriY);  //鼠标在窗口y轴方向上的改变加到视点y的坐标上，就可以上下转
	// 限制垂直视角，避免过度旋转
    if (h > 60.0) h = 60.0;
    else if (h < -60.0) h = -60.0;
	OriX = x, OriY = y;  //将此时的坐标作为旧值，为下一次计算增量做准备
}

void init()
{
	///设置为非平滑着色
	glShadeModel(GL_FLAT);
	///开启深度检测
	glEnable(GL_DEPTH_TEST);
	///开启面剔除，取消对那些看不到的面的渲染
	glEnable(GL_CULL_FACE);
	///设置逆时针的为正面
	glFrontFace(GL_CCW);
	///开启颜色混合
	glEnable(GL_BLEND);
	///设置以源颜色的alpha，目标颜色的所有进行混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	///开启光照，关闭则物体全是昏暗的
	glEnable(GL_COLOR_MATERIAL);
}


int main(int argc, char* argv[])
{
	//基本初始化
	glutInit(&argc, argv);                                          
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);     
	glutInitWindowSize(WindowWidth,WindowHeight);
	GLint screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	GLint screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((screenWidth - WindowWidth) / 2, (screenHeight - WindowHeight) / 2);
	glutCreateWindow("Industrial Metaverse");

	//init();
	init_texture();

	//注册回调函数
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(key);
	//glutMotionFunc(onMouseMove);   //鼠标按下才会触发
	glutPassiveMotionFunc(onMouseMove); //鼠标移动就能触发

	glutMainLoop();
	return 0;
}