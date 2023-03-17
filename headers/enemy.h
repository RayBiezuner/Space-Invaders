#ifndef ENEMY_H
#define ENEMY_H

#define GLFW_INCLUDE_NONE

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "shader.h"
#include "texture.h"
//#include "bullet.h"

#include <iostream>
#include <cmath>

class Enemy {
private:
    float m_Position[2];
    bool m_Alive = true;
    Texture *m_Texture;
    Shader *m_Shader;
    //Bullet *m_Bullet;
public:
    Enemy();
    Enemy(Shader *shader, Texture *texture, float position[2]);
    void setTexture(Texture *texture){ m_Texture = texture; };
    void setShader(Shader *shader){ m_Shader = shader; };
    //void setBullet(Bullet *bullet){ m_Bullet = bullet; };
    void Draw(unsigned int *VAO);
    //Movement related functions
    void setPosition(float (&position)[2]) { m_Position[0] = position[0]; m_Position[1] = position[1];}
    void setPosition(float x, float y) { m_Position[0] = x; m_Position[1] = y; }
    void move(float velocity, std::string direction);
    float* getPosition() { return m_Position; }
    float getX() { return m_Position[0]; }
    float getY() { return m_Position[1]; }
    //Gameplay related functions
    void kill() { m_Alive = false; }
    bool isAlive() { return m_Alive; }
};





#endif