---
layout: page
status: publish
published: true
title: "第十课：透明"
date: '2014-12-05 15:03:48 +0100'
date_gmt: '2014-12-05 15:03:48 +0100'
categories: []
tags: []
language: cn
order: 20
---

# alpha通道

alpha通道的概念很简单。我们以前的计算结果是RGB值，现在则是RGBA值：

``` glsl
// Ouput data : it's now a vec4
out vec4 color;
```
{: .highlightglslfs }

前三个分量仍可以通过重组操作符（swizzle operator）.xyz访问，最后一个分量通过.a访问：

``` glsl
color.a = 0.3;
```
{: .highlightglslfs }

与直觉相反，alpha代表的是不透明度；因此alpha = 1代表完全不透明，alpha = 0为完全透明。

这里我们简单地将alpha硬编码为0.3；但更常见的做法是用一个uniform变量表示它，或从RGBA纹理中读取（TGA格式支持alpha通道，而GLFW支持TGA格式）。

结果如下。既然我们能"看透"模型表面，请确保关闭背面剔除（glDisable(GL_CULL_FACE) ）。否则我们就发现模型没有了"背"面。

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyok.png)


# 顺序很重要！

上一个截图看上去还行，但这仅仅是运气好罢了。

##问题所在

这里我画了一红一绿两个alpha值为50%的正方形。从中可以看出顺序的重要性，最终的颜色显著影响了眼睛对深度的感知。

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyorder.png)


我们的场景中也出现了同样的现象。试着稍稍改变一下观察点：

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencybad.png)


原来这还是个十分棘手的问题。您在游戏中也没怎么见过透明的东西，是吧？

##常见解决方案

常见解决方案即对所有的透明三角形排序。是的，所有的透明三角形。

* 渲染场景的不透明部分，让深度缓冲丢弃被遮挡的透明三角形。
* 对透明三角形按深度由远及近排序。
* 渲染透明三角形。

可以用C语言的qsort函数或者C++的std::sort函数来排序。细节就不多说了，因为......

##警告

这么做可以解决问题（下一节还会介绍它），但是：

* 您将受限于填充率。亦即每个片段会写10、20次，也许更多次。这对力不从心的内存总线来说太繁重了。通常，深度缓冲可以自动丢弃"远"片段；但这里我们已显式地对片段进行了排序，因此深度缓冲实际上没起作用。
* 这些操作，每个像素上都会执行4遍（我们用了4倍多重采样抗锯齿（MSAA）），除非用了什么巧妙的优化。
* 透明三角形排序很耗时
* 若要逐个三角形地切换纹理，或者更糟糕，切换着色器--性能会大打折扣。不要这么做。

一个足够好的解决方案是：

* 限制透明多边形的数量
* 对所有透明多边形使用同一个着色器和纹理
* 若这些透明多边形本就是外表各异的，那就用不同的纹理
* 若不排序时效果还*凑合*，那就不排序好了。


##顺序无关透明

如果您的引擎确实需要顶级的透明效果，这里有一些值得研究的技术：

* [The original 2001 Depth Peeling paper](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.9286&rep=rep1&type=pdf)：像素级精细度，但速度不快。
* [Dual Depth Peeling](http://developer.download.nvidia.com/SDK/10/opengl/src/dual_depth_peeling/doc/DualDepthPeeling.pdf)：小幅改进
* 桶排序相关的几篇论文。把片段存到数组，在着色器中进行深度排序。
* [ATI's Mecha Demo](http://fr.slideshare.net/hgruen/oit-and-indirect-illumination-using-dx11-linked-lists)：效果速度俱佳，但实现起来有难度，需要最新的硬件。用链表存储片段。
* [Cyril Crassin's variation on the ATI's  technique](http://blog.icare3d.org/2010/07/opengl-40-abuffer-v20-linked-lists-of.html)：实现难度更大

注意，即便是《小小大星球》（*Little Big Planet*）这种刚出炉的、运行在高端主机上的游戏，也只用了一层透明。

# 混合函数

要让上述代码运行起来，得设置好混合函数。

``` cpp
// Enable blending
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

这意味着
```

New color in framebuffer =
           current alpha in framebuffer * current color in framebuffer +
           (1 - current alpha in framebuffer) * shader's output color
```

上图红色方块居上的效果由如下等式得来：
```

new color = 0.5*(0,1,0) + (1-0.5)*(1,0.5,0.5); // (the red was already blended with the white background)
new color = (1, 0.75, 0.25) = the same orange

```

 
