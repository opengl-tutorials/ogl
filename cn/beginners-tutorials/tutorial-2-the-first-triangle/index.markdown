---
layout: page
status: publish
published: true
title: "第二课：画第一个三角形"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 718
wordpress_url: http://www.opengl-tutorial.org/?page_id=718
date: '2014-12-06 09:33:17 +0100'
date_gmt: '2014-12-06 09:33:17 +0100'
categories: []
tags: []
order: 20
language: cn
---
<p><!-- Include required JS files --><br />
<!--     At least one brush, here we choose JS. You need to include a brush for every     language you want to highlight --></p>
<p>本课依然是&ldquo;长篇大论&rdquo;。</p>
<p>用OpenGL 3绘制复杂的物体很方便，绘制一个简单的三角形却十分麻烦。</p>
<p>别忘了不时地复制粘贴代码，动手调试。</p>
<blockquote><p><span style="color: #ff0000">如果程序启动时崩溃了，很可能是您的运行目录有误。请仔细阅读第一课中讲到的Visual Studio配置方法！<&#47;span><&#47;blockquote></p>
<h1>顶点数组对象(VAO)<&#47;h1><br />
您得创建一个VAO，并将它设为当前对象（暂不详细展开）：</p>
<pre>GLuint VertexArrayID;<br />
glGenVertexArrays(1, &amp;VertexArrayID);<br />
glBindVertexArray(VertexArrayID);<&#47;pre><br />
窗口创建成功后（即OpenGL上下文创建后）紧接着完成上述动作；这一步必须在其他OpenGL调用前完成。</p>
<p>若想进一步了解顶点数组对象（VAO）可以参考其他教程，不过VAO不是很重要。</p>
<h1>屏幕坐标系<&#47;h1><br />
三点确定一个三角形。我们常常用&ldquo;顶点&rdquo;（Vertex，复数vertices）来指代3D图形学中的点。一个顶点有三个坐标：X，Y和Z。您可以这样想象这三根坐标轴：</p>
<ul>
<li>X轴朝右<&#47;li>
<li>Y轴朝上<&#47;li>
<li>Z轴指向您后面（没错，是后面，不是前面）<&#47;li><br />
<&#47;ul><br />
还有更形象的方法：使用右手定则</p>
<ul>
<li>拇指代表X轴<&#47;li>
<li>食指代表Y轴<&#47;li>
<li>中指代表Z轴。如果您的拇指指向右边，食指指向天空，那么中指将指向您的后面。<&#47;li><br />
<&#47;ul><br />
为什么Z轴方向这么奇怪呢？简言之：因为基于右手定则的坐标系统被广泛使用了100多年，这一系统涵盖了许多实用工具，唯一的缺点就是Z方向比较别扭。</p>
<p>补充说明一下，您的手可以自由移动，X轴，Y轴和Z轴同样也能移动（详见后文）。</p>
<p>我们需要三个三维点来组成一个三角形；下面来定义一个三角形：</p>
<pre>&#47;&#47; An array of 3 vectors which represents 3 vertices<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
   -1.0f, -1.0f, 0.0f,<br />
   1.0f, -1.0f, 0.0f,<br />
   0.0f,? 1.0f, 0.0f,<br />
};<&#47;pre><br />
第一个顶点是(-1, -1, 0)。<br />
这意味着<em>如果不变换该顶点<&#47;em>，它就将显示在屏幕的(-1, -1)位置。这是什么意思呢？屏幕的原点在中间，X轴朝右，Y轴朝上。屏幕坐标如下图：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;screenCoordinates.png"><img class="alignnone size-medium wp-image-16" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;screenCoordinates-300x165.png" alt="" width="300" height="165" &#47;><&#47;a></p>
<p>这是显卡内置的坐标系，无法改变。(-1, -1)是屏幕的左下角，(1, -1)是右下角，(0, 1)位于中上部。这个三角形占据了大部分屏幕。</p>
<h1>绘制三角形<&#47;h1><br />
下一步，通过缓冲把三角形传给OpenGL：</p>
<pre>&#47;&#47; This will identify our vertex buffer<br />
GLuint vertexbuffer;</p>
<p>&#47;&#47; Generate 1 buffer, put the resulting identifier in vertexbuffer<br />
glGenBuffers(1, &amp;vertexbuffer);</p>
<p>&#47;&#47; The following commands will talk about our 'vertexbuffer' buffer<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);</p>
<p>&#47;&#47; Give our vertices to OpenGL.<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);<&#47;pre><br />
这步操作仅需执行一次。<br />
之前在主循环中我们什么也没绘制，现在终于可以绘制三角形了：</p>
<pre>&#47;&#47; 1rst attribute buffer : vertices<br />
glEnableVertexAttribArray(0);<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);<br />
glVertexAttribPointer(<br />
   0,                  &#47;&#47; attribute 0. No particular reason for 0, but must match the layout in the shader.<br />
   3,                  &#47;&#47; size<br />
   GL_FLOAT,           &#47;&#47; type<br />
   GL_FALSE,           &#47;&#47; normalized?<br />
   0,                  &#47;&#47; stride<br />
   (void*)0            &#47;&#47; array buffer offset<br />
);</p>
<p>&#47;&#47; Draw the triangle !<br />
glDrawArrays(GL_TRIANGLES, 0, 3); &#47;&#47; Starting from vertex 0; 3 vertices total -> 1 triangle</p>
<p>glDisableVertexAttribArray(0);<&#47;pre><br />
结果如图（看不到也别慌哦）：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;triangle_no_shader.png"><img class="alignnone size-medium wp-image-17" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;triangle_no_shader-300x232.png" alt="" width="300" height="232" &#47;><&#47;a></p>
<p>白色太单调了。来看看怎么把它染成红色吧。这就要用到&ldquo;着色器（Shader）&rdquo;了。</p>
<h1>着色器（Shader）<&#47;h1></p>
<h2>编译着色器<&#47;h2><br />
在最简配置下，您得有两个着色器：一个叫顶点着色器（vertex shader），它将作用于每个顶点上；另一个叫片段着色器（fragment shader），它将作用于每一个采样点。我们采用4倍抗锯齿，因此每个像素有四个采样点。</p>
<p>着色器编程使用GLSL(GL Shading Language)，属于OpenGL的一部分。与C、Java不同，GLSL必须在运行时编译，这意味着每次启动程序时，所有的着色器将重新编译。</p>
<p>这两个着色器通常单独存放在文件里。本例中有SimpleFragmentShader.fragmentshader和SimpleVertexShader.vertexshader两个着色器。扩展名无关紧要，也可以是.txt或者.glsl。</p>
<p>以下是加载着色器的代码。没必要完全理解，因为在程序中这些操作一般只需执行一次，结合注释能看懂就够了。其他课程代码都用到了这个函数，因此将其放在一个单独的文件中：common&#47;loadShader.cpp。注意，着色器和缓冲对象一样不能直接访问：我们仅拥有其ID，其真正的实现隐藏在驱动程序中。</p>
<pre>GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){</p>
<p>    &#47;&#47; Create the shaders<br />
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);<br />
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);</p>
<p>    &#47;&#47; Read the Vertex Shader code from the file<br />
    std::string VertexShaderCode;<br />
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);<br />
    if(VertexShaderStream.is_open())<br />
    {<br />
        std::string Line = "";<br />
        while(getline(VertexShaderStream, Line))<br />
            VertexShaderCode += "n" + Line;<br />
        VertexShaderStream.close();<br />
    }</p>
<p>    &#47;&#47; Read the Fragment Shader code from the file<br />
    std::string FragmentShaderCode;<br />
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);<br />
    if(FragmentShaderStream.is_open()){<br />
        std::string Line = "";<br />
        while(getline(FragmentShaderStream, Line))<br />
            FragmentShaderCode += "n" + Line;<br />
        FragmentShaderStream.close();<br />
    }</p>
<p>    GLint Result = GL_FALSE;<br />
    int InfoLogLength;</p>
<p>    &#47;&#47; Compile Vertex Shader<br />
    printf("Compiling shader : %sn", vertex_file_path);<br />
    char const * VertexSourcePointer = VertexShaderCode.c_str();<br />
    glShaderSource(VertexShaderID, 1, &amp;VertexSourcePointer , NULL);<br />
    glCompileShader(VertexShaderID);</p>
<p>    &#47;&#47; Check Vertex Shader<br />
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector VertexShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &amp;VertexShaderErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;VertexShaderErrorMessage[0]);</p>
<p>    &#47;&#47; Compile Fragment Shader<br />
    printf("Compiling shader : %sn", fragment_file_path);<br />
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();<br />
    glShaderSource(FragmentShaderID, 1, &amp;FragmentSourcePointer , NULL);<br />
    glCompileShader(FragmentShaderID);</p>
<p>    &#47;&#47; Check Fragment Shader<br />
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector FragmentShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &amp;FragmentShaderErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;FragmentShaderErrorMessage[0]);</p>
<p>    &#47;&#47; Link the program<br />
    fprintf(stdout, "Linking programn");<br />
    GLuint ProgramID = glCreateProgram();<br />
    glAttachShader(ProgramID, VertexShaderID);<br />
    glAttachShader(ProgramID, FragmentShaderID);<br />
    glLinkProgram(ProgramID);</p>
<p>    &#47;&#47; Check the program<br />
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &amp;Result);<br />
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector ProgramErrorMessage( max(InfoLogLength, int(1)) );<br />
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &amp;ProgramErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;ProgramErrorMessage[0]);</p>
<p>    glDeleteShader(VertexShaderID);<br />
    glDeleteShader(FragmentShaderID);</p>
<p>    return ProgramID;<br />
}<&#47;pre></p>
<h2>顶点着色器<&#47;h2><br />
先写顶点着色器。<br />
第一行告诉编译器我们将用OpenGL 3的语法。</p>
<pre>#version 330 core<&#47;pre><br />
第二行声明输入数据：</p>
<pre>layout(location = 0) in vec3 vertexPosition_modelspace;<&#47;pre><br />
下面详细解释这一行：</p>
<ul>
<li>在GLSL中&ldquo;vec3&rdquo;代表一个三维向量。类似但不等同于之前声明三角形的glm::vec3。最重要的是，如果我们在C++中使用三维向量，那么在GLSL中也要相应地使用三维向量。<&#47;li>
<li>"layout(location = 0)"指向存储vertexPosition_modelspace属性（attribute）的缓冲。每个顶点有多种属性：位置，一种或多种颜色，一个或多个纹理坐标等等。OpenGL并不清楚什么是颜色，它只能识别vec3这样的数据类型。因此我们必须将glvertexAttribPointer函数的第一个参数值赋给layout，以此告知OpenGL每个缓冲对应的是哪种属性数据。第二个参数&ldquo;0&rdquo;并不重要，也可以换成12（但是不能超过glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &amp;v)），关键是C++和GLSL两边数值必须保持一致。<&#47;li>
<li>&ldquo;vertexPosition_modelspace&rdquo;这个变量名可以任取，其中保存的是顶点位置，顶点着色器每次运行时都会用到。<&#47;li>
<li>&ldquo;in&rdquo;表明是这是输入数据。不久我们将会看到&ldquo;out&rdquo;关键字。<&#47;li><br />
<&#47;ul><br />
每个顶点都会调用main函数（和C语言一样）：</p>
<pre>void main(){<&#47;pre><br />
这里的main函数只是简单地将缓冲里的值作为顶点位置。因此如果位置是(1,1)，那么三角形有一个顶点位于屏幕的右上角。 在下一课中我们将看到怎样对输入位置做一些更有趣的计算。</p>
<pre>    gl_Position.xyz = vertexPosition_modelspace;<br />
}<&#47;pre><br />
gl_Position是仅有的几个内置变量之一：您必须对其赋值。其他操作都是可选的，我们将在第四课中看到究竟有哪些&ldquo;其他操作&rdquo;。 </p>
<h2>片段着色器<&#47;h2><br />
这就是我们的第一个片段着色器，它仅仅简单将每个片段的颜色设为红色。（记住，我们采用了4倍抗锯齿，因此每个像素有4个片段）</p>
<pre>out vec3 color;</p>
<p>void main(){<br />
    color = vec3(1,0,0);<br />
}<&#47;pre><br />
vec3(1,0,0)代表红色。因为在计算机屏幕上，颜色由红、绿、蓝三元组表示。因此(1,0,0)代表纯红色，无绿、蓝分量。</p>
<h1>汇总<&#47;h1><br />
在主循环之前调用LoadShaders函数：</p>
<pre>&#47;&#47; Create and compile our GLSL program from the shaders<br />
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );<&#47;pre><br />
首先在主循环中清屏。在进入主循环之前调用了glClearColor(0.0f, 0.0f, 0.4f, 0.0f) ，把背景色设为深蓝色。</p>
<pre>glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);<&#47;pre><br />
然后让OpenGL使用您的着色器：</p>
<pre>&#47;&#47; Use our shader<br />
glUseProgram(programID);</p>
<p>&#47;&#47; Draw triangle...<&#47;pre><br />
...然后，哒哒，就看到您亲手绘制的红色三角形啦！</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;red_triangle.png"><img class="alignnone size-medium wp-image-15" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;red_triangle-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<p>下一课中我们将学习变换（transformation）：设置相机，移动物体等等。</p>
