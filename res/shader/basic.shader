#shader vertex
#version 330
layout(location = 2) in vec4 position;
layout(location = 3) in vec4 coordinates;
vec2 pos;
out vec4 coords;
void main()
{
    gl_Position = position;
    coords = coordinates;
}

#shader fragment
#version 330
uniform vec4 u_Colour;
layout(location = 0) out vec4 colour;
in vec4 coords;
uniform sampler2D text;
void main()
{
    colour = texture(text, coords.xy);
}
