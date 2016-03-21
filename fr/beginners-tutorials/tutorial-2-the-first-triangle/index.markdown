---
layout: page
status: publish
published: true
title: 'Tutoriel 2 : le premier triangle'
date: '2015-11-14 09:17:41 +0200'
categories: [tuto]
order: 20
tags: []
language: fr
---
{:TOC}

Cela va être un autre long tutoriel.

OpenGL 3 facilite l'écriture des choses compliquées, mais possède l'inconvénient de rendre l'affichage d'un simple triangle relativement difficile.

N'oublie pas de copier/coller le code régulièrement.

**<span style="color: red">Si le programme crashe au démarrage, tu l'exécute certainement à partir du mauvais répertoire. Lis PRÉCAUTIONNEUSEMENT le premier tutoriel sur comment configurer Visual Studio.</span>**

## Le VAO

On ne va pas s'enfoncer dans les détails maintenant, mais on doit créer un **V**ertex **A**rray **O**bject et le définir comment objet courant.

``` cpp
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
```

Fait-le une fois que ta fenêtre est créée (= après la création du contexte OpenGL) et avant tout autre appel OpenGL.

Si tu souhaite vraiment en apprendre plus sur les VAO, il y a quelques autres tutoriels sur le Web, mais ce n'est pas très important pour l'instant.

## Coordonnées écran

Un triangle est défini par trois points. Lorsque l'on parle de « points » en graphismes 3D, on utilise habituellement le terme de *sommet* (en anglais *vertex*, *vertices* au pluriel). Un sommet possède trois coordonnées : X, Y et Z. Tu peux imaginer ces trois coordonnées de la manière suivante 

- X est sur ta droite
- Y est vers le haut
- Z est derrière toi (oui, derrière et non devant).

Mais voici une meilleure méthode pour les visualiser : utilise la règle de la main droite :

- X est ton pouce
- Y est ton index
- Z est ton majeur. Si tu place ton pouce sur ta droite et ton index vers le ciel, ton majeur pointera aussi derrière ton dos.

Il est étrange d'avoir l'axe Z dans cette direction. Pourquoi est-ce ainsi ? Pour faire court : car 100 années de « règle de la main droite » te donneront des outils pratiques. La seule contrepartie est un axe Z contre-intuitif.

Mis à part cela, remarque aussi que tu peux bouger ta main librement : ton X, Y et Z suivront. On reviendra sur ce point.

Donc, on a besoin de trois points 3D afin de faire un triangle ; les voici :

``` cpp
// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
```

Le premier sommet est (-1, -1, 0). Cela signifie que, sauf si nous le transformons d'une quelconque manière, il sera affiché à la position (-1, -1) à l'écran. Qu'est-ce que cela donne ? L'origine de l'écran est au centre, l'axe X va vers la droite, comme toujours et l'axe Y vers le haut. Voici ce que cela donne sur un écran large :

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}

C'est une chose que tu ne peux pas modifier, c'est intégré dans ta carte graphique. Donc (-1, -1) est le coin inférieur gauche de votre écran. (1, -1) est le coin inférieur droit et (0, 1), le milieu haut. Donc ce triangle devrait couvrir la majorité de l'écran.

## Dessiner notre triangle

La prochaine étape est de fournir ce triangle à OpenGL. Pour cela il faut créer un *buffer* (Tampon en Français) :

``` cpp
// This will identify our vertex buffer
GLuint vertexbuffer;
// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);
// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
```

C'est nécessaire qu'une seule fois au lancement du programme.

Maintenant, la boucle principale, où on ne dessiner *rien* dans le premier tuto. On peut maintenant dessiner un fantastique triangle :

``` cpp
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
```

Si tu es chanceux, tu peux voir ce résultat (<span style="color: red">**Si tu vois rien, panique pas et continue !**</span>)

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}

C'est juste du blanc ennuyeux. Voyons voir comment l'améliorer en l'affichant en rouge. Cela peut être fait avec quelque chose appelé *shader*.

## Shaders

#Compilation de shader

Dans la configuration la plus simple, tu as besoin de deux shaders : un appelé *Vertex Shader*, qui sera exécuté pour chaque sommet et l'autre appelé *Fragment Shader*, qui sera exécuté pour chaque fragment. Comme on utilise un antialiasing 4x, on a quatre échantillons pour chaque pixel.

Les shaders se programment avec un langage appelé GLSL : *GL* *S*hader *L*anguage, qui est intégré à OpenGL. Contrairement au C ou au Java, le GLSL est compilé durant l'exécution du programme, ce qui signifie que chaque fois que tu lance ton application, tous tes shaders sont recompilés.

Les deux shaders sont généralement dans des fichiers distincts. Dans cet exemple, nous avons SimpleFragmentShader.fragmentshader et SimpleVertexShader.vertexshader. L'extension importe peu, cela aurait pu être .txt ou .glsl.

Voici enfin le code pour charger des shaders. Il n'est pas très important de le comprendre entièrement, car on ne l'utilise qu'une seule fois dans un programme, les commentaires suffiront. Comme cette fonction va être utilisée dans tous les autres tutoriels, elle est placée dans un fichier à part : common/loadShader.cpp. On peut remarquer que, comme les *buffer*, les shaders ne sont pas directement accessibles : on n'a qu'un identifiant. L'implémentation actuelle est cachée par le pilote.

``` cpp
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

```

#Notre vertex shader

Écrivons notre premier vertex shader.

La première ligne indique au compilateur que l'on va utiliser la syntaxe de OpenGL 3.

``` glsl
#version 330 core
```

La seconde ligne déclare les données d'entrées :

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```

Expliquons-la en détail :

- *vec3* est un vecteur de trois composantes dans le GLSL. Il est similaire (mais différent) au glm::vec3 que nous avons utilisé pour définir notre triangle. Le point important est que si on utilise trois composantes en C++, nous utilisons aussi trois composantes dans le GLSL
- *layout(location = 0)* se réfère au buffer (tampon) que l'on fournit à l'attribut *vertexPosition_modelspace*. Chaque sommet peut avoir de nombreux attributs : une position, une ou plusieurs couleurs, une ou plusieurs coordonnées de texture et plein d'autres choses. OpenGL ne sait pas ce qu'est une couleur : il ne voit qu'un vec3. Donc on doit lui dire quel tampon correspond à quelle entrée. Nous le faisons en définissant le *layout* à la même valeur que le premier paramètre de la fonction glVertexAttribPointer. La valeur *0* n'est pas importante, cela aurait pu être 12 (mais, elle ne peut être supérieure à glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v)), la chose importante est qu'elle soit la même des deux côtés
- *vertexPosition_modelspace* aurait pu être n'importe quoi. Il contiendra la position des sommets pour chaque exécution du vertex shader
- *in* signifie que ce sont des données d'entrée. Bientôt on va voir le mot clé *out*

La fonction qui est appelée pour chaque sommet est appelée main, tout comme en C :

``` glsl
void main(){
```

Notre fonction principale va simplement définir la position du vertex à ce qui est dans le buffer (tampon). Donc, si on donne (1, 1), le triangle aura l'un de ces sommets au coin supérieur droit de l'écran. On verra dans le prochain tutoriel comment effectuer des calculs plus intéressants sur les positions passées au shader.

``` glsl
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
```

*gl_Position* est l'une des rares variables codé en dur dans le langage : _vous devez assigner une valeur à celle-ci_. Tout le reste est optionnel ; on verra « tout le reste » dans le quatrième tutoriel.

#Notre fragment shader

Pour notre premier fragment shader, on va faire quelque chose de très simple : définir la couleur de chaque fragment à rouge. (Rappel-toi, il y a quatre fragments dans un pixel, car nous utilisons l'*A*nti-*A*liasing 4x.)

``` glsl
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
```

Donc voilà, *vec3(1,0,0)* signifie rouge. Cela est dû aux écrans d'ordinateur. La couleur est représentée par un triplet rouge, vert, bleu, dans cet ordre. Donc (1, 0, 0) indique complètement rouge, pas de vert et pas de bleu.

## Mettre tout ensemble

Avant la boucle principale, on appelle la fonction LoadShaders :

``` cpp
// Create and compile our GLSL program from the shaders
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

En premier, dans la boucle principale, on nettoie l'écran. Cela changera la couleur de fond en bleu foncé à cause de l'appel glClearColor(0.0f, 0.0f, 0.4f, 0.0f) au-dessus de la boucle principale.

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

Puis on indique à OpenGL que l'on souhaite les shaders vus précédemment :

``` cpp
// Use our shader
glUseProgram(programID);
// Draw triangle...
```

... et voilà ton triangle rouge !

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

Dans le prochain tutoriel, on étudiera les transformations : comment définir une caméra, déplacer les objets, etc.
