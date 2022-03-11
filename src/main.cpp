#include <iostream>

#define GLEW_STATIC
#include "glew-2.1.0\include\GL\glew.h"
#include "glfw-3.3.6\include\GLFW\glfw3.h"

#include "shaders.hpp"
#include "textures.hpp"
#include "transforms.hpp"

float vertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};


void root_resize_callback(GLFWwindow* window, int width, int height) {
    if(width==height){
        glViewport(0,0,width,height);
    } else if (width<height) {
        glViewport(0,0,height,height); //#TODO make appear that is anchored to top left, extends past bottom/left
    } else if (width>height) {
        glViewport(0,0,width,width);
    }
    
}

int translateDir=transforms::NONE; //its int because | or operator returns int and wont cast automatically
int rotateDir=transforms::NONE; //reset these back to NONE every frame

void keyCallback(GLFWwindow* window,int key,int scancode,int action, int mods) { //idk what a scancode is 

    if(action==GLFW_PRESS){
        switch(key){ //i dont have the time to learn howto implement custom operators, and certainly not for making it for a enum, which isnt even a class type

            case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window,true);break;

            case GLFW_KEY_ENTER:
            transforms::reset(); break;

            case GLFW_KEY_W:
            rotateDir|=transforms::LEFT;break;
            case GLFW_KEY_S:
            rotateDir|=transforms::RIGHT;break;
            case GLFW_KEY_A:
            rotateDir|=transforms::DOWN;break;
            case GLFW_KEY_D:
            rotateDir|=transforms::UP;break;
            case GLFW_KEY_Q:
            rotateDir|=transforms::BACK;break;
            case GLFW_KEY_E:
            rotateDir|=transforms::FORWARD;break;

            case GLFW_KEY_UP:
            translateDir|=transforms::UP;break;
            case GLFW_KEY_DOWN:
            translateDir|=transforms::DOWN;break;
            case GLFW_KEY_LEFT:
            translateDir|=transforms::LEFT;break;
            case GLFW_KEY_RIGHT:
            translateDir|=transforms::RIGHT;break;
            case GLFW_KEY_MINUS:
            translateDir|=transforms::FORWARD;break;
            case GLFW_KEY_EQUAL:
            translateDir|=transforms::BACK;break;
        }
    } else if(action==GLFW_RELEASE){
        switch(key){
            case GLFW_KEY_W:
            rotateDir&=~transforms::LEFT;break;
            case GLFW_KEY_S:
            rotateDir&=~transforms::RIGHT;break;
            case GLFW_KEY_A:
            rotateDir&=~transforms::DOWN;break;
            case GLFW_KEY_D:
            rotateDir&=~transforms::UP;break;
            case GLFW_KEY_Q:
            rotateDir&=~transforms::BACK;break;
            case GLFW_KEY_E:
            rotateDir&=~transforms::FORWARD;break;

            case GLFW_KEY_UP:
            translateDir&=~transforms::UP;break;
            case GLFW_KEY_DOWN:
            translateDir&=~transforms::DOWN;break;
            case GLFW_KEY_LEFT:
            translateDir&=~transforms::LEFT;break;
            case GLFW_KEY_RIGHT:
            translateDir&=~transforms::RIGHT;break;
            case GLFW_KEY_MINUS:
            translateDir&=~transforms::FORWARD;break;
            case GLFW_KEY_EQUAL:
            translateDir&=~transforms::BACK;break;
        }

    }

}

const int ROOT_STRT_SIZE[2]={900,900}; //size may change with window resizes

int main() {
try{

    if (!glfwInit()) {return -1;}
    
    //window setup
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE,false);

    GLFWwindow* root=glfwCreateWindow(ROOT_STRT_SIZE[0],ROOT_STRT_SIZE[1],";)",NULL,NULL);
    if (root==NULL) {
        std::cerr<<"Failed to create glfw window.\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(root);

    glewExperimental=true;
    unsigned int glew_err=glewInit();
    if(glew_err) {
        std::cerr<<"failed to init glew: "<<glewGetErrorString(glew_err);
        return -1;//glew requires openGL context first
    }

    glViewport(0,0,ROOT_STRT_SIZE[0],ROOT_STRT_SIZE[1]); //maps opengl float coordinates to window px ones
    glfwSetFramebufferSizeCallback(root,root_resize_callback);

    glfwSetInputMode(root,GLFW_STICKY_KEYS,true); //#RM?
    glfwSetKeyCallback(root,keyCallback);

    /*
    int noShaderAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&noShaderAttributes);
    std::cout<<"max no. of vertex shader attributes: "<<noShaderAttributes<<'\n'; //29 on this gtx 1660ti, guaranteed minimum of 16
    */

    //vertex array object
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    //make vertex buffer object
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //can bind multiple buffers to same buffer object, if they are different types
    //this sets internally in internal opengl state that the GL_ARRAY_BUFFER to be set to the object (ID) VBO
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW); //copy to VBO buffer, we previously set opengl to use VBO with glBindBuffer
    
    /*
    //element buffer object
    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    */

    //link shader attributes to data layout in vertex buffer
    glVertexAttribPointer(0,3,GL_FLOAT,false,5*sizeof(float), (void*)(0) );
    glVertexAttribPointer(1,2,GL_FLOAT,false,5*sizeof(float), (void*)(3*sizeof(float)) ); //(location number,(vec) size,type,normalise,stride,offset)

    //enable use of location attrib
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);

    textures::init();
    shaders::init();
    transforms::reset();

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //wireframe mode

    //mainloop
    double timeCurrent=glfwGetTime();
    double timeOld;
    while(!glfwWindowShouldClose(root)){
        
        glClearColor(0.35f,0.15f,0.15f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timeOld=timeCurrent;
        timeCurrent=glfwGetTime();
        double deltaT=timeCurrent-timeOld;
        if(!((rotateDir+translateDir)==0)){
            transforms::control(root,deltaT,(transforms::direction) translateDir,(transforms::direction) rotateDir);
        }
        glDrawArrays(GL_TRIANGLES,0,36);

        glfwSwapBuffers(root);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

} catch (std::exception &e) {
    std::cerr<<"Unhandled exception in main: "<<e.what();
}
}