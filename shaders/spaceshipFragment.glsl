#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 uColor;

void main()
{
    vec4 texture = texture2D(ourTexture, TexCoord);
    if (texture.a == 0.0)
        discard;
    float average = 0.2126 * texture.r * 0.6 + 0.7152 * texture.g * 0.6 + 0.0722 * texture.b * 0.6;
    vec4 finalColor = vec4(average + uColor.x, average + uColor.y, average + uColor.z, texture.a);
    FragColor = finalColor;
}