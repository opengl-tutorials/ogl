---
layout: page
status: publish
published: true
title: Building your own C application
date: '2015-11-22 13:49:21 +0200'
categories: []
order: 50
tags: []
language: fr
---

Beaucoup d'efforts ont été effectués pour que ces tutoriels soient faciles à compiler et exécuter. Malheureusement, cela signifie aussi que CMake cache la façon de mettre en place ton propre projet.

Donc, ce tutoriel va expliquer comment compiler ta propre application C à partir de rien. Mais avant tout, tu as besoin de quelques connaissances de base sur ce que ton compilateur fait.

<span style="color: #ff0000;">Ne saute pas les deux premières sections. Si tu lis ce tutoriel, tu as probablement besoin de connaître ces choses.</span>

#Le modèle des applications C

##Le préprocesseur

On parle ici des *#define* et *#include*.

L'étape du préprocesseur est très simple : c'est du copier-coller.

Lorsque le préprocesseur voit le code du fichier MyCode.c suivant :

{% highlight cpp linenos %}
#include "MyHeader.h"

void main(){
    FunctionDefinedInHeader();
}
{% endhighlight %}

Il ouvre simplement le fichier MyHeader.h et copie-colle son contenu dans le fichier MyCode.c.

{% highlight text linenos %}
// Begin of MyCode.c
// Begin of MyHeader.h
#ifndef MYHEADER_H
#define MYHEADER_H

void FunctionDefinedInHeader(); // Declare the function

#endif
// End of MyHeader.h

void main(){
    FunctionDefinedInHeader(); // Use it
}

// End of MyCode
{% endhighlight %}

De façon similaire, les *#define* sont copiées-collées, les *#if* sont analysés et potentiellement retirés, etc.

À la fin de cette étape, vous obtenez un fichier C++, sans #define, #if, #ifdef, #include, prêt à être compilé.

Par exemple, voici le fichier main.cpp du sixième tutoriel, complètement prétraité dans Visual : [fichier préprocessé]({{site.baseurl}}/assets/images/build-own-app/tutorial06_preprocessed.txt). Attention, c'est un immense fichier ! Mais ça vaut le coup de savoir ce qu'un fichier .cpp simple est réellement pour le compilateur.

##Compilation

Le compilateur traduit le code C++ en une représentation que le CPU peut comprendre directement. Par exemple, le code suivant :
{% highlight cpp linenos %}
int i=3;
int j=4*i+2;
{% endhighlight %}

sera traduit en ces opcodes x86 :

{% highlight text linenos %}
mov         dword ptr [i],3
mov         eax,dword ptr [i]
lea         ecx,[eax*4+2]
mov         dword ptr [j],ecx
{% endhighlight %}

Chaque fichier .cpp est compilé séparément et le code binaire résultant est écrit dans des fichiers .o/.obj.

![]({{site.baseurl}}/assets/images/build-own-app/compilation.png)

> Nous n'avons pas encore l'exécutable : il reste une étape à faire.

##Linking

Le linker prend tout le code binaire (le tien, mais aussi celui des bibliothèques externes) et génère l'exécutable final. Quelques notes :

* Une bibliothèque possède l'extension .lib.
* Certaines bibliothèques sont *statiques*. Cela signifie que les .lib contiennent tous les opcodes x86 nécessaires.
* Certaines bibliothèques sont *dynamiques* (aussi appelées bibliothèques *partagées*). Cela signifie que le fichier .lib ne contient pas tout le code x86 ; il indique simplement : « Je jure que les fonctions *Foo*, *Bar* et *WhatsNot* seront disponibles à l'exécution ».

Lorsque le linker a été exécuté, on obtient un exécutable (.exe sous Windows, sans extension sous Unix) :

![]({{site.baseurl}}/assets/images/build-own-app/linking.png)

##Exécution

Lorsque tu lances l'exécutable, le système d'exploitation va ouvrir le .exe et placer les opcodes x86 en mémoire. Comme indiqué précédemment, certains codes ne sont pas disponibles à ce moment-là : le code des bibliothèques dynamiques. Mais le linker a été assez gentil pour indiquer où les trouver : le .exe indique clairement que la fonction glClearColor est implémentée dans le fichier OpenGL32.dll.

![]({{site.baseurl}}/assets/images/build-own-app/dynamiclinking.png)

Windows va ouvrir la .dll et trouver glClearColor :

![]({{site.baseurl}}/assets/images/build-own-app/depends.png)

Quelques fois, une .dll ne peut être trouvée, sûrement, car l'installation a échoué et le programme ne peut pas s'exécuter.

![]({{site.baseurl}}/assets/images/build-own-app/dynamiclinking.png)

#Comment faire X avec l'éditeur Y ?

On va expliquer les opérations de base de création d'un projet séparement des opérations specifiques a OpenGL.

* Premièrement, tu devras faire les opérations de base tout le temps, donc tu as plutot intérêt à les connaître par coeur
* Deuxièmement, vous allez connaître ce qui est spécifique à OpenGL de ce qui ne l'est pas

##Visual Studio

###Creating a new project

Fichier (File) -> Nouveau (New) -> Projet (Project) -> Projet vide (Empty Project). N'utilise pas ces étranges assistants. N'utilise aucune option que tu ne connais pas (désactivez MFC, ATL, les entêtes précompilés, stdafx, le fichier main).

###Adding a source file in a project

Faites un clic droit sur Fichiers sources (Sources Files) -> Ajouter nouveau (Add new).

###Ajouter un fichier source dans un projet

Fait un clic droit sur projet (Project) -> Propriétés du projet (Project Properties) -> C++ -> Général -> Répertoire d'inclusion additionnel (Additional include directories). C'est une liste déroulante, tu peux la modifier comme tu le souhaites.

###Lier une bibliothèque

Fait un clic droit sur projet (Project) -> Propriétés du projet (Project Properties) -> Éditeur de liens (Linker) -> Entrée (Input) -> Dépendances additionnelles (Additional dependencies) : tape le nom du fichier .lib. Par exemple : opengl32.lib.

Dans les propriétés du projet (Project Properties) -> Éditeur de liens (Linker) -> Général -> répertoires de bibliothèques additionnels (Additional library directories), assures-toi que le chemin de la bibliothèque ci-dessus est présent.

###Compiler, exécuter et déboguer

Pour définir le répertoire de travail (là où sont les textures et les shaders) : Propriétés du projet (Project Properties) -> Débogage (Debugging) -> Répertoire de travail (Working Directory).

Pour exécuter : Maj-F5 ; mais tu ne souhaites probablement jamais faire ça. Pour déboguer : F5.

Voici une courte liste de raccourcis pour le débogage :

* F9 sur une ligne, ou en faisant un clic gauche sur les numéros de ligne : définit un point d'arrêt. Un point rouge va apparaître
* F10 : exécuter la ligne actuelle
* F11 : exécuter la ligne actuelle, mais en s'enfoncer dans les fonctions que cette ligne appelle (« Step into »)
* Maj-F1 : exécuter jusqu'à la fin de la fonction (« Step out »)

Tu as aussi de nombreuses fenêtres de débogage : les variables observées, la pile d'appels, les threads…

##QtCreator

QtCreator est disponible gratuitement [ici](http://qt-project.org/).

###Créer un nouveau projet

Utilise un projet vide C ou C++ ; éviter les templates contenant des trucs de Qt.

![]({{site.baseurl}}/assets/images/build-own-app/QtCreator_newproject.png)

Utilise les options par défaut.

###Ajouter un fichier source dans un projet

Utilise l'interface, ou ajoute un fichier dans le .pro :

{% highlight text linenos %}
SOURCES += main.cpp \
           other.cpp \
           foo.cpp
{% endhighlight %}

###Ajouter un répertoire d'inclusion

Dans le fichier .pro :

{% highlight text linenos %}
INCLUDEPATH += [ton chemin] \ [ton autre chemin]
{% endhighlight %}

###Lier avec une bibliothèque

Clic droit sur le projet -> Ajout une bibliothèque (Add library)

* Si tu es sous Linux et que tu as installé la bibliothèque à partir de apt-get ou similaire, il y a de fortes chances que la bibliothèque soit enregistrée dans le système. Tu peux sélectionner « Paquet système » (System package) et entrer le nom de la bibliothèque (par exemple : libglfw ou glew).

![]({{site.baseurl}}/assets/images/build-own-app/QtCreator_linking.png)

* Sinon, utilise « Bibliothèque système » (System library) et navigue jusqu'à atteindre le dossier où tu as compilée ta lib.

###Compiler, exécuter et déboguer

Pour compiler : Ctrl-B ou le marteau dans le coin inférieur gauche.

Pour exécuter : la flèche verte. Tu peux définir les arguments du programme et le répertoire de travail dans Projets (Projects) -> Paramètres d'exécution (Run Settings).

Pour déboguer :

* Définir un point d'arrêt : clique à gauche des numéros de ligne. Un point rouge apparaîtra
* F10 : exécuter la ligne actuelle
* F11 : exécuter la ligne actuelle, mais en s'enfonçant dans les fonctions que cette ligne appelle (« Step into »)
* Maj-F11 : exécuter jusqu'à la fin de la fonction (« Step out »)

Tu as aussi de nombreuses fenêtres de débogage : les variables observées, la pile d'appels, les threads ...

##XCode

En cours ...

##CMake

CMake créera les projets et cela pour pratiquement tous les IDE : Visual, Qt Creator, XCode, make, Code::Blocks, Eclipse, etc., sur n'importe quel système d'exploitation. Ça te libère de la maintenance de multiples fichiers de projet.

###Créer un nouveau projet

Crée un fichier CMakeLists.txt et écris ceci (adapte au besoin) :

{% highlight text linenos %}
cmake_minimum_required (VERSION 2.6)
project (your_project_name)

find_package(OpenGL REQUIRED)

add_executable(your_exe_name
    tutorial04_colored_cube/tutorial04.cpp
    common/shader.cpp
    common/shader.hpp
)
{% endhighlight %}

Lance l'interface graphique de CMake, navigue jusqu'à atteindre ton fichier .txt et sélectionne ton dossier de compilation. Clique sur « Configurer » (Configure) puis « Générer » (Generate). Ta solution va être créée dans le dossier de compilation.

###Ajouter un fichier source dans un projet

Ajoute simplement une ligne dans la commande *add_executable*.

###Ajouter des répertoires d'inclusion

{% highlight text linenos %}
include_directories(
    external/AntTweakBar-1.15/include/
    external/glfw-2.7.2/include/
    external/glm-0.9.1/
    external/glew-1.5.8/include/
    .
)
{% endhighlight %}

###Lier une bibliothèque

{% highlight text linenos %}
set(ALL_LIBS
    ${OPENGL_LIBRARY}
    GLFW_272
    GLEW_158
    ANTTWEAKBAR_151_OGLCORE_GLFW
)

target_link_libraries(tutorial01_first_window
    ${ALL_LIBS}
)
{% endhighlight %}

###Compiler, exécuter et déboguer

CMake ne fait pas cela. Utilisez votre IDE favori.

##make

Vraiment ??

##GCC

Cela peut être intéressant de compiler un petit projet « à la main » afin de mieux comprendre ce qui se passe. Ne le fait pas sur un vrai projet ...

>Tu peux aussi le faire sur Windows avec MinGW.

Compile chaque fichier .cpp séparément :

{% highlight text linenos %}
g++ -c main.cpp
g++ -c tools.cpp
{% endhighlight %}

Comme indiqué précédemment, tu vas obtenir des fichiers main.o et tools.o. Link-les :

{% highlight text linenos %}
g++ main.o tools.o
{% endhighlight %}

un fichier *a.out* apparaît ; c'est ton exécutable. Exécute-le :

{% highlight text linenos %}
./a.out
{% endhighlight %}

C'est tout !

#Compiler votre propre application C

Armé de cette connaissance, on peut commencer à compiler soi-même une application OpenGL.

1. Télécharge les dépendances : ici on utilise GLFW, GLEW et GLM, mais suivant ton projet, tu peux avoir besoin d'autre chose. Sauvegarde-les préférablement dans des sous-répertoires de ton projet (par exemple : external/).
2. Elles doivent être précompilées pour votre plateforme. Toutefois, GLM n'a pas besoin d'être compilée.
3. Créez un nouveau projet avec l'IDE de ton choix.
4. Ajoute un nouveau fichier .cpp dans le projet.
5. Copie et colle, par exemple, le code suivant (c'est en fait le fichier playground.cpp) :

{% highlight cpp linenos %}
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GL/glfw.h>

#include <glm/glm.hpp>
using namespace glm;

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Playground" );

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

	do{
		// Draw nothing, see you in tutorial 2 !

		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
{% endhighlight %}

6. Compile le projet.

Tu vas obtenir de nombreuses erreurs de compilation. On va les analyser une par une.

#Dépannage

Les messages d'erreurs ci-dessous sont pour Visual Studio 2010, mais ils sont plus ou moins proches de ceux de GCC.

##Visual Studio - fatal error C1083 : impossible d'ouvrir le fichier 'GL/glew.h' : Aucun fichier trouvé.

(Ou n'importe quel autre fichier.)

Certains entêtes ont des emplacements bizarres. Par exemple, les fichiers à inclure de GLEW sont situés dans external/glew-x.y.z/include. Le compilateur n'a aucune méthode magique pour le deviner, donc tu dois les lui indiquer. Dans les propriétés du projet, ajoute le chemin approprié dans les options du compilateur (et non pas l'éditeur de liens).

Pour *aucune raison* tu ne dois copier les fichiers dans les répertoires du compilateur (Program Files/Visual Studio/... ). Techniquement, cela fonctionnera, mais c'est une **très** mauvaise pratique.

De plus, c'est une bonne chose d'utiliser des chemins relatifs (./external/glew/... au lieu de C:/Users/utilisateur/Downloads/...).

Par exemple, voici ce que contiennent les fichiers de CMake de ces tutoriels :

{% highlight text linenos %}
external/glfw-2.7.2/include
external/glm-0.9.1
external/glew-1.5.8/include
{% endhighlight %}

Répéte ça jusqu'à ce que tous les fichiers soient trouvés.

##GCC - fatal error : GL/glew.h : aucun fichier trouvé

(ou n'importe quel autre fichier.)

Ça signifie que la bibliothèque n'est pas installée. Si tu es chanceux, la bibliothèque est connue et tu n'a qu'à l'installer. C'est le cas pour GLFW, GLEW et GLM :

{% highlight text linenos %}
sudo apt-get install libglfw-dev libglm-dev libglew1.6-dev
{% endhighlight %}

Si ce n'est pas une bibliothèque répandue, regarde la réponse pour Visual Studio ci-dessus.

##Visual Studio - error LNK2019 : symbole non résolu glfwGetWindowParam référencé dans la fonction main

(ou n'importe quel autre symbole dans n'importe quelle autre fonction.)

Félicitations ! Tu as une erreur d'édition de liens. C'est une excellente nouvelle : ça signifie que la compilation a réussi. Plus qu'une dernière étape !

Les fonctions GLFW se trouvent dans une bibliothèque externe. Tu dois indiquer cette bibliothèque à l'éditeur de liens. Ajoute-la dans les options de l'éditeur de liens. N'oublie pas d'ajouter le chemin menant à cette bibliothèque.

Par **exemple**, voici ce que le projet Visual Studio utilise. Les noms sont quelque peu inhabituels, car c'est une compilation personnalisée. De plus, GLM ne nécessite pas d'être compilée ou liée, donc elle n'est pas là.

{% highlight text linenos %}
external\Debug\GLFW_272.lib
external\Debug\GLEW_158.lib
{% endhighlight %}

Si tu télécharges ces bibliothèques à partir de SourceForge ([GLFW](http://www.glfw.org/download.html), [GLEW](http://glew.sourceforge.net/index.html)) et les compile toi-même, tu devras spécifier le chemin adéquat. Par exemple :

{% highlight text linenos %}
C:\Where\You\Put\The\Library\glfw.lib
C:\Where\You\Put\The\Other\Library\glew32.lib
{% endhighlight %}

##GCC - main.cpp : référence indéfinie vers 'glfwInit'

(ou n'importe quel autre symbole.)

Même réponse que pour Visual Studio ci-dessus.

> Sur Linux, GLFW et GLEW (et plein d'autres) sont généralement installées avec apt-get ou autre : *sudo apt-get install libglew-dev libglfw-dev* (cela peut changer). Lorsque tu fais ça, les bibliothèques sont copiées dans les répertoires standards du compilateur, donc tu n'as pas à préciser le chemin. Lie simplement glfw et glew comme présenté dans la première section.

##J'ai tout configuré correctement, mais j'ai toujours une erreur « unresolved external error » !

Ça peut être quelque peu difficile à tracer. Il y a plusieurs solutions :

###J'ai une erreur durant l'édition des liens avec _imp_glewInit ou d'autres symboles qui commencent par _imp

Ça signifie que la bibliothèque (dans ce cas, glew) a été compilée comme bibliothèque statique, mais tu essayes de l'utiliser comme bibliothèque dynamique. Ajoute simplement la définition pour le préprocesseur suivante dans les options du compilateur (pour ton propre projet, et non celui de glew) :

{% highlight text linenos %}
GLEW_STATIC
{% endhighlight %}
 
###J'ai quelques problèmes étranges avec GLFW

Peut-être, car GLFW a été compilée comme bibliothèque dynamique, mais tu essayes de l'utiliser comme bibliothèque statique ?

Essaye d'ajouter la définition pour le préprocesseur suivante :

{% highlight text linenos %}
GLFW_DLL
{% endhighlight %}

###J'ai un autre problème avec l'éditeur de liens ! Aidez-moi, je suis bloqué !

Envoie nous par mail ton projet complet compressé dans un zip et on te répondra et ajoutera les indications manquantes.

###J'aimerais résoudre cela moi-même. Quelles sont les règles générales ?

Admettons que tu es l'auteur de la GLFW. Tu veux fournir la fonction glfwInit().

Lors de la compilation comme DLL, tu dois indiquer au compilateur que glfwInit() n'est pas comme n'importe quelle autre fonction dans la DLL ; elle doit être vue par les autres, contrairement à glfwPrivateImplementationMethodNobodyShouldCareAbout(). On fait ça en déclarant la fonction externe (external en anglais) avec GCC, ou "__declspec(dllexport)" avec Visual Studio.

Lorsque tu veux utiliser GLFW, tu deois indiquer au compilateur que la fonction n'est pas réellement disponible : il doit la lier dynamiquement. On fait ça en déclarant la fonction externe (external) avec GCC ou "__declspec(dllimport)" avec Visual.

Donc tu utilises une définition pratique #define : GLFWAPI et tu l'utilises pour déclarer les fonctions :

*GLFWAPI int glfwInit(void) ;*

* Lorsque tu compiles la bibliothèque en DLL, tu définis #define GLFW_BUILD_DLL. GLFWAPI sera alors défini en __declspec(dllexport)
* Lorsque tu utilises GLFW à travers une DLL, tu définis #define GLFW_DLL. GLFWAPI sera alors défini en __declspec(dllimport)
* Lorsque tu compiles la bibliothèque statique, GLFWAPI est défini vide
* Lorsque tu utilises GLFW en bibliothèque statique, GLFWAPI est défini vide.

Donc la règle est : ces indications doivent être consistantes. Si tu compiles une bibliothèque (n'importe quelle bibliothèque, pas que GLFW) en DLL, utilise la bonne définition pour le préprocesseur : GLFW_DLL, GLEW_STATIC.

##Mon programme crashe !

Il y a de multiples raisons pour qu'une application C++ OpenGL plante. Voici quelques-unes d'entre elles. Si tu ne sais pas la ligne exacte où ton programme plante, apprend à utiliser un débogueur (voir les raccourcis ci-dessus). NE débogue PAS avec printf().

###Je n'atteins même pas le main()

C'est certainement dû à des DLL qui n'ont pas pu être trouvées. Essaye d'ouvrir ton application avec Dependency Walker (Windows) ou ldd (Linux ; essaye aussi [ceci](http://stackoverflow.com/questions/6977298/dependency-walker-equivalent-for-linux)).

###Mon programme crashe sur glfwOpenWindow(), ou toute autre fonction qui crée un contexte OpenGL

Plusieurs raisons possible :

* Ton GPU ne supporte pas la version OpenGL demandée. Essaye de voir la version supportée avec GPU Caps Viewer ou un outil similaire. Met à jour tes pilotes si la version semble trop vieille. Les cartes intégrées Intel sur les netbooks sont particulièrement nulles. Utilise une version d'OpenGL plus basse (2.1 par exemple) et utilise les extensions si tu manques de fonctionnalités
* Ton système d'exploitation ne supporte pas la version OpenGL demandée : Mac OS pre-Lion ... même réponse
* Tu essayes d'utiliser GLEW avec un contexte OpenGL core (c'est-à-dire, sans les choses dépréciées). C'est un bogue de GLEW. Utilise glewExperimental=true avec glewInit() ou utilise le mode de compatibilité (c'est-à-dire utilise GLFW_OPENGL_COMPAT_PROFILE à la place de GLFW_OPENGL_CORE_PROFILE).

##Mon programme crash au premier appel OpenGL, ou a la création du premier buffer

Trois raisons possible:

* Tu n'appels pas *glewInit()* APRES *glfwOpenWindow()*
* Tu utilises le profil OpenGL Core, et tu n'a pas crée de VAO, Ajoute ça après *glewInit()* :

{% highlight cpp linenos %}
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
{% endhighlight %}

* Tu utilise la version normales de GLEW, qui a un bug. Tu ne peux pas utiliser un profil OpenGL Corea cause d'un bug. Soit tu utilise: glewExperimental=true avant glewInit(), soit tu demandes a GLFW un Compatibility Profile à la place :

{% highlight cpp linenos %}
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
{% endhighlight %}

##Mon programme crashe lorsque j'essaie de charger un fichier

Définis ton répertoire de travail correctement. Lis le premier tutoriel.

Crée un fichier test.txt et essaye le code suivant :

{% highlight cpp linenos %}
if ( fopen("test.txt", "r" ) == NULL ){
    printf("I'm probably running my program from a wrong folder");
}
{% endhighlight %}
<span style="color: #ff0000;">UTILISE LE DÉBOGUEUR !!!!</span>
Sincèrement ! Ne débogue pas avec printf() ; utilise un bon EDI. [http://www.dotnetperls.com/debugging](http://www.dotnetperls.com/debugging) est pour le C# mais c'est aussi valide pour le C++. Cela peut être différent pour XCode ou Qt Creator, mais les concepts restent exactement les mêmes.

##Autre chose ne va pas

Envoie nous un courriel !

 
