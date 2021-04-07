#pragma once

#include <Windows.h>
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h> 
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <cstdio>  
#include <iostream>

class Ternary {
public:
	float x, y, z;
	Ternary(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
};

class People {
public:
	float leftArma,//���۸첲��ת���ٶ�
		leftArmb, //��С�۸첲��ת���ٶ�
		rightArma, //�Ҵ�۸첲��ת���ٶ�
		rightArmb, //��С�۸첲��ת���ٶ�
		leftLegb, //����ȸ첲��ת���ٶ�
		rightLegb, //��С�ȸ첲��ת���ٶ�
		leftLega, //�Ҵ��ȸ첲��ת���ٶ�
		rightLega = 0;//��С�ȸ첲��ת���ٶ�
	float leftWrist = 0;
	float rightWrist = 0;
	float la, ra, ll, rl = 0;
	float laa , raa = 0;
	float a = 0.2,
		b = 0.1,
		angle = 0;
	const float angle1 = 0.2;
	const float angle2 = 0.1;
	void initAngle();
	void InitGL(int Width, int Height);
	void DrawBody();
	void DrawShoulder();
	void DrawHip();
	void DrawArmA();
	void DrawArmB();
	void DrawWrist();
	void DrawLegA();
	void DrawLegB();
	void DrawHead();
	void DrawNeck();
	void DrawAnkle();
};