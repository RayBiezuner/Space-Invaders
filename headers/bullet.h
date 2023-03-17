#ifndef BULLET_H
#define BULLET_H

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "shader.h"



class Bullet {
private:
    float m_Position[2] = {0.0f, 1.1f};
    bool m_Active = true;
    Texture *m_Texture;
    Shader *m_Shader;
public:
    Bullet() {}
    Bullet(Shader *shader, Texture *texture, float (&position)[2]);
    void setTexture(Texture *texture){ m_Texture = texture; };
    void setShader(Shader *shader){ m_Shader = shader; };
    void Draw(unsigned int *VAO);
    //Movement related functions
    void setPosition(float position[2]) { m_Position[0] = position[0]; m_Position[1] = position[1];}
    //void setPosition(float x, float y) { m_Position[0] = x; m_Position[1] = y; }
    void move(float velocity, std::string direction);
    float* getPosition() { return m_Position; }
    float getX() { return m_Position[0]; }
    float getY() { return m_Position[1]; }
    bool OnScreen() {
        bool x = m_Position[0] < 1.0f && m_Position[0] > -1.0f;
        bool y = m_Position[1] < 1.0f && m_Position[1] > -1.0f;
        if(x && y)
            return true;
        else
            return false;
    }
    //Bullet related functions

};





#endif