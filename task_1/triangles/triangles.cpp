#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>

int main( void )
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 1024, 768, "Triangles", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the "
                   "2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Light blue background
	glClearColor(0.58f, 0.87f, 0.89f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint yellowTriangleProgramID = LoadShaders(
	        "TransformVertexShader.glsl",
	        "YellowTriangleFragmentShader.glsl" );

    GLuint purpleTriangleProgramID = LoadShaders(
            "TransformVertexShader.glsl",
            "PurpleTriangleFragmentShader.glsl" );


    GLuint yellowTriangleMatrixID = glGetUniformLocation(yellowTriangleProgramID, "MVP");
    GLuint purpleTriangleMatrixID = glGetUniformLocation(purpleTriangleProgramID, "MVP");

    glm::mat4 Projection = glm::perspective(
            glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 Model = glm::mat4(1.0f);

	static const GLfloat g_vertex_buffer_data[] = { 
		-0.8f, -0.9f,  0.0f,
		-0.5f,  0.7f,  0.0f,
		 0.6f, -0.6f,  0.0f,

         0.7f,  0.6f,  0.0f,
         0.4f, -0.9f,  0.0f,
        -0.9f,  0.0f,  0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Fixed FPS
    int targetFPS = 60;
    double timePerFrame = 1000.0 / targetFPS;

    // Fixed rotation frequency
    double timePerRotation = 8 * 1000;
    double currentRotation = 0;

    int64_t cameraRotationRadius = 3;

    double startTime = glfwGetTime();

	do{

	    double lastTime = startTime;

	    double cameraX = cos(M_PI * 2 * currentRotation / timePerRotation) * cameraRotationRadius;
	    double cameraZ = sin(M_PI * 2 * currentRotation / timePerRotation) * cameraRotationRadius;

        // Camera matrix
        glm::mat4 View = glm::lookAt(
                glm::vec3(cameraX,0,cameraZ), // Camera is at (cameraX, 0, cameraZ), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)  // Head is up
        );

        glm::mat4 MVP = Projection * View * Model;

		glClear(GL_COLOR_BUFFER_BIT);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

        // Use shaders
        glUseProgram(yellowTriangleProgramID);

        // Send our transformation to the currently bound shader
        glUniformMatrix4fv(yellowTriangleMatrixID, 1, GL_FALSE, &MVP[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(purpleTriangleProgramID);
        glUniformMatrix4fv(purpleTriangleMatrixID, 1, GL_FALSE, &MVP[0][0]);
        glDrawArrays(GL_TRIANGLES, 3, 3);

		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

        startTime = glfwGetTime();
        double elapsedTime = (startTime - lastTime) * 1000;
        int64_t freeTime = std::max(timePerFrame - elapsedTime, 0.0);

        // Sleep until next frame to keep FPS rate at the certain level
        if (freeTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(freeTime));
        }

		currentRotation += elapsedTime + freeTime;
        if (currentRotation >= timePerRotation) {
            currentRotation -= static_cast<int64_t>(currentRotation / timePerRotation) * timePerRotation;
        }

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(yellowTriangleProgramID);
    glDeleteProgram(purpleTriangleProgramID);

	glfwTerminate();

	return 0;
}
