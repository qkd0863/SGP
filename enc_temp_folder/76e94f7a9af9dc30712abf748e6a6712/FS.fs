#version 330
//물결로 움직이기
//동심원 그리기
layout(location=0) out vec4 FragColor;

in vec2 v_UV;

uniform float u_Time;
uniform sampler2D u_RGBTexture;

const float c_PI = 3.141592;


void Test()
{
	vec2 newPos=v_UV;
	newPos += vec2(0,0.1*sin(v_UV.x*2*c_PI+u_Time));
	
	vec4 newColor = texture(u_RGBTexture,newPos);
	
	
	FragColor = newColor;
}

void Circles()
{
	vec2 newUV = v_UV;
	vec2 center = vec2(0.5,0.5);
	float d = distance(newUV,center);
	float value = sin(d*4*c_PI*8-u_Time*8);
	
	vec4 newColor = vec4(value);
	FragColor = newColor;
}

void Flag()
{
	vec2 newUV = vec2(v_UV.x,(1-v_UV.y)-0.5);
	float sinValue = v_UV.x * 0.2*(sin(v_UV.x*2*c_PI - u_Time * 5));
	vec4 newColor = vec4(0);
	float width = 0.2*(1-v_UV.x);


	if(sinValue + width > newUV.y && sinValue - width < newUV.y)
	{
		newColor=vec4(1);
	}
	FragColor = newColor;
}
void main()
{
	//Circles();
	Flag();
}
