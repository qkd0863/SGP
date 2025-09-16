#version 330

in vec3 a_Position;
in vec4 a_Color;

out vec4 v_Color;

uniform float u_Time;
const float c_Pi = 3.141592;

void main()
{
	vec4 newPosition = vec4(a_Position, 1);
	//newPosition.x -= 0.5;
	//newPosition.y -= 0.5;
	//newPosition.xy = newPosition.xy - vec2(0.5, 0.5);
	
	

	float value = 2*fract(u_Time)-1;
	float rad = (value+1)*c_Pi;
	float x = value;
	float y = sin(rad);

	newPosition.xy += vec2(x,y);




	gl_Position = newPosition;


	v_Color = a_Color;
}
