---
layout: page
status: publish
published: true
title: 'Picking avec une bibliothèque physique'
date: '2015-11-22 09:30:19 +0200'
categories: []
order: 80
tags: []
language: fr
---

Dans ce tutoriel, nous allons voir la méthode « recommandée » pour picker[^picker] dans un moteur de jeu classique - ce qui peut ne pas être ton cas.

L'idée est que le moteur de jeu devra intégrer un moteur physique dans tous les cas et tous les moteurs physiques ont des fonctions pour obtenir l'intersection d'un rayon avec la scène. En plus, ces fonctions sont certainement mieux optimisées que ce que tu peux faire toi-même : tous les moteurs physiques utilisent des structures de partitionnement de l'espace évitant de tester les intersections avec les objets qui ne sont pas dans la même région.

Dans ce tutoriel, nous allons utiliser le moteur Bullet Physics Engine, mais les concepts sont identiques pour n'importe quel autre : PhysX, HavoK, etc.

#Intégration de Bullet

De nombreux tutoriels expliquent comment intégrer Bullet ; en particulier, le [wiki de Bullet](http://bulletphysics.org/mediawiki-1.5.8/index.php/Main_Page) est très bien fait.

``` cpp
// Initialize Bullet. This strictly follows http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World, 
// even though we won't use most of this stuff.

// Build the broadphase
btBroadphaseInterface* broadphase = new btDbvtBroadphase();

// Set up the collision configuration and dispatcher
btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

// The actual physics solver
btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

// The world.
btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
dynamicsWorld->setGravity(btVector3(0,-9.81f,0));
```

Chaque objet doit avoir une forme de collision (*Collision Shape*). Même si celle-ci peut être le modèle en lui-même, cela est généralement une mauvaise idée pour les performances. À la place, on utilise habituellement des formes plus simples telles que les boîtes, les sphères ou les capsules. Voici quelques formes de collision. De gauche à droite : sphère, cube, convex hull du modèle, modèle d'origine. Les sphères sont moins précises que le modèle, mais bien plus rapides à tester.

![]({{site.baseurl}}/assets/images/tuto-picking-physics-library/CollisionShapes.png)

Dans cet exemple, tous les modèles utilisent la même boîte :

``` cpp
btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
```

Les moteurs physiques ne connaissent rien sur OpenGL ; et en réalité, ceux-ci peuvent s'exécuter sans aucune visualisation 3D. Donc on ne peut pas directement donner notre VBO à Bullet. À la place, on doit ajouter un corps rigide (*Rigid Body*) dans la simulation.

``` cpp
btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
	btQuaternion(orientations[i].x, orientations[i].y, orientations[i].z, orientations[i].w), 
	btVector3(positions[i].x, positions[i].y, positions[i].z)
));

btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
	0,                  // mass, in kg. 0 -> Static object, will never move.
	motionstate,
	boxCollisionShape,  // collision shape of body
	btVector3(0,0,0)    // local inertia
);
btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

dynamicsWorld->addRigidBody(rigidBody);
```

On peut voir que le corps rigide utilise une forme de collision pour définir sa forme.

On garde aussi une trace du corps rigide, mais comme il est indiqué dans le commentaire, un vrai moteur aura d'une quelconque façon une classe MonGameObject avec la position, l'orientation, le modèle OpenGL et un pointeur vers le corps rigide.

``` cpp
rigidbodies.push_back(rigidBody);

// Small hack : store the mesh's index "i" in Bullet's User Pointer.
// Will be used to know which object is picked. 
// A real program would probably pass a "MyGameObjectPointer" instead.
rigidBody->setUserPointer((void*)i);
```

En d'autres mots : n'utilise pas le code ci-dessus dans la vraie vie ! Ce n'est que pour les besoins de la démonstration.

#Lancer de rayon

##Trouver la position/direction du rayon

Premièrement, on doit trouver un rayon qui commence à la position de la caméra et va « à travers la souris ». Cela est fait dans la fonction ScreenPosToWorldRay().

D'abord, on trouve la position de départ et de fin du rayon dans les coordonnées normalisées du périphérique (Normalized Device Coordinates). On le fait dans cet espace, car c'est très simple :

``` cpp
// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
glm::vec4 lRayStart_NDC(
	((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
	((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
	-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
	1.0f
);
glm::vec4 lRayEnd_NDC(
	((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
	((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
	0.0,
	1.0f
);
```

Pour comprendre ce code, voila une nouvelle fois à cette image du quatrième tutoriel :

![]({{site.baseurl}}/assets/images/tuto-picking-physics-library/homogeneous.png)

L'espace de coordonnées normalisé du périphérique est un cube 2*2*2, centré sur l'origine, donc dans cet espace, le rayon « passant par la souris » n'est qu'une ligne droite, perpendiculaire au plan proche ! Cela rend IRayStart_NDC et IEndStart_NDC facile à calculer.

Maintenant, on n'a qu'à appliquer la transformation inverse :

``` cpp
// The Projection matrix goes from Camera Space to NDC.
// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

// The View Matrix goes from World Space to Camera Space.
// So inverse(ViewMatrix) goes from Camera Space to World Space.
glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;

// Faster way (just one inverse)
//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;
```

Avec *IRayStart_worldspace* et *IRayEnd_worldspace*, la direction du rayon (dans l'espace monde) est facile à calculer :

``` cpp
glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
lRayDir_world = glm::normalize(lRayDir_world);
```

##Utiliser RayTest()

Le lancer de rayon est très simple, aucun besoin de commentaire :

``` cpp
glm::vec3 out_end = out_origin + out_direction*1000.0f;

btCollisionWorld::ClosestRayResultCallback RayCallback(
	btVector3(out_origin.x, out_origin.y, out_origin.z), 
	btVector3(out_end.x, out_end.y, out_end.z)
);
dynamicsWorld->rayTest(
	btVector3(out_origin.x, out_origin.y, out_origin.z), 
	btVector3(out_end.x, out_end.y, out_end.z), 
	RayCallback
);

if(RayCallback.hasHit()) {
	std::ostringstream oss;
	oss << "mesh " << (int)RayCallback.m_collisionObject->getUserPointer();
	message = oss.str();
}else{
	message = "background";
}
```

La seule chose est que pour une raison étrange, tu dois définir la position de départ et de fin du rayon, deux fois.

C'est tout, tu sais comment implémenter le picking[^picker] dans Bullet !

#Avantages et inconvénients

Avantages :

* Très simple lorsque tu as déjà un moteur physique
* Rapide
* N'impacte pas les performances OpenGL

Inconvénients :

* Probablement pas la bonne solution si tu n'as pas besoin de simulation physique ou d'un moteur de collision.


#Remarques finales

Tous les moteurs physiques possèdent une vue de débogage. Le code d'exemple montre comment l'activer avec Bullet. Tu obtiendras une représentation de ce que Bullet sait sur votre scène, ce qui est vraiment très utile pour déboguer les problèmes liés à la physique, notamment pour être sûr que le « monde visuel » est consistant avec le « monde physique ».

![]({{site.baseurl}}/assets/images/tuto-picking-physics-library/BulletDebug.png)

La boîte verte est la forme de collision, à la même position et orientation que le modèle. La boîte rouge est la boîte englobante alignée sur les axes (AABB), qui est utilisée pour un rapide test de réjection : si le rayon ne touche pas le AABB (très facile à calculer), alors il ne touchera pas la forme de collision. Finalement, tu peux voir les axes de l'objet en bleu et rouge (regarde au nez et à l'oreille). Pratique !

[^picker]: *Picker* c'est détecter quel objet se trouve sous le pointeur de la souris. Le *picking* c'est donc la *détection de l'objet sous le pointeur de la souris*
