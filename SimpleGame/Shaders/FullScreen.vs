#version 330

in vec3 a_Position;

out vec4 v_Color;

const float c_Pi = 3.141592;

void main()
{
	vec4 newPosition = vec4(a_Position, 1);
	gl_Position = newPosition;

	vec3 center = vec3(0,0,0);

	if(distance(a_Position,center)<=0.3  && distance(a_Position,center)>=0.1 )
	{
		v_Color = vec4(0,1,0,0);
	}


}
