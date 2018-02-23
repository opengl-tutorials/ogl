// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace glm;

// Include AntTweakBar
#include <AntTweakBar.h>

// Include Bullet
#include <btBulletDynamicsCommon.h>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>


void ScreenPosToWorldRay(
	int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
	int screenWidth, int screenHeight,  // Window size, in pixels
	glm::mat4 ViewMatrix,               // Camera position and orientation
	glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
	glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
	glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
){

	// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
	glm::vec4 lRayStart_NDC(
		((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
	);
	glm::vec4 lRayEnd_NDC(
		((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
		((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
		0.0,
		1.0f
	);


	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);
	
	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);
	
	glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
	glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
	glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
	glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;


	// Faster way (just one inverse)
	//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);


	out_origin = glm::vec3(lRayStart_world);
	out_direction = glm::normalize(lRayDir_world);
}


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Misc 05 - Bullet version", NULL, NULL);
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

	// Initialize the GUI
	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(1024, 768);
	TwBar * GUI = TwNewBar("Picking");
	TwSetParam(GUI, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");
	std::string message;
	TwAddVarRW(GUI, "Last picked object", TW_TYPE_STDSTRING, &message, NULL);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
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
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );


	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

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

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);



	// Generate positions & rotations for 100 monkeys
	std::vector<glm::vec3> positions(100);
	std::vector<glm::quat> orientations(100);
	for(int i=0; i<100; i++){
		positions[i] = glm::vec3(rand()%20-10, rand()%20-10, rand()%20-10);
		orientations[i] = glm::normalize(glm::quat(glm::vec3(rand()%360, rand()%360, rand()%360)));
		
	}


	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");



	// Initialize Bullet. This strictly follows http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World, 
	// even though we won't use most of this stuff.

   // Build the broadphase
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
 
	// The world.
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-9.81f,0));


	
 

	std::vector<btRigidBody*> rigidbodies;

	// In this example, all monkeys will use the same collision shape : 
	// A box of 2m*2m*2m (1.0 is the half-extent !)
	btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

	for(int i=0; i<100; i++){

		btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
			btQuaternion(orientations[i].x, orientations[i].y, orientations[i].z, orientations[i].w), 
			btVector3(positions[i].x, positions[i].y, positions[i].z)
		));

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			0,                  // mass, in kg. 0 -> Static object, will never move.
			motionstate,
			boxCollisionShape,  // collision shape of body
			btVector3(0,0,0)    // local inertia
		);
		btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

		rigidbodies.push_back(rigidBody);
		dynamicsWorld->addRigidBody(rigidBody);

		// Small hack : store the mesh's index "i" in Bullet's User Pointer.
		// Will be used to know which object is picked. 
		// A real program would probably pass a "MyGameObjectPointer" instead.
		rigidBody->setUserPointer((void*)i);

	}


	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	do{

		btVector3 p0 = rigidbodies[0]->getCenterOfMassPosition();
		glm::vec3 v0 = positions[0];
		//printf("p0 : %f %f %f, v0 : %f %f %f\n", p0.x(), p0.y(), p0.z(), v0.x, v0.y, v0.z);


		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		float deltaTime = currentTime - lastTime;

		// Step the simulation? In this example this won't do anything, 
		// since all the monkeys are static (mass = 0).
		dynamicsWorld->stepSimulation(deltaTime, 7);


		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();




		// PICKING IS DONE HERE
		// (Instead of picking each frame if the mouse button is down, 
		// you should probably only check if the mouse button was just released)
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){


			glm::vec3 out_origin;
			glm::vec3 out_direction;
			ScreenPosToWorldRay(
				1024/2, 768/2,
				1024, 768, 
				ViewMatrix, 
				ProjectionMatrix, 
				out_origin, 
				out_direction
			);	
			
			glm::vec3 out_end = out_origin + out_direction*1000.0f;

			btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(out_origin.x, out_origin.y, out_origin.z), btVector3(out_end.x, out_end.y, out_end.z));
			dynamicsWorld->rayTest(btVector3(out_origin.x, out_origin.y, out_origin.z), btVector3(out_end.x, out_end.y, out_end.z), RayCallback);
			if(RayCallback.hasHit()) {
				std::ostringstream oss;
				oss << "mesh " << (size_t)RayCallback.m_collisionObject->getUserPointer();
				message = oss.str();
			}else{
				message = "background";
			}


		}


		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// Re-clear the screen for real rendering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use our shader
		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		for(int i=0; i<100; i++){


			glm::mat4 RotationMatrix = glm::toMat4(orientations[i]);
			glm::mat4 TranslationMatrix = translate(mat4(), positions[i]);
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix;

			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

			glm::vec3 lightPos = glm::vec3(4,4,4);
			glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture);
			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(TextureID, 0);

			// 1rst attribute buffer : vertices
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
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glVertexAttribPointer(
				2,                                // attribute
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
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);


		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Draw GUI
		TwDraw();



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
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	// Clean up behind ourselves like good little programmers

	for(int i=0; i<rigidbodies.size(); i++){
		dynamicsWorld->removeRigidBody(rigidbodies[i]);
		delete rigidbodies[i]->getMotionState();
		delete rigidbodies[i];
	}
	delete boxCollisionShape;

	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;

	return 0;
}

//// Helper class; draws the world as seen by Bullet.
//// This is very handy to see it Bullet's world matches yours.
//// This example uses the old OpenGL API for simplicity, 
//// so you'll have to remplace GLFW_OPENGL_CORE_PROFILE by
//// GLFW_OPENGL_COMPAT_PROFILE in glfwWindowHint()
//// How to use this class :
//// Declare an instance of the class :
//// BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
//// dynamicsWorld->setDebugDrawer(&mydebugdrawer);
//// Each frame, call it :
//// mydebugdrawer.SetMatrices(ViewMatrix, ProjectionMatrix);
//// dynamicsWorld->debugDrawWorld();
//
//class BulletDebugDrawer_DeprecatedOpenGL : public btIDebugDraw{
//public:
//	void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix){
//		glUseProgram(0); // Use Fixed-function pipeline (no shaders)
//		glMatrixMode(GL_MODELVIEW);
//		glLoadMatrixf(&pViewMatrix[0][0]);
//		glMatrixMode(GL_PROJECTION);
//		glLoadMatrixf(&pProjectionMatrix[0][0]);
//	}
//	virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color){
//		glColor3f(color.x(), color.y(), color.z());
//		glBegin(GL_LINES);
//			glVertex3f(from.x(), from.y(), from.z());
//			glVertex3f(to.x(), to.y(), to.z());
//		glEnd();
//	}
//	virtual void drawContactPoint(const btVector3 &,const btVector3 &,btScalar,int,const btVector3 &){}
//	virtual void reportErrorWarning(const char *){}
//	virtual void draw3dText(const btVector3 &,const char *){}
//	virtual void setDebugMode(int p){
//		m = p;
//	}
//	int getDebugMode(void) const {return 3;}
//	int m;
//};
