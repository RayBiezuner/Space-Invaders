#include "../include/gun.h"

Gun::Gun(){};

Gun::Gun(Shader *shader, Texture *texture, float velocity, std::string direction) : m_Velocity(velocity), m_Direction(direction)
{
    float position[2] = {1.1f, 1.1f};
    for (auto &bullet : m_Cartridge)
    {
        bullet = Bullet(shader, texture, position);
    }
}

void Gun::BulletOnScreen()
{
    for (int i = 0; i < 5; i++)
    {
        bool offLimits;
        offLimits = m_Cartridge[i].getY() >= 1.0f || m_Cartridge[i].getY() <= -1.0f;
        if (offLimits == true)
        {
            m_BulletReady[i] = true;
        }
    }
}

void Gun::Draw(unsigned int *VAO)
{
    // std::cout << m_BulletReady[0] << std::endl;
    for (int i = 0; i < 5; i++)
        if (!m_BulletReady[i])
            m_Cartridge[i].Draw(VAO);
}

void Gun::Move()
{
    // std::cout << m_Cartridge[0].getX() << "/" << m_Cartridge[0].getY() << std::endl;
    for (int i = 0; i < 5; i++)
        m_Cartridge[i].move(m_Velocity, m_Direction);
}

void Gun::Fire(float initialPosition[2])
{
    BulletOnScreen();
    for (int i = 0; i < 5; i++)
    {
        if (m_BulletReady[i])
        {
            // std::cout << i <<std::endl;
            m_BulletReady[i] = false;
            m_Cartridge[i].setPosition(initialPosition);
            // std::cout << m_Cartridge[1].getX() << "/"<< m_Cartridge[1].getY() << std::endl;
            // std::cout << "Bullet fired: " << i << std::endl;
            break;
        }
    }
}

bool Gun::BulletHit(float entityPosition[2])
{
    for (int i = 0; i < 5; i++)
    {
        if (m_BulletReady[i] == false)
        {
            float xDistance = std::abs(entityPosition[0] - m_Cartridge[i].getX());
            float yDistance = std::abs(entityPosition[1] - m_Cartridge[i].getY());
            bool entityWasHit = xDistance <= (32.0f / 1080.0f) && yDistance <= (32.0f / 1080.0f);
            if (entityWasHit)
            {
                m_BulletReady[i] = true;
                return true;
            }
        }
    }
    return false;
}
