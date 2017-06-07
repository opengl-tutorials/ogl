---
layout: tutorial
status: publish
published: true
title: 'Tutoriel 1 : ouvrir une fenêtre'
date: '2015-11-13 23:51:22 +0200'
categories: [tuto]
order: 10
tags: []
language: fr
---

* TOC
{:toc}

# Introduction

Bienvenue dans le premier tutoriel !

Avant de s'attaquer à OpenGL, tu dois d'abord apprendre à compiler le code accompagnant chaque tutoriel, apprendre à l'exécuter, et plus important, apprendre avec le code.

# Prérequis

Aucun prérequis n'est nécessaire pour suivre ces tutoriels. Une expérience avec n'importe quel langage de programmation (C, Java, Lisp, JavaScript, ou autre) est préférable pour comprendre le code, mais pas nécessaire ; il sera *simplement* plus difficile d'apprendre deux choses à la fois.

Tous les tutoriels sont écrits en « C++ simple » : beaucoup d'efforts ont été faits pour rendre le code aussi simple que possible. Pas de templates, pas de classes, pas de pointeurs. De cette façon, tu vas pouvoir tout comprendre même si tu ne connais que le Java.

# Oublie tout

Tu n'as rien besoin de connaître, mais tu dois oublier tout ce que tu connais sur OpenGL. Si tu connais quelque chose qui ressemble à glBegin(), oublie-le. Ici tu vas apprendre *l'OpenGL moderne* (OpenGL 3 et 4), et la plupart des tutoriels en ligne apprennent le *vieux* OpenGL (OpenGL 1 et 2). Donc oublie tout ce que tu pourrais savoir, avant que ton cerveau ne fonde face à ce mélange.

# Compiler les tutoriels

Tous les tutoriels peuvent être compilés sur Windows, Linux et Mac. Pour ces plates-formes, la procédure est grossièrement la même :

* **Mets à jour tes pilotes !!** Fais-le. Tu as été prévenus
* Télécharge un compilateur, si tu n'en as pas encore
* Installe CMake
* Télécharge le code source des tutoriels
* Génére un projet avec CMake
* Compile le projet
* Joue avec les exemples

## Compilation sous Windows

 

* La mise à jour de tes pilotes devrait être simple. Va sur le site de NVIDIA ou AMD et télécharge les pilotes. Si tu n'es pas sûr de connaître ton modèle de carte graphique : Panneau de configuration → Système et Sécurité → Système → Gestionnaire de périphériques → Cartes graphiques. Si tu as un GPU intégré Intel, les pilotes sont généralement fournis par votre OEM (Dell, HP…).
* On suggère d'utiliser Visual Studio 2010 Express comme compilateur. Tu peux le télécharger gratuitement [ici](https://www.visualstudio.com/fr-fr/products/visual-studio-express-vs). Si tu préféres utiliser MinGW, on recommande d'utiliser [Qt Creator](http://www.qt.io/download/#qt-creator). Installe celui que tu veux. Les étapes suivantes seront expliquées pour Visual Studio mais devraient être similaires pour tout autre EDI.
* Télécharge [CMake](http://www.cmake.org/cmake/resources/software.html) et installe-le.
* [Télécharge le code source](http://www.opengl-tutorial.org/download/) et décompresse-le, par exemple dans C:\Users\XYZ\Projects\OpenGLTutorials .
* Lance CMake. Dans la première ligne, navigue jusqu'au dossier décompressé. Si tu n'es pas sûr, choisis le dossier contenant le fichier CMakeLists.txt. Dans la seconde ligne, entre le chemin où tu veux que les fichiers spécifiques au compilateur soient généré. Par exemple, tu peux choisir C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\, ou C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2010-32bits . Cela peut être n'importe où et pas nécessairement dans le même dossier.
![]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)

* Clique sur le bouton « Configurer » (« Configure »). Comme c'est la première fois que tu configure le projet, CMake te demandera quel compilateur tu veux utiliser. Choisisse-le sagement suivant la première étape. Si tu as un Windows 64 bits, tu peux choisir 64 bits ; si tu n'es pas sur, choisis 32 bits.
* Clique sur « Configurer » (« Configure ») jusqu'à ce que les lignes rouges disparaissent. Clique sur « Générer » (« Generate »). Ton projet Visual Studio est maintenant créé. Tu peux oublier CMake ou même le désinstaller si tu as envie.
* Ouvre C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits . Tu vas voir un fichier Tutorials.sln : ouvre-le avec Visual Studio.
![]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)
Dans le menu *Générer* (*Build*), clique sur *Tout générer* (*Build All*). Tous les tutoriels et les dépendances vont être compilés. Chaque exécutable sera aussi copié dans C:\Users\XYZ\Projects\OpenGLTutorials\. Avec un peu de chance, aucune erreur n'apparaît.
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)
* Ouvre C:\Users\XYZ\Projects\OpenGLTutorials\playground et lance playground.exe. Une fenêtre noire devrait apparaître.
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)

Tu peux aussi démarrer n'importe quel tutoriel à partir de Visual Studio. Fait un clic droit sur Playground et choisis *Définir comme projet de démarrage* (*Choose as startup project*). Tu peux maintenant déboguer le code en appuyant sur F5.

![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)


## Compilation sous Linux

Il y a tellement de variantes disponibles de Linux qu'il est impossible de lister toutes les plates-formes possibles. Adapte les instructions si nécessaire et n'hésite pas à lire la documentation de ta distribution.

* Installe les derniers pilotes. On recommande chaudement les pilotes binaires propriétaires. Ce n'est pas contre GNU ou autre, mais au moins ils fonctionnent. Si ta distribution ne fournit pas d'installation automatique, essaye le [guide d'Ubuntu](http://help.ubuntu.com/community/BinaryDriverHowto).
* Installe tous les compilateurs, outils et bibliothèques nécessaires. La liste complète est : cmake make g++ libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev. Utilise sudo apt-get install ***** ou su && yum install ******.
* [Télécharge le code source](http://www.opengl-tutorial.org/download/) et décompresse-le, par exemple dans ~/Projects/OpenGLTutorials/.
* cd dans ~/Projects/OpenGLTutorials/ et entre les commandes suivantes :
 * mkdir build
 * cd build
 * cmake ..
* Un makefile a été créé dans le répertoire build/.
* Tape « make all ». Chaque tutoriel et dépendance sera compilé. Chaque exécutable sera aussi copié dans ~/Projects/OpenGLTutorials/. Avec un peu de chance, aucune erreur n'apparaît.
* Ouvre ~/Projects/OpenGLTutorials/playground et lance ./playground. Une fenêtre noire devrait apparaître.

Tu devrais vraiment utiliser un IDE comme [Qt Creator](http://qt-project.org/). En particulier, celui-ci supporte les projets CMake nativement et fournira une meilleure expérience au débogage. Voici les instructions pour Qt Creator :

* Dans Qt Creator, va dans « Fichier » (« File ») → « Outils » (« Tools ») → « Options » → « Compilation et exécution » (« Compile&Execute) → CMake
* Définis le chemin vers CMake. C'est probablement /usr/bin/cmake
* Fichier→Ouvrir projet ; Sélectionne tutorials/CMakeLists.txt
* Sélectionne un répertoire de compilation, si possible en dehors du répertoire des tutoriels
* Optionel: Définis -DCMAKE_BUILD_TYPE=Debug dans la boite des paramètres et valide
* Clique sur le marteau en bas. Les tutoriels peuvent maintenant être lancés à partir du répertoire tutorials/
* Pour exécuter les tutoriels dans Qt Creator, clique sur Projets→Paramètres d'exécution→Répertoire de travail et sélectionne le répertoire où les shaders, textures et modèles sont. Par exemple, pour le second tutoriel : ~/opengl-tutorial/tutorial02_red_triangle/.

## Compilation sur Mac

La procédure est très similaire à celle de Windows (les Makefiles sont aussi supportés, mais on ne l'expliquera pas ici) :

* Installe XCode à partir du Mac App Store
* [Télécharge](http://www.cmake.org/cmake/resources/software.html) CMake et installe le fichier .dmg. Vous n'avez pas besoin d'installer les outils en ligne de commande
* [Télécharge le code source](http://www.opengl-tutorial.org/download/) et décompressez-le, par exemple dans ~/Projects/OpenGLTutorials/ .
* Lance CMake (Applications → CMake). Dans la première ligne, navigue jusqu'au dossier décompressé. Si tu n'es pas sûr, choisis le dossier contenant le fichier CMakeLists.txt. Dans la seconde ligne, entre l'emplacement où tu souhaite mettre tous les fichiers spécifiques au compilateur. Par exemple, tu peux choisir ~/Projects/OpenGLTutorials_bin_XCode/. Note que cela peut être n'importe où et pas nécessairement dans le même dossier.
* Clique sur le bouton *Configurer*. Comme c'est la première fois que tu configures le projet, CMake te demandera quel est le compilateur à utiliser. Choisis XCode.
* Clique sur *Configurer* jusqu'à ce que les lignes rouges disparaissent. Clique sur *Générer*. Ton projet XCode est maintenant créé. Tu peux oublier CMake et même le désinstaller si tu veux.
* Ouvre ~/Projects/OpenGLTutorials_bin_XCode/. Tu vas voir un fichier Tutorials.xcodeproj : Ouvre-le.
* Sélectionne le tutoriel dans le panneau de projet que tu souhaites lancer et utilise le bouton *Lancer* pour compiler et exécuter :
![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)

## Notes pour Code::Blocks

À cause de deux bogues (un dans Code::Blocks, un dans CMake), tu dois éditer la ligne de commande dans Projet→Options de compilation→Commandes Make, comme suit :

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)

Tu devras peut être aussi configurer le répertoire de travail toi-même : Projet→Propriétés→Cibles de compilation→tutorial N→Répertoire d'exécution (c'est src_dir/tutorial_N/).

# Exécuter les tutoriels

Tu dois exécuter les tutoriels directement à partir du bon répertoire : simplement en double cliquant sur l'exécutable. Si tu préféres la ligne de commande, *cd* vers le bon répertoire.

Si tu souhaites exécuter les tutoriels à partir de l'IDE, n'oublie pas de lire les instructions ci-dessus pour définir le bon répertoire de travail.

# Comment suivre ces tutoriels

Chaque tutoriel est fourni avec son code source et ses données, qui se trouvent dans tutorialXX/. Par contre, tu ne dois jamais modifier ces projets : ils ne servent que de référence. Ouvre playground/playground.cpp et modifie ce fichier à la place. Torture-le comme tu le souhaites. Si tu es perdu, copie n'importe quel tutoriel dans celui-ci et tout devrait revenir à la normale.

On va fournir des morceaux de code tout au long des tutoriels. N'hésite pas à les copier/coller dans ton bac à sable durant la lecture : l'expérimentation est une bonne chose. Évite de te limiter à lire le code fini : tu ne vas pas apprendre grand-chose comme cela. Même avec un simple copier/coller, tu vas avoir ton lot de problèmes.

# Ouvrir une fenêtre

Finalement ! Du code OpenGL !
Enfin, pas vraiment. Tous les tutoriels te montre la façon *bas niveau* de faire les choses afin que tu puisses voir qu'il n'y a pas de magie. Mais cette partie est très ennuyeuse et inutile, donc on va utiliser GLFW, une bibliothèque externe qui fera cela à notre place. Si tu le souhaite vraiment, tu peux utiliser l'api Win32 sous Windows, l'api X11 sous Linux et Cocoa sous Mac ; ou utiliser une autre bibliothèque comme SFML, FreeGLUT, SDL, … regarde la page des [liens]({{site.baseurl}}/miscellaneous/useful-tools-links/).

Ok, allons-y. Premièrement, on doit gérer les dépendances : on a besoin de choses basiques pour afficher les messages dans la console :

``` cpp
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
```

Premièrement, GLEW. Celle-ci est en faite un peu magique, alors on la laisse de côté pour plus tard.

``` cpp
// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
```

On a décidé de laisser GLFW gérer la fenêtre et le clavier, donc on l'inclue aussi :

``` cpp
// Include GLFW
#include <GL/glfw3.h>
```

Pour l'instant, on n'a pas besoin du prochain include, mais c'est la bibliothèque pour les opérations mathématiques liées à la 3D. Elle va se montrer rapidement très utile. Il n'y a pas de magie dans GLM, tu peux écrire ta propre bibliothèque si tu veux, c'est juste pratique de pas réinventer la roue. Le *using namespace* permet d'éviter de taper *glm::vec3*, au lieu de *vec3*.

``` cpp
// Include GLM
#include <glm/glm.hpp>
using namespace glm;
```

Si tu copies/colles tout ces includes dans playground.cpp, le compilateur se plaindra, car il n'y a pas de fonction main(). Donc, créons-la :

``` cpp
int main(){
```

La première chose à faire est d'initialiser GLFW :

``` cpp
// Initialise GLFW
if( !glfwInit() )
{
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
}
```

On peut maintenant créer notre premier fenêtre OpenGL !

``` cpp
glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

// Open a window and create its OpenGL context
GLFWwindow* window; // (In the accompanying source code, this variable is global)
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // Initialize GLEW
glewExperimental=true; // Needed in core profile
if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
}
```

Compile et exécute ce code. Une fenêtre devrait apparaître et se fermer immédiatement. Évidemment ! On doit attendre que l'utilisateur appuie sur la touche Échap :

``` cpp
// Ensure we can capture the escape key being pressed below
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    // Draw nothing, see you in tutorial 2 !

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

} // Check if the ESC key was pressed or the window was closed
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0 );
```

Et cela conclut notre premier tutoriel ! Dans le deuxième tutoriel, tu vas apprendre comment afficher un triangle.
