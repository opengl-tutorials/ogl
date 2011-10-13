#ifndef CONTROLS_HPP
#define CONTROLS_HPP

// *NEW - Can now target either glfw or SDL 1.3!
#ifdef __USE_SDL_PLEASE
#include <SDL/SDL.h>
#include "sdlapp.hpp"
void computeMatricesFromInputs( SDLApp& app );
#else
#include <GL/glfw.h>
void computeMatricesFromInputs();
#endif
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif