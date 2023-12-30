#include"header.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
using namespace tinyobj;

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
CParticle Snow;					//粒子系统

//窗口大小原神
int WindowWidth = WINDOW_WIDTH;	
int WindowHeight = WINDOW_HEIGHT;

GLfloat matYellowGreen[] = { 0.5, 1, 0.5, 1 };
GLfloat matWhite[] = { 1, 1, 1, 1 };
GLfloat matShininess[] = { 50 };
GLfloat matBlack[] = { 0, 0, 0, 1 };

//Obj导入
std::vector<float> vertices;
std::vector<unsigned int> indices;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;

void loadObjFile(const std::string& filename) {
	tinyobj::attrib_t attrib;
	std::string err; // Declare a string variable to hold possible error messages
	bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());

	if (!err.empty()) {
		std::cerr << "TinyObjLoader: " << err << std::endl;
	}

	if (!success) {
		std::cerr << "Failed to load OBJ file" << std::endl;
		return;
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			int vertexIndex = 3 * index.vertex_index;
			vertices.push_back(attrib.vertices[vertexIndex]);
			vertices.push_back(attrib.vertices[vertexIndex + 1]);
			vertices.push_back(attrib.vertices[vertexIndex + 2]);
			indices.push_back(indices.size()); // 填充索引
		}
	}
}

void drawObj() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices.data()); // 使用data()获取指向数据的指针
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data()); // 使用data()获取指向数据的指针
	glDisableClientState(GL_VERTEX_ARRAY);
}

//绘制基本体素
void draw_Base() {
	Ground* ground = new Ground(0, 0, 0);
	ground->draw();
	Circle* circle = new Circle(5, 2, 5, 2);
	circle->draw();
}


void draw_sky()
{
	/*skybox.CreateSkyBox(camera_front_distance * cos(c * du) - camera_left_distance * sin(c * du),
		camera_up_distance,
		+camera_front_distance * sin(c * du) + camera_left_distance * cos(c * du),50.0,50.0,50.0);*/


	skybox.CreateSkyBox(camera.mPos.m_x, camera.mPos.m_y, camera.mPos.m_z, 50, 50, 50);
}

void drawRobot()
{
	glColor3f(1, 0.78, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellowGreen);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matBlack);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);

	glPushMatrix();
	glTranslatef(8, 1.2, -5);
	glRotatef(-60, 0, 1, 0);
	glScalef(1, 1, 1);

	glPushMatrix();
	glRotatef(90, 1, 0, 0); // Body
	gluCylinder(quadratic, 1, 1, 1.5, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0); // Hand
	glTranslatef(0, 1.2, 0.3);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0); // Hand
	glTranslatef(0, -1.2, 0.3);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0); // Foot1
	glTranslatef(0, 0.5, 1.5);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0); // Foot2
	glTranslatef(0, -0.5, 1.5);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.2, 0.7); // Antenna
	glRotatef(90, 3, 1.5, 0);
	gluCylinder(quadratic, 0.1, 0.1, 0.5, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.2, -0.7); // Antenna
	glRotatef(90, 3, 1.5, 0);
	gluCylinder(quadratic, 0.1, 0.1, 0.5, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glutSolidSphere(1, 16, 16); // Head
	glPopMatrix();
	glPushMatrix();

	glColor3f(1, 0, 0);//eye

	glTranslatef(0.75, 0, -0.5);
	gluCylinder(quadratic, 0.2, 0.2, 1, 16, 16);
	glPopMatrix();

	glPopMatrix();
}

void drawSimpleExcavator() {
	// 设置铲车的位置
	float posX = 5.0; // 水平方向位置
	float posY = -1.0; // 垂直方向位置
	float posZ = 10.0; // 深度方向位置

	glPushMatrix();
	glTranslatef(posX, posY, posZ);

	// 铲车车身
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.0); // 橙色
	glTranslatef(0.0, 0.5, 0.0);
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// 车轮
	glColor3f(0.0, 0.0, 0.0); // 黑色
	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	for (int i = -1; i <= 1; i += 2) {
		for (int j = -1; j <= 1; j += 2) {
			glPushMatrix();
			glTranslatef(i * 1.0, 0.25, j * 0.5);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			gluCylinder(quadratic, 0.25, 0.25, 0.5, 12, 12);
			glPopMatrix();
		}
	}

	// 铲斗
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5); // 灰色
	glTranslatef(1.0, 0.5, 0.0);
	glRotatef(-30.0, 0.0, 0.0, 1.0);
	glScalef(0.5, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();
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
	/*glPushMatrix();
	glTranslatef(-2.0f, 0, -2.0f);
	glutSolidTeapot(1);
	glPopMatrix();*/

	glPushMatrix();
	drawObj(); // Render the loaded OBJ model
	glPopMatrix();

	/** 绘制粒子 */
	glPushMatrix();
	drawRobot();
	glPopMatrix();
	DrawParticle();
	draw_Forklift();
	draw_Base();
	draw_robot();
	drawSimpleExcavator();
	draw_sky();
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


void captureScreen() {
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// 读取屏幕像素数据
	unsigned char* pixelData = new unsigned char[width * height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

	// 处理像素数据：翻转图像
	unsigned char* flippedData = new unsigned char[width * height * 3];
	for (int y = 0; y < height; y++) {
		memcpy(flippedData + (height - 1 - y) * width * 3,
			pixelData + y * width * 3,
			width * 3);
	}

	// 保存图像
	stbi_write_png("screenshot.png", width, height, 3, flippedData, width * 3);

	// 清理内存
	delete[] pixelData;
	delete[] flippedData;
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
	case 'P':
	case 'p':
		captureScreen();
		break;
	case 'O':
	case 'o':
		camera.mIsWorldView = !camera.mIsWorldView;
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
	//glEnable(GL_CULL_FACE);
	/*///开启颜色混合
	glEnable(GL_BLEND);*/
	///设置以源颜色的alpha，目标颜色的所有进行混合
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	///开启光照，关闭则物体全是昏暗的
	glEnable(GL_COLOR_MATERIAL);

	/** 创建500个粒子 */
	Snow.Create(100);
	/** 初始化粒子 */
	InitSnow();
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

	init();
	init_texture();

	//注册回调函数
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(key);
	//glutMotionFunc(onMouseMove);   //鼠标按下才会触发
	glutPassiveMotionFunc(onMouseMove); //鼠标移动就能触发

	loadObjFile("monkey.obj");

	glutMainLoop();
	return 0;
}
