#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 View;
void main()
{
    color = vColor;
    gl_Position = Projection*View*ModelView*vPosition;
}
