---
layout: page
status: publish
published: true
title: 'Cliquer avec un hack OpenGL'
date: '2015-11-22 07:52:18 +0200'
date_gmt: '2013-05-18 20:43:28 +0200'
categories: []
order: 70
tags: []
language: fr
---

Cette technique n'est pas vraiment conseillée, mais c'est une méthode facile et rapide pour ajouter un picking[^1] simple. Dans tous les cas, évite d'utiliser cela dans les jeux, car cela peut provoquer une chute de FPS. Toutefois, si tu as une simulation et que tu ne te soucie pas des performances liées au picking, cette technique peut être la solution parfaite.

Le code source pour ce tutoriel est disponible dans le fichier au nom lourd de sens : [misc05_picking/misc05_picking_slow_easy.cpp](https://github.com/opengl-tutorials/ogl/blob/master/misc05_picking/misc05_picking_slow_easy.cpp).

#Idée de base

L'idée derrière cette technique est d'afficher la scène, comme d'habitude, mais au lieu d'utiliser un joli rendu, on dessine chaque objet avec une couleur spécifique et unique.

Ensuite, on récupére la couleur du pixel sous le curseur de la souris et on utilise cette couleur pour identifier l'objet. On obtient ainsi l'objet sur lequel l'utilisateur a cliqué.

Voici un exemple :

![]({{site.baseurl}}/assets/images/tuto-picking-color/UniqueColors.png)

Dans cette capture d'écran, chaque singe possède une couleur légèrement différente permettant de les identifier.

Bien sûr, tu ne veux pas voir l'image avec toutes ces couleurs étranges donc tu dois nettoyer l'écran et redessiner comme d'habitude.

#Implémentation

##Donner un identifiant à chaque objet

Chaque objet de la scène doit avoir un identifiant unique. La façon la plus facile de le faire est de donner à chaque objet un entier et de le convertir en une couleur. Cette couleur ne doit pas avoir de sens ; cette technique est simplement un hack de toute façon.

Dans le code source accompagnant ce tutoriel, 100 objets sont créés et conservés dans un std::vector dont l'identifiant n'est que l'index de l'objet dans ce vecteur. Si tu as une hiérarchie plus complexe, tu dois sans doute ajouter l'identifiant dans ta classe de Mesh et maintenir une sorte de std::map pour associer l'identifiant à l'objet.

##Détecter le clic

Dans cet exemple simple, le picking est effectué à chaque image lorsque le bouton gauche de la souris est appuyé :

{% highlight cpp linenos %}
		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){
{% endhighlight %}

Dans une application réelle, tu veux certainement le faire uniquement lorsque l'utilisateur relâche le bouton et donc tu dois garder un booléen estCeQueLeBoutonGaucheAEteAppuyeLorsDeLImagePrecedente, ou mieux, utiliser glfwSetMouseButtonCallback() (lis le manuel GLFW pour savoir comment l'utiliser).

##Convertir l'identifiant en une couleur spécifique

Comme on doit afficher chaque modèle avec une couleur différente, la première étape est de calculer cette couleur. Une méthode simple est de placer les bits de poids faible dans le canal rouge et les bits de poids fort dans le canal bleu :

{% highlight cpp linenos %}
// Convert "i", the integer mesh ID, into an RGB color
int r = (i & 0x000000FF) >>  0;
int g = (i & 0x0000FF00) >>  8;
int b = (i & 0x00FF0000) >> 16;
{% endhighlight %}

Ça peut paraître effrayant, mais c'est un code de manipulation de bits standard. Tu obtiens finalement trois entiers, chacun compris entre 0 et 255. Avec cette méthode, tu peux représenter 255^3 = 16 millions d'objets différents, ce qui est sans doute suffisant.

##Afficher la scène avec ces couleurs

On a maintenant besoin d'un shader pour utiliser cette couleur. C'est très simple. Le vertex shader ne fait rien :

{% highlight glsl linenos cssclass=highlightglslvs %}
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

}
{% endhighlight %}

Et le fragment shader écrit simplement la couleur voulue dans le framebuffer :

{% highlight glsl linenos cssclass=highlightglslfs %}
#version 330 core

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform vec4 PickingColor;

void main(){

    color = PickingColor;

}
{% endhighlight %}
 
Facile !

La seule astuce est que tu dois envoyer tes couleurs en nombres flottants (compris dans [0, 1]) alors que tu as des entiers (compris dans [0, 255]), donc tu dois effectuer une petite division lors de l'appel à *glUniformXX()* :

{% highlight cpp linenos %}
// OpenGL expects colors to be in [0,1], so divide by 255.
glUniform4f(pickingColorID, r/255.0f, g/255.0f, b/255.0f, 1.0f);
{% endhighlight %}

Tu peux maintenant dessiner les modèles comme d'habitude (glBindBuffer, glVertexAttribBuffer, glDrawElements) et tu obtiendra l'étrange image ci-dessus.

##Obtenir la couleur sous le curseur de souris

Lorsque tu as dessiné tous les modèles (certainement avec une boucle for()), tu dois appeler *glReadPixels()*, permettant d'obtenir les pixels rasterizés sur le CPU. Mais pour que cela fonctionne, quelques étapes supplémentaires sont nécessaires.

Premièrement, tu dois appeler *glFlush()*. Cela indiquera au pilote OpenGL d'envoyer les commandes en attente (incluant votre dernier *glDrawXX*) au GPU. Cela n'est typiquement pas fait automatiquement, car les commandes sont envoyées en groupe et non immédiatement (cela signifie que lorsque tu appels *glDrawElements()*, rien n'est dessiné. Cela VA être dessiné quelques millisecondes plus tard). Cette opération est LENTE.

Ensuite, tu dois appeler *glFinish()*, qui attendra jusqu'à ce que tout soit vraiment affiché. La différence avec glFlush() est que glFlush() envoie simplement les commandes ; glFinish() attend que les commandes soient exécutées. Cette opération est LEEENTE.

Tu dois aussi configurer comment *glReadPixels()* se comportera par rapport à l'alignement mémoire. C'est quelque peu hors sujet, mais simplement, tu dois appeler *glPixelStore(GL_UNPACK_ALIGNMENT, 1)*.

Finalement, tu peux appeler *glReadPixels()* ! Voici le code complet :

{% highlight cpp linenos %}
// Wait until all the pending drawing commands are really done.
// Ultra-mega-over slow ! 
// There are usually a long time between glDrawElements() and
// all the fragments completely rasterized.
glFlush();
glFinish(); 

glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

// Read the pixel at the center of the screen.
// You can also use glfwGetMousePos().
// Ultra-mega-over slow too, even for 1 pixel, 
// because the framebuffer is on the GPU.
unsigned char data[4];
glReadPixels(1024/2, 768/2,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);
{% endhighlight %}

Ta couleur est maintenant dans le tableau data. Par exemple ci-dessous, tu peux voir que l'identifiant est 19 :

![]({{site.baseurl}}/assets/images/tuto-picking-color/DataArray.png)

##Convertir la couleur en un identifiant

Tu peux maintenant retrouver ton identifiant à partir du tampon data. Le code est exactement l'opposé du code de conversion de l'identifiant en une couleur :

{% highlight cpp linenos %}
// Convert the color back to an integer ID
int pickedID = 
	data[0] + 
	data[1] * 256 +
	data[2] * 256*256;
{% endhighlight %}

##Utiliser cet identifiant

Tu peux maintenant utiliser l'identifiant comme tu veux. Dans l'exemple, le texte de l'interface est mis à jour, mais bien sûr, tu peux faire ce que tu veux.

{% highlight cpp linenos %}
if (pickedID == 0x00ffffff){ // Full white, must be the background !
	message = "background";
}else{
	std::ostringstream oss; // C++ strings suck
	oss << "mesh " << pickedID;
	message = oss.str();
}
{% endhighlight %}
 

#Avantages et inconvénients

Avantages :

* Facile et rapide à implémenter
* Pas besoin de bibliothèque externe ni de mathématique complexe

Inconvénients :

* Utilise glFlush(), glFinish(), glReadPixels() qui sont toutes des fonctions lentes, car elles forcent le CPU à attendre le GPU, ce qui ruine les performances
* Tu n'as pas une information précise : quel triangle est touché, la normale en ce point, etc

#Remarques finales

Bien que cela ne soit pas recommandé, cette technique peut être vraiment utile, mais elle est complètement restreinte au picking. Les méthodes dans les deux prochains tutoriels peuvent être utilisées pour d'autres buts, comme la détection des collisions, faire marcher un avatar sur le sol, effectuer des requêtes de visibilité pour l'intelligence artificielle, etc.

Si finalement tu utilises cette technique et que tu veux obtenir plusieurs points dans une même image, tu dois obtenir ces points en une seule fois. Par exemple, si tu veux gérer cinq points de toucher, ne dessinez pas cinq fois la scène !

[^1] *Picker* c'est détecter quel objet se trouve sous le pointeur de la souris. Le *picking* c'est donc la *détection de l'objet sous le pointeur de la souris*

 
