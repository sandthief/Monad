#ifndef __RENDERER_HPP
#define __RENDERER_HPP

#include <Common.hpp>
#include <Color.hpp>
#include <Looper.hpp>

class Renderer {
public:

        float FOV;
        float zNear;
        float zFar;
        Color clearColor;
        int   width,height;

        Renderer(int widthIn,int heightIn);
        void startFrame();
        void endFrame();
};

extern Renderer* renderer;
#endif
