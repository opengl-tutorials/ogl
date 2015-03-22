---
layout: page
status: publish
published: true
title: Picking with an OpenGL hack
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 878
wordpress_url: http://www.opengl-tutorial.org/?page_id=878
date: '2013-05-18 20:43:28 +0200'
date_gmt: '2013-05-18 20:43:28 +0200'
categories: []
tags: []
---
<p>This technique is not really recommended, but it's an easy and fast way to add simple picking. By all means, avoid using this in a game, since it might introduce noticeable framerate drops. However, if you have some kind of simulation and you don't really care about picking performance, this might the perfect option.</p>
<p>Source code for this tutorial is available in <em>misc05_picking/misc05_picking_slow_easy.cpp</em>, which is a quite meaningful name.</p>
<p>Basic idea</p>
<p>The idea behind this technique is to render the scene as usual, but instead of using a nice shading, you render each mesh with a specific and unique color.</p>
<p>Then, you retrieve the colour of the pixel under the mouse cursor and convert this color back to the original identifier. You have your clicked object.</p>
<p>Here's an example :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/UniqueColors.png"><img class="alignnone size-full wp-image-879" title="UniqueColors" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/UniqueColors.png" alt="" width="1040" height="806" /></a></p>
<p>In this screenshot, each monkey has a slightly different color, which make is possible to uniquely identify them.</p>
<p>Of course, you don't want to see the image with all these weird colors, so you also have to clear the screen and re-draw as usual.</p>
<h1>Implementation</h1></p>
<h2>Giving an ID to every object</h2><br />
Each object of the scene will need a unique color. The easiest way to do this is to give each object an identifying integer, and convert it to a color. This color doesn't have to have a meaning; this technique is just a hack anyway.</p>
<p>In the accompanying source code, 100 objects are created and stored in a std::vector, so the ID is just the index of the object in the vector. If you have a more complex hierarchy, you'll probably need to add the ID to your Mesh class, and maintain some sort of std::map to associate the ID with the desired object.</p>
<p>&nbsp;</p>
<h2>Detecting the click</h2><br />
In this simple example, the picking is done each frame where the left mouse button is down :</p>
<pre class="brush: cpp">		if&nbsp;(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)){</pre><br />
In a real application, you probably want to do this only when the user just released the button, so you'll have to store a bool wasLeftMouseButtonPressedLastFrame; or, better, use <em>glfwSetMouseButtonCallback()</em> (read GLFW's manual to know how to use this).</p>
<h2>Convert your ID into a special color</h2><br />
Since we're going to render each mesh with a different color, the first step is to compute this color. An easy way to do this is to put the least signifying bits in the red channels, and the most significant bits in the blue channel :</p>
<pre class="brush: cpp">//&nbsp;Convert&nbsp;"i",&nbsp;the&nbsp;integer&nbsp;mesh&nbsp;ID,&nbsp;into&nbsp;an&nbsp;RGB&nbsp;color<br />
int&nbsp;r&nbsp;=&nbsp;(i&nbsp;&amp;&nbsp;0x000000FF)&nbsp;>>&nbsp;&nbsp;0;<br />
int&nbsp;g&nbsp;=&nbsp;(i&nbsp;&amp;&nbsp;0x0000FF00)&nbsp;>>&nbsp;&nbsp;8;<br />
int&nbsp;b&nbsp;=&nbsp;(i&nbsp;&amp;&nbsp;0x00FF0000)&nbsp;>>&nbsp;16;</pre><br />
This might seem scary, but it's standard bit-manipulation code. You end up with 3 integers, each in the [0-255] range. With this scheme, you can represent 255^3 = 16 million different meshes, which is probably enough.</p>
<h2>Drawing the scene with this color</h2><br />
We now need a shader to use this color. It's very simple. The vertex shader does nothing :</p>
<pre class="brush: vs">#version 330 core</p>
<p>// Input vertex data, different for all executions of this shader.<br />
layout(location = 0) in vec3 vertexPosition_modelspace;</p>
<p>// Values that stay constant for the whole mesh.<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>&nbsp;&nbsp; &nbsp;// Output position of the vertex, in clip space : MVP * position<br />
&nbsp;&nbsp; &nbsp;gl_Position =&nbsp; MVP * vec4(vertexPosition_modelspace,1);</p>
<p>}</pre><br />
and the fragment shader simply writes the desired color in the framebuffer :</p>
<pre class="brush: fs">#version 330 core</p>
<p>// Ouput data<br />
out vec4 color;</p>
<p>// Values that stay constant for the whole mesh.<br />
uniform vec4 PickingColor;</p>
<p>void main(){</p>
<p>&nbsp;&nbsp; &nbsp;color = PickingColor;</p>
<p>}</pre><br />
&nbsp;</p>
<p>Easy !</p>
<p>The only trick is that you have to send your color as floats (in [0,1]) but you have integers (in [0,255]), so you have to make a small division when calling <em>glUniformXX()</em> :</p>
<pre class="brush: cpp">//&nbsp;OpenGL&nbsp;expects&nbsp;colors&nbsp;to&nbsp;be&nbsp;in&nbsp;[0,1],&nbsp;so&nbsp;divide&nbsp;by&nbsp;255.<br />
glUniform4f(pickingColorID,&nbsp;r/255.0f,&nbsp;g/255.0f,&nbsp;b/255.0f,&nbsp;1.0f);</pre><br />
You can now draw the meshes as usual (<em>glBindBuffer, glVertexAttribPointer, glDrawElements</em>) and you'll get the weird picture above.</p>
<p>&nbsp;</p>
<h2>Get the color under the mouse</h2><br />
When you have drawn all meshes (probably with a for() loop), you need to call <em>glReadPixels()</em>, which will retrieve the rasterized pixels on the CPU. But for this function to work, a few more calls are needed.</p>
<p>First, you need to call <em>glFlush()</em>. This will tell the OpenGL driver to send all the pending commands (including your latest <em>glDrawXX</em>) to the GPU. This is typically not done automatically, because commands are sent in batches, and not immediately (this means that when you call <em>glDrawElements()</em>, nothing is actually draw. It WILL be drawn a few milliseconds later). This operation is SLOW.</p>
<p>Then, you need to call <em>glFinish()</em>, which will wait until everything is really drawn. The difference with <em>glFlush()</em> is that <em>glFlush()</em> just sends the commands; <em>glFinish()</em> waits for these commands to be executed. This operation is SLOOOW.</p>
<p>You also need to configure how <em>glReadPixels</em> will behave with respect to memory alignment. This is a bit off-topic, but you simply need to call <em>glPixelStorei(GL_UNPACK_ALIGNMENT, 1)</em>.</p>
<p>And finally, you can call <em>glReadPixels</em> ! Here is the full code :</p>
<pre class="brush: cpp">//&nbsp;Wait&nbsp;until&nbsp;all&nbsp;the&nbsp;pending&nbsp;drawing&nbsp;commands&nbsp;are&nbsp;really&nbsp;done.<br />
//&nbsp;Ultra-mega-over&nbsp;slow&nbsp;!&nbsp;<br />
//&nbsp;There&nbsp;are&nbsp;usually&nbsp;a&nbsp;long&nbsp;time&nbsp;between&nbsp;glDrawElements()&nbsp;and<br />
//&nbsp;all&nbsp;the&nbsp;fragments&nbsp;completely&nbsp;rasterized.<br />
glFlush();<br />
glFinish();&nbsp;</p>
<p>glPixelStorei(GL_UNPACK_ALIGNMENT,&nbsp;1);</p>
<p>//&nbsp;Read&nbsp;the&nbsp;pixel&nbsp;at&nbsp;the&nbsp;center&nbsp;of&nbsp;the&nbsp;screen.<br />
//&nbsp;You&nbsp;can&nbsp;also&nbsp;use&nbsp;glfwGetMousePos().<br />
//&nbsp;Ultra-mega-over&nbsp;slow&nbsp;too,&nbsp;even&nbsp;for&nbsp;1&nbsp;pixel,&nbsp;<br />
//&nbsp;because&nbsp;the&nbsp;framebuffer&nbsp;is&nbsp;on&nbsp;the&nbsp;GPU.<br />
unsigned&nbsp;char&nbsp;data[4];<br />
glReadPixels(1024/2,&nbsp;768/2,1,1,&nbsp;GL_RGBA,&nbsp;GL_UNSIGNED_BYTE,&nbsp;data);</pre><br />
Your color is now in the 'data' array. Here, you can see that the ID is 19.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/DataArray.png"><img class="alignnone size-full wp-image-880" title="DataArray" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/05/DataArray.png" alt="" width="684" height="121" /></a></p>
<h2>Convert the color back to an ID</h2><br />
You can now reconstruct your ID from the 'data' buffer. The code is the complete opposite from the id-to-color code :</p>
<pre class="brush: cpp">//&nbsp;Convert&nbsp;the&nbsp;color&nbsp;back&nbsp;to&nbsp;an&nbsp;integer&nbsp;ID<br />
int&nbsp;pickedID&nbsp;=&nbsp;<br />
	data[0]&nbsp;+&nbsp;<br />
	data[1]&nbsp;*&nbsp;256&nbsp;+<br />
	data[2]&nbsp;*&nbsp;256*256;</pre></p>
<h2>Use this ID</h2><br />
You can now use this ID for whatever you need. In the example, the text in the GUI is updated, but of course, you can do whatever you want.</p>
<pre class="brush: cpp">if&nbsp;(pickedID&nbsp;==&nbsp;0x00ffffff){&nbsp;//&nbsp;Full&nbsp;white,&nbsp;must&nbsp;be&nbsp;the&nbsp;background&nbsp;!<br />
	message&nbsp;=&nbsp;"background";<br />
}else{<br />
	std::ostringstream&nbsp;oss; // C++ strings suck<br />
	oss&nbsp;<<&nbsp;"mesh&nbsp;"&nbsp;<<&nbsp;pickedID;<br />
	message&nbsp;=&nbsp;oss.str();<br />
}</pre><br />
&nbsp;</p>
<h1>Pros and cons</h1><br />
Pros :</p>
<ul>
<li>Easy, fast to implement</li>
<li>No need for external library, or complicated math</li><br />
</ul><br />
Cons :</p>
<ul>
<li>Use glFlush(), glFinish(), glReadPixels(), all of which are notoriously slow, because they force the CPU to wait for the GPU, which ruins performance.</li>
<li>You don't have more precise information : which exact triangle was hit, normal at this point, etc.</li><br />
</ul><br />
&nbsp;</p>
<h1>Final remarks</h1><br />
While not very recommended, this technique can be really useful; but it's quite restricted to picking. The methods in the two other tutorials can be used for other purposes, like detecting collisions, making an avatar walk on the ground, visibility queries for AIs, etc.</p>
<p>If you end up using this technique, and you need to pick several points in a single frame, you should do all these points at once. For instance, if you need to handle 5 touch inputs, don't draw the scene 5 times !</p>
<p>&nbsp;</p>
