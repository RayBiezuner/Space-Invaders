#ifndef PLAYER_H
#define PLAYER_H

#define GLFW_INCLUDE_NONE

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "gun.h"


#include <iostream>
#include <cmath>


class Player {
private:
    float m_Position[2] = {0.0f, 0.0f};
    float m_OldPosition[2] = {0.0f, 0.0f};
    float m_OldTime = 0.0f;
    float m_CurrentTime = 0.0f;
    bool m_PowerUp = true;
    Texture *m_Texture;
    Shader *m_Shader;
    unsigned int *m_VAO;
    Gun m_Gun;
    bool m_Alive = true;
public:
    Player(Shader *playerShader, Shader *bulletShader, unsigned int *VAO, Texture *playerTexture, Texture *bulletTexture);
    void Draw();
    void playerLoop(Gun* gun);
    //Movement related functions
    float* getPosition() { return m_Position; }
    void setPosition(float position[2]) {
        m_OldPosition[0] = m_Position[0];
        m_OldPosition[1] = m_Position[1];
        m_Position[0] = position[0]; 
        m_Position[1] = position[1]; 
        m_OldTime = m_CurrentTime;
        m_CurrentTime = glfwGetTime();
    }
    void setColor();
    //Gun related functions
    void bulletLoop();
    void bulletDraw();
    void fireBullet();
    Gun* getGun() {return &m_Gun; }
    bool isAlive() { return m_Alive; }
    void PrintData() {
        float v;
        v = (m_Position[0] - m_OldPosition[0]) / (m_CurrentTime - m_OldTime);
        ImGui::Text("Player position: %f/%f velocity: %f/0.0", m_Position[0], m_Position[1], v);
    }
    //Gameplay
};

#endif
