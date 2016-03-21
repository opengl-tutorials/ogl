---
layout: page
status: publish
published: true
title: 'Tutoriel 6 : clavier et souris'
date: '2015-11-18 07:47:59 +0200'
categories: [tuto]
order: 60
tags: []
language: fr
---

Bienvenue dans le sixième tutoriel !

Tu vas apprendre à utiliser le clavier et la souris pour déplacer la caméra exactement comme dans un FPS.

#L'interface

Comme le code va être réutilisé dans les autres tutoriels, on va placer le code dans un fichier à part : common/controls.cpp et déclarer les fonctions dans common/controls.hpp afin que le fichier tutorial06.cpp puisse les utiliser.

Le code du fichier tutoriel06.cpp ne change pas beaucoup par rapport au tutoriel précédent. La plus grande modification est le calcul de la matrice MVP à chaque image au lieu de la calculer une unique fois. On déplace donc ce code dans la boucle principale :

``` cpp
do{

    // ...

    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    // ...
}
```

Ce code nécessite trois nouvelles fonctions :

* computeMatricesFromInputs() lit le clavier et la souris et calcule les matrices de projection et de vue. C'est ici que la magie opère
* getProjectionMatrix() retourne simplement la matrice de projection calculée par computeMatricesFromInputs()
* getViewMatrix() retourne simplement la matrice de vue calculée par computeMatricesFromInputs()

C'est une façon de faire. Bien sûr, si tu n'aimes pas ces fonctions, vas-y et change-les.

Voyons voir maintenant ce qu'il y a dans controls.cpp.

#Le vrai code

On a besoin de quelques variables :

``` cpp
// position
glm::vec3 position = glm::vec3( 0, 0, 5 );
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
```

Le champ de vision (FoV en anglais) est le niveau de zoom. 80° = un grand angle donc de grosses déformations. 60° - 45° : standard. 20° : gros zoom.

Premièrement, on va recalculer la position, l'angle horizontal, l'angle vertical et le champ de vision selon les entrées, puis on va calculer les matrices de vue et de projection à partir de la position, de l'angle horizontal, de l'angle vertical et du champ de vision.

## Orientation

Lire les informations de la souris est facile :

``` cpp
// Get mouse position
int xpos, ypos;
glfwGetMousePos(&xpos, &ypos);
```

Mais on doit prendre garde à replacer le curseur au centre de l'écran ou il ira en dehors de la fenêtre et on ne sera plus capable de bouger.

``` cpp
// Reset mouse position for next frame
glfwSetMousePos(1024/2, 768/2);
```

>Ce code fait l'hypothèse que la fenêtre est de 1024 * 768, ce qui n'est évidemment pas toujours le cas. Si tu veux tu peux utiliser glfwGetWindowSize pour récupérer la taille de la fenêtre.

Maintenant, on calcule nos angles de vision :

``` cpp
// Compute new orientation
horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
```

Lisons ces lignes de droite à gauche :

* 1024/2 - xpos correspond à la distance de la souris par rapport au centre de la fenêtre. Plus grande est la valeur, plus nous voulons tourner
* float(...) convertit la position en un float (nombre à virgule flottante) afin que la multiplication soit exacte
* mouseSpeed n'est là que pour ralentir ou accélérer les rotations. Modifie cette valeur à volonté ou laisse l'utilisateur la choisir
* += : si tu n'as pas déplacé la souris, 1024/2 - xpos vaudra 0 et horizontalAngle += 0 ne modifie pas la variable. Si tu avais un '=' à la place, tu serais retourné de force à l'orientation d'origine et cela à chaque image, ce qui n'est pas ce que l'on veut.

Maintenant, on peut calculer un vecteur qui représente, dans l'espace monde, la direction vers laquelle on regarde.

``` cpp
// Direction : Spherical coordinates to Cartesian coordinates conversion
glm::vec3 direction(
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
);
```

C'est un calcul standard, mais si tu ne connais pas sinus et cosinus, voici une courte explication en 2D :

<img class="alignnone whiteborder" title="Trigonometric circle" src="http://www.numericana.com/answer/trig.gif" alt="" width="150" height="150" />

La formule ci-dessus n'est qu'une généralisation pour la 3D.

Maintenant, on souhaite calculer le vecteur « haut » efficacement. Le « haut » n'est pas toujours en direction de +Y : si tu regardes vers le bas, par exemple, le vecteur « haut » sera en réalité horizontale. Voici un exemple avec deux caméras ayant la même position, la même direction, mais de vecteurs « haut » différents:

![]({{site.baseurl}}/assets/images/tuto-6-mouse-keyboard/CameraUp.png)

Dans ce cas, la seule constante est que le vecteur allant sur la droite est toujours horizontal. Vous pouvez vérifier cela en plaçant votre bras à l'horizontal et en regardant vers le haut, le bas et dans toutes les directions. Voici comment définir le « bon » vecteur « vers la droite » : sa coordonnée Y est 0, car le vecteur est horizontal et ses coordonnées X et Z sont exactement comme dans la figure ci-dessus, mais avec des angles tournés de 90°, ou Pi/2 radians.

``` cpp
// Right vector
glm::vec3 right = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
);
```

On a le vecteur « vers la droite » et une « direction » ( =  vecteur vers « l'avant »). Le vecteur vers « le haut » est le vecteur qui est perpendiculaire à ceux-ci. Il y a un outil mathématique pratique qui rend cela très simple : le produit vectoriel.

``` cpp
// Up vector : perpendicular to both direction and right
glm::vec3 up = glm::cross( right, direction );
```

Pour se souvenir de ce que fait le produit vectoriel, c'est très simple. Rappele-toi la règle de la main droite du troisième tutoriel. Le premier vecteur est le pouce ; le second l'index et le résultat est le majeur. C'est très pratique.

## Position

Le code est facile à comprendre. D'ailleurs, j'ai utilisé les touches fléchées à la place de aswd, car je suis sur un clavier azerty et aswd correspond à zqsd. C'est aussi différent avec les claviers qwerZ et passons les claviers coréens. Je ne sais même pas quelle disposition les coréens ont, mais je suppose que c'est différent.

``` cpp
// Move forward
if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
    position += direction * deltaTime * speed;
}
// Move backward
if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
    position -= direction * deltaTime * speed;
}
// Strafe right
if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
    position += right * deltaTime * speed;
}
// Strafe left
if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
    position -= right * deltaTime * speed;
}
```

La seule chose particulière est deltaTime. Tu ne veux pas te déplacer d'une unité chaque image pour la simple raison que :

* Si tu as un ordinateur rapide et que tu exécutes le programme à 60 FPS, tu te déplacera de 60*speed en une seconde
* Si tu as un ordinateur lent et que tu exécutes le programme à 20 FPS, tu te déplacera de 20*speed en une seconde.

Comme le fait d'avoir un ordinateur plus rapide n'est pas une raison pour se déplacer plus vite, on doit faire dépendre la distance du « temps depuis la dernière image », ou « deltaTime ».

* Si tu as un ordinateur rapide et que tu exécutes le programme à 60 FPS, tu te déplacera de 1/60*speed en une image, donc 1*speed en une seconde.
* Si tu as un ordinateur lent et que tu exécutes le programme à 20 FPS, tu te déplacera de 1/20*speed en une image, donc 1*speed en une seconde.

Ce qui est bien mieux ! Le deltaTime est très facile à calculer :

``` cpp
double currentTime = glfwGetTime();
float deltaTime = float(currentTime - lastTime);
```

## Champ de vision

Pour s'amuser, on peut aussi lier la roulette de la souris au champ de vision pour faire rapidement un zoom :

``` cpp
float FoV = initialFoV - 5 * glfwGetMouseWheel();
```

## Calculer les matrices

Le calcul des matrices est maintenant très simple. On utilise les mêmes fonctions que précédemment mais avec les nouveaux paramètres.

``` cpp
// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
// Camera matrix
ViewMatrix       = glm::lookAt(
    position,           // Camera is here
    position+direction, // and looks here : at the same position, plus "direction"
    up                  // Head is up (set to 0,-1,0 to look upside-down)
);
```

#Résultat

![]({{site.baseurl}}/assets/images/tuto-6-mouse-keyboard/moveanim.gif)

## Backface Culling

Maintenant que tu peux librement te déplacer, si tu vas dans le cube, tu vas remarquer que les polygones sont toujours affichés. Cela peut sembler évident, mais cette remarque ouvre en réalité une possibilité d'optimisation. En effet, normalement dans les applications, tu n'es jamais _dans_ un object 3D.

L'idée consiste à dire au GPU de vérifier si la caméra est derrière ou devant le triangle. Si elle est devant, afficher le triangle ; si elle est derrière, *et* que le modèle est fermé *et* que l'on n'est pas dans le modèle, *alors* il y aura un autre triangle devant et personne ne le remarquera, sauf que tout sera plus rapide : deux fois moins de triangles en moyenne !

Le mieux, c'est qu'il est très facile à calculer. Le GPU calcule la normale du triangle (en utilisant le produit scalaire, tu te rappels ?) et vérifie si la normale est orientée vers la caméra ou non.

Cela possède un coût malheureusement : l'orientation du triangle est implicite. Cela signifie que si tu inverses deux sommets dans ton buffer(tampon) de sommets, tu vas probablement avoir un trou. Mais cela vaut généralement le petit travail supplémentaire. Souvent, tu n'as qu'à cliquer sur « inverser les normales » dans ton logiciel de modélisation 3D (qui va, en réalité, inverser les sommets et donc les normales) et tout sera parfait.

Voici comment on active le backface culling :

``` cpp
// Cull triangles which normal is not towards the camera
glEnable(GL_CULL_FACE);
```

#Exercices

* Restreins verticalAngle afin de ne pas pouvoir retourner la caméra de haut en bas (mais seulement de gauche à droite)
* Crée une caméra qui tourne autour de l'objet (position = ObjectCenter + ( radius * cos(time), height, radius * sin(time) ) ) ; lie le rayon/hauteur/temps au clavier/souris, ou autre
* Amuse-toi !

 
