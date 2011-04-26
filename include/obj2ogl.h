#ifndef _OBJ_INCLUDED_
#define _OBJ_INCLUDED_

#include <vector>
#include <list>
#include <GL/glut.h>
#include <util.h>

class Face
{

public:
	Face() {};
	void add(int);
	void add(int, int);
	void add(int, int, int);

	std::list<int>::iterator vbegin();
	std::list<int>::iterator tbegin();
	std::list<int>::iterator nbegin();

	std::list<int>::iterator vend();
	std::list<int>::iterator tend();
	std::list<int>::iterator nend();

private:
	std::list<int> vtx; // vertices index
	std::list<int> txt; // textures index
	Vector3D nml; // normal index
};

class Model
{

public:

	Model() {shading = 0;}
	Model(const char *fname) { shading=0; loadModel(fname); }
	Model(const char *fname, int sh) { shading=sh; loadModel(fname); }

	void loadModel(const char *);
	void drawModel();
	void setShading(int sh) {shading = sh;}

private:
	int shading; // 0 = flat, 1 = smooth

	//vertices
	std::vector<Point3D> vertices;
	std::vector<Point3D> txtcoords;
	std::vector<Vector3D> vnorms;

	// faces
	std::vector< std::vector<int> > facevtx; // vertices
	std::vector< std::vector<int> > facetxt; // textures
	std::vector<Vector3D> facenml; // face normals

	// methods
	void loadvnorms();
};

#endif
