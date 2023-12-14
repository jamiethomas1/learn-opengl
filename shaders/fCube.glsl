#version 330 core

in vec2 TexCoord;

uniform sampler2D textures[16];
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    //FragColor = mix(texture(textures[0], TexCoord), texture(textures[1], TexCoord), 0.2);
    FragColor = vec4(lightColor * objectColor, 1.0);
}