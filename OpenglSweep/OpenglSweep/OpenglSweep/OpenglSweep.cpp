// OpenglSweep.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <vector>
#include <GL/glut.h>
#include <Windows.h>
#include <math.h>  
#define PI 3.14159265
float mouseX, mouseY;
bool mouseRightDown;

float cameraAngleX;
float cameraAngleY;
bool mouseDown = false;
void DrawBezier(int type);
void display();

class Point2
{
public:
	double x, y;
	Point2(double _x, double _y) {
		x = _x;
		y = _y;
	}
	Point2() {}
};

class Point3
{
public:
	double x, y, z;
	Point3(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Point3(Point2 bef)
	{
		x = bef.x;
		y = bef.y;
		z = 0;
	}
	Point3() {}
};
struct face
{
	Point3 a;
	Point3 b;
	Point3 c;
	face(Point3 _a, Point3 _b, Point3 _c) :a(_a), b(_b), c(_c) {}
};
struct Mmatrix
{
	Point3 xs;
	Point3 ys;
	Point3 zs;
	Mmatrix(Point3 x, Point3 y, Point3 z) { xs = x; ys = y; zs = z; }
};
std::vector<face> faces;//旋转曲面上的三角形面片
std::vector<Point3> points;//profile点
std::vector<Point3> BezierPoint;//prpfile曲线
std::vector<Point3> sweepPoint;//sweep曲线
//计算转置
Mmatrix trans(Mmatrix a)
{
	double temp = a.xs.y;
	a.xs.y = a.ys.x;
	a.ys.x = temp;
	temp = a.xs.z;
	a.xs.z = a.zs.x;
	a.zs.x = temp;
	temp = a.ys.z;
	a.ys.z = a.zs.y;
	a.zs.y = temp;
	return a;
}
Point3 ADD(Point3 a, Point3 b)
{
	return Point3(a.x + b.x, a.y + b.y, a.z + b.z);
}
Point3 CoorTrans(Mmatrix m, Point3 b)
{
	double x = m.xs.x * b.x + m.xs.y * b.y + m.xs.z * b.z;
	double y = m.ys.x * b.x + m.ys.y * b.y + m.ys.z * b.z;
	double z = m.zs.x * b.x + m.zs.y * b.y + m.zs.z * b.z;
	return Point3(x, y, z);
}
void readCurves()
{
	points.push_back(Point2(0, -0.25)); 
	points.push_back(Point2(0.55, -0.55));
	points.push_back(Point2(0.25, 0.0));
	points.push_back(Point2(0.55, 0.55));
	
	points.push_back(Point2(-0.55, 0.55));
	points.push_back(Point2(-0.25, 0.0));
	points.push_back(Point2(0, -0.25));
	DrawBezier(0);//存入profile曲线

	points.clear();
	points.push_back(Point3(-1.427273, 0.424545, 0.929339));
	points.push_back(Point3(-1.767273, -1.585455 ,0.371157));
	points.push_back(Point3(0.912727, -1.585455, -0.278843));
	points.push_back(Point3(1.922727, -0.255455 ,-0.080661));
	
//	points.push_back(Point3(1.582727, 1.374545, -1.050661));
	points.push_back(Point3(0.212727,1.034545, -1.260661));
	points.push_back(Point3(-1.097273, 1.444545 ,0.259339));
	points.push_back(Point3(-1.427273, 0.424545 ,0.9293391));

/*	points.push_back(Point3(-1.767273, -1.585455 ,0.371157));
	points.push_back(Point3(0.912727, -1.585455, -0.278843));
	*/
	DrawBezier(1);

}
Point3 Normalize(Point3 cur)
{
	double dis = (double)sqrt(cur.x * cur.x + cur.y * cur.y + cur.z * cur.z);
	return Point3(cur.x / dis, cur.y / dis, cur.z / dis);
}
//向量叉乘，假设此处输入的Point3为向量
Point3 Xmulti(Point3 u, Point3 v)
{
	double xn = u.y * v.z - u.z * v.y;
	double yn = u.z * v.x - u.x * v.z;
	double zn = u.x * v.y - u.y * v.x;
	return Point3(xn, yn, zn);
}
Point3 recT; Point3 recB; Point3 recN;
void DrawSweep()
{
	int i = 0;//从sweep第一个点出发
	Point3 curPoint = sweepPoint[i];
	Point3 nextPoint = sweepPoint[i + 1];
	//得到当前的坐标系
	Point3 curT = Normalize(Point3((nextPoint.x - curPoint.x) / 2, (nextPoint.y - curPoint.y) / 2, (nextPoint.z - curPoint.z) / 2));
 	Point3 iniB(0, 1, 0);//假设初始的B在y轴上
	Point3 iniN;
	Point3 preN;
	while (true)
	{
		preN = iniN;
		iniN = Normalize(Xmulti(iniB, curT));
		iniB = Normalize(Xmulti(curT, iniN));
		double va = (preN.x - iniN.x) * (preN.x - iniN.x) + (preN.y - iniN.y) * (preN.y - iniN.y) + (preN.z - iniN.z) * (preN.z - iniN.z);
		if (va < 0.01)
		{
			break;
		}
	}
	recT = curT; recN = iniN; recB = iniB;
	while (i < sweepPoint.size())
	{
		//得到下一面的坐标系
		Point3 nnextPoint;
		if (i + 1 == sweepPoint.size())
		{
			
			nnextPoint = sweepPoint[1];
		}
		else
		{
			if (i + 2 >= sweepPoint.size())
			{
			
				nnextPoint = sweepPoint[0];
			}
			else
			{
				nnextPoint = sweepPoint[i + 2];
			}
		}
		Point3 T = Normalize(Point3((nnextPoint.x - nextPoint.x) / 2, (nnextPoint.y - nextPoint.y) / 2, (nnextPoint.z - nextPoint.z) / 2));
		Point3 B=iniB;//假设两个坐标系的变化不大
		Point3 N; Point3 ppreN;
		

		while (true)
		{
			ppreN = N;
			N = Normalize(Xmulti(B, T));
			B = Normalize(Xmulti(T, N));
			
			double va = (ppreN.x - N.x) * (ppreN.x - N.x) + (ppreN.y - N.y) * (ppreN.y - N.y) + (ppreN.z - N.z) * (ppreN.z - N.z);
			if (va < 0.01)
			{
				break;
			}
		}
		if (i + 1 == sweepPoint.size())
		{
			N = recN;
			T = recT;
			B = recB;
		}
		for (int j = 0; j < BezierPoint.size(); j++)//遍历两个坐标下的点，生成三角形网格
		{
			//得到两个转置矩阵
			Mmatrix curm=trans(Mmatrix(iniN,iniB,curT));
			Mmatrix m=trans(Mmatrix(N,B,T));
			Point3 curr = ADD(curPoint,CoorTrans(curm, BezierPoint[j]));
			Point3 nextr = ADD(nextPoint,CoorTrans(m, BezierPoint[j]));
			Point3 currup; Point3 nextdown;
			if (j + 1 < BezierPoint.size())
			{
				currup =ADD(curPoint, CoorTrans(curm, BezierPoint[j + 1]));
			}
			else
			{
				currup = ADD(curPoint,CoorTrans(curm, BezierPoint[0]));
			}
			if (j - 1 < 0)
			{
				nextdown = ADD(nextPoint,CoorTrans(m, BezierPoint[BezierPoint.size()-1]));
			}
			else
			{
				nextdown =ADD(nextPoint, CoorTrans(m, BezierPoint[j - 1]));
			}
			
			faces.push_back(face(curr, nextr, currup));
			faces.push_back(face(nextr, curr, nextdown));
			
		}
//		display();
//		Sleep(1);
		//本轮循环结束
		curT = T;
		iniB = B;
		iniN = N;
		curPoint = nextPoint;
		nextPoint = nnextPoint;
		i++;
	}
}
Point3 GetBeZier(Point3 p0, Point3 p1, Point3 p2, Point3 p3, double t)
{
	double x;
	x = p0.x + (-3 * p0.x + 3 * p1.x) * t + (3 * p0.x - 6 * p1.x + 3 * p2.x) * t * t + (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t * t * t;
	double y;
	y = p0.y + (-3 * p0.y + 3 * p1.y) * t + (3 * p0.y - 6 * p1.y + 3 * p2.y) * t * t + (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t * t * t;
	double z;
	z = p0.z + (-3 * p0.z + 3 * p1.z) * t + (3 * p0.z - 6 * p1.z + 3 * p2.z) * t * t + (-p0.z + 3 * p1.z - 3 * p2.z + p3.z) * t * t * t;
	return Point3(x, y,z);

}

void DrawBezier(int type)//type=0,BezierPoint
{
	int i = 0;
	Point3 preP;

	//glBegin(GL_LINES);
	while (i < points.size())
	{

		Point3 p0 = points[i]; preP = p0;
		i++;
		if (i >= points.size())
		{
			break;
		}
		Point3 p1 = points[i];
		i++;
		if (i >= points.size())
		{
			break;
		}
		Point3 p2 = points[i];
		i++;

		if (i >= points.size())
		{
			break;
		}
		else
		{
			Point3 p3 = points[i];
			for (float t = 0.0;;)
			{
				if (t > 1.00)
				{
					break;
					printf("in");
				}
				Point3 d = GetBeZier(p0, p1, p2, p3, t);

				if (type == 0)
				{
					BezierPoint.push_back(d);//存储旋转曲线上的点
				}
				else
				{
					sweepPoint.push_back(d);
				}
			//	glVertex3d(preP.x, preP.y,preP.z);
			//	glVertex3d(d.x, d.y,d.z);
				preP = d;
				t = t + 0.01;
			}
		
		}
	}
	//glEnd();
}

void Draw()
{

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < sweepPoint.size()-1; i++)
	{
		glVertex3f(sweepPoint[i].x, sweepPoint[i].y, sweepPoint[i].z);
		glVertex3f(sweepPoint[i+1].x, sweepPoint[i+1].y, sweepPoint[i+1].z);
	}
/*	for (int i = 0; i < BezierPoint.size() - 1; i++)
	{
		glVertex3f(BezierPoint[i].x, BezierPoint[i].y, BezierPoint[i].z);
		glVertex3f(BezierPoint[i + 1].x, BezierPoint[i + 1].y, BezierPoint[i + 1].z);
	}*/
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.749, 1.0);
	for (int i = 0; i < faces.size(); i++) {

		face cur = faces[i];
		Point3 u(cur.b.x - cur.a.x, cur.b.y - cur.a.y, cur.b.z - cur.a.z);
		Point3 v(cur.c.x - cur.b.x, cur.c.y - cur.b.y, cur.c.z - cur.b.z);
		double xn = u.y * v.z - u.z * v.y;
		double yn = u.z * v.x - u.x * v.z;
		double zn = u.x * v.y - u.y * v.x;
///		glNormal3f(xn, yn, zn);
		glVertex3f(cur.a.x, cur.a.y, cur.a.z);
	//	glNormal3f(xn, yn, zn);
		glVertex3f(cur.b.x, cur.b.y, cur.b.z);
//		glNormal3f(xn, yn, zn);
		glVertex3f(cur.c.x, cur.c.y, cur.c.z);

	}
	glEnd();
}
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glColor3d(1.0, 0.0, 0.0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	//DrawBezier(1);
	Draw();
	glutSwapBuffers();
}
void reshape(GLsizei width, GLsizei height)
{
	if (height == 0)height = 1;
	float size = 2;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.5, 2.5, -2.5, 2.5, 2.5, -2.5);

}
void MouseMotion(int x, int y)
{
	cameraAngleX = cameraAngleY = 0;
	//mouseLeftDown = false;
	if (mouseRightDown)
	{
		cameraAngleY += (x - mouseX) * 0.1f;
		cameraAngleX += (y - mouseY) * 0.1f;
		mouseX = x;
		mouseY = y;
		glutPostRedisplay();
	}

}
void MouseFunc(int button, int state, int x, int y)
{

	mouseX = x;
	mouseY = y; mouseRightDown = false;
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_RIGHT_BUTTON)
		{
			mouseRightDown = true;
		}
		else
		{
			mouseDown = true;
		}

	}
	else
	{
		if (state == GLUT_UP)
		{
			if (button == GLUT_RIGHT_BUTTON)
			{
				mouseRightDown = false;
			}
			//		mouseDown = false;
		}
	}

}
int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);

	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("OpenGL test1");

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
	glPointSize(5);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotion);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);


	GLfloat light_position[] = { 3,3, 3, 1.0 };
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	readCurves();
	DrawSweep();
	glutMainLoop();
	return 0;

}
