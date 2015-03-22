---
layout: page
status: publish
published: true
title: 'Tutorial 10 : Transparency'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 281
wordpress_url: http://www.opengl-tutorial.org/?page_id=281
date: '2011-05-13 23:00:42 +0200'
date_gmt: '2011-05-13 23:00:42 +0200'
categories: []
tags: []
---
<h1>The alpha channel</h1><br />
The concept of the alpha channel is pretty simple. Instead of a writing an RGB result, you write an RGBA :</p>
<pre class="brush:fs">// Ouput data : it's now a vec4<br />
out vec4 color;</pre><br />
the first 3 components are still accessed with the .xyz swizzle operator, while the last one is accessed with .a :</p>
<pre class="brush:fs">color.a = 0.3;</pre><br />
Unintuitively, alpha = opaqueness, so alpha = 1 means fully opaque while alpha = 0 means fully transparent.</p>
<p>Here, we simply hardcode the alpha channel at 0.3, but you probably want to use a uniform, or read it from a RGBA texture ( TGA supports the alpha channel, and GLFW supports TGA )</p>
<p>Here's the result. Make sure to turn backface culling off (glDisable(GL_CULL_FACE) ) because since we can look through the mesh, we could see that it has no "back" face.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transparencyok.png"><img class="alignnone size-large wp-image-289" title="transparencyok" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transparencyok-1024x793.png" alt="" width="640" height="495" /></a></p>
<h1>Order matters !</h1><br />
The previous screenshot looks okay-ish, but that's just because we're lucky.</p>
<h2>The problem</h2><br />
Here, I drew two squares with 50% alpha, one green and one red. You can see that order is important, the final colour gives an important clue to the eyes for proper depth perception.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transparencyorder.png"><img class="alignnone size-full wp-image-282" title="transparencyorder" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transparencyorder.png" alt="" width="500" height="255" /></a></p>
<p>This phenomena also happens in our scene. Let's change the viewpoint a bit :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transparencybad.png"><img class="alignnone size-large wp-image-288" title="transparencybad" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transparencybad-1024x793.png" alt="" width="640" height="495" /></a></p>
<p>It turns out that this is a very hard problem. You never see lots of transparency in games, do you ?</p>
<h2>Usual solution</h2><br />
The usual solution is to sort all transparent triangles. Yes, ALL transparent triangles.</p>
<ul>
<li>Draw the opaque part of the world so that the depth buffer already can reject hidden transparent triangles</li>
<li>Sort transparent triangles, from the furthest to the closest</li>
<li>Draw the transparent triangles.</li><br />
</ul><br />
You can sort whatever you want with qsort (in C) or std::sort (in C++). I won't dig in the details, because...</p>
<h2>Caveat</h2><br />
Doing so will work ( more on this in the next section ), but :</p>
<ul>
<li>You will be fillrate limited. That is, each fragment will be written 10, 20 times, maybe more. This is way too much for the poor memory bus. Usually the depth buffer allows to reject enough "far" fragments, but here, you explicitly sorted them, so the depth buffer is actually useless.</li>
<li>You will be doing this 4 times per pixel ( we use 4xMSAA ), except if you use some clever optimisation</li>
<li>Sorting all the transparent triangles takes time</li>
<li>If you have to switch your texture, or worse, your shader, from triangle to triangle, you're going into deep performance trouble. Don't do this.</li><br />
</ul><br />
A good enough solution is often to :</p>
<ul>
<li>Limit to a maximum the number of transparent polygons</li>
<li>Use the same shader and the same texture for all of them</li>
<li>If they are supposed to look very different, use your texture !</li>
<li>If you can avoid sorting, and it still doesn't look <em>too </em>bad, consider yourself lucky.</li><br />
</ul></p>
<h2>Order-Independent Transparency</h2><br />
A number of other techniques are worth investigating if your engine really, really needs state-of-the-art transparency :</p>
<ul>
<li><a href="http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.9286&amp;rep=rep1&amp;type=pdf">The original 2001 Depth Peeling paper</a>: pixel-perfect results, not very fast.</li>
<li><a href="http://developer.download.nvidia.com/SDK/10/opengl/src/dual_depth_peeling/doc/DualDepthPeeling.pdf">Dual Depth Peeling</a> : a slight improvement</li>
<li>Several papers on bucket sort. Uses an array of fragments; sort them by depth in a shader.</li>
<li><a href="http://fr.slideshare.net/hgruen/oit-and-indirect-illumination-using-dx11-linked-lists">ATI's Mecha Demo</a> : good and fast, but tricky to implement, needs recent hardware. Uses a linked list of fragments.</li>
<li><a href="http://blog.icare3d.org/2010/07/opengl-40-abuffer-v20-linked-lists-of.html">Cyril Crassin's variation on the ATI's&nbsp; technique</a> : even harder implementation</li><br />
</ul><br />
Note that even a recent game like Little Big Planet, which ran on a powerful console, used only 1 layer of transparency.</p>
<h1>The blend function</h1><br />
In order for the previous code to work, you need to setup your blend function.</p>
<pre class="brush:cpp">// Enable blending<br />
glEnable(GL_BLEND);<br />
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);</pre><br />
Which means :</p>
<pre class="brush:plain">New color in framebuffer =<br />
           current alpha in framebuffer * current color in framebuffer +<br />
           (1 - current alpha in framebuffer) * shader's output color</pre><br />
Example from the image above, with red on top :</p>
<pre class="brush:plain">new color = 0.5*(0,1,0) + (1-0.5)*(1,0.5,0.5); // (the red was already blended with the white background)<br />
new color = (1, 0.75, 0.25) = the same orange</pre><br />
&nbsp;</p>
<p>&nbsp;</p>
