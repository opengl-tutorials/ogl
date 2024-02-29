---
layout: tutorial
status: publish
published: true
title: 公告板技术
date: '2013-10-15 17:15:15 +0200'
date_gmt: '2013-10-15 17:15:15 +0200'
categories: []
order: 584
tags: []
language: cn
---

* TOC
{:toc}

公告板是3D世界中的有2D样式的物体。不是绘制2D菜单覆盖在所有物体上；也不是一个可以围绕你转动的3D面板；而是在它们之间的一种设计，例如许多游戏中的血量条。 公告板的特殊之处在于它们处于特定的位置，它们的朝向会自动计算来使它们面向相机。
 

# 方案 #1 : 2D方法

这个真的超级简单。

只要计算点在屏幕上的位置，然后在这个位置显示2D文字(见教程11)。

``` cpp
// 下面所有代码在教程3中都有解释，并没有新加入什么
glm::vec4 BillboardPos_worldspace(x,y,z, 1.0f);
glm::vec4 BillboardPos_screenspace = ProjectionMatrix * ViewMatrix * BillboardPos_worldspace;
BillboardPos_screenspace /= BillboardPos_screenspace.w;

if (BillboardPos_screenspace.z < 0.0f){
    // 物体在相机后面，不显示
}
```

当当当当!

这个方法的优点是它非常简单，而且无论相机有多远，公告板也会都会保持同样的大小。但是2D文字总会显示在其他物体之上，并且这也可能会破坏渲染并挡住其他物体。
 

# 方案 #2 : 3D方法

这个方法通常更优，同时没有更复杂很多。

我们这里的目标是无论相机如何移动，使网格与相机对齐：

![]({{site.baseurl}}/assets/images/tuto-billboard/2a.gif)


你可以把这个问题看作生成一个合适的模型矩阵，虽然这个问题远远更简单。

思路就是通过相机的“上(up)”和“右(right)”向量改变公告板的每个角，使它们保持在特定位置。
 

![]({{site.baseurl}}/assets/images/tuto-billboard/principle.png)


 

当然，我们仅仅知道公告板中心在世界空间下的坐标，所以我们也需要相机的在世界空间下的up和right向量。

在相机空间下，相机的up向量是(0,1,0)。要将其转换到世界空间，只需要乘从相机空间到世界空间的转移矩阵，当然也就是视图矩阵(View matrix)的逆矩阵。

用更简单的方法阐述这个数学运算就是：
```

CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}
CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}
```

得到了这个之后，计算最终的顶点坐标就非常容易了。

``` glsl
vec3 vertexPosition_worldspace =
    particleCenter_wordspace
    + CameraRight_worldspace * squareVertices.x * BillboardSize.x
    + CameraUp_worldspace * squareVertices.y * BillboardSize.y;
```
{: .highlightglslvs }

* particleCenter_worldspace正如其变量名的，表示公告板的中心坐标。它被定义为一个uniform vec3。
* squareVertices是原网格。左定点squareVertices.x是-0.5，因此也就会被移向相机左侧(因为*CameraRight_worldspace)
* BillboardSize表示公告板的大小，使用的是世界空间下的单位，并作为uniform传入。

<div><span style="font-size: medium;"><span style="line-height: 24px;">一二三 变！结果是这样的，是不是很简单？</span></span><span style="font-size: 16px;"> </span></div>
![]({{site.baseurl}}/assets/images/tuto-billboard/2.gif)


 

请注意, 下面是如何生成squareVertices：

``` cpp
// 包含例子4个定点的VBO
 static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
 };
```

# 方案 #3 : 固定尺寸的3D方法

正如你上面看到的，公告板会随着相机的距离改变大小。这在某些情况下是我们期待的，但是在其他情况比如血量条，你可能会希望它能固定大小。

因为中心和四角的位移必须在屏幕空间下计算，我们可以这么做：计算公告板中心在屏幕空间下的位置，在将其偏移。

``` cpp
vertexPosition_worldspace = particleCenter_wordspace;
// 计算粒子中心在屏幕空间下的位置
gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);
// 这里我们必须自己做透视除法
gl_Position /= gl_Position.w;

// 直接在屏幕空间下移动顶点。无需考虑CameraUp/Right_worlspace。
gl_Position.xy += squareVertices.xy * vec2(0.2, 0.05);
```

记住，在渲染管线的这一步，你使用的是正规化的设备坐标(Normalized Device Coordinates)，也就是两个坐标取值是在-1到1之间的：这里管线给的不是像素值。

如果你想要使用像素单位的尺寸，很简单：只需要使用 (ScreenSizeInPixels / BillboardSizeInPixels) 而非 BillboardSizeInScreenPercentage。
 

![]({{site.baseurl}}/assets/images/tuto-billboard/3.gif)


 
# 方案 #4 : 仅仅纵向旋转

有些系统会将远处的树木和路灯建模成公告板。你肯定，肯定不想让你的树弯曲：它**一定**是直立的。所以你需要一个混合系统来只让其绕一个轴旋转。

好吧，这个留给读者当作练习！