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

    static const GLfloat g_vertexes_pool[14][3] = {
            {-0.15f, 0.15f,-0.15f},
            {-0.15f,-0.15f,-0.15f},
            {-0.9f, 0.0f, 0.0f},
            {-0.15f,-0.15f, 0.15f},
            {-0.15f, 0.15f, 0.15f},
            {0.15f, 0.15f,-0.15f},
            {0.15f,-0.15f,-0.15f},
            {0.9f, 0.0f, 0.0f},
            {0.15f,-0.15f, 0.15f},
            {0.15f, 0.15f, 0.15f},
            {0.0f,-0.9f, 0.0f},
            {0.0f, 0.9f, 0.0f},
            {0.0f, 0.0f,-0.9f},
            {0.0f, 0.0f, 0.9f}
    };

    static const GLfloat g_vertex_buffer_data[] = {
            g_vertexes_pool[0][0], g_vertexes_pool[0][1], g_vertexes_pool[0][2],
            g_vertexes_pool[1][0], g_vertexes_pool[1][1], g_vertexes_pool[1][2],
            g_vertexes_pool[2][0], g_vertexes_pool[2][1], g_vertexes_pool[2][2],
            g_vertexes_pool[1][0], g_vertexes_pool[1][1], g_vertexes_pool[1][2],
            g_vertexes_pool[3][0], g_vertexes_pool[3][1], g_vertexes_pool[3][2],
            g_vertexes_pool[2][0], g_vertexes_pool[2][1], g_vertexes_pool[2][2],
            g_vertexes_pool[3][0], g_vertexes_pool[3][1], g_vertexes_pool[3][2],
            g_vertexes_pool[4][0], g_vertexes_pool[4][1], g_vertexes_pool[4][2],
            g_vertexes_pool[2][0], g_vertexes_pool[2][1], g_vertexes_pool[2][2],
            g_vertexes_pool[4][0], g_vertexes_pool[4][1], g_vertexes_pool[4][2],
            g_vertexes_pool[0][0], g_vertexes_pool[0][1], g_vertexes_pool[0][2],
            g_vertexes_pool[2][0], g_vertexes_pool[2][1], g_vertexes_pool[2][2],
            g_vertexes_pool[5][0], g_vertexes_pool[5][1], g_vertexes_pool[5][2],
            g_vertexes_pool[6][0], g_vertexes_pool[6][1], g_vertexes_pool[6][2],
            g_vertexes_pool[7][0], g_vertexes_pool[7][1], g_vertexes_pool[7][2],
            g_vertexes_pool[6][0], g_vertexes_pool[6][1], g_vertexes_pool[6][2],
            g_vertexes_pool[8][0], g_vertexes_pool[8][1], g_vertexes_pool[8][2],
            g_vertexes_pool[7][0], g_vertexes_pool[7][1], g_vertexes_pool[7][2],
            g_vertexes_pool[8][0], g_vertexes_pool[8][1], g_vertexes_pool[8][2],
            g_vertexes_pool[9][0], g_vertexes_pool[9][1], g_vertexes_pool[9][2],
            g_vertexes_pool[7][0], g_vertexes_pool[7][1], g_vertexes_pool[7][2],
            g_vertexes_pool[9][0], g_vertexes_pool[9][1], g_vertexes_pool[9][2],
            g_vertexes_pool[5][0], g_vertexes_pool[5][1], g_vertexes_pool[5][2],
            g_vertexes_pool[7][0], g_vertexes_pool[7][1], g_vertexes_pool[7][2],
            g_vertexes_pool[6][0], g_vertexes_pool[6][1], g_vertexes_pool[6][2],
            g_vertexes_pool[1][0], g_vertexes_pool[1][1], g_vertexes_pool[1][2],
            g_vertexes_pool[10][0], g_vertexes_pool[10][1], g_vertexes_pool[10][2],
            g_vertexes_pool[1][0], g_vertexes_pool[1][1], g_vertexes_pool[1][2],
            g_vertexes_pool[3][0], g_vertexes_pool[3][1], g_vertexes_pool[3][2],
            g_vertexes_pool[10][0], g_vertexes_pool[10][1], g_vertexes_pool[10][2],
            g_vertexes_pool[3][0], g_vertexes_pool[3][1], g_vertexes_pool[3][2],
            g_vertexes_pool[8][0], g_vertexes_pool[8][1], g_vertexes_pool[8][2],
            g_vertexes_pool[10][0], g_vertexes_pool[10][1], g_vertexes_pool[10][2],
            g_vertexes_pool[8][0], g_vertexes_pool[8][1], g_vertexes_pool[8][2],
            g_vertexes_pool[6][0], g_vertexes_pool[6][1], g_vertexes_pool[6][2],
            g_vertexes_pool[10][0], g_vertexes_pool[10][1], g_vertexes_pool[10][2],
            g_vertexes_pool[5][0], g_vertexes_pool[5][1], g_vertexes_pool[5][2],
            g_vertexes_pool[0][0], g_vertexes_pool[0][1], g_vertexes_pool[0][2],
            g_vertexes_pool[11][0], g_vertexes_pool[11][1], g_vertexes_pool[11][2],
            g_vertexes_pool[0][0], g_vertexes_pool[0][1], g_vertexes_pool[0][2],
            g_vertexes_pool[4][0], g_vertexes_pool[4][1], g_vertexes_pool[4][2],
            g_vertexes_pool[11][0], g_vertexes_pool[11][1], g_vertexes_pool[11][2],
            g_vertexes_pool[4][0], g_vertexes_pool[4][1], g_vertexes_pool[4][2],
            g_vertexes_pool[9][0], g_vertexes_pool[9][1], g_vertexes_pool[9][2],
            g_vertexes_pool[11][0], g_vertexes_pool[11][1], g_vertexes_pool[11][2],
            g_vertexes_pool[9][0], g_vertexes_pool[9][1], g_vertexes_pool[9][2],
            g_vertexes_pool[5][0], g_vertexes_pool[5][1], g_vertexes_pool[5][2],
            g_vertexes_pool[11][0], g_vertexes_pool[11][1], g_vertexes_pool[11][2],
            g_vertexes_pool[6][0], g_vertexes_pool[6][1], g_vertexes_pool[6][2],
            g_vertexes_pool[1][0], g_vertexes_pool[1][1], g_vertexes_pool[1][2],
            g_vertexes_pool[12][0], g_vertexes_pool[12][1], g_vertexes_pool[12][2],
            g_vertexes_pool[1][0], g_vertexes_pool[1][1], g_vertexes_pool[1][2],
            g_vertexes_pool[0][0], g_vertexes_pool[0][1], g_vertexes_pool[0][2],
            g_vertexes_pool[12][0], g_vertexes_pool[12][1], g_vertexes_pool[12][2],
            g_vertexes_pool[0][0], g_vertexes_pool[0][1], g_vertexes_pool[0][2],
            g_vertexes_pool[5][0], g_vertexes_pool[5][1], g_vertexes_pool[5][2],
            g_vertexes_pool[12][0], g_vertexes_pool[12][1], g_vertexes_pool[12][2],
            g_vertexes_pool[5][0], g_vertexes_pool[5][1], g_vertexes_pool[5][2],
            g_vertexes_pool[6][0], g_vertexes_pool[6][1], g_vertexes_pool[6][2],
            g_vertexes_pool[12][0], g_vertexes_pool[12][1], g_vertexes_pool[12][2],
            g_vertexes_pool[8][0], g_vertexes_pool[8][1], g_vertexes_pool[8][2],
            g_vertexes_pool[3][0], g_vertexes_pool[3][1], g_vertexes_pool[3][2],
            g_vertexes_pool[13][0], g_vertexes_pool[13][1], g_vertexes_pool[13][2],
            g_vertexes_pool[3][0], g_vertexes_pool[3][1], g_vertexes_pool[3][2],
            g_vertexes_pool[4][0], g_vertexes_pool[4][1], g_vertexes_pool[4][2],
            g_vertexes_pool[13][0], g_vertexes_pool[13][1], g_vertexes_pool[13][2],
            g_vertexes_pool[4][0], g_vertexes_pool[4][1], g_vertexes_pool[4][2],
            g_vertexes_pool[9][0], g_vertexes_pool[9][1], g_vertexes_pool[9][2],
            g_vertexes_pool[13][0], g_vertexes_pool[13][1], g_vertexes_pool[13][2],
            g_vertexes_pool[9][0], g_vertexes_pool[9][1], g_vertexes_pool[9][2],
            g_vertexes_pool[8][0], g_vertexes_pool[8][1], g_vertexes_pool[8][2],
            g_vertexes_pool[13][0], g_vertexes_pool[13][1], g_vertexes_pool[13][2]
    };

    static const GLfloat g_colors_pool[14][3] = {
            {0.8f, 1.0f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {1.0f, 0.416f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {1.0f, 0.416f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {0.8f, 1.0f, 0.0f},
            {1.0f, 0.416f, 0.0f},
            {1.0f, 0.416f, 0.0f},
            {1.0f, 0.416f, 0.0f},
            {1.0f, 0.416f, 0.0f}
    };

    static const GLfloat g_color_buffer_data[] = {
            g_colors_pool[0][0], g_colors_pool[0][1], g_colors_pool[0][2],
            g_colors_pool[1][0], g_colors_pool[1][1], g_colors_pool[1][2],
            g_colors_pool[2][0], g_colors_pool[2][1], g_colors_pool[2][2],
            g_colors_pool[1][0], g_colors_pool[1][1], g_colors_pool[1][2],
            g_colors_pool[3][0], g_colors_pool[3][1], g_colors_pool[3][2],
            g_colors_pool[2][0], g_colors_pool[2][1], g_colors_pool[2][2],
            g_colors_pool[3][0], g_colors_pool[3][1], g_colors_pool[3][2],
            g_colors_pool[4][0], g_colors_pool[4][1], g_colors_pool[4][2],
            g_colors_pool[2][0], g_colors_pool[2][1], g_colors_pool[2][2],
            g_colors_pool[4][0], g_colors_pool[4][1], g_colors_pool[4][2],
            g_colors_pool[0][0], g_colors_pool[0][1], g_colors_pool[0][2],
            g_colors_pool[2][0], g_colors_pool[2][1], g_colors_pool[2][2],
            g_colors_pool[5][0], g_colors_pool[5][1], g_colors_pool[5][2],
            g_colors_pool[6][0], g_colors_pool[6][1], g_colors_pool[6][2],
            g_colors_pool[7][0], g_colors_pool[7][1], g_colors_pool[7][2],
            g_colors_pool[6][0], g_colors_pool[6][1], g_colors_pool[6][2],
            g_colors_pool[8][0], g_colors_pool[8][1], g_colors_pool[8][2],
            g_colors_pool[7][0], g_colors_pool[7][1], g_colors_pool[7][2],
            g_colors_pool[8][0], g_colors_pool[8][1], g_colors_pool[8][2],
            g_colors_pool[9][0], g_colors_pool[9][1], g_colors_pool[9][2],
            g_colors_pool[7][0], g_colors_pool[7][1], g_colors_pool[7][2],
            g_colors_pool[9][0], g_colors_pool[9][1], g_colors_pool[9][2],
            g_colors_pool[5][0], g_colors_pool[5][1], g_colors_pool[5][2],
            g_colors_pool[7][0], g_colors_pool[7][1], g_colors_pool[7][2],
            g_colors_pool[6][0], g_colors_pool[6][1], g_colors_pool[6][2],
            g_colors_pool[1][0], g_colors_pool[1][1], g_colors_pool[1][2],
            g_colors_pool[10][0], g_colors_pool[10][1], g_colors_pool[10][2],
            g_colors_pool[1][0], g_colors_pool[1][1], g_colors_pool[1][2],
            g_colors_pool[3][0], g_colors_pool[3][1], g_colors_pool[3][2],
            g_colors_pool[10][0], g_colors_pool[10][1], g_colors_pool[10][2],
            g_colors_pool[3][0], g_colors_pool[3][1], g_colors_pool[3][2],
            g_colors_pool[8][0], g_colors_pool[8][1], g_colors_pool[8][2],
            g_colors_pool[10][0], g_colors_pool[10][1], g_colors_pool[10][2],
            g_colors_pool[8][0], g_colors_pool[8][1], g_colors_pool[8][2],
            g_colors_pool[6][0], g_colors_pool[6][1], g_colors_pool[6][2],
            g_colors_pool[10][0], g_colors_pool[10][1], g_colors_pool[10][2],
            g_colors_pool[5][0], g_colors_pool[5][1], g_colors_pool[5][2],
            g_colors_pool[0][0], g_colors_pool[0][1], g_colors_pool[0][2],
            g_colors_pool[11][0], g_colors_pool[11][1], g_colors_pool[11][2],
            g_colors_pool[0][0], g_colors_pool[0][1], g_colors_pool[0][2],
            g_colors_pool[4][0], g_colors_pool[4][1], g_colors_pool[4][2],
            g_colors_pool[11][0], g_colors_pool[11][1], g_colors_pool[11][2],
            g_colors_pool[4][0], g_colors_pool[4][1], g_colors_pool[4][2],
            g_colors_pool[9][0], g_colors_pool[9][1], g_colors_pool[9][2],
            g_colors_pool[11][0], g_colors_pool[11][1], g_colors_pool[11][2],
            g_colors_pool[9][0], g_colors_pool[9][1], g_colors_pool[9][2],
            g_colors_pool[5][0], g_colors_pool[5][1], g_colors_pool[5][2],
            g_colors_pool[11][0], g_colors_pool[11][1], g_colors_pool[11][2],
            g_colors_pool[6][0], g_colors_pool[6][1], g_colors_pool[6][2],
            g_colors_pool[1][0], g_colors_pool[1][1], g_colors_pool[1][2],
            g_colors_pool[12][0], g_colors_pool[12][1], g_colors_pool[12][2],
            g_colors_pool[1][0], g_colors_pool[1][1], g_colors_pool[1][2],
            g_colors_pool[0][0], g_colors_pool[0][1], g_colors_pool[0][2],
            g_colors_pool[12][0], g_colors_pool[12][1], g_colors_pool[12][2],
            g_colors_pool[0][0], g_colors_pool[0][1], g_colors_pool[0][2],
            g_colors_pool[5][0], g_colors_pool[5][1], g_colors_pool[5][2],
            g_colors_pool[12][0], g_colors_pool[12][1], g_colors_pool[12][2],
            g_colors_pool[5][0], g_colors_pool[5][1], g_colors_pool[5][2],
            g_colors_pool[6][0], g_colors_pool[6][1], g_colors_pool[6][2],
            g_colors_pool[12][0], g_colors_pool[12][1], g_colors_pool[12][2],
            g_colors_pool[8][0], g_colors_pool[8][1], g_colors_pool[8][2],
            g_colors_pool[3][0], g_colors_pool[3][1], g_colors_pool[3][2],
            g_colors_pool[13][0], g_colors_pool[13][1], g_colors_pool[13][2],
            g_colors_pool[3][0], g_colors_pool[3][1], g_colors_pool[3][2],
            g_colors_pool[4][0], g_colors_pool[4][1], g_colors_pool[4][2],
            g_colors_pool[13][0], g_colors_pool[13][1], g_colors_pool[13][2],
            g_colors_pool[4][0], g_colors_pool[4][1], g_colors_pool[4][2],
            g_colors_pool[9][0], g_colors_pool[9][1], g_colors_pool[9][2],
            g_colors_pool[13][0], g_colors_pool[13][1], g_colors_pool[13][2],
            g_colors_pool[9][0], g_colors_pool[9][1], g_colors_pool[9][2],
            g_colors_pool[8][0], g_colors_pool[8][1], g_colors_pool[8][2],
            g_colors_pool[13][0], g_colors_pool[13][1], g_colors_pool[13][2]
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
		glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, 0);

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
