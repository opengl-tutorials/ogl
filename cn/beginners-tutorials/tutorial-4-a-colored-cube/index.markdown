---
layout: page
status: publish
published: true
title: "第四课：彩色立方体"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 725
wordpress_url: http://www.opengl-tutorial.org/?page_id=725
date: '2014-12-06 09:46:18 +0100'
date_gmt: '2014-12-06 09:46:18 +0100'
categories: []
tags: []
order: 40
---
<p>欢迎来到第四课！您将学到：</p>
<ul>
<li>绘制立方体，向单调的三角形说再见<&#47;li>
<li>加上绚丽的色彩<&#47;li>
<li>深度缓冲（Z-Buffer）<&#47;li><br />
<&#47;ul></p>
<h1>绘制立方体<&#47;h1><br />
立方体有六个方形表面，而OpenGL只支持画三角形，因此需要画12个三角形，每个面两个。我们用定义三角形顶点的方式来定义这些顶点。</p>
<pre>&#47;&#47; Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.<br />
&#47;&#47; A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
-1.0f,-1.0f,-1.0f, &#47;&#47; triangle 1 : begin<br />
-1.0f,-1.0f, 1.0f,<br />
-1.0f, 1.0f, 1.0f, &#47;&#47; triangle 1 : end<br />
1.0f, 1.0f,-1.0f, &#47;&#47; triangle 2 : begin<br />
-1.0f,-1.0f,-1.0f,<br />
-1.0f, 1.0f,-1.0f, &#47;&#47; triangle 2 : end<br />
1.0f,-1.0f, 1.0f,<br />
-1.0f,-1.0f,-1.0f,<br />
1.0f,-1.0f,-1.0f,<br />
1.0f, 1.0f,-1.0f,<br />
1.0f,-1.0f,-1.0f,<br />
-1.0f,-1.0f,-1.0f,<br />
-1.0f,-1.0f,-1.0f,<br />
-1.0f, 1.0f, 1.0f,<br />
-1.0f, 1.0f,-1.0f,<br />
1.0f,-1.0f, 1.0f,<br />
-1.0f,-1.0f, 1.0f,<br />
-1.0f,-1.0f,-1.0f,<br />
-1.0f, 1.0f, 1.0f,<br />
-1.0f,-1.0f, 1.0f,<br />
1.0f,-1.0f, 1.0f,<br />
1.0f, 1.0f, 1.0f,<br />
1.0f,-1.0f,-1.0f,<br />
1.0f, 1.0f,-1.0f,<br />
1.0f,-1.0f,-1.0f,<br />
1.0f, 1.0f, 1.0f,<br />
1.0f,-1.0f, 1.0f,<br />
1.0f, 1.0f, 1.0f,<br />
1.0f, 1.0f,-1.0f,<br />
-1.0f, 1.0f,-1.0f,<br />
1.0f, 1.0f, 1.0f,<br />
-1.0f, 1.0f,-1.0f,<br />
-1.0f, 1.0f, 1.0f,<br />
1.0f, 1.0f, 1.0f,<br />
-1.0f, 1.0f, 1.0f,<br />
1.0f,-1.0f, 1.0f<br />
};<&#47;pre><br />
OpenGL的缓冲由一些标准的函数（glGenBuffers, glBindBuffer, glBufferData, glVertexAttribPointer）来创建、绑定、填充和配置；这些可参阅第二课。若有遗忘，可参见第二课。绘制的调用也没变，只需改变绘制的点的个数：</p>
<pre>&#47;&#47; Draw the triangle !<br />
glDrawArrays(GL_TRIANGLES, 0, 12*3); &#47;&#47; 12*3 indices starting at 0 -> 12 triangles -> 6 squares<&#47;pre><br />
关于这段代码，有几点要说明一下：</p>
<ul>
<li>截至目前我们使用的三维模型都是固定的：只能在源码中修改模型，重新编译，然后祈祷不要出什么差错。我们将在第七课中学习如何动态地加载模型。<&#47;li>
<li>实际上，每个顶点至少出现了三次（在以上代码中搜索&ldquo;-1.0f,-1.0f,-1.0f&rdquo;看看）。这严重浪费了内存空间。我们将在第九课中学习怎样对此进行优化。<&#47;li><br />
<&#47;ul><br />
现在您已具备绘制一个白色立方体的所有条件。试着让着色器运行起来吧:)</p>
<h1>增色添彩<&#47;h1><br />
从概念上讲，颜色与位置是一回事：就是数据嘛。OpenGL术语中称之为&ldquo;属性（attribute）&rdquo;。其实我们之前已用glEnableVertexAttribArray()和glVertexAttribPointer()设置过属性了。现在加上颜色属性，代码很相似。</p>
<p>首先声明颜色：每个顶点一个RGB三元组。这里随机生成一些颜色，所以效果看起来可能不太好；您可以调整得更好些，例如把顶点的位置作为颜色值。</p>
<pre>&#47;&#47; One color for each vertex. They were generated randomly.<br />
static const GLfloat g_color_buffer_data[] = {<br />
0.583f, 0.771f, 0.014f,<br />
0.609f, 0.115f, 0.436f,<br />
0.327f, 0.483f, 0.844f,<br />
0.822f, 0.569f, 0.201f,<br />
0.435f, 0.602f, 0.223f,<br />
0.310f, 0.747f, 0.185f,<br />
0.597f, 0.770f, 0.761f,<br />
0.559f, 0.436f, 0.730f,<br />
0.359f, 0.583f, 0.152f,<br />
0.483f, 0.596f, 0.789f,<br />
0.559f, 0.861f, 0.639f,<br />
0.195f, 0.548f, 0.859f,<br />
0.014f, 0.184f, 0.576f,<br />
0.771f, 0.328f, 0.970f,<br />
0.406f, 0.615f, 0.116f,<br />
0.676f, 0.977f, 0.133f,<br />
0.971f, 0.572f, 0.833f,<br />
0.140f, 0.616f, 0.489f,<br />
0.997f, 0.513f, 0.064f,<br />
0.945f, 0.719f, 0.592f,<br />
0.543f, 0.021f, 0.978f,<br />
0.279f, 0.317f, 0.505f,<br />
0.167f, 0.620f, 0.077f,<br />
0.347f, 0.857f, 0.137f,<br />
0.055f, 0.953f, 0.042f,<br />
0.714f, 0.505f, 0.345f,<br />
0.783f, 0.290f, 0.734f,<br />
0.722f, 0.645f, 0.174f,<br />
0.302f, 0.455f, 0.848f,<br />
0.225f, 0.587f, 0.040f,<br />
0.517f, 0.713f, 0.338f,<br />
0.053f, 0.959f, 0.120f,<br />
0.393f, 0.621f, 0.362f,<br />
0.673f, 0.211f, 0.457f,<br />
0.820f, 0.883f, 0.371f,<br />
0.982f, 0.099f, 0.879f<br />
};<&#47;pre><br />
缓冲的创建、绑定和填充方法与之前一样：</p>
<pre>GLuint colorbuffer;<br />
glGenBuffers(1, &amp;colorbuffer);<br />
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);<&#47;pre><br />
配置也一样：</p>
<pre>&#47;&#47; 2nd attribute buffer : colors<br />
glEnableVertexAttribArray(1);<br />
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);<br />
glVertexAttribPointer(<br />
1, &#47;&#47; attribute. No particular reason for 1, but must match the layout in the shader.<br />
3, &#47;&#47; size<br />
GL_FLOAT, &#47;&#47; type<br />
GL_FALSE, &#47;&#47; normalized?<br />
0, &#47;&#47; stride<br />
(void*)0 &#47;&#47; array buffer offset<br />
);<&#47;pre><br />
现在在顶点着色器中已经能访问这个新增的缓冲了：</p>
<pre>&#47;&#47; Notice that the "1" here equals the "1" in glVertexAttribPointer<br />
layout(location = 1) in vec3 vertexColor;<&#47;pre><br />
这一课的顶点着色器没有什么复杂的效果，仅仅是简单地把颜色传递到片段着色器：</p>
<pre>&#47;&#47; Output data ; will be interpolated for each fragment.<br />
out vec3 fragmentColor;</p>
<p>void main(){</p>
<p>[...]</p>
<p>&#47;&#47; The color of each vertex will be interpolated<br />
&#47;&#47; to produce the color of each fragment<br />
fragmentColor = vertexColor;<br />
}<&#47;pre><br />
在片段着色器中要再次声明片段颜色：</p>
<pre>&#47;&#47; Interpolated values from the vertex shaders<br />
in vec3 fragmentColor;<&#47;pre><br />
然后将其拷贝到输出颜色：</p>
<pre>&#47;&#47; Output color = color specified in the vertex shader,<br />
&#47;&#47; interpolated between all 3 surrounding vertices<br />
color = fragmentColor;<&#47;pre><br />
于是得到：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;missing_z_buffer.png"><img class="alignnone size-medium wp-image-107" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;missing_z_buffer-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<p>呃，太难看了。为了搞清楚出现这种情况原因，我们先看看画一个&ldquo;远&rdquo;和&ldquo;近&rdquo;的三角形会发生什么：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;FarNear.png"><img class="alignnone size-full wp-image-109" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;FarNear.png" alt="" width="189" height="94" &#47;><&#47;a></p>
<p>似乎挺好。现在画&ldquo;远&rdquo;三角形：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;NearFar.png"><img class="alignnone size-full wp-image-110" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;NearFar.png" alt="" width="189" height="94" &#47;><&#47;a></p>
<p>它遮住了&ldquo;近&rdquo;三角形！它本应该在&ldquo;近&rdquo;三角形后面的！我们的立方体问题就在这里：一些理应被遮挡的面，因为绘制次序靠后，竟然变成可见的了。我们将用深度缓冲（Z-Buffer）算法解决它。</p>
<p><em>便签1<&#47;em><br />
: 如果您没发现问题，把摄像机放到(4,3,-3)试试</p>
<p><em>便签2<&#47;em><br />
: 如果&ldquo;颜色和位置同为属性&rdquo;，那为什么颜色要声明 out vec3 fragmentColor，而位置不需要？实际上，位置有点特殊：它是唯一必须赋初值的（否则OpenGL不知道在哪画三角形）。所以在顶点着色器里， gl_Position是内置变量。</p>
<h1>深度缓冲（Z-Buffer）The Z-Buffer<&#47;h1><br />
该问题的解决方案是：在缓冲中存储每个片段的深度（即&ldquo;Z&rdquo;值）；并且每次绘制片段之前要比较当前与先前片段的深度值，看谁离摄像机更近。</p>
<p>您可以自己实现深度缓冲，但让硬件自动完成更简单：</p>
<pre>&#47;&#47; Enable depth test<br />
glEnable(GL_DEPTH_TEST);<br />
&#47;&#47; Accept fragment if it closer to the camera than the former one<br />
glDepthFunc(GL_LESS);<&#47;pre><br />
问题解决了。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;one_color_per_vertex.png"><img class="alignnone size-medium wp-image-108" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;one_color_per_vertex-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<h1>练习<&#47;h1></p>
<ul>
<li>在不同的位置画立方体<strong>和<&#47;strong>三角形。您得构造两个MVP矩阵，在主循环中进行两次绘制调用，但只需一个着色器。<&#47;li><br />
<&#47;ul></p>
<ul>
<li>自己生成颜色值。一些点子：随机生成颜色，这样每次运行时颜色都不同；根据顶点位置生成颜色；把前面两种思路结合起来；或其他创意:)。若您不了解C，参考以下语法：<&#47;li><br />
<&#47;ul></p>
<pre>static GLfloat g_color_buffer_data[12*3*3];<br />
for (int v = 0; v < 12*3 ; v++){<br />
g_color_buffer_data[3*v+0] = your red color here;<br />
g_color_buffer_data[3*v+1] = your green color here;<br />
g_color_buffer_data[3*v+2] = your blue color here;<br />
}<&#47;pre></p>
<ul>
<li>完成上面习题后，尝试每帧都改变颜色。您得在每帧都调用`glBufferData`。请确保已绑定（`glBindBuffer`）了合适的缓冲！<&#47;li><br />
<&#47;ul></p>
