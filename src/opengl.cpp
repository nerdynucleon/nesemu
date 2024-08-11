#include "opengl.h"
#include <GLFW/glfw3.h>

float vertices[] = {
    // positions        // texture coords
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f,    // top-right
     1.0f, -1.0f, 0.0f,  1.0f, 0.0f,   // bottom-right
    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,   // top-left
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,   // bottom-left
};

const char * fragShader = R"(
#version 330 core

out vec4 FragColor; // Output color

in vec2 TexCoord; // Input texture coordinate from the vertex shader

uniform sampler2D texture1; // The texture sampler

void main()
{
    FragColor = texture(texture1, TexCoord); // Sample the texture and output the color
}

)";

const char * vertShader = R"(
  #version 330 core

layout(location = 0) in vec3 aPos;   // Position attribute
layout(location = 1) in vec2 aTexCoord; // Texture coordinate attribute

out vec2 TexCoord; // Output texture coordinate

void main()
{
    gl_Position = vec4(aPos, 1.0); // Set the position of the vertex
    TexCoord = aTexCoord; // Pass the texture coordinate to the fragment shader
}
)";

OpenGL::OpenGL() {}

void OpenGL::render(const void *data, int32_t width, int32_t height) {
      // Clear the screen
		GL(glClear( GL_COLOR_BUFFER_BIT ));

    GL(glBindTexture(GL_TEXTURE_2D, ppuTexture));
    GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

		// Use our shader
		GL(glUseProgram(programID));

		// Bind our texture in Texture Unit 0
		GL(glActiveTexture(GL_TEXTURE0));
		glBindTexture(GL_TEXTURE_2D, ppuTexture);
		// Set our "renderedTexture" sampler to use Texture Unit 0
		glUniform1i(glGetUniformLocation(programID, "texture1"), 0);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the quad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Unbind the VAO (Optional)
    glBindVertexArray(0);
}


void OpenGL::init() {

  //Texture for PPU to render to
  GL(glGenTextures(1, &ppuTexture));
  GL(glBindTexture(GL_TEXTURE_2D, ppuTexture));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLuint VBO;
  glGenBuffers(1, &VBO); // Generate a buffer ID
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer as a vertex buffer (GL_ARRAY_BUFFER)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Upload data to the buffer

  glGenVertexArrays(1, &VAO); // Generate a VAO ID
  glBindVertexArray(VAO); // Bind the VAO

  // Now bind the VBO and set up vertex attribute pointers
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the VAO

  // Define the layout of the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position attribute
  glEnableVertexAttribArray(0); // Enable the vertex attribute

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture coord attribute
  glEnableVertexAttribArray(1); // Enable the texture coord attribute

  glBindVertexArray(0); // Unbind the VAO

  // Create and compile our GLSL program from the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLint Result = GL_FALSE;
  int InfoLogLength;

	glShaderSource(VertexShaderID, 1, &vertShader , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	glShaderSource(FragmentShaderID, 1, &fragShader , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	// Check the program


	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(programID, VertexShaderID);
	glDetachShader(programID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}
