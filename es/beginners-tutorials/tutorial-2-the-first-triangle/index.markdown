---
layout: page
status: publish
published: true
title: 'Tutorial 2 : The first triangle'
date: '2011-04-07 18:54:11 +0200'
date_gmt: '2011-04-07 18:54:11 +0200'
categories: [tuto]
order: 20
tags: []
language: es
---
{:TOC}

Este será otro tutorial largo .

OpenGL 3 hace que sea facil escrbiir las cosas complicadas a cambio de dibujar un solo triangulo de forma un poco complicada.

No olvide copiar el código continuamente.

**<span style="color: red"> Si el programa no funciona al iniciar, es probable que lo este intentando correr desde la carpeta incorrecta. Lea detenidamente el tutorial 1 y configure correctamente Visual Studio !</span>**

## El VAO

No vamos a entrar en detalles ahora, pero se necesita crear un arreglo de objetos (Vertex Array Object) y tenerlo como el actual :

{% highlight cpp linenos %}
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
{% endhighlight %}

Haga esto una vez haya creado su ventana (= luego de haber creado el contexto OpenGL) y antes de cualquier llamada a una función OpenGL.

Si realmente quiere saber sobre los VAO, hay tutoriales por doquier, pero no es realmente importante .

## Coordenadas de la pantalla

Un triangulo es definido por tres puntos. Cuando hablamos de puntos en computación gráfica, usualmente usamos la palabra "vertice". Un vertice tiene 3 coordenadas : X, Y, y Z, puede pensar en estas tres coordenadas asi :

- X es su derecha
- Y es hacia arriba
- Z es hacia atrás (si, hacia atrás, no hacia el frente)

Pero hay una mejor forma de visualizar esto : la regla de la mano derecha

- X es su pulgar
- Y es su dedo indice
- Z es su dedo corazón 
- Si usted pone su dedo pulgar hacia la derecha y su dedo indice hacia arriba, su dedo corazón apuntará hacia usted.

Tener la coordenada Z en esta dirección no es intuitivo, ¿Por qué? en resumen : porque 100 años de la regla de la mano derecha le va a dar a usted muchas herramientas matemáticas que le harán la vida mas sencilla, todo a cambio de esta pequeña incomodidad de tener el Z al revés.

Una nota aparte : Note que usted puede mover su mano libremente y con ella X, Y y Z. Le diremos mas el respecto luego.

Asi que necesitamos puntos 3D para hacer un triangulo, empecemos :

{% highlight cpp linenos %}
// Un arreglo de 3 vectores que representan 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
{% endhighlight %}

El primer vertice es (-1,-1,0). Esto significa que _amenos que lo transformemos de alguna forma_, se mostrará en (-1,-1) en la pantalla. ¿qué significa esto? El origen de la pantalla esta en el medio, X es a la derecha, y Y es arriba. Esto es lo que aparece en una pantalla amplia :

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}

Esto es algo que no se puede cambiar, viene asi desde la trajeta gráfica. Asi que (-1,-1) es la esquina inferior izquierda de su pantalla. (1,-1) es la esquina inferior derecha, y (0,1) es el medio arriba. Este triangulo va a tomar casi toda la pantalla.

##Dibujando nuestro triangulo

El siguiente paso es entregarle este triangulo a OpenGL. Hacemos esto creando un buffer :

{% highlight cpp linenos %}
// Identificar el vertex buffer
GLuint vertexbuffer;
// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
glGenBuffers(1, &vertexbuffer);
// Los siguientes comandos le darán caractrtísticas especiales al 'vertexbuffer' 
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);{% endhighlight %}

This needs to be done only once.

Now, in our main loop, where we used to draw "nothing", we can draw our magnificent triangle :

{% highlight cpp linenos %}
// 1rst attribute buffer : vertices
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
   3,                  // size
   GL_FLOAT,           // type
   GL_FALSE,           // normalized?
   0,                  // stride
   (void*)0            // array buffer offset
);
// Draw the triangle !
glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
glDisableVertexAttribArray(0);
{% endhighlight %}

If you're on lucky, you can see the result (<span style="color: red">**don't panic if you don't**</span>) :

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}

Now this is some boring white. Let's see how we can improve it by painting it in red. This is done by using something called shaders.

## Shaders

# Shader Compilation

In the simplest possible configuration, you will need two shaders : one called Vertex Shader, which will be executed for each vertex, and one called Fragment Shader, which will be executed for each sample. And since we use 4x antialising, we have 4 samples in each pixel.

Shaders are programmed in a language called GLSL : GL Shader Language, which is part of OpenGL. Unlike C or Java, GLSL has to be compiled at run time, which means that each and every time you launch your application, all your shaders are recompiled.

The two shaders are usually in separate files. In this example, we have SimpleFragmentShader.fragmentshader and SimpleVertexShader.vertexshader . The extension is irrelevant, it could be .txt or .glsl .

So here's the code. It's not very important to fully understand it, since you often do this only once in a program, so comments should be enough. Since this function will be used by all other tutorials, it is placed in a separate file : common/loadShader.cpp . Notice that just as buffers, shaders are not directly accessible : we just have an ID. The actual implementation is hidden inside the driver.

{% highlight cpp linenos %}
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

{% endhighlight %}

# Our Vertex Shader

Let's write our vertex shader first.
The first line tells the compiler that we will use OpenGL 3's syntax.

{% highlight glsl linenos %}
#version 330 core
{% endhighlight %}

The second line declares the input data :

{% highlight glsl linenos %}
layout(location = 0) in vec3 vertexPosition_modelspace;
{% endhighlight %}

Let's explain this line in detail :

- "vec3" is a vector of 3 components in GLSL. It is similar (but different) to the glm::vec3 we used to declare our triangle. The important thing is that if we use 3 components in C++, we use 3 components in GLSL too.
- "layout(location = 0)" refers to the buffer we use to feed the *vertexPosition_modelspace* attribute. Each vertex can have numerous attributes : A position, one or several colours, one or several texture coordinates, lots of other things. OpenGL doesn't know what a colour is : it just sees a vec3. So we have to tell him which buffer corresponds to which input. We do that by setting the layout to the same value as the first parameter to glVertexAttribPointer. The value "0" is not important, it could be 12 (but no more than glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) ), the important thing is that it's the same number on both sides.
- "vertexPosition_modelspace" could have any other name. It will contain the position of the vertex for each run of the vertex shader.
- "in" means that this is some input data. Soon we'll see the "out" keyword.

The function that is called for each vertex is called main, just as in C :

{% highlight glsl linenos %}
void main(){
{% endhighlight %}

Our main function will merely set the vertex' position to whatever was in the buffer. So if we gave (1,1), the triangle would have one of its vertices at the top right corner of the screen. We'll see in the next tutorial how to do some more interesting computations on the input position.

{% highlight glsl linenos %}
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
{% endhighlight %}

gl_Position is one of the few built-in variables : you *have *to assign some value to it. Everything else is optional; we'll see what "everything else" means in Tutorial 4.

# Our Fragment Shader

For our first fragment shader, we will do something really simple : set the color of each fragment to red. (Remember, there are 4 fragment in a pixel because we use 4x AA)

{% highlight glsl linenos %}
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
{% endhighlight %}

So yeah, vec3(1,0,0) means red. This is because on computer screens, colour is represented by a Red, Green, and Blue triplet, in this order. So (1,0,0) means Full Red, no green and no blue.

## Putting it all together

Before the main loop, call our LoadShaders function :

{% highlight cpp linenos %}
// Create and compile our GLSL program from the shaders
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
{% endhighlight %}

Now inside the main loop, first clear the screen. This will change the background color to dark blue because of the previous glClearColor(0.0f, 0.0f, 0.4f, 0.0f) call:

{% highlight cpp linenos %}
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
{% endhighlight %}

and then tell OpenGL that you want to use your shader:

{% highlight cpp linenos %}
// Use our shader
glUseProgram(programID);
// Draw triangle...
{% endhighlight %}

... and presto, here's your red triangle !

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

In the next tutorial we'll learn transformations : How to setup your camera, move your objects, etc.
