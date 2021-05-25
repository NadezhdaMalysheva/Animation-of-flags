#version 320 es

precision mediump float;

out vec4 fragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;


void main()
{
    if ((TexCoord.x >= 1.9f) && (TexCoord.x < 3.0f))
        fragColor = vec4(0.5, 0.3, 0.0, 1.0);
    else if ((TexCoord.x >= 2.9f))
        fragColor = vec4(0.5, 0.0, 1.0, 1.0);
    else
        fragColor = texture(ourTexture, TexCoord);
}

