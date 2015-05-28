---
layout: page
status: publish
published: true
title: Picking with a physics library
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 883
wordpress_url: http://www.opengl-tutorial.org/?page_id=883
date: '2013-05-18 20:42:49 +0200'
date_gmt: '2013-05-18 20:42:49 +0200'
categories: []
order: 80
tags: []
language: ru
---
<p>In this tutorial, we will see the "recommended" way to pick objects in a classical game engine - which might not be your case.</p>
<p>The idea is that the game engine will need a physics engine anyway, and all physics engine have functions to intersect a ray with the scene. On top of that, these functions are probably more optimized than what you'll be able to do yourself : all engines use <em>space partitionning</em> structures, which make it possible to avoid testing intersection with most objects which are not in the same region.</p>
<p>In this tutorial, we will use the Bullet Physics Engine, but the concepts are exactly the same for any other : PhysX, Havok, etc.</p>
<h1>Bullet integration</h1><br />
Lots of tutorials explain how to integrate Bullet; in particular, the Bullet's wiki is very well done.</p>
<pre class="brush: cpp">//&nbsp;Initialize&nbsp;Bullet.&nbsp;This&nbsp;strictly&nbsp;follows&nbsp;http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World,&nbsp;<br />
//&nbsp;even&nbsp;though&nbsp;we&nbsp;won't&nbsp;use&nbsp;most&nbsp;of&nbsp;this&nbsp;stuff.</p>
<p>//&nbsp;Build&nbsp;the&nbsp;broadphase<br />
btBroadphaseInterface*&nbsp;broadphase&nbsp;=&nbsp;new&nbsp;btDbvtBroadphase();</p>
<p>//&nbsp;Set&nbsp;up&nbsp;the&nbsp;collision&nbsp;configuration&nbsp;and&nbsp;dispatcher<br />
btDefaultCollisionConfiguration*&nbsp;collisionConfiguration&nbsp;=&nbsp;new&nbsp;btDefaultCollisionConfiguration();<br />
btCollisionDispatcher*&nbsp;dispatcher&nbsp;=&nbsp;new&nbsp;btCollisionDispatcher(collisionConfiguration);</p>
<p>//&nbsp;The&nbsp;actual&nbsp;physics&nbsp;solver<br />
btSequentialImpulseConstraintSolver*&nbsp;solver&nbsp;=&nbsp;new&nbsp;btSequentialImpulseConstraintSolver;</p>
<p>//&nbsp;The&nbsp;world.<br />
btDiscreteDynamicsWorld*&nbsp;dynamicsWorld&nbsp;=&nbsp;new&nbsp;btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);<br />
dynamicsWorld->setGravity(btVector3(0,-9.81f,0));</pre><br />
Each object must have a <em>Collision Shape</em>. While this collision shape can be the mesh itself, it's often a bad idea for performance. Instead, one usually use much simpler shapes as boxes, spheres or capsules. Here are a few collision shapes.&nbsp;From left to right : sphere, cube, convex hull of the mesh, original mesh. Spheres are less precise than the full mesh, but much much faster to test.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/CollisionShapes.png"><img class="alignnone  wp-image-889" title="CollisionShapes" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/CollisionShapes.png" alt="" width="960" height="324" /></a></p>
<p>In this example, all meshes will use the same box :</p>
<pre class="brush: cpp">btCollisionShape*&nbsp;boxCollisionShape&nbsp;=&nbsp;new&nbsp;btBoxShape(btVector3(1.0f,&nbsp;1.0f,&nbsp;1.0f));</pre><br />
Physics engines don't know anything about OpenGL; and in fact, all of them can run without any 3D visualization at all. So you can't directly give Bullet your VBO. You have to add a <em>Rigid Body</em> in the simulation instead.</p>
<pre class="brush: cpp">btDefaultMotionState*&nbsp;motionstate&nbsp;=&nbsp;new&nbsp;btDefaultMotionState(btTransform(<br />
	btQuaternion(orientations[i].x,&nbsp;orientations[i].y,&nbsp;orientations[i].z,&nbsp;orientations[i].w),&nbsp;<br />
	btVector3(positions[i].x,&nbsp;positions[i].y,&nbsp;positions[i].z)<br />
));</p>
<p>btRigidBody::btRigidBodyConstructionInfo&nbsp;rigidBodyCI(<br />
	0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;//&nbsp;mass,&nbsp;in&nbsp;kg.&nbsp;0&nbsp;->&nbsp;Static&nbsp;object,&nbsp;will&nbsp;never&nbsp;move.<br />
	motionstate,<br />
	boxCollisionShape,&nbsp;&nbsp;//&nbsp;collision&nbsp;shape&nbsp;of&nbsp;body<br />
	btVector3(0,0,0)&nbsp;&nbsp;&nbsp;&nbsp;//&nbsp;local&nbsp;inertia<br />
);<br />
btRigidBody&nbsp;*rigidBody&nbsp;=&nbsp;new&nbsp;btRigidBody(rigidBodyCI);</p>
<p>dynamicsWorld->addRigidBody(rigidBody);</pre><br />
Notice that the Rigid Body use the Collision Shape to determine its shape.</p>
<p>We also keep track of this rigid body, but as the comment says, a real engine would somehow have a MyGameObject class with the position, the orientation, the OpenGL mesh, and a pointer to the Rigid Body.</p>
<pre class="brush: cpp">rigidbodies.push_back(rigidBody);</p>
<p>//&nbsp;Small&nbsp;hack&nbsp;:&nbsp;store&nbsp;the&nbsp;mesh's&nbsp;index&nbsp;"i"&nbsp;in&nbsp;Bullet's&nbsp;User&nbsp;Pointer.<br />
//&nbsp;Will&nbsp;be&nbsp;used&nbsp;to&nbsp;know&nbsp;which&nbsp;object&nbsp;is&nbsp;picked.&nbsp;<br />
//&nbsp;A&nbsp;real&nbsp;program&nbsp;would&nbsp;probably&nbsp;pass&nbsp;a&nbsp;"MyGameObjectPointer"&nbsp;instead.<br />
rigidBody->setUserPointer((void*)i);</pre><br />
In other words : please don't use the above code in real life ! It's just for demo purpose.</p>
<h1>Raycasting</h1></p>
<h2>Finding the ray direction</h2><br />
First, we need to find a ray which starts at the camera and goes "through the mouse". This is done in the <em>ScreenPosToWorldRay()</em> function.</p>
<p>First, we find the ray's start and end position in Normalized Device Coordinates. We do it in this space because it's very easy :</p>
<pre class="brush: cpp">//&nbsp;The&nbsp;ray&nbsp;Start&nbsp;and&nbsp;End&nbsp;positions,&nbsp;in&nbsp;Normalized&nbsp;Device&nbsp;Coordinates&nbsp;(Have&nbsp;you&nbsp;read&nbsp;Tutorial 4 ?)<br />
glm::vec4&nbsp;lRayStart_NDC(<br />
	((float)mouseX/(float)screenWidth&nbsp;&nbsp;-&nbsp;0.5f)&nbsp;*&nbsp;2.0f,&nbsp;//&nbsp;[0,1024]&nbsp;->&nbsp;[-1,1]<br />
	((float)mouseY/(float)screenHeight&nbsp;-&nbsp;0.5f)&nbsp;*&nbsp;2.0f,&nbsp;//&nbsp;[0,&nbsp;768]&nbsp;->&nbsp;[-1,1]<br />
	-1.0,&nbsp;//&nbsp;The&nbsp;near&nbsp;plane&nbsp;maps&nbsp;to&nbsp;Z=-1&nbsp;in&nbsp;Normalized&nbsp;Device&nbsp;Coordinates<br />
	1.0f<br />
);<br />
glm::vec4&nbsp;lRayEnd_NDC(<br />
	((float)mouseX/(float)screenWidth&nbsp;&nbsp;-&nbsp;0.5f)&nbsp;*&nbsp;2.0f,<br />
	((float)mouseY/(float)screenHeight&nbsp;-&nbsp;0.5f)&nbsp;*&nbsp;2.0f,<br />
	0.0,<br />
	1.0f<br />
);</pre><br />
To understand this code, let's have a look at this picture from Tutorial 4 again :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/homogeneous.png"><img class="alignnone size-full wp-image-76" title="homogeneous" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/homogeneous.png" alt="" width="960" height="540" /></a></p>
<p>NDC is a 2*2*2 cube centered on the origin, so in this space, the ray going "trough the mouse" is just a straight line, perpendicular to the near plane! Which makes lRayStart_NDC and lEndStart_NDC so easy to compute.</p>
<p>Now we simply have to apply the inverse transformation as the usual one :</p>
<pre class="brush: cpp">//&nbsp;The&nbsp;Projection&nbsp;matrix&nbsp;goes&nbsp;from&nbsp;Camera&nbsp;Space&nbsp;to&nbsp;NDC.<br />
//&nbsp;So&nbsp;inverse(ProjectionMatrix)&nbsp;goes&nbsp;from&nbsp;NDC&nbsp;to&nbsp;Camera&nbsp;Space.<br />
glm::mat4&nbsp;InverseProjectionMatrix&nbsp;=&nbsp;glm::inverse(ProjectionMatrix);</p>
<p>//&nbsp;The&nbsp;View&nbsp;Matrix&nbsp;goes&nbsp;from&nbsp;World&nbsp;Space&nbsp;to&nbsp;Camera&nbsp;Space.<br />
//&nbsp;So&nbsp;inverse(ViewMatrix)&nbsp;goes&nbsp;from&nbsp;Camera&nbsp;Space&nbsp;to&nbsp;World&nbsp;Space.<br />
glm::mat4&nbsp;InverseViewMatrix&nbsp;=&nbsp;glm::inverse(ViewMatrix);</p>
<p>glm::vec4&nbsp;lRayStart_camera&nbsp;=&nbsp;InverseProjectionMatrix&nbsp;*&nbsp;lRayStart_NDC;&nbsp;&nbsp;&nbsp;&nbsp;lRayStart_camera/=lRayStart_camera.w;<br />
glm::vec4&nbsp;lRayStart_world&nbsp;&nbsp;=&nbsp;InverseViewMatrix&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*&nbsp;lRayStart_camera;&nbsp;lRayStart_world&nbsp;/=lRayStart_world&nbsp;.w;<br />
glm::vec4&nbsp;lRayEnd_camera&nbsp;&nbsp;&nbsp;=&nbsp;InverseProjectionMatrix&nbsp;*&nbsp;lRayEnd_NDC;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lRayEnd_camera&nbsp;&nbsp;/=lRayEnd_camera&nbsp;&nbsp;.w;<br />
glm::vec4&nbsp;lRayEnd_world&nbsp;&nbsp;&nbsp;&nbsp;=&nbsp;InverseViewMatrix&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*&nbsp;lRayEnd_camera;&nbsp;&nbsp;&nbsp;lRayEnd_world&nbsp;&nbsp;&nbsp;/=lRayEnd_world&nbsp;&nbsp;&nbsp;.w;</p>
<p>//&nbsp;Faster&nbsp;way&nbsp;(just&nbsp;one&nbsp;inverse)<br />
//glm::mat4&nbsp;M&nbsp;=&nbsp;glm::inverse(ProjectionMatrix&nbsp;*&nbsp;ViewMatrix);<br />
//glm::vec4&nbsp;lRayStart_world&nbsp;=&nbsp;M&nbsp;*&nbsp;lRayStart_NDC;&nbsp;lRayStart_world/=lRayStart_world.w;<br />
//glm::vec4&nbsp;lRayEnd_world&nbsp;&nbsp;&nbsp;=&nbsp;M&nbsp;*&nbsp;lRayEnd_NDC&nbsp;&nbsp;;&nbsp;lRayEnd_world&nbsp;&nbsp;/=lRayEnd_world.w;</pre><br />
With lRayStart_worldspace and lRayEnd_worldspace, the ray's direction (in world space) is straightforward to compute :</p>
<pre class="brush: cpp">glm::vec3&nbsp;lRayDir_world(lRayEnd_world&nbsp;-&nbsp;lRayStart_world);<br />
lRayDir_world&nbsp;=&nbsp;glm::normalize(lRayDir_world);</pre></p>
<h2>Using rayTest()</h2><br />
Raycasting is very simple, no need for special comments :</p>
<pre class="brush: cpp">out_direction&nbsp;=&nbsp;out_direction*1000.0f;</p>
<p>btCollisionWorld::ClosestRayResultCallback&nbsp;RayCallback(<br />
	btVector3(out_origin.x,&nbsp;out_origin.y,&nbsp;out_origin.z),&nbsp;<br />
	btVector3(out_direction.x,&nbsp;out_direction.y,&nbsp;out_direction.z)<br />
);<br />
dynamicsWorld->rayTest(<br />
	btVector3(out_origin.x,&nbsp;out_origin.y,&nbsp;out_origin.z),&nbsp;<br />
	btVector3(out_direction.x,&nbsp;out_direction.y,&nbsp;out_direction.z),&nbsp;<br />
	RayCallback<br />
);</p>
<p>if(RayCallback.hasHit())&nbsp;{<br />
	std::ostringstream&nbsp;oss;<br />
	oss&nbsp;<<&nbsp;"mesh&nbsp;"&nbsp;<<&nbsp;(int)RayCallback.m_collisionObject->getUserPointer();<br />
	message&nbsp;=&nbsp;oss.str();<br />
}else{<br />
	message&nbsp;=&nbsp;"background";<br />
}</pre><br />
The only thing is that for some weird reason, you have to set the ray's start and direction twice.</p>
<p>That's it, you know how to implement picking with Bullet !</p>
<h1>Pro and cons</h1><br />
Pros :</p>
<ul>
<li>Very easy when you already have a physics engine</li>
<li>Fast</li>
<li>Doesn't impact OpenGL's performance</li><br />
</ul><br />
Cons :</p>
<ul>
<li>Probably not the right solution if you don't need any physics or collision engine</li><br />
</ul></p>
<h1>Final remarks</h1><br />
All physics engines have a debug viewer. The example code shows how to to it with Bullet. You end up with a representation of what Bullet knows about your scene, which is incredibly useful to debug physics-related problem, especially to be sure that the "visual world" is consistent with the "physics world" :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/BulletDebug.png"><img class="alignnone size-large wp-image-887" title="BulletDebug" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/BulletDebug-1024x793.png" alt="" width="640" height="495" /></a></p>
<p>The green box is the <em>Collision Shape</em>, at the same position and orientation than the mesh. The red box is the object's <em>Axis-Aligned Bounding Box</em> (AABB), which is used as a faster rejection test : if the ray doesn't intersect the AABB (very cheap to compute), then there is no chance that it will intersect the collision shape. Finally, you can see the object's axes in blue and red (look at the nose and ear). Handy !</p>
