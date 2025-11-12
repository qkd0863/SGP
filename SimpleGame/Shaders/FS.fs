#version 330
//물결로 움직이기
layout(location=0) out vec4 FragColor;

in vec2 v_UV;

uniform float u_Time;
uniform sampler2D u_RGBTexture;

const float c_PI = 3.141592;

void main()
{
	vec2 newPos=v_UV;
	newPos += vec2(0,0.1*sin(v_UV.x*2*c_PI+u_Time));
	vec4 newColor = texture(u_RGBTexture,newPos);
	
	
	FragColor = newColor;
}
