---
layout: page
status: publish
published: true
title: Використовуючи бібліотеку фізики
date: '2013-05-18 20:42:49 +0200'
date_gmt: '2013-05-18 20:42:49 +0200'
categories: []
order: 80
tags: []
print: true
language: uk
---

В цьому туторіалі ми побачимо "рекомендований" спосіб обирання об'єкту в класичному рушію для гри, що може бути не Ваш випадок.

Основана ідея в тому, що ігровий рушій буде мати бібліотеку фізики в будь-якому випадку і всі бібліотеки фізики мають функції для визначення перетину променя з сценою. В основному, такі функції будуть більше оптимізовані ніж те, що Ви зможете написати власноруч - все рушії використовують структури для *поділу простору*, які дозволяють не робити розрахунків для об'єктів, що не знаходяться в потрібній області.

В цьому туторіалі ми будемо використовувати рушій Bullet Physics, але в цілому принципи аналогічні в інших - PhysX, Havok.

# Інтеграція Bullet

Багато туторіалів пояснює, як інтегрувати Bullet, наприклад [Bullet's wiki](http://bulletphysics.org/mediawiki-1.5.8/index.php/Main_Page) - гарний варіант.


``` cpp
// Ініціалізація Bullet. Чітко по інструкції http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World, 
// хоча ми не будемо використовувати більшість можливостей.

// Побудуємо "широку фазу"
btBroadphaseInterface* broadphase = new btDbvtBroadphase();

// Налаштуємо конфігурації колізій і диспетчер
btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

// Справжній "розв'язувач" фізики
btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

// Світ
btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
dynamicsWorld->setGravity(btVector3(0,-9.81f,0));
```

Кожний об'єкт повинен мати *форму зіткнення* (*Collision Shape*). Так, меш об'єкту можна використовувати як фігуру для зіткнення (колізії), та це погано для продуктивності (швидкості виконання). Тому, зазвичай, використовується значно простіші фігури - коробка (паралелепіпед), сфери, капсули. Є декілька фігур зіткнення.  Зліва направо - сфера, куб, опукла оболонка меша, оригінальний меш. Сфери не такі точні, але значно значно швидші для перевірки.

![]({{site.baseurl}}/assets/images/tuto-picking-physics-library/CollisionShapes.png)


В цьому прикладі, всі меши (сітки) будуть використовувати однакову коробку:

``` cpp
btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
```

Рушії фізики нічого не знають про OpenGL і, як факт, всі вони можуть бути запущені без 3D візуалізації. Отже, ви не можете просто передати Ваш VBO в Bullet. Ви повинні додати *Жорстке тіло* (*Rigid Body*) в симуляцію.

``` cpp
btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
	btQuaternion(orientations[i].x, orientations[i].y, orientations[i].z, orientations[i].w), 
	btVector3(positions[i].x, positions[i].y, positions[i].z)
));

btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
	0,                  // маса, в кг. 0 -> статичний об'єкт, ніколи не буде рухатись.
	motionstate,
	boxCollisionShape,  // фігура для зіткнення
	btVector3(0,0,0)    // локальна інерція
);
btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

dynamicsWorld->addRigidBody(rigidBody);
```

Зверніть увагу, що Жорстке тіло використовує фігуру зіткнень для визначення його форми.

В повноцінному ігровому рушії скоріш за все буде клас з ім'ям наклашт MyGameObject, який буде містити позицію, орієнтацію, меш для OpenGL вказівник на об'єкт Жорсткого тіла. Та тут ми спрощуємо.

Notice that the Rigid Body use the Collision Shape to determine its shape.


``` cpp
rigidbodies.push_back(rigidBody);

// Маленький хак : Збережемо індекс меша в Bullet's User Pointer.
// І таким чином ми будемо знати, який об'єкт обрали 
// В повноцінній програмі скоріше за все буде передано "MyGameObjectPointer"
rigidBody->setUserPointer((void*)i);
```

Простіше кажучи - не використовуйте наведений код в реальному житті. Це демо!

# Кидання променів (Raycasting)


## Знаходження напрямку променя

Спочатку нам потрібно знайти промінь, який починається в камері і йде "через вказівник миші". Це реалізовано в функції `ScreenPosToWorldRay()`.

Знайдемо початкову та кінцеву позицію променя (відрізка?) в нормалізованих координатах пристрою (NDC). Ми робимо це в цих координатах, тому що це дуже легко:

``` cpp
// Початок і кінець променя в нормалізованих координатах пристрою (Ви читали 4 туторіал?)
glm::vec4 lRayStart_NDC(
	((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
	((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
	-1.0, // Ближня площина знаходиться на Z=-1 в Нормальних координатах пристрою
	1.0f
);
glm::vec4 lRayEnd_NDC(
	((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f,
	((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
	0.0,
	1.0f
);
```

Щоб зрозуміти цей код, давайте поглянемо на малюнок з 4 туторіалу:

![]({{site.baseurl}}/assets/images/tuto-picking-physics-library/homogeneous.png)

NDC це куб, 2*2*2 з центром в початку координат, в цьому просторі, промінь йде "через мишу" є просто прямою лінією, перпендикулярною до ближньої площини. Це робить `lRayStart_NDC` та `lEndStart_NDC` такими, що легко розраховуються.

Тепер нам потрібно застосувати зворотне перетворення як звичайне:

``` cpp
// Матриця проекції веде від Простору камери в NDC
// Отже inverse(ProjectionMatrix) веде з NDC в простір камери.
glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

// Матриця виду веде з світового простору в прості камери.
// Отже inverse(ViewMatrix) веде з простору камери в світовий простір.
glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;

// Найшвидший шлях (одна інверсія)
//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;
```

За допомогою lRayStart_worldspace і lRayEnd_worldspace, напрямок променю (в світовому просторі) дуже легко обчислити:

``` cpp
glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
lRayDir_world = glm::normalize(lRayDir_world);
```

## Використання rayTest()

Raycasting дуже простий, навіть не потрібно спеціальних коментарів:

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

Є тільки одна дивна річ, Вам потрібно встановити початок променю і напрямок двічі.

Це все, що Вам потрібно знати, що б реалізувати функцію вибору з Bullet!

# Переваги та недоліки

Переваги :

* Дуже легко, якщо у Вас все є рушій фізики
* Швидко
* Не заважає швидкодії OpenGL.

Недоліки :

* Можливо це не найкраще рішення, якщо Вам більше ні для чого не потрібний рушій фізики чи зіткнень.

# Висновки та зауваження

Всі фізичні рушії містять засоби налагодження. Приклад коду вище показує, як це зробити з Bullet. У підсумку Ви отримуєте представлення того, що Bullet знає про Вашу сцену, що є неймовірно корисним для налагодження проблеми, пов'язаної з фізикою, особливо для того, щоб переконатися, що «візуальний світ» узгоджується зі «світом фізики»:

![]({{site.baseurl}}/assets/images/tuto-picking-physics-library/BulletDebug.png)

Зелений ящик є *Collision Shape* (формою зіткнення) з тією самою позицією і орієнтацією, що і меш. Червоний ящик є об'єктом *Axis-Aligned Bounding Box*  (вирівненим по осям обмежувальним ящиком) - AABB, що використовується як швидкий тест на відкидання - якщо промінь не перетинається з AABB (а це дуже легко і швидко порахувати), то тоді немає шансу, що промінь перетнеться з самим об'єктом. А ще Ви бачите осі об'єкту, зображені синім та червоним (подивіться на ніс на вухо). Дуже зручно!