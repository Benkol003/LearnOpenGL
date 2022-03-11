#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "glm/glm/gtx/string_cast.hpp" //#RM
#include <cmath>

#include "shaders.hpp" //linting include

namespace transforms{
    
    glm::mat4 rotation,translation;
    glm::mat4 projectMat;

    enum direction{
        NONE=0,
        UP=1<<0,
        DOWN=1<<1,
        LEFT=1<<2,
        RIGHT=1<<3,
        FORWARD=1<<4,
        BACK=1<<5,
    };

    int calcDirVec(direction flags, glm::vec3 &retVec){
        glm::vec3 unitVec(0.0f);
        if (flags&UP){
            unitVec[1]+=1;
        }
        if(flags&DOWN){
            unitVec[1]-=1;
        }
        if (flags&LEFT){
            unitVec[0]-=1;
        }
        if (flags&RIGHT){
            unitVec[0]+=1;
        }
        if (flags&FORWARD){
            unitVec[2]-=1; //z axis is positive coming out the screen for gl, i think
        }
        if (flags&BACK){
            unitVec[2]+=1;
        }

        //normalise vector
        int magnitude=sqrt( pow(unitVec[0],2) + pow(unitVec[1],2) + pow(unitVec[2],2) );
        if (magnitude!=0){
            for(int i=0;i<3;++i){
                unitVec[i]=unitVec[i]/magnitude;
            }
        }
        retVec=unitVec;
        return magnitude;
    }


    void reset(){
        projectMat=glm::perspective(glm::radians(50.0f),1.0f,0.1f,100.0f);
        translation=rotation=glm::mat4(1.0f);
        glUniformMatrix4fv(shaders::uTransform,1,false,glm::value_ptr(projectMat*translation*rotation));
    }

    glm::mat4 move(double deltaT, direction flags) {
        glm::vec3 dirVec;
        int dirMagnitude=calcDirVec(flags,dirVec);
        glm::mat4 translateMat(1.0f);
        if(dirMagnitude) {
            translateMat=glm::translate(translateMat, dirVec*(float)(50*deltaT) );
        }
        return translateMat;
    }

    glm::mat4 rotate(double deltaT, direction flags) {
        glm::vec3 axisVec(0.0f);
        int axisMagnitude=calcDirVec(flags,axisVec);
        glm::mat4 rotateMat(1.0f);
        if(axisMagnitude){
            rotateMat=glm::rotate(rotateMat, (float)glm::radians(720*deltaT) ,axisVec);
        }
        return rotateMat;
    }

    void control(GLFWwindow* root,double deltaT, direction translateFlags, direction rotateFlags){
        if( translateFlags!=transforms::NONE ) translation=move(deltaT,translateFlags)*translation;
        if( rotateFlags!=transforms::NONE ) rotation=rotate(deltaT,rotateFlags)*rotation;
        glUniformMatrix4fv(shaders::uTransform,1,false,glm::value_ptr(projectMat*translation*rotation));
    }

}
#endif