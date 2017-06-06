---
layout: tutorial
status: publish
published: true
title: "第二课：绘制第一个三角形"
date: '2012-11-15 01:37:45 +0100'
date_gmt: '2012-11-15 01:37:45 +0100'
categories: []
tags: []
order: 20
language: cn
---

* TOC
{:toc}

第二课：绘制第一个三角形
===

本课依然是“长篇大论”。

用OpenGL 3绘制复杂的物体很方便，绘制一个简单的三角形却十分麻烦。

别忘了不时地复制粘贴代码，动手调试。

<span style="color: red">**如果程序启动时崩溃了，很可能是您的运行目录有误。请仔细阅读第一课中讲到的Visual Studio配置方法！**</span>

## 顶点数组对象(VAO)
您得创建一个VAO，并将它设为当前对象（暂不详细展开）：

``` cpp
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
```

窗口创建成功后（即OpenGL上下文创建后）紧接着完成上述动作；这一步必须在其他OpenGL调用前完成。

若想进一步了解顶点数组对象（VAO）可以参考其他教程，不过VAO不是很重要。

## 屏幕坐标系
三点确定一个三角形。我们常常用“顶点”（Vertex，复数vertices）来指代3D图形学中的点。一个顶点有三个坐标：X，Y和Z。您可以这样想象这三根坐标轴：

- X轴朝右
- Y轴朝上
- Z轴指向您后面（没错，是后面，不是前面）

还有更形象的方法：使用右手定则

- 拇指代表X轴
- 食指代表Y轴
- 中指代表Z轴。如果您的拇指指向右边，食指指向天空，那么中指将指向您的后面。

为什么Z轴方向这么奇怪呢？简言之：因为基于右手定则的坐标系统被广泛使用了100多年，这一系统涵盖了许多实用工具，唯一的缺点就是Z方向比较别扭。

补充说明一下，您的手可以自由移动，X轴，Y轴和Z轴同样也能移动（详见后文）。

我们需要三个三维点来组成一个三角形；下面来定义一个三角形：

``` cpp
// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
```

第一个顶点是(-1, -1, 0)。
这意味着如果不变换该顶点，它就将显示在屏幕的(-1, -1)位置。这是什么意思呢？屏幕的原点在中间，X轴朝右，Y轴朝上。屏幕坐标如下图：

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}

这是显卡内置的坐标系，无法改变。(-1, -1)是屏幕的左下角，(1, -1)是右下角，(0, 1)位于中上部。这个三角形占据了大部分屏幕。

## 绘制三角形
下一步，通过缓冲把三角形传给OpenGL：

``` cpp
// This will identify our vertex buffer
GLuint vertexbuffer;

// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);

// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
```

这步操作仅需执行一次。

之前在主循环中我们什么也没绘制，现在终于可以绘制三角形了：

``` cpp
// 1rst attribute buffer : vertices
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
   3,                  // size
   GL_FLOAT,           // type
   GL_FALSE,           // normalized?
   0,                  // stride
   (void*)0            // array buffer offset
);
// Draw the triangle !
glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
glDisableVertexAttribArray(0);
```

结果如图（<span style="color: red">**看不到也别慌哦**</span>）：

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}

白色太单调了。来看看怎么把它染成红色吧。这就要用到“着色器（Shader）”了。

# 着色器（Shader）
## 编译着色器
在最简配置下，您得有两个着色器：一个叫顶点着色器（vertex shader），它将作用于每个顶点上；另一个叫片段着色器（fragment shader），它将作用于每一个采样点。我们采用4倍抗锯齿，因此每个像素有四个采样点。

着色器编程使用GLSL(GL Shading Language)，属于OpenGL的一部分。与C、Java不同，GLSL必须在运行时编译，这意味着每次启动程序时，所有的着色器将重新编译。

这两个着色器通常单独存放在文件里。本例中有`SimpleFragmentShader.fragmentshader`和`SimpleVertexShader.vertexshader`两个着色器。扩展名无关紧要，也可以是.txt或者.glsl。

以下是加载着色器的代码。没必要完全理解，因为在程序中这些操作一般只需执行一次，结合注释能看懂就够了。其他课程代码都用到了这个函数，因此将其放在一个单独的文件中：`common/loadShader.cpp`。注意，着色器和缓冲对象一样不能直接访问：我们仅拥有其ID，其真正的实现隐藏在驱动程序中。

``` cpp
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
```

## 顶点着色器
先写顶点着色器。
第一行告诉编译器我们将用OpenGL 3语法。

``` glsl
#version 330 core
```

第二行声明输入数据：

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```

下面详细解释这一行：

- 在GLSL中“`vec3`”代表一个三维向量。类似但不等同于之前声明三角形的`glm::vec3`。最重要的是，如果我们在C++中使用三维向量，那么在GLSL中也要相应地使用三维向量。
- "`layout(location = 0)`"指向存储`vertexPosition_modelspace`属性（attribute）的缓冲。每个顶点有多种属性：位置，一种或多种颜色，一个或多个纹理坐标等等。OpenGL并不清楚什么是颜色，它只能识别`vec3`这样的数据类型。因此我们必须将`glvertexAttribPointer`函数的第一个参数值赋给`layout`，以此告知OpenGL每个缓冲对应的是哪种属性数据。第二个参数“0”并不重要，也可以换成12（但是不能超过`glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v)）`，关键是C++和GLSL两边数值必须保持一致。
- “`vertexPosition_modelspace`”这个变量名可以任取，其中保存的是顶点位置，顶点着色器每次运行时都会用到。
- “`in`”表明是这是输入数据。不久我们将会看到“out”关键字。


每个顶点都会调用`main`函数（和C语言一样）：

``` glsl
void main(){
```

这里的`main`函数只是简单地将缓冲里的值作为顶点位置。因此如果位置是(1,1)，那么三角形有一个顶点位于屏幕的右上角。
在下一课中我们将看到怎样对输入位置做一些更有趣的计算。


``` glsl
gl_Position.xyz = vertexPosition_modelspace;
gl_Position.w = 1.0;
}
```

gl_Position是仅有的几个内置变量之一：您必须对其赋值。其他操作都是可选的，我们将在第四课中看到究竟有哪些“其他操作”。


## 片段着色器
这就是我们的第一个片段着色器，它仅仅简单将每个片段的颜色设为红色。（记住，我们采用了4倍抗锯齿，因此每个像素有4个片段）

``` glsl
#version 330 core
out vec3 color;

void main(){
color = vec3(1,0,0);
}
```

vec3(1,0,0)代表红色。因为在计算机屏幕上，颜色由红、绿、蓝三元组表示。因此(1,0,0)代表纯红色，无绿、蓝分量。


# 汇总
在主循环之前调用`LoadShaders`函数：

``` cpp
// Create and compile our GLSL program from the shaders
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

首先在主循环中清屏。在进入主循环之前调用了`glClearColor(0.0f, 0.0f, 0.4f, 0.0f)` ，把背景色设为深蓝色。

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

然后让OpenGL使用您的着色器：

``` cpp
// Use our shader
glUseProgram(programID);

// Draw triangle...
```

...然后，哒哒，就看到您亲手绘制的红色三角形啦！

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

下一课中我们将学习变换（transformation）：设置相机，移动物体等等。
