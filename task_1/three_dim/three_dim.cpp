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
#include <glm/gtx/transform.hpp>
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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint yellowTriangleProgramID = LoadShaders(
	        "TransformVertexShader.glsl",
	        "ColorFragmentShader.glsl" );

    GLuint yellowTriangleMatrixID = glGetUniformLocation(yellowTriangleProgramID, "MVP");

    glm::mat4 Projection = glm::perspective(
            glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 Model = glm::rotate(glm::radians(60.0f), glm::vec3(1.0f));

    static const GLfloat g_vertex_buffer_data[] = {
            -0.15f, 0.15f,-0.15f,
            -0.15f,-0.15f,-0.15f,
            -0.9f, 0.0f, 0.0f,
            -0.15f,-0.15f,-0.15f,
            -0.15f,-0.15f, 0.15f,
            -0.9f, 0.0f, 0.0f,
            -0.15f,-0.15f, 0.15f,
            -0.15f, 0.15f, 0.15f,
            -0.9f, 0.0f, 0.0f,
            -0.15f, 0.15f, 0.15f,
            -0.15f, 0.15f,-0.15f,
            -0.9f, 0.0f, 0.0f,
             0.15f, 0.15f,-0.15f,
             0.15f,-0.15f,-0.15f,
             0.9f, 0.0f, 0.0f,
             0.15f,-0.15f,-0.15f,
             0.15f,-0.15f, 0.15f,
             0.9f, 0.0f, 0.0f,
             0.15f,-0.15f, 0.15f,
             0.15f, 0.15f, 0.15f,
             0.9f, 0.0f, 0.0f,
             0.15f, 0.15f, 0.15f,
             0.15f, 0.15f,-0.15f,
             0.9f, 0.0f, 0.0f,
             0.15f,-0.15f,-0.15f,
            -0.15f,-0.15f,-0.15f,
             0.0f,-0.9f, 0.0f,
            -0.15f,-0.15f,-0.15f,
            -0.15f,-0.15f, 0.15f,
             0.0f,-0.9f, 0.0f,
            -0.15f,-0.15f, 0.15f,
             0.15f,-0.15f, 0.15f,
             0.0f,-0.9f, 0.0f,
             0.15f,-0.15f, 0.15f,
             0.15f,-0.15f,-0.15f,
             0.0f,-0.9f, 0.0f,
             0.15f, 0.15f,-0.15f,
            -0.15f, 0.15f,-0.15f,
             0.0f, 0.9f, 0.0f,
            -0.15f, 0.15f,-0.15f,
            -0.15f, 0.15f, 0.15f,
             0.0f, 0.9f, 0.0f,
            -0.15f, 0.15f, 0.15f,
             0.15f, 0.15f, 0.15f,
             0.0f, 0.9f, 0.0f,
             0.15f, 0.15f, 0.15f,
             0.15f, 0.15f,-0.15f,
             0.0f, 0.9f, 0.0f,
             0.15f,-0.15f,-0.15f,
            -0.15f,-0.15f,-0.15f,
             0.0f, 0.0f,-0.9f,
            -0.15f,-0.15f,-0.15f,
            -0.15f, 0.15f,-0.15f,
             0.0f, 0.0f,-0.9f,
            -0.15f, 0.15f,-0.15f,
             0.15f, 0.15f,-0.15f,
             0.0f, 0.0f,-0.9f,
             0.15f, 0.15f,-0.15f,
             0.15f,-0.15f,-0.15f,
             0.0f, 0.0f,-0.9f,
             0.15f,-0.15f, 0.15f,
            -0.15f,-0.15f, 0.15f,
             0.0f, 0.0f, 0.9f,
            -0.15f,-0.15f, 0.15f,
            -0.15f, 0.15f, 0.15f,
             0.0f, 0.0f, 0.9f,
            -0.15f, 0.15f, 0.15f,
             0.15f, 0.15f, 0.15f,
             0.0f, 0.0f, 0.9f,
             0.15f, 0.15f, 0.15f,
             0.15f,-0.15f, 0.15f,
             0.0f, 0.0f, 0.9f
    };

    static const GLfloat g_color_buffer_data[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f, //
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.327f,  0.483f,  0.844f, //
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.327f,  0.483f,  0.844f, //
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f,
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                1,
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

		glDrawArrays(GL_TRIANGLES, 0, 6 * 4 * 3);

		glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

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
    glDeleteBuffers(1, &colorbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(yellowTriangleProgramID);

	glfwTerminate();

	return 0;
}
