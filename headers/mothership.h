#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#define GLFW_INCLUDE_NONE

#include "enemy.h"
#include "gun.h"
#include <ctime>
extern const unsigned int WIDTH;
/*
extern Texture* ALIEN1_TEXTURE;
extern Texture* ALIEN2_TEXTURE;
extern Texture* ALIEN3_TEXTURE;
extern Texture* ALIEN4_TEXTURE;
extern Texture* ALIEN_BULLET_TEXTURE;
*/


class Mothership {
private:
    unsigned int* m_VAO;
    Enemy** m_EnemyArmy;
    //Enemy* m_FrontRowEnemies;
    unsigned int m_Rows, m_Columns;
    std::string m_Direction = "NO DIRECTION";
    float m_Velocity = 0.00007f;
    int* m_FrontRowEnemies;
    Gun m_Gun;
public:
    Mothership(unsigned int* VAO, unsigned int rows, unsigned int columns);
    void SetEnemies(Shader* shaderProgram, Texture* alien1, Texture* alien2, Texture* alien3, Texture* alien4);
    void Move(float velocity, std::string direction);
    void Movement(float boundary);
    void UpdateFrontRow(int i, int j);
    void Collision(Gun* gun);
    void SetGun(Shader* shader, Texture* texture);
    void Shoot();
    void BulletLoop();
    void BulletDraw();
    void Draw();
    Gun* getGun() { return &m_Gun; }
    bool EnemiesWon();
    bool EnemiesLoose();
    void PrintEnemies() {
        float v_x, v_y;
        if(m_Direction == "NO DIRECTION") {
            v_x = 0.0f; v_y = 0.0f;
        }
        else if(m_Direction == "UP") {
            v_x = 0.0f; v_y = m_Velocity;
        }
        else if(m_Direction == "DOWN") {
            v_x = 0.0f; v_y = -1.0f * m_Velocity;
        }
        else if(m_Direction == "RIGHT") {
            v_x = m_Velocity; v_y = 0.0f;
        }
        else if(m_Direction == "LEFT") {
            v_x = -1.0f * m_Velocity; v_y = 0.0f;
        }
        for(int i = 0; i < m_Rows; i++){
            for(int j = 0; j < m_Columns; j++) {
                if(m_EnemyArmy[i][j].isAlive())
                    ImGui::Text("Enemy[%d][%d] position: %f/%f, velocity: %f/%f", i, j, m_EnemyArmy[i][j].getPosition()[0], m_EnemyArmy[i][j].getPosition()[1], v_x, v_y);
            }
        }
    }
    void Delete();
};

#endif