---
layout: page
status: publish
published: true
title: 'Tutoriel 16 : Shadow mapping'
date: '2015-11-21 09:29:49 +0200'
categories: [tuto]
order: 80
tags: []
language: fr
---

# Introduction

Dans le [quinzième tutoriel]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-15-lightmaps/), on a appris à créer des lightmaps, qui incluent l'éclairage statique. Bien que cela produise de ombres vraiment belles, ça ne gère pas les modèles animés.

Les shadow maps (textures d'ombre) sont la technique actuelle (en 2012) pour créer des ombres dynamiques. Leur bon point c'est qu'elles sont relativement faciles à mettre en place. En contrepartie, c'est extrêmement difficile de les faire fonctionner *correctement*.

Dans ce tutoriel, on introduira l'algorithme de base, on verra ses défauts et on implémentera quelques techniques pour obtenir de meilleurs résultats. Sachant qu'au moment de l'écriture (2012), les textures d'ombre sont un sujet de recherche d'actualité, on donnera quelques directions pour te permettre d'améliorer tes propres textures d'ombre, suivant tes besoins.

# Shadowmap basique

L'algorithme des shadowmap de base se décompose en deux passes. Premièrement, la scène est dessinée à partir de la position de la lumière. Seule la profondeur de chaque fragment est calculée. Ensuite, la scène est affichée comme d'habitude, mais avec un test supplémentaire pour vérifier si le fragment actuel est dans l'ombre.

Le test « être dans l'ombre » est vraiment très simple. Si l'échantillon actuel est plus éloigné de la lumière que la texture d'ombre au même point, cela signifie que la scène contient un objet plus proche de la lumière. En d'autres termes, le fragment actuel est dans l'ombrage.

L'image suivante aide à comprendre le principe :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/shadowmapping.png)


## Génération de la shadow map

Dans ce tutoriel, on ne considérera que les lumières directionnelles - lumières qui sont si loin que l'on peut considérer les rayons comme étant parallèles. Ainsi, la génération de la texture d'ombre est effectuée avec une matrice de projection orthographique. Une matrice de projection orthographique est exactement comme une matrice de projection en perspective, sauf qu'aucune perspective n'est prise en compte - un objet sera identique indépendamment de sa distance avec la caméra.

### Configurer le renderbuffer et la matrice MVP

Depuis le [quatorzième tutoriel]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-14-render-to-texture/), tu sais comment dessiner une scène dans une texture afin d'y accéder plus tard à partir d'un shader.

Ici, on utilise une texture de profondeur 1024x1024 sur 16 bits pour stocker la texture d'ombre. 16 bits sont généralement suffisants pour une texture d'ombre. Libre à toi d'expérimenter avec d'autres valeurs.

> On utilise une texture de profondeur et non pas un renderbuffer pour la profondeur, car on a besoin de l'échantillonner par la suite.

``` cpp
 // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
 GLuint FramebufferName = 0;
 glGenFramebuffers(1, &FramebufferName);
 glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

 // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
 GLuint depthTexture;
 glGenTextures(1, &depthTexture);
 glBindTexture(GL_TEXTURE_2D, depthTexture);
 glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

 glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

 glDrawBuffer(GL_NONE); // No color buffer is drawn to.

 // Always check that our framebuffer is ok
 if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
 return false;
```

La matrice MVP utilisée pour dessiner la scène du point de vue de la lumière est calculée comme suit :

* La matrice de projection est une matrice orthographique incluant tout ce qui est compris dans une [boîte alignée aux axes](https://en.wikipedia.org/wiki/Minimum_bounding_box#Axis-aligned_minimum_bounding_box) de (-10, 10), (-10, 10), (-10, 20) sur les axes X, Y et Z, respectivement. Ces valeurs ont été choisies pour que toute la partie visible de la scène soit toujours visible ; plus d'informations sur ce point dans la section : voir plus loin
* Notre matrice de vue tournera le monde afin que, dans l'espace caméra, la direction de la lumière soit -Z (Envie de refaire un tour dans le [troisième tutoriel]({{site.baseurl}}/fr/beginners-tutorials/tutorial-3-matrices/) ?)
* La matrice de modèle est peut importe ce que tu veux.

``` cpp
glm::vec3 lightInvDir = glm::vec3(0.5f,2,2);

 // Compute the MVP matrix from the light's point of view
 glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
 glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
 glm::mat4 depthModelMatrix = glm::mat4(1.0);
 glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

 // Send our transformation to the currently bound shader,
 // in the "MVP" uniform
 glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0])
```

### Les shaders

Les shaders utilisés durant cette passe sont très simples. Le vertex shader est un shader passant les données au fragment shader qui calcule simplement la position des sommets en coordonnées homogènes :

``` glsl
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 depthMVP;

void main(){
 gl_Position =  depthMVP * vec4(vertexPosition_modelspace,1);
}
```
{: .highlightglslvs }

Le fragment shader est tout aussi simple : il écrit la profondeur du fragment à l'emplacement 0 (c'est-à-dire dans la texture de profondeur).

``` glsl
#version 330 core

// Ouput data
layout(location = 0) out float fragmentdepth;

void main(){
    // Not really needed, OpenGL does it anyway
    fragmentdepth = gl_FragCoord.z;
}
```
{: .highlightglslfs }

Le rendu d'une shadow map est généralement deux fois plus rapide qu'un rendu normal, car seule une profondeur en faible précision est écrite, au lieu de la profondeur *et* de la couleur. La bande passante mémoire est souvent le plus grand problème de performance sur les GPU.

### Résultat

La texture ressemble à ça :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/DepthTexture.png)

Une couleur sombre signifie un petit z ; donc, le coin supérieur droit du mur est proche de la caméra. Au contraire, le blanc signifie z=1 (en coordonnées homogènes), donc que l'élément est très loin.

## Utiliser la shadow map

### Shader de base

Maintenant, on retourne à notre shader habituel. Pour chaque fragment que l'on calcule, on doit tester s'il se trouve « derrière » la texture d'ombre ou pas.

Pour ce faire, on doit calculer la position actuelle du fragment dans le même espace que celui que nous avons utilisé lors de la création de la texture d'ombre. Donc, on doit le transformer avec la matrice MVP habituelle et une seconde fois avec la matrice MVP de la passe de profondeur (depthMVP).

Il y a tout de même une petite astuce. La multiplication de la position du sommet avec la matrice depthMVP donnera des coordonnées homogènes, qui sont comprises entre [-1, 1]. Mais l'échantillonnage d'une texture doit être fait entre [0, 1].

Par exemple, un fragment au milieu de l'écran sera en (0, 0) dans l'espace de coordonnées homogènes. Mais comme il devra correspondre au milieu de la texture, les coordonnées UV devront être (0.5, 0.5).

Cela peut être corrigé en ajustant les coordonnées directement dans le fragment shader, mais c'est plus efficace de multiplier les coordonnées homogènes avec la matrice suivante, qui divise simplement les coordonnées par 2 (la diagonale : [-1, 1]-> [-0.5, 0.5]) et les déplace (la ligne du bas : [-0.5, 0.5]-> [0, 1]).

``` cpp
glm::mat4 biasMatrix(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);
glm::mat4 depthBiasMVP = biasMatrix*depthMVP;
```

On peut maintenant écrire le vertex shader. Il est identique au précédent, mais on écrit deux positions au lieu d'une :

* gl_Position est la position du sommet tel qu'il est vu par la caméra actuelle.
* ShadowCoord est la position du sommet tel qu'il est vu à partir de l'ancienne caméra (la lumière).

``` glsl
// Output position of the vertex, in clip space : MVP * position
gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

// Same, but with the light's view matrix
ShadowCoord = DepthBiasMVP * vec4(vertexPosition_modelspace,1);
```
{: .highlightglslvs }

Ensuite, le fragment shader est très simple :

* texture(shadowMap, ShadowCoord.xy).z est la distance entre la lumière et l'objet le plus proche
* ShadowCoord.z est la distance entre la lumière et le fragment actuel

Donc si le fragment actuel est plus loin que l'objet le plus proche, cela signifie que l'on se trouve dans l'ombre (de objet plus proche) :

``` glsl
float visibility = 1.0;
if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z){
    visibility = 0.5;
}
```
{: .highlightglslfs }

On a juste besoin d'utiliser ça pour modifier l'ombrage. Bien sûr, la couleur ambiante n'est pas modifiée, car son but est d'imiter une lumière arrivant même lorsqu'on se trouve dans l'ombrage (ou sinon tout ce qui est dans l'ombre serait complètement noir).

``` glsl
color =
 // Ambient : simulates indirect lighting
 MaterialAmbientColor +
 // Diffuse : "color" of the object
 visibility * MaterialDiffuseColor * LightColor * LightPower * cosTheta+
 // Specular : reflective highlight, like a mirror
 visibility * MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5);
```
{: .highlightglslfs }

### Résultat - acné d'ombre

Voici le résultat du code actuel. Évidemment, l'idée générale est présente, mais la qualité est inacceptable.

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/1rstTry.png)

On va regarder chacun des problèmes de l'image dans les sections suivantes. Le code possède deux projets : shadowmaps et shadowmaps_simple : commence par celui que tu préféres. La version simple est tout aussi laide que l'image ci-dessus, mais plus facile à comprendre.

# Problèmes

## Acné d'ombre

Le problème le plus évident s'appelle *shadow acne* (acné de d'ombre) :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/ShadowAcne.png)

Ce phénomène est facilement explicable avec une image :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/shadow-acne.png)

Le « correctif » habituel pour ça consiste à utiliser une marge d'erreur : on n'ajoute l'ombre que si la profondeur du fragment actuel (encore une fois, dans l'espace de la lumière) est vraiment loin de la valeur de la texture de lumière. On fait ça en ajoutant un biais :

``` glsl
float bias = 0.005;
float visibility = 1.0;
if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z-bias){
    visibility = 0.5;
}
```
{: .highlightglslfs }

Le résultat est déjà beaucoup plus beau :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/FixedBias.png)

Par contre, tu peux remarquer qu'à cause de notre biais, l'artefact entre le sol est le mur s'est empiré. Qui plus est, un biais de 0.005 semble trop important pour le sol, mais pas assez pour les surfaces arrondies : quelques artefacts sont toujours visibles sur le cylindre et la sphère.

Une approche commune consiste à modifier le biais suivant la pente :

``` glsl
float bias = 0.005*tan(acos(cosTheta)); // cosTheta is dot( n,l ), clamped between 0 and 1
bias = clamp(bias, 0,0.01);
```
{: .highlightglslfs }

L'acné d'ombrage n'est plus là, même sur les surfaces arrondies :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/VariableBias.png)

Une autre astuce qui peut ou non fonctionner suivant vos modèles est d'afficher seulement les faces arrière dans la texture d'ombre. Cela force à utiliser une scène spécifique (voir la prochaine section - Peter Panning) avec les murs fins. Mais au moins, l'acné sera sur les surfaces qui sont dans l'ombre (on la verra donc pas) :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/shadowmapping-backfaces.png)

Lors du rendu de la texture d'ombre, supprime les faces avant des triangles :

``` cpp
        // We don't use bias in the shader, but instead we draw back faces,
        // which are already separated from the front faces by a small distance
        // (if your geometry is made this way)
        glCullFace(GL_FRONT); // Cull front-facing triangles -> draw only back-facing triangles
```

Et ensuite, affiche la scène avec un rendu normal (suppression des faces arrière) :

``` cpp
         glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles
```

Cette méthode est utilisée dans le code, en plus du biais.

## Peter Panning

On n'a plus d'acné d'ombrages, mais on a toujours un mauvais ombrage sur le sol, faisant comme si les murs volaient (d'où le terme « Peter Panning »). En fait, en ajoutant le biais, c'est devenu pire.

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/PeterPanning.png)

Celui-ci est très facile à corriger : évite tout simplement les géométries sans épaisseurs. Ça a deux avantages :

* Premièrement, ça corrige le « Peter Panning » : si ta géométrie est plus épaisse que le biais, tout est bon
* Deuxièmement, tu peux réactiver la suppression des faces arrière lors du rendu de la texture de lumière, car maintenant, il y a un polygone du mur qui fait face à la lumière et donc cache l'autre côté, qui n'aurait pas été affiché avec la suppression des faces arrière.

L'inconvénient est que tu as plus de triangles à afficher (deux fois par image !).

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/NoPeterPanning.png)

## Aliasing

Mais avec ces deux astuces, tu vas remarquer qu'il y a toujours du crénelage sur le bord de l'ombre. En d'autres termes, un pixel est blanc et le prochain noir, sans même de transition douce entre les deux.

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/Aliasing.png)

### PCF

La façon la plus simple d'améliorer ça est de changer le type d'échantillonnage de la texture d'ombre en shadow2DShadow. La conséquence est que, lorsque tu échantillonnes une fois, le matériel fera en réalité aussi un échantillonnage des pixels voisins, une comparaison entre eux et retournera un nombre à virgule flottante compris dans [0, 1] avec un filtrage bilinéaire du résultat de la comparaison.

Par exemple, 0.5 signifie que deux échantillons sont dans l'ombre et deux échantillons dans la lumière.

> Ce n'est pas la même chose qu'un échantillonnage simple d'une texture de profondeur filtrée ! Une comparaison retourne toujours vrai ou faux ; PCF donne une interpolation de quatre « vrai ou faux ».

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/PCF_1tap.png)

Comme vous pouvez le voir, les bordures de l'ombre sont douces, mais la texture d'ombre est toujours visible.

###Échantillonnage de Poisson

Une méthode simple pour le gérer est d'échantillonner la texture d'ombre N fois au lieu d'une seule. En combinaison avec le PCF, cela peut donner de très bons résultats, même avec un petit N. Voici le code pour quatre échantillonnages :

``` glsl
for (int i=0;i<4;i++){
  if ( texture( shadowMap, ShadowCoord.xy + poissonDisk[i]/700.0 ).z  <  ShadowCoord.z-bias ){
    visibility-=0.2;
  }
}
```
{: .highlightglslfs }

poissonDisk est un tableau constant qui peut être défini comme suit :

``` glsl
vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);
```
{: .highlightglslfs }

De cette façon, suivant le nombre d'échantillon de la shadow map qui passe le test, le fragment généré sera plus ou moins sombre :

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/SoftShadows.png)

La constante 700.0 définit la « diffusion » des échantillons. Si la diffusion est trop petite, on obtient du *crénelage* ; si la diffusion est trop importante, on a alors des *bandes* (cette capture n'utilise pas PCF pour accentuer l'effet, mais utilise 16 échantillons à la place).

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/SoftShadows_Close.png)

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/SoftShadows_Wide.png)

###Échantillonnage de Poisson stratifié

On peut supprimer cet effet de bande en choisissant différents échantillons pour chaque pixel. Il y a deux méthodes principales : l'échantillonnage de Poisson *stratifié* ou de Poisson *tourné*. Le *stratifié* choisit différents échantillons, le *tourné* toujours les mêmes, mais avec une rotation aléatoire afin qu'ils semblent différents. Dans ce tutoriel, je vais expliquer seulement la version stratifiée.

La seule différence avec la version précédente est que l'on indexe poissonDisk avec un indice aléatoire :

``` glsl
    for (int i=0;i<4;i++){
        int index = // A random number between 0 and 15, different for each pixel (and each i !)
        visibility -= 0.2*(1.0-texture( shadowMap, vec3(ShadowCoord.xy + poissonDisk[index]/700.0,  (ShadowCoord.z-bias)/ShadowCoord.w) ));
    }
```
{: .highlightglslfs }

On peut générer un nombre aléatoire avec une ligne comme celle-ci, qui retourne un nombre entre [0, 1[ :

``` glsl
    float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
    return fract(sin(dot_product) * 43758.5453);
```
{: .highlightglslfs }

Dans notre cas, seed4 sera une combinaison de i (faisant que l'on échantillonne à quatre emplacements différents) et ... quelque chose d'autre. On peut utiliser gl_FragCoord (l'emplacement du pixel sur l'image) ou Position_worldspace :

``` glsl
        //  - A random sample, based on the pixel's screen location.
        //    No banding, but the shadow moves with the camera, which looks weird.
        int index = int(16.0*random(gl_FragCoord.xyy, i))%16;
        //  - A random sample, based on the pixel's position in world space.
        //    The position is rounded to the millimeter to avoid too much aliasing
        //int index = int(16.0*random(floor(Position_worldspace.xyz*1000.0), i))%16;
```
{: .highlightglslfs }

Cela fera que les motifs de l'image ci-dessus vont disparaître, au détriment d'un bruit visuel. Mais au final un bruit correctement distribué soit souvent moins désagréable que les motifs précédents.

![]({{site.baseurl}}/assets/images/tuto-16-shadow-mapping/PCF_stratified_4tap.png)

Regarde le fichier [tutorial16/ShadowMapping.fragmentshader](https://github.com/opengl-tutorials/ogl/blob/master/tutorial16_shadowmaps/ShadowMapping.fragmentshader) pour les trois exemples d'implémentation.

# Aller plus loin

Même avec toutes ces astuces, il reste de nombreuses, très nombreuses méthodes pour améliorer tes ombres. Voici les plus répandues :

## Early bailing

Au lieu de prendre seize échantillons pour chaque fragment (encore une fois, c'est beaucoup), on prend quatre échantillons distants. S'ils sont tous dans la lumière ou dans l'ombre, tu peux sûrement considérer que les seize échantillons auraient donné le même résultat : tu peux arrêter tout de suite (bail early). Si certains sont différents, tu es probablement sur une bordure d'ombre, donc les seize sont nécessaires.

## Spot lights

La gestion des lumières de type "spots" nécessite quelques petites modifications. La plus évidente est de changer la matrice de projection orthographique pour une matrice de projection en perspective :

``` cpp
glm::vec3 lightPos(5, 20, 20);
glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0f, 1.0f, 2.0f, 50.0f);
glm::mat4 depthViewMatrix = glm::lookAt(lightPos, lightPos-lightInvDir, glm::vec3(0,1,0));
```

Même chose, mais avec une pyramide tronquée de matrice de perspective à la place de celle de la matrice orthographique. Utilise texture2Dproj pour prendre en compte la division de la perspective (voir les notes de bas de pages du troisième tutoriel sur les matrices).

La seconde étape consiste à prendre en compte la perspective dans le shader (voir les notes de bas de pages du troisième tutoriel sur les matrices aussi). En résumé, une matrice de projection perspective n'a en fait pas besoin d'effectuer de perspective. Cela est effectué par le matériel, lors de la division avec la coordonnée projetée w. Ici, on émule la transformation dans le shader, donc on doit effectuer la division de la perspective. D'ailleurs, une matrice orthographique génère toujours des vecteurs homogènes avec w = 1, faisant qu'elle ne produit jamais de perspective.

Voici deux façons de faire cela en GLSL. La seconde utilise la fonction du langage textureProj, mais les deux méthodes produisent le exactement le même résultat.

``` glsl
if ( texture( shadowMap, (ShadowCoord.xy/ShadowCoord.w) ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
if ( textureProj( shadowMap, ShadowCoord.xyw ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )
```
{: .highlightglslfs }

## Lumières ponctuelles

Même chose, mais avec une cubemap (carte cubique) de profondeur. Une cubemap est un ensemble de six textures, une pour chaque côté du cube. De plus, l'accès ne se fait pas avec des coordonnées UV standard, mais avec un vecteur 3D représentant une direction.

La profondeur est conservée pour chaque direction dans l'espace, rendant possible la projection des ombres tout autour de la lumière ponctuelle.

## Combination of several lights

L'algorithme gère plusieurs lumières, mais garde à l'esprit que chaque lumière nécessite un rendu supplémentaire de la scène afin de produire la carte d'ombres. Cela nécessitera une quantité énorme de mémoire lors de l'application des ombres et tu peux être très rapidement limité par la bande passante.

## Automatic light frustum

Dans ce tutoriel, la zone de lumière est produite à la main pour contenir toute la scène. Bien que cela fonctionne dans cet exemple restreint, c'est à éviter. Si ta carte s'étend sur 1 km x 1 km, chaque texel de ta shadow map 1024x1024 prendra un mètre carré, ce qui est honteux. La matrice de projection de la lumière doit être aussi compacte que possible.

Pour les lumières spots, cela peut être facilement modifié en jouant sur sa portée.

Pour les lumières directionnelles, comme le soleil, c'est plus compliqué : elles illuminent réellement toute la scène. Voici une façon de calculer cette pyramide tronquée :

1. Les Potential Shadow Receivers, ou PSR, sont des objets qui appartiennent en même temps à la zone de lumière, à celle de la vue et à la boîte englobante de la scène. Comme leur nom le suggère, ces objets sont susceptibles d'être dans l'ombre : ils sont visibles par la caméra et la lumière ;

2. Les Potential Shadow Casters, ou PSC, sont tous les Potential Shadow Receivers, plus tous les objets qui se tiennent entre eux et la lumière (un objet peut ne pas être visible mais produire une ombre visible).

Donc, pour calculer la matrice de projection de la lumière, prend tous les objets visibles, retire ceux qui sont trop loin et calcule leur boîte englobante. Ajoute les objets se tenant entre la boîte englobante et la lumière, et calcule la nouvelle boîte englobante (mais cette fois, alignée suivant la direction de la lumière).

Le calcul précis de ces ensembles implique le calcul d'intersections d'enveloppes convexes, mais cette méthode est bien plus facile à implémenter.

Cette méthode provoquera des apparitions soudaines lorsque les objets disparaîtrons de la zone, car la résolution de la texture d'ombre diminuera brusquement. Les textures d'ombre en cascade ne souffrent pas de ce problème, mais sont plus compliquées à implémenter et tu peux toujours compenser cela en adoucissant le redimensionnement de la texture dans le temps.

## Shadow maps exponentielles

Les cartes d'ombres exponentielles tentent de limiter le crénelage en supposant qu'un fragment se situant dans l'ombre, mais proche de la surface éclairée, est en fait « quelque part entre les deux ». Cela est lié au biais, sauf que le test n'est plus binaire : le fragment devient plus sombre lorsque la distance de la surface éclairée augmente.

C'est de la triche, évidemment, et des artefacts peuvent apparaître lorsque deux objets se recouvrent.

## Light-space perspective shadow maps

Les LiSPSM ajustent la matrice de projection de la lumière afin d'obtenir une plus grande précision pour les objets proches de la caméra. C'est très important dans les cas de « duelling frustra » : tu regardes dans une direction, mais la lumière spot « semble » dans la direction opposée. Vous avez une grande précision pour la carte d'ombres près de la lumière, soit loin de toi et une faible résolution proche de la caméra, là où tu en as le plus besoin.

Par contre, les LiSPSM sont délicates à implémenter. Lis les références pour des détails d'implémentation.

## Shadow maps en cascade

Les CSM gèrent le même problème que les LiSPSM mais d'une manière différente. Elles utilisent simplement plusieurs (2-4) cartes d'ombres standards pour les différentes parties de la zone vue. La première gère les premiers mètres, donc tu vas obtenir une bonne résolution pour une petite zone. La prochaine carte d'ombres gère les objets plus loin. La dernière carte d'ombres gère la grosse partie de la scène, mais à cause de la perspective, elle ne sera pas aussi importante visuellement que la zone la plus proche.

Les cartes d'ombres en cascade ont, au moment de l'écriture (2012), le meilleur compromis complexité/qualité. C'est *la solution de choix* dans bien des cas.

# Conclusion

Comme tu peux le voir, les shadow maps sont un sujet compliqué. Chaque année, de nouvelles variations et améliorations sont publiées, et aujourd'hui (2012), aucune solution n'est parfaite. (PS: C'est toujours vrai en 2015)

Heureusement, les solutions présentées peuvent être mélangées : il est parfaitement possible d'avoir des shadow maps en cascade dans une perspective dans l'espace lumière, adoucie avec le PCF... Essaye d'expérimenter toutes ces techniques.

Comme conclusion, je vous suggère de rester avec les lightmap précalculées autant que possible et d'utiliser les shadow maps seulement pour les objets dynamiques. Et assures-toi que la qualité visuelle des deux soit équivalente : il n'est pas bon d'avoir des ombres statiques parfaites et des ombres dynamiques atroces.
