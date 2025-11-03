#version 330

in vec3 a_Position;
in vec4 a_Color;

uniform float u_Time;

out vec4 v_Color;

uniform vec4 u_Trans;
const float c_Pi = 3.141592;


void main()
{
	vec4 newPosition = vec4(a_Position, 1);
	
	float x =  2*fract(u_Time)-1;

	
	newPosition.x += x;
	newPosition.y += sin((x+1)*c_Pi*2);

	
	
	
	gl_Position = newPosition;

	v_Color = a_Color;
}
