---
layout: page
status: publish
published: true
title: "第九课：VBO索引"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1244
wordpress_url: http://www.opengl-tutorial.org/?page_id=1244
date: '2014-12-05 13:51:20 +0100'
date_gmt: '2014-12-05 13:51:20 +0100'
categories: []
tags: []
---
<h1>索引的原理<&#47;h1><br />
到目前为止，我们在创建VBO时总是重复存储三角形公共边的顶点。</p>
<p>本课将介绍索引。索引是通过<em>索引缓冲（index buffer）<&#47;em>来实现的顶点复用。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;indexing1.png"><img class="alignnone size-full wp-image-267 whiteborder" title="indexing" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;indexing1.png" alt="" width="600" height="375" &#47;><&#47;a></p>
<p>索引缓冲存储的是整数；每个三角形有三个整数索引，分别指向各种<em>属性缓冲（attribute buffer）<&#47;em>顶点位置、颜色、UV坐标、其他UV坐标、法线缓冲法线等）。这和OBJ文件格式有些类似，但一个最大的区别在于：索引缓冲<em>只有一个<&#47;em>。这也就是说仅当某顶点的所有属性（译注：即位置、颜色、UV坐标、法线等等）在两个三角形中都相同时，我们才认为此顶点是两个三角形的公共顶点。</p>
<h1>公共顶点？不同顶点？<&#47;h1><br />
来看看法线的例子。下图中，艺术家创建了两个三角形来表示一个平滑曲面。因此，我们可以把两个三角形的法线混合成一个顶点的法线。为了便于观察，我画了一条红线表示平滑曲面。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;goodsmooth.png"><img class="alignnone size-full wp-image-270" title="goodsmooth" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;goodsmooth.png" alt="" width="400" height="239" &#47;><&#47;a></p>
<p>然而在第二幅图中，艺术家想画的是&ldquo;缝隙&rdquo;或者&ldquo;粗糙的边缘&rdquo;。若混合了法线，就意味着色器会像进行平滑插值，形成一个和上图一样的平滑的表面：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;badmooth.png"><img class="alignnone size-full wp-image-269" title="badmooth" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;badmooth.png" alt="" width="400" height="239" &#47;><&#47;a></p>
<p>因此这种情况下，我们应该为这个顶点设置两条不同的法线；在OpenGL中，唯一可行的办法是把顶点属性完整复制一份。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;spiky.png"><img class="alignnone size-full wp-image-271" title="spiky" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;spiky.png" alt="" width="399" height="239" &#47;><&#47;a></p>
<h1>OpenGL中的索引VBO<&#47;h1><br />
索引的用法很简单。首先，需要再创建一个缓冲来存储索引。代码与之前一样，不过参数由ARRAY_BUFFER变为了ELEMENT_ARRAY_BUFFER。</p>
<pre class="brush: cpp">std::vector indices;</p>
<p>&#47;&#47; fill "indices" as needed</p>
<p>&#47;&#47; Generate a buffer for the indices<br />
 GLuint elementbuffer;<br />
 glGenBuffers(1, &amp;elementbuffer);<br />
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);<br />
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &amp;indices[0], GL_STATIC_DRAW);<&#47;pre><br />
只需把glDrawArrays替换为如下语句，即可绘制模型：</p>
<pre class="brush: cpp">&#47;&#47; Index buffer<br />
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);</p>
<p> &#47;&#47; Draw the triangles !<br />
 glDrawElements(<br />
     GL_TRIANGLES,      &#47;&#47; mode<br />
     indices.size(),    &#47;&#47; count<br />
     GL_UNSIGNED_INT,   &#47;&#47; type<br />
     (void*)0           &#47;&#47; element array buffer offset<br />
 );<&#47;pre><br />
（小提示：最好使用unsigned short，不要用unsigned int。这样更节省空间，速度也更快。）</p>
<h1>填充索引缓冲<&#47;h1><br />
现在真正的问题来了。如前所述，OpenGL只能使用一个索引缓冲，而OBJ（及一些其他常用的3D格式，如Collada）每个属性都有一个索引缓冲。这意味着，必须通过某种方式把若干个索引缓冲合并成一个。</p>
<p>合并算法如下：</p>
<pre class="brush: plain">For each input vertex<br />
    Try to find a similar ( = same for all attributes ) vertex between all those we already output<br />
    If found :<br />
        A similar vertex is already in the VBO, use it instead !<br />
    If not found :<br />
        No similar vertex found, add it to the VBO<&#47;pre><br />
完整的C++代码位于common&#47;vboindexer.cpp，注释很详尽。如果理解了以上算法，读懂代码应该没问题。</p>
<p>若两顶点的坐标、UV坐标和法线都相等，则认为两顶点是同一顶点。若还有其他属性，就得视具体情况而定了。</p>
<p>为了简单，我们采用了性能较差的线性搜索来寻找相似顶点。实际中用std::map更合适。</p>
<h1>补充：FPS计数器<&#47;h1><br />
虽与索引无直接关系，但现在去看看&ldquo;&rdquo;<a title="An FPS counter" href="&#47;?page_id=436">FPS计数器<&#47;a>是很合适的&mdash;&mdash;这样我们就能看到索引究竟能提升多少性能。<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;miscellaneous&#47;useful-tools-links&#47;#header-4">工具&mdash;&mdash;调试器<&#47;a>中还有其他与性能相关的工具。</p>
