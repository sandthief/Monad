#include <MD5.hpp>

using namespace std;

MD5Joint::MD5Joint(string nameIn,int parentIn,Point3D positionIn,Quaternion orientationIn) {
    name        = nameIn;
    parent      = parentIn;
    position    = positionIn;
    orientation = orientationIn;

}

MD5Model::MD5Model() {

}

MD5Model::MD5Model(string filename) {
	load(filename);
}

void MD5Model::load(string filename) {
	int version;
	int numjoints;
    int nummeshes;
    cout << "loading " << filename << endl;
	string line;
	ifstream myfile (filename.c_str());

	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
			if (sscanf (line.c_str(), " MD5Version %d", &version) == 1) {

			}
			else if (sscanf (line.c_str(), " numJoints %d", &numjoints) == 1){

			}
			else if (sscanf (line.c_str(), " numMeshes %d", &nummeshes) == 1){

			}
			else if (strncmp (line.c_str(), "joints {", 8) == 0) {
                for(int i = 0; i < numjoints; i++) {
                    char      name[56];
                    int        parent;
                    Point3D    position;
                    Quaternion orientation;

                    getline (myfile,line);

                    if (sscanf (line.c_str(), "%s %d ( %f %f %f ) ( %f %f %f )",
                                       name, &parent, &position.x,&position.y, &position.z, &orientation.x, &orientation.y, &orientation.z) == 8){
                        orientation.computeW();
                        cout << "creating joint" << endl;
                        skeleton.push_back(MD5Joint(name,parent,position,orientation));
                    }
                }
            }
            else if(strncmp (line.c_str(), "mesh {", 6) == 0) {
                char    shader[56];
                MD5Vertex   vertex;
                MD5Mesh     mesh;
                MD5Triangle triangle;
                MD5Weight   weight;
                int      vert_index;
                int      tri_index;
                int      weight_index;
                getline (myfile,line);
                while(line.find("}") == string::npos) {
                    if(sscanf (line.c_str(), "\tshader %s",shader) == 1) {
                        string unquoted(shader);
                        unquoted = unquoted.substr(1, unquoted.size() - 2);
                        string full = "resources/models/" + unquoted;
                        mesh.texture = TextureManager::get(full);

                    }
	                else if (sscanf (line.c_str(), " vert %d ( %f %f ) %d %d", &vert_index,&vertex.st.x, &vertex.st.y, &vertex.start, &vertex.count) == 5) {
                        mesh.verticies.push_back(vertex);
                    }
                    else if (sscanf (line.c_str(), " tri %d %d %d %d", &tri_index,&triangle.index[0], &triangle.index[1], &triangle.index[2]) == 4) {
                        mesh.triangles.push_back(triangle);
                    }
                    else if (sscanf (line.c_str(), " weight %d %d %f ( %f %f %f )", &weight_index, &weight.joint, &weight.bias,&weight.position.x, &weight.position.y, &weight.position.z) == 6 )                 {
                        mesh.weights.push_back(weight);
                    }
                    getline (myfile,line);
                }

                meshes.push_back(mesh);
            }
		}
		myfile.close();

	}
    else
        cout << "could not load " << filename << endl;
}

void MD5Model::render() {
    // Draw triangles
    for(int m = 0; m < meshes.size(); m++) {
        sf::Texture::bind(&meshes[m].texture);
        glBegin(GL_TRIANGLES);
        for(int t = 0; t < meshes[m].triangles.size(); t++)  {
            MD5Triangle tri     =  meshes[m].triangles[t];
            for(int i = 0; i < 3; i++){

                MD5Vertex   a       =  meshes[m].verticies[tri.index[i]];
                Point3D  finalV(0,0,0);

                for(int v = 0; v < a.count; v++) {

                    MD5Weight   weight  =  meshes[m].weights[a.start + v];
                    MD5Joint    joint   =  skeleton[weight.joint];
                    Point3D  wv      = joint.orientation.rotatePoint(weight.position);
                    finalV.x += (joint.position.x + wv.x) * weight.bias;
	            finalV.y += (joint.position.y + wv.y) * weight.bias;
	            finalV.z += (joint.position.z + wv.z) * weight.bias;
                }

                glTexCoord2f(a.st.x,a.st.y);
                glVertex3f(finalV.x,finalV.z,finalV.y);
                }
        }

        glEnd();
    }
}
