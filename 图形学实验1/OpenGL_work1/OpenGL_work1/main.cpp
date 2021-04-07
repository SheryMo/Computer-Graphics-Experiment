#include "StrickMan.h"
#include <string>
People people;

Ternary camera(0, 0, 40);
std::string str = "current fps = ";
float curTransX;
float curTransY;//记录当前总体的位置

GLfloat angle = 0.0f;
float mouseX, mouseY;
bool mouseLeftDown = false;
bool mouseRightDown = false;
bool idleBegin = false;
bool needRecord = false;
float cameraDistanceX;
float cameraDistanceY;
float cameraDistanceZ;
float cameraAngleX;
float cameraAngleY;
void DisPlay() {
	//清除了深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
	
	

	//本次绘图最基础的开始坐标原点
	glTranslatef(0.0f, 0.0f, 0.0f);//平移矩阵(x,y,z)
	glMatrixMode(GL_MODELVIEW);
	if(mouseRightDown == true)
		glRotatef(people.angle, 0, 1, 0);//旋转矩阵
	//glRotatef(people.angle, 0, 1, 0);//旋转矩阵
//	gluLookAt(camera.x, camera.y, camera.z, 0, 0, 0, 0, 1, 0);
	glPushMatrix();//保存当前模型的视图矩阵
//	gluLookAt(camera.x, camera.y, camera.z, 0, 0, 0, 0, 1, 0);


	glTranslatef(0.0f, 0.0f, 0.0f);
	//glTranslatef(25.0, 0.0, 0.0);
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.0f, 1.2f, 0.0f);
	glPushMatrix();
	glTranslatef(0.8, 0.0, 0.0);
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(people.leftArmb, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -0.8, 0.0);
	glTranslatef(0.0, -0.3, 0.0);
	glRotatef(people.leftArma, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -0.8, 0.0);//Test
	glTranslatef(0.0, -0.2, 0.0);
	glRotatef(people.leftWrist, 1, 0, 0);
	people.DrawWrist();
	glPopMatrix();
	people.DrawArmA();
	glPopMatrix();
	people.DrawArmB();
	glPopMatrix();
	//画出右臂
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 0.0);
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(people.rightArmb, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -0.8, 0.0);
	glTranslatef(0.0, -0.3, 0.0);
	glRotatef(people.rightArma, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -0.8, 0.0);//Test
	glTranslatef(0.0, -0.2, 0.0);
	glRotatef(people.rightWrist, 1, 0, 0);
	people.DrawWrist();
	glPopMatrix();
	people.DrawArmA();
	glPopMatrix();
	people.DrawArmB();
	glPopMatrix();

	//return shoulder  
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.7, 0.0);
	people.DrawHead();
	glPopMatrix();
	people.DrawNeck();
	glPopMatrix();
	people.DrawShoulder();
	glPopMatrix();
	//return body  
	glPushMatrix();
	glTranslatef(0.0f, -1.2f, 0.0f);
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(people.leftLegb, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -1.5, 0.0);
	glRotatef(people.leftLega, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -1.5, 0.0);
	people.DrawAnkle();
	glPopMatrix();
	people.DrawLegA();
	glPopMatrix();
	people.DrawLegB();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glTranslatef(0.0, -0.4, 0.0);
	glRotatef(people.rightLegb, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -1.5, 0.0);
	glRotatef(people.rightLega, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.0, -1.5, 0.0);
	people.DrawAnkle();
	glPopMatrix();
	people.DrawLegA();
	glPopMatrix();
	people.DrawLegB();
	glPopMatrix();
	people.DrawHip();
	glPopMatrix();
	people.DrawBody();
	glPopMatrix();

	glPopMatrix();

	people.leftArma += people.la;
	people.rightArma += people.ra;
	people.leftArmb += people.a;
	people.rightArmb -= people.a;
	people.leftWrist += people.laa;
	people.rightWrist += people.raa;

	people.leftLega += people.ll;
	people.rightLega += people.rl;
	people.leftLegb -= people.b;
	people.rightLegb += people.b;

	/*if (trans <= -50)
		trans = 0;*/
	if (50 > people.leftArmb && people.leftArmb > 0 && people.a > 0) {
		people.a = people.angle1;
		people.b = people.angle2;
		people.la = -people.angle1 * 0.75;
		people.ra = -people.angle1;
		people.ll = 0.75*people.angle2;
		people.rl = people.angle2 * 1.5;
		people.laa = -people.angle2 * 0.7 ;
		people.raa = -people.angle2 * 0.7;
	}
	if (people.leftArmb >= 50 && people.a > 0) {
		people.a = -people.angle1;
		people.b = -people.angle2;
	}
	if (people.leftArmb > 0 && people.a < 0) {
		people.a = -people.angle1;
		people.b = -people.angle2;
		people.la = people.angle1 * 0.75;
		people.ra = people.angle1;
		people.ll = -people.angle2 * 0.75;
		people.rl = -people.angle2 * 1.5;
		people.laa = people.angle2 * 0.7;
		people.raa = people.angle2 * 0.7;
	}
	if (-50 < people.leftArmb && people.leftArmb <= 0 && people.a < 0) {
		people.a = -people.angle1;
		people.b = -people.angle2;
		people.la = -people.angle1;
		people.ra = -people.angle1 * 0.75;
		people.ll = people.angle2 * 1.5;
		people.rl = people.angle2 * 0.75;
		people.laa = -people.angle2 * 0.7;
		people.raa = -people.angle2 * 0.7;
	}
	if (people.leftArmb <= -50 && people.a < 0) {
		people.a = people.angle1;
		people.b = people.angle2;
		people.laa = people.raa = 0;
	}
	if (people.leftArmb < 0 && people.a>0) {
		people.a = people.angle1;
		people.b = people.angle2;
		people.la = people.angle1;
		people.ra = people.angle1 * 0.75;
		people.ll = -people.angle2 * 1.5;
		people.rl = -people.angle2 * 0.75;
		people.laa = people.angle2 * 0.7;
		people.raa = people.angle2 * 0.7;
	}

	glutSwapBuffers();
}


void ReSizeGLScene(int Width, int Height)
{
	float size = 8;
	if (Height == 0)
		Height = 1;
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (Width <= Height)
		glOrtho(-size, size, -size * (GLfloat)Height / (GLfloat)Width, size*(GLfloat)Height / (GLfloat)Width, -size, size);
	else
		glOrtho(-size * (GLfloat)Width / (GLfloat)Height, size*(GLfloat)Width / (GLfloat)Height, -size, size, -size, size);

	//gluPerspective(1.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);
	//glMatrixMode(GL_MODELVIEW);
	//设置模型参数--几何体参数
	glMatrixMode(GL_MODELVIEW);
}

void MouseMotion(int x, int y)
{
	cameraAngleX = cameraAngleY = 0;
	//mouseLeftDown = false;
	if (mouseRightDown)
	{
		cameraAngleY += (x - mouseX) ;
		cameraAngleX += (y - mouseY) ;
		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
	people.angle = cameraAngleY*0.1;
}
void MouseFunc(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	mouseRightDown = false;
	mouseLeftDown = false; cameraDistanceZ = cameraDistanceX = cameraDistanceY = 0;
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else
		{
			if (state == GLUT_UP)
			{
				mouseLeftDown = false;
			}
		}
	}
	else
	{
		if (button == GLUT_RIGHT_BUTTON)
		{
			if (state == GLUT_DOWN)
			{
				mouseRightDown = true;
			}
			else
			{
				if (state == GLUT_UP)
				{
					mouseRightDown = false;
				}
			}
		}

	}

}
int main(int argc, char **argv) {
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1080, 768);
	glutInitWindowPosition(100,100);
	int window = glutCreateWindow("Stick man");
	glutDisplayFunc(&DisPlay);/* Register the function to do all our OpenGL drawing. */
	glutIdleFunc(&DisPlay);/* Even if there are no events, redraw our gl scene. */
	glutMouseFunc(&MouseFunc);
	glutMotionFunc(&MouseMotion);

	glutReshapeFunc(&ReSizeGLScene);/* Register the function called when our window is resized. */
	//glutKeyboardFunc(&keyPressed);
	people.InitGL(640, 480);
	glutMainLoop();
	return 0;
}