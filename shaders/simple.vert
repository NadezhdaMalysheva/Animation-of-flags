#version 320 es

precision mediump float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 TexCoord;
uniform float GlobalTime;
uniform float Offsets[200];

void main()
{	
	
    vec2 offset = vec2(Offsets[gl_InstanceID*2], Offsets[gl_InstanceID*2+1]);
    float speed = 10.0;
    float len = (0.05 + position.x) * (0.05 + position.x); 
    float shift = sin((GlobalTime)/speed + (position.x*100.0) + float(gl_InstanceID))*len;
    
    gl_Position = vec4(offset.x + position.x + shift, offset.y + position.y + shift, position.z, 1.0); //
    TexCoord = texture;
}
