#version 320 es

precision mediump float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 TexCoord;
uniform float GlobalTime;
void main()
{	
	
    float speed = 20.0;
    float len = (0.05 + position.x) * (0.05 + position.x); 
    
    gl_Position = vec4(position.x -  sin(GlobalTime/speed + (position.x*100.0))*len , position.y  + sin(GlobalTime/speed + (position.x*100.0))*len , position.z, 1.0); //
    TexCoord = texture;
}
