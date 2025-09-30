#version 330

in vec3 a_Position;
in float a_Value;
in vec4 a_Color;
in float a_STime;
in vec3 a_Vel;
in float a_Life;
in float a_Mass;
in float a_Period;

out vec4 v_Color;

uniform float u_Time;
uniform vec3 u_Force;
const float c_Pi = 3.141592;
const vec2 c_G = vec2(0, -9.8);


void fountain()
{
	float lifeTime = a_Life;
	float newAlpha = 1;
	float newTime = u_Time - a_STime;
	float ax = u_Force.x / a_Mass;
	float ay = u_Force.y / a_Mass;
	vec4 newPosition = vec4(a_Position, 1);
	if(newTime>0)
	{ 
		float fX = c_G.x*a_Mass + u_Force.x;	
		float fY = c_G.y*a_Mass + u_Force.y;
		float aX = fX / a_Mass;
		float aY = fY / a_Mass;
		float t = fract(newTime/lifeTime)*lifeTime;
		float tt =  t * t;
		float x = a_Vel.x * t + 0.5 * aX  * tt;
		float y = a_Vel.y * t + 0.5 * aY  * tt;
		
		newPosition.xy += vec2(x, y);
		newAlpha = 1 - t/lifeTime;
	
	}
	else
	{
		newPosition.xy = vec2(-10000, 0);
	}


	gl_Position = newPosition;
	v_Color = vec4(a_Color.rgb,newAlpha);
}

void sinParticle()
{

	vec4 centerC = vec4(1,0,0,1);
	vec4 borderC = vec4(1,1,1,1);
	vec4 newColor = a_Color;

	
	vec4 newPosition = vec4(a_Position, 1);
	float newAlpha = 1;
	
	float period = a_Period * 1;
	float newTime = u_Time - a_STime;
	float lifeTime = a_Life;

	if(newTime>0)
	{
		

		float t = fract(u_Time/lifeTime) * lifeTime;
		float tt = t * t;
		
		
		float nTime = (t/lifeTime) * 2;
		float amp = (a_Value * 2 - 1) * nTime;
		
		float x = nTime * 2 - 1;
		float y = nTime * sin(nTime * c_Pi) * amp * sin(period * 2 * c_Pi * t/lifeTime);

		newPosition.xy += vec2(x, y);
		newAlpha = 1-t/lifeTime;

		float d = abs(y);
		newColor = mix(centerC,borderC,d*10);
	}
	else
	{
		newPosition.xy=vec2(-100000,0);
	}
	

	gl_Position = newPosition;
	v_Color = vec4(newColor.rgb,newAlpha);
}

void circleParticle()
{
	vec4 newPosition = vec4(a_Position, 1);
	float newAlpha = 1;
	float lifeTime = a_Life;


	float newTime = u_Time - a_STime;


	if(newTime>0)
	{
		float value = 2 * c_Pi *a_Value;
		float t = fract(u_Time/lifeTime) * lifeTime;
		float tt = t * t;
		float radius = 0.5;



		float x = radius * cos(value);
		float y = radius * sin(value);

		float newX = x + 0.5 * c_G.x * tt;
		float newY = y + 0.5 * c_G.y * tt;

		

		newPosition.xy+=vec2(newX,newY);
		newAlpha = 1-t/lifeTime;
	}
	else
	{
		newPosition.xy=vec2(-100000,0);
	}


	gl_Position = newPosition;
	v_Color = vec4(a_Color.rgb,newAlpha);
	
}



void main()
{
	//fountain();
	//sinParticle();
	circleParticle();
}
