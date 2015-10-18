---
layout: page
status: publish
published: true
title: 'Tutorial 5 : A Textured Cube'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 83
wordpress_url: http://www.opengl-tutorial.org/?page_id=83
date: '2011-04-26 07:55:58 +0200'
date_gmt: '2011-04-26 07:55:58 +0200'
categories: [tuto]
order: 50
tags: []
---

In this tutorial, you will learn :

* What are UV coordinates
* How to load textures yourself
* How to use them in OpenGL
* What is filtering and mipmapping, and how to use them
* How to load texture more robustly with GLFW
* What is the alpha channel


#About UV coordinates

When texturing a mesh, you need a way to tell to OpenGL which part of the image has to be used for each triangle. This is done with UV coordinates.

Each vertex has, on top of its position, a couple of floats, U and V. These coordinates are used to access the texture, in the following way :

[<img class="alignnone size-full wp-image-116" title="UVintro" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/UVintro.png" width="662" height="337" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/UVintro.png)

Notice how the texture is distorted on the triangle.

 

#Loading .BMP images yourself

Knowing the BMP file format is not crucial : plenty of libraries can do it for you. But it's very simple and can help you understand how things work under the hood. So we'll write a BMP file loader from scratch, so that you know how it works, <span style="text-decoration: underline;">and never use it again</span>.

Here is the declaration of the loading function :
{% highlight cpp linenos %}
GLuint loadBMP_custom(const char * imagepath);
{% endhighlight %}
so it's used like this :
{% highlight cpp linenos %}
GLuint image = loadBMP_custom("./my_texture.bmp");
{% endhighlight %}
Let's see how to read a BMP file, then.

First, we'll need some data. These variable will be set when reading the file.
{% highlight cpp linenos %}
// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
// Actual RGB data
unsigned char * data;
{% endhighlight %}
We now have to actually open the file
{% highlight cpp linenos %}
// Open the file
FILE * file = fopen(imagepath,"rb");
if (!file)							    {printf("Image could not be opened\n"); return 0;}
{% endhighlight %}
The first thing in the file is a 54-bytes header. It contains information such as "Is this file really a BMP file?", the size of the image, the number of bits per pixel, etc. So let's read this header :
{% highlight cpp linenos %}
if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}
{% endhighlight %}
The header always begins by BM. As a matter of fact, here's what you get when you open a .BMP file in a hexadecimal editor :

[<img class="alignnone size-full wp-image-662" title="hexbmp" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/hexbmp.png" width="541" height="128" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/hexbmp.png)

So we have to check that the two first bytes are really 'B' and 'M' :
{% highlight cpp linenos %}
if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
}
{% endhighlight %}
Now we can read the size of the image, the location of the data in the file, etc :
{% highlight cpp linenos %}
// Read ints from the byte array
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);
{% endhighlight %}
We have to make up some info if it's missing :
{% highlight cpp linenos %}
// Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
if (dataPos==0)      dataPos=54; // The BMP header is done that way
{% endhighlight %}
Now that we know the size of the image, we can allocate some memory to read the image into, and read :
{% highlight cpp linenos %}
// Create a buffer
data = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
fread(data,1,imageSize,file);

//Everything is in memory now, the file can be closed
fclose(file);
{% endhighlight %}
We arrive now at the real OpenGL part. Creating textures is very similar to creating vertex buffers : Create a texture, bind it, fill it, and configure it.

In glTexImage2D, the GL_RGB indicates that we are talking about a 3-component color, and GL_BGR says how exactly it is represented in RAM. As a matter of fact, BMP does not store Red->Green->Blue but Blue->Green->Red, so we have to tell it to OpenGL.
{% highlight cpp linenos %}
// Create one OpenGL texture
GLuint textureID;
glGenTextures(1, &textureID);

// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, textureID);

// Give the image to OpenGL
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
{% endhighlight %}
We'll explain those last two lines later. Meanwhile, on the C++-side, you can use your new function to load a texture :
{% highlight cpp linenos %}
GLuint Texture = loadBMP_custom("uvtemplate.bmp");
{% endhighlight %}
Another very important point :** use power-of-two textures !**

* good : 128*128*, 256*256, 1024*1024, 2*2...
* bad : 127*128, 3*5, ...
* okay but weird : 128*256


#Using the texture in OpenGL

We'll have a look at the fragment shader first. Most of it is straightforward :
{% highlight glsl linenos cssclass=highlightglslfs %}
#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV ).rgb;
}
{% endhighlight %}
Three things :

* The fragment shader needs UV coordinates. Seems fair.
* It also needs a "sampler2D" in order to know which texture to access (you can access several texture in the same shader)
* Finally, accessing a texture is done with texture(), which gives back a (R,G,B,A) vec4. We'll see about the A shortly.

The vertex shader is simple too, you just have to pass the UVs to the fragment shader :
{% highlight glsl linenos cssclass=highlightglslvs %}
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
{% endhighlight %}
Remember "layout(location = 1) in vec2 vertexUV" from Tutorial 4 ? Well, we'll have to do the exact same thing here, but instead of giving a buffer (R,G,B) triplets, we'll give a buffer of (U,V) pairs.
{% highlight cpp linenos %}
// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};
{% endhighlight %}
The UV coordinates above correspond to the following model :

[<img class="alignnone size-medium wp-image-115" title="uv_mapping_blender" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/uv_mapping_blender-300x222.png" width="300" height="222" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/uv_mapping_blender.png)

The rest is obvious. Generate the buffer, bind it, fill it, configure it, and draw the Vertex Buffer as usual. Just be careful to use 2 as the second parameter (size) of glVertexAttribPointer instead of 3.

This is the result :

[<img class="alignnone size-full wp-image-119" title="nearfiltering" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nearfiltering.png" width="533" height="557" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering.png)

and a zoomed-in version :

[<img class="alignnone size-full wp-image-120" title="nearfiltering_zoom" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nearfiltering_zoom.png" width="348" height="340" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering_zoom.png)

#What is filtering and mipmapping, and how to use them

As you can see in the screenshot above, the texture quality is not that great. This is because in loadBMP_custom, we wrote :
{% highlight cpp linenos %}
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
{% endhighlight %}
This means that in our fragment shader, texture() takes the texel that is at the (U,V) coordinates, and continues happily.

[<img class="alignnone size-full wp-image-130" title="nearest" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nearest.png" width="440" height="240" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearest.png)

There are several things we can do to improve this.

##Linear filtering

With linear filtering, texture() also looks at the other texels around, and mixes the colours according to the distance to each center. This avoids the hard edges seen above.

[<img class="alignnone size-full wp-image-133" title="linear" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/linear1.png" width="440" height="240" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/linear1.png)

This is much better, and this is used a lot, but if you want very high quality you can also use anisotropic filtering, which is a bit slower.

##Anisotropic filtering

This one approximates the  part of the image that is really seen through the fragment. For instance, if the following texture is seen from the side, and a little bit rotated, anisotropic filtering will compute the colour contained in the blue rectangle by taking a fixed number of samples (the "anisotropic level") along its main direction.

[<img class="alignnone size-full wp-image-131" title="aniso" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/aniso.png" width="440" height="240" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/aniso.png)

##Mipmaps

Both linear and anisotropic filtering have a problem. If the texture is seen from far away, mixing only 4 texels won't be enough. Actually, if your 3D model is so far away than it takes only 1 fragment on screen, ALL the texels of the image should be averaged to produce the final color. This is obviously not done for performance reasons. Instead, we introduce MipMaps :

[<img class="alignnone" title="An original image and its mipmaps. Image by Tokigun under Creative Commons" alt="" src="http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg" width="384" height="256" />](http://en.wikipedia.org/wiki/File:MipMap_Example_STS101.jpg)

* At initialisation tile, you scale down your image by 2, successively, until you only have a 1x1 image (which effectively is the average of all the texels in the image)
* When you draw a mesh, you select which mipmap is the more appropriate to use given how big the texel should be.
* You sample this mipmap with either nearest, linear or anisotropic filtering
* For additional quality, you can also sample two mipmaps and blend the results.

Luckily, all this is very simple to do, OpenGL does everything for us provided that you ask him nicely :
{% highlight cpp linenos %}
// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// Generate mipmaps, by the way.
glGenerateMipmap(GL_TEXTURE_2D);
{% endhighlight %}

#How to load texture with GLFW

Our loadBMP_custom function is great because we made it ourselves, but using a dedicated library is better. GLFW can do that too (but only for TGA files) :
{% highlight cpp linenos %}
GLuint loadTGA_glfw(const char * imagepath){

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Read the file, call glTexImage2D with the right parameters
    glfwLoadTexture2D(imagepath, 0);

    // Nice trilinear filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Return the ID of the texture we just created
    return textureID;
}
{% endhighlight %}

#Compressed Textures

At this point, you're probably wondering how to load JPEG files instead of TGA.

Short answer : don't. There's a better option.

##Creating compressed textures


* Download [The Compressonator](http://developer.amd.com/Resources/archive/ArchivedTools/gpu/compressonator/Pages/default.aspx), an ATI tool
* Load a Power-Of-Two texture in it
* Compress it in DXT1, DXT3 or in DXT5 (more about the differences between the various formats on [Wikipedia](http://en.wikipedia.org/wiki/S3_Texture_Compression)) :

[<img class="alignnone size-full wp-image-358" title="TheCompressonator" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/TheCompressonator.png" width="806" height="688" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/TheCompressonator.png)

* Generate mipmaps so that you won't have to do it on runtime
* Export it as a .DDS file.

At this point, your image is compressed in a format that is directly compatible with the GPU. Whenever calling texture() in a shader, it will uncompress it on-the-fly. This can seem slow, but since it takes a LOT less memory, less data needs to be transferred. But memory transfers are expensive; and texture decompression is free (there is dedicated hardware for that). Typically, using texture compression yields a 20% increase in performance.

##Using the compressed texture

Let's see how to load the image. It's very similar to the BMP code, except that the header is organized differently :
{% highlight cpp linenos %}
GLuint loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fp = fopen(imagepath, "rb");
    if (fp == NULL)
        return 0;

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
{% endhighlight %}
After the header is the actual data : all the mipmap levels, successively. We can read them all in one batch :

 
{% highlight cpp linenos %}
    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);
{% endhighlight %}
Here we'll deal with 3 different formats : DXT1, DXT3 and DXT5. We need to convert the "fourCC" flag into a value that OpenGL understands.
{% highlight cpp linenos %}
    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }
{% endhighlight %}
Creating the texture is done as usual :
{% highlight cpp linenos %}
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
{% endhighlight %}
And now, we just have to fill each mipmap one after another :
{% highlight cpp linenos %}
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 
            0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer); 

    return textureID;
{% endhighlight %}

##Inversing the UVs

DXT compression comes from the DirectX world, where the V texture coordinate is inversed compared to OpenGL. So if you use compressed textures, you'll have to use ( coord.u, 1.0-coord.v) to fetch the correct texel. You can do this whenever you want : in your export script, in your loader, in your shader...

#Conclusion

You just learnt to create, load and use textures in OpenGL.

In general, you should only use compressed textures, since they are smaller to store, almost instantaneous to load, and faster to use; the main drawback it that you have to convert your images through The Compressonator.

#Exercices


* The DDS loader is implemented in the source code, but not the texture coordinate modification. Change the code at the appropriate place to display the cube correctly.
* Experiment with the various DDS formats. Do they give different result ? Different compression ratios ?
* Try not to generate mipmaps in The Compressonator. What is the result ? Give 3 different ways to fix this.


#References


* [Using texture compression in OpenGL](http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf) , S&eacute;bastien Domine, NVIDIA

