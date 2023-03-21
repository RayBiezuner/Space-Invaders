#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
public:
	//The shader program ID
	unsigned int ID;
	//Constructor to build the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//Function to use/activate this shader
	void Use();
	//Function to get shader program ID
	
	//Utility functions to set values to uniforms in the shader program
	void setBool(const std::string &uniformName, bool value) const;
	void setInt(const std::string &uniformName, int value) const;
	void setFloat(const std::string &uniformName, float value) const;
	void setVec4(const std::string &uniformName, float value[4]) const;
	void setVec3(const std::string &uniformName, float value[3]) const;
	void setVec2(const std::string &uniformName, float value[2]) const;
};
#endif