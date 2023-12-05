#version 330 core

in vec2 TexCoord;

uniform sampler2D tex;
//uniform sampler2D tex2;

out vec4 FragColor;

void main()
{
    //FragColor = mix(texture(tex, TexCoord), texture(tex2, TexCoord), 0.2);
    FragColor = texture(tex, TexCoord);
}