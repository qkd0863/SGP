#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	CompileAllShaderPrograms();
	
	//Create VBOs
	CreateVertexBufferObjects();

	//Create Particles
	CreatePartiocles(10000);

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);


	float center = 0.5f;
	float size = 0.1f;


	float testPos[]
		=
	{
		(0.f - center)* size , (0.f - center)* size , 0.f, 1, //x, y, z, value
		(1.f - center)* size , (0.f - center)* size , 0.f, 1,
		(1.f - center)* size , (1.f - center)* size , 0.f, 1,
		(0.f - center)* size , (0.f - center)* size , 0.f, 1,
		(1.f - center)* size , (1.f - center)* size , 0.f, 1,
		(0.f - center)* size , (1.f - center)* size , 0.f, 1, //Quad1



		(0.f - center)* size , (0.f - center)* size , 0.f, 0.5, //x, y, z, value
		(1.f - center)* size , (0.f - center)* size , 0.f, 0.5,
		(1.f - center)* size , (1.f - center)* size , 0.f, 0.5,
		(0.f - center)* size , (0.f - center)* size , 0.f, 0.5,
		(1.f - center)* size , (1.f - center)* size , 0.f, 0.5,
		(0.f - center)* size , (1.f - center)* size , 0.f, 0.5, //Quad2
	};

	glGenBuffers(1, &m_VBOTestPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testPos), testPos, GL_STATIC_DRAW);



	float testColor[]
		=
	{
		1.f  , 0.f  , 0.f  ,1.f,
		0.f  , 1.f  , 0.f  ,1.f,
		0.f  , 0.f  , 1.f  ,1.f,  
		1.f  , 0.f  , 0.f  ,1.f,
		0.f  , 1.f  , 0.f  ,1.f,
		0.f  , 0.f  , 1.f  ,1.f, //Quad1

		1.f  , 0.f  , 0.f  ,1.f,
		0.f  , 1.f  , 0.f  ,1.f,
		0.f  , 0.f  , 1.f  ,1.f,  
		1.f  , 0.f  , 0.f  ,1.f,
		0.f  , 1.f  , 0.f  ,1.f,
		0.f  , 0.f  , 1.f  ,1.f, //Quad2
	};

	glGenBuffers(1, &m_VBOTestColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(testColor), testColor, GL_STATIC_DRAW);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];

	size_t slen = strlen(pShaderText);
	if (slen > INT_MAX) {
		// Handle error
	}
	GLint len = (GLint)slen;

	Lengths[0] = len;
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	float newX, newY;

	GetGLPosition(x, y, &newX, &newY);

	//Program select
	glUseProgram(m_SolidRectShader);

	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), newX, newY, 0, size);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::CreatePartiocles(int count)
{
	int particleCounts = count;
	int verticesCounts = particleCounts * 6;
	int floatCountsPerVertex = 3 + 1 + 4 + 1 + 3; //x, y, z, value, r, g, b, a, sTime, vx, vy, vz
	int totalFloatCounts = floatCountsPerVertex * verticesCounts;
	int floatCountsPerParticle = floatCountsPerVertex * 6;

	float* temp = NULL;
	temp = new float[totalFloatCounts];

	for (int i = 0; i < particleCounts; i++)
	{
		float size = 0.01 * ((float)rand() / RAND_MAX);
		float centerX = 0;//  ((float)rand() / RAND_MAX) * 2.f - 1.f;
		float centerY = 0;//  ((float)rand() / RAND_MAX) * 2.f - 1.f;
		float value = ((float)rand() / RAND_MAX);
		float r = ((float)rand() / RAND_MAX);
		float g = ((float)rand() / RAND_MAX);
		float b = ((float)rand() / RAND_MAX);
		float sTime = ((float)rand() / RAND_MAX) * 2.f - 1.f;
		float vx = ((float)rand() / RAND_MAX) * 2.f - 1.f;
		float vy = ((float)rand() / RAND_MAX) * 2.f - 1.f;
		float vz = 0.f;



		int Index = i * floatCountsPerParticle;

		temp[Index] = centerX - size; Index++;	//x
		temp[Index] = centerY - size; Index++;	//y
		temp[Index] = 0; Index++;				//z
		temp[Index] = value; Index++;			//value
		temp[Index] = r; Index++;	//r	
		temp[Index] = g; Index++;	//g
		temp[Index] = b; Index++;	//b
		temp[Index] = 1; Index++;	//a
		temp[Index] = sTime; Index++;	//sTime
		temp[Index] = vx; Index++;	//vx
		temp[Index] = vy; Index++;	//vy
		temp[Index] = vz; Index++;	//vz

		temp[Index] = centerX + size; Index++;
		temp[Index] = centerY + size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;	//r	
		temp[Index] = g; Index++;	//g
		temp[Index] = b; Index++;	//b
		temp[Index] = 1; Index++;	//a
		temp[Index] = sTime; Index++;	//sTime
		temp[Index] = vx; Index++;	//vx
		temp[Index] = vy; Index++;	//vy
		temp[Index] = vz; Index++;	//vz

		temp[Index] = centerX - size; Index++;
		temp[Index] = centerY + size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;	//r	
		temp[Index] = g; Index++;	//g
		temp[Index] = b; Index++;	//b
		temp[Index] = 1; Index++;	//a
		temp[Index] = sTime; Index++;	//sTime
		temp[Index] = vx; Index++;	//vx
		temp[Index] = vy; Index++;	//vy
		temp[Index] = vz; Index++;	//vz


		temp[Index] = centerX - size; Index++;
		temp[Index] = centerY - size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;	//r	
		temp[Index] = g; Index++;	//g
		temp[Index] = b; Index++;	//b
		temp[Index] = 1; Index++;	//a
		temp[Index] = sTime; Index++;	//sTime
		temp[Index] = vx; Index++;	//vx
		temp[Index] = vy; Index++;	//vy
		temp[Index] = vz; Index++;	//vz

		temp[Index] = centerX + size; Index++;
		temp[Index] = centerY - size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;	//r	
		temp[Index] = g; Index++;	//g
		temp[Index] = b; Index++;	//b
		temp[Index] = 1; Index++;	//a
		temp[Index] = sTime; Index++;	//sTime
		temp[Index] = vx; Index++;	//vx
		temp[Index] = vy; Index++;	//vy
		temp[Index] = vz; Index++;	//vz

		temp[Index] = centerX + size; Index++;
		temp[Index] = centerY + size; Index++;
		temp[Index] = 0; Index++;
		temp[Index] = value; Index++;
		temp[Index] = r; Index++;	//r	
		temp[Index] = g; Index++;	//g
		temp[Index] = b; Index++;	//b
		temp[Index] = 1; Index++;	//a
		temp[Index] = sTime; Index++;	//sTime
		temp[Index] = vx; Index++;	//vx
		temp[Index] = vy; Index++;	//vy
		temp[Index] = vz; Index++;	//vz
	}



	glGenBuffers(1, &m_VBOParticles);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticles);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCounts, temp, GL_STATIC_DRAW);

	delete[] temp;

	m_VBOParticlesVertexCount = verticesCounts;
}



void Renderer::DrawTest()
{
	m_Time += 0.016;
	//Program select
	glUseProgram(m_TestShader);


	int uTimeLoc = glGetUniformLocation(m_TestShader, "u_Time");
	glUniform1f(uTimeLoc, m_Time);



	int aPosLoc = glGetAttribLocation(m_TestShader, "a_Position");
	glEnableVertexAttribArray(aPosLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	int aValueLoc = glGetAttribLocation(m_TestShader, "a_Value");
	glVertexAttribPointer(aValueLoc, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(float) * 3));
	glEnableVertexAttribArray(aValueLoc);


	int aColorLoc = glGetAttribLocation(m_TestShader, "a_Color");
	glEnableVertexAttribArray(aColorLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glVertexAttribPointer(aColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);


	

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glDisableVertexAttribArray(aPosLoc);
	glDisableVertexAttribArray(aColorLoc);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawParticle()
{
	m_Time += 0.016;
	//Program select
	GLuint shader = m_ParticleShader;
	glUseProgram(shader);


	int uTimeLoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(uTimeLoc, m_Time);


	int stride = 12;


	int aPosLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(aPosLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticles);
	glVertexAttribPointer(aPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);

	int aValueLoc = glGetAttribLocation(shader, "a_Value");
	glVertexAttribPointer(aValueLoc, 1, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (GLvoid*)(sizeof(float) * 3));
	glEnableVertexAttribArray(aValueLoc);


	int aColorLoc = glGetAttribLocation(shader, "a_Color");
	glEnableVertexAttribArray(aColorLoc);
	glVertexAttribPointer(aColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (GLvoid*)(sizeof(float) * 4));

	
	int aSTimeLoc = glGetAttribLocation(shader, "a_STime");
	glEnableVertexAttribArray(aSTimeLoc);
	glVertexAttribPointer(aSTimeLoc, 1, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (GLvoid*)(sizeof(float) * 8));
	
	int aVelLoc = glGetAttribLocation(shader, "a_Vel");
	glEnableVertexAttribArray(aVelLoc);
	glVertexAttribPointer(aVelLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, (GLvoid*)(sizeof(float) * 9));

	
	glDrawArrays(GL_TRIANGLES, 0, m_VBOParticlesVertexCount);


	glDisableVertexAttribArray(aPosLoc);
	glDisableVertexAttribArray(aColorLoc);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::ReloadAllShaderPrograms()
{
	DeleteAllShaderPrograms();
	CompileAllShaderPrograms();
}

void Renderer::DeleteAllShaderPrograms()
{
	glDeleteShader(m_SolidRectShader);
	glDeleteShader(m_TestShader);
	glDeleteShader(m_ParticleShader);
}

void Renderer::CompileAllShaderPrograms()
{
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_TestShader = CompileShaders("./Shaders/test.vs", "./Shaders/test.fs");
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs", "./Shaders/Particle.fs");
}
