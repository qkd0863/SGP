#version 330
#define MAX_POINTS 500

in vec3 a_Position;

out vec4 v_Color;

uniform float u_Time;
uniform float u_DropCount;
uniform vec4 u_Points[MAX_POINTS];
const float c_Pi = 3.141592;
/*const vec4 c_Points[3] = vec4[](vec4(0, 0, 2, 2), 
								vec4(0.5, 0, 3, 3),
								vec4(-0.5, 0, 4, 4));*/

void Flag()
{
	vec4 newPosition = vec4(a_Position, 1);
	float x = a_Position.x;
	float y = a_Position.y;
	float value = (a_Position.x + 0.5) * 2 * c_Pi;
	float value1 = a_Position.x + 0.5;
	float value2 = (a_Position.x+0.5) / 2;
	

	float dx = 0;
	float dy = value1 * 0.15 * sin(value+u_Time*4);
	
	float shading = (sin(value - u_Time*4)+1) / 2 + 0.2;
	
	newPosition.y *= 1 - value2;
	newPosition.xy += vec2(dx, dy);
	
	gl_Position = newPosition;
	

	

	v_Color = vec4(shading);
}

void Wave()
{
	vec4 newPosition = vec4(a_Position, 1);
	
	gl_Position = newPosition;
	

	
	//float r = 0.5 * sin(fract(u_Time));
	float d = distance(a_Position.xy, vec2(0,0));
	//float value = clamp(r - d,0,1);
	//value = ceil(value);
	//value = (r - d)*100;
	

	float value = sin(d * 4 * c_Pi * 10- u_Time*10);
	float p = 1 - clamp(d * 2,0,1);
	
	v_Color=vec4(value*p);
	
}

void RainDrop()
{
	vec4 newPosition = vec4(a_Position, 1);
	
	gl_Position = newPosition;
	
	
	
	vec2 pos = a_Position.xy;
	float newColor = 0;

	for(int i = 0; i < u_DropCount; ++i)
	{
		vec2 cen =  u_Points[i].xy;
		float sTime = u_Points[i].z;
		float lTime = u_Points[i].w;
		
		float newTime = u_Time - sTime;
		
		if(newTime > 0)
		{
			float baseTime = fract(newTime/lTime);
			float oneMinus = 1 * baseTime;
			float t = baseTime * lTime;
			float range = baseTime*0.2*lTime;
			float d = distance(pos, cen);
			float value = sin(d * 4 * c_Pi * 10 - t*10);  
			float p = 30*clamp(range - d,0,1) * (1-baseTime);
	
			newColor += value*p*oneMinus;
		}

	
	}

	v_Color = vec4(newColor);
	
	
}


void main()
{
	//Flag();
	//Wave();
	RainDrop();
}


