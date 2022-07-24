#include <Common.hpp>
#include <Renderer.hpp>
#include <GUI.hpp>
#include <Color.hpp>

using namespace std;

Renderer::Renderer(int widthIn,int heightIn) {
        width  = widthIn;
        height = heightIn;

        GLenum error = glewInit();
        if (error != GLEW_OK) {
                cout << "Could not initialize GLEW" << endl;
                exit(1);
        }
        FOV        = 45.0f;
        zNear      = 1.0f;
        zFar       = 5000.0f;
        clearColor = Color(0.0f,0.0f,1.0f,0.0f);

        glEnable(GL_TEXTURE_2D);

        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glClearDepth(1.0);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(FOV,width/height,zNear,zFar);
        glMatrixMode(GL_MODELVIEW);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable( GL_BLEND );
        glClearStencil(0);
        glStencilMask(0xFF);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);

        //  glEnable(GL_COLOR_MATERIAL);
        float dif[] = {1.0,1.0,1.0,1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
        float amb[] = {0.2,0.2,0.2,1.0};
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}

void Renderer::startFrame() {
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glLoadIdentity();
}

void Renderer::endFrame() {
        window->display();
}

Renderer* renderer;
