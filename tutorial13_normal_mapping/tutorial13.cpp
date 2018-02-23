// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/tangentspace.hpp>

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // So that glBegin/glVertex/glEnd work

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 13 - Normal Mapping", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "NormalMapping.vertexshader", "NormalMapping.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	GLuint ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");

	// Load the texture
	GLuint DiffuseTexture = loadDDS("diffuse.DDS");
	GLuint NormalTexture = loadBMP_custom("normal.bmp");
	GLuint SpecularTexture = loadDDS("specular.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint DiffuseTextureID  = glGetUniformLocation(programID, "DiffuseTextureSampler");
	GLuint NormalTextureID  = glGetUniformLocation(programID, "NormalTextureSampler");
	GLuint SpecularTextureID  = glGetUniformLocation(programID, "SpecularTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("cylinder.obj", vertices, uvs, normals);

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	computeTangentBasis(
		vertices, uvs, normals, // input
		tangents, bitangents    // output
	);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec3> indexed_tangents;
	std::vector<glm::vec3> indexed_bitangents;
	indexVBO_TBN(
		vertices, uvs, normals, tangents, bitangents, 
		indices, indexed_vertices, indexed_uvs, indexed_normals, indexed_tangents, indexed_bitangents
	);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	GLuint tangentbuffer;
	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &indexed_tangents[0], GL_STATIC_DRAW);

	GLuint bitangentbuffer;
	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &indexed_bitangents[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do{

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
		glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
		

		glm::vec3 lightPos = glm::vec3(0,0,4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our diffuse texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
		// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
		glUniform1i(DiffuseTextureID, 0);

		// Bind our normal texture in Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, NormalTexture);
		// Set our "NormalTextureSampler" sampler to use Texture Unit 1
		glUniform1i(NormalTextureID, 1);

		// Bind our specular texture in Texture Unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, SpecularTexture);
		// Set our "SpecularTextureSampler" sampler to use Texture Unit 2
		glUniform1i(SpecularTextureID, 2);


		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 4th attribute buffer : tangents
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
		glVertexAttribPointer(
			3,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 5th attribute buffer : bitangents
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
		glVertexAttribPointer(
			4,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);


		////////////////////////////////////////////////////////
		// DEBUG ONLY !!!
		// Don't use this in real code !!
		////////////////////////////////////////////////////////



		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf((const GLfloat*)&ProjectionMatrix[0]);
		glMatrixMode(GL_MODELVIEW);
		glm::mat4 MV = ViewMatrix * ModelMatrix;
		glLoadMatrixf((const GLfloat*)&MV[0]);


		glUseProgram(0);

		// normals
		glColor3f(0,0,1);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<indices.size(); i++){
			glm::vec3 p = indexed_vertices[indices[i]];
			glVertex3fv(&p.x);
			glm::vec3 o = glm::normalize(indexed_normals[indices[i]]);
			p+=o*0.1f;
			glVertex3fv(&p.x);
		}
		glEnd();
		// tangents
		glColor3f(1,0,0);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<indices.size(); i++){
			glm::vec3 p = indexed_vertices[indices[i]];
			glVertex3fv(&p.x);
			glm::vec3 o = glm::normalize(indexed_tangents[indices[i]]);
			p+=o*0.1f;
			glVertex3fv(&p.x);
		}
		glEnd();
		// bitangents
		glColor3f(0,1,0);
		glBegin(GL_LINES);
		for (unsigned int i=0; i<indices.size(); i++){
			glm::vec3 p = indexed_vertices[indices[i]];
			glVertex3fv(&p.x);
			glm::vec3 o = glm::normalize(indexed_bitangents[indices[i]]);
			p+=o*0.1f;
			glVertex3fv(&p.x);
		}
		glEnd();
		// light pos
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			glVertex3fv(&lightPos.x);
			lightPos+=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&lightPos.x);
			lightPos-=glm::vec3(1,0,0)*0.1f;
			glVertex3fv(&lightPos.x);
			lightPos+=glm::vec3(0,1,0)*0.1f;
			glVertex3fv(&lightPos.x);
		glEnd();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &tangentbuffer);
	glDeleteBuffers(1, &bitangentbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &DiffuseTexture);
	glDeleteTextures(1, &NormalTexture);
	glDeleteTextures(1, &SpecularTexture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

