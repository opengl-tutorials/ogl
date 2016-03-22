---
layout: page
status: publish
published: true
title: 'Tutoriel 4 : un cube coloré'
date: '2015-11-16 21:47:1 +0200'
categories: [tuto]
order: 40
tags: []
language: fr
---

Bienvenue dans le quatrième tutoriel ! Dans celui-ci on va :
* Afficher un cube au lieu d'un ennuyeux triangle
* Ajouter de jolies couleur
* Apprendre ce qu'est le Z-buffer (tampon de profondeur)

# Afficher un cube

Un cube possède six faces carrées. Comme OpenGL ne connaît que les triangles, on doit dessiner douze triangles : deux pour chaque face. On définit les sommets de la même façon que pour le triangle.   

``` cpp
// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
```

Le tampon OpenGL est créé, lié, rempli et configuré avec les fonctions de base (glGenBuffers, glBindBuffer, glBufferData, glVertexAttribPointer) ; lisez le [deuxième tutoriel](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/) pour un rappel rapide. L'appel pour l'affichage ne change pas non plus, vous avez simplement à donner le bon nombre de sommets à dessiner :

``` cpp
// Draw the triangle !
glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
```

Quelques remarques sur ce code :

* Pour l'instant, nos modèles 3D sont fixes : afin de les modifier, on doit changer le code source, recompiler l'application et prier que tout aille bien. On apprendra comment charger dynamiquement les modèles dans le [septième tutoriel](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/)
* Chaque sommet est écrit au moins trois fois (cherchez la ligne « -1.0f,-1.0f,-1.0f » dans le code ci-dessus). C'est une incroyable perte de mémoire. On apprendra comment gérer cela dans le [neuvième tutoriel](http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/).

Tu as maintenant tous les morceaux pour dessiner le cube en blanc. Fait fonctionner les shaders ! Allez va y, ou au moins, essaye :)

# Ajouter des couleurs

Une couleur est, conceptuellement, exactement identique à une position : ce ne sont que des données. Avec les mots d'OpenGL, ce sont des « attributs ». En fait, on les a déjà utilisés avec glEnableVertexAttribArray() et glVertexAttribPointer(). On ajoute un autre attribut à chaque sommet. Le code va ressembler à celui pour les positions.

D'abord, déclare des couleurs : un triplet RGB par sommet. Ici, j'en ai généré quelques-uns aléatoirement, donc le résultat ne sera pas beau, mais tu peux faire mieux, par exemple en copiant la position des sommets pour définir sa couleur.

``` cpp
// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
```

Le buffer (tampon) est créé, lié et rempli de la même façon que le précédent :

``` cpp
GLuint colorbuffer;
glGenBuffers(1, &colorbuffer);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
```

La configuration est identique, elle aussi :

``` cpp
// 2nd attribute buffer : colors
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glVertexAttribPointer(
    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    3,                                // size
    GL_FLOAT,                         // type
    GL_FALSE,                         // normalized?
    0,                                // stride
    (void*)0                          // array buffer offset
);
```

Maintenant, dans le vertex shader, on accède au nouveau buffer (tampon) :

``` glsl
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;
```
{: .highlightglslvs }

Dans notre cas, on ne fait rien de fantaisiste dans le vertex shader. On envoie simplement la couleur au fragment shader :

``` glsl
// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

void main(){

    [...]

    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    fragmentColor = vertexColor;
}
```
{: .highlightglslvs }

Dans le fragment shader, on déclare encore une fois *fragmentColor* :

``` glsl
// Interpolated values from the vertex shaders
in vec3 fragmentColor;
```
{: .highlightglslfs }

... et on la copie dans la couleur finale de sortie :

``` glsl
// Ouput data
out vec3 color;

void main(){
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    color = fragmentColor;
}
```
{: .highlightglslfs }

Et voici ce que l'on obtient :

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/missing_z_buffer.png)

Argh. Horrible. Pour comprendre ce qui se passe, voici un schéma de ce qui se produit lorsque vous dessinez un triangle « au loin » et ensuite un triangle « proche » :

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/FarNear.png)

Cela semble ok. Maintenant si on dessine le triangle « au loin » en deuxième :

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/NearFar.png)

Il recouvre le triangle « proche » même s'il est supposé être derrière ! C'est ce qui se passe avec notre cube : certaines faces sont supposées être cachées, mais comme elles sont dessinées après, elles sont visibles. Le tampon de profondeur (Z-buffer) va venir à la rescousse !

>Si tu ne voit pas le problème, change la position de ta caméra à (4,3,-3)

>Si « la couleur est comme une position, c'est un attribut », pourquoi doit-on déclarer *out vec3 fragmentColor* ; et *in vec3 fragmentColor* ; pour la couleur et pas pour la position ? Car la position est un peu spéciale : c'est la seule qui est obligatoire (sinon OpenGL ne saurait pas où dessiner le triangle !). Donc, dans le vertex shader, gl_Position est une variable intégrée du langage.

# Le Z-Buffer (tampon de profondeur)

La solution à ce problème est de conserver la profondeur ('Z') de chaque fragment dans un tampon et pour toutes les fois où on veut écrire un fragment, on vérifiez d'abord si on peut le faire (si le nouveau fragment est plus proche que l'ancien).

On pourrait le faire nous-même, mais c'est beaucoup plus simple de demander au matériel de le faire :

``` cpp
// Enable depth test
glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
glDepthFunc(GL_LESS);
```

On doit aussi nettoyer le tampon de profondeur à chaque image, au lieu de ne le faire que pour la couleur :

``` cpp
// Clear the screen
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

Et ça suffit pour régler tous nos problèmes.

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/one_color_per_vertex.png)

# Exercices

* Dessine le cube ET le triangle à deux emplacements différents. Tu auras besoin de générer deux matrices MVP, de faire deux appels pour l'affichage dans la boucle principale, mais seulement un shader est nécessaire.

* Génére les valeurs des couleurs toi-même. Quelques idées : aléatoirement, de manière à ce que les couleurs changent à chaque exécution ; dépendantes de la position des sommets ; un mélange des deux ; quelques idées créatives :). Au cas où tu ne connais pas la syntaxe en C++, la voici :

``` cpp
static GLfloat g_color_buffer_data[12*3*3];
for (int v = 0; v < 12*3 ; v++){
    g_color_buffer_data[3*v+0] = your red color here;
    g_color_buffer_data[3*v+1] = your green color here;
    g_color_buffer_data[3*v+2] = your blue color here;
}
```

* Une fois que tu as fait ça, modifie les couleurs à chaque affichage. Tu dois appeler glBufferData à chaque image. Assure-toi que le tampon approprié est lié (glBindBuffer).
