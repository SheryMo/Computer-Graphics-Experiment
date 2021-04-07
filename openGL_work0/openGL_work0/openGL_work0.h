#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <vector>
#include <string>
#include <random>

using namespace std;

template<typename T>
class Ternary {
public:
	T x, y, z;
	Ternary() {};
	Ternary(T a, T b, T c);
};

class Surface {
public:
	Ternary<int> vertex;
	Ternary<int> texture;
	Ternary<int> normal;
	Surface(Ternary<int>, Ternary<int>, Ternary<int>);
};

class ObjLoader {
	public:
		vector<Ternary<float>> obj_vertexe;
		vector<Ternary<float>> obj_texture;
		vector<Ternary<float>> obj_normal;
		vector<Surface> obj_surface;
		ObjLoader(string filename);//¹¹Ôìº¯Êý
};