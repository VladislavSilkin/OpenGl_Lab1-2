#version 330 core
in vec4 myColor;
out vec4 outColor;

void main(void)
{
    vec3 source = vec3(2.0,2.0,3.0);
    outColor = myColor;
}
