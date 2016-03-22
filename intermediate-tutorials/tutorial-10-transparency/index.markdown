---
layout: page
status: publish
published: true
title: 'Tutorial 10 : Transparency'
date: '2011-05-13 23:00:42 +0200'
date_gmt: '2011-05-13 23:00:42 +0200'
categories: [tuto]
order: 20
tags: []
---

# The alpha channel

The concept of the alpha channel is pretty simple. Instead of a writing an RGB result, you write an RGBA :

``` glsl
// Ouput data : it's now a vec4
out vec4 color;
```
{: .highlightglslfs }

the first 3 components are still accessed with the .xyz swizzle operator, while the last one is accessed with .a :

``` glsl
color.a = 0.3;
```
{: .highlightglslfs }

Unintuitively, alpha = opaqueness, so alpha = 1 means fully opaque while alpha = 0 means fully transparent.

Here, we simply hardcode the alpha channel at 0.3, but you probably want to use a uniform, or read it from a RGBA texture ( TGA supports the alpha channel, and GLFW supports TGA )

Here's the result. Make sure to turn backface culling off (glDisable(GL_CULL_FACE) ) because since we can look through the mesh, we could see that it has no "back" face.

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyok.png)


# Order matters !

The previous screenshot looks okay-ish, but that's just because we're lucky.

## The problem

Here, I drew two squares with 50% alpha, one green and one red. You can see that order is important, the final colour gives an important clue to the eyes for proper depth perception.

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyorder.png)


This phenomena also happens in our scene. Let's change the viewpoint a bit :

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencybad.png)


It turns out that this is a very hard problem. You never see lots of transparency in games, do you ?

## Usual solution

The usual solution is to sort all transparent triangles. Yes, ALL transparent triangles.

* Draw the opaque part of the world so that the depth buffer already can reject hidden transparent triangles
* Sort transparent triangles, from the furthest to the closest
* Draw the transparent triangles.

You can sort whatever you want with qsort (in C) or std::sort (in C++). I won't dig in the details, because...

## Caveat

Doing so will work ( more on this in the next section ), but :

* You will be fillrate limited. That is, each fragment will be written 10, 20 times, maybe more. This is way too much for the poor memory bus. Usually the depth buffer allows to reject enough "far" fragments, but here, you explicitly sorted them, so the depth buffer is actually useless.
* You will be doing this 4 times per pixel ( we use 4xMSAA ), except if you use some clever optimisation
* Sorting all the transparent triangles takes time
* If you have to switch your texture, or worse, your shader, from triangle to triangle, you're going into deep performance trouble. Don't do this.

A good enough solution is often to :

* Limit to a maximum the number of transparent polygons
* Use the same shader and the same texture for all of them
* If they are supposed to look very different, use your texture !
* If you can avoid sorting, and it still doesn't look *too *bad, consider yourself lucky.


## Order-Independent Transparency

A number of other techniques are worth investigating if your engine really, really needs state-of-the-art transparency :

* [The original 2001 Depth Peeling paper](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.9286&rep=rep1&type=pdf): pixel-perfect results, not very fast.
* [Dual Depth Peeling](http://developer.download.nvidia.com/SDK/10/opengl/src/dual_depth_peeling/doc/DualDepthPeeling.pdf) : a slight improvement
* Several papers on bucket sort. Uses an array of fragments; sort them by depth in a shader.
* [ATI's Mecha Demo](http://fr.slideshare.net/hgruen/oit-and-indirect-illumination-using-dx11-linked-lists) : good and fast, but tricky to implement, needs recent hardware. Uses a linked list of fragments.
* [Cyril Crassin's variation on the ATI's  technique](http://blog.icare3d.org/2010/07/opengl-40-abuffer-v20-linked-lists-of.html) : even harder implementation

Note that even a recent game like Little Big Planet, which ran on a powerful console, used only 1 layer of transparency.

# The blend function

In order for the previous code to work, you need to setup your blend function.

``` cpp
// Enable blending
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

Which means :
```

New color in framebuffer =
           current alpha in framebuffer * current color in framebuffer +
           (1 - current alpha in framebuffer) * shader's output color
```

Example from the image above, with red on top :

``` cpp
new color = 0.5*(0,1,0) + (1-0.5)*(1,0.5,0.5); // (the red was already blended with the white background)
new color = (1, 0.75, 0.25) = the same orange
```

 
