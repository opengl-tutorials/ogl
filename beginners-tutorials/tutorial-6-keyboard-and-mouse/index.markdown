---
layout: page
status: publish
published: true
title: 'Tutorial 6 : Keyboard and Mouse'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 170
wordpress_url: http://www.opengl-tutorial.org/?page_id=170
date: '2011-05-08 08:26:13 +0200'
date_gmt: '2011-05-08 08:26:13 +0200'
categories: [tuto]
order: 60
tags: []
---
<p>Welcome for our 6th tutorial !</p>
<p>We will now learn how to use the mouse and the keyboard to move the camera just like in a FPS.</p>
<h1>The interface</h1><br />
Since this code will be re-used throughout the tutorials, we will put the code in a separate file : common/controls.cpp, and declare the functions in common/controls.hpp so that tutorial06.cpp knows about them.</p>
<p>The code of tutorial06.cpp doesn't change much from the previous tutorial. The major modification is that instead of computing the MVP matrix once, we now have to do it every frame. So let's move this code inside the main loop :</p>
<pre class="brush: cpp">do{</p>
<p>    // ...</p>
<p>    // Compute the MVP matrix from keyboard and mouse input<br />
    computeMatricesFromInputs();<br />
    glm::mat4 ProjectionMatrix = getProjectionMatrix();<br />
    glm::mat4 ViewMatrix = getViewMatrix();<br />
    glm::mat4 ModelMatrix = glm::mat4(1.0);<br />
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;</p>
<p>    // ...<br />
}</pre><br />
This code needs 3 new functions :</p>
<ul>
<li>computeMatricesFromInputs() reads the keyboard and mouse and computes the Projection and View matrices. This is where all the magic happens.</li>
<li>getProjectionMatrix() just returns the computed Projection matrix.</li>
<li>getViewMatrix() just returns the computed View matrix.</li><br />
</ul><br />
This is just one way to do it, of course. If you don't like these functions, go ahead and change them.</p>
<p>Let's see what's inside controls.cpp.</p>
<h1>The actual code</h1><br />
We'll need a few variables.</p>
<pre class="brush: cpp">// position<br />
glm::vec3 position = glm::vec3( 0, 0, 5 );<br />
// horizontal angle : toward -Z<br />
float horizontalAngle = 3.14f;<br />
// vertical angle : 0, look at the horizon<br />
float verticalAngle = 0.0f;<br />
// Initial Field of View<br />
float initialFoV = 45.0f;</p>
<p>float speed = 3.0f; // 3 units / second<br />
float mouseSpeed = 0.005f;</pre><br />
FoV is the level of zoom. 80&deg; = very wide angle, huge deformations. 60&deg; - 45&deg; : standard. 20&deg; : big zoom.</p>
<p>We will first recompute position, horizontalAngle, verticalAngle and FoV according to the inputs, and then compute the View and Projection matrices from position, horizontalAngle, verticalAngle and FoV.</p>
<h2>Orientation</h2><br />
Reading the mouse position is easy :</p>
<pre class="brush: cpp">// Get mouse position<br />
int xpos, ypos;<br />
glfwGetMousePos(&amp;xpos, &amp;ypos);</pre><br />
but we have to take care to put the cursor back to the center of the screen, or it will soon go outside the window and you won't be able to move anymore.</p>
<pre class="brush: cpp">// Reset mouse position for next frame<br />
glfwSetMousePos(1024/2, 768/2);</pre><br />
Notice that this code assumes that the window is 1024*768, which of course is not necessarily the case. You can use glfwGetWindowSize if you want, too.</p>
<p>We can now compute our viewing angles :</p>
<pre class="brush: cpp">// Compute new orientation<br />
horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );<br />
verticalAngle&nbsp;&nbsp; += mouseSpeed * deltaTime * float( 768/2 - ypos );</pre><br />
Let's read this from right to left :</p>
<ul>
<li>1024/2 - xpos means : how far is the mouse from the center of the window ? The bigger this value, the more we want to turn.</li>
<li>float(...) converts it to a floating-point number so that the multiplication goes well.</li>
<li>mouseSpeed is just there to speed up or slow down the rotations. Finetune this at will, or let the user choose it.</li>
<li>+= : If you didn't move the mouse, 1024/2-xpos will be 0, and horizontalAngle+=0 doesn't change horizontalAngle. If you had a "=" instead, you would be forced back to your original orientation each frame, which isn't good.</li><br />
</ul><br />
We can now compute a vector that represents, in World Space, the direction in which we're looking</p>
<pre class="brush: cpp">// Direction : Spherical coordinates to Cartesian coordinates conversion<br />
glm::vec3 direction(<br />
    cos(verticalAngle) * sin(horizontalAngle),<br />
    sin(verticalAngle),<br />
    cos(verticalAngle) * cos(horizontalAngle)<br />
);</pre><br />
This is a standard computation, but if you don't know about cosine and sinus, here's a short explanation :</p>
<p><img class="alignnone whiteborder" title="Trigonometric circle" src="http://www.numericana.com/answer/trig.gif" alt="" width="150" height="150" /></p>
<p>The formula above is just the generalisation to 3D.</p>
<p>Now we want to compute the "up" vector reliably. Notice that "up" isn't always towards +Y : if you look down, for instance, the "up" vector will be in fact horizontal. Here is an example of to cameras with the same position, the same target, but a different up.</p>
<p>In our case, the only constant is that the vector goes to the right of the camera is always horizontal. You can check this by putting your arm horizontal, and looking up, down, in any direction. So let's define the "right" vector : its Y coordinate is 0 since it's horizontal, and its X and Z coordinates are just like in the figure above, but with the angles rotated by 90&deg;, or Pi/2 radians.</p>
<pre class="brush: cpp">// Right vector<br />
glm::vec3 right = glm::vec3(<br />
    sin(horizontalAngle - 3.14f/2.0f),<br />
    0,<br />
    cos(horizontalAngle - 3.14f/2.0f)<br />
);</pre><br />
We have a "right" vector and a "direction", or "front" vector. The "up" vector is a vector that is perpendicular to these two. A useful mathematical tool makes this very easy : the cross product.</p>
<pre class="brush: cpp">// Up vector : perpendicular to both direction and right<br />
glm::vec3 up = glm::cross( right, direction );</pre><br />
To remember what the cross product does, it's very simple. Just recall the Right Hand Rule from Tutorial 3. The first vector is the thumb; the second is the index; and the result is the middle finger. It's very handy.</p>
<h2>Position</h2><br />
The code is pretty straightforward. By the way, I used the up/down/right/left keys instead of the awsd because on my azerty keyboard, awsd is actually zqsd. And it's also different with qwerZ keyboards, let alone korean keyboards. I don't even know what layout korean people have, but I guess it's also different.</p>
<pre class="brush: cpp">// Move forward<br />
if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){<br />
    position += direction * deltaTime * speed;<br />
}<br />
// Move backward<br />
if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){<br />
    position -= direction * deltaTime * speed;<br />
}<br />
// Strafe right<br />
if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){<br />
    position += right * deltaTime * speed;<br />
}<br />
// Strafe left<br />
if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){<br />
    position -= right * deltaTime * speed;<br />
}</pre><br />
The only special thing here is the deltaTime. You don't want to move from 1 unit each frame for a simple reason :</p>
<ul>
<li>If you have a fast computer, and you run at 60 fps, you'd move of 60*speed units in 1 second</li>
<li>If you have a slow computer, and you run at 20 fps, you'd move of 20*speed units in 1 second</li><br />
</ul><br />
Since having a better computer is not an excuse for going faster, you have to scale the distance by the "time since the last frame", or "deltaTime".</p>
<ul>
<li>If you have a fast computer, and you run at 60 fps, you'd move of 1/60 * speed units in 1 frame, so 1*speed in 1 second.</li>
<li>If you have a slow computer, and you run at 20 fps, you'd move of 1/20 * speed units in 1 second, so 1*speed in 1 second.</li><br />
</ul><br />
which is much better. deltaTime is very simple to compute :</p>
<pre class="brush: cpp">double currentTime = glfwGetTime();<br />
float deltaTime = float(currentTime - lastTime);</pre></p>
<h2>Field Of View</h2><br />
For fun, we can also bind the wheel of the mouse to the Field Of View, so that we can have a cheap zoom :</p>
<pre class="brush: cpp">float FoV = initialFoV - 5 * glfwGetMouseWheel();</pre></p>
<h2>Computing the matrices</h2><br />
Computing the matrices is now straightforward. We use the exact same functions than before, but with our new parameters.</p>
<pre class="brush: cpp">// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units<br />
ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);<br />
// Camera matrix<br />
ViewMatrix&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = glm::lookAt(<br />
    position,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // Camera is here<br />
    position+direction, // and looks here : at the same position, plus "direction"<br />
    up&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // Head is up (set to 0,-1,0 to look upside-down)<br />
);</pre></p>
<h1>Results</h1><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/moveanim.gif"><img class="alignnone size-full wp-image-372" title="moveanim" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/moveanim.gif" alt="" width="206" height="159" /></a></p>
<h2>Backface Culling</h2><br />
Now that you can freely move around, you'll notice that if you go inside the cube, polygons are still displayed. This can seem obvious, but this remark actually opens an opportunity for optimisation. As a matter of fact, in a usual application, you are never _inside_ a cube.</p>
<p>The idea is to let the GPU check if the camera is behind, or in front of, the triangle. If it's in front, display the triangle; if it's behind, *and* the mesh is closed, *and* we're not inside the mesh, *then* there will be another triangle in front of it, and nobody will notice anything, except that everything will be faster : 2 times less triangles on average !</p>
<p>The best thing is that it's very easy to check this. The GPU computes the normal of the triangle (using the cross product, remember ?) and checks whether this normal is oriented towards the camera or not.</p>
<p>This comes at a cost, unfortunately : the orientation of the triangle is implicit. This means that is you invert two vertices in your buffer, you'll probably end up with a hole. But it's generally worth the little additional work. Often, you just have to click "invert normals" in your 3D modeler (which will, in fact, invert vertices, and thus normals) and everything is just fine.</p>
<p>Enabling backface culling is a breeze :</p>
<pre class="brush: cpp">// Cull triangles which normal is not towards the camera<br />
glEnable(GL_CULL_FACE);</pre></p>
<h1>Exercices</h1></p>
<ul>
<li>Restrict verticalAngle so that you can't go upside-down</li>
<li>Create a camera that rotates around the object ( position = ObjectCenter + ( radius * cos(time), height, radius * sin(time) ) ); bind the radius/height/time to the keyboard/mouse, or whatever</li>
<li>Have fun !</li><br />
</ul><br />
&nbsp;</p>
