#shader vertex
#version 450
layout(location = 2) in vec4 position;
layout(location = 3) in vec4 id;
layout(location = 4) in vec4 coordinates;
uniform mat4 u_MPV;
out vec4 coords;
out vec4 ID;
void main()
{
    gl_Position = u_MPV * position;
    coords = coordinates;
    ID = id;
}

#shader fragment
#version 450
uniform vec4 u_Colour;
layout(location = 0) out vec4 colour;
in vec4 coords;
in vec4 ID;
uniform sampler2D text[2];
void main()
{
    int id = int(ID.x);
    colour = texture(text[id], coords.xy);
}
