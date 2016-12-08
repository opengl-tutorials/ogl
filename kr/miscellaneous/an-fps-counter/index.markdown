---
layout: page
status: publish
published: true
title: An FPS counter
date: '2012-01-28 16:24:41 +0100'
date_gmt: '2012-01-28 16:24:41 +0100'
categories: []
order: 40
tags: []
---

In real-time graphics, it is important to keep an eye on performance. A good practice is to choose a target FPS ( usually 60 or 30 ) and make everything possible to stick to it.

A FPS counter looks like this :

``` cpp
 double lastTime = glfwGetTime();
 int nbFrames = 0;

 do{

     // Measure speed
     double currentTime = glfwGetTime();
     nbFrames++;
     if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
         // printf and reset timer
         printf("%f ms/frame\n", 1000.0/double(nbFrames));
         nbFrames = 0;
         lastTime += 1.0;
     }

     ... rest of the main loop
```

There is an odd thing in this code. It displays the time, in milliseconds, needed to draw a frame (averaged on 1 second) instead of how many frame were drawn in the last second.

This is actually **much better**. Don't rely on FPS. Never. FramesPerSecond = 1/SecondsPerFrame, so this is an inverse relationship, and we humans suck at understanding this kind of relationship. Let's take an example.

You write a great rendering function that runs at 1000 FPS ( 1ms/frame ). But you forgot a little computation in a shader, which adds an extra cost of 0.1ms. And bam, 1/0.0011 = 900. You just lost 100FPS. Morality : **never use FPS for performance analysis.**

If you intend to make a 60fps game, your target will be 16.6666ms ; If you intend to make a 30fps game, your target will be 33.3333ms. That's all you need to know.

This code is available in all tutorials starting from [Tutorial 9 : VBO indexing]({{site.baseurl}}/intermediate-tutorials/tutorial-9-vbo-indexing/); see [tutorial09_vbo_indexing/tutorial09.cpp](https://github.com/opengl-tutorials/ogl/blob/master/tutorial09_vbo_indexing/tutorial09.cpp#L142) . Other performance tools are available in [Tools - Debuggers]({{site.baseurl}}/miscellaneous/useful-tools-links/#debugging-tools).
