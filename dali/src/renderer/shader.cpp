//
// Created by Leo on 5/23/2020.
//

#include <dali/renderer/shader.h>
#include <dali/core.h>

#include <glad/glad.h>

dali::Shader::Shader(std::string vertex_src, std::string fragment_src) {
// Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

// Send the vertex shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *) vertex_src.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

// Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        DALI_CORE_ERROR("{0}", infoLog.data());
        DALI_CORE_ASSERT(false, "Vertex shader compilation failure!");

        // In this simple program, we'll just leave
        return;
    }

// Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *) fragment_src.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

// Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        DALI_CORE_ERROR("{0}", infoLog.data());
        DALI_CORE_ASSERT(false, "Vertex shader compilation failure!");

        // In this simple program, we'll just leave
        return;
    }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
    m_program_id = glCreateProgram();

// Attach our shaders to our program
    glAttachShader(m_program_id, vertexShader);
    glAttachShader(m_program_id, fragmentShader);

// Link our program
    glLinkProgram(m_program_id);

// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_program_id, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(m_program_id);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.

        // In this simple program, we'll just leave
        return;
    }

// Always detach shaders after a successful link.
    glDetachShader(m_program_id, vertexShader);
    glDetachShader(m_program_id, fragmentShader);
}

dali::Shader::~Shader() {
    glDeleteProgram(m_program_id);
}

void dali::Shader::bind() const {
    glUseProgram(m_program_id);
}

void dali::Shader::unbind() const {
    glUseProgram(0);
}
