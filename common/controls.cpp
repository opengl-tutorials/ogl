// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

// Initial horizontal angle : toward +Z
float horizontalAngle = 0.0f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial position : since we look towards +Z, we have to move backwards ( in the -Z direction ) in order to see the origin
glm::vec3 position = glm::vec3( 0, 0, -5 ); 
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 5.0f;

glm::mat4 getMatrixFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetMousePos(1024/2, 738/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * deltaTime * float( 738/2 - ypos );

	// Up vector
	glm::vec3 up(0,1,0);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::cross( direction, up );


	// Move forward
	if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV - 5 * glfwGetMouseWheel();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	return MVP;
}