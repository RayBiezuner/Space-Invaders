#include "headers/bullet.h"
#include "stb_image.h"

Bullet::Bullet( Shader *shader, Texture *texture, float (&position)[2])
: m_Texture(texture), m_Shader(shader) {
    m_Position[0] = position[0];
    m_Position[1] = position[1];
}

void Bullet::Draw(unsigned int* VAO) {
    if(m_Active == true) {
        m_Texture->Bind();
    //std::cout << "m_Texture: " << m_Texture->getLocation() << std::endl;
    m_Shader->Use();
    m_Shader->setVec2("uDimension", m_Texture->getDimensions());
    m_Shader->setVec2("uTranslate", m_Position);
    glBindVertexArray(*VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Bullet::move(float velocity, std::string direction) {
    if(direction == "UP")
        m_Position[1] += velocity;
    else if(direction == "DOWN")
        m_Position[1] -= velocity;
    else if(direction == "RIGHT")
        m_Position[0] += velocity;
    else if(direction == "LEFT") 
        m_Position[0] -= velocity;
    else 
        std::cout << "ERROR: " << direction << " is an invalid direction." << std::endl;
}
