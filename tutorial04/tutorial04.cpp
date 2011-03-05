#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GL/glfw.h>

#include <common/shader.hpp>

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 800, 800, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );

        glfwTerminate();
        exit( EXIT_FAILURE );
    }
	int ret = glewInit();
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

	static const GLfloat g_vertex_buffer_data[] = { 
		 0.500000, -0.500000, -0.500000,
		 0.500000, -0.500000,  0.500000,
		-0.500000, -0.500000,  0.500000,
		-0.500000, -0.500000, -0.500000,
		 0.500000,  0.500000, -0.500000,
		 0.500000,  0.500000,  0.500000,
		-0.500000,  0.500000,  0.500000,
		-0.500000,  0.500000, -0.500000
	};
	static const GLfloat g_color_buffer_data[] = { 
		 1.000000, 0.000000, 0.000000,
		 0.000000, 1.000000, 0.000000,
		 0.000000, 0.000000, 1.000000,
		 1.000000, 0.000000, 0.000000,
		 0.000000, 1.000000, 0.000000,
		 0.000000, 0.000000, 1.000000,
		 1.000000, 0.000000, 0.000000,
		 0.000000, 1.000000, 0.000000,
	};
	static const GLushort g_element_buffer_data[] = { 
		5, 1, 4,
		5, 4, 8,
		3, 7, 8,
		3, 8, 4,
		2, 6, 3,
		6, 7, 3,
		1, 5, 2,
		5, 6, 2,
		5, 8, 6,
		8, 7, 6,
		1, 2, 3,
		1, 3, 4
	};

	GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data, GL_STATIC_DRAW);
	
	
	do
    {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, 800,800);
		glClearColor(0,0,0.3f,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(
			0,  /* attribute */
			3,                                /* size */
			GL_FLOAT,                         /* type */
			GL_FALSE,                         /* normalized? */
			0,                /* stride */
			(void*)0                          /* array buffer offset */
		);

		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,  /* attribute */
			3,                                /* size */
			GL_FLOAT,                         /* type */
			GL_FALSE,                         /* normalized? */
			0,                /* stride */
			(void*)0                          /* array buffer offset */
		);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glDrawElements(
			GL_TRIANGLES,  /* mode */
			12*3,                  /* count */
			GL_UNSIGNED_SHORT,  /* type */
			(void*)0            /* element array buffer offset */
		);
    
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
           glfwGetWindowParam( GLFW_OPENED ) );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit( EXIT_SUCCESS );
}

