#version 330 core

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D textures[16];

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; // Need to figure out a way of passing the light position to the cube shader

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = ambient * objectColor;

    //FragColor = mix(texture(textures[0], TexCoord), texture(textures[1], TexCoord), 0.2);
    FragColor = vec4(result, 1.0);
}