#include "StrickMan.h"
#include <iostream>

using namespace std;

void People::InitGL(int Width, int Height) {



	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void People::initAngle() {
	leftArma = 0;//左大臂胳膊旋转角速度
	leftArmb = 0; //左小臂胳膊旋转角速度
	leftWrist = 0;//左手腕旋转角速度
	rightWrist = 0;//右手腕旋转角速度
	rightArma = 0; //右大臂胳膊旋转角速度
	rightArmb = 0; //右小臂胳膊旋转角速度
	leftLegb = 0; //左大腿胳膊旋转角速度
	rightLegb = 0; //左小腿胳膊旋转角速度
	leftLega = 0; //右大腿胳膊旋转角速度
	rightLega = 0;//右小腿胳膊旋转角速度
	la = 0;
	ra = 0;
	ll = 0;
	rl = 0;
}

void People::DrawBody() {
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	//forward           
	glVertex3f(-0.5f, 1.0f, 0.25f);
	glVertex3f(0.5f, 1.0f, 0.25f);
	glVertex3f(0.5f, -1.0f, 0.25f);
	glVertex3f(-0.5f, -1.0f, 0.25f);
	//left  
	glVertex3f(0.5f, 1.0f, 0.25f);
	glVertex3f(0.5f, 1.0f, -0.25f);
	glVertex3f(0.5f, -1.0f, -0.25f);
	glVertex3f(0.5f, -1.0f, 0.25f);
	//back  
	glVertex3f(0.5f, 1.0f, -0.25f);
	glVertex3f(-0.5f, 1.0f, -0.25f);
	glVertex3f(-0.5f, -1.0f, -0.25f);
	glVertex3f(0.5f, -1.0f, -0.25f);
	//right  
	glVertex3f(-0.5f, 1.0f, 0.25f);
	glVertex3f(-0.5f, 1.0f, -0.25f);
	glVertex3f(-0.5f, -1.0f, -0.25f);
	glVertex3f(-0.5f, -1.0f, 0.25f);
	//top  
	glVertex3f(0.5f, 1.0f, 0.25f);
	glVertex3f(0.5f, 1.0f, -0.25f);
	glVertex3f(-0.5f, 1.0f, -0.25f);
	glVertex3f(-0.5f, 1.0f, 0.25f);
	//bottom  
	glVertex3f(0.5f, -1.0f, 0.25f);
	glVertex3f(0.5f, -1.0f, -0.25f);
	glVertex3f(-0.5f, -1.0f, -0.25f);
	glVertex3f(-0.5f, -1.0f, 0.25f);
	glEnd();
}
void People::DrawShoulder() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	//forward           
	glVertex3f(-1.0f, 0.2f, 0.25f);
	glVertex3f(1.0f, 0.2f, 0.25f);
	glVertex3f(1.0f, -0.2f, 0.25f);
	glVertex3f(-1.0f, -0.2f, 0.25f);
	//left  
	glVertex3f(1.0f, 0.2f, 0.25f);
	glVertex3f(1.0f, 0.2f, -0.25f);
	glVertex3f(1.0f, -0.2f, -0.25f);
	glVertex3f(1.0f, -0.2f, 0.25f);
	//back  
	glVertex3f(1.0f, 0.2f, -0.25f);
	glVertex3f(-1.0f, 0.2f, -0.25f);
	glVertex3f(-1.0f, -0.2f, -0.25f);
	glVertex3f(1.0f, -0.2f, -0.25f);
	//right  
	glVertex3f(-1.0f, 0.2f, 0.25f);
	glVertex3f(-1.0f, 0.2f, -0.25f);
	glVertex3f(-1.0f, -0.2f, -0.25f);
	glVertex3f(-1.0f, -0.2f, 0.25f);
	//top  
	glVertex3f(1.0f, 0.2f, 0.25f);
	glVertex3f(1.0f, 0.2f, -0.25f);
	glVertex3f(-1.0f, 0.2f, -0.25f);
	glVertex3f(-1.0f, 0.2f, 0.25f);
	//bottom  
	glVertex3f(1.0f, -0.2f, 0.25f);
	glVertex3f(1.0f, -0.2f, -0.25f);
	glVertex3f(-1.0f, -0.2f, -0.25f);
	glVertex3f(-1.0f, -0.2f, 0.25f);
	glEnd();
}
void People::DrawHip() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	//forward             
	glVertex3f(-0.7f, 0.2f, 0.25f);
	glVertex3f(0.7f, 0.2f, 0.25f);
	glVertex3f(0.7f, -0.2f, 0.25f);
	glVertex3f(-0.7f, -0.2f, 0.25f);
	//left  
	glVertex3f(0.7f, 0.2f, 0.25f);
	glVertex3f(0.7f, 0.2f, -0.25f);
	glVertex3f(0.7f, -0.2f, -0.25f);
	glVertex3f(0.7f, -0.2f, 0.25f);
	//back  
	glVertex3f(0.7f, 0.2f, -0.25f);
	glVertex3f(-0.7f, 0.2f, -0.25f);
	glVertex3f(-0.7f, -0.2f, -0.25f);
	glVertex3f(0.7f, -0.2f, -0.25f);
	//right  
	glVertex3f(-0.7f, 0.2f, 0.25f);
	glVertex3f(-0.7f, 0.2f, -0.25f);
	glVertex3f(-0.7f, -0.2f, -0.25f);
	glVertex3f(-0.7f, -0.2f, 0.25f);
	//top  
	glVertex3f(0.7f, 0.2f, 0.25f);
	glVertex3f(0.7f, 0.2f, -0.25f);
	glVertex3f(-0.7f, 0.2f, -0.25f);
	glVertex3f(-0.7f, 0.2f, 0.25f);
	//bottom  
	glVertex3f(0.7f, -0.2f, 0.25f);
	glVertex3f(0.7f, -0.2f, -0.25f);
	glVertex3f(-0.7f, -0.2f, -0.25f);
	glVertex3f(-0.7f, -0.2f, 0.25f);
	glEnd();
}
void People::DrawArmA() {
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, -1.0f, 0.25f);
	glVertex3f(-0.2f, -1.0f, 0.25f);
	//left  
	glVertex3f(0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, 0.2f, -0.25f);
	glVertex3f(0.2f, -1.0f, -0.25f);
	glVertex3f(0.2f, -1.0f, 0.25f);
	//back  
	glVertex3f(0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, -1.0f, -0.25f);
	glVertex3f(0.2f, -1.0f, -0.25f);
	//right  
	glVertex3f(-0.2f, 0.2f, 0.25f);
	glVertex3f(-0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, -1.0f, -0.25f);
	glVertex3f(-0.2f, -1.0f, 0.25f);
	//top  
	glVertex3f(0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, 0.2f, 0.25f);
	//bottom  
	glVertex3f(0.2f, -0.2f, 0.25f);
	glVertex3f(0.2f, -0.2f, -0.25f);
	glVertex3f(-0.2f, -0.2f, -0.25f);
	glVertex3f(-0.2f, -0.2f, 0.25f);

	glEnd();
}
void People::DrawArmB() {
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, -1.0f, 0.25f);
	glVertex3f(-0.2f, -1.0f, 0.25f);
	//left  
	glVertex3f(0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, 0.2f, -0.25f);
	glVertex3f(0.2f, -1.0f, -0.25f);
	glVertex3f(0.2f, -1.0f, 0.25f);
	//back  
	glVertex3f(0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, -1.0f, -0.25f);
	glVertex3f(0.2f, -1.0f, -0.25f);
	//right  
	glVertex3f(-0.2f, 0.2f, 0.25f);
	glVertex3f(-0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, -1.0f, -0.25f);
	glVertex3f(-0.2f, -1.0f, 0.25f);
	//top  
	glVertex3f(0.2f, 0.2f, 0.25f);
	glVertex3f(0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, 0.2f, -0.25f);
	glVertex3f(-0.2f, 0.2f, 0.25f);
	//bottom  
	glVertex3f(-0.2f, -1.0f, 0.25f);
	glVertex3f(0.2f, -1.0f, 0.25f);
	glVertex3f(0.2f, -1.0f, -0.25f);
	glVertex3f(-0.2f, -1.0f, -0.25f);
	glEnd();
}
void People::DrawWrist()
{
	glColor3f(1.0f,0.0f,1.0f);
	glBegin(GL_QUADS);

	//forward
	glVertex3f(0.2f, 0.1f, 0.2f);
	glVertex3f(0.2f, -0.4f, 0.2f);
	glVertex3f(-0.2f, -0.4f, 0.2f);
	glVertex3f(-0.2f, 0.1f, 0.2f);
	//left
	glVertex3f(0.2f, 0.1f, 0.2f);
	glVertex3f(0.2f, 0.1f, -0.2f);
	glVertex3f(0.2f, -0.4f, -0.2f);
	glVertex3f(0.2f, -0.4f, 0.2f);
	//back
	glVertex3f(0.2f, 0.1f, -0.2f);
	glVertex3f(0.2f, -0.4f, -0.2f);
	glVertex3f(-0.2f, -0.4f, -0.2f);
	glVertex3f(-0.2f, 0.1f, -0.2f);
	//right
	glVertex3f(-0.2f, 0.1f, 0.2f);
	glVertex3f(-0.2f, 0.1f, -0.2f);
	glVertex3f(-0.2f, -0.4f, -0.2f);
	glVertex3f(-0.2f, -0.4f, 0.2f);
	//top
	glVertex3f(0.2f, 0.1f, 0.2f);
	glVertex3f(0.2f, 0.1f, -0.2f);
	glVertex3f(-0.2f, 0.1f, -0.2f);
	glVertex3f(-0.2f, 0.1f, 0.2f);
	//bottom
	glVertex3f(0.2f, -0.4f, 0.2f);
	glVertex3f(0.2f, -0.4f, -0.2f);
	glVertex3f(-0.2f, -0.4f, -0.2f);
	glVertex3f(-0.2f, -0.4f, 0.2f);
	glEnd();
}
void People::DrawLegB() {//画大腿
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, -1.25f, 0.255f);
	glVertex3f(-0.3f, -1.25f, 0.255f);
	//left  
	glVertex3f(0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, 0.25f, -0.255f);
	glVertex3f(0.3f, -1.25f, -0.255f);
	glVertex3f(0.3f, -1.25f, 0.255f);
	//back  
	glVertex3f(0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, -0.255f);
	glVertex3f(0.3f, -1.25f, -0.255f);
	//right  
	glVertex3f(-0.3f, 0.25f, 0.255f);
	glVertex3f(-0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, 0.255f);
	//top  
	glVertex3f(0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, 0.25f, 0.255f);
	//bottom  
	glVertex3f(0.3f, -1.25f, 0.255f);
	glVertex3f(0.3f, -1.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, 0.255f);

	glEnd();
}
void People::DrawLegA() {
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, -1.25f, 0.255f);
	glVertex3f(-0.3f, -1.25f, 0.255f);
	//left  
	glVertex3f(0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, 0.25f, -0.255f);
	glVertex3f(0.3f, -1.25f, -0.255f);
	glVertex3f(0.3f, -1.25f, 0.255f);
	//back  
	glVertex3f(0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, -0.255f);
	glVertex3f(0.3f, -1.25f, -0.255f);
	//right  
	glVertex3f(-0.3f, 0.25f, 0.255f);
	glVertex3f(-0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, 0.255f);
	//top  
	glVertex3f(0.3f, 0.25f, 0.255f);
	glVertex3f(0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, 0.25f, -0.255f);
	glVertex3f(-0.3f, 0.25f, 0.255f);
	//bottom  
	glVertex3f(0.3f, -1.25f, 0.255f);
	glVertex3f(0.3f, -1.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, -0.255f);
	glVertex3f(-0.3f, -1.25f, 0.255f);

	glEnd();
}
void People::DrawHead() {
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.6f, 0.6f, 0.35f);
	glVertex3f(0.6f, 0.6f, 0.35f);
	glVertex3f(0.6f, -0.6f, 0.35f);
	glVertex3f(-0.6f, -0.6f, 0.35f);
	//left  
	glVertex3f(0.6f, 0.6f, 0.35f);
	glVertex3f(0.6f, 0.6f, -0.35f);
	glVertex3f(0.6f, -0.6f, -0.35f);
	glVertex3f(0.6f, -0.6f, 0.35f);
	//back  
	glVertex3f(0.6f, 0.6f, -0.35f);
	glVertex3f(-0.6f, 0.6f, -0.35f);
	glVertex3f(-0.6f, -0.6f, -0.35f);
	glVertex3f(0.6f, -0.6f, -0.35f);
	//right  
	glVertex3f(-0.6f, 0.6f, 0.35f);
	glVertex3f(-0.6f, 0.6f, -0.35f);
	glVertex3f(-0.6f, -0.6f, -0.35f);
	glVertex3f(-0.6f, -0.6f, 0.35f);
	//top  
	glVertex3f(0.6f, 0.6f, 0.35f);
	glVertex3f(0.6f, 0.6f, -0.35f);
	glVertex3f(-0.6f, 0.6f, -0.35f);
	glVertex3f(-0.6f, 0.6f, 0.35f);
	//bottom  
	glVertex3f(0.6f, -0.6f, 0.35f);
	glVertex3f(0.6f, -0.6f, -0.35f);
	glVertex3f(-0.6f, -0.6f, -0.35f);
	glVertex3f(-0.6f, -0.6f, 0.35f);
	glEnd();
}
void People::DrawNeck() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.2f, 0.1f, 0.25f);
	glVertex3f(0.2f, 0.1f, 0.25f);
	glVertex3f(0.2f, -0.1f, 0.25f);
	glVertex3f(-0.2f, -0.1f, 0.25f);
	//left  
	glVertex3f(0.2f, 0.1f, 0.25f);
	glVertex3f(0.2f, 0.1f, -0.25f);
	glVertex3f(0.2f, -0.1f, -0.25f);
	glVertex3f(0.2f, -0.1f, 0.25f);
	//back  
	glVertex3f(0.2f, 0.1f, -0.25f);
	glVertex3f(-0.2f, 0.1f, -0.25f);
	glVertex3f(-0.2f, -0.1f, -0.25f);
	glVertex3f(0.2f, -0.1f, -0.25f);
	//right  
	glVertex3f(-0.2f, 0.1f, 0.25f);
	glVertex3f(-0.2f, 0.1f, -0.25f);
	glVertex3f(-0.2f, -0.1f, -0.25f);
	glVertex3f(-0.2f, -0.1f, 0.25f);
	//top  
	glVertex3f(0.2f, 0.1f, 0.25f);
	glVertex3f(0.2f, 0.1f, -0.25f);
	glVertex3f(-0.2f, 0.1f, -0.25f);
	glVertex3f(-0.2f, 0.1f, 0.25f);
	//bottom  
	glVertex3f(0.2f, -0.1f, 0.25f);
	glVertex3f(0.2f, -0.1f, -0.25f);
	glVertex3f(-0.2f, -0.1f, -0.25f);
	glVertex3f(-0.2f, -0.1f, 0.25f);

	glEnd();
}

void People::DrawAnkle()
{
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//forward           
	glVertex3f(-0.2f, 0.25f, 0.5f);
	glVertex3f(0.2f, 0.25f, 0.5f);
	glVertex3f(0.2f, -0.1f, 0.5f);
	glVertex3f(-0.2f, -0.1f, 0.5f);
	//left  
	glVertex3f(0.2f, 0.25f, 0.5f);
	glVertex3f(0.2f, 0.25f, -0.255f);
	glVertex3f(0.2f, -0.1f, -0.255f);
	glVertex3f(0.2f, -0.1f, 0.5f);
	//back  
	glVertex3f(0.2f, 0.25f, -0.255f);
	glVertex3f(-0.2f, 0.25f, -0.255f);
	glVertex3f(-0.2f, -0.1f, -0.255f);
	glVertex3f(0.2f, -0.1f, -0.255f);
	//right  
	glVertex3f(-0.2f, 0.25f, 0.5f);
	glVertex3f(-0.2f, 0.25f, -0.255f);
	glVertex3f(-0.2f, -0.1f, -0.255f);
	glVertex3f(-0.2f, -0.1f, 0.5f);
	//top  
	glVertex3f(0.2f, 0.25f, 0.5f);
	glVertex3f(0.2f, 0.25f, -0.255f);
	glVertex3f(-0.2f, 0.25f, -0.255f);
	glVertex3f(-0.2f, 0.25f, 0.5f);
	//bottom  
	glVertex3f(0.2f, -0.1f, 0.5f);
	glVertex3f(0.2f, -0.1f, -0.255f);
	glVertex3f(-0.2f, -0.1f, -0.255f);
	glVertex3f(-0.2f, -0.1f, 0.5f);

	glEnd();
}


