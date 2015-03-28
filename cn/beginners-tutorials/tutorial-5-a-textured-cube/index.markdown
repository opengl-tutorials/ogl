---
layout: page
status: publish
published: true
title: "第五课：带纹理的立方体"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 741
wordpress_url: http://www.opengl-tutorial.org/?page_id=741
date: '2014-12-06 10:09:43 +0100'
date_gmt: '2014-12-06 10:09:43 +0100'
categories: []
tags: []
order: 50
---
<p>本课学习如下几点：</p>
<ul>
<li>什么是UV坐标<&#47;li>
<li>怎样自行加载纹理<&#47;li>
<li>怎样在OpenGL中使用纹理<&#47;li>
<li>什么是过滤？什么是mipmap？怎样使用？<&#47;li>
<li>怎样利用GLFW更加鲁棒地加载纹理？<&#47;li>
<li>什么是alpha通道？<&#47;li><br />
<&#47;ul></p>
<h1>关于UV坐标<&#47;h1><br />
给模型贴纹理时，我们需要通过UV坐标来告诉OpenGL用哪块图像填充三角形。</p>
<p>每个顶点除了位置坐标外还有两个浮点数坐标：U和V。这两个坐标用于访问纹理，如下图所示：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;UVintro.png"><img class="alignnone size-full wp-image-116" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;UVintro.png" alt="" width="662" height="337" &#47;><&#47;a></p>
<p>注意观察纹理是怎样在三角形上扭曲的。</p>
<p>&nbsp;</p>
<h1>自行加载.BMP图片<&#47;h1><br />
不用花太多心思了解BMP文件格式：很多库可以帮你加载BMP文件。但BMP格式极为简单，可以帮助你理解那些库的工作原理。所以，我们从头开始写一个BMP文件加载器，不过<strong>千万别在实际工程中使用这个实验品<&#47;strong>。</p>
<p>如下是加载函数的声明：</p>
<pre>GLuint loadBMP_custom(const char * imagepath);<&#47;pre><br />
使用方式如下：</p>
<pre>GLuint image = loadBMP_custom(".&#47;my_texture.bmp");<&#47;pre><br />
接下来看看如何读取BMP文件。</p>
<p>首先需要一些数据。读取文件时将设置这些变量。</p>
<pre>&#47;&#47; Data read from the header of the BMP file<br />
unsigned char header[54]; &#47;&#47; Each BMP file begins by a 54-bytes header<br />
unsigned int dataPos;     &#47;&#47; Position in the file where the actual data begins<br />
unsigned int width, height;<br />
unsigned int imageSize;   &#47;&#47; = width*height*3<br />
&#47;&#47; Actual RGB data<br />
unsigned char * data;<&#47;pre><br />
现在正式开始打开文件。</p>
<pre>&#47;&#47; Open the file<br />
FILE * file = fopen(imagepath,"rb");<br />
if (!file)<br />
{<br />
    printf("Image could not be openedn");<br />
    return 0;<br />
}<&#47;pre><br />
文件一开始是54字节长的文件头，用于标识&ldquo;这是不是一个BMP文件&rdquo;、图像大小、像素位等等。来读取文件头吧：</p>
<pre>if ( fread(header, 1, 54, file)!=54 ){ &#47;&#47; If not 54 bytes read : problem<br />
    printf("Not a correct BMP filen");<br />
    return false;<br />
}<&#47;pre></p>
<p>文件头总是以&ldquo;BM&rdquo;开头。实际上，如果用十六进制编辑器打开BMP文件，您会看到如下情形：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;hexbmp.png"><img class="alignnone size-full wp-image-662" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;hexbmp.png" alt="" width="541" height="128" &#47;><&#47;a></p>
<p>因此得检查一下头两个字节是否确为&lsquo;B&rsquo;和&lsquo;M&rsquo;：</p>
<pre>if ( header[0]!='B' || header[1]!='M' ){<br />
    printf("Not a correct BMP filen");<br />
    return 0;<br />
}<&#47;pre><br />
现在可以读取文件中图像大小、数据位置等信息了：</p>
<pre>&#47;&#47; Read ints from the byte array<br />
dataPos    = *(int*)&amp;(header[0x0A]);<br />
imageSize  = *(int*)&amp;(header[0x22]);<br />
width      = *(int*)&amp;(header[0x12]);<br />
height     = *(int*)&amp;(header[0x16]);<&#47;pre><br />
如果这些信息缺失，您得手动补齐：</p>
<pre>&#47;&#47; Some BMP files are misformatted, guess missing information<br />
if (imageSize==0)    imageSize=width*height*3; &#47;&#47; 3 : one byte for each Red, Green and Blue component<br />
if (dataPos==0)      dataPos=54; &#47;&#47; The BMP header is done that way<&#47;pre><br />
现在我们知道了图像的大小，可以为之分配一些内存，把图像读进去：</p>
<pre>&#47;&#47; Create a buffer<br />
data = new unsigned char [imageSize];</p>
<p>&#47;&#47; Read the actual data from the file into the buffer<br />
fread(data,1,imageSize,file);</p>
<p>&#47;&#47;Everything is in memory now, the file can be closed<br />
fclose(file);<&#47;pre><br />
到了真正的OpenGL部分了。创建纹理和创建顶点缓冲差不多：创建一个纹理、绑定、填充、配置。</p>
<p>在glTexImage2D函数中，GL_RGB表示颜色由三个分量构成，GL_BGR则说明了颜色在内存中的存储格式。实际上，BMP存储的并不是RGB，而是BGR，因此得把这个告诉OpenGL。</p>
<pre>&#47;&#47; Create one OpenGL texture<br />
GLuint textureID;<br />
glGenTextures(1, &amp;textureID);</p>
<p>&#47;&#47; "Bind" the newly created texture : all future texture functions will modify this texture<br />
glBindTexture(GL_TEXTURE_2D, textureID);</p>
<p>&#47;&#47; Give the image to OpenGL<br />
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);</p>
<p>glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);<&#47;pre><br />
稍后再解释最后两行代码。同时，得在C++代码中使用刚写好的函数加载一个纹理：</p>
<pre>GLuint Texture = loadBMP_custom("uvtemplate.bmp");<&#47;pre><br />
另外十分重要的一点：<strong> 使用2次幂（power-of-two）的纹理！<&#47;strong></p>
<ul>
<li>优质纹理： 128*128*, 256*256, 1024*1024, 2*2...<&#47;li>
<li>劣质纹理： 127*128, 3*5, ...<&#47;li>
<li>勉强可以但很怪异的纹理： 128*256<&#47;li><br />
<&#47;ul></p>
<h1>在OpenGL中使用纹理<&#47;h1><br />
先来看看片段着色器。大部分代码一目了然：</p>
<pre>#version 330 core</p>
<p>&#47;&#47; Interpolated values from the vertex shaders<br />
in vec2 UV;</p>
<p>&#47;&#47; Ouput data<br />
out vec3 color;</p>
<p>&#47;&#47; Values that stay constant for the whole mesh.<br />
uniform sampler2D myTextureSampler;</p>
<p>void main(){</p>
<p>    &#47;&#47; Output color = color of the texture at the specified UV<br />
    color = texture( myTextureSampler, UV ).rgb;<br />
}<&#47;pre><br />
注意三点：</p>
<ul>
<li>片段着色器需要UV坐标。看似合情合理。<&#47;li>
<li>同时也需要一个&ldquo;Sampler2D&rdquo;来获知要加载哪一个纹理（同一个着色器中可以访问多个纹理）<&#47;li>
<li>最后一点，用texture()访问纹理，该方法返回一个(R,G,B,A)的vec4变量。马上就会了解到分量A。<&#47;li><br />
<&#47;ul><br />
顶点着色器也很简单，只需把UV坐标传给片段着色器：</p>
<pre>#version 330 core</p>
<p>&#47;&#47; Input vertex data, different for all executions of this shader.<br />
layout(location = 0) in vec3 vertexPosition_modelspace;<br />
layout(location = 1) in vec2 vertexUV;</p>
<p>&#47;&#47; Output data ; will be interpolated for each fragment.<br />
out vec2 UV;</p>
<p>&#47;&#47; Values that stay constant for the whole mesh.<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>    &#47;&#47; Output position of the vertex, in clip space : MVP * position<br />
    gl_Position =&nbsp; MVP * vec4(vertexPosition_modelspace,1);</p>
<p>    &#47;&#47; UV of the vertex. No special space for this one.<br />
    UV = vertexUV;<br />
}<&#47;pre><br />
还记得第四课中的&ldquo;layout(location = 1) in vec2 vertexUV&rdquo;吗？我们得在这儿把相同的事情再做一遍，但这次的缓冲中放的不是(R,G,B)三元组，而是(U,V)数对。</p>
<pre>&#47;&#47; Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.<br />
static const GLfloat g_uv_buffer_data[] = {<br />
    0.000059f, 1.0f-0.000004f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    1.000023f, 1.0f-0.000013f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.999958f, 1.0f-0.336064f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.667969f, 1.0f-0.671889f,<br />
    1.000023f, 1.0f-0.000013f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.000059f, 1.0f-0.000004f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.336098f, 1.0f-0.000071f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    1.000004f, 1.0f-0.671847f,<br />
    0.999958f, 1.0f-0.336064f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.336098f, 1.0f-0.000071f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.000004f, 1.0f-0.671870f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.667969f, 1.0f-0.671889f,<br />
    1.000004f, 1.0f-0.671847f,<br />
    0.667979f, 1.0f-0.335851f<br />
};<&#47;pre><br />
上述UV坐标对应于下面的模型：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;uv_mapping_blender.png"><img class="alignnone size-medium wp-image-115" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;uv_mapping_blender-300x222.png" alt="" width="300" height="222" &#47;><&#47;a></p>
<p>其余的就很清楚了。创建一个缓冲、绑定、填充、配置，像往常一样绘制顶点缓冲对象。要注意把glVertexAttribPointer的第二个参数（大小）3改成2。</p>
<p>结果如下：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering.png"><img class="alignnone size-full wp-image-119" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering.png" alt="" width="533" height="557" &#47;><&#47;a></p>
<p>放大后：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering_zoom.png"><img class="alignnone size-full wp-image-120" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering_zoom.png" alt="" width="348" height="340" &#47;><&#47;a></p>
<h1>什么是过滤和mipmap？怎样使用？<&#47;h1><br />
正如在上面截图中看到的，纹理质量不是很好。这是因为在loadBMP_custom函数中，有如下两行代码：</p>
<pre>glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);<&#47;pre><br />
这意味着在片段着色器中，texture()将直接提取位于(U,V)坐标的纹素（texel）。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearest.png"><img class="alignnone size-full wp-image-130" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearest.png" alt="" width="440" height="240" &#47;><&#47;a></p>
<p>有几种方法可以改善这一状况。</p>
<h2>线性过滤（Linear filtering）<&#47;h2><br />
若采用线性过滤。texture()会查看周围的纹素，然后根据UV坐标距离各纹素中心的距离来混合颜色。这就避免了前面看到的锯齿状边缘。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;linear1.png"><img class="alignnone size-full wp-image-133" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;linear1.png" alt="" width="440" height="240" &#47;><&#47;a></p>
<p>线性过滤可以显著改善纹理质量，应用的也很多。但若想获得更高质量的纹理，可以采用各向异性过滤，不过速度有些慢。</p>
<h2>各向异性过滤（Anisotropic filtering）<&#47;h2><br />
这种方法逼近了真正片断中的纹素区块。例如下图中稍稍旋转了的纹理，各向异性过滤将沿蓝色矩形框的主方向，作一定数量的采样（即所谓的&ldquo;各向异性层级&rdquo;），计算出其内的颜色。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;aniso.png"><img class="alignnone size-full wp-image-131" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;aniso.png" alt="" width="440" height="240" &#47;><&#47;a></p>
<h2>Mipmaps<&#47;h2><br />
线性过滤和各向异性过滤都存在一个共同的问题。那就是如果从远处观察纹理，只对4个纹素作混合显得不够。实际上，如果3D模型位于很远的地方，屏幕上只看得见一个片断（像素），那计算平均值得出最终颜色值时，图像所有的纹素都应该考虑在内。很显然，这种做法没有考虑性能问题。撇开两种过滤方法不谈，这里要介绍的是mipmap技术：</p>
<p><a href="http:&#47;&#47;en.wikipedia.org&#47;wiki&#47;File:MipMap_Example_STS101.jpg"><img class="alignnone" src="http:&#47;&#47;upload.wikimedia.org&#47;wikipedia&#47;commons&#47;5&#47;5c&#47;MipMap_Example_STS101.jpg" alt="" width="384" height="256" &#47;><&#47;a></p>
<ul>
<li>一开始，把图像缩小到原来的1&#47;2，然后依次缩小，直到图像只有1x1大小（应该是图像所有纹素的平均值）<&#47;li>
<li>绘制模型时，根据纹素大小选择合适的mipmap。<&#47;li>
<li>可以选用nearest、linear、anisotropic等任意一种滤波方式来对mipmap采样。<&#47;li>
<li>要想效果更好，可以对两个mipmap采样然后混合，得出结果。<&#47;li><br />
<&#47;ul><br />
好在这个比较简单，OpenGL都帮我们做好了，只需一个简单的调用：</p>
<pre>&#47;&#47; When MAGnifying the image (no bigger mipmap available), use LINEAR filtering<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);<br />
&#47;&#47; When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);<br />
&#47;&#47; Generate mipmaps, by the way.<br />
glGenerateMipmap(GL_TEXTURE_2D);<&#47;pre></p>
<h1>怎样利用GLFW加载纹理？<&#47;h1><br />
我们的loadBMP_custom函数很棒，因为这是我们自己写的！不过用专门的库更好。GLFW就可以加载纹理（仅限TGA文件）：</p>
<pre>GLuint loadTGA_glfw(const char * imagepath){</p>
<p>    &#47;&#47; Create one OpenGL texture<br />
    GLuint textureID;<br />
    glGenTextures(1, &amp;textureID);</p>
<p>    &#47;&#47; "Bind" the newly created texture : all future texture functions will modify this texture<br />
    glBindTexture(GL_TEXTURE_2D, textureID);</p>
<p>    &#47;&#47; Read the file, call glTexImage2D with the right parameters<br />
    glfwLoadTexture2D(imagepath, 0);</p>
<p>    &#47;&#47; Nice trilinear filtering.<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);<br />
    glGenerateMipmap(GL_TEXTURE_2D);</p>
<p>    &#47;&#47; Return the ID of the texture we just created<br />
    return textureID;<br />
}<&#47;pre></p>
<h1>压缩纹理<&#47;h1><br />
学到这儿，您可能会问：那JPEG格式的纹理又该怎样加载呢？</p>
<p>简答：用不着考虑这些文件格式，您还有更好的选择。</p>
<h2>创建压缩纹理<&#47;h2></p>
<ul>
<li>下载<a href="http:&#47;&#47;developer.amd.com&#47;Resources&#47;archive&#47;ArchivedTools&#47;gpu&#47;compressonator&#47;Pages&#47;default.aspx">The Compressonator<&#47;a>,一款ATI工具<&#47;li>
<li>用它加载一个二次幂纹理<&#47;li>
<li>将其压缩成DXT1、DXT3或DXT5格式（这些格式之间的差别请参考<a href="http:&#47;&#47;en.wikipedia.org&#47;wiki&#47;S3_Texture_Compression">Wikipedia<&#47;a>）：<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;TheCompressonator.png"><img class="alignnone size-full wp-image-358" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;TheCompressonator.png" alt="" width="806" height="688" &#47;><&#47;a></p>
<ul>
<li>生成mipmap，这样就不用在运行时生成mipmap了。<&#47;li>
<li>导出为.DDS文件。<&#47;li><br />
<&#47;ul><br />
至此，图像已压缩为可被GPU直接使用的格式。在着色中随时调用texture()均可以实时解压。这一过程看似很慢，但由于它节省了很多内存空间，传输的数据量就少了。传输内存数据开销很大；纹理解压缩却几乎不耗时（有专门的硬件负责此事）。一般情况下，采用压缩纹理可使性能提升20%。</p>
<h2>使用压缩纹理<&#47;h2><br />
来看看怎样加载压缩纹理。这和加载BMP的代码很相似，只不过文件头的结构不一样：</p>
<pre>GLuint loadDDS(const char * imagepath){</p>
<p>&nbsp;&nbsp;&nbsp; unsigned char header[124];</p>
<p>&nbsp;&nbsp;&nbsp; FILE *fp;</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* try to open the file *&#47;<br />
&nbsp;&nbsp;&nbsp; fp = fopen(imagepath, "rb");<br />
&nbsp;&nbsp;&nbsp; if (fp == NULL)<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; return 0;</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* verify the type of file *&#47;<br />
&nbsp;&nbsp;&nbsp; char filecode[4];<br />
&nbsp;&nbsp;&nbsp; fread(filecode, 1, 4, fp);<br />
&nbsp;&nbsp;&nbsp; if (strncmp(filecode, "DDS ", 4) != 0) {<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; fclose(fp);<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; return 0;<br />
&nbsp;&nbsp;&nbsp; }</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* get the surface desc *&#47;<br />
&nbsp;&nbsp;&nbsp; fread(&amp;header, 124, 1, fp); </p>
<p>&nbsp;&nbsp;&nbsp; unsigned int height&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = *(unsigned int*)&amp;(header[8 ]);<br />
&nbsp;&nbsp;&nbsp; unsigned int width&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; = *(unsigned int*)&amp;(header[12]);<br />
&nbsp;&nbsp;&nbsp; unsigned int linearSize&nbsp;&nbsp;&nbsp; &nbsp;= *(unsigned int*)&amp;(header[16]);<br />
&nbsp;&nbsp;&nbsp; unsigned int mipMapCount = *(unsigned int*)&amp;(header[24]);<br />
&nbsp;&nbsp;&nbsp; unsigned int fourCC&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = *(unsigned int*)&amp;(header[80]);<&#47;pre><br />
文件头之后是真正的数据：紧接着是mipmap层级。可以一次性批量地读取：</p>
<p>&nbsp;</p>
<pre>&nbsp;&nbsp;&nbsp; unsigned char * buffer;<br />
&nbsp;&nbsp;&nbsp; unsigned int bufsize;<br />
&nbsp;&nbsp;&nbsp; &#47;* how big is it going to be including all mipmaps? *&#47;<br />
&nbsp;&nbsp;&nbsp; bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;<br />
&nbsp;&nbsp;&nbsp; buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));<br />
&nbsp;&nbsp;&nbsp; fread(buffer, 1, bufsize, fp);<br />
&nbsp;&nbsp;&nbsp; &#47;* close the file pointer *&#47;<br />
&nbsp;&nbsp;&nbsp; fclose(fp);<&#47;pre><br />
这里要处理三种格式：DXT1、DXT3和DXT5。我们得把&ldquo;fourCC&rdquo;标识转换成OpenGL能识别的值。</p>
<pre>&nbsp;&nbsp;&nbsp; unsigned int components&nbsp; = (fourCC == FOURCC_DXT1) ? 3 : 4;<br />
&nbsp;&nbsp;&nbsp; unsigned int format;<br />
&nbsp;&nbsp;&nbsp; switch(fourCC)<br />
&nbsp;&nbsp;&nbsp; {<br />
&nbsp;&nbsp;&nbsp; case FOURCC_DXT1:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; break;<br />
&nbsp;&nbsp;&nbsp; case FOURCC_DXT3:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; break;<br />
&nbsp;&nbsp;&nbsp; case FOURCC_DXT5:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; break;<br />
&nbsp;&nbsp;&nbsp; default:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; free(buffer);<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; return 0;<br />
&nbsp;&nbsp;&nbsp; }<&#47;pre><br />
像往常一样创建纹理：</p>
<pre>&nbsp;&nbsp;&nbsp; &#47;&#47; Create one OpenGL texture<br />
&nbsp;&nbsp;&nbsp; GLuint textureID;<br />
&nbsp;&nbsp;&nbsp; glGenTextures(1, &amp;textureID);</p>
<p>&nbsp;&nbsp;&nbsp; &#47;&#47; "Bind" the newly created texture : all future texture functions will modify this texture<br />
&nbsp;&nbsp;&nbsp; glBindTexture(GL_TEXTURE_2D, textureID);<&#47;pre><br />
现在只需逐个填充mipmap：</p>
<pre>&nbsp;&nbsp;&nbsp; unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;<br />
&nbsp;&nbsp;&nbsp; unsigned int offset = 0;</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* load the mipmaps *&#47;<br />
&nbsp;&nbsp;&nbsp; for (unsigned int level = 0; level < mipMapCount &amp;&amp; (width || height); ++level)<br />
&nbsp;&nbsp;&nbsp; {<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; unsigned int size = ((width+3)&#47;4)*((height+3)&#47;4)*blockSize;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,&nbsp;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; 0, size, buffer + offset);</p>
<p>&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; offset += size;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; width&nbsp; &#47;= 2;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; height &#47;= 2;<br />
&nbsp;&nbsp;&nbsp; }<br />
&nbsp;&nbsp;&nbsp; free(buffer); </p>
<p>&nbsp;&nbsp;&nbsp; return textureID;<&#47;pre></p>
<h2>反转UV坐标<&#47;h2><br />
DXT压缩源自DirectX。和OpenGL相比，DirectX中的V纹理坐标是反过来的。所以使用压缩纹理时，得用(coord.v, 1.0-coord.v)来获取正确的纹素。可以在导出脚本、加载器、着色器等环节中执行这步操作</p>
<h1>总结<&#47;h1><br />
刚才我们学习了创建、加载以及在OpenGL中使用纹理。</p>
<p>总的来说，压缩纹理体积小、加载迅速、使用便捷，应该只用压缩纹理；主要的缺点是得用The Compressonator来转换图像格式。</p>
<h1>练习<&#47;h1></p>
<ul>
<li>源代码中实现了DDS加载器，但没有做纹理坐标的改动（译者注：指文中讲述的反转 UV坐标）。在适当的位置添加该功能，以使正方体正确显示。<&#47;li>
<li>试试各种DDS格式。所得结果有何不同？压缩率呢？<&#47;li>
<li>试试在The Compressonator不生成mipmap。结果如何？请给出3种方案解决这一问题。<&#47;li><br />
<&#47;ul></p>
<h1>参考文献<&#47;h1></p>
<ul>
<li><a href="http:&#47;&#47;www.oldunreal.com&#47;editing&#47;s3tc&#47;ARB_texture_compression.pdf">Using texture compression in OpenGL<&#47;a> , S&eacute;bastien Domine, NVIDIA<&#47;li><br />
<&#47;ul></p>
