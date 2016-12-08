---
layout: page
status: publish
published: true
title: 'Tutorial 9 : VBO Indexing'
date: '2011-05-12 19:21:49 +0200'
date_gmt: '2011-05-12 19:21:49 +0200'
categories: [tuto]
order: 10
tags: []
---

# The principle of indexing

Until now, when building your VBO, we always duplicated our vertices whenever two triangles shared an edge.

In this tutorial, we introduce indexing, which enables to reuse the same vertex over and over again. This is done with an *index buffer*.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/indexing1.png)


The index buffer contains integers, three for each triangle in the mesh, which reference the various *attribute buffers* (position, colour, UV coordinates, other UV coordinates, normal, ...). It's a little bit like in the OBJ file format, with one huge difference : there is only ONE index buffer. This means that for a vertex to be shared between two triangles, all attributes must be the same.

# Shared vs Separate

Let's take the example of the normals. In this figure, the artist who created these two triangle probably wanted them to represent a smooth surface. We can thus blend the normals of the two triangle into a single vertex normal. For visualization purposes, I added a red line which represents the aspect of the smooth surface.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/goodsmooth.png)


In this second figure however, the artist visibly wanted a "seam", a rough edge. But if we merge the normals, this means that the shader will smoothly interpolate as usual and create a smooth aspect just like before :

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/badmooth.png)


So in this case it's actually better to have two different normals, one for each vertex. The only way to do this in OpenGL is to duplicate the whole vertex, with its whole set of attributes.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/spiky.png)


# Indexed VBO in OpenGL

Using indexing is very simple. First, you need to create an additional buffer, which you fill with the right indices. The code is the same as before, but now it's an ELEMENT_ARRAY_BUFFER, not an ARRAY_BUFFER.

``` cpp
std::vector<unsigned int> indices;

// fill "indices" as needed

// Generate a buffer for the indices
 GLuint elementbuffer;
 glGenBuffers(1, &elementbuffer);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
```

and to draw the mesh, simply replace glDrawArrays by this :

``` cpp
// Index buffer
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

 // Draw the triangles !
 glDrawElements(
     GL_TRIANGLES,      // mode
     indices.size(),    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 );
```

(quick note : it's better to use "unsigned short" than "unsigned int", because it takes less memory, which also makes it faster)

# Filling the index buffer

Now we actually have a problem. As I said before, OpenGL can only use one index buffer, whereas OBJ (and some other popular 3D formats like Collada) use one index buffer *by attribute*. Which means that we somehow have to convert from N index buffers to 1 index buffer.

The algorithm to do this is as follows :
```

For each input vertex
    Try to find a similar ( = same for all attributes ) vertex between all those we already output
    If found :
        A similar vertex is already in the VBO, use it instead !
    If not found :
        No similar vertex found, add it to the VBO
```

The actual C++ code can be found in common/vboindexer.cpp. It's heavily commented so if you understand the algorithm above, it should be all right.

The criterion for similarity is that vertices' position, UVs and normals should be ** equal. You'll have to adapt this if you add more attributes.

Searching a similar vertex is done with a lame linear search for simplicity. A std::map would be more appropriate for real use.

# Extra : the FPS counter

It's not directly related to indexing, but it's a good moment to have a look at [the FPS counter](http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/) because we can eventually see the speed improvement of indexing. Other performance tools are available in [Tools - Debuggers](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/#debugging-tools).
