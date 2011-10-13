#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#ifdef __USE_SDL_PLEASE

GLuint loadTexture(const char * imagepath);

#else
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);

// Load a .TGA file using GLFW's own loader
GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);
#endif

#endif