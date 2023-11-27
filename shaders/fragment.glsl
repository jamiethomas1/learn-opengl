#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;

uniform float time;
uniform sampler2D tex;

out vec4 FragColor;

float pi = 3.1415926535;

void main()
{
    float sinTime = sin(time * 4) / 4 + 0.75;
    float sin2Time = sin(4*(time + pi*1/3)) / 4 + 0.75;
    float sin3Time = sin(4*(time + pi*2/3)) / 4 + 0.75;
    FragColor = texture(tex, TexCoord) * vec4(vertexColor.r * sinTime, vertexColor.g * sin2Time, vertexColor.b * sin3Time, 1.);
}