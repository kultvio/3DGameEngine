#include "ShaderProgram.h"
#include <glad/glad.h>
#include <iostream>
namespace GameEngine
{
	bool createShader(const char* source, const GLenum shader_type, GLuint& shader_id)
	{
		shader_id = glCreateShader(shader_type);
		glShaderSource(shader_id, 1, &source, nullptr);
		glCompileShader(shader_id);

		GLint success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			return false;
		}
		return true;
	}

	ShaderProgram::ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src)
	{
		GLuint vertex_shader_id = 0;
		if (!createShader(vertex_shader_src, GL_VERTEX_SHADER, vertex_shader_id))
		{
			glDeleteShader(vertex_shader_id);
			return;
		}
		GLuint fragment_shader_id = 0;
		if (!createShader(fragment_shader_src, GL_FRAGMENT_SHADER, fragment_shader_id))
		{
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}

		shader_program = glCreateProgram();
		glAttachShader(shader_program, vertex_shader_id);
		glAttachShader(shader_program, fragment_shader_id);
		glLinkProgram(shader_program);

		GLint success;
		glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLchar info_log[1024];
			glGetProgramInfoLog(shader_program, 1024, nullptr, info_log);
			std::cout << info_log << "\n";
			glDeleteProgram(shader_program);
			shader_program = 0;
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}
		else
		{
			m_isCompiled = true;
		}
		glDetachShader(shader_program, vertex_shader_id);
		glDetachShader(shader_program, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);

	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(shader_program);
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(shader_program);
	}
	void ShaderProgram::unbind()
	{
		glUseProgram(0);
	}
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram)
	{
		glDeleteProgram(shader_program);
		shader_program = shaderProgram.shader_program;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_isCompiled = false;
		shaderProgram.shader_program = 0;

		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram)
	{
		shader_program = shaderProgram.shader_program;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_isCompiled = false;
		shaderProgram.shader_program = 0;
	}
}