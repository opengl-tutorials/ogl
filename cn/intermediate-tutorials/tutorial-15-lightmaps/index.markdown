---
layout: page
status: publish
published: true
title: "第十五课：光照贴图（Lightmap）"
date: '2014-12-13 03:20:09 +0100'
date_gmt: '2014-12-13 03:20:09 +0100'
categories: []
tags: []
language: cn
order: 70
---

#简介

这节视频课程不介绍新的OpenGL技术/语法，而是教大家用已学到的技术生成高质量的阴影。

本课介绍怎样用Blender创建简单场景；还介绍了如何烘培光照贴图，并应用到实际中。

![]({{site.baseurl}}/assets/images/tuto-15-lightmaps/lighmappedroom.png)

本课不需要Blender预备知识，我会讲解快捷键等内容。

#关于光照贴图

光照贴图是预先一次性烘焙好的。也就是说光照贴图完全是静态的，你不能实时地移动甚至删除光源。

但对于阳光这种光源来说，光照贴图还是大有用处的；在灯泡不会破碎的室内场景中，也可以用光照贴图。2009年发布的《镜之边缘》（*Mirror Edge*）室内外场景就大量采用了光照贴图。

更重要的是，光照贴图很容易配置，渲染速度无出其右。

#视频

本视频分辨率为1024x768，请用高清模式观看。

Vimeo 高清原版视频:
<iframe src="http://player.vimeo.com/video/24359223?title=0&byline=0&portrait=0" frameborder="0" width="800" height="450"></iframe>
Youku 标清(中文字幕):
<iframe src="http://player.youku.com/embed/XNDg5MjYzMzk2" frameborder="0" width="800" height="450" allowfullscreen></iframe>

#附录

用OpenGL渲染时，您大概会注意到一些瑕疵（这里故意把瑕疵放大了）：

![]({{site.baseurl}}/assets/images/tuto-15-lightmaps/positivebias.png)


这是由mipmap造成的。从远处观察时，mipmap对纹素做了混合。纹理背景中的黑色像素和光照贴图中的像素混合在了一起。为了避免这一点，可以采取如下措施：

* 让Blender在UV贴图的边界上生成白边（margin）。这个`margin`参数位于`bake`面板。要想效果更好，可以把`margin`值设为20个纹素。
* 获取纹理时，加上一个偏差（bias）：

^```s*glsls*
color = texture( myTextureSampler, UV, -2.0 ).rgb;
```
{: .highlightglslfs }

-2是偏差。这个值是通过不断尝试得出的。上面的截图中偏差值为+2，也就是说OpenGL将在原本的mipmap层次上再加两层（因此，纹素大小变为原来的1/16，瑕疵也随之变小了）。

* 后期处理中可将背景填充为黑色，这一点后续还会讲解。

