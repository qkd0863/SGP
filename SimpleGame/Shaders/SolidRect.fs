#version 330

layout(location=0) out vec4 FragColor;

in vec4 v_Color;
uniform vec4 u_Color;

void main()
{
	//FragColor = vec4(v_Color.r, v_Color.g, v_Color.b, v_Color.a);

	if(v_Color.b<0.5f && v_Color.r<0.5f)
		FragColor = v_Color;
	else
		discard;
}
