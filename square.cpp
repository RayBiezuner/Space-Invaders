#include "headers/square.h"
#include "stb_image.h"

Square::Square(Texture *texture, Shader *shader)
: m_Texture(texture), m_Shader(shader) {

}

void Square::Draw(unsigned int* VAO, float scale) {
    m_Texture->Bind();
    m_Shader->Use();
    float newDimensions[2] = {m_Texture->getDimensions()[0] * scale, m_Texture->getDimensions()[1] * scale};
    m_Shader->setVec2("uDimension", newDimensions);
    m_Shader->setVec2("uTranslate", m_Position);
    glBindVertexArray(*VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}

void Square::move(float velocity, std::string direction) {
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
