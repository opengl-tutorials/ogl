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

No olvides copiar el código continuamente.

**<span style="color: red"> Si el programa no funciona al iniciar, es probable que lo estes intentando correr desde la carpeta incorrecta. Lee detenidamente el tutorial 1 y configura correctamente Visual Studio !</span>**

## El VAO

No vamos a entrar en detalles ahora, pero se necesita crear un arreglo de objetos (Vertex Array Object) y tenerlo como el actual :

``` cpp
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
```

Haz esto una vez hayas creado tu ventana (= luego de haber creado el contexto OpenGL) y antes de cualquier llamada a una función OpenGL.

Si realmente quieres saber sobre los VAO, hay tutoriales por doquier, pero no es realmente importante .

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

Una nota aparte : Note que puedes mover tu mano libremente y con ella X, Y y Z. Le diremos mas el respecto luego.

Asi que necesitamos puntos 3D para hacer un triangulo, empecemos :

``` cpp
// Un arreglo de 3 vectores que representan 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
```

El primer vertice es (-1,-1,0). Esto significa que _amenos que lo transformemos de alguna forma_, se mostrará en (-1,-1) en la pantalla. ¿qué significa esto? El origen de la pantalla esta en el medio, X es a la derecha, y Y es arriba. Esto es lo que aparece en una pantalla amplia :

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}

Esto es algo que no se puede cambiar, viene asi desde la trajeta gráfica. Asi que (-1,-1) es la esquina inferior izquierda de su pantalla. (1,-1) es la esquina inferior derecha, y (0,1) es el medio arriba. Este triangulo va a tomar casi toda la pantalla.

## Dibujando nuestro triangulo

El siguiente paso es entregarle este triangulo a OpenGL. Hacemos esto creando un buffer :

``` cpp
// Identificar el vertex buffer
GLuint vertexbuffer;
// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
glGenBuffers(1, &vertexbuffer);
// Los siguientes comandos le darán caractrtísticas especiales al 'vertexbuffer' 
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Darle nuestros vertices a  OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
```

Esto solo debe hacerse una vez.

Ahora en nuestro ciclo principal, donde antes no dibujabamos "nada" ahora podemos dibujar nuestro majestuoso triangulo :

``` cpp
// 1rst attribute buffer : vertices
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // atributo 0. No hyar razon particular para el 0, pero debe corresponder en el shader.
   3,                  // tamaño
   GL_FLOAT,           // tipo
   GL_FALSE,           // normalizado?
   0,                  // Paso
   (void*)0            // desfase del buffer
);
// Dibujar el triangulo !
glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vertice 0S; 3 vertices en total -> 1 triangulo
glDisableVertexAttribArray(0);
```

Si tienes suerte veras el resultado (<span style="color: red">**No entres en panico si no.**</span>) :

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}

Este es un blanco aburrico. Vamos a ver cómo podemos mejorarlo pintando en rojo. Esto se hace con algo llamado shaders

## Shaders

# Compilación de shaders

En su configuración mas simple, necesitaras dos shaders: Uno llamado "vertex shader" (que se ejecuta una vez por cada pixel) y otro llamado "Fragment shader" (que se ejecuta una vez por cada muestra). Ya que usamos antialiasing 4x necesitamos 4 muestras por cada pixel.

Los shaders se programan en un lenguaje llamado GLSL, Gl Shader Language, que es parte de OpenGL. A diferencia de C o java, GLSL tiene que se compilado en tiempo de ejecución, lo que significa que cada vez que lances una aplicación, todos los shaders son recompilados.

Usualmente los dos shaders estan en archivos separados. En este ejemplo, tomamos SimpleFragmentShader.fragmentshader y SimpleVertexShader.vertexshader . La extensión es irrelevante, puede ser .txt o .glsl .

Y que aqui esta el cóodigo. No es tan importante que lo entiendas completamente, ya que es un programa que solo se mira una vez, los comentarios deberian ser suficientes. Ya que esta funcion la vamos a usar en otros programas, estara ubicada en common/loadShader.cpp . Nota que asi como los buffers, los shaders no son asequibles directamente, necesitamos un identificador. La implentación ya viene en el controlador.

``` cpp
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Crear los shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Leer el Vertex Shader desde archivo
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

	// Leer el Fragment Shader desde archivo
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


	// Compilar Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Revisar Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compilar Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Revisar Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Vincular el programa por medio del ID
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Revisar el programa
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

```

# Nuestro Vertex Shader

Vamos a escribir nuestro primer vertex shader.
La primera linea le dice al compilador que usaremos la sintaxis de OpenGL 3

``` glsl
#version 330 core
```

La segunda linea declara los datos de entrada :

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```

Vamos a explicar esto en detalle :

- "vec3" es un vector de 3 componentes en GLSL. Es similar al glm::vec3 que usamos para declarar nuestro triangulo. Lo importante es que si usamos 3 componentes en C++, usemos 3 componentes en GLSL también.
- "layout(location = 0)" se refiere al buffer que usamos para el atributo *vertexPosition_modelspace* . Cada vertice tiene varios atributos : una posición, uno o mas colores, una o mas coordenadas de textura y muchas otras cosas. OpenGL no sabe lo que es un color, solo ve un vec3. Asi que tenemos que decirle qué buffer corresponde a cual entrada. Eso lo hacemos asignando el mismo numero en ambas partes el diseño (layout) y el glVertexAttribPointer. El valor "0" no es importante, podría ser 12 (pero no mas que glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) ), lo importante es que sea el mismo numero en ambas partes.
- "vertexPosition_modelspace" puede tener otro nombre. Contendrá la posición del vertice para cada pasada del vertex shader.
- "in" significa que es algun tipo de datos de entrada. Pronto veremos la palabra clave "out.

La función que se llamará para cada vertice es llamada main, tal como en C : 

``` glsl
void main(){
```

Nuestra primera función simplemente le dara al vertice la posición guardada en el buffer. Asi que si le dimos (1,1), el triangulo tendrá uno de sus vertices arriba a la derecha en la pantalla. En el siguiente tutorial veremos cómo hacer calculos mas interesantes con la posición de entrada.

``` glsl
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
```

gl_Position es una de las pocas variables internas : tienes que asignarle un valor. Todo lo demás es opcional; Veremos lo que significan todas las demás en el tutorial 4.

# Nuestro Fragment Shader

Para nuestro primer fragment shader, haremos algo realmente simple : hacer que cada fragmento sea rojo. (Recuerda, hay 4 fragmentos por pixel por que usamos AA 4x)

``` glsl
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
```

Si, vec3(1,0,0) significa rojo. En las pantallas de computador, el color es representado por una tripla Rojo, verde y azul, en ese orden. Así que (1,0,0) significa solo rojo, no verde y no azul.

## Combinando todo

Antes del ciclo main, llamamos las funciones que cargan los shaders 'LoadShaders' :

``` cpp
// Crear y compilar el programa GLSL desde los shaders
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

Ahora dentro del ciclo principal, primero limpiar la pantalla. Esto pondrá el fondo de color azul oscuro dada la llamada a la instrucción glClearColor(0.0f, 0.0f, 0.4f, 0.0f) :

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

y luego decirle a OpenGl que queremos usar el shader:

``` cpp
// Use our shader
glUseProgram(programID);
// Draw triangle...
```

Y helo ahí, el triangulo rojo !

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

En el siguiente tutorial aprenderemos sobre transformaciones : Como iniciar la camara, mover objetos, etc.