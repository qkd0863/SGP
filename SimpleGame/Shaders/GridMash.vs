#version 330

in vec3 a_Position;

out vec4 v_Color;

uniform float u_Time;
const float c_Pi = 3.141592;

void main()
{
	vec4 newPosition = vec4(a_Position, 1);
	float x = a_Position.x;
	float y = a_Position.y;
	float value = (a_Position.x + 0.5) * 2 * c_Pi;
	float value1 = a_Position.x + 0.5;
	float value2 = (a_Position.x+0.5)/2;
	

	float dx = 0;
	float dy = value1 * 0.15 * sin(value+u_Time*4);
	
	float shading = (sin(value - u_Time*4)+1) / 2 + 0.2;
	
	newPosition.y *= 1 - value1;
	newPosition.xy += vec2(dx, dy);
	
	gl_Position = newPosition;



	v_Color = vec4(shading);
}
