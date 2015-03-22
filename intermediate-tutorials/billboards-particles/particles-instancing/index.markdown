---
layout: page
status: publish
published: true
title: Particles / Instancing
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 951
wordpress_url: http://www.opengl-tutorial.org/?page_id=951
date: '2013-10-19 10:52:04 +0200'
date_gmt: '2013-10-19 10:52:04 +0200'
categories: []
tags: []
---
<p>Particles are very similar to 3D billboards. There are two major differences, though :</p>
<ul>
<li>there is usually a LOT of them</li>
<li>they move</li>
<li>the appear and die.</li>
<li>they are semi-transparent</li><br />
</ul><br />
Both of these difference come with problems. This tutorial will present ONE way to solve them; there are many other possibilities.</p>
<h1>Particles, lots of them !</h1><br />
The first idea to draw many particles would be to use the previous tutorial's code, and call glDrawArrays once for each particle. This is a very bad idea, because this means that all your shiny GTX' 512+ multiprocessors will all be dedicated to draw ONE quad (obviously, only one will be used, so that's 99% efficiency loss). Then you will draw the second billboard, and it will be the same.</p>
<p>Clearly, we need a way to draw all particles at the same time.</p>
<p>There are many ways to do this; here are three of them :</p>
<ul>
<li>Generate a single VBO with all the particles in them. Easy, effective, works on all platforms.</li>
<li>Use geometry shaders. Not in the scope of this tutorial, mostly because 50% of the computers don't support this.</li>
<li>Use instancing. Not available on ALL computers, but a vast majority of them.</li><br />
</ul><br />
In this tutorial, we'll use the 3rd option, because it is a nice balance between performance and availability, and on top of that, it's easy to add support for the first method once this one works.</p>
<h2>Instancing</h2><br />
"Instancing" means that we have a base mesh (in our case, a simple quad of 2 triangles), but many instances of this quad.</p>
<p>Technically, it's done via several buffers :</p>
<ul>
<li>Some of them describe the base mesh</li>
<li>Some of them describe the particularities of each instance of the base mesh.</li><br />
</ul><br />
You have many, many options on what to put in each buffer. In our simple case, we have :</p>
<ul>
<li>One buffer for the vertices of the mesh. No index buffer, so it's 6 vec3, which make 2 triangles, which make 1 quad.</li>
<li>One buffer for the particles' centers.</li>
<li>One buffer for the particles' colors.</li><br />
</ul><br />
These are very standard buffers. They are created this way :</p>
<pre class="brush:cpp">// The VBO containing the 4 vertices of the particles.<br />
// Thanks to instancing, they will be shared by all particles.<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
 -0.5f, -0.5f, 0.0f,<br />
 0.5f, -0.5f, 0.0f,<br />
 -0.5f, 0.5f, 0.0f,<br />
 0.5f, 0.5f, 0.0f,<br />
};<br />
GLuint billboard_vertex_buffer;<br />
glGenBuffers(1, &amp;billboard_vertex_buffer);<br />
glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);</p>
<p>// The VBO containing the positions and sizes of the particles<br />
GLuint particles_position_buffer;<br />
glGenBuffers(1, &amp;particles_position_buffer);<br />
glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);<br />
// Initialize with empty (NULL) buffer : it will be updated later, each frame.<br />
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);</p>
<p>// The VBO containing the colors of the particles<br />
GLuint particles_color_buffer;<br />
glGenBuffers(1, &amp;particles_color_buffer);<br />
glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);<br />
// Initialize with empty (NULL) buffer : it will be updated later, each frame.<br />
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);</pre><br />
&nbsp;</p>
<p>, which is as usual.&nbsp;They are updated this way :</p>
<p>&nbsp;</p>
<pre class="brush:cpp">// Update the buffers that OpenGL uses for rendering.<br />
// There are much more sophisticated means to stream data from the CPU to the GPU,<br />
// but this is outside the scope of this tutorial.<br />
// http://www.opengl.org/wiki/Buffer_Object_Streaming</p>
<p>glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);<br />
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.<br />
glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);</p>
<p>glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);<br />
glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.<br />
glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);</pre><br />
&nbsp;</p>
<p>, which is as usual.&nbsp;Before render, they are bound this way :</p>
<p>&nbsp;</p>
<pre class="brush:cpp">// 1rst attribute buffer : vertices<br />
glEnableVertexAttribArray(0);<br />
glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);<br />
glVertexAttribPointer(<br />
 0, // attribute. No particular reason for 0, but must match the layout in the shader.<br />
 3, // size<br />
 GL_FLOAT, // type<br />
 GL_FALSE, // normalized?<br />
 0, // stride<br />
 (void*)0 // array buffer offset<br />
);</p>
<p>// 2nd attribute buffer : positions of particles' centers<br />
glEnableVertexAttribArray(1);<br />
glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);<br />
glVertexAttribPointer(<br />
 1, // attribute. No particular reason for 1, but must match the layout in the shader.<br />
 4, // size : x + y + z + size => 4<br />
 GL_FLOAT, // type<br />
 GL_FALSE, // normalized?<br />
 0, // stride<br />
 (void*)0 // array buffer offset<br />
);</p>
<p>// 3rd attribute buffer : particles' colors<br />
glEnableVertexAttribArray(2);<br />
glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);<br />
glVertexAttribPointer(<br />
 2, // attribute. No particular reason for 1, but must match the layout in the shader.<br />
 4, // size : r + g + b + a => 4<br />
 GL_UNSIGNED_BYTE, // type<br />
 GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***<br />
 0, // stride<br />
 (void*)0 // array buffer offset<br />
);</pre><br />
, which is as usual. The difference comes when rendering. Instead of using glDrawArrays (or glDrawElements if your base mesh has an index buffer), you use glDrawArrraysInstanced / glDrawElementsInstanced, which is equivalent to calling glDrawArrays N times (N is the last parameter, in our case ParticlesCount) :</p>
<pre class="brush:cpp">glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);</pre><br />
Bue something is missing here. We didn't tell OpenGL which buffer was for the base mesh, and which were for the different instances. This is done with&nbsp;glVertexAttribDivisor. Here's the full commented code :</p>
<pre class="brush:cpp">// These functions are specific to glDrawArrays*Instanced*.<br />
// The first parameter is the attribute buffer we're talking about.<br />
// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"<br />
// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml<br />
glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0<br />
glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1<br />
glVertexAttribDivisor(2, 1); // color : one per quad -> 1</p>
<p>// Draw the particules !<br />
// This draws many times a small triangle_strip (which looks like a quad).<br />
// This is equivalent to :<br />
// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),<br />
// but faster.<br />
glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);</pre><br />
As you can see, instancing is very versatile, because you can pass any integer as the AttribDivisor. For instance, with glVertexAttribDivisor(2, 10), each 10 subsequent instances will have the same color.</p>
<h2>What's the point ?</h2><br />
The point is that now, we only have to update a small buffer each frame (the center of the particles) and not a huge mesh. This is a x4 bandwidth gain !</p>
<p>&nbsp;</p>
<h1>Life and death</h1><br />
On the contrary to most other objects in the scene, particles die and born at a very high rate. We need a decently fast way to get new particles and to discard them, something better than "new Particle()".</p>
<h2>Creating new particles</h2><br />
For this, we will have a big particles container :</p>
<pre class="brush:cpp">// CPU representation of a particle<br />
struct Particle{<br />
	glm::vec3 pos, speed;<br />
	unsigned char r,g,b,a; // Color<br />
	float size, angle, weight;<br />
	float life; // Remaining life of the particle. if < 0 : dead and unused.</p>
<p>};</p>
<p>const int MaxParticles = 100000;<br />
Particle ParticlesContainer[MaxParticles];</pre><br />
Now, we need a way to create new ones. This function searches linearly in ParticlesContainer, which should be an horrible idea, except that it starts at the last known place, so this function usually returns immediately :</p>
<pre class="brush:cpp">int LastUsedParticle = 0;</p>
<p>// Finds a Particle in ParticlesContainer which isn't used yet.<br />
// (i.e. life < 0);<br />
int FindUnusedParticle(){</p>
<p>    for(int i=LastUsedParticle; i<MaxParticles; i++){<br />
        if (ParticlesContainer[i].life < 0){<br />
            LastUsedParticle = i;<br />
            return i;<br />
        }<br />
    }</p>
<p>    for(int i=0; i<LastUsedParticle; i++){<br />
        if (ParticlesContainer[i].life < 0){<br />
            LastUsedParticle = i;<br />
            return i;<br />
        }<br />
    }</p>
<p>    return 0; // All particles are taken, override the first one<br />
}</pre><br />
We can now fill&nbsp;ParticlesContainer[particleIndex] with interesting "life", "color", "speed" and "position" values. See the code for details, but you can do pretty much anything here. The only interesting bit is, how many particles should we generate each frame ? This is mostly application-dependant, so let's say 10000 new particles per second (yes, it's quite a lot) :</p>
<pre class="brush:cpp">int newparticles = (int)(deltaTime*10000.0);</pre><br />
except that you should probably clamp this to a fixed number :</p>
<pre class="brush:cpp">// Generate 10 new particule each millisecond,<br />
// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),<br />
// newparticles will be huge and the next frame even longer.<br />
int newparticles = (int)(deltaTime*10000.0);<br />
if (newparticles > (int)(0.016f*10000.0))<br />
    newparticles = (int)(0.016f*10000.0);</pre></p>
<h2>Deleting old particles</h2><br />
There's a trick, see below =)</p>
<h1>The main simulation loop</h1><br />
ParticlesContainer contains both active and "dead" particles, but the buffer that we send to the GPU needs to have only living particles.</p>
<p>So we will iterate on each particle, check if it is alive, if it must die, and if everything is allright, add some gravity, and finally copy it in a GPU-specific buffer.</p>
<pre class="brush:cpp">// Simulate all particles<br />
int ParticlesCount = 0;<br />
for(int i=0; i<MaxParticles; i++){</p>
<p>    Particle&amp; p = ParticlesContainer[i]; // shortcut</p>
<p>    if(p.life > 0.0f){</p>
<p>        // Decrease life<br />
        p.life -= delta;<br />
        if (p.life > 0.0f){</p>
<p>            // Simulate simple physics : gravity only, no collisions<br />
            p.speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;<br />
            p.pos += p.speed * (float)delta;<br />
            p.cameradistance = glm::length2( p.pos - CameraPosition );<br />
            //ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;</p>
<p>            // Fill the GPU buffer<br />
            g_particule_position_size_data[4*ParticlesCount+0] = p.pos.x;<br />
            g_particule_position_size_data[4*ParticlesCount+1] = p.pos.y;<br />
            g_particule_position_size_data[4*ParticlesCount+2] = p.pos.z;</p>
<p>            g_particule_position_size_data[4*ParticlesCount+3] = p.size;</p>
<p>            g_particule_color_data[4*ParticlesCount+0] = p.r;<br />
            g_particule_color_data[4*ParticlesCount+1] = p.g;<br />
            g_particule_color_data[4*ParticlesCount+2] = p.b;<br />
            g_particule_color_data[4*ParticlesCount+3] = p.a;</p>
<p>        }else{<br />
            // Particles that just died will be put at the end of the buffer in SortParticles();<br />
            p.cameradistance = -1.0f;<br />
        }</p>
<p>        ParticlesCount++;</p>
<p>    }<br />
}</pre><br />
This is what you get. Almost there, but there's a problem...</p>
<p><img class="alignnone size-full wp-image-963" title="particles_unsorted" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/particles_unsorted.png" alt="" width="905" height="751" /></p>
<h2>Sorting</h2><br />
As explained in <a title="Tutorial 10 : Transparency" href="http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/">Tutorial 10</a>, you need to sort semi-transparent objects from back to front for the blending to be correct.</p>
<pre class="brush:cpp">void SortParticles(){<br />
&nbsp; &nbsp; std::sort(&amp;ParticlesContainer[0], &amp;ParticlesContainer[MaxParticles]);<br />
}</pre><br />
Now, std::sort needs a function that can tell whether a Particle must be put before or after another Particle in the container. This can be done with Particle::operator< :</p>
<pre>// CPU representation of a particle<br />
struct Particle{</p>
<p>    ...</p>
<p>    bool operator<(Particle&amp; that){<br />
        // Sort in reverse order : far particles drawn first.<br />
        return this->cameradistance > that.cameradistance;<br />
    }<br />
};</pre><br />
This will make ParticleContainer be sorted, and the particles now display correctly*:</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/particles_final.gif"><img class="alignnone size-full wp-image-965" title="particles_final" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/particles_final.gif" alt="" width="400" height="300" /></a></p>
<p>&nbsp;</p>
<h1>Going further</h1></p>
<h2>Animated particles</h2><br />
You can animate your particles' texture with a texture atlas. Send the age of each particle along with the position, and in the shaders, compute the UVs like we did for the <a title="Tutorial 11 : 2D text" href="http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-11-2d-text/">2D font tutorial</a>. A texture atlas looks like this :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/ParticleAtlas.png"><img class="alignnone size-full wp-image-970" title="ParticleAtlas" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/ParticleAtlas.png" alt="" width="1024" height="1024" /></a></p>
<h2>Handling several particle systems</h2><br />
If you need more than one particle system, you have two options : either use a single ParticleContainer, or one per system.</p>
<p>If you have a single container for ALL particles, then you will be able to sort them perfectly. The main drawback is that you'll have to use the same texture for all particles, which is a big problem. This can be solved by using a texture atlas (one big texture with all your different textures on it, just use different UVs), but it's not really handy to edit and use.</p>
<p>If you have one container per particle system, on the other hand, particles will only be sorted inside these containers : if two particle sytems overlap, artefacts will start to appear. Depending on your application, this might not be a problem.</p>
<p>Of course, you can also use some kind of hybrid system with several particle systems, each with a (small and manageable) atlas.</p>
<h2>Smooth particles</h2><br />
You'll notice very soon a common artifact : when your particle intersect some geometry, the limit becomes very visible and ugly :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/ParticleHardSmooth.jpg"><img class="alignnone size-full wp-image-974" title="ParticleHardSmooth" src="http://www.opengl-tutorial.org/wp-content/uploads/2013/10/ParticleHardSmooth.jpg" alt="" width="379" height="187" /></a></p>
<p>(image from&nbsp;http://www.gamerendering.com/2009/09/16/soft-particles/ )</p>
<p>A common technique to solve this is to test if the currently-drawn fragment is near the Z-Buffer. If so, the fragment is faded out.</p>
<p>However, you'll have to sample the Z-Buffer, which is not possible with the "normal" Z-Buffer. You need to render your scene in a <a title="Tutorial 14 : Render To Texture" href="http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/">render target</a>. Alternatively, you can copy the Z-Buffer from one framebuffer to another with glBlitFramebuffer.</p>
<p>http://developer.download.nvidia.com/whitepapers/2007/SDK10/SoftParticles_hi.pdf</p>
<h2>Improving fillrate</h2><br />
One of the most limiting factor in modern GPUs is fillrate : the amount of fragments (pixels) it can write in the 16.6ms allowed to get 60 FPS.</p>
<p>This is a problem, because particles typically need a LOT of fillrate, since you can re-draw the same fragment 10 times, each time with another particle; and if you don't do that, you get the same artifacts as above.</p>
<p>Amongst all the fragments that are written, many are completely useless : these on the border. Your particle textures are often completely transparent on the edges, but the particle's mesh will still draw them - and update the color buffer with exactly the same value than before.</p>
<p>This small utility computes a mesh (the one you're supposed to draw with glDrawArraysInstanced() ) that tightly fits your texture :</p>
<p><a href="http://www.humus.name/Cool/ParticleTrimmer.jpg"><img class="alignnone" src="http://www.humus.name/Cool/ParticleTrimmer.jpg" alt="" width="256" height="192" /></a></p>
<p><a href="http://www.humus.name/index.php?page=Cool&amp;ID=8">http://www.humus.name/index.php?page=Cool&amp;ID=8</a>&nbsp;. Emil Person's site has plenty of other fascinating articles, too.</p>
<h2>Particle physics</h2><br />
At some point, you'll probably want your particles to interact some more with your world. In particular, particles could rebound on the ground.</p>
<p>You could simply launch a raycast for each particle, between the current position and the future one; we learnt to do this in the <a title="Picking with a physics library" href="http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-a-physics-library/">Picking tutorials</a>. But this is extremely expensive, you just can't to this for each particle, each frame.</p>
<p>Depending on your application, you can either approximate your geometry with a set of planes and do the raycast on these planes only; Or, you can use real raycast, but cache the results and approximate nearby collisions with the cache (or, you can do both).</p>
<p>A completely different technique is to use the existing Z-Buffer as a very rough approximation of the (visible) geometry, and collide particles on this. This is "good enough" and fast, but you'll have to do all your simulation on the GPU, since you can't access the Z-Buffer on the CPU (at least not fast), so it's way more complicated.</p>
<p>Here are a few links about these techniques :</p>
<p><a href="http://www.altdevblogaday.com/2012/06/19/hack-day-report/">http://www.altdevblogaday.com/2012/06/19/hack-day-report/</a></p>
<p><a href="http://www.gdcvault.com/search.php#&amp;category=free&amp;firstfocus=&amp;keyword=Chris+Tchou's%2BHalo%2BReach%2BEffects&amp;conference_id=">http://www.gdcvault.com/search.php#&amp;category=free&amp;firstfocus=&amp;keyword=Chris+Tchou's%2BHalo%2BReach%2BEffects&amp;conference_id=</a></p>
<h2>GPU Simulation</h2><br />
As said above, you can simulate the particles' movements completely on the GPU. You will still have to manage your particle's lifecycle on the CPU - at least to spawn them.</p>
<p>You have many options to do this, and none in the scope of this tutorial ; I'll just give a few pointers.</p>
<ul>
<li>Use Transform Feedback. It allows you to store the outputs of a vertex shader in a GPU-side VBO. Store the new positions in this VBO, and next frame, use this VBO as the starting point, and store the new position in the former VBO.</li>
<li>Same thing but without Transform Feedback: encode your particles' positions in a texture, and update it with Render-To-Texture.</li>
<li>Use a General-Purpose GPU library : CUDA or OpenCL, which have interoperability functions with OpenGL.</li>
<li>Use a Compute Shader. Cleanest solution, but only available on very recent GPUs.</li><br />
</ul><br />
&nbsp;</p>
<p>* Note that for simplicity, in this implementation, ParticleContainer is sorted after updating the GPU buffers. This makes the particles not exactly sorted (there is a one-frame delay), but it's not really noticeable. You can fix it by splitting the main loop in 2 : Simulate, Sort, and update.</p>
