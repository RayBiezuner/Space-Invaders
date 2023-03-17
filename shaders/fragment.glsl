#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 texture = texture2D(ourTexture, TexCoord);
    if (texture.a == 0.0)
        discard;
    FragColor = texture;
}