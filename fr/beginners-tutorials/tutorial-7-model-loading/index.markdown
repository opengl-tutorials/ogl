---
layout: tutorial
status: publish
published: true
title: 'Tutoriel 7 : Charger un modèle 3D'
date: '2015-11-18 17:32:03 +0200'
categories: [tuto]
order: 70
tags: []
language: fr
---

Jusqu'à maintenant, on avait manuellement codé le cube dans le code source. Je suis sûr que vous êtes d'accord pour dire que c'est pénible et pas pratique.

Dans ce tutoriel, on apprendra à charger un modèle 3D à partir d'un fichier. On fera exactement comme on a fait pour les textures : on va écrire un simple et très limité chargeur de modèle 3D et je vais vous donner quelques pistes vers des bibliothèques qui le font mieux que nous.

Pour garder ce tutoriel aussi simple que possible, on utilisera le format de fichier OBJ, qui est à la fois simple et très commun. Une fois encore, pour garder les choses simples, on gérera les fichiers OBJ n'ayant qu'une coordonnée UV et qu'une normale par sommet (tu n'as pas à savoir ce qu'est une normale pour le moment).

# Charger le fichier OBJ

La fonction, située dans common/objloader.cpp, et déclarée dans common/objloader.hpp, aura la signature suivante :

``` cpp
bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
)
```

On souhaite que loadOBJ lise le fichier « path », écrive les données dans out_vertices/out_uvs/out_normals et retourne false si quelque chose s'est mal passé. *std::vector<glm::vec3>* est la façon de déclarer un tableau de glm::vec3 en C++ dont la taille peut être modifiée à volonté : cela n'a rien à voir avec un vecteur mathématique. Sincèrement, ce n'est qu'un tableau. Finalement, le & signifie que la fonction sera capable de modifier les std::vector.

## Exemple de fichier OBJ

Un fichier OBJ ressemble plus ou moins à ceci :
```

# Blender3D v249 OBJ File: untitled.blend
# www.blender3d.org
mtllib cube.mtl
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -1.000000
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 0.748573 0.750412
vt 0.749279 0.501284
vt 0.999110 0.501077
vt 0.999455 0.750380
vt 0.250471 0.500702
vt 0.249682 0.749677
vt 0.001085 0.750380
vt 0.001517 0.499994
vt 0.499422 0.500239
vt 0.500149 0.750166
vt 0.748355 0.998230
vt 0.500193 0.998728
vt 0.498993 0.250415
vt 0.748953 0.250920
vn 0.000000 0.000000 -1.000000
vn -1.000000 -0.000000 -0.000000
vn -0.000000 -0.000000 1.000000
vn -0.000001 0.000000 1.000000
vn 1.000000 -0.000000 0.000000
vn 1.000000 0.000000 0.000001
vn 0.000000 1.000000 -0.000000
vn -0.000000 -1.000000 0.000000
usemtl Material_ray.png
s off
f 5/1/1 1/2/1 4/3/1
f 5/1/1 4/3/1 8/4/1
f 3/5/2 7/6/2 8/7/2
f 3/5/2 8/7/2 4/8/2
f 2/9/3 6/10/3 3/5/3
f 6/10/4 7/6/4 3/5/4
f 1/2/5 5/1/5 2/9/5
f 5/1/6 6/10/6 2/9/6
f 5/1/7 8/11/7 6/10/7
f 8/11/7 7/12/7 6/10/7
f 1/2/8 2/9/8 3/13/8
f 1/2/8 3/13/8 4/14/8
```

Soit :

* '#'' est un commentaire, tout comme '//'' en C++
* usemtl et mtllib décrivent l'aspect du modèle. On ne les utilise pas de ce tutoriel
* v est un sommet
* vt est une coordonnée de texture (UV) pour un sommet
* vn est la normale pour un sommet
* f est une face

v, vt et vn sont simples à comprendre. f est un peu plus compliqué. Pour *f 8/11/7 7/12/7 6/10/7* :

* 8/11/7 décrit le premier sommet du triangle
* 7/12/7 décrit le second sommet du triangle
* 6/10/7 décrit le troisième sommet du triangle (doh)
* Pour le premier sommet, 8 indique quel sommet utiliser. Dans ce cas, ce sera donc -1.0000000 1.0000000 -1.0000000 (les indices commencent à partir de 1 et non pas de 0 comme en C++)
* 11 indique quelle coordonnée de texture utiliser. Dans ce cas, ce sera donc 0.748355 0.998230
* 7 indique quelle normale utiliser. Dans ce cas, ce sera donc 0.0000000 1.0000000 -0.0000000

Ces nombres sont appelés des indices. Ils sont pratiques, car si plusieurs sommets partagent la même position, vous n'avez qu'à écrire une seule fois « v » dans le fichier et l'utiliser plusieurs fois. Cela économise de la mémoire.

La mauvaise nouvelle est que l'on ne peut pas indiquer à OpenGL d'utiliser un indice pour la position, un autre pour la texture et un dernier pour la normale. Donc l'approche que j'ai choisie est de faire un modèle classique, non indexé et de gérer l'indexage plus tard, dans le neuvième tutoriel qui expliquera comment contourner cela.

## Créer un fichier OBJ avec Blender

Comme notre chargeur va être très limité, on doit être très précautionneux et définir les bonnes options lors de l'exportation du fichier. Voici comment cela devrait être dans Blender :

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/Blender.png)

## Lecture du fichier

Ok, voilà le code. On doit définir des variables temporaires dans lesquelles on stocke le contenu du .obj :

``` cpp
std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;
```

Depuis le [cinquième tutoriel : un cube coloré]({{site.baseurl}}/fr/beginners-tutorials/tutorial-5-a-textured-cube), on sais comment ouvrir un fichier :

``` cpp
FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
}
```

On le lit jusqu'à la fin :

``` cpp
while( 1 ){

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

    // else : parse lineHeader
```

> On fait l'hypothèse que le premier mot d'une ligne ne fait pas plus de 128 caractères, ce qui est une hypothèse très idiote. Mais c'est un chargeur pour s'amuser, donc c'est ok.

Premièrement, on s'occupe les sommets :

``` cpp
if ( strcmp( lineHeader, "v" ) == 0 ){
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    temp_vertices.push_back(vertex);
```

Si le premier mot de la ligne est 'v', alors le reste doit être trois nombres flottants, donc on crée un glm::vec3 à partir de ceux-ci et on l'ajoute au vecteur.

``` cpp
}else if ( strcmp( lineHeader, "vt" ) == 0 ){
    glm::vec2 uv;
    fscanf(file, "%f %f\n", &uv.x, &uv.y );
    temp_uvs.push_back(uv);
```

Si ce n'est pas 'v' mais un 'vt', alors le reste doit être deux flottants, donc on crée un glm::vec2 et on l'ajoute au vecteur.

Même chose pour les normales :

``` cpp
}else if ( strcmp( lineHeader, "vn" ) == 0 ){
    glm::vec3 normal;
    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
    temp_normals.push_back(normal);
```

Et maintenant le 'f', qui est plus difficile :

``` cpp
}else if ( strcmp( lineHeader, "f" ) == 0 ){
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9){
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
    }
    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices    .push_back(uvIndex[0]);
    uvIndices    .push_back(uvIndex[1]);
    uvIndices    .push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
```

Le code est en réalité très similaire au précédent, sauf qu'il y a plus de données à lire.

## Traiter les données

Donc, ce que l'on a fait c'est simplement changer la « forme » des données. On avait une chaîne de caractères, on a maintenant un ensemble de std::vector. Mais ce n'est pas suffisant, nous avons à mettre ceux-ci dans une forme que OpenGL aime. Plus précisément en retirant les indices et en ayant que des glm::vec3 à la place. Cette opération est appelée indexation.

On parcourt chaque sommet (chaque v/vt/vn) pour chaque triangle (chaque ligne avec un « f ») :

``` cpp
    // For each vertex of each triangle
    for( unsigned int i=0; i < vertexIndices.size(); i++ ){

```

L'indice de la position du sommet est *vertexIndices[i]* :

``` cpp
unsigned int vertexIndex = vertexIndices[i];
```

Donc la position est *temp_vertices[ vertexIndex-1 ]* (il y a un -1 car le C++ commence à compter à partir de 0 alors que l'indice du fichier OBJ débute à 1, tu te rappelez ?) :

``` cpp
glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
```

Et cela donne la position du nouveau sommet :

``` cpp
out_vertices.push_back(vertex);
```

La même chose est appliquée pour les UV et les normales et c'est fini !

# Utiliser les données chargées

Une fois que l'on a cela, il n'y a presque plus rien à faire. À la place de déclarer l'habituel static const GLfloat g_vertex_buffer_data[] = {...}, on déclare un std::vector de sommets (même chose pour les UV et les normales). Ensuite on appel la fonction loadOBJ avec les bons paramètres :

``` cpp
// Read our .obj file
std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
bool res = loadOBJ("cube.obj", vertices, uvs, normals);
```

Et envoie tes vecteurs à OpenGL à la place de tes tableaux :

``` cpp
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
```

And that's it !

# Résultat

Désolé pour la texture naze, je NE suis PAS un bon artiste :( Toute contribution est bienvenue !

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/ModelLoading.png)

# Autres formats/chargeurs

Ce petit chargeur devrait te suffire pour démarrer, mais ne sera d'aucune utilité dans la vraie vie. Regarde la page des [outils et liens utiles]({{site.baseurl}}/miscellaneous/useful-tools-links/) pour une sélection d'outils que tu peux utiliser. Note, par contre, qu'il est *préférable d'attendre le neuvième tutoriel* avant d'essayer d'utiliser l'un d'entre eux.
