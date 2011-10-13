
#include <GL3/gl3w.h>

#include <SDL/SDL.h>
#include <string>
#include <vector>

#ifndef __opengltutorial_sdlapp
#define __opengltutorial_sdlapp	1

	class SDLApp {
	public:
		SDLApp( std::string wtitle, int w, int h, int depth, int glVersion[], bool doubleBuffer=true, bool vsync=false, bool fullscreen=false );
		
		~SDLApp( );
		
		void setWindowTitle( const std::string& newtitle );
		
		void getResolution( int *x, int *y );
		
		void setMouse( int x, int y );
		
		Uint8 getMouse( int *x, int *y );
		
		bool getKey( int key );
		
		int getMouseWheel( void );
		
		void handleInput( void );
		
		void glSwap( );
		
		bool keepRunning( void );
		
		bool hasError( std::string& errorStr );
		
		int getFramesPerSecond( void );
		
	private:
		void setErrorFromSDL( void );
		void setError( std::string message );
		void clearError( void );
		
		SDL_Window		*wnd;
		SDL_GLContext	ctx;
		bool			running;
		std::vector< int > keys;
		int				_mousewheel;
		int				rx, ry;
		Uint32			timer;
		int				frames;
		int				fps;
		std::string		errorMessage;
	};

#endif