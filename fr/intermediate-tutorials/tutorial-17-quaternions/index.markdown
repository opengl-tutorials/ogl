---
layout: page
status: publish
published: true
title: 'Tutoriel 17 : Les rotations'
date: '2015-11-21 12:31:28 +0200'
categories: [tuto]
order: 90
tags: []
language: fr
---

#Introduction

Ce tutoriel sort du contexte d'OpenGL, mais s'attaque néanmoins à un problème très courant : comment représenter les rotations ?

Dans le troisième tutoriel - les matrices, on a appris que celles-ci sont capables de tourner un point autour d'un axe donné. Bien que les matrices offrent une méthode propre pour transformer les sommets, leur gestion est difficile : comme, par exemple, l'obtention de la matrice de rotation à partir de la matrice finale.

On présentera les deux manières les plus courantes pour définir des rotations : les angles d'Euler et les quaternions. Et le plus important, on expliquera pourquoi tu devrais probablement utiliser les quaternions.

![]({{site.baseurl}}/assets/images/tuto-17-rotation/tuto17.png)

#Avant-propos : rotation VS orientation

En lisant des articles sur les rotations, tu peux être pertubé par le vocabulaire. Dans ce tutoriel :

* Une orientation est un état : « l'orientation de l'objet est ...»
* Une rotation est une opération : « appliquer cette rotation à l'objet »

Lorsque tu *appliques une rotation*, tu *changes l'orientation*. Les deux peuvent être représentés avec les mêmes outils, menant à la confusion. Maintenant, on y va ...

#Euler Angles

Les angles d'Euler sont la méthode la plus simple d'imaginer une orientation. Tu stockes trois orientations autour des axes X, Y et Z. C'est un concept très facile à comprendre. Tu peux utiliser un vec3 pour stocker la rotation :

{% highlight cpp linenos %}
vec3 EulerAngles( RotationAroundXInRadians, RotationAroundYInRadians, RotationAroundZInRadians);
{% endhighlight %}

Ces trois rotations sont ensuite appliquées successivement, habituellement dans cet ordre : en premier Y, puis Z et X (mais pas obligatoirement). L'utilisation d'un autre ordre entraîne d'autres résultats.

Une utilisation simple des angles d'Euler est l'orientation d'un personnage. Habituellement, les personnages de jeux ne tournent pas autour des axes X et Z, seulement autour de l'axe vertical. Donc, il est plus simple d'écrire, de comprendre et de maintenir  un *float direction;* que trois orientations différentes.
 
Voila une autre bonne utilisation des angles d'Euler : une caméra de type FPS (First Person Shooter) : tu as un angle pour le cap (Y) et un pour le haut/bas (X). Jetez un œil au fichier [common/controls.cpp](https://github.com/opengl-tutorials/ogl/blob/master/common/controls.cpp) pour voir un exemple.

Cependant, lorsque les choses deviennent plus complexes, les angles d'Euler rendront le travail plus difficile. Par exemple :

* L'interpolation douce entre deux orientations est complexe. L'interpolation naïve des angles autour de X, Y et Z sera horrible
* L'application de plusieurs rotations est compliquée et inexacte : tu dois calculer la matrice de rotation finale et *deviner* les angles d'Euler de cette matrice
* Un problème bien connu : le « blocage de cardan » (« Gimbal lock »). Il bloquera quelques fois vos rotations et d'autres singularités retourneront votre modèle à l'envers.
* Des angles différents donnent la même rotation (-180° et 180°, par exemple), ça complique les comparaison d'orientation.
* C'est le bordel ! Comme dit précédemment, le bon ordre est habituellement YZX, mais si tu utilises une bibliothèque avec un autre ordre, tu vas avoir des soucis ;
* Certaines opérations sont complexes : par exemple, la rotation de N degrés autour d'un axe spécifique.

Les quaternions sont l'outil qui résout ces problèmes pour représenter les rotations.

#Quaternions

Un quaternion est un ensemble de quatre nombres, [x, y, z, w], qui représentent les rotations de la façon suivante :

{% highlight cpp linenos %}
// RotationAngle is in radians
x = RotationAxis.x * sin(RotationAngle / 2)
y = RotationAxis.y * sin(RotationAngle / 2)
z = RotationAxis.z * sin(RotationAngle / 2)
w = cos(RotationAngle / 2)
{% endhighlight %}

*RotationAxis* est, comme son nom l'indique, l'axe autour duquel vous souhaitez effectuer la rotation.

*RotationAngle* est l'angle de rotation autour de cet axe.

![]({{site.baseurl}}/assets/images/tuto-17-rotation/quaternion.png)

Donc fondamentalement, les quaternions stockent un *axe de rotation* et un *angle de rotation*, d'une façon qui simplifira la combinaison des rotations.

##Lire des quaternions

Le format est définitivement moins intuitif que celui des angles d'Euler, mais il reste lisible : les composantes xyz correspondent grossièrement à l'axe de rotation et w est l'arc cosinus de l'angle de rotation (divisé par 2). Par exemple, imagines que tu veux les valeurs suivantes dans le débogueur : [0.7, 0, 0, 0.7]. x = 0.7, c'est plus grand que y et z, donc vous savez grossièrement que la rotation est principalement autour de l'axe X, et 2 * acos(0.7) = 1.59 radians, donc que la rotation est de 90°.

Pareillement, [0, 0, 0, 1] (w = 1) signifie que l'angle = 2*acos(1) = 0, donc que c'est un quaternion unitaire, ne faisant aucune rotation.

##Opérations de bases

Connaître les mathématiques derrière les quaternions n'est que rarement utile : la représentation est tellement non intuitive que tu te reposes habituellement sur les fonctions utilitaires qui feront les calculs pour toi. Si tu êtes intéressés, regardez les livres de mathématiques dans la page des [outils et liens utiles]({{site.baseurl}}}/miscellaneous/useful-tools-links/).

###Comment créer un quaternion en C++ ?

{% highlight cpp linenos %}
// Don't forget to #include <glm/gtc/quaternion.hpp> and <glm/gtx/quaternion.hpp>

// Creates an identity quaternion (no rotation)
quat MyQuaternion;

// Direct specification of the 4 components
// You almost never use this directly
MyQuaternion = quat(w,x,y,z); 

// Conversion from Euler angles (in radians) to Quaternion
vec3 EulerAngles(90, 45, 0);
MyQuaternion = quat(EulerAngles);

// Conversion from axis-angle
// In GLM the angle must be in degrees here, so convert it.
MyQuaternion = gtx::quaternion::angleAxis(degrees(RotationAngle), RotationAxis);
{% endhighlight %}

###Comment créer un quaternion en GLSL ?

Tu ne le fais pas. Convertis le quaternion vers une matrice de rotation et utilises-la dans la matrice de modèle. Tes sommets seront tournés comme d'habitude, avec la matrice MVP.

Dans quelques cas, tu peux réellement vouloir utiliser les quaternions en GLSL, par exemple si tu fais l'animation d'un squelette sur le GPU. Il n'y a pas de type pour les quaternions en GLSL, mais tu peux utiliser un vec4 et faire les mathématiques toi-même dans le shader.

###Comment convertir un quaternion vers une matrice ?

{% highlight cpp linenos %}
mat4 RotationMatrix = quaternion::toMat4(quaternion);
{% endhighlight %}

Tu peux maintenant construire ta matrice de modèle comme d'habitude :

{% highlight cpp linenos %}
mat4 RotationMatrix = quaternion::toMat4(quaternion);
...
mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
// Tu peux maintenant utiliser ModelMatrix pour construire la matrice MVP
{% endhighlight %}

#Donc, quelle méthode choisir ?

Choisir entre les angles d'Euler et les quaternions est difficile. Les angles d'Euler sont intuitifs pour les artistes, donc si tu écris un éditeur 3D, utilises-les. Mais les quaternions sont pratiques pour les programmeurs et aussi moins couteux, donc tu devrais les utiliser dans le cœur du moteur 3D.

Le consensus général est exactement cela : utilises les quaternions en interne et exposes les angles d'Euler à chaque fois qu'il y a une interface utilisateur.

Tu vas être capable de gérer tout ce que tu veux (ou du moins, cela sera plus facile) et tu peux toujours utiliser les angles d'Euler pour les entités le nécessitant (comme dit précédemment : la caméra, les humanoïdes et c'est à peu près tout) avec une simple conversion.

#Autres ressources

* Les livres dans la page des [outils et liens utiles]({{site.baseurl}}/miscellaneous/useful-tools-links/#books) !
* Aussi vieux qu'il puisse être, le Game Programming Gem 1 contient quelques articles géniaux sur les quaternions. Tu peux probablement le trouver en ligne aussi.
* Cette [présentation de la GDC](http://www.essentialmath.com/GDC2012/GDC2012_JMV_Rotations.pdf) sur les rotations
* Le [tutoriel sur les quaternions](http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation) du wiki des programmeurs de jeux vidéo
* La [FAQ sur les quaternions](http://www.ogre3d.org/tikiwiki/Quaternion+and+Rotation+Primer) d'Ogre, bien que la seconde partie soit principalement spécifique à Ogre
* Les fichiers d'Ogre [Vector3D.h](https://bitbucket.org/sinbad/ogre/src/3cbd67467fab3fef44d1b32bc42ccf4fb1ccfdd0/OgreMain/include/OgreVector3.h?at=default) et [Quaternions.cpp](https://bitbucket.org/sinbad/ogre/src/3cbd67467fab3fef44d1b32bc42ccf4fb1ccfdd0/OgreMain/src/OgreQuaternion.cpp?at=default).

#Feuille de triche

##Comment savoir que deux quaternions sont similaires ?

Lors de l'utilisation d'un vecteur, le produit scalaire donne le cosinus de l'angle entre ces deux vecteurs. Si cette valeur est 1, alors les vecteurs sont dans la même direction.

Avec les quaternions, c'est la même chose :

{% highlight cpp linenos %}
float matching = quaternion::dot(q1, q2);
if ( abs(matching-1.0) < 0.001 ){
    // q1 and q2 are similar
}
{% endhighlight %}

Tu peux aussi obtenir l'angle entre q1 et q2 en prenant le acos() de ce produit scalaire.

##Comment appliquer une rotation sur un point ?

Tu peux faire comme ça :

{% highlight cpp linenos %}
rotated_point = orientation_quaternion *  point;
{% endhighlight %}

... mais si tu souhaites calculer ta matrice de modèle, tu devrais plutot convertir le quaternion en une matrice.

> Le centre de la rotation est toujours l'origine.

Si tu souhaites tourner autour d'un autre point :

{% highlight cpp linenos %}
rotated_point = origin + (orientation_quaternion * (point-origin));
{% endhighlight %}

##Comment interpoler entre deux quaternions ?

Cela s'appelle SLERP : **S**phérical **L**iner int**ERP**olation. Avec GLM, tu peux le faire avec la fonction mix :

{% highlight cpp linenos %}
glm::quat interpolatedquat = quaternion::mix(quat1, quat2, 0.5f); // or whatever factor
{% endhighlight %}

##Comment accumuler deux rotations ?

C'est simple ! Multiplie les deux quaternions ensemble. L'ordre est identique à celui des matrices, c'est-à-dire l'inverse :

{% highlight cpp linenos %}
quat combined_rotation = second_rotation * first_rotation;
{% endhighlight %}

##Comment trouver la rotation entre deux vecteurs ?

(En d'autres mots : Comment trouver le quaternion dont on a besoin pour tourner v1 et qu'il corresponde à v2.)

L'idée de base est évidente :

* L'angle entre deux vecteurs est facilement trouvable : le produit scalaire donne son cosinus
* L'axe nécessaire est aussi facilement trouvable : c'est le produit vectoriel des deux vecteurs.

L'algorithme suivant fait exactement cela, mais gère aussi quelques cas spéciaux :

{% highlight cpp linenos %}
quat RotationBetweenVectors(vec3 start, vec3 dest){
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
		if (gtx::norm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return gtx::quaternion::angleAxis(180.0f, rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}
{% endhighlight %}

(Tu peux trouver cette fonction dans [common/quaternion_utils.cpp](https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp).)

##J'ai besoin d'un équivalent à gluLookAt. Comment orienter un objet vers un point ?

Utilise RotationBetweenVectors !

{% highlight cpp linenos %}
// Find the rotation between the front of the object (that we assume towards +Z,
// but this depends on your model) and the desired direction
quat rot1 = RotationBetweenVectors(vec3(0.0f, 0.0f, 1.0f), direction);
{% endhighlight %}

Maintenant, tu peux aussi souhaiter que ton objet soit droit :

{% highlight cpp linenos %}
// Recompute desiredUp so that it's perpendicular to the direction
// You can skip that part if you really want to force desiredUp
vec3 right = cross(direction, desiredUp);
desiredUp = cross(right, direction);

// Because of the 1rst rotation, the up is probably completely screwed up.
// Find the rotation between the "up" of the rotated object, and the desired up
vec3 newUp = rot1 * vec3(0.0f, 1.0f, 0.0f);
quat rot2 = RotationBetweenVectors(newUp, desiredUp);
{% endhighlight %}

Maintenant, combine-les :

{% highlight cpp linenos %}
quat targetOrientation = rot2 * rot1; // remember, in reverse order.
{% endhighlight %}

Attention, « direction » est, bien sûr, une direction et non la position cible ! Tu peux calculer la position simplement avec : targetPos - currentPos.

Une fois que tu as l'orientation cible, tu vas probablement souhaiter effectuer une interpolation entre startOrientation et targetOrientation.
(Tu peux trouver cette fonction dans [common/quaternion_utils.cpp](https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp)).

##Comment utiliser LookAt mais en limitant la rotation à une certaine vitesse ?

L'idée de base est d'effectuer un SLERP (utilise glm::mix), mais de jouer avec la valeur d'interpolation afin que l'angle ne soit pas supérieur à la valeur désirée :

{% highlight cpp linenos %}
float mixFactor = maxAllowedAngle / angleBetweenQuaternions;
quat result = glm::gtc::quaternion::mix(q1, q2, mixFactor);
{% endhighlight %}

Voici une fonction plus complexe, qui gère les cas spéciaux. Elle n'utilise même pas directement mix() comme optimisation :

{% highlight cpp linenos %}
quat RotateTowards(quat q1, quat q2, float maxAngle){

	if( maxAngle < 0.001f ){
		// No rotation allowed. Prevent dividing by 0 later.
		return q1;
	}

	float cosTheta = dot(q1, q2);

	// q1 and q2 are already equal.
	// Force q2 just to be sure
	if(cosTheta > 0.9999f){
		return q2;
	}

	// Avoid taking the long path around the sphere
	if (cosTheta < 0){
	    q1 = q1*-1.0f;
	    cosTheta *= -1.0f;
	}

	float angle = acos(cosTheta);

	// If there is only a 2&deg; difference, and we are allowed 5&deg;,
	// then we arrived.
	if (angle < maxAngle){
		return q2;
	}

	float fT = maxAngle / angle;
	angle = maxAngle;

	quat res = (sin((1.0f - fT) * angle) * q1 + sin(fT * angle) * q2) / sin(angle);
	res = normalize(res);
	return res;

}
{% endhighlight %}

Que tu peux utiliser comme suit :

{% highlight cpp linenos %}
CurrentOrientation = RotateTowards(CurrentOrientation, TargetOrientation, 3.14f * deltaTime );
{% endhighlight %}

(Tu peux trouver cette fonction dans [common/quaternion_utils.cpp](https://github.com/opengl-tutorials/ogl/blob/master/common/quaternion_utils.cpp))

##Comment je peux ...

Si tu arrives pas à trouver comment faire quelque chose, envoie nous un email, et on l'ajoutera à la liste !
