#version 330

in vec3 a_Position;

out vec4 v_Color;

uniform float u_Time;
const float c_Pi = 3.141592;

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


void main()
{
	//Flag();
	Wave();
	
}


