#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


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
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );

        glfwTerminate();
        exit( EXIT_FAILURE );
    }
//	int ret = glewInit();

	  if (glewInit()) {
                fprintf(stderr, "failed to initialize OpenGL\n");
                return -1;
        }


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

	GLuint MatrixID  = glGetUniformLocation(programID, "MVP");
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(10,10,10), glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0,
		 1.0f, -1.0f, 0,
		 0.0f,  1.0f, 0,
	};
	static const GLushort g_element_buffer_data[] = { 0, 1, 2 };

	GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data, GL_STATIC_DRAW);
	
	
	do
    {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, 1024,768);
		glClearColor(0,0,0.3f,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(
			0,  /* attribute */
			3,                                /* size */
			GL_FLOAT,                         /* type */
			GL_FALSE,                         /* normalized? */
			0,                /* stride */
			(void*)0                          /* array buffer offset */
		);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glDrawElements(
			GL_TRIANGLES,  /* mode */
			3,                  /* count */
			GL_UNSIGNED_SHORT,  /* type */
			(void*)0            /* element array buffer offset */
		);
    
		glDisableVertexAttribArray(0);


        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
           glfwGetWindowParam( GLFW_OPENED ) );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit( EXIT_SUCCESS );
}

