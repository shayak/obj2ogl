#include <string>
#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <vector>
#include <list>
#include <obj2ogl.h>
#include <util.h>

using namespace std;

void Model::loadvnorms()
{
	unsigned int i, j;
	for(i=0; i<facevtx.size(); i++)
	{
		for(j=0; j<facevtx[i].size(); j++)
		{
			int k = facevtx[i][j];
			vnorms[k] = vnorms[k] + facenml[i];
			vnorms[k].normalize();
		}
		//cout<<endl;
	}
}

// shade = flat (face facenml) vs smooth (vertex facenml)
void Model::loadModel(const char *filename)
{
	// open file
	ifstream file;
	file.open(filename);
	
	string line, coordtype;
	vector<int> *T;//exture
	
	// read each line
	while (!file.eof())
	{
		getline(file, line);
		istringstream instr;
		instr.str(line);
		instr>>coordtype;
		double x, y, z;
		
		// load vertices
		if (coordtype.length()==1 && coordtype[0] == 'v')
		{
			instr>>x>>y>>z;
			vertices.push_back(Point3D(x,y,z));
			vnorms.push_back(Vector3D(0,0,0));
		}

		// load textures
		if (coordtype.length()==2 && coordtype[1] == 't')
		{
			instr>>x>>y;
			if (!(instr>>z))
				z = 0.0;
			txtcoords.push_back(Point3D(x,y,z));
		}

		// load facenml
		if (coordtype.length()==2 && coordtype[1] == 'n')
		{
			instr>>x>>y>>z;
			facenml.push_back(Vector3D(x,y,z));

		}

		// load faces
		if (coordtype.length()==1 && coordtype[0] == 'f')
		{
			string s;
			bool t = 0;
			T = new vector<int>;

			Point3D p[3];
			Vector3D norm(0.0, 0.0, 0.0);
			int numverts = 0; // to calc facenml

			vector<int> v;
			facevtx.push_back(v);

			while (instr>>s) // vertex/texture/normal
			{
				int pos = s.find("/");

				if (pos<0) pos = s.length();				
				
				// insert vertex into vertices list
				int vert = atoi(s.substr(0, pos).c_str())-1;
				facevtx[facevtx.size()-1].push_back(vert);
				
				if (numverts < 3)
					p[numverts] = vertices[vert];
				
				s.erase(0, ((int)s.length() < pos+1 ? s.length() : pos+1));

				if (!s.empty()) // texture
				{
					if (s[0]=='/')
						s.erase(0,1);
					else
					{
						t = 1;
						pos = s.find("/");
						if (pos<0) pos = s.length();
						
						// insert texture into texture list
						T->push_back(atoi(s.substr(0,pos).c_str())-1);
						s.erase(0,((int)s.length() < pos+1 ? 
									s.length() : pos+1));
					}
				}

			   	if (numverts == 2)
				{
					norm = (p[1] - p[0]).cross(p[2] - p[1]);
					norm.normalize();
				}

				numverts++;

			} // while(intr>>s)

			if (t)
				facetxt.push_back(*T);
			
			if (norm.length() > 0.5)
				facenml.push_back(norm);

		} // if stmt

	} // read each line

	file.close();

	loadvnorms();
}

void Model::drawModel()
{
	for(unsigned int i=0; i<facevtx.size(); i++)
	{
		if (!shading)
		{
			Vector3D n = facenml[i];
			glNormal3f(n[0], n[1], n[2]);
		}

		if (facevtx[i].size() == 3)
			glBegin(GL_TRIANGLES);
		else if (facevtx[i].size() == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);
			
			for(unsigned int j=0; j<facevtx[i].size(); j++)
			{
				int k = facevtx[i][j];
			
				if (shading)
				{
					Vector3D n = vnorms[k];
					glNormal3f(n[0], n[1], n[2]);
				}

				glVertex3f(vertices[k][0],
							vertices[k][1],
							 vertices[k][2]);
			}
			
			glEnd();
	}
}
