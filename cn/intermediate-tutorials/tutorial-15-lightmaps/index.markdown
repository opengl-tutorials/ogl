---
layout: page
status: publish
published: true
title: "第十五课：光照贴图（Lightmap）"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1360
wordpress_url: http://www.opengl-tutorial.org/?page_id=1360
date: '2014-12-13 03:20:09 +0100'
date_gmt: '2014-12-13 03:20:09 +0100'
categories: []
tags: []
language: cn
---
<h1>简介<&#47;h1><br />
这节视频课程不介绍新的OpenGL技术&#47;语法，而是教大家用已学到的技术生成高质量的阴影。</p>
<p>本课介绍怎样用Blender创建简单场景；还介绍了如何烘培光照贴图，并应用到实际中。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;lighmappedroom.png"><img class="alignnone size-large wp-image-345" title="lighmappedroom" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;lighmappedroom-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a><br />
本课不需要Blender预备知识，我会讲解快捷键等内容。</p>
<h1>关于光照贴图<&#47;h1><br />
光照贴图是预先一次性烘焙好的。也就是说光照贴图完全是静态的，你不能实时地移动甚至删除光源。</p>
<p>但对于阳光这种光源来说，光照贴图还是大有用处的；在灯泡不会破碎的室内场景中，也可以用光照贴图。2009年发布的《镜之边缘》（<em>Mirror Edge<&#47;em>）室内外场景就大量采用了光照贴图。</p>
<p>更重要的是，光照贴图很容易配置，渲染速度无出其右。</p>
<h1>视频<&#47;h1><br />
本视频分辨率为1024x768，请用高清模式观看。</p>
<p>Vimeo 高清原版视频:<br />
<iframe src="http:&#47;&#47;player.vimeo.com&#47;video&#47;24359223?title=0&byline=0&portrait=0" frameborder="0" width="800" height="450"><&#47;iframe><br />
Youku 标清(中文字幕):<br />
<iframe src="http:&#47;&#47;player.youku.com&#47;embed&#47;XNDg5MjYzMzk2" frameborder="0" width="800" height="450" allowfullscreen><&#47;iframe></p>
<h1>附录<&#47;h1><br />
用OpenGL渲染时，您大概会注意到一些瑕疵（这里故意把瑕疵放大了）：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;positivebias.png"><img class="alignnone size-large wp-image-346" title="positivebias" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;positivebias-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>这是由mipmap造成的。从远处观察时，mipmap对纹素做了混合。纹理背景中的黑色像素和光照贴图中的像素混合在了一起。为了避免这一点，可以采取如下措施：</p>
<ul>
<li>让Blender在UV贴图的边界上生成白边（margin）。这个`margin`参数位于`bake`面板。要想效果更好，可以把`margin`值设为20个纹素。<&#47;li>
<li>获取纹理时，加上一个偏差（bias）：<&#47;li><br />
<&#47;ul></p>
<pre class="brush:fs">color = texture2D( myTextureSampler, UV, -2.0 ).rgb;<&#47;pre><br />
-2是偏差。这个值是通过不断尝试得出的。上面的截图中偏差值为+2，也就是说OpenGL将在原本的mipmap层次上再加两层（因此，纹素大小变为原来的1&#47;16，瑕疵也随之变小了）。</p>
<ul>
<li>后期处理中可将背景填充为黑色，这一点后续还会讲解。<&#47;li><br />
<&#47;ul></p>
