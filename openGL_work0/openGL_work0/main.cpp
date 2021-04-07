#include "openGL_work0.h"
#include "ArcBall.h"

using namespace std;
//模型路径
string filePath = "teapot.obj";

//相机
Ternary<float> camera;
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
float curTransX;
float curTransY;//记录当前总体的位置
float recordX;
float recordY;
float intervalX;
float intervalY;
ObjLoader objModel = ObjLoader(filePath);
float times = 1;
GLfloat timesCounter = 1;
GLfloat curwidth;
GLfloat curheight;
GLfloat storeX;
GLfloat storeY;
GLfloat matScal[16];//当前变换矩阵
GLfloat matbegin[16];//起始处的变换矩阵
GLfloat curChange[4][4];
GLfloat multi[16];

GLfloat t;
int refreshMills = 60;
//GLfloat iden[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
float nx; float ny; float nz;//得到转轴的向量
struct Quaternion
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;

};
Quaternion froms;
Quaternion tos;

Quaternion convertToQuaternion(GLfloat mat[])
{
	Quaternion temp;
	GLfloat m[4][4];
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			m[j][i] = mat[j * 4 + i];
		}
	}
	float tr, s, q[4];
	int i, j, k;
	int nxt[3] = { 1,2,0 };
	tr = m[0][0] + m[1][1] + m[2][2];//对角线元素和
	if (tr > 0.0)
	{
		s = sqrt(tr + 1.0);
		temp.w = s / 2.0;
		s = 0.5 / s;
		temp.x = (m[1][2] - m[2][1]) * s;
		temp.y = (m[2][0] - m[0][2]) * s;
		temp.z = (m[0][1] - m[1][0]) * s;

	}
	else
	{
		i = 0;
		if (m[1][1] > m[0][0])i = 1;
		if (m[2][2] > m[i][i])i = 2;
		j = nxt[i];
		k = nxt[j];
		s = sqrt((m[i][i] - (m[j][j] + m[k][k])) + 1.0);
		q[i] = s * 0.5;
		if (s != 0.0)
		{
			s = 0.5 / s;
		}
		q[3] = (m[j][k] - m[k][j]) * s;
		q[j] = (m[i][j] + m[j][i]) * s;
		q[k] = (m[i][k] + m[k][i]) * s;
		temp.x = q[0];
		temp.y = q[1];
		temp.z = q[2];
		temp.w = q[3];
	}
	return temp;

}
void QuaternionToMatrix(Quaternion q)
{
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
	x2 = q.x + q.x; y2 = q.y + q.y;
	z2 = q.z + q.z;
	xx = q.x * x2; xy = q.x * y2; xz = q.x * z2;
	yy = q.y * y2; yz = q.y * z2;
	zz = q.z * z2;
	wx = q.w * x2; wy = q.w * y2; wz = q.w * z2;

	curChange[0][0] = 1.0 - (yy + zz); curChange[1][0] = xy - wz;
	curChange[2][0] = xz + wy; curChange[3][0] = 0.0;
	curChange[0][1] = xy + wz; curChange[1][1] = 1.0 - (xx + zz);
	curChange[2][1] = yz - wx; curChange[3][1] = 0.0;

	curChange[0][2] = xz - wy; curChange[1][2] = yz + wx;
	curChange[2][2] = 1.0 - (xx + yy); curChange[3][2] = 0.0;

	curChange[0][3] = 0; curChange[1][3] = 0;
	curChange[2][3] = 0; curChange[3][3] = 1;
	int c = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			multi[c] = curChange[i][j];
			c++;
		}
	}
}
Quaternion QuatMul(Quaternion q1, Quaternion q2)
{
	Quaternion res;
	float A, B, C, D, E, F, G, H;
	A = (q1.w + q1.x) * (q2.w + q2.x);
	B = (q1.z - q1.y) * (q2.y - q2.z);
	C = (q1.w - q1.x) * (q2.y + q2.z);
	D = (q1.y = q1.z) * (q2.w - q2.x);
	E = (q1.x + q1.z) * (q2.x + q2.y);
	F = (q1.x - q1.z) * (q2.x - q2.y);
	G = (q1.w + q1.y) * (q2.w - q2.z);
	H = (q1.w - q1.y) * (q2.w + q2.z);
	res.w = B + (-E - F + G + H) / 2;
	res.x = A - (E + F + G + H) / 2;
	res.y = C + (E - F + G - H) / 2;
	res.z = D + (E - F - G + H) / 2;
	return res;
}
Quaternion SLERP(Quaternion from, Quaternion to, float t)
{
	Quaternion res;
	float tol[4];
	double omega, cosom, sinom, scale0, scale1;
	cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
	//得到cos角度
	if (cosom < 0.0)
	{
		cosom = -cosom;
		tol[0] = -to.x;
		tol[1] = -to.y;
		tol[2] = -to.z;
		tol[3] = -to.w;

	}
	else
	{
		tol[0] = to.x;
		tol[1] = to.y;
		tol[2] = to.z;
		tol[3] = to.w;
	}
	float DELTA = 0.0005f;
	if ((1 - cosom) > DELTA)
	{
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		scale0 = 1.0 - t;
		scale1 = t;
	}
	res.x = scale0 * from.x + scale1 * tol[0];
	res.y = scale0 * from.y + scale1 * tol[1];
	res.z = scale0 * from.z + scale1 * tol[2];
	res.w = scale0 * from.w + scale1 * tol[3];
	return res;

}
//初始化
void init() {
	camera.x = -20;
	camera.y = 30;
	camera.z = 20;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ObjLoader");

	//材质反光性设置
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
	GLfloat mat_shininess[] = { 50.0 };               //高光指数
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //灯位置(1,1,1), 最后1-开关
	GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数

	glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
	glShadeModel(GL_SMOOTH);           //多变性填充模式

									   //材质属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	//灯光设置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

	glEnable(GL_LIGHTING);   //开关:使用光
	glEnable(GL_LIGHT0);     //打开0#灯
	glEnable(GL_DEPTH_TEST); //打开深度测试
}

void Draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//开始绘制
	for (int i = 0; i < objModel.obj_surface.size(); i++) {
		glBegin(GL_TRIANGLES);

		Ternary<float> normal = objModel.obj_normal[objModel.obj_surface[i].normal.x - 1];
		glNormal3f(normal.x, normal.y, normal.z);
		Ternary<float> texture = objModel.obj_texture[objModel.obj_surface[i].texture.x - 1];
		glTexCoord3f(texture.x, texture.y, texture.z);
		Ternary<float> vertex = objModel.obj_vertexe[objModel.obj_surface[i].vertex.x - 1];
		glVertex3f(vertex.x, vertex.y, vertex.z);

		normal = objModel.obj_normal[objModel.obj_surface[i].normal.y - 1];
		glNormal3f(normal.x, normal.y, normal.z);
		texture = objModel.obj_texture[objModel.obj_surface[i].texture.y - 1];
		glTexCoord3f(texture.x, texture.y, texture.z);
		vertex = objModel.obj_vertexe[objModel.obj_surface[i].vertex.y - 1];
		glVertex3f(vertex.x, vertex.y, vertex.z);

		normal = objModel.obj_normal[objModel.obj_surface[i].normal.z - 1];
		glNormal3f(normal.x, normal.y, normal.z);
		texture = objModel.obj_texture[objModel.obj_surface[i].texture.z - 1];
		glTexCoord3f(texture.x, texture.y, texture.z);
		vertex = objModel.obj_vertexe[objModel.obj_surface[i].vertex.z - 1];
		glVertex3f(vertex.x, vertex.y, vertex.z);

		glEnd();
	}
	glFlush();
}

void reshape(int w, int h)
{
	float size = 100;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-size, size, -size * (GLfloat)h / (GLfloat)w, size*(GLfloat)h / (GLfloat)w, -size, size);
	else
		glOrtho(-size * (GLfloat)w / (GLfloat)h, size*(GLfloat)w / (GLfloat)h, -size, size, -size, size);

	//设置模型参数--几何体参数
	gluLookAt(camera.x, camera.y, camera.z, 0, 20, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

float past_x, past_y;
int get_pos = 0;




default_random_engine e;
uniform_real_distribution<double> u(0, 1);
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

		glColor3f(u(e), u(e), u(e));
		Draw();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		get_pos = 1;
		past_x = x;
		past_y = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		get_pos = 0;
	}

}
void mouse_move(int x, int y)
{
	float speed = 0.3;
	if (get_pos == 1)
	{
		glRotatef(speed*(x - past_x), 0, 1, 0);
		glRotatef(speed*(y - past_y), 1, 0, 0);
		Draw();
		past_x = x;
		past_y = y;
	}
}
void display2()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (idleBegin)
	{

		curTransX += intervalX;
		curTransY += intervalY;
		Quaternion cur = SLERP(froms, tos, t);
		QuaternionToMatrix(cur);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScalef(timesCounter, timesCounter, timesCounter);//假设并不改变图像
		glTranslatef(curTransX, curTransY, 0);
		glMultMatrixf(multi);
		Draw();
		//re.draw();

		glutSwapBuffers();
	}
	t += 0.01f;
	if (t > 1)
	{
		idleBegin = false;
		return;
	}

}
void KeyBoards(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q'://放大
		times = 0.008f + 1;
		timesCounter += 0.008f;
		glutPostRedisplay();
		break;
	case 'e'://缩小
		times = -0.008f + 1;
		timesCounter -= 0.008f;
		glutPostRedisplay();
		break;
	case 'a'://记录位置以及状态
		needRecord = true;
		glGetFloatv(GL_MODELVIEW_MATRIX, matScal);//得到当前局部坐标的旋转矩阵

		recordX = curTransX;
		recordY = curTransY;
		matScal[0] = matScal[0] / timesCounter; matScal[1] = matScal[1] / timesCounter; matScal[2] = matScal[2] / timesCounter;
		matScal[4] = matScal[4] / timesCounter; matScal[5] = matScal[5] / timesCounter; matScal[6] = matScal[6] / timesCounter;
		matScal[8] = matScal[8] / timesCounter; matScal[9] = matScal[9] / timesCounter; matScal[10] = matScal[10] / timesCounter;
		matScal[12] = 0; matScal[13] = 0; matScal[14] = 0; matScal[15] = 0;
		tos = convertToQuaternion(matScal);
		break;
	case 'd'://开始绘制运动曲线
		idleBegin = true;
		glGetFloatv(GL_MODELVIEW_MATRIX, matbegin);//得到局部坐标的旋转矩阵
		matbegin[0] /= timesCounter; matbegin[1] /= timesCounter; matbegin[2] /= timesCounter;
		matbegin[4] /= timesCounter; matbegin[5] /= timesCounter; matbegin[6] /= timesCounter;
		matbegin[8] /= timesCounter; matbegin[9] /= timesCounter; matbegin[10] /= timesCounter;
		matbegin[12] = 0; matbegin[13] = 0; matbegin[14] = 0; matbegin[15] = 0;
		froms = convertToQuaternion(matbegin);
		intervalX = (recordX - curTransX) / 100;
		intervalY = (recordY - curTransY) / 100;
		t = 0;
		//glutPostRedisplay();
	}
}
void idle(int value)
{
	if (idleBegin)
	{
		//reshape(curwidth, curheight);
		display2();
	}
	glutTimerFunc(refreshMills, idle, 0);
}
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glScalef(times, times, times);
	glTranslatef(cameraDistanceX, cameraDistanceY, 0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	Draw();
	//re.draw();

	glutSwapBuffers();
	//angle += 0.02f;

}
void MouseMotion(int x, int y)
{
	cameraAngleX = cameraAngleY = 0;
	cameraDistanceX = cameraDistanceY = 0;
	cameraDistanceZ = 0;
	//mouseLeftDown = false;
	if (mouseRightDown)
	{
		cameraAngleY += (x - mouseX) * 0.1f;
		cameraAngleX += (y - mouseY) * 0.1f;
		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
	if (mouseLeftDown)
	{
		cameraDistanceX = (x - mouseX) * 0.08f;
		cameraDistanceY = -(y - mouseY) * 0.08f;
		curTransX += cameraDistanceX;
		curTransY += cameraDistanceY;
		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}
}
void MouseFunc(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	times = 1;
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
int main(int argc, char* argv[])
{
	t = 0;
	curTransX = 0;
	curTransY = 0;
	glutInit(&argc, argv);
	init();	
	glEnable(GL_COLOR_MATERIAL);
	glutDisplayFunc(&display);
	glutReshapeFunc(&reshape);
	glutMouseFunc(&MouseFunc);
	glutMotionFunc(&MouseMotion);
	glutKeyboardFunc(KeyBoards);
	glutTimerFunc(0, idle, 0);
	glutMainLoop();
	return 0;
}