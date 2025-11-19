#version 330
//물결로 움직이기
//동심원 그리기
//grb 만들기
layout(location=0) out vec4 FragColor;

in vec2 v_UV;

uniform float u_Time;
uniform sampler2D u_RGBTexture;
uniform sampler2D u_NumTexture;
uniform sampler2D u_TotalTexture;
uniform int u_Number;

const float c_PI = 3.141592;


void Test()
{
	vec2 newPos=v_UV;
	//newPos += vec2(0,0.1*sin(v_UV.x*2*c_PI+u_Time));
	vec4 newColor = texture(u_RGBTexture,newPos);
	
	
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
	else{
	discard;}
	FragColor = newColor;
}

void Q1()
{
	float newX = v_UV.x;
	float newY = 1 - abs(v_UV.y * 2 - 1);

	FragColor = texture(u_RGBTexture,vec2(newX,newY));
}

void Q2()
{
	float newX = fract(v_UV.x*3);
	float newY = (2 - floor(v_UV.x*3))/3 + v_UV.y/3;

	FragColor = texture(u_RGBTexture,vec2(newX,newY));
}
void Q3()
{
	float newX = fract(v_UV.x*3);
	float newY = floor(v_UV.x*3)/3+v_UV.y/3;

	FragColor = texture(u_RGBTexture,vec2(newX,newY));

}
void Q4()
{
	float count = 3;
	float shift = 0.1*u_Time;
	float newX = fract(fract(v_UV.x*count)+floor((v_UV.y*count)+1)*shift);
	float newY = fract(v_UV.y*count);

	FragColor = texture(u_RGBTexture,vec2(newX,newY));

}

void Q5()
{
	float count = 2;
	float shift = 0.1*u_Time;
	float newX = fract(v_UV.x*count);
	float newY = fract(fract(v_UV.y*count)+floor((v_UV.x*count)+1)*shift);

	FragColor = texture(u_RGBTexture,vec2(newX,newY));

}


void Number()
{  
	FragColor = texture(u_NumTexture,v_UV);
}
void TotalNumber()
{  
	float newX = v_UV.x / 5;
	float newY = v_UV.y / 2;
	FragColor = texture(u_TotalTexture,vec2(newX,newY));
}

vec4 sampleDigit(int digit, vec2 uv)
{
    // digit(0~9) → 아틀라스 인덱스(0~9)
    // 이미지가 1 2 3 4 5 / 6 7 8 9 0 순서이므로 변환 필요
    int index = (digit + 9) % 10;

    int col = index % 5;
    int row = index / 5;

    // 아틀라스 타일 크기
    vec2 tileSize = vec2(1.0/5.0, 1.0/2.0);

    // 텍스처 상단이 1~5 라고 가정 → y 뒤집기
    int rowAtlas = row;

    vec2 offset = vec2(float(col), float(rowAtlas)) * tileSize;

    vec2 atlasUV = uv * tileSize + offset;
    return texture(u_TotalTexture, atlasUV);
}

void is()
{
	// 화면을 5칸으로 나눔
    float cellW = 1.0 / 5.0;
    int cellIndex = int(floor(v_UV.x / cellW)); // 0~4

    // cellIndex에 따라 출력할 자리 선택 (왼→오)
    // 0 1 2 3 4
    // ↑ ↑ ↑ ↑ ↑
    // 만 자리 / 천 자리 / 백 자리 / 십 자리 / 일 자리
    int digits[5];
    int num = u_Number;

    digits[4] = num % 10; num /= 10;  // 1의 자리
    digits[3] = num % 10; num /= 10;  // 10의 자리
    digits[2] = num % 10; num /= 10;  // 100의 자리
    digits[1] = num % 10; num /= 10;  // 1000의 자리
    digits[0] = num % 10;             // 10000의 자리

    // 해당 셀 내부의 로컬 UV (0~1)
    float localX = (v_UV.x - float(cellIndex) * cellW) / cellW;
    vec2 localUV = vec2(localX, v_UV.y);

    // 숫자 샘플링
    vec4 col = sampleDigit(digits[cellIndex], localUV);

    FragColor = col;
}
void main()
{	
	//Test();
	//Circles();
	//Flag();
	//Q1();
	//Q2();
	//Q3();
	//Q4();
	//Q5();
	//Number();
	//TotalNumber();
	is();
}
