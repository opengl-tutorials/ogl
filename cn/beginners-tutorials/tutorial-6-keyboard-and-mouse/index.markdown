---
layout: page
status: publish
published: true
title: "第六课：键盘和鼠标"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 740
wordpress_url: http://www.opengl-tutorial.org/?page_id=740
date: '2014-12-06 12:38:25 +0100'
date_gmt: '2014-12-06 12:38:25 +0100'
categories: []
tags: []
order: 60
language: cn
---
<p>欢迎来到第六课！</p>
<p>我们将学习如何通过鼠标和键盘来移动摄像机，就像在第一人称射击游戏中一样。</p>
<h1>接口<&#47;h1><br />
这段代码在整个课程中多次被使用，因此把它单独放在common&#47;controls.cpp中，然后在common&#47;controls.hpp中声明函数接口，这样tutorial06.cpp就能使用它们了。</p>
<p>与上节课相比，tutorial06.cpp里的代码变动很小。主要的变化是：每帧都计算MVP矩阵，而不像之前那样只算一次。现在把这段代码加到主循环中：</p>
<pre>do{</p>
<p>    &#47;&#47; ...</p>
<p>    &#47;&#47; Compute the MVP matrix from keyboard and mouse input<br />
    computeMatricesFromInputs();<br />
    glm::mat4 ProjectionMatrix = getProjectionMatrix();<br />
    glm::mat4 ViewMatrix = getViewMatrix();<br />
    glm::mat4 ModelMatrix = glm::mat4(1.0);<br />
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;</p>
<p>    &#47;&#47; ...<br />
}<&#47;pre><br />
这段代码需要3个新函数：</p>
<ul>
<li>computeMatricesFromInputs()读键盘和鼠标操作，然后计算投影观察矩阵。这一步正是精华所在。<&#47;li>
<li>getProjectionMatrix()返回计算好的投影矩阵。<&#47;li>
<li>getViewMatrix()返回计算好的观察矩阵。<&#47;li><br />
<&#47;ul><br />
这只是一种实现方式，当然，如果您不喜欢这些函数，不妨自行修改。</p>
<p>来看看controls.cpp做了些什么。</p>
<h1>实际代码<&#47;h1><br />
我们需要几个变量。</p>
<pre>&#47;&#47; position<br />
glm::vec3 position = glm::vec3( 0, 0, 5 );<br />
&#47;&#47; horizontal angle : toward -Z<br />
float horizontalAngle = 3.14f;<br />
&#47;&#47; vertical angle : 0, look at the horizon<br />
float verticalAngle = 0.0f;<br />
&#47;&#47; Initial Field of View<br />
float initialFoV = 45.0f;</p>
<p>float speed = 3.0f; &#47;&#47; 3 units &#47; second<br />
float mouseSpeed = 0.005f;<&#47;pre><br />
FoV is the level of zoom. 80&deg; = very wide angle, huge deformations. 60&deg; - 45&deg; : standard. 20&deg; : big zoom.</p>
<p>首先根据输入，重新计算位置，水平角，竖直角和视野（FoV）；再由它们算出观察和投影矩阵。</p>
<h2>朝向<&#47;h2><br />
读取鼠标位置很简单：</p>
<pre>&#47;&#47; Get mouse position<br />
int xpos, ypos;<br />
glfwGetMousePos(&amp;xpos, &amp;ypos);<&#47;pre><br />
我们要把光标放到屏幕中心，否则它将很快移到屏幕外，失去响应。</p>
<pre>&#47;&#47; Reset mouse position for next frame<br />
glfwSetMousePos(1024&#47;2, 768&#47;2);<&#47;pre><br />
注意：这段代码假设窗口大小是1024*768，这不是必须的。您可以用glfwGetWindowSize来设定窗口大小。</p>
<p>计算观察角度：</p>
<pre>&#47;&#47; Compute new orientation<br />
horizontalAngle += mouseSpeed * deltaTime * float(1024&#47;2 - xpos );<br />
verticalAngle&nbsp;&nbsp; += mouseSpeed * deltaTime * float( 768&#47;2 - ypos );<&#47;pre><br />
从右往左读这几行代码：</p>
<ul>
<li>1024&#47;2 - xpos表示鼠标离窗口中心点的距离。这个值越大，转动角越大。<&#47;li>
<li>float(...)是浮点数转换，使乘法顺利进行<&#47;li>
<li>mouseSpeed用来加速或减慢旋转，可以任意调整或让用户选择。<&#47;li>
<li>+= : 如果没移动鼠标，1024&#47;2-xpos的值为零，horizontalAngle+=0不改变horizontalAngle的值。如果用的是"="，每帧视角都被强制转回到原始方向，这可不是我们想要的效果。<&#47;li><br />
<&#47;ul><br />
现在，在世界空间中下计算代表视线方向的向量。</p>
<pre>&#47;&#47; Direction : Spherical coordinates to Cartesian coordinates conversion<br />
glm::vec3 direction(<br />
    cos(verticalAngle) * sin(horizontalAngle),<br />
    sin(verticalAngle),<br />
    cos(verticalAngle) * cos(horizontalAngle)<br />
);<&#47;pre><br />
这是一种标准计算，如果您不懂余弦和正弦，下面有一个简短的解释：</p>
<p><img class="alignnone whiteborder" src="http:&#47;&#47;www.numericana.com&#47;answer&#47;trig.gif" alt="" width="150" height="150" &#47;></p>
<p>上面的公式，只是上图在三维空间下的推广。</p>
<p>我们想算出摄像机的&ldquo;上&rdquo;。&ldquo;上&rdquo;不一定是Y轴正方向：您俯视时，&ldquo;上&rdquo;实际上是水平的。这里有一个例子，位置相同，视点相同的摄像机，却有不同的&ldquo;上&rdquo;。</p>
<p>本例中&ldquo;摄像机的右边&rdquo;这个方向始终保持不变，指向水平方向。您可以试试：保持手臂水平伸直，向正上方看、向下看、随意看。现在定义&ldquo;右&rdquo;向量：因为是水平的，故Y坐标为零，X和Z值就像上图中的一样，只是角度旋转了90&deg;，或Pi&#47;2弧度。</p>
<pre>&#47;&#47; Right vector<br />
glm::vec3 right = glm::vec3(<br />
    sin(horizontalAngle - 3.14f&#47;2.0f),<br />
    0,<br />
    cos(horizontalAngle - 3.14f&#47;2.0f)<br />
);<&#47;pre><br />
我们有一个&ldquo;右&rdquo;和一个视线方向（或者说是&ldquo;前&rdquo;）。&ldquo;上&rdquo;与两者垂直。叉乘是一个很有用的数学工具，可以轻松地将三者联系起来：</p>
<pre>&#47;&#47; Up vector : perpendicular to both direction and right<br />
glm::vec3 up = glm::cross( right, direction );<&#47;pre><br />
叉乘的具体含义是什么？很简单，回忆第三课讲到的右手定则。第一个向量是大拇指；第二个是食指；叉乘的结果就是中指。这种方法十分快捷。</p>
<h2>位置<&#47;h2><br />
代码十分直观。顺便说下，由于我使用的是法语azerty键盘，美式键盘的awsd键位对应的实际上是zqsd，因此我用上&#47;下&#47;右&#47;左键而没用wsad。qwerz键盘更不一样，更别提韩语键盘了。我甚至不知道韩国人用的键盘是什么布局。我猜肯定和我的大不相同。</p>
<pre>&#47;&#47; Move forward<br />
if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){<br />
    position += direction * deltaTime * speed;<br />
}<br />
&#47;&#47; Move backward<br />
if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){<br />
    position -= direction * deltaTime * speed;<br />
}<br />
&#47;&#47; Strafe right<br />
if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){<br />
    position += right * deltaTime * speed;<br />
}<br />
&#47;&#47; Strafe left<br />
if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){<br />
    position -= right * deltaTime * speed;<br />
}<&#47;pre><br />
这里唯一特别的是deltaTime。您决不会希望每帧偏移1个单位距离的，原因很简单：</p>
<ul>
<li>如果您的电脑运行速度快，fps = 60，您每秒将移动60*speed个单位。<&#47;li>
<li>如果您的电脑运行速度慢，fps = 20，您每秒将移动20*speed个单位。<&#47;li><br />
<&#47;ul><br />
不能拿电脑性能作为速度不稳的借口；您得用&ldquo;前一帧到现在的时间&rdquo;或&ldquo;时间间隔（deltaTime）&rdquo;来控制移动步长。</p>
<ul>
<li>如果您的电脑运行速度快，fps = 60，您每帧将移动1&#47;60*speed个单位，每秒移动1*speed个单位。<&#47;li>
<li>如果您的电脑运行速度慢，fps = 20，您每帧将移动1&#47;20*speed个单位，每秒移动1*speed个单位。<&#47;li><br />
<&#47;ul><br />
这就好多了。deltaTime很容易算：</p>
<pre>double currentTime = glfwGetTime();<br />
float deltaTime = float(currentTime - lastTime);<&#47;pre></p>
<h2>视野<&#47;h2><br />
为了增添趣味，我们可以用鼠标滚轮控制视野，实现简单的缩放：</p>
<pre>float FoV = initialFoV - 5 * glfwGetMouseWheel();<&#47;pre></p>
<h2>计算矩阵<&#47;h2><br />
矩阵计算非常直观，使用的函数和前面几乎相同，仅参数不同。</p>
<pre>&#47;&#47; Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit  100 units<br />
ProjectionMatrix = glm::perspective(FoV, 4.0f &#47; 3.0f, 0.1f, 100.0f);<br />
&#47;&#47; Camera matrix<br />
ViewMatrix&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = glm::lookAt(<br />
    position,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Camera is here<br />
    position+direction, &#47;&#47; and looks here : at the same position, plus "direction"<br />
    up&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Head is up (set to 0,-1,0 to look upside-down)<br />
);<&#47;pre></p>
<h1>结果<&#47;h1><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;moveanim.gif"><img class="alignnone size-full wp-image-372" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;moveanim.gif" alt="" width="206" height="159" &#47;><&#47;a></p>
<h2>背面剔除<&#47;h2><br />
现在可以自由移动鼠标了，您会观察到：如果移动到立方体内部，多边形仍然会显示。这看起来理所当然，实则大有优化的余地。实际上在常见应用中您绝不会身处立方体内部。</p>
<p>有一种思路是让GPU检查摄像机与三角形前后位置关系。如果摄像机在三角形前面则显示该三角形；如果摄像机在三角形后面，且不在网格（mesh）（网格必须是封闭的）内部，那么必有三角形位于摄像机前面。您一定会察觉到速度变快了：三角形数量平均减少了一半！</p>
<p>最可喜的是这种检查十分简单。GPU计算出三角形的法线（用叉乘，还记得吗？），然后检查这个法线是否朝向摄像机。</p>
<p>不过这种方法是有代价的：三角形的方向是隐含的。这意味着如果在缓冲中翻转两个顶点，可能会产生孔洞。但一般来说，这一点额外工作是值得的。一般在3D建模软件中只需点击&ldquo;反转法线&rdquo;（实际是翻转两个顶点，从而翻转法线）就大功告成了。</p>
<p>开启背面剔除十分简单：</p>
<pre>&#47;&#47; Cull triangles which normal is not towards the camera<br />
glEnable(GL_CULL_FACE);<&#47;pre></p>
<h1>练习<&#47;h1></p>
<ul>
<li>限制verticalAngle，使之不能颠倒方向<&#47;li>
<li>创建一个摄像机，使它绕着物体旋转 ( position = ObjectCenter + ( radius * cos(time), height, radius * sin(time) ) )；然后将半径&#47;高度&#47;时间的变化绑定到键盘&#47;鼠标上，诸如此类。<&#47;li>
<li>玩得开心哦！<&#47;li><br />
<&#47;ul></p>
