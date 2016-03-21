---
layout: page
status: publish
published: true
title: "第六课：键盘和鼠标"
date: '2014-12-06 12:38:25 +0100'
date_gmt: '2014-12-06 12:38:25 +0100'
categories: []
tags: []
order: 60
language: cn
---

欢迎来到第六课！

我们将学习如何通过鼠标和键盘来移动摄像机，就像在第一人称射击游戏中一样。

#接口

这段代码在整个课程中多次被使用，因此把它单独放在common/controls.cpp中，然后在common/controls.hpp中声明函数接口，这样tutorial06.cpp就能使用它们了。

与上节课相比，tutorial06.cpp里的代码变动很小。主要的变化是：每帧都计算MVP矩阵，而不像之前那样只算一次。现在把这段代码加到主循环中：
{% highlight text linenos %}
do{

    // ...

    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    // ...
}
```
这段代码需要3个新函数：

* computeMatricesFromInputs()读键盘和鼠标操作，然后计算投影观察矩阵。这一步正是精华所在。
* getProjectionMatrix()返回计算好的投影矩阵。
* getViewMatrix()返回计算好的观察矩阵。

这只是一种实现方式，当然，如果您不喜欢这些函数，不妨自行修改。

来看看controls.cpp做了些什么。

#实际代码

我们需要几个变量。
{% highlight text linenos %}
// position
glm::vec3 position = glm::vec3( 0, 0, 5 );
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
```
FoV is the level of zoom. 80&deg; = very wide angle, huge deformations. 60&deg; - 45&deg; : standard. 20&deg; : big zoom.

首先根据输入，重新计算位置，水平角，竖直角和视野（FoV）；再由它们算出观察和投影矩阵。

##朝向

读取鼠标位置很简单：
{% highlight text linenos %}
// Get mouse position
int xpos, ypos;
glfwGetMousePos(&xpos, &ypos);
```
我们要把光标放到屏幕中心，否则它将很快移到屏幕外，失去响应。
{% highlight text linenos %}
// Reset mouse position for next frame
glfwSetMousePos(1024/2, 768/2);
```
注意：这段代码假设窗口大小是1024*768，这不是必须的。您可以用glfwGetWindowSize来设定窗口大小。

计算观察角度：
{% highlight text linenos %}
// Compute new orientation
horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
```
从右往左读这几行代码：

* 1024/2 - xpos表示鼠标离窗口中心点的距离。这个值越大，转动角越大。
* float(...)是浮点数转换，使乘法顺利进行
* mouseSpeed用来加速或减慢旋转，可以任意调整或让用户选择。
* += : 如果没移动鼠标，1024/2-xpos的值为零，horizontalAngle+=0不改变horizontalAngle的值。如果用的是"="，每帧视角都被强制转回到原始方向，这可不是我们想要的效果。

现在，在世界空间中下计算代表视线方向的向量。
{% highlight text linenos %}
// Direction : Spherical coordinates to Cartesian coordinates conversion
glm::vec3 direction(
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
);
```
这是一种标准计算，如果您不懂余弦和正弦，下面有一个简短的解释：

<img class="alignnone whiteborder" src="http://www.numericana.com/answer/trig.gif" alt="" width="150" height="150" />

上面的公式，只是上图在三维空间下的推广。

我们想算出摄像机的"上"。"上"不一定是Y轴正方向：您俯视时，"上"实际上是水平的。这里有一个例子，位置相同，视点相同的摄像机，却有不同的"上"。

本例中"摄像机的右边"这个方向始终保持不变，指向水平方向。您可以试试：保持手臂水平伸直，向正上方看、向下看、随意看。现在定义"右"向量：因为是水平的，故Y坐标为零，X和Z值就像上图中的一样，只是角度旋转了90&deg;，或Pi/2弧度。
{% highlight text linenos %}
// Right vector
glm::vec3 right = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
);
```
我们有一个"右"和一个视线方向（或者说是"前"）。"上"与两者垂直。叉乘是一个很有用的数学工具，可以轻松地将三者联系起来：
{% highlight text linenos %}
// Up vector : perpendicular to both direction and right
glm::vec3 up = glm::cross( right, direction );
```
叉乘的具体含义是什么？很简单，回忆第三课讲到的右手定则。第一个向量是大拇指；第二个是食指；叉乘的结果就是中指。这种方法十分快捷。

##位置

代码十分直观。顺便说下，由于我使用的是法语azerty键盘，美式键盘的awsd键位对应的实际上是zqsd，因此我用上/下/右/左键而没用wsad。qwerz键盘更不一样，更别提韩语键盘了。我甚至不知道韩国人用的键盘是什么布局。我猜肯定和我的大不相同。
{% highlight text linenos %}
// Move forward
if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
    position += direction * deltaTime * speed;
}
// Move backward
if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
    position -= direction * deltaTime * speed;
}
// Strafe right
if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
    position += right * deltaTime * speed;
}
// Strafe left
if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
    position -= right * deltaTime * speed;
}
```
这里唯一特别的是deltaTime。您决不会希望每帧偏移1个单位距离的，原因很简单：

* 如果您的电脑运行速度快，fps = 60，您每秒将移动60*speed个单位。
* 如果您的电脑运行速度慢，fps = 20，您每秒将移动20*speed个单位。

不能拿电脑性能作为速度不稳的借口；您得用"前一帧到现在的时间"或"时间间隔（deltaTime）"来控制移动步长。

* 如果您的电脑运行速度快，fps = 60，您每帧将移动1/60*speed个单位，每秒移动1*speed个单位。
* 如果您的电脑运行速度慢，fps = 20，您每帧将移动1/20*speed个单位，每秒移动1*speed个单位。

这就好多了。deltaTime很容易算：
{% highlight text linenos %}
double currentTime = glfwGetTime();
float deltaTime = float(currentTime - lastTime);
```

##视野

为了增添趣味，我们可以用鼠标滚轮控制视野，实现简单的缩放：
{% highlight text linenos %}
float FoV = initialFoV - 5 * glfwGetMouseWheel();
```

##计算矩阵

矩阵计算非常直观，使用的函数和前面几乎相同，仅参数不同。
{% highlight text linenos %}
// Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit  100 units
ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
// Camera matrix
ViewMatrix       = glm::lookAt(
    position,           // Camera is here
    position+direction, // and looks here : at the same position, plus "direction"
    up                  // Head is up (set to 0,-1,0 to look upside-down)
);
```

#结果

![]({{site.baseurl}}/assets/images/tuto-6-mouse-keyboard/moveanim.gif)


##背面剔除

现在可以自由移动鼠标了，您会观察到：如果移动到立方体内部，多边形仍然会显示。这看起来理所当然，实则大有优化的余地。实际上在常见应用中您绝不会身处立方体内部。

有一种思路是让GPU检查摄像机与三角形前后位置关系。如果摄像机在三角形前面则显示该三角形；如果摄像机在三角形后面，且不在网格（mesh）（网格必须是封闭的）内部，那么必有三角形位于摄像机前面。您一定会察觉到速度变快了：三角形数量平均减少了一半！

最可喜的是这种检查十分简单。GPU计算出三角形的法线（用叉乘，还记得吗？），然后检查这个法线是否朝向摄像机。

不过这种方法是有代价的：三角形的方向是隐含的。这意味着如果在缓冲中翻转两个顶点，可能会产生孔洞。但一般来说，这一点额外工作是值得的。一般在3D建模软件中只需点击"反转法线"（实际是翻转两个顶点，从而翻转法线）就大功告成了。

开启背面剔除十分简单：
{% highlight text linenos %}
// Cull triangles which normal is not towards the camera
glEnable(GL_CULL_FACE);
```

#练习


* 限制verticalAngle，使之不能颠倒方向
* 创建一个摄像机，使它绕着物体旋转 ( position = ObjectCenter + ( radius * cos(time), height, radius * sin(time) ) )；然后将半径/高度/时间的变化绑定到键盘/鼠标上，诸如此类。
* 玩得开心哦！

