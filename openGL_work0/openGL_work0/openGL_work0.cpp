#include "openGL_work0.h"
#include<sstream>
#include <fstream>
#include <iostream>
using namespace std;

double change_size = 20;

template<typename T>
Ternary<T>::Ternary(T a, T b, T c) {
	x = a;
	y = b;
	z = c;
}

Surface::Surface(Ternary<int> v, Ternary<int> t, Ternary<int> n) {
	vertex = v;
	texture = t;
	normal = n;
}

/*字符分割函数，s是待分割字符串，sv是分割好之后存储的向量，flag是分割符*/
void split(const string& s, vector<string>& sv, const char flag = ' ') {
	sv.clear();
	istringstream iss(s);
	string temp;

	while (getline(iss, temp, flag)) {
		sv.push_back(temp);
	}
	return;
}

template<typename T>
T stringToNum(const string& str)
{
	istringstream iss(str);
	T num;
	iss >> num;
	return num;
}

ObjLoader::ObjLoader(string filename)
{
	string line;
	fstream f;
	f.open(filename, ios::in);
	if (!f.is_open()) {
		cout << "Something Went Wrong When Opening Objfiles" << endl;
	}

	while (!f.eof()) {
		getline(f, line);//拿到obj文件中一行，作为一个字符串
		vector<string> data;
		split(line, data);
		if (data.size() < 4) {
			continue;
		}
		if (data[0] == "v") {//读入的一行是点的坐标信息
			obj_vertexe.push_back(Ternary<float>(stringToNum<float>(data[2]), stringToNum<float>(data[3]), stringToNum<float>(data[4])));
		}
		else if(data[0] == "vn"){//读入的一行是点的法向量
			obj_normal.push_back(Ternary<float>(stringToNum<float>(data[1]), stringToNum<float>(data[2]), stringToNum<float>(data[3])));
		}
		else if (data[0] == "vt") {//读入的一行是点的纹理坐标
			obj_texture.push_back(Ternary<float>(stringToNum<float>(data[1]), stringToNum<float>(data[2]), stringToNum<float>(data[3])));
		}
		else if (data[0] == "f") {//读入的一行是面的信息
			vector<string> tmp;
			Ternary<int> tmp_surface;
			Ternary<int> tmp_texture;
			Ternary<int> tmp_vn;
			split(data[1], tmp, '/');
			tmp_surface.x = stringToNum<int>(tmp[0]);
			tmp_texture.x = stringToNum<int>(tmp[1]);
			tmp_vn.x = stringToNum<int>(tmp[2]);

			split(data[2], tmp, '/');
			tmp_surface.y = stringToNum<int>(tmp[0]);
			tmp_texture.y = stringToNum<int>(tmp[1]);
			tmp_vn.y = stringToNum<int>(tmp[2]);

			split(data[3], tmp, '/');
			tmp_surface.z = stringToNum<int>(tmp[0]);
			tmp_texture.z = stringToNum<int>(tmp[1]);
			tmp_vn.z = stringToNum<int>(tmp[2]);

			obj_surface.push_back(Surface(tmp_surface, tmp_texture, tmp_vn));
		}
		//cout << "ok" << endl;
	}
	f.close();
}
