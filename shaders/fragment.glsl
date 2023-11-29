#version 330 core

in vec2 TexCoord;

uniform float time;

uniform sampler2D tex;
uniform sampler2D tex2;

out vec4 FragColor;

float pi = 3.1415926535;

void main()
{
    float sinTime = sin(time * 4) / 4 + 0.75;
    float sin2Time = sin(4*(time + pi*1/3)) / 4 + 0.75;
    float sin3Time = sin(4*(time + pi*2/3)) / 4 + 0.75;
    //FragColor = texture(tex, TexCoord) * vec4(vertexColor.r * sinTime, vertexColor.g * sin2Time, vertexColor.b * sin3Time, 1.);
    vec4 reversedFace = texture(tex2, TexCoord * vec2(-1., 1));
    FragColor = mix(texture(tex, TexCoord), texture(tex2, TexCoord), 0.2);
}