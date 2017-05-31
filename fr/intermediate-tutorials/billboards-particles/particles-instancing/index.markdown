---
layout: tutorial
status: publish
published: true
title: 'Particules/Instanciation'
date: '2015-11-21 15:23:39 +0200'
categories: []
order: 588
tags: []
language: fr
---

# Introduction

Les particules sont très similaires aux billboards 3D. Il y a toutefois quelques différences importantes :

* Il y a généralement énormément de particules
* Elles se déplacent
* Elles apparaissent et meurent
* Elles sont semi-transparentes

Toutes ces différences entraînent des problèmes. Ce tutoriel présente UNE solution pour les résoudre ; il y a beaucoup d'autres possibilités.

# Des particules, plein partout !

La première idée pour dessiner une multitude de particules serait d'utiliser le code du tutoriel précédent et d'appeler glDrawArrays pour chaque particule. C'est une très mauvaise idée, car cela signifie que l'ensemble de tes superbes multiprocesseurs GTX 512+ seront tous utilisés pour ne dessiner qu'UN unique rectangle (évidemment, un seul sera utilisé, perdant 99 % d'efficacité). Puis tu vas dessiner le billboard suivant et cela sera identique.

Clairement, on doit trouver une méthode pour dessiner toutes les particules en même temps.

Il y a plusieurs façons pour le faire ; en voici trois :

* Générer un seul VBO avec toutes les particules à l'intérieur. Facile, efficace, fonctionne sur toutes les plates-formes
* Utiliser les geometry shaders. Ce n'est pas exploré dans ce tutoriel, notamment parce que 50 % des ordinateurs ne les supportent pas (en 2012)
* Utiliser l'instanciation. Ce n'est pas disponible sur TOUTES les plates-formes, mais une grande majorité de celles-ci.

Dans ce tutoriel, nous allons utiliser la troisième option : c'est un bon compromis entre les performances et la disponibilité et par-dessus tout, il est facile d'ajouter le support de la première méthode une fois que celle-ci fonctionne.

## Instanciation

« Instanciation » signifie que l'on a un modèle de base (dans ce cas, un simple rectangle fait de deux triangles), mais de nombreuses instances de ce rectangle.

Techniquement, cela s'effectue avec plusieurs buffers (tampons) :

* Certains pour décrire le modèle de base
* D'autres pour décrire les particularités de chaque instance du modèle de base

Tu as de nombreuses, très nombreuses options sur ce que tu mets dans chaque buffer. Dans notre cas basique on a :

* Un buffer pour les sommets du modèle. Pas de buffer d'indices, donc c'est 6 vec3, constituant deux triangles, qui font un rectangle
* Un buffer pour le centre des particules
* Un buffer pour la couleur des particules

Ce sont des buffers standards. Ils sont créés de cette façon :

``` cpp
// The VBO containing the 4 vertices of the particles.
// Thanks to instancing, they will be shared by all particles.
static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
};
GLuint billboard_vertex_buffer;
glGenBuffers(1, &billboard_vertex_buffer);
glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

// The VBO containing the positions and sizes of the particles
GLuint particles_position_buffer;
glGenBuffers(1, &particles_position_buffer);
glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
// Initialize with empty (NULL) buffer : it will be updated later, each frame.
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

// The VBO containing the colors of the particles
GLuint particles_color_buffer;
glGenBuffers(1, &particles_color_buffer);
glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
// Initialize with empty (NULL) buffer : it will be updated later, each frame.
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
```

Ce qui est habituel. Ils sont mis à jour de cette façon :

``` cpp
// Update the buffers that OpenGL uses for rendering.
// There are much more sophisticated means to stream data from the CPU to the GPU,
// but this is outside the scope of this tutorial.
// http://www.opengl.org/wiki/Buffer_Object_Streaming

glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);

glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);
```

Ce qui est aussi habituel. Ils sont liés avant le rendu de cette façon :
 

``` cpp
// 1rst attribute buffer : vertices
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
glVertexAttribPointer(
 0, // attribute. No particular reason for 0, but must match the layout in the shader.
 3, // size
 GL_FLOAT, // type
 GL_FALSE, // normalized?
 0, // stride
 (void*)0 // array buffer offset
);

// 2nd attribute buffer : positions of particles' centers
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
glVertexAttribPointer(
 1, // attribute. No particular reason for 1, but must match the layout in the shader.
 4, // size : x + y + z + size => 4
 GL_FLOAT, // type
 GL_FALSE, // normalized?
 0, // stride
 (void*)0 // array buffer offset
);

// 3rd attribute buffer : particles' colors
glEnableVertexAttribArray(2);
glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
glVertexAttribPointer(
 2, // attribute. No particular reason for 1, but must match the layout in the shader.
 4, // size : r + g + b + a => 4
 GL_UNSIGNED_BYTE, // type
 GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
 0, // stride
 (void*)0 // array buffer offset
);
```

Ce qui est aussi normal. La différence vient lors du rendu. Au lieu d'utiliser glDrawArrays (ou glDrawElements si votre modèle de base possède un tampon d'indices), on utilise glDrawArraysInstanced/glDrawElementsInstanced, qui est équivalent à appeler N fois glDrawArrays (N est le dernier paramètre, dans notre cas ParticlesCount).

``` cpp
glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);
```

Mais il manque quelque chose ici. On n'a pas indiqué à OpenGL quel buffer était pour le modèle de base et lesquels sont pour les différentes instances. Cela se fait avec glVertexAttribDivisor. Voici le code complet commenté :

``` cpp
// These functions are specific to glDrawArrays*Instanced*.
// The first parameter is the attribute buffer we're talking about.
// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
glVertexAttribDivisor(2, 1); // color : one per quad -> 1

// Draw the particules !
// This draws many times a small triangle_strip (which looks like a quad).
// This is equivalent to :
// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
// but faster.
glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);
```

Comme vous pouvez le voir, l'instanciation est très polyvalente, car tu peux passer n'importe quel entier comme AttribDivisor. Par exemple, avec glVertexAttribDivisor(2, 10), chaque groupe de dix instances aura la même couleur.

## Quel est le but ?

Le but est que maintenant, on doit seulement mettre à jour un petit buffer à chaque image (le centre des particules) et non plus un immense modèle. C'est un gain de 75 % pour la bande passante !

# Vie et mort

Contrairement à la plupart des objets de la scène, les particules meurent et naissent à un grand débit. On doit trouver une méthode convenablement rapide pour obtenir de nouvelles particules et se débarrasser d'elles, quelque chose de mieux que new Particle().

## Créer de nouvelles particules

Pour cela, on doit avoir un grand conteneur de particules :

``` cpp
// CPU representation of a particle
struct Particle{
	glm::vec3 pos, speed;
	unsigned char r,g,b,a; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if < 0 : dead and unused.

};

const int MaxParticles = 100000;
Particle ParticlesContainer[MaxParticles];
```

Maintenant, on a besoin d'une méthode pour en créer. Cette fonction recherche linéairement dans ParticlesContainer, ce qui est une idée horrible, sauf qu'elle démarre au dernier emplacement connu, donc cette fonction retourne généralement immédiatement :

``` cpp
int LastUsedParticle = 0;

// Finds a Particle in ParticlesContainer which isn't used yet.
// (i.e. life < 0);
int FindUnusedParticle(){

    for(int i=LastUsedParticle; i<MaxParticles; i++){
        if (ParticlesContainer[i].life < 0){
            LastUsedParticle = i;
            return i;
        }
    }

    for(int i=0; i<LastUsedParticle; i++){
        if (ParticlesContainer[i].life < 0){
            LastUsedParticle = i;
            return i;
        }
    }

    return 0; // All particles are taken, override the first one
}
```

On peut maintenant remplir ParticlesContainer[particleIndex] avec des valeurs intéressantes pour life, color, speed et position. Voir le code pour les détails, mais tu peux faire ce que tu veux ici. La seule chose intéressante est, comment plusieurs particules doivent être générées à chaque image ? C'est principalement dépendant de l'application, donc prenons un taux de 10 000 nouvelles particules par seconde (oui, c'est plutot beaucoup) :

``` cpp
int newparticles = (int)(deltaTime*10000.0);
```

Sauf que on devrait restreindre cela a une nombre fixe :

``` cpp
// Generate 10 new particule each millisecond,
// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
// newparticles will be huge and the next frame even longer.
int newparticles = (int)(deltaTime*10000.0);
if (newparticles > (int)(0.016f*10000.0))
    newparticles = (int)(0.016f*10000.0);
```

## Supprimer les vieilles particules

Il y a une astuce, comme montré ci-dessous =)

# La boucle principale de simulation

*ParticlesContainer* contient aussi bien les particules actives que les « mortes », mais le tampon que l'on envoie au GPU ne doit avoir que les particules vivantes.

Donc, on va parcourir chaque particule, vérifier si elle est vivante, si elle doit mourir, et si tout est correct, ajouter un peu de gravité, puis finalement la copier dans un buffer GPU spécifique.

``` cpp
// Simulate all particles
int ParticlesCount = 0;
for(int i=0; i<MaxParticles; i++){

    Particle& p = ParticlesContainer[i]; // shortcut

    if(p.life > 0.0f){

        // Decrease life
        p.life -= delta;
        if (p.life > 0.0f){

            // Simulate simple physics : gravity only, no collisions
            p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
            p.pos += p.speed * (float)delta;
            p.cameradistance = glm::length2( p.pos - CameraPosition );
            //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

            // Fill the GPU buffer
            g_particule_position_size_data[4*ParticlesCount+0] = p.pos.x;
            g_particule_position_size_data[4*ParticlesCount+1] = p.pos.y;
            g_particule_position_size_data[4*ParticlesCount+2] = p.pos.z;

            g_particule_position_size_data[4*ParticlesCount+3] = p.size;

            g_particule_color_data[4*ParticlesCount+0] = p.r;
            g_particule_color_data[4*ParticlesCount+1] = p.g;
            g_particule_color_data[4*ParticlesCount+2] = p.b;
            g_particule_color_data[4*ParticlesCount+3] = p.a;

        }else{
            // Particles that just died will be put at the end of the buffer in SortParticles();
            p.cameradistance = -1.0f;
        }

        ParticlesCount++;

    }
}
```

Voici ce que t'obtiens. Presque réussi, mais il y a un souci ...

![]({{site.baseurl}}/assets/images/tuto-particules/particles_unsorted.png)

## Tri

Comme expliqué dans le [dixième tutoriel]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-10-transparency/), tu dois trier les objets semi-transparents du plus loin au plus proche pour que le mélange soit correct.

``` cpp
void SortParticles(){
    std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticles]);
}
```

Maintenant, *std::sort* nécessite une fonction qui peut indiquer si une particule doit être placée avant ou après une autre particule dans le conteneur. Ça peut être fait avec Particle::operator< :

```

// CPU representation of a particle
struct Particle{

    ...

    bool operator<(Particle& that){
        // Sort in reverse order : far particles drawn first.
        return this->cameradistance > that.cameradistance;
    }
};
```

Ça permet de trier ParticleContainer et les particules vont maintenant être affichées correctement[^1] :

![]({{site.baseurl}}/assets/images/tuto-particules/particles_final.gif)

# Aller plus loin

## Particules animées

Tu peux animer ta texture de particules avec une texture atlas. Envoie *l'âge* de chaque particule avec la position et dans les shaders, calcule les coordonnées UV comme on l'a fait dans le [tutoriel de police 2D]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-11-2d-text/). Une texture atlas ressemble à ça :

![]({{site.baseurl}}/assets/images/tuto-particules/ParticleAtlas.png)

## Gérer plusieurs systèmes de particules

Si tu as besoin de plus d'un système de particules, tu as deux options : soit utiliser un seul ParticleContainer, soit un par système.

Si vous avez un seul conteneur pour toutes les particules, alors tu vas être capable de parfaitement les trier. Le principal inconvénient est que tu dois utiliser la même texture pour toutes les particules, ce qui est un gros problème. Cela peut être corrigé en utilisant une texture atlas (une grande texture avec toutes les différentes textures sur celle-ci, ayant simplement des coordonnées UV différentes), mais ce n'est pas vraiment pratique pour l'éditer et l'utiliser.

Si tu as un conteneur par système de particules, d'un autre côté, les particules seront seulement triées dans ces conteneurs : si deux systèmes de particules se superposent, des artefacts apparaîtront. Suivant ton application, ça peut ne pas être un souci.

Bien sûr, tu peux aussi utiliser un système hybride avec plusieurs systèmes de particules et chacun avec un (petit et gérable) atlas.

## Particules douces

Tu vas remarquer très rapidement un artefact classique : lorsque tes particules croisent une géométrie, la limite devient très visible et moche :

![]({{site.baseurl}}/assets/images/tuto-particules/ParticleHardSmooth.jpg)

(image provenant de [http://www.gamerendering.com/2009/09/16/soft-particles/](http://www.gamerendering.com/2009/09/16/soft-particles/)).

Une technique classique pour corriger cela est de tester si le fragment actuellement dessiné est proche du Z-buffer (buffer de profondeur). Si c'est le cas, le fragment est fondu (= tout de même rendu mais avec plus de transparence).

Par contre, tu vas devoir échantillonner le Z-buffer (buffer de profondeur), ce qui n'est pas possible avec le Z-buffer « normal ». Tu dois afficher ta scène dans une [render target]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-14-render-to-texture/). Sinon, tu peux copier le Z-buffer à partir d'un framebuffer vers un autre avec glBlitFramebuffer.

[http://developer.download.nvidia.com/whitepapers/2007/SDK10/SoftParticles_hi.pdf](http://developer.download.nvidia.com/whitepapers/2007/SDK10/SoftParticles_hi.pdf)

## Amélioration du taux de remplissage

L'un des facteurs les plus limitants dans les GPU modernes est le taux de remplissage : le nombre de fragments (pixels) que le GPU peut écrire en 16,6 ms, permis pour obtenir 60 FPS.

C'est un problème, car les particules nécessitent typiquement un GRAND taux de remplissage, comme tu dois redessiner le même fragment dix fois, chaque fois avec une particule spécifique ; et si tu ne le fait pas, tu vas obtenir les mêmes artefacts que précédemment.

Parmi tous les fragments qui sont écrits, la plupart sont complètement inutiles : ceux se trouvant sur la bordure. Vos textures de particules sont souvent complètement transparentes sur les bordures, mais le modèle de particule continuera de les dessiner - et mettre à jour le buffer de couleur avec exactement la même valeur que précédemment.

Ce petit utilitaire calcule un modèle (celui que tu es supposé dessiner avec glDrawArrayInstanced()), qui correspond précisément à ta texture :

![](http://www.humus.name/Cool/ParticleTrimmer.jpg)

[http://www.humus.name/index.php?page=Cool&ID=8](http://www.humus.name/index.php?page=Cool&ID=8). Le site de Emil Person contient plein d'autres articles fascinant.

## Physique des particules

Au bout d'un moment, tu vas probablement souhaiter que tes particules interagissent un peu plus avec le reste de l'environement. En particulier, les particules pourraient rebondir sur le sol.

Tu pourrais simplement lancer un rayon pour chaque particule, entre la position actuelle et la prochaine ; on apprend à le faire dans les [tutoriels de Picking]({{site.baseurl}}/miscellaneous/clicking-on-objects/picking-with-a-physics-library/). Mais c'est très coûteux. simplement, tu ne peux pas le faire pour chaque particule, à chaque image, et garder un bon fps.

Suivant ton application, tu peux aussi approximer ta géométrie avec un ensemble de plans et faire un lancer de rayon sur ces plans uniquement ; ou tu peux utiliser un vrai lancer de rayon, mais mettre en cache le résultat et approcher les collisions alentour avec le cache (ou tu peux faire les deux).

Une technique complètement différente est d'utiliser le Z-buffer existant tel une approximation très brute de la géométrie (visible) et faire collisionner les particules avec celle- ci. C'est « assez efficace » et rapide, mais tu vas devoir effectuer toute la simulation sur le GPU, car tu ne peux pas accéder au tampon de profondeur à partir du CPU (du moins, pas rapidement), donc c'est bien plus compliqué.

Voici quelques liens sur ces techniques :

[http://www.altdevblogaday.com/2012/06/19/hack-day-report/](http://www.altdevblogaday.com/2012/06/19/hack-day-report/)

[http://www.gdcvault.com/search.php#&category=free&[...]](http://www.gdcvault.com/search.php#&category=free&firstfocus=&keyword=Chris+Tchou's%2BHalo%2BReach%2BEffects&conference_id=)

## Simulation GPU

Comme indiqué précédemment, tu peux complètement simuler le mouvement des particules sur le GPU. Tu vas toujours devoir gérer le cycle de vie de tes particules sur le CPU - au moins pour les faire apparaître.

Tu as plusieurs options pour ce faire et aucune ne rentre dans le champ de ce tutoriel ; je vais juste donner quelques pointeurs.

* Utiliser le retour de transformation (Transform Feedback). Cela te permet de stocker les sorties du vertex shader dans un VBO côté GPU. Stocke la nouvelle position dans ce VBO et à la prochaine image, utilise ce VBO comme point de départ et stocke les nouvelles positions dans le premier VBO.
* Même chose, mais sans le retour de transformation : encode vos positions de particules dans une texture et mettez-la à jour en faisant un rendu dans cette texture ([tutoriel 14]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-14-render-to-texture/)).
* Utiliser une bibliothèque GPU généraliste : CUDA ou OpenCL, qui possède des fonctions d'interopérabilité avec OpenGL.
* Utilisez un compute shader. La solution la plus propre, mais seulement disponible sur les GPU récents (en 2012).


[^1] Pour des raisons de simplicité, dans cette implémentation, ParticleContainer est trié après la mise à jour des tampons GPU. Cela fait que les particules ne sont pas exactement triées (il y a un délai d'une image), mais ce n'est pas vraiment remarquable. Tu peux corriger cela en séparant la boucle principale en deux. Simule, trie puis met à jour.
