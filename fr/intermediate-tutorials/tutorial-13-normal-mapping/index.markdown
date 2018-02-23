---
layout: tutorial
status: publish
published: true
title: 'Tutoriel 13 : Normal Mapping'
date: '2015-11-19 22:23:06 +0200'
categories: [tuto]
order: 530
tags: []
language: fr
---

* TOC
{:toc}

Bienvenue dans le treizième tutoriel ! Aujourd'hui on parle de normal mapping.

Depuis le [huitème tutoriel : shaders de base]({{site.baseurl}}/fr/beginners-tutorials/tutorial-8-basic-shading/), tu sais comment obtenir un ombrage décent en utilisant les normales des triangles. Jusqu'à présent, il existait un inconvénient : on n'avait qu'une seule normale par sommet dans chaque triangle et elle va varier doucement, contrairement aux couleurs, qui sont échantillonnées à partir d'une texture. L'idée de base de l'application des normales (normal mapping) est de donner aux normales des variations similaires.

# Textures de normales

Une « texture de normales » ressemble à ça :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normal.jpg)

Dans chaque texel RGB est encodé un vecteur XYZ : chacune des composantes d'une couleur est comprise entre 0 et 1 et chacune des composantes d'un vecteur est entre -1 et 1, donc la conversion d'un texel en normale s'effectue ainsi :

``` c
normal = (2*color)-1 // on each component
```

La texture a une teinte bleue car après tout, la normale pointe vers « l'extérieur de la surface ». Comme toujours X va vers la droite ( dans le plan de la texture), Y vers le haut (toujours dans le plan de la texture), et donc, avec la règle de la main droite, Z pointe vers l'extérieur du plan de la texture.

Cette texture est appliquée exactement comme la texture de diffusion ; le gros problème est la conversion de notre normale, qui est exprimée dans l'espace de chaque triangle (espace tangent, aussi appelé espace de l'image), vers l'espace modèle (car c'est ce que l'on utilise dans notre équation d'ombrage).

# Tangente et bitangente

Maintenant, que tu connais les matrices tellement bien que tu sais que pour définir un espace (dans notre cas, l'espace tangent), on a besoin de trois vecteurs. On a déjà le vecteur UP : c'est la normale, donnée par Blender ou calculée à partir du triangle à l'aide d'un produit scalaire. Elle est représentée en bleu, tout comme la teinte de la texture de normales :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/NormalVector.png)

Ensuite, on a besoin d'une tangente, T : un vecteur parallèle à la surface. Mais il y a vraiment beaucoup de vecteurs correspondant à ce critère :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/TangentVectors.png)

Lequel choisir ? En théorie, n'importe lequel, mais on doit être consistant avec ses voisins pour éviter de voir apparaître d'affreuses bordures. La méthode standard est d'orienter la tangente dans la même direction que les coordonnées de textures :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/TangentVectorFromUVs.png)

Comme on a besoin de trois vecteurs pour définir une base, on doit aussi calculer la bitangente B (qui peut être n'importe quel autre vecteur tangent, mais si tout est perpendiculaire, les calculs sont simplifiées) :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/NTBFromUVs.png)

Voici l'algorithme : si on appelle deltaPos1 et deltaPos2 deux côtés de notre triangle et deltaUV1 et deltaUV2 les différences de coordonnées UV correspondante, on peut exprimer notre problème avec l'équation suivante :

``` c
deltaPos1 = deltaUV1.x * T + deltaUV1.y * B
deltaPos2 = deltaUV2.x * T + deltaUV2.y * B
```

Résoud les équations de ce système pour T et B et tu obtiens tes vecteurs ! Voir le code ci-dessous.

Une fois que l'on a les vecteurs T, B et N, on obtient aussi cette jolie matrice qui nous permet de passer de l'espace tangent à l'espace modèle :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/TBN.png)

Avec cette matrice TBN, on peut transformer les normales (extraites à partir de la texture) dans l'espace modèle. Par contre, habituellement c'est l'inverse que l'on fait : transformer tout de l'espace modèle vers l'espace tangent et garder les normales telles quelles. Tous les calculs sont faits dans l'espace tangent, ce qui ne change absolument rien.

Pour effectuer cette transformation inverse, on doit simplement prendre l'inverse de la matrice, ce qui dans ce cas (une matrice orthogonale, où chaque vecteur est perpendiculaire aux autres. Voir la section « Aller plus loin ».) est aussi sa transposée, moins coûteuse à calculer :

``` c
invTBN = transpose(TBN)
```

Soit :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/transposeTBN.png)

# Préparation du VBO

## Calcul des tangentes et bitangentes

Comme les tangentes et bitangentes sont nécessaires en plus des normales, on doit les calculer pour la globalité du modèle. On fait cela dans une fonction à part :

``` cpp
void computeTangentBasis(
    // inputs
    std::vector<glm::vec3> & vertices,
    std::vector<glm::vec2> & uvs,
    std::vector<glm::vec3> & normals,
    // outputs
    std::vector<glm::vec3> & tangents,
    std::vector<glm::vec3> & bitangents
){
```

Pour chaque triangle, on calcule le côté (deltaPos) et le deltaUV.

``` cpp
    for ( int i=0; i < vertices.size(); i+=3){

        // Shortcuts for vertices
        glm::vec3 & v0 = vertices[i+0];
        glm::vec3 & v1 = vertices[i+1];
        glm::vec3 & v2 = vertices[i+2];

        // Shortcuts for UVs
        glm::vec2 & uv0 = uvs[i+0];
        glm::vec2 & uv1 = uvs[i+1];
        glm::vec2 & uv2 = uvs[i+2];

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;
```

On peut utiliser la formule pour calculer la tangente et la bitangente :

``` cpp
        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
```

Finalement, on remplit les tampons tangents et bitangents. Rappels-toi, ces tampons ne sont pas encore indexés, donc chaque sommet possède sa propre copie.

``` cpp
        // Set the same tangent for all three vertices of the triangle.
        // They will be merged later, in vboindexer.cpp
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        // Same thing for binormals
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);

    }
```

## Indexation

L'indexation du VBO est très similaire à ce que l'on avait l'habitude de faire, mais il y a une légère différence.

Si on trouve un sommet similaire (même position, même normale, même coordonnées de texture), on ne souhaite pas utiliser sa tangente et sa bitangente ; au contraire, on souhaite en faire la moyenne (entre ce sommet et celui similaire). Donc, modifie un peu le vieux code :

``` cpp
        // Try to find a similar vertex in out_XXXX
        unsigned int index;
        bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);

        if ( found ){ // A similar vertex is already in the VBO, use it instead !
            out_indices.push_back( index );

            // Average the tangents and the bitangents
            out_tangents[index] += in_tangents[i];
            out_bitangents[index] += in_bitangents[i];
        }else{ // If not, it needs to be added in the output data.
            // Do as usual
            [...]
        }
```

Remarque que l'on ne normalise rien ici. En réalité c'est pratique, car de cette façon, les petits triangles, qui ont une tangente et bitangente plus petites, auront un effet diminué sur le vecteur final par rapport aux grands triangles (qui contribueront plus à la forme finale).

# Le shader


## Tampons et variables uniformes supplémentaires

On a besoin de deux nouveaux buffer, un pour les tangentes, l'autre pour les bitangentes :

``` cpp
    GLuint tangentbuffer;
    glGenBuffers(1, &tangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &indexed_tangents[0], GL_STATIC_DRAW);

    GLuint bitangentbuffer;
    glGenBuffers(1, &bitangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &indexed_bitangents[0], GL_STATIC_DRAW);
```

On a aussi besoin d'une nouvelle variable uniforme pour notre nouvelle texture de normales :

``` cpp
    [...]
    GLuint NormalTexture = loadTGA_glfw("normal.tga");
    [...]
    GLuint NormalTextureID  = glGetUniformLocation(programID, "NormalTextureSampler");
```

Et d'une autre pour la matrice 3x3 de modèle-vue. Cela n'est pas strictement obligatoire, mais c'est plus simple ; plus d'informations là-dessus plus tard. On a besoin que de la partie 3 x 3 supérieure gauche car on va multiplier des directions : on peut donc se débarrasser de la partie liée à la translation.

``` cpp
    GLuint ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");
```

Au final le code de rendu complet donne :

``` cpp
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
        glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); // Take the upper-left part of ModelViewMatrix
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);

        glm::vec3 lightPos = glm::vec3(0,0,4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // Bind our diffuse texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
        // Set our "DiffuseTextureSampler" sampler to user Texture Unit 0
        glUniform1i(DiffuseTextureID, 0);

        // Bind our normal texture in Texture Unit 1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, NormalTexture);
        // Set our "Normal    TextureSampler" sampler to user Texture Unit 0
        glUniform1i(NormalTextureID, 1);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // 4th attribute buffer : tangents
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
        glVertexAttribPointer(
            3,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // 5th attribute buffer : bitangents
        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
        glVertexAttribPointer(
            4,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      // mode
            indices.size(),    // count
            GL_UNSIGNED_INT,   // type
            (void*)0           // element array buffer offset
        );

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);

        // Swap buffers
        glfwSwapBuffers();
```

## Vertex shader

Comme dit précédemment, on va tout faire dans l'espace de la caméra, car il est plus simple d'obtenir la position du fragment dans cet espace. C'est pourquoi on multiplie nos vecteurs T, B et N avec la matrice de modèle-vue.

``` glsl
    vertexNormal_cameraspace = MV3x3 * normalize(vertexNormal_modelspace);
    vertexTangent_cameraspace = MV3x3 * normalize(vertexTangent_modelspace);
    vertexBitangent_cameraspace = MV3x3 * normalize(vertexBitangent_modelspace);
```
{: .highlightglslfs }

Ces trois vecteurs définissent la matrice TBN, qui est créée de cette façon :

```

    mat3 TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    )); // You can use dot products instead of building this matrix and transposing it. See References for details.
```

Cette matrice passe de l'espace de la caméra à l'espace tangent (la même matrice, mais avec XXX_modelspace à la place, permettrai de passer de l'espace modèle à l'espace tangent). On peut l'utiliser pour calculer la direction de la lumière et la direction de l'œil, dans l'espace tangent :

```

    LightDirection_tangentspace = TBN * LightDirection_cameraspace;
    EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;
```

## Fragment shader

La normale, dans l'espace tangent, est immédiate à obtenir, c'est la texture :

``` glsl
    // Local normal, in tangent space
    vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, UV ).rgb*2.0 - 1.0);
```
{: .highlightglslfs }

Donc, on a tout ce dont nous avons besoin. La lumière diffuse utilise clamp(dot(n,l), 0, 1), avec n et l exprimé dans l'espace tangent (l'espace dans lequel on effectue nos produits scalaire et vectoriel n'importe pas ; la chose importante est que l et n soit tous les deux exprimés dans le même espace). La lumière spéculaire utilise clamp(dot(E,R), 0, 1), où, encore une fois, E et R sont exprimés dans l'espace tangent. Super !

# Résultats

Voici le résultat obtenu. Tu peux remarquer que :

* les briques semblent bosselées car on a de nombreuses variations dans les normales
* le ciment semble plat car la texture de normales est complètement bleue.

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normalmapping.png)

# Aller plus loin

## Orthogonalisation

Dans le vertex shader on prend la transposée au lieu de l'inverse, car c'est plus rapide. Mais cela ne fonctionne que si l'espace représenté par la matrice est orthogonal, ce qui n'est pas encore le cas à ce moment là. Heureusement, c'est facilement corrigeable : on doit simplement faire que la tangente soit perpendiculaire à la normale à la fin de computeTangentBasis() :

``` glsl
t = glm::normalize(t - n * glm::dot(n, t));
```
{: .highlightglslvs }

La formule peut être difficile à saisir, donc voici un petit schéma pour aider :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/gramshmidt.png)

n et t sont presque perpendiculaire, donc on « pousse » t dans la direction de -n multiplié par dot(n,t).

Avant il y avait [une petite application](http://www.cse.illinois.edu/iem/least_squares/gram_schmidt/) qui expliquait aussi cela (utilise seulement deux vecteurs si jamais elle remarche ^^).

## Règle de la main droite

Tu n'as normalement pas à t'en inquiéter, mais dans quelques cas, lorsque tu utilises des modèles symétriques, les coordonnées UV sont orientées dans le mauvais sens et ton T possède la mauvaise orientation.

Pour vérifier si elle doit être inversée ou pas, c'est simple : TBN doit former un système de coordonnées répondant à la règle de la main droite. Par exemple, cross(n,t) doit avoir la même orientation que b.

En mathématiques, « Un vecteur A à la même orientation qu'un vecteur B » se traduit par dot(A,B) > 0, donc on doit vérifier si dot(cross(n,t),b) > 0.

Si c'est incorrect, inversez t :

``` c
if (glm::dot(glm::cross(n, t), b) < 0.0f){
     t = t * -1.0f;
 }
```

Cela est aussi effectué pour chaque sommet à la fin de la fonction computeTangentBasis().

## Texture spéculaire

Pour le fun, j'ai ajouté une texture spéculaire au code. Ça ressemble à ça :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/specular.jpg)

et je l'ai utilisée pour remplacer le simple gris « vec3(0.3,0.3,0.3) » que l'on utilise pour la couleur spéculaire :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normalmappingwithspeculartexture.png)

Le ciment est toujours noir : la texture indique qu'il n'y a pas de composante spéculaire.

## Débogage avec le mode immédiat

Le vrai but de ce site Web est que **tu N'utilises PAS le mode immédiat**, qui est obsolète, lent et problématique en de nombreux aspects.

Par contre, il se trouve qu'il soit très pratique pour le débogage :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/immediatemodedebugging.png)

Ici, on observe notre espace tangent avec les lignes dessinées dans le mode immédiat.

Pour cela, tu dois abandonner le profil core 3.3 :

``` cpp
glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
```

Puis passer les matrices au vieux pipeline OpenGL (tu peux aussi écrire un autre shader, mais c'est plus simple de cette façon et tu es en train de bidouiller de toute façon) :

``` cpp
glMatrixMode(GL_PROJECTION);
glLoadMatrixf((const GLfloat*)&ProjectionMatrix[0]);
glMatrixMode(GL_MODELVIEW);
glm::mat4 MV = ViewMatrix * ModelMatrix;
glLoadMatrixf((const GLfloat*)&MV[0]);
```

Désactiver les shaders :

``` cpp
glUseProgram(0);
```

Et dessiner tes lignes (dans ce cas, les normales, normalisées et multipliées par 0.1 et appliquées au bon sommet) :

``` cpp
glColor3f(0,0,1);
glBegin(GL_LINES);
for (int i=0; i < indices.size(); i++){
    glm::vec3 p = indexed_vertices[indices[i]];
    glVertex3fv(&p.x);
    glm::vec3 o = glm::normalize(indexed_normals[indices[i]]);
    p+=o*0.1f;
    glVertex3fv(&p.x);
}
glEnd();
```

Rappel-toi : n'utilise pas le mode immédiat dans une vraie application ! Uniquement pour du débogage ! Et n'oublie pas de réactiver le profil core après coup, cela t'empêcheras d'utiliser le mode immédiat par inadvertence.

## Débogage avec les couleurs

Lors du débogage, il peut être utile de visualiser la valeur d'un vecteur. La façon la plus simple pour ce faire est d'écrire sa valeur dans le tampon d'image au lieu de la couleur actuelle. Par exemple, pour visualiser *LightDiretion_tangentspace* :

``` glsl
color.xyz = LightDirection_tangentspace;
```
{: .highlightglslfs }

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/colordebugging.png)

Cela signifie que :

* Sur la partie droite du cylindre, la lumière (représentée par la fine ligne blanche) est vers le HAUT (dans l'espace tangent). En d'autres mots, la lumière est dans la direction de la normale des triangles ;
* Sur le milieu du cylindre, la lumière est dans la direction de la tangente (avant+X).

Quelques conseils :

* Suivant ce que tu essayes de voir, tu peux souhaiter le normaliser
* Si tu ne comprends pas ce que tu vois, visualises toutes les composantes séparément en forçant par exemple le vert et le bleu à 0
* Evite de jouer avec l'alpha, c'est trop compliqué :)
* Si tu veux visualiser une valeur négative, tu peux utiliser la même astuce que celle pour notre texture de normales : visualise (v+1.0)/2.0 à la place. Le noir signifie -1 et la couleur +1. Toutefois, c'est pas toujurs facile d'interpréter le rendu.

## Débogage avec les noms des variables

Comme dit précédemment, il est important de connaître exactement dans quel espace vos vecteurs se trouvent. Ne faites pas le produit scalaire d'un vecteur situé dans l'espace de la caméra avec un vecteur dans l'espace modèle.

Ajouter l'espace de chaque vecteur à son nom (« ..._modelspace ») aide énormement à la correction de bogues mathématiques.

## Comment créer une texture de normales

Créé par James O'Hare. Clique pour agrandir :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normalMapMiniTut.jpg)

# Exercices

* Normalise les vecteurs dans indexVBO_TBN avant l'addition et vois ce que ça fait.
* Visualise les autres vecteurs (par exemple, EyeDirection_tangentspace) dans le mode de débogage avec les couleurs et essayez de comprendre ce que tu vois

# Outils et liens

* [Crazybump](http://www.crazybump.com/), un outil super pour faire des textures de normales. Payant.
* [Plugin Nvidia pour Photoshop](http://developer.nvidia.com/nvidia-texture-tools-adobe-photoshop). Gratuit, mais Photoshop ne l'est pas ...
* [Fais tes propres textures de normales à partir de plusieurs photos](http://www.zarria.net/nrmphoto/nrmphoto.html).
* [Faites vos propres textures de normales à partir d'une photo](http://www.katsbits.com/tutorials/textures/making-normal-maps-from-photographs.php).
* Plus d'informations sur la [transposition de matrices](http://www.katjaas.nl/transpose/transpose.html).

# References

* [Lengyel, Eric. “Computing Tangent Space Basis Vectors for an Arbitrary Mesh”. Terathon Software 3D Graphics Library, 2001.](http://www.terathon.com/code/tangent.html)
* [Real Time Rendering, troisième édition.](http://www.amazon.com/dp/1568814240)
* [ShaderX4](http://www.amazon.com/dp/1584504250)




