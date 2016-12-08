---
layout: page
status: publish
published: true
title: Billboards
date: '2013-10-15 17:15:15 +0200'
date_gmt: '2013-10-15 17:15:15 +0200'
categories: []
order: 110
tags: []
---

Billboards are 2D elements incrusted in a 3D world. Not a 2D menu on top of everything else; not a 3D plane around which you can turn; but something in-between, like health bars in many games.

What's different with billboards is that they are positionned at a specific location, but their orientation is automatically computed so that it always faces the camera.

 

# Solution #1 : The 2D way

This one is supra-easy.

Just compute where your point is on screen, and display a 2D text (see Tutorial 11) at this position.

``` cpp
// Everything here is explained in Tutorial 3 ! There's nothing new.
glm::vec4 BillboardPos_worldspace(x,y,z, 1.0f);
glm::vec4 BillboardPos_screenspace = ProjectionMatrix * ViewMatrix * BillboardPos_worldspace;
BillboardPos_screenspace /= BillboardPos_screenspace.w;

if (BillboardPos_screenspace.z < 0.0f){
    // Object is behind the camera, don't display it.
}
```

Ta-dah !

On the plus side, this method is really easy, and the billboard will have the same size regardless of its distance to the camera. But 2D text is always displayed on top of everything else, and this can/will mess up the rendering and show above other objects.

 

# Solution #2 : The 3D way

This one is usually better and not much more complicated.

The goal is to keep the mesh aligned with the camera, even when the camera moves :

![]({{site.baseurl}}/assets/images/tuto-billboard/2a.gif)


You can view this problem as generating an appropriate Model matrix, even though it's is much simpler than that.

The idea is that each corner of the billboard is at the center position, displaced by the camera's up and right vectors :

 

![]({{site.baseurl}}/assets/images/tuto-billboard/principle.png)


 

Of course, we only know the billboard's center position in world space, so we also need the camera's up/right vectors in world space.

In camera space, the camera's up vector is (0,1,0). To get it in world space, just multiply this by the matrix that goes from Camera Space to World Space, which is, of course, the inverse of the View matrix.

An easier way to express the same math is :
```

CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}
CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}
```

Once we have this, it's very easy to compute the final vertex' position :

``` glsl
vec3 vertexPosition_worldspace =
    particleCenter_wordspace
    + CameraRight_worldspace * squareVertices.x * BillboardSize.x
    + CameraUp_worldspace * squareVertices.y * BillboardSize.y;
```
{: .highlightglslvs }

* particleCenter_worldspace is, as its name suggests, the billboard's center position. It is specified with an uniform vec3.
* squareVertices is the original mesh. squareVertices.x is -0.5 for the left vertices, which are thus moved towars the left of the camera (because of the *CameraRight_worldspace)
* BillboardSize is the size, in world units, of the billboard, sent as another uniform.

<div><span style="font-size: medium;"><span style="line-height: 24px;">And presto, here's the result. Wasn't this easy ? </span></span><span style="font-size: 16px;"> </span></div>
![]({{site.baseurl}}/assets/images/tuto-billboard/2.gif)


 

For the record, here's how squareVertices is made :

``` cpp
// The VBO containing the 4 vertices of the particles.
 static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
 };
```

# Solution #3 : The fixed-size 3D way

As you can see above, the size of the billboard changes with respect to the camera's distance. This is the expected result in some cases, but in others, such as health bars, you probably want a fixed-size instead.

Since the displacement between the center and a corner must be fixed in screen-space, that's exactly what we're going to do : compute the center's position in screen space, and offset it.

``` cpp
vertexPosition_worldspace = particleCenter_wordspace;
// Get the screen-space position of the particle's center
gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);
// Here we have to do the perspective division ourselves.
gl_Position /= gl_Position.w;

// Move the vertex in directly screen space. No need for CameraUp/Right_worlspace here.
gl_Position.xy += squareVertices.xy * vec2(0.2, 0.05);
```

Remember that at this stage of the rendering pipeline, you're in Normalized Device Coordinates, so between -1 and 1 on both axes : it's not in pixels.

If you want a size in pixels, easy : just use (ScreenSizeInPixels / BillboardSizeInPixels) instead of BillboardSizeInScreenPercentage.

 

![]({{site.baseurl}}/assets/images/tuto-billboard/3.gif)


 

# Solution #4 : Vertical rotation only

Some systems model faraway trees and lamps as billboards. But you really, really don't want your tree to be bent : it MUST be vertical. So you need an hybrid system that rotates only around one axis.

Well, this one is left as an exercise to the reader !

 

 
