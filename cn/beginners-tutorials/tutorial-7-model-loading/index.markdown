---
layout: page
status: publish
published: true
title: "第七课：模型加载"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 742
wordpress_url: http://www.opengl-tutorial.org/?page_id=742
date: '2014-12-06 12:52:26 +0100'
date_gmt: '2014-12-06 12:52:26 +0100'
categories: []
tags: []
order: 70
---
<p>目前为止，我们一直在用硬编码描述立方体。您一定也觉得这是种很笨拙、很麻烦的办法。</p>
<p>本课将学习从文件中加载3D模型。和加载纹理类似，我们先写一个小的、功能有限的加载器，接着再为大家介绍几个比我们写的更好的、实用的库。</p>
<p>为了让课程尽可能简单，我们将采用简单、常用的OBJ格式。同样也是出于简单原则，我们只处理每个顶点有一个UV坐标和一个法线的OBJ文件（目前不需要知道什么是法线）。</p>
<h1>加载OBJ模型<&#47;h1><br />
加载函数在common&#47;objloader.hpp中声明，在common&#47;objloader.cpp中实现。函数原型如下：</p>
<pre>bool loadOBJ(<br />
    const char * path,<br />
    std::vector  & out_vertices,<br />
    std::vector  & out_uvs,<br />
    std::vector  & out_normals<br />
)<&#47;pre><br />
我们让loadOBJ读取文件路径，把数据写入out_vertices&#47;out_uvs&#47;out_normals。如果出错则返回false。std::vector是C++中的数组，可存放glm::vec3类型的数据，数组大小可任意修改，不过std::vector和数学中的向量（vector）是两码事。其实它只是个数组。最后提一点，符号&amp;意思是这个函数将会直接修改这些数组。</p>
<h2>OBJ文件示例<&#47;h2><br />
OBJ文件大概是这个模样：</p>
<pre># Blender3D v249 OBJ File: untitled.blend<br />
# www.blender3d.org<br />
mtllib cube.mtl<br />
v 1.000000 -1.000000 -1.000000<br />
v 1.000000 -1.000000 1.000000<br />
v -1.000000 -1.000000 1.000000<br />
v -1.000000 -1.000000 -1.000000<br />
v 1.000000 1.000000 -1.000000<br />
v 0.999999 1.000000 1.000001<br />
v -1.000000 1.000000 1.000000<br />
v -1.000000 1.000000 -1.000000<br />
vt 0.748573 0.750412<br />
vt 0.749279 0.501284<br />
vt 0.999110 0.501077<br />
vt 0.999455 0.750380<br />
vt 0.250471 0.500702<br />
vt 0.249682 0.749677<br />
vt 0.001085 0.750380<br />
vt 0.001517 0.499994<br />
vt 0.499422 0.500239<br />
vt 0.500149 0.750166<br />
vt 0.748355 0.998230<br />
vt 0.500193 0.998728<br />
vt 0.498993 0.250415<br />
vt 0.748953 0.250920<br />
vn 0.000000 0.000000 -1.000000<br />
vn -1.000000 -0.000000 -0.000000<br />
vn -0.000000 -0.000000 1.000000<br />
vn -0.000001 0.000000 1.000000<br />
vn 1.000000 -0.000000 0.000000<br />
vn 1.000000 0.000000 0.000001<br />
vn 0.000000 1.000000 -0.000000<br />
vn -0.000000 -1.000000 0.000000<br />
usemtl Material_ray.png<br />
s off<br />
f 5&#47;1&#47;1 1&#47;2&#47;1 4&#47;3&#47;1<br />
f 5&#47;1&#47;1 4&#47;3&#47;1 8&#47;4&#47;1<br />
f 3&#47;5&#47;2 7&#47;6&#47;2 8&#47;7&#47;2<br />
f 3&#47;5&#47;2 8&#47;7&#47;2 4&#47;8&#47;2<br />
f 2&#47;9&#47;3 6&#47;10&#47;3 3&#47;5&#47;3<br />
f 6&#47;10&#47;4 7&#47;6&#47;4 3&#47;5&#47;4<br />
f 1&#47;2&#47;5 5&#47;1&#47;5 2&#47;9&#47;5<br />
f 5&#47;1&#47;6 6&#47;10&#47;6 2&#47;9&#47;6<br />
f 5&#47;1&#47;7 8&#47;11&#47;7 6&#47;10&#47;7<br />
f 8&#47;11&#47;7 7&#47;12&#47;7 6&#47;10&#47;7<br />
f 1&#47;2&#47;8 2&#47;9&#47;8 3&#47;13&#47;8<br />
f 1&#47;2&#47;8 3&#47;13&#47;8 4&#47;14&#47;8<&#47;pre><br />
因此：</p>
<ul>
<li>#是注释标记，就像C++中的&#47;&#47;<&#47;li>
<li>usemtl和mtlib描述了模型的外观。本课用不到。<&#47;li>
<li>v代表顶点<&#47;li>
<li>vt代表顶点的纹理坐标<&#47;li>
<li>vn代表顶点的法线<&#47;li>
<li>f代表面<&#47;li><br />
<&#47;ul><br />
v vt vn都很好理解。f比较麻烦。例如f 8&#47;11&#47;7 7&#47;12&#47;7 6&#47;10&#47;7：</p>
<ul>
<li>8&#47;11&#47;7描述了三角形的第一个顶点<&#47;li>
<li>7&#47;12&#47;7描述了三角形的第二个顶点<&#47;li>
<li>6&#47;10&#47;7描述了三角形的第三个顶点<&#47;li>
<li>对于第一个顶点，8指向要用的顶点。此例中是-1.000000 1.000000 -1.000000（索引从1开始，和C++中从0开始不同）<&#47;li>
<li>11指向要用的纹理坐标。此例中是0.748355 0.998230。<&#47;li>
<li>7指向要用的法线。此例中是0.000000 1.000000 -0.000000。<&#47;li><br />
<&#47;ul><br />
我们称这些数字为索引。若几个顶点共用同一个坐标，索引就显得很方便，文件中只需保存一个&ldquo;V&rdquo;，可以多次引用，节省了存储空间。</p>
<p>其弊端在于我们无法让OpenGL混用顶点、纹理和法线索引。因此本课采用的方法是创建一个标准的、未加索引的模型。等第九课时再讨论索引，届时将会介绍如何解决OpenGL的索引问题。</p>
<h2>用Blender创建OBJ文件<&#47;h2><br />
我们写的蹩脚加载器功能实在有限，因此在导出模型时得格外小心。下图展示了在Blender中导出模型的情形：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;Blender.png"><img class="alignnone size-full wp-image-697" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;Blender.png" alt="" width="321" height="529" &#47;><&#47;a></p>
<h2>读取OBJ文件<&#47;h2><br />
OK，真正开始写代码了。我们需要一些临时变量存储.obj文件的内容。</p>
<pre>std::vector vertexIndices, uvIndices, normalIndices;<br />
std::vector temp_vertices;<br />
std::vector temp_uvs;<br />
std::vector temp_normals;<&#47;pre><br />
学第五课带纹理的立方体时您已学会打开文件了：</p>
<pre>FILE * file = fopen(path, "r");<br />
if( file == NULL ){<br />
    printf("Impossible to open the file !n");<br />
    return false;<br />
}<&#47;pre><br />
读文件直到文件末尾：</p>
<pre>while( 1 ){</p>
<p>    char lineHeader[128];<br />
    &#47;&#47; read the first word of the line<br />
    int res = fscanf(file, "%s", lineHeader);<br />
    if (res == EOF)<br />
        break; &#47;&#47; EOF = End Of File. Quit the loop.</p>
<p>    &#47;&#47; else : parse lineHeader<&#47;pre><br />
（注意，我们假设第一行的文字长度不超过128，这样做太笨了。但既然这只是个实验品，就凑合一下吧）</p>
<p>首先处理顶点：</p>
<pre>if ( strcmp( lineHeader, "v" ) == 0 ){<br />
    glm::vec3 vertex;<br />
    fscanf(file, "%f %f %fn", &amp;vertex.x, &amp;vertex.y, &amp;vertex.z );<br />
    temp_vertices.push_back(vertex);<&#47;pre><br />
也就是说，若第一个字是&ldquo;v&rdquo;，则后面一定是3个float值，于是以这3个值创建一个glm::vec3变量，将其添加到数组。</p>
<pre>}else if ( strcmp( lineHeader, "vt" ) == 0 ){<br />
    glm::vec2 uv;<br />
    fscanf(file, "%f %fn", &amp;uv.x, &amp;uv.y );<br />
    temp_uvs.push_back(uv);<&#47;pre><br />
也就是说，如果不是&ldquo;v&rdquo;而是&ldquo;vt&rdquo;，那后面一定是2个float值，于是以这2个值创建一个glm::vec2变量，添加到数组。</p>
<p>以同样的方式处理法线：</p>
<pre>}else if ( strcmp( lineHeader, "vn" ) == 0 ){<br />
    glm::vec3 normal;<br />
    fscanf(file, "%f %f %fn", &amp;normal.x, &amp;normal.y, &amp;normal.z );<br />
    temp_normals.push_back(normal);<&#47;pre><br />
接下来是&ldquo;f&rdquo;，略难一些：</p>
<pre>}else if ( strcmp( lineHeader, "f" ) == 0 ){<br />
    std::string vertex1, vertex2, vertex3;<br />
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];<br />
    int matches = fscanf(file, "%d&#47;%d&#47;%d %d&#47;%d&#47;%d %d&#47;%d&#47;%dn", &amp;vertexIndex[0], &amp;uvIndex[0], &amp;normalIndex[0], &amp;vertexIndex[1], &amp;uvIndex[1], &amp;normalIndex[1], &amp;vertexIndex[2], &amp;uvIndex[2], &amp;normalIndex[2] );<br />
    if (matches != 9){<br />
        printf("File can't be read by our simple parser : ( Try exporting with other optionsn");<br />
        return false;<br />
    }<br />
    vertexIndices.push_back(vertexIndex[0]);<br />
    vertexIndices.push_back(vertexIndex[1]);<br />
    vertexIndices.push_back(vertexIndex[2]);<br />
    uvIndices    .push_back(uvIndex[0]);<br />
    uvIndices    .push_back(uvIndex[1]);<br />
    uvIndices    .push_back(uvIndex[2]);<br />
    normalIndices.push_back(normalIndex[0]);<br />
    normalIndices.push_back(normalIndex[1]);<br />
    normalIndices.push_back(normalIndex[2]);<&#47;pre><br />
代码与前面的类似，只不过读取的数据多一些。</p>
<h2>处理数据<&#47;h2><br />
我们只需改变一下数据的形式。读取的是字符串，现在有了一组数组。这还不够，我们得把数据组织成OpenGL要求的形式。也就是去掉索引，只保留顶点坐标数据。这步操作称为索引。</p>
<p>遍历每个三角形（每个&ldquo;f&rdquo;行）的每个顶点（每个 v&#47;vt&#47;vn）：</p>
<pre>    &#47;&#47; For each vertex of each triangle<br />
    for( unsigned int i=0; i<&#47;pre><br />
顶点坐标的索引存放到vertexIndices[i]：</p>
<pre>unsigned int vertexIndex = vertexIndices[i];<&#47;pre><br />
因此坐标是temp_vertices[ vertexIndex-1 ]（-1是因为C++的下标从0开始，而OBJ的索引从1开始，还记得吗？）：</p>
<pre>glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];<&#47;pre><br />
这样就有了一个顶点坐标：</p>
<pre>out_vertices.push_back(vertex);<&#47;pre><br />
UV和法线同理，任务完成！</p>
<h1>使用加载的数据<&#47;h1><br />
到这一步，几乎什么变化都没发生。这次我们不再声明static const GLfloat g_vertex_buffer_data[] = {&hellip;}，而是创建一个顶点数组（UV和法向同理）。用正确的参数调用loadOBJ：</p>
<pre>&#47;&#47; Read our .obj file<br />
std::vector vertices;<br />
std::vector uvs;<br />
std::vector normals; &#47;&#47; Won't be used at the moment.<br />
bool res = loadOBJ("cube.obj", vertices, uvs, normals);<&#47;pre><br />
把数组传给OpenGL：</p>
<pre>glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &amp;vertices[0], GL_STATIC_DRAW);<&#47;pre><br />
就是这样啦！</p>
<h1>结果<&#47;h1><br />
不好意思，这个纹理不大漂亮。我不太擅长美术:(。欢迎您来提供一些好的纹理。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;ModelLoading.png"><img class="alignnone size-medium wp-image-670" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;ModelLoading-300x232.png" alt="" width="300" height="232" &#47;><&#47;a></p>
<h1>其他模型格式及加载器<&#47;h1><br />
这个小巧的加载器应该比较适合初学，不过别在实际中使用它。参考一下<a title="Useful Tools &amp; Links" href="&#47;?page_id=210">实用链接和工具<&#47;a>页面，看看有什么能用的。不过请注意，等到第九课才会<em>真正<&#47;em>用到这些工具。</p>
