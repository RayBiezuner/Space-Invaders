#include "../include/player.h"

Player::Player(Shader *playerShader, Shader *bulletShader, unsigned int *VAO, Texture *playerTexture, Texture *bulletTexture) : m_Shader(playerShader), m_VAO(VAO), m_Texture(playerTexture)
{
    m_Gun = Gun(bulletShader, bulletTexture, 0.007f, "UP");
}

void Player::setColor()
{
    if (m_PowerUp == true)
    {
        float time;
        time = glfwGetTime();
        time = time - float(floor(time)) + float(int(floor(time)) % 3);
        if (time >= 0.0f && time < 1.0f)
        {
            float color[4] = {-1.0f * time + 1.0f, time, 0.0f, 0.5f};
            m_Shader->setVec4("uColor", color);
        }
        if (time >= 1.0f && time < 2.0f)
        {
            float color[4] = {0.0f, -1.0f * time + 2.0f, time - 1.0f, 0.5f};
            m_Shader->setVec4("uColor", color);
        }
        if (time >= 2.0f && time <= 3.0f)
        {
            float color[4] = {time - 2.0f, 0.0f, -1.0f * time + 3.0f, 0.5f};
            m_Shader->setVec4("uColor", color);
        }
    }
    else
    {
        float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        m_Shader->setVec4("uColor", color);
    }
}

void Player::Draw()
{
    if (m_Alive)
    {
        m_Texture->Bind();
        m_Shader->Use();
        // Setting uniforms
        m_Shader->setVec2("uDimension", m_Texture->getDimensions());
        m_Shader->setVec2("uTranslate", m_Position);
        setColor();
        glBindVertexArray(*m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Player::playerLoop(Gun *gun)
{
    if (gun->BulletHit(getPosition()))
        m_Alive = false;
}

void Player::bulletLoop()
{
    if (m_Alive)
    {
        m_Gun.Move();
    }
}

void Player::bulletDraw()
{
    m_Gun.Draw(m_VAO);
}

void Player::fireBullet()
{
    // std::cout << getPosition()[0] << "/" << getPosition()[1] << std::endl;
    m_Gun.Fire(getPosition());
}
