#ifndef OBJ__H
#define OBJ__H

#include <Common.hpp>
#include <Point.hpp>
#include <Model.hpp>
#include <TextureManager.hpp>

class Engine;


class OBJTextCoord {
    public:
        float u,v;

        OBJTextCoord(float,float);
};
class OBJVertex {
    public:
        Point3D position;
};

class OBJFace {
    public:
        int vertexIndecies[3];
        int uvIndecies[3];
        int normalIndecies[3];

        OBJFace(int,int,int,
                int,int,int,
                int,int,int);
};

class OBJGroup {
    public:
        std::string          name;
        std::vector<OBJFace> faces;
        std::string          material;
};

class OBJTexture {
    public:
        std::string name;
        std::string file;
        sf::Texture texture;
        OBJTexture(std::string file);
        bool load(std::string);
};

class OBJMaterial {
    public:
        std::vector<OBJTexture> textures;

};

class Obj : public Model {
    public:
        std::vector<Point3D>      verticies;
        std::vector<OBJTextCoord> uvs;
        std::vector<Point3D>      normals;
        std::vector<OBJGroup>     groups;
        OBJMaterial               material;

	Obj();
	Obj(std::string fileName);
        static void exportToScript();
        virtual void load(std::string filename);
        virtual void render();

};

#endif
