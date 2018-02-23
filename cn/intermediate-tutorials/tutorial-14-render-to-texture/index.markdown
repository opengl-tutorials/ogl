---
layout: tutorial
status: publish
published: true
title: '教程14：渲染到纹理'
date: '2011-05-26 19:33:15 +0200'
date_gmt: '2011-05-26 19:33:15 +0200'
categories: [tuto]
order: 540
tags: []
language: cn
---

* TOC
{:toc}

渲染到纹理是少数用于创建各种特效的方法。这种方法的基础思想像平常一样渲染一个场景，但是这一次是渲染一张纹理并且在之后进行使用。

应用范围包括，游戏内的摄像机，后处理与其他你能够想象得到的特效.

# 渲染到纹理

我们有三个任务：创建一个我们即将要渲染的纹理，然后渲染一些图像到纹理上，然后使用我们渲染后的纹理。

## 创建渲染纹理对象

我们要渲染的对象叫帧缓存。帧缓存是一个包含纹理和深度缓存（可选择）区的容器。 其创建方式与其余的在OpenGL创建对象的方式一致。 

``` cpp
// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
GLuint FramebufferName = 0;
glGenFramebuffers(1, &FramebufferName);
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
```

现在我们需要创建一个存储从着色器输出RGB的一张纹理。代码非常的简单。

``` cpp
// The texture we're going to render to
GLuint renderedTexture;
glGenTextures(1, &renderedTexture);

// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, renderedTexture);

// Give an empty image to OpenGL ( the last "0" )
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

// Poor filtering. Needed !
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

同时我们需要一个深度缓存区。这个操作是可选择的，基于我们最后渲染到纹理的对象是什么。 因为我们要渲染Suzanne这个模型，因此深度缓存是必要的。

``` cpp
// The depth buffer
GLuint depthrenderbuffer;
glGenRenderbuffers(1, &depthrenderbuffer);
glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
```

最后，我们要将纹理配置到帧缓存中。

``` cpp
// Set "renderedTexture" as our colour attachement #0
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

// Set the list of draw buffers.
GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
```

在这个过程中可能会出现一些问题，这取决与你GPU的功能。下面的代码会教你如何检测它。

``` cpp
// Always check that our framebuffer is ok
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
return false;
```

## 渲染纹理

渲染纹理很简单。简单地绑定你的帧缓冲区，并像往常一样绘制场景。 简单

``` cpp
// Render to our framebuffer
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
```

片段着色器只需稍作改动：

``` cpp
layout(location = 0) out vec3 color;
```

这意味着当写入变量 “color” 时， 我们实际上将会在 Render Target 0 中写入，这正好是我们的纹理， 因为D rawBuffers [0] 是 GL_COLOR_ATTACHMENT i， 在我们的例子中是 renderedTexture。

回顾一下：

* *color* (颜色) 将写入第一个缓冲区因为 layout(location=0)
* 第一个缓冲区是GL_COLOR_ATTACHMENT0，因为DrawBuffers [1] = {GL_COLOR_ATTACHMENT0}
* GL_COLOR_ATTACHMENT0有renderedTexture连接，所以你写入的颜色。
* 换句话说，你可以用GL_COLOR_ATTACHMENT2替换GL_COLOR_ATTACHMENT0，它依旧可以正常运行。

注意：在OpenGL &lt;3.3中没有layout（location = i），但是你依旧可以使用glFragData [i] = myvalue。

## 使用渲染纹理

我们即将用一个四边形来填充我们的屏幕，跟往常一样，我们需要缓存，着色，ID等等。

``` cpp
// The fullscreen quad's FBO
GLuint quad_VertexArrayID;
glGenVertexArrays(1, &quad_VertexArrayID);
glBindVertexArray(quad_VertexArrayID);

static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
};

GLuint quad_vertexbuffer;
glGenBuffers(1, &quad_vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

// Create and compile our GLSL program from the shaders
GLuint quad_programID = LoadShaders( "Passthrough.vertexshader", "SimpleTexture.fragmentshader" );
GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
GLuint timeID = glGetUniformLocation(quad_programID, "time");
```

现在我们将要对象渲染到屏幕上，这里将0作为glBindFramebuffer方法调用的第二个参数。

``` cpp
// Render to the screen
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
```

我们可以用下面的着色器来画出一个覆盖全屏幕的四边形。

``` glsl
#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;

void main(){
    color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz;
}
```
{: .highlightglslfs }

上述代码简单的对纹理进行了采样，同时增加了一些根据时间变化的小偏移。

# 结果

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvy.png)

# 延伸阅读

## 使用深度缓存

在某些时候，你可能需要深度缓存来渲染纹理。在本章的例子中，你可以简单的使用以下代码来渲染一个纹理。

``` cpp
glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
```

24是以位为单位的精度单位。你可以根据你的需求自选择16,24,32。通常24已经足够满足需求。

以上的步骤应该足以让你完成目标，同时提供的代码也实现了这一点。

值得注意的是这一步可能会有点慢，因为驱动程序可能无法使用一些例如Hi-Z的优化在这张屏幕截图中，深度被人为的美化过。通常来说，在深度纹理中，你看不到任何东西。近距离Z和0为黑色，远距离Z和1为白色。

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvydepth.png)


## 多重采样

你可用多重采样纹理代替基础的纹理，只需要在C++中将glTexImage2D方法替换为 glTexImage2DMultisample 方法，同时在片段着色器中将sampler2D/texture替换为 sampler2DMS/texelFetch。

这里有一个重要的说明，texelFetch额外需要一个采样数字作为参数。从另一个方面来说，没有自动“过滤”这一说。(当谈到多重采样时，正确的术语是“分辨率”)

所以你可能不得不在另一个非MS纹理中自己解析MS纹理，这要归功于另一个着色器。

这没有什么困难，只是操作比较复杂。

## 多重渲染对象

你可以在同一时间渲染几个纹理。

简单的创建几个纹理（全都用正确且相同的尺寸），使用不同的颜色附件来调用glFramebufferTexture, 使用更新后的参数调用glDrawBuffers(例如(2,{GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1}}))， 并在片段着色器中添加另一个输出变量

``` glsl
layout(location = 1) out vec3 normal_tangentspace; // or whatever
```
{: .highlightglslfs }


提示：如果需要快速的从文立中输出一个向量，则浮点纹理将以16或32位精度而不是8位精度存在。请参阅glTexImage2D的文档（搜索GL_FLOAT）。

提示2：对于以前版本的OpenGL，请改用glFragData [1] = myvalue。



Hint : If you effectively need to output a vector in a texture, floating-point textures exist, with 16 or 32 bit precision instead of 8... See [glTexImage2D](http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml)'s reference (search for GL_FLOAT).

Hint2 : For previous versions of OpenGL, use glFragData[1] = myvalue instead.

# 练习

* 尝试使用glViewport（0,0,512,768）; 而不是glViewport（0,0,1024,768)（尝试同时使用帧缓冲区和屏幕）
* 在最后一个片段着色器中尝试其他UV坐标
* 尝试使用变换矩阵变换四边形。首先硬编码它，然后尝试使用controls.hpp的函数; 你注意到了什么变化？