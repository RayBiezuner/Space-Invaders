#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 uTranslate;
uniform vec2 uDimension;
void main()
{
    float width = float(uDimension.x);
    float height = float(uDimension.y);
    gl_Position = vec4((9.0f / 16.0f) * (aPos.x / 270.0 * width) + uTranslate.x, aPos.y / 270.0 * height + uTranslate.y, aPos.z, 1.0);
    TexCoord = aTexCoord;
}