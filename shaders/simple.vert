#version 320 es

precision mediump float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 TexCoord;
uniform float GlobalTime;
void main()
{	
	
    float len = 0.5 + position.x; 
    
    gl_Position = vec4(position.x, position.y + sin(GlobalTime)*len, position.z, 1.0);
    TexCoord = texture;
}
