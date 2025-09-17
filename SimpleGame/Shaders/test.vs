#version 330

in vec3 a_Position;
in float a_Value;
in vec4 a_Color;

out vec4 v_Color;

uniform float u_Time;
const float c_Pi = 3.141592;

void main()
{
	

	float radius = a_Value;
	float value = 2 * fract(u_Time) - 1;
	float rad = (value + 1) * c_Pi;
	float x =  radius * cos(rad);
	float y =  radius * sin(rad);

	vec4 newPosition = vec4(a_Position, 1);
	newPosition.xy += a_Value * vec2(x,y);
	

    gl_Position = newPosition;


	v_Color = a_Color;
}
