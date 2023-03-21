#ifndef GUN_H
#define GUN_H

#define GLFW_INCLUDE_NONE

#include "bullet.h"
// #include "../imgui/imgui.h"

class Gun
{
private:
    std::string m_Direction;
    float m_Velocity;
    Bullet m_Cartridge[5];
    bool m_BulletReady[5] = {true, true, true, true, true};

public:
    Gun();
    Gun(Shader *shader, Texture *texture, float velocity, std::string direction);
    void BulletOnScreen();
    void Draw(unsigned int *VAO);
    void Move();
    void Fire(float initialPosition[2]);
    bool BulletHit(float entityPosition[2]);
    /*void PrintPositions()
    {
        if (m_Cartridge[0].OnScreen())
            ImGui::Text("Bullet0: %f/%f", m_Cartridge[0].getPosition()[0], m_Cartridge[0].getPosition()[1]);
        if (m_Cartridge[1].OnScreen())
            ImGui::Text("Bullet1: %f/%f", m_Cartridge[1].getPosition()[0], m_Cartridge[1].getPosition()[1]);
        if (m_Cartridge[2].OnScreen())
            ImGui::Text("Bullet2: %f/%f", m_Cartridge[2].getPosition()[0], m_Cartridge[2].getPosition()[1]);
        if (m_Cartridge[3].OnScreen())
            ImGui::Text("Bullet3: %f/%f", m_Cartridge[3].getPosition()[0], m_Cartridge[3].getPosition()[1]);
        if (m_Cartridge[4].OnScreen())
            ImGui::Text("Bullet4: %f/%f", m_Cartridge[4].getPosition()[0], m_Cartridge[4].getPosition()[1]);
    }*/
};

#endif