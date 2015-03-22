---
layout: page
status: publish
published: true
title: 'Tutorial 3 : Matrices'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 19
wordpress_url: http://www.dreamyourgame.com/wordpress/?page_id=19
date: '2011-04-09 20:59:15 +0200'
date_gmt: '2011-04-09 20:59:15 +0200'
categories: [tuto]
tags: []
---
<p>&nbsp;</p>
<blockquote><p><em>The engines don't move the ship at all. The ship stays where it is and the engines move the universe around it.</em><span id="content_parent" class="mceEditor wp_themeSkin"><img id="ft_1303837888870" class="foxytunes-signature-button" style="cursor: pointer; display: block; visibility: visible; position: absolute; z-index: 100; width: 30px; height: 20px; opacity: 1; padding: 0px; margin-bottom: 5px; margin-right: 7px; left: 1312px; top: 311px; border: 1px solid threedshadow threedhighlight threedhighlight threedshadow;" title="Insert current track Signatune" src="chrome://foxytunes-pbulic/content/signatures/signature-button-on-hover.png" alt="" /></span><br />
Futurama</blockquote><br />
<span style="color: #ff0000;">This is the single most important tutorial of the whole set. Be sure to read it at least eight times.</span></p>
<h1>Homogeneous coordinates</h1><br />
Until then, we only considered 3D vertices as a (x,y,z) triplet. Let's introduce w. We will now have (x,y,z,w) vectors.</p>
<p>This will be more clear soon, but for now, just remember this :</p>
<ul>
<li>If w == 1, then the vector (x,y,z,1) is a position in space.</li>
<li>If w == 0, then the vector (x,y,z,0) is a direction.</li><br />
</ul><br />
(In fact, remember this forever.)</p>
<p>What difference does this make ? Well, for a rotation, it doesn't change anything. When you rotate a point or a direction, you get the same result. However, for a translation (when you move the point in a certain direction), things are different. What could mean "translate a direction" ? Not much.</p>
<p>Homogeneous coordinates allow us to use a single mathematical formula to deal with these two cases.</p>
<h1>Transformation matrices</h1></p>
<h2>An introduction to matrices</h2><br />
Simply put, a matrix is an array of numbers with a predefined number of rows and colums. For instance, a 2x3 matrix can look like this :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/2X3.png"><img class="alignnone size-full wp-image-61 whiteborder" title="2X3" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/2X3.png" alt="" width="68" height="44" /></a></p>
<p>In 3D graphics we will only use 4x4 matrices. They will allow us to transform our (x,y,z,w) vertices. This is done by multiplying the vertex with the matrix :</p>
<p style="text-align: left;"><strong>Matrix x Vertex&nbsp; (in this order !!) = TransformedVertex</strong></p><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MatrixXVect.gif"><img class="alignnone size-medium wp-image-64 whiteborder" title="MatrixXVect" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MatrixXVect-300x71.gif" alt="" width="300" height="71" /></a></p>
<p>This isn't as scary as it looks. Put your left finger on the a, and your right finger on the x. This is <em>ax</em>. Move your left finger to the next number (b), and your right finger to the next number (y). You've got <em>by</em>. Once again : <em>cz</em>. Once again : <em>dw</em>. ax + by + cz + dw. You've got your new x ! Do the same for each line, and you'll get your new (x,y,z,w) vector.</p>
<p>Now this is quite boring to compute, an we will do this often, so let's ask the computer to do it instead.</p>
<p><strong>In C++, with GLM:</strong></p>
<pre class="brush: cpp">glm::mat4 myMatrix;<br />
glm::vec4 myVector;<br />
// fill myMatrix and myVector somehow<br />
glm::vec4 transformedVector = myMatrix * myVector; // Again, in this order ! this is important.</pre><br />
<strong>In GLSL :</strong></p>
<pre class="brush: vs">mat4 myMatrix;<br />
vec4 myVector;<br />
// fill myMatrix and myVector somehow<br />
vec4 transformedVector = myMatrix * myVector; // Yeah, it's pretty much the same than GLM</pre><br />
( have you cut'n pasted this in your code ? go on, try it)</p>
<h2>Translation matrices</h2><br />
These are the most simple tranformation matrices to understand. A translation matrix look like this :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationMatrix.png"><img class="alignnone size-full wp-image-60 whiteborder" title="translationMatrix" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationMatrix.png" alt="" width="103" height="88" /></a></p>
<p>where X,Y,Z are the values that you want to add to your position.</p>
<p>So if we want to translate the vector (10,10,10,1) of 10 units in the X direction, we get :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationExamplePosition1.png"><img class="alignnone  wp-image-798" title="translationExamplePosition" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationExamplePosition1.png" alt="" width="639" height="82" /></a></p>
<p>(do it ! doooooo it)</p>
<p>... and we get a (20,10,10,1) homogeneous vector ! Remember, the 1 means that it is a position, not a direction. So our transformation didn't change the fact that we were dealing with a position, which is good.</p>
<p>Let's now see what happens to a vector that represents a direction towards the -z axis : (0,0,-1,0)</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationExampleDirection1.png"><img class="alignnone size-full wp-image-799" title="translationExampleDirection" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationExampleDirection1.png" alt="" width="621" height="82" /></a></p>
<p>... ie our original (0,0,-1,0) direction, which is great because as I said ealier, moving a direction does not make sense.</p>
<p>So, how does this translate to code ?</p>
<p><strong>In C++, with GLM:</strong></p>
<pre class="brush: cpp">#include <glm/transform.hpp> // after <glm/glm.hpp></p>
<p>glm::mat4 myMatrix = glm::translate(10.0f, 0.0f, 0.0f);<br />
glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);<br />
glm::vec4 transformedVector = myMatrix * myVector; // guess the result</pre><br />
<strong>In GLSL : </strong>Well, in fact, you almost never do this. Most of the time, you use glm::translate() in C++ to compute your matrix, send it to GLSL, and do only the multiplication :</p>
<pre class="brush: cpp">vec4 transformedVector = myMatrix * myVector;</pre></p>
<h2>The Identity matrix</h2><br />
This one is special. It doesn't do anything. But I mention it because it's as important as knowing that multiplying A by 1.0 gives A.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/identityExample.png"><img class="alignnone size-full wp-image-99 whiteborder" title="identityExample" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/identityExample.png" alt="" width="742" height="80" /></a></p>
<p><strong>In C++ :</strong></p>
<pre class="brush: cpp">glm::mat4 myIdentityMatrix = glm::mat4(1.0f);</pre></p>
<h2>Scaling matrices</h2><br />
Scaling matrices are quite easy too :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/scalingMatrix.png"><img class="alignnone size-full wp-image-93 whiteborder" title="scalingMatrix" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/scalingMatrix.png" alt="" width="98" height="88" /></a></p>
<p>So if you want to scale a vector (position or direction, it doesn't matter) by 2.0 in all directions :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/scalingExample.png"><img class="alignnone size-full wp-image-98 whiteborder" title="scalingExample" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/scalingExample.png" alt="" width="799" height="80" /></a></p>
<p>&nbsp;</p>
<p>and the w still didn't change. You may ask : what is the meaning of "scaling a direction" ? Well, often, not much, so you usually don't do such a thing, but in some (rare) cases it can be handy.<br />
(notice that the identity matrix is only a special case of scaling matrices, with (X,Y,Z) = (1,1,1). It's also a special case of translation matrix with (X,Y,Z)=(0,0,0), by the way)</p>
<p><strong>In C++ :</strong></p>
<pre class="brush: cpp">// Use #include <glm/gtc/matrix_transform.hpp> and #include <glm/gtx/transform.hpp><br />
glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);</pre></p>
<h2>Rotation matrices</h2><br />
These are quite complicated. I'll skip the details here, as it's not important to know their exact layout for everyday use. For more information, please have a look to the <a href="http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html">Matrices and Quaternions FAQ</a> (popular resource, probably available in your language as well).</p>
<p><strong>In C++ :</strong></p>
<pre class="brush: cpp">// Use #include <glm/gtc/matrix_transform.hpp> and #include <glm/gtx/transform.hpp><br />
glm::vec3 myRotationAxis( ??, ??, ??);<br />
glm::rotate( angle_in_degrees, myRotationAxis );</pre></p>
<h2>Cumulating transformations</h2><br />
So now we know how to rotate, translate, and scale our vectors. It would be great to combine these transformations. This is done by multiplying the matrices together, for instance :</p>
<pre class="brush: cpp">TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;</pre><br />
!!! BEWARE !!! This lines actually performs the scaling FIRST, and THEN the rotation, and THEN the translation. This is how matrix multiplication works.</p>
<p>Writing the operations in another order wouldn't produce the same result. Try it yourself :<br />
- make one step ahead ( beware of your computer ) and turn left;<br />
- turn left, and make one step ahead</p>
<p>As a matter of fact, the order above is what you will usually need for game characters and other items : Scale it first if needed; then set its direction, then translate it. For instance, given a ship model (rotations have been removed for simplification) :</p>
<ul>
<ul>
<li>The wrong way :</li><br />
</ul><br />
</ul></p>
<p style="padding-left: 120px;">- You translate the ship by (10,0,0). Its center is now at 10 units of the origin.<br />
- You scale your ship by 2. Every coordinate is multiplied by 2 <em>relative to the origin</em>, which is far away... So you end up with a big ship, but centered at 2*10 = 20. Which you don't want.</p></p>
<ul>
<ul>
<li>The right way :</li><br />
</ul><br />
</ul></p>
<p style="padding-left: 120px;">- You scale your ship by 2. You get a big ship, centered on the origin.<br />
- You translate your ship. It's still the same size, and at the right distance.</p><br />
&nbsp;</p>
<p>Matrix-matrix multiplication is very similar to matrix-vector multiplication, so I'll once again skip some details and redirect you the the Matrices and Quaternions FAQ if needed. For now, we'll simply ask the computer to do it :</p>
<p><strong>in C++, with GLM :</strong></p>
<pre class="brush: cpp">glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;<br />
glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;</pre><br />
<strong>in GLSL :</strong></p>
<pre class="brush: vs">mat4 transform = mat2 * mat1;<br />
vec4 out_vec = transform * in_vec;</pre></p>
<h1>The Model, View and Projection matrices</h1><br />
<em>For the rest of this tutorial, we will suppose that we know how to draw Blender's favourite 3d model : the monkey Suzanne.</em></p>
<p>The Model, View and Projection matrices are a handy tool to separate transformations cleanly. You may not use this (after all, that's what we did in tutorials 1 and 2). But you should. This is the way everybody does, because it separates everything cleanly, as we'll see.</p>
<h2>The Model matrix</h2><br />
This model, just as our beloved red triangle, is defined by a set of vertices. The X,Y,Z coordinates of these vertices are defined relative to the object's center : that is, if a vertex is at (0,0,0), it is at the center of the object.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model.png"><img class="alignnone size-full wp-image-22" title="model" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model.png" alt="" width="960" height="540" /></a></p>
<p>&nbsp;</p>
<p>We'd like to be able to move this model, maybe because the player controls it with the keyboard and the mouse. Easy, you just learnt do do so : translation*rotation*scale, and done. You apply this matrix to all your vertices at each frame (in GLSL, not in C++!) and everything moves. Something that doesn't move will be at the _center of the world_.</p>
<p>&nbsp;</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/world.png"><img class="alignnone size-full wp-image-25" title="world" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/world.png" alt="" width="960" height="540" /></a></p>
<p>&nbsp;</p>
<p>Your vertices are now in <em>World Space</em>. This is the meaning of the black arrow in the image below : <em>We went from Model Space (all vertices defined relatively to the center of the model) to World Space (all vertices defined relatively to the center of the world).</em></p>
<p>&nbsp;</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model_to_world.png"><img class="alignnone size-full wp-image-23" title="model_to_world" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model_to_world.png" alt="" width="960" height="540" /></a></p>
<p>We can sum this up with the following diagram :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/M.png"><img class="alignnone size-full wp-image-63 whiteborder" title="M" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/M.png" alt="" width="240" height="148" /></a></p>
<p>&nbsp;</p>
<h2>The View matrix</h2><br />
Let's quote Futurama again :</p>
<blockquote><p><em>The engines don't move the ship at all. The ship stays where it is and the engines move the universe around it.</em></blockquote><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/camera.png"><img class="alignnone size-full wp-image-21" title="camera" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/camera.png" alt="" width="960" height="540" /></a></p>
<p>When you think about it, the same applies to cameras. It you want to view a moutain from another angle, you can either move the camera... or move the mountain. While not practical in real life, this is really simple and handy in Computer Graphics.</p>
<p>So initially your camera is at the origin of the World Space. In order to move the world, you simply introduce another matrix. Let's say you want to move your camera of 3 units to the right (+X). This is equivalent to moving your whole world (meshes included) 3 units to the LEFT ! (-X). While you brain melts, let's do it :</p>
<pre class="brush: cpp">// Use #include <glm/gtc/matrix_transform.hpp> and #include <glm/gtx/transform.hpp><br />
glm::mat4 ViewMatrix = glm::translate(-3.0f, 0.0f ,0.0f);</pre><br />
Again, the image below illustrates this : <em>We went from World Space (all vertices defined relatively to the center of the world, as we made so in the previous section) to Camera Space (all vertices defined relatively to the camera).</em></p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model_to_world_to_camera.png"><img class="alignnone size-full wp-image-24" title="model_to_world_to_camera" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model_to_world_to_camera.png" alt="" width="960" height="540" /></a></p>
<p>Before you head explodes from this, enjoy GLM's great glm::lookAt function:</p>
<pre class="brush: cpp">glm::mat4 CameraMatrix = glm::lookAt(<br />
    cameraPosition, // the position of your camera, in world space<br />
    cameraTarget,&nbsp;&nbsp; // where you want to look at, in world space<br />
    upVector&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too<br />
);</pre><br />
Here's the compulsory diagram :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MV.png"><img class="alignnone size-full wp-image-65 whiteborder" title="MV" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MV.png" alt="" width="240" height="265" /></a></p>
<p>&nbsp;</p>
<p>This is not over yet, though.</p>
<h2>The Projection matrix</h2><br />
We're now in Camera Space. This means that after all theses transformations, a vertex that happens to have x==0 and y==0 should be rendered at the center of the screen. But we can't use only the x and y coordinates to determine where an object should be put on the screen : its distance to the camera (z) counts, too ! For two vertices with similar x and y coordinates, the vertex with the biggest z coordinate will be more on the center of the screen than the other.</p>
<p>This is called a perspective projection :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model_to_world_to_camera_to_homogeneous.png"><img class="alignnone size-full wp-image-26" title="model_to_world_to_camera_to_homogeneous" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/model_to_world_to_camera_to_homogeneous.png" alt="" width="960" height="540" /></a></p>
<p>&nbsp;</p>
<p>And luckily for us, a 4x4 matrix can represent this projection&sup1; :</p>
<pre class="brush: cpp">// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless<br />
glm::mat4 projectionMatrix = glm::perspective(<br />
    FoV,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90&deg; (extra wide) and 30&deg; (quite zoomed in)<br />
    4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?<br />
    0.1f,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // Near clipping plane. Keep as big as possible, or you'll get precision issues.<br />
    100.0f&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // Far clipping plane. Keep as little as possible.<br />
);</pre><br />
One last time :</p>
<p><em>We went from Camera Space (all vertices defined relatively to the camera) to Homogeneous Space (all vertices defined in a small cube. Everything inside the cube is onscreen).</em></p>
<p>And the final diagram :</p>
<p>&nbsp;</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MVP.png"><img class="alignnone size-medium wp-image-66 whiteborder" title="MVP" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MVP-235x300.png" alt="" width="235" height="300" /></a></p>
<p>&nbsp;</p>
<p>Here's another diagram so that you understand better what happens with this Projection stuff. Before projection, we've got our blue objects, in Camera Space, and the red shape represents the frustum of the camera : the part of the scene that the camera is actually able to see.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nondeforme.png"><img class="alignnone size-full wp-image-67" title="nondeforme" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nondeforme.png" alt="" width="960" height="540" /></a></p>
<p>Multiplying everything by the Projection Matrix has the following effect :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/homogeneous.png"><img class="alignnone size-full wp-image-76" title="homogeneous" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/homogeneous.png" alt="" width="960" height="540" /></a></p>
<p>In this image, the frustum is now a perfect cube (between -1 and 1 on all axes, it's a little bit hard to see it), and all blue objects have been deformed in the same way. Thus, the objects that are near the camera ( = near the face of the cube that we can't see) are big, the others are smaller. Seems like real life !</p>
<p>Let's see what it looks like from the "behind" the frustum :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/projected1.png"><img class="alignnone size-full wp-image-368 whiteborder" title="projected" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/projected1.png" alt="" width="602" height="588" /></a></p>
<p>Here you get your image ! It's just a little bit too square, so another mathematical transformation is applied to fit this to the actual window size :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/final1.png"><img class="alignnone size-full wp-image-367 whiteborder" title="final" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/final1.png" alt="" width="640" height="462" /></a></p>
<p>And this is the image that is actually rendered !</p>
<h2>Cumulating transformations : the ModelViewProjection matrix</h2><br />
... Just a standard matrix multiplication as you already love them !</p>
<pre class="brush: cpp">// C++ : compute the matrix<br />
glm::mat4 MVPmatrix = projection * view * model; // Remember : inverted !</pre></p>
<pre class="brush: vs">// GLSL : apply it<br />
transformed_vertex = MVP * in_vertex;</pre></p>
<h1>Putting it all together</h1></p>
<ul>
<li>First step : generating our MVP matrix. This must be done for each model you render.</li><br />
</ul></p>
<pre class="brush: cpp">// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units<br />
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);<br />
// Camera matrix<br />
glm::mat4 View&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = glm::lookAt(<br />
    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space<br />
    glm::vec3(0,0,0), // and looks at the origin<br />
    glm::vec3(0,1,0)&nbsp; // Head is up (set to 0,-1,0 to look upside-down)<br />
);<br />
// Model matrix : an identity matrix (model will be at the origin)<br />
glm::mat4 Model&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = glm::mat4(1.0f);&nbsp; // Changes for each model !<br />
// Our ModelViewProjection : multiplication of our 3 matrices<br />
glm::mat4 MVP&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = Projection * View * Model; // Remember, matrix multiplication is the other way around</pre></p>
<ul>
<li>Second step : give it to GLSL</li><br />
</ul></p>
<pre class="brush: cpp">// Get a handle for our "MVP" uniform.<br />
// Only at initialisation time.<br />
GLuint MatrixID = glGetUniformLocation(programID, "MVP");</p>
<p>// Send our transformation to the currently bound shader,<br />
// in the "MVP" uniform<br />
// For each model you render, since the MVP will be different (at least the M part)<br />
glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &amp;MVP[0][0]);</pre></p>
<ul>
<li>Third step : use it in GLSL to transform our vertices</li><br />
</ul></p>
<pre class="brush: vs">in vec3 vertexPosition_modelspace;<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>    // Output position of the vertex, in clip space : MVP * position<br />
    vec4 v = vec4(vertexPosition_modelspace,1); // Transform an homogeneous 4D vector, remember ?<br />
    gl_Position = MVP * v;<br />
}</pre></p>
<ul>
<li>Done ! Here is the same triangle as in tutorial 2, still at the origin (0,0,0), but viewed in perspective from point (4,3,3), heads up (0,1,0), with a 45&deg; field of view.</li><br />
</ul><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/perspective_red_triangle.png"><img class="alignnone size-medium wp-image-20" title="perspective_red_triangle" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/perspective_red_triangle-300x231.png" alt="" width="300" height="231" /></a></p>
<p>In tutorial 6 you'll learn how to modify these values dynamically using the keyboard and the mouse to create a game-like camera, but first, we'll learn how to give our 3D models some colour (tutorial 4) and textures (tutorial 5).</p>
<h1>Exercises</h1></p>
<ul>
<li>Try changing the glm::perspective</li>
<li>Instead of using a perspective projection, use an orthographic projection (glm::ortho)</li>
<li>Modify ModelMatrix to translate, rotate, then scale the triangle</li>
<li>Do the same thing, but in different orders. What do you notice ? What is the "best" order that you would want to use for a character ?</li><br />
</ul></p>
<address>Addendum</address><br />
<address>&nbsp;</address><br />
<address>&nbsp;</address><br />
<address>1 : [...]luckily for us, a 4x4 matrix can represent this projection&sup1; : Actually, this is not correct. A perspective transformation is not affine, and as such, can't be represented entirely by a matrix. After beeing multiplied by the ProjectionMatrix, homogeneous coordinates are divided by their own W component. This W component happens to be -Z (because the projection matrix has been crafted this way). This way, points that are far away from the origin are divided by a big Z; their X and Y coordinates become smaller; points become more close to each other, objects seem smaller; and this is what gives the perspective.</address></p>
