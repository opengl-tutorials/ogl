---
layout: page
status: publish
published: true
title: "第十课：透明"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1356
wordpress_url: http://www.opengl-tutorial.org/?page_id=1356
date: '2014-12-05 15:03:48 +0100'
date_gmt: '2014-12-05 15:03:48 +0100'
categories: []
tags: []
language: cn
---
<h1>alpha通道<&#47;h1><br />
alpha通道的概念很简单。我们以前的计算结果是RGB值，现在则是RGBA值：</p>
<pre class="brush:fs">&#47;&#47; Ouput data : it's now a vec4<br />
out vec4 color;<&#47;pre><br />
前三个分量仍可以通过重组操作符（swizzle operator）.xyz访问，最后一个分量通过.a访问：</p>
<pre class="brush:fs">color.a = 0.3;<&#47;pre><br />
与直觉相反，alpha代表的是不透明度；因此alpha = 1代表完全不透明，alpha = 0为完全透明。</p>
<p>这里我们简单地将alpha硬编码为0.3；但更常见的做法是用一个uniform变量表示它，或从RGBA纹理中读取（TGA格式支持alpha通道，而GLFW支持TGA格式）。</p>
<p>结果如下。既然我们能&ldquo;看透&rdquo;模型表面，请确保关闭背面剔除（glDisable(GL_CULL_FACE) ）。否则我们就发现模型没有了&ldquo;背&rdquo;面。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transparencyok.png"><img class="alignnone size-large wp-image-289" title="transparencyok" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transparencyok-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<h1>顺序很重要！<&#47;h1><br />
上一个截图看上去还行，但这仅仅是运气好罢了。</p>
<h2>问题所在<&#47;h2><br />
这里我画了一红一绿两个alpha值为50%的正方形。从中可以看出顺序的重要性，最终的颜色显著影响了眼睛对深度的感知。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transparencyorder.png"><img class="alignnone size-full wp-image-282" title="transparencyorder" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transparencyorder.png" alt="" width="500" height="255" &#47;><&#47;a></p>
<p>我们的场景中也出现了同样的现象。试着稍稍改变一下观察点：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transparencybad.png"><img class="alignnone size-large wp-image-288" title="transparencybad" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transparencybad-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>原来这还是个十分棘手的问题。您在游戏中也没怎么见过透明的东西，是吧？</p>
<h2>常见解决方案<&#47;h2><br />
常见解决方案即对所有的透明三角形排序。是的，所有的透明三角形。</p>
<ul>
<li>渲染场景的不透明部分，让深度缓冲丢弃被遮挡的透明三角形。<&#47;li>
<li>对透明三角形按深度由远及近排序。<&#47;li>
<li>渲染透明三角形。<&#47;li><br />
<&#47;ul><br />
可以用C语言的qsort函数或者C++的std::sort函数来排序。细节就不多说了，因为&hellip;&hellip;</p>
<h2>警告<&#47;h2><br />
这么做可以解决问题（下一节还会介绍它），但是：</p>
<ul>
<li>您将受限于填充率。亦即每个片段会写10、20次，也许更多次。这对力不从心的内存总线来说太繁重了。通常，深度缓冲可以自动丢弃&ldquo;远&rdquo;片段；但这里我们已显式地对片段进行了排序，因此深度缓冲实际上没起作用。<&#47;li>
<li>这些操作，每个像素上都会执行4遍（我们用了4倍多重采样抗锯齿（MSAA）），除非用了什么巧妙的优化。<&#47;li>
<li>透明三角形排序很耗时<&#47;li>
<li>若要逐个三角形地切换纹理，或者更糟糕，切换着色器&mdash;&mdash;性能会大打折扣。不要这么做。<&#47;li><br />
<&#47;ul><br />
一个足够好的解决方案是：</p>
<ul>
<li>限制透明多边形的数量<&#47;li>
<li>对所有透明多边形使用同一个着色器和纹理<&#47;li>
<li>若这些透明多边形本就是外表各异的，那就用不同的纹理<&#47;li>
<li>若不排序时效果还<em>凑合<&#47;em>，那就不排序好了。<&#47;li><br />
<&#47;ul></p>
<h2>顺序无关透明<&#47;h2><br />
如果您的引擎确实需要顶级的透明效果，这里有一些值得研究的技术：</p>
<ul>
<li><a href="http:&#47;&#47;citeseerx.ist.psu.edu&#47;viewdoc&#47;download?doi=10.1.1.18.9286&amp;rep=rep1&amp;type=pdf">The original 2001 Depth Peeling paper<&#47;a>：像素级精细度，但速度不快。<&#47;li>
<li><a href="http:&#47;&#47;developer.download.nvidia.com&#47;SDK&#47;10&#47;opengl&#47;src&#47;dual_depth_peeling&#47;doc&#47;DualDepthPeeling.pdf">Dual Depth Peeling<&#47;a>：小幅改进<&#47;li>
<li>桶排序相关的几篇论文。把片段存到数组，在着色器中进行深度排序。<&#47;li>
<li><a href="http:&#47;&#47;fr.slideshare.net&#47;hgruen&#47;oit-and-indirect-illumination-using-dx11-linked-lists">ATI's Mecha Demo<&#47;a>：效果速度俱佳，但实现起来有难度，需要最新的硬件。用链表存储片段。<&#47;li>
<li><a href="http:&#47;&#47;blog.icare3d.org&#47;2010&#47;07&#47;opengl-40-abuffer-v20-linked-lists-of.html">Cyril Crassin's variation on the ATI's&nbsp; technique<&#47;a>：实现难度更大<&#47;li><br />
<&#47;ul><br />
注意，即便是《小小大星球》（<em>Little Big Planet<&#47;em>）这种刚出炉的、运行在高端主机上的游戏，也只用了一层透明。</p>
<h1>混合函数<&#47;h1><br />
要让上述代码运行起来，得设置好混合函数。</p>
<pre class="brush:cpp">&#47;&#47; Enable blending<br />
glEnable(GL_BLEND);<br />
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);<&#47;pre><br />
这意味着</p>
<pre class="brush:plain">New color in framebuffer =<br />
           current alpha in framebuffer * current color in framebuffer +<br />
           (1 - current alpha in framebuffer) * shader's output color<&#47;pre><br />
上图红色方块居上的效果由如下等式得来：</p>
<pre class="brush:plain">new color = 0.5*(0,1,0) + (1-0.5)*(1,0.5,0.5); &#47;&#47; (the red was already blended with the white background)<br />
new color = (1, 0.75, 0.25) = the same orange<br />
<&#47;pre><br />
&nbsp;</p>
<p>&nbsp;</p>
