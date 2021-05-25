#version 320 es

precision mediump float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec2 TexCoord;
uniform float GlobalTime;
uniform float Offsets[200];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{	
	vec4 aPos;
    vec2 offset = vec2(Offsets[gl_InstanceID*2], Offsets[gl_InstanceID*2+1]);
    float speed = 10.0;
    float len = (0.05 + position.x) * (0.05 + position.x); 
    float shift = sin((GlobalTime)/speed + (position.x*100.0) + float(gl_InstanceID))*len;
    if (texture.x < 2.0f)
    {
        aPos = vec4(offset.x + position.x - shift/2.0, position.y + shift, offset.y + position.z, 1.0); //
        
    }
    else 
    {
        aPos = vec4(offset.x + position.x, position.y, offset.y + position.z, 1.0);
    }
    gl_Position = projection * view * model * aPos; // 
    TexCoord = texture;
}
