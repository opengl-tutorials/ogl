---
layout: page
status: publish
published: true
title: Billboards
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 933
wordpress_url: http://www.opengl-tutorial.org/?page_id=933
date: '2013-10-15 17:15:15 +0200'
date_gmt: '2013-10-15 17:15:15 +0200'
categories: []
tags: []
---
<p>Billboards are 2D elements incrusted in a 3D world. Not a 2D menu on top of everything else; not a 3D plane around which you can turn; but something in-between, like health bars in many games.</p>
<p>What's different with billboards is that they are positionned at a specific location, but their orientation is automatically computed so that it always faces the camera.</p>
<p>&nbsp;</p>
<h1>Solution #1 : The 2D way</h1><br />
This one is supra-easy.</p>
<p>Just compute where your point is on screen, and display a 2D text (see Tutorial 11) at this position.</p>
<pre class="brush: cpp">// Everything here is explained in Tutorial 3 ! There's nothing new.<br />
glm::vec4 BillboardPos_worldspace(x,y,z, 1.0f);<br />
glm::vec4 BillboardPos_screenspace = ProjectionMatrix * ViewMatrix * BillboardPos_worldspace;<br />
BillboardPos_screenspace /= BillboardPos_screenspace.w;</p>
<p>if (BillboardPos_screenspace.z < 0.0f){<br />
    // Object is behind the camera, don't display it.<br />
}</pre><br />
Ta-dah !</p>
<p>On the plus side, this method is really easy, and the billboard will have the same size regardless of its distance to the camera. But 2D text is always displayed on top of everything else, and this can/will mess up the rendering and show above other objects.</p>
<p>&nbsp;</p>
<h1>Solution #2 : The 3D way</h1><br />
This one is usually better and not much more complicated.</p>
<p>The goal is to keep the mesh aligned with the camera, even when the camera moves :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/2a.gif"><img class="alignnone size-full wp-image-944" title="2a" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/2a.gif" alt="" width="400" height="300" /></a></p>
<p>You can view this problem as generating an appropriate Model matrix, even though it's is much simpler than that.</p>
<p>The idea is that each corner of the billboard is at the center position, displaced by the camera's up and right vectors :</p>
<p>&nbsp;</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/principle.png"><img class="alignnone size-full wp-image-946 whiteborder" title="principle" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/principle.png" alt="" width="555" height="572" /></a></p>
<p>&nbsp;</p>
<p>Of course, we only know the billboard's center position in world space, so we also need the camera's up/right vectors in world space.</p>
<p>In camera space, the camera's up vector is (0,1,0). To get it in world space, just multiply this by the matrix that goes from Camera Space to World Space, which is, of course, the inverse of the View matrix.</p>
<p>An easier way to express the same math is :</p>
<pre>CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}<br />
CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}</pre><br />
&nbsp;</p>
<p>Once we have this, it's very easy to compute the final vertex' position :</p>
<pre class="brush: vs">vec3 vertexPosition_worldspace =<br />
&nbsp; &nbsp; particleCenter_wordspace<br />
&nbsp; &nbsp; + CameraRight_worldspace * squareVertices.x * BillboardSize.x<br />
&nbsp; &nbsp; + CameraUp_worldspace * squareVertices.y * BillboardSize.y;</pre></p>
<ul>
<li>particleCenter_worldspace is, as its name suggests, the billboard's center position. It is specified with an uniform vec3.</li>
<li>squareVertices is the original mesh. squareVertices.x is -0.5 for the left vertices, which are thus moved towars the left of the camera (because of the *CameraRight_worldspace)</li>
<li>BillboardSize is the size, in world units, of the billboard, sent as another uniform.</li><br />
</ul></p>
<div><span style="font-size: medium;"><span style="line-height: 24px;">And presto, here's the result. Wasn't this easy ?&nbsp;</span></span><span style="font-size: 16px;">&nbsp;</span></div><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/2.gif"><img class="alignnone size-full wp-image-942" title="2" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/2.gif" alt="" width="400" height="300" /></a></p>
<p>&nbsp;</p>
<p>For the record, here's how squareVertices is made :</p>
<pre class="brush: cpp">// The VBO containing the 4 vertices of the particles.<br />
 static const GLfloat g_vertex_buffer_data[] = {<br />
 -0.5f, -0.5f, 0.0f,<br />
 0.5f, -0.5f, 0.0f,<br />
 -0.5f, 0.5f, 0.0f,<br />
 0.5f, 0.5f, 0.0f,<br />
 };</pre><br />
&nbsp;</p>
<h1>Solution #3 : The fixed-size 3D way</h1><br />
As you can see above, the size of the billboard changes with respect to the camera's distance. This is the expected result in some cases, but in others, such as health bars, you probably want a fixed-size instead.</p>
<p>Since the displacement between the center and a corner must be fixed in screen-space, that's exactly what we're going to do : compute the center's position in screen space, and offset it.</p>
<pre class="brush: cpp">vertexPosition_worldspace = particleCenter_wordspace;<br />
// Get the screen-space position of the particle's center<br />
gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);<br />
// Here we have to do the perspective division ourselves.<br />
gl_Position /= gl_Position.w;</p>
<p>// Move the vertex in directly screen space. No need for CameraUp/Right_worlspace here.<br />
gl_Position.xy += squareVertices.xy * vec2(0.2, 0.05);</pre><br />
Remember that at this stage of the rendering pipeline, you're in Normalized Device Coordinates, so between -1 and 1 on both axes : it's not in pixels.</p>
<p>If you want a size in pixels, easy : just&nbsp;use (ScreenSizeInPixels / BillboardSizeInPixels) instead of BillboardSizeInScreenPercentage.</p>
<p>&nbsp;</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/3.gif"><img class="alignnone size-full wp-image-943" title="3" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/09/3.gif" alt="" width="400" height="300" /></a></p>
<p>&nbsp;</p>
<h1>Solution #4 : Vertical rotation only</h1><br />
Some systems model faraway trees and lamps as billboards. But you really, really don't want your tree to be bent : it MUST be vertical. So you need an hybrid system that rotates only around one axis.</p>
<p>Well, this one is left as an exercise to the reader !</p>
<p>&nbsp;</p>
<p>&nbsp;</p>
