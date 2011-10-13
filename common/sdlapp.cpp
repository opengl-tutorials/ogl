#include "sdlapp.hpp"

SDLApp::SDLApp( std::string wtitle, int w, int h, int depth, int glVersion[], bool doubleBuffer, bool vsync, bool fullscreen )
: running(true), _mousewheel(0), rx(w), ry(h), frames(0), fps(0)
{
	Uint32 flags = SDL_WasInit( 0 );
	if( !( flags & SDL_INIT_VIDEO ) && !( flags & SDL_INIT_TIMER ) ) {
		if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 ) throw SDLexc();
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glVersion[0]);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glVersion[1]);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	if( doubleBuffer == true ) SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth);	// This seems to crash the OpenGL context
														// May or may not be a SDL problem

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if( fullscreen == true ) windowFlags |= SDL_WINDOW_FULLSCREEN;
	this->wnd = SDL_CreateWindow(
				wtitle.c_str(),
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				w, h,
				windowFlags
			);
	
	if( this->wnd == NULL ) {
		this->setErrorFromSDL( );
		return;
	}
	
	this->ctx = SDL_GL_CreateContext( this->wnd );
	
	if( SDL_GL_MakeCurrent( this->wnd, this->ctx ) != 0 ) {
		this->setErrorFromSDL( );
		return;
	}
	
	glewExperimental = GL_TRUE;
	if( glewInit() != GLEW_OK ) {
		this->setError( "Could not initialize glew" );
		return;
	}
	
	SDL_GL_SetSwapInterval( (vsync==true)?1:0 );
	
	SDL_ShowCursor(0);
	
	this->timer = SDL_GetTicks()+1000;
}
SDLApp::~SDLApp( ) {
	if( this->wnd != NULL ) SDL_DestroyWindow( this->wnd );
	this->wnd = NULL;
	SDL_Quit( );
}
void SDLApp::setWindowTitle( const std::string& newtitle ) {
	SDL_SetWindowTitle( this->wnd, newtitle.c_str() );
}
void SDLApp::getResolution( int *x, int *y ) {
	*x = rx;
	*y = ry;
}
void SDLApp::setMouse( int x, int y ) {
	int appw=0, apph=0;
	int px=0, py=0;
	SDL_GetWindowSize( this->wnd, &appw, &apph );
	px = x;
	py = y;
	if( x < 0 ) px = appw/2;
	if( y < 0 ) py = apph/2;
	SDL_WarpMouseInWindow( this->wnd, px, py );
}
Uint8 SDLApp::getMouse( int *x, int *y ) {
	return SDL_GetMouseState( x, y );
}
bool SDLApp::getKey( int key ) {
	for( std::vector< int >::iterator it = this->keys.begin(); it != this->keys.end(); ++it) {
		if( *it == key ) return true;
	}
	return false;
}
int SDLApp::getMouseWheel( void ) {
	return this->_mousewheel;
}
void SDLApp::handleInput( void ) {
	SDL_Event e;
	bool found = false;
	
	while( SDL_PollEvent( &e ) ) {
		switch( e.type ) {
		case SDL_KEYDOWN:
			found = false;
			for( std::vector< int >::iterator it = this->keys.begin(); it != this->keys.end(); ++it) {
				if( *it == e.key.keysym.sym ) { found = true; break; }
			}
			if( found == false ) { this->keys.push_back( e.key.keysym.sym ); }
			if( e.key.keysym.sym == SDLK_ESCAPE ) {
				this->running = false;
				return;
			}
			break;
		case SDL_KEYUP:
			for( std::vector< int >::iterator it = this->keys.begin(); it != this->keys.end(); ++it) {
				if( *it == e.key.keysym.sym ) {
					this->keys.erase( it );
					break;
				}
			}
			break;
		case SDL_MOUSEWHEEL:
			this->_mousewheel += ((e.wheel.y<0)?-1:((e.wheel.y>0)?1:0));
			break;
		case SDL_QUIT:
			this->running = false;
			break;
		}
	}
	
	return;
}
void SDLApp::glSwap( ) {
	SDL_GL_SwapWindow( this->wnd );
	this->frames++;
	Uint32 now = SDL_GetTicks();
	if( now > (this->timer) ) {
		this->timer = now + 1000;
		this->fps = this->frames;
		this->frames = 0;
	}
}
bool SDLApp::keepRunning( void ) {
	return this->running;
}
bool SDLApp::hasError( std::string& errorStr ) {
	errorStr = this->errorMessage;
	return (this->errorMessage.size()>0)?true:false;
}
int SDLApp::getFramesPerSecond( void ) {
	return this->fps;
}
void SDLApp::setErrorFromSDL( void ) {
	if( SDL_HasError( ) ) 
		this->SetError( "SDL Error: " + std::string( SDL_GetError( ) ) );
	else
		this->clearError( );
}
void SDLApp::setError( std::string message ) {
	this->errorMessage = message;
	if( message.size()>0 ) this->running = false;	// Kill app if there's an error. (Necessary?)
}
void SDLApp::clearError( void ) {
	this->setError( "" );
}
