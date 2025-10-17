#include "Shader.h"

GLClasses::Shader::Shader(const string& vertexPath, const string& fragmentPath) : m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
{
	this->m_VertexData = getFileContent(vertexPath);
	this->m_FragmentData = getFileContent(fragmentPath);
}

GLClasses::Shader::~Shader()
{
	glUseProgram(0);
}

void GLClasses::Shader::CompileShaders()
{
	GLuint vs;
	GLuint fs;
	GLint successful;
	GLchar GLInfoLog[512];

	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs_char = m_VertexData.c_str();
	const char* fs_char = m_FragmentData.c_str();

	glShaderSource(vs, 1, &vs_char, 0);
	glShaderSource(fs, 1, &fs_char, 0);

	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &successful);

	if (!successful)
	{
		glGetShaderInfoLog(vs, 512, NULL, GLInfoLog);
		cout << "\nCOMPILATION ERROR IN VERTEX SHADER (" << m_VertexPath << ")" << "\n" << GLInfoLog << "\n\n";
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &successful);

	if (!successful)
	{
		glGetShaderInfoLog(fs, 512, NULL, GLInfoLog);
		cout << "\nCOMPILATION ERROR IN FRAGMENT SHADER (" << m_FragmentPath << ")" << "\n" << GLInfoLog << "\n";
	}

	m_Program = glCreateProgram();
	glAttachShader(m_Program, vs);
	glAttachShader(m_Program, fs);
	glLinkProgram(m_Program);

	glGetProgramiv(m_Program, GL_LINK_STATUS, &successful);

	if (!successful)
	{
		glGetProgramInfoLog(m_Program, 512, NULL, GLInfoLog);
		cout << "ERROR : SHADER LINKING FAILED : \n" << GLInfoLog << endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void GLClasses::Shader::Use()
{
	glUseProgram(m_Program);
}

GLuint GLClasses::Shader::getProgramID() const
{
	return m_Program;
}

void GLClasses::Shader::SetVector3f(const GLchar* name, const glm::vec3& value)
{
	glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void GLClasses::Shader::SetVector4f(const GLchar* name, const glm::vec4& value)
{
	glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void GLClasses::Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void GLClasses::Shader::SetInteger(const GLchar* name, GLuint value)
{
	glUniform1i(GetUniformLocation(name), value);
}

GLuint GLClasses::Shader::GetUniformLocation(const string name) const
{
	return glGetUniformLocation(m_Program, name.c_str());
}

std::string GLClasses::Shader::getFileContent(const string path)
{
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(path);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		return shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		return "";
	}
}