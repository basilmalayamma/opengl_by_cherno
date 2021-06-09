#shader vertex
#version 330
layout(location = 0) in vec4 position;
void main()
{
    gl_Position = position;
}

#shader fragment
#version 330
uniform vec4 u_Colour;
layout(location = 0) out vec4 colour;
void main()
{
    colour = u_Colour;
}
