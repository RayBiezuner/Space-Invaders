#ifndef TEXTURE_H
#define TEXTURE_H

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Texture {
private:
    //Texture location in OpenGL
    unsigned int m_TextureID;
    std::string m_ImagePath;
    int m_Width, m_Height, m_NumberOfChannels;
    float m_Dimensions[2];
public:
    //Constructor with texture path
    Texture(std::string imagePath);
    //Get texture location in OpenGL
    unsigned int getLocation() { return m_TextureID; };
    //Get texture dimensions
    float getWidth() { return float(m_Width); };
    float getHeight() { return float(m_Height); };
    float* getDimensions() { return m_Dimensions; }
    //Bind texture
    void Bind();
};

#endif