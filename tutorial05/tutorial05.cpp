#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GL/glfw.h>

#include <common/shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

GLuint loadBMP_custom(const char * imagepath){

	printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height, bpp;
	// Actual RGB data
	unsigned char * data;

	// Open the file
    FILE * file = fopen(imagepath,"rb");
	if (!file)							    {printf("Image could not be opened\n"); return 0;}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 byes are read, problem
    if ( fread(header, 1, 54, file)!=54 ){ 
		printf("Not a correct BMP file\n");
		return false;
	}
	// A BMP files always begins with "BM"
    if ( header[0]!='B' || header[1]!='M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
    if ( *(int*)&(header[0x1E])!=0  )         {printf("Not a correct BMP file\n");    return 0;}
    if ( *(int*)&(header[0x1C])!=24 )         {printf("Not a correct BMP file\n");    return 0;}

	// Read the information about the image
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    bpp=3;

	// Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54;

	// Create a buffer
    data = new unsigned char [imageSize];

	// Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

	// Everything is in memory now, the file wan be closed
    fclose (file);

	// Swap Red and Blue component for each texel of the image
    unsigned char t;
    for (unsigned int i = 0; i < imageSize; i += 3 )
	{
        t = data[i];
        data[i] = data[i+2];
        data[i+2] = t;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	
	// "Bind" the newly created texture as a 2D texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,(bpp == 3 ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	// Return the ID of the texture we just created
    return textureID;
}

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
    if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );

        glfwTerminate();
        exit( EXIT_FAILURE );
    }
	int ret = glewInit();
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

	GLuint MatrixID  = glGetUniformLocation(programID, "MVP");
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(10,10,10), glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * View * Model;


		//glEnable(GL_TEXTURE_2D);
	GLuint Texture = loadBMP_custom("texture.bmp");
	GLuint TextureID  = glGetUniformLocation(programID, "texture");

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
	static const GLfloat g_uv_buffer_data[] = { 
		 0.000000, 0.000000,
		 1.000000, 0.000000,
		 0.000000, 1.000000,
		 1.000000, 1.000000,
		 0.000000, 0.000000,
		 1.000000, 0.000000,
		 0.000000, 1.000000,
		 1.000000, 1.000000
	};
	static const GLushort g_element_buffer_data[] = { 
		4, 0, 3,
		4, 3, 7,
		2, 6, 7,
		2, 7, 3,
		1, 5, 2,
		5, 6, 2,
		0, 4, 1,
		4, 5, 1,
		4, 7, 5,
		7, 6, 5,
		0, 1, 2,
		0, 2, 3
	};

	GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data, GL_STATIC_DRAW);
	
	glViewport(0, 0, 1024,768);
	glClearColor(0, 0, 0.3f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // activer ou désactiver

	do
    {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glUseProgram(programID);
		
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		

		//glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);

		glUniform1i(TextureID, 0);

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glVertexAttribPointer(
			0,  /* attribute */
			3,                                /* size */
			GL_FLOAT,                         /* type */
			GL_FALSE,                         /* normalized? */
			0,                /* stride */
			(void*)0                          /* array buffer offset */
		);

		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,  /* attribute */
			2,                                /* size */
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

