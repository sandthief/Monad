#include <Obj.hpp>
#include <Math.hpp>

using namespace std;


OBJTexture::OBJTexture(std::string file) {
    name = file;
}
bool OBJTexture::load(std::string file) {
cout << "\tloading " << file << endl;
	texture = TextureManager::get(file);
}


OBJTextCoord::OBJTextCoord(float uIn,float vIn) {
    u = uIn;
    v = vIn;
}
OBJFace::OBJFace(int vertexIn1,int uvIn1,int normalIn1,
                 int vertexIn2,int uvIn2,int normalIn2,
                 int vertexIn3,int uvIn3,int normalIn3) {
     vertexIndecies[0] = vertexIn1;
     vertexIndecies[1] = vertexIn2;
     vertexIndecies[2] = vertexIn3;

     uvIndecies[0] = uvIn1;
     uvIndecies[1] = uvIn2;
     uvIndecies[2] = uvIn3;

     normalIndecies[0] = normalIn1;
     normalIndecies[1] = normalIn2;
     normalIndecies[2] = normalIn3;

}

Obj::Obj() {
}

Obj::Obj(string fileName) {
	load(fileName);
}

void Obj::load(string fileName) {

    string line;
    ifstream objfile(fileName);
    if(objfile.is_open()) {
        OBJGroup currentGroup;
        char     currentMaterial[56];
        while ( getline (objfile,line) ) {
            float x,y,z,u,v;
            int vertexIndecies[3];
            int uvIndecies[3];
            int normalIndecies[3];
            char group[56];
            char materialName[56];
            if(sscanf (line.c_str(), "usemtl %s", currentMaterial) == 1){

            }
            if(sscanf (line.c_str(), "mtllib %s", materialName) == 1) {
		string fullPath = "resources/models/" + string(materialName);
		ifstream mtlfile(fullPath.c_str());
		if(mtlfile.is_open()) {
		    char name[56];
		    string mtlline;

		    while ( getline (mtlfile,mtlline) ) {
			if (sscanf (mtlline.c_str(), "newmtl %s", name) == 1) {
			    OBJTexture texture(name);
			    material.textures.push_back(texture);
			}
		       else if (sscanf (mtlline.c_str(), " map_Kd %s", name) == 1) {
			    material.textures[material.textures.size() - 1].load(string("resources/models/") + name);
			}
		    }
		    mtlfile.close();
		}
            }
            else if (sscanf (line.c_str(), "v %f %f %f", &x,&y,&z) == 3) {
				verticies.push_back(Point3D(x,y,z));
			}
            else if (sscanf (line.c_str(), "vn %f %f %f", &x,&y,&z) == 3) {
				normals.push_back(Point3D(x,y,z));
			}
            else if (sscanf (line.c_str(), "vt %f %f", &u,&v) == 2) {
				uvs.push_back(OBJTextCoord(u,v));
			}
            else if (sscanf (line.c_str(), "g %s", group) == 1) {
				groups.push_back(OBJGroup());
                groups[groups.size() - 1].material = currentMaterial;
                groups[groups.size() - 1].name     = group;

	    }

            else if (sscanf (line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d ", &vertexIndecies[0],&uvIndecies[0],&normalIndecies[0],
                                                                            &vertexIndecies[1],&uvIndecies[1],&normalIndecies[1],
                                                                            &vertexIndecies[2],&uvIndecies[2],&normalIndecies[2]) == 9) {
				groups[groups.size() - 1].faces.push_back(OBJFace(vertexIndecies[0],uvIndecies[0],normalIndecies[0],
                                                                  vertexIndecies[1],uvIndecies[1],normalIndecies[1],
                                                                  vertexIndecies[2],uvIndecies[2],normalIndecies[2]));
			}

        }
        objfile.close();

    }
    else {
        cout << "could not load " << fileName << endl;

    }
}

void Obj::render() {
    for(int g = 0; g < groups.size(); g++) {
       if(groups[g].material != "collision") {
        	   for(int t = 0; t < material.textures.size(); t++)
        		    if(material.textures[t].name == groups[g].material) {
                                    sf::Texture::bind(&material.textures[t].texture);
                }

        		for(int f = 0; f < groups[g].faces.size(); f++) {
                                        glBegin(GL_TRIANGLES);
                                        OBJFace      face  = groups[g].faces[f];
                                        //Point3D        n   = normals[face.normalIndecies[0]-1];
                                        //glNormal3f(n.x,n.y,n.z);
                                        OBJTextCoord uv1   = uvs[face.uvIndecies[0]-1];
                                        Point3D        a   = verticies[face.vertexIndecies[0]-1];
                                        //glNormal3f(n.x,n.y,n.z);
                                        OBJTextCoord uv2   = uvs[face.uvIndecies[1]-1];
                                        Point3D        b   = verticies[face.vertexIndecies[1]-1];

                                        //glNormal3f(n.x,n.y,n.z);
                                        OBJTextCoord uv3   = uvs[face.uvIndecies[2]-1];
                                        Point3D        c   = verticies[face.vertexIndecies[2]-1];
                                        Vector N = normalize(cross(b - a, c - a));
                                        glNormal3f(N.x,N.y,N.z);
                                        glTexCoord2f(uv1.u,1.0f - uv1.v);
                                        glVertex3f(a.x,a.y,a.z);

                                        glTexCoord2f(uv2.u,1.0f - uv2.v);
                                        glVertex3f(b.x,b.y,b.z);

                                        glTexCoord2f(uv3.u,1.0f - uv3.v);
                                        glVertex3f(c.x,c.y,c.z);
                                        glEnd();

        		}
          }
        }
}
