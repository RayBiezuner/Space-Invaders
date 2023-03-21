#ifndef ENTITY_H
#define ENTITY_H

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "shader.h"

class Square {
private:
    float m_Position[2] = {0.0f, 0.0f};
    Texture *m_Texture;
    Shader *m_Shader;
public:
    Square(Texture *texture, Shader *shader);

    void setTexture(Texture *texture){ m_Texture = texture; };
    void setShader(Shader *shader){ m_Shader = shader; };
    void Draw(unsigned int *VAO, float scale);
    //Movement related functions
    void setPosition(float (&position)[2]) { m_Position[0] = position[0]; m_Position[1] = position[1];}
    void setPosition(float x, float y) { m_Position[0] = x; m_Position[1] = y; }
    void move(float velocity, std::string direction);
    float* getPosition() { return m_Position; }
    //Laser related functions
};


#endif