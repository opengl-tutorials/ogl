---
layout: page
status: publish
published: true
title: "第十三课：法线贴图"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1359
wordpress_url: http://www.opengl-tutorial.org/?page_id=1359
date: '2014-12-06 03:31:09 +0100'
date_gmt: '2014-12-06 03:31:09 +0100'
categories: []
tags: []
language: cn
---
<p>欢迎来到第十三课！今天的内容是法线贴图（normal mapping）。</p>
<p>学完<a title="Tutorial 8 : Basic shading" href="http:&#47;&#47;www.opengl-tutorial.org&#47;zh-hans&#47;beginners-tutorials-zh&#47;tutorial-8-basic-shading-zh&#47;">第八课：基本着色<&#47;a> 后，我们知道了如何用三角形法线得到不错的着色效果。需要注意的是，截至目前，每个顶点仅有一条法线。在三角形内部，法线是平滑过渡的，而颜色则是通过纹理采样得到的（译注：三角形内部法线由插值计算得出，颜色则是直接从纹理取数据）。法线贴图的基本思想就是像纹理采样一样为法线取值。</p>
<h1>法线纹理<&#47;h1><br />
下图是一张法线纹理：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normal.jpg"><img class="alignnone size-full wp-image-307" title="normal" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normal.jpg" alt="" width="341" height="336" &#47;><&#47;a></p>
<p>每个纹素的RGB值实际上表示的是XYZ向量：颜色的分量取值范围为0到1，而向量的分量取值范围是-1到1；可以建立从纹素到法线的简单映射</p>
<pre class="brush:c">normal = (2*color)-1 &#47;&#47; on each component<&#47;pre><br />
由于法线基本都是指向&ldquo;曲面外侧&rdquo;的（按照惯例，X轴朝右，Y轴朝上），因此法线纹理整体呈蓝色。</p>
<p>法线纹理的映射方式和漫反射纹理相似。麻烦之处在于如何将法线从各三角形局部空间（切线空间tangent space，亦称图像空间image space）变换到模型空间（着色计算所采用的空间）。</p>
<h1>切线和副切线（Tangent and Bitangent）<&#47;h1><br />
大家对矩阵已经十分熟悉了，应该知道定义一个空间（本例是切线空间）需要三个向量。现在Up向量已经有了，即法线：可用Blender生成，或由一个简单的叉乘计算得到。下图中蓝色箭头代表法线（法线贴图整体颜色也恰好是蓝色）。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;NormalVector.png"><img class="alignnone size-full wp-image-821" title="NormalVector" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;NormalVector.png" alt="" width="480" height="270"><&#47;a></p>
<p>然后是切线T：垂直于法线的向量。但这样的切线有很多个：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;TangentVectors.png"><img class="alignnone size-full wp-image-822" title="TangentVectors" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;TangentVectors.png" alt="" width="480" height="270"><&#47;a></p>
<p>这么多切线中该选哪个呢？理论上哪一个都行。但我们必须保持连续一致性，以免衔接处出现瑕疵。标准的做法是将切线方向和纹理空间对齐：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;TangentVectorFromUVs.png"><img class="alignnone size-full wp-image-823" title="TangentVectorFromUVs" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;TangentVectorFromUVs.png" alt="" width="480" height="270"><&#47;a></p>
<p>定义一组基需要三个向量，因此我们还得计算副切线B（本可以随便选一条切线，但选定垂直于另外两条轴的切线，计算会方便些）。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;NTBFromUVs.png"><img class="alignnone size-full wp-image-824" title="NTBFromUVs" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;NTBFromUVs.png" alt="" width="480" height="270"><&#47;a></p>
<p>算法如下：记三角形的两条边为deltaPos1和deltaPos2，deltaUV1和deltaUV2是对应的UV坐标下的差值；则问题可用如下方程表示：</p>
<pre class="brush:c">deltaPos1 = deltaUV1.x * T + deltaUV1.y * B<br />
deltaPos2 = deltaUV2.x * T + deltaUV2.y * B<&#47;pre><br />
求解T和B就得到了切线和副切线！（代码见下文）</p>
<p>已知T、B、N向量之后，即可得下面这个漂亮的矩阵，完成从切线空间到模型空间的变换：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;TBN.png"><img class="alignnone size-full wp-image-308 whiteborder" title="TBN" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;TBN.png" alt="" width="107" height="66" &#47;><&#47;a></p>
<p>有了TBN矩阵，我们就能把（从法线纹理中获取的）法线变换到模型空间。</p>
<p>可我们需要的却是从切线空间到模型空间的变换，法线则保持不变。所有计算均在切线空间中进行，不会对其他计算产生影响。</p>
<p>只需对上述矩阵求逆即可得逆变换。这个矩阵（正交阵，即各向量相互正交的矩阵，参见下文&ldquo;延伸阅读&rdquo;小节）的逆矩阵恰好也就是其转置矩阵，计算十分简单：</p>
<pre class="brush:c">invTBN = transpose(TBN)<&#47;pre><br />
亦即：<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transposeTBN.png"><img class="alignnone size-full wp-image-309 whiteborder" title="transposeTBN" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;transposeTBN.png" alt="" width="262" height="70" &#47;><&#47;a></p>
<h1>准备VBO<&#47;h1></p>
<h2>计算切线和副切线<&#47;h2><br />
我们需要为整个模型计算切线、副切线和法线。我们用一个单独的函数完成这些计算</p>
<pre class="brush: cpp">void computeTangentBasis(<br />
    &#47;&#47; inputs<br />
    std::vector &amp; vertices,<br />
    std::vector &amp; uvs,<br />
    std::vector &amp; normals,<br />
    &#47;&#47; outputs<br />
    std::vector &amp; tangents,<br />
    std::vector &amp; bitangents<br />
){<&#47;pre><br />
为每个三角形计算边（deltaPos）和deltaUV</p>
<pre class="brush: cpp">    for ( int i=0; i<vertices.size(); i+=3){</p>
<p>        &#47;&#47; Shortcuts for vertices<br />
        glm::vec3 &amp; v0 = vertices[i+0];<br />
        glm::vec3 &amp; v1 = vertices[i+1];<br />
        glm::vec3 &amp; v2 = vertices[i+2];</p>
<p>        &#47;&#47; Shortcuts for UVs<br />
        glm::vec2 &amp; uv0 = uvs[i+0];<br />
        glm::vec2 &amp; uv1 = uvs[i+1];<br />
        glm::vec2 &amp; uv2 = uvs[i+2];</p>
<p>        &#47;&#47; Edges of the triangle : postion delta<br />
        glm::vec3 deltaPos1 = v1-v0;<br />
        glm::vec3 deltaPos2 = v2-v0;</p>
<p>        &#47;&#47; UV delta<br />
        glm::vec2 deltaUV1 = uv1-uv0;<br />
        glm::vec2 deltaUV2 = uv2-uv0;<&#47;pre><br />
现在用公式来算切线和副切线：</p>
<pre class="brush: cpp">        float r = 1.0f &#47; (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);<br />
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;<br />
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;<&#47;pre><br />
最后，把这些<em>切线<&#47;em>和<em>副切线<&#47;em>缓存起来。记住，我们还没为这些缓存的数据生成索引，因此每个顶点都有一份拷贝</p>
<pre class="brush: cpp">        &#47;&#47; Set the same tangent for all three vertices of the triangle.<br />
        &#47;&#47; They will be merged later, in vboindexer.cpp<br />
        tangents.push_back(tangent);<br />
        tangents.push_back(tangent);<br />
        tangents.push_back(tangent);</p>
<p>        &#47;&#47; Same thing for binormals<br />
        bitangents.push_back(bitangent);<br />
        bitangents.push_back(bitangent);<br />
        bitangents.push_back(bitangent);</p>
<p>    }<&#47;pre></p>
<h2>索引<&#47;h2><br />
索引VBO的方法和之前类似，仅有些许不同。</p>
<p>找到相似顶点（相同的坐标、法线、纹理坐标）后，我们不直接用它的切线、副法线，而是取其均值。因此，只需把老代码修改一下：</p>
<pre class="brush: cpp">        &#47;&#47; Try to find a similar vertex in out_XXXX<br />
        unsigned int index;<br />
        bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);</p>
<p>        if ( found ){ &#47;&#47; A similar vertex is already in the VBO, use it instead !<br />
            out_indices.push_back( index );</p>
<p>            &#47;&#47; Average the tangents and the bitangents<br />
            out_tangents[index] += in_tangents[i];<br />
            out_bitangents[index] += in_bitangents[i];<br />
        }else{ &#47;&#47; If not, it needs to be added in the output data.<br />
            &#47;&#47; Do as usual<br />
            [...]<br />
        }<&#47;pre><br />
注意，这里没有对结果归一化。这种做法十分便利。由于小三角形的切线、副切线向量较小；相对于大三角形来说，对模型外观的影响程度较小。</p>
<h1>着色器<&#47;h1></p>
<h2>新增缓冲和uniform变量<&#47;h2><br />
我们需要再加两个缓冲，分别存储切线和副切线：</p>
<pre class="brush: cpp">    GLuint tangentbuffer;<br />
    glGenBuffers(1, &amp;tangentbuffer);<br />
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);<br />
    glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &amp;indexed_tangents[0], GL_STATIC_DRAW);</p>
<p>    GLuint bitangentbuffer;<br />
    glGenBuffers(1, &amp;bitangentbuffer);<br />
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);<br />
    glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &amp;indexed_bitangents[0], GL_STATIC_DRAW);<&#47;pre><br />
还需要一个uniform变量存储新增的法线纹理：</p>
<pre class="brush: cpp">    [...]<br />
    GLuint NormalTexture = loadTGA_glfw("normal.tga");<br />
    [...]<br />
    GLuint NormalTextureID  = glGetUniformLocation(programID, "NormalTextureSampler");<&#47;pre><br />
另外一个uniform变量存储3x3的模型视图矩阵。严格地讲，这个矩阵可有可无，它仅仅是让计算更方便罢了；详见后文。由于仅仅计算旋转，不需要平移，因此只需矩阵左上角3x3的部分。</p>
<pre class="brush: cpp">    GLuint ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");<&#47;pre><br />
完整的绘制代码如下：</p>
<pre class="brush: cpp">        &#47;&#47; Clear the screen<br />
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);</p>
<p>        &#47;&#47; Use our shader<br />
        glUseProgram(programID);</p>
<p>        &#47;&#47; Compute the MVP matrix from keyboard and mouse input<br />
        computeMatricesFromInputs();<br />
        glm::mat4 ProjectionMatrix = getProjectionMatrix();<br />
        glm::mat4 ViewMatrix = getViewMatrix();<br />
        glm::mat4 ModelMatrix = glm::mat4(1.0);<br />
        glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;<br />
        glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); &#47;&#47; Take the upper-left part of ModelViewMatrix<br />
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;</p>
<p>        &#47;&#47; Send our transformation to the currently bound shader,<br />
        &#47;&#47; in the "MVP" uniform<br />
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &amp;MVP[0][0]);<br />
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &amp;ModelMatrix[0][0]);<br />
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &amp;ViewMatrix[0][0]);<br />
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &amp;ViewMatrix[0][0]);<br />
        glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &amp;ModelView3x3Matrix[0][0]);</p>
<p>        glm::vec3 lightPos = glm::vec3(0,0,4);<br />
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);</p>
<p>        &#47;&#47; Bind our diffuse texture in Texture Unit 0<br />
        glActiveTexture(GL_TEXTURE0);<br />
        glBindTexture(GL_TEXTURE_2D, DiffuseTexture);<br />
        &#47;&#47; Set our "DiffuseTextureSampler" sampler to user Texture Unit 0<br />
        glUniform1i(DiffuseTextureID, 0);</p>
<p>        &#47;&#47; Bind our normal texture in Texture Unit 1<br />
        glActiveTexture(GL_TEXTURE1);<br />
        glBindTexture(GL_TEXTURE_2D, NormalTexture);<br />
        &#47;&#47; Set our "Normal    TextureSampler" sampler to user Texture Unit 0<br />
        glUniform1i(NormalTextureID, 1);</p>
<p>        &#47;&#47; 1rst attribute buffer : vertices<br />
        glEnableVertexAttribArray(0);<br />
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);<br />
        glVertexAttribPointer(<br />
            0,                  &#47;&#47; attribute<br />
            3,                  &#47;&#47; size<br />
            GL_FLOAT,           &#47;&#47; type<br />
            GL_FALSE,           &#47;&#47; normalized?<br />
            0,                  &#47;&#47; stride<br />
            (void*)0            &#47;&#47; array buffer offset<br />
        );</p>
<p>        &#47;&#47; 2nd attribute buffer : UVs<br />
        glEnableVertexAttribArray(1);<br />
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);<br />
        glVertexAttribPointer(<br />
            1,                                &#47;&#47; attribute<br />
            2,                                &#47;&#47; size<br />
            GL_FLOAT,                         &#47;&#47; type<br />
            GL_FALSE,                         &#47;&#47; normalized?<br />
            0,                                &#47;&#47; stride<br />
            (void*)0                          &#47;&#47; array buffer offset<br />
        );</p>
<p>        &#47;&#47; 3rd attribute buffer : normals<br />
        glEnableVertexAttribArray(2);<br />
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);<br />
        glVertexAttribPointer(<br />
            2,                                &#47;&#47; attribute<br />
            3,                                &#47;&#47; size<br />
            GL_FLOAT,                         &#47;&#47; type<br />
            GL_FALSE,                         &#47;&#47; normalized?<br />
            0,                                &#47;&#47; stride<br />
            (void*)0                          &#47;&#47; array buffer offset<br />
        );</p>
<p>        &#47;&#47; 4th attribute buffer : tangents<br />
        glEnableVertexAttribArray(3);<br />
        glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);<br />
        glVertexAttribPointer(<br />
            3,                                &#47;&#47; attribute<br />
            3,                                &#47;&#47; size<br />
            GL_FLOAT,                         &#47;&#47; type<br />
            GL_FALSE,                         &#47;&#47; normalized?<br />
            0,                                &#47;&#47; stride<br />
            (void*)0                          &#47;&#47; array buffer offset<br />
        );</p>
<p>        &#47;&#47; 5th attribute buffer : bitangents<br />
        glEnableVertexAttribArray(4);<br />
        glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);<br />
        glVertexAttribPointer(<br />
            4,                                &#47;&#47; attribute<br />
            3,                                &#47;&#47; size<br />
            GL_FLOAT,                         &#47;&#47; type<br />
            GL_FALSE,                         &#47;&#47; normalized?<br />
            0,                                &#47;&#47; stride<br />
            (void*)0                          &#47;&#47; array buffer offset<br />
        );</p>
<p>        &#47;&#47; Index buffer<br />
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);</p>
<p>        &#47;&#47; Draw the triangles !<br />
        glDrawElements(<br />
            GL_TRIANGLES,      &#47;&#47; mode<br />
            indices.size(),    &#47;&#47; count<br />
            GL_UNSIGNED_INT,   &#47;&#47; type<br />
            (void*)0           &#47;&#47; element array buffer offset<br />
        );</p>
<p>        glDisableVertexAttribArray(0);<br />
        glDisableVertexAttribArray(1);<br />
        glDisableVertexAttribArray(2);<br />
        glDisableVertexAttribArray(3);<br />
        glDisableVertexAttribArray(4);</p>
<p>        &#47;&#47; Swap buffers<br />
        glfwSwapBuffers();<&#47;pre></p>
<h2>顶点着色器<&#47;h2><br />
如前所述，所有计算都摄像机空间中做，因为在这一空间中更容易获取片段坐标。这就是为什么要用模型视图矩阵乘T、B、N向量。</p>
<pre class="brush:fs">    vertexNormal_cameraspace = MV3x3 * normalize(vertexNormal_modelspace);<br />
    vertexTangent_cameraspace = MV3x3 * normalize(vertexTangent_modelspace);<br />
    vertexBitangent_cameraspace = MV3x3 * normalize(vertexBitangent_modelspace);<&#47;pre><br />
这三个向量确定了TBN矩阵，其创建方式如下：</p>
<pre>    mat3 TBN = transpose(mat3(<br />
        vertexTangent_cameraspace,<br />
        vertexBitangent_cameraspace,<br />
        vertexNormal_cameraspace<br />
    )); &#47;&#47; You can use dot products instead of building this matrix and transposing it. See References for details.<&#47;pre><br />
此矩阵是从摄像机空间到切线空间的变换（若矩阵名为XXX_modelspace，则是从模型空间到切线空间的变换）。我们可以利用它计算切线空间中的光线方向和视线方向。</p>
<pre>    LightDirection_tangentspace = TBN * LightDirection_cameraspace;<br />
    EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;<&#47;pre></p>
<h2>片段着色器<&#47;h2><br />
切线空间中的法线很容易获取&mdash;&mdash;就在纹理中：</p>
<pre class="brush:fs">    &#47;&#47; Local normal, in tangent space<br />
    vec3 TextureNormal_tangentspace = normalize(texture2D( NormalTextureSampler, UV ).rgb*2.0 - 1.0);<&#47;pre><br />
&nbsp;</p>
<p>一切准备就绪。漫反射光的值由切线空间中的n和l计算得来（在哪个空间中计算并不重要，关键是n和l必须位于同一空间中），并用<em>clamp( dot( n,l ), 0,1 )<&#47;em>截取。镜面光用<&#47;em>clamp( dot( E,R ), 0,1 )<&#47;em>截取，E和R也必须位于同一空间中。大功告成！</p>
<h1>结果<&#47;h1><br />
这是目前得到的结果，您可以看到：</p>
<ul>
<li>砖块看上去凹凸不平，这是因为砖块表面法线变化比较剧烈<&#47;li>
<li>水泥部分看上去很平整，这是因为这部分的法线纹理全都是蓝色<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normalmapping.png"><img class="alignnone size-large wp-image-315" title="normalmapping" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normalmapping-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<h1>延伸阅读<&#47;h1></p>
<h2>正交化（Orthogonalization）<&#47;h2><br />
顶点着色器中，为了计算速度，我们没有进行矩阵求逆，而是进行了转置。这只有当矩阵表示的空间正交时才成立，而这个矩阵还不是正交的。好在这个问题很容易解决：只需在computeTangentBasis()末尾让切线与法线垂直。</p>
<pre class="brush:vs">t = glm::normalize(t - n * glm::dot(n, t));<&#47;pre><br />
这个公式有点难理解，来看看图：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;gramshmidt.png"><img class="alignnone size-full wp-image-319 whiteborder" title="gramshmidt" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;gramshmidt.png" alt="" width="300" height="157" &#47;><&#47;a></p>
<p>n和t差不多是相互垂直的，只要把t沿-n方向稍微&ldquo;推&rdquo;一下，幅度是dot(n,t)。</p>
<p><a href="http:&#47;&#47;www.cse.illinois.edu&#47;iem&#47;least_squares&#47;gram_schmidt&#47;">这里<&#47;a>有一个applet也演示得很清楚（仅含两个向量）。</p>
<h2>左手系还是右手系？<&#47;h2><br />
一般不必担心这个问题。但在某些情况下，比如使用对称模型时，UV坐标方向会出错，导致切线T方向错误。</p>
<p>判断是否需要翻转坐标系很容易：TBN必须形成一个右手坐标系&mdash;&mdash;向量cross(n,t)应该和b同向。</p>
<p>用数学术语讲，&ldquo;向量A和向量B同向&rdquo;则有&ldquo;dot(A,B)>0&rdquo;；故只需检查dot( cross(n,t) , b )是否大于0。</p>
<p>若dot( cross(n,t) , b ) < 0，就要翻转t：</p>
<pre class="brush: c">if (glm::dot(glm::cross(n, t), b) < 0.0f){<br />
&nbsp;&nbsp;&nbsp;&nbsp; t = t * -1.0f;<br />
 }<&#47;pre><br />
在computeTangentBasis()末对每个顶点都做这个操作。</p>
<h2>镜面纹理（Specular texture）<&#47;h2><br />
为了增强趣味性，我在代码里加上了镜面纹理；取代了原先作为镜面颜色的灰色vec3(0.3,0.3,0.3)。镜面纹理看起来像这样：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;specular.jpg"><img class="alignnone size-full wp-image-317" title="specular" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;specular.jpg" alt="" width="351" height="335" &#47;><&#47;a></p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normalmappingwithspeculartexture.png"><img class="alignnone size-large wp-image-316" title="normalmappingwithspeculartexture" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normalmappingwithspeculartexture-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>请注意，由于如上镜面纹理中没有镜面分量，水泥部分均呈黑色。</p>
<h2>用立即模式（immediate mode）进行调试<&#47;h2><br />
本站的初衷是让大家<strong>不再使用<&#47;strong>已被废弃、缓慢、问题频出的立即模式。</p>
<p>不过，用立即模式进行调试却十分方便：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;immediatemodedebugging.png"><img class="alignnone size-large wp-image-314" title="immediatemodedebugging" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;immediatemodedebugging-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>这里，我们在立即模式下画了一些线条表示切线空间。</p>
<p>要进入立即模式，必须先关闭3.3 Core Profile：</p>
<pre class="brush: cpp">glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);<&#47;pre><br />
然后把矩阵传给旧式的OpenGL流水线（你也可以另写一个着色器，不过这样做更简单，反正都是在hacking）：</p>
<pre class="brush: cpp">glMatrixMode(GL_PROJECTION);<br />
glLoadMatrixf((const GLfloat*)&amp;ProjectionMatrix[0]);<br />
glMatrixMode(GL_MODELVIEW);<br />
glm::mat4 MV = ViewMatrix * ModelMatrix;<br />
glLoadMatrixf((const GLfloat*)&amp;MV[0]);<&#47;pre><br />
禁用着色器：</p>
<pre class="brush: cpp">glUseProgram(0);<&#47;pre><br />
然后绘制线条（本例中法线都已被归一化，乘以0.1，置于对应顶点上）：</p>
<pre class="brush: cpp">glColor3f(0,0,1);<br />
glBegin(GL_LINES);<br />
for (int i=0; i<indices.size(); i++){<br />
&nbsp;&nbsp;&nbsp; glm::vec3 p = indexed_vertices[indices[i]];<br />
&nbsp;&nbsp;&nbsp; glVertex3fv(&amp;p.x);<br />
&nbsp;&nbsp;&nbsp; glm::vec3 o = glm::normalize(indexed_normals[indices[i]]);<br />
&nbsp;&nbsp;&nbsp; p+=o*0.1f;<br />
&nbsp;&nbsp;&nbsp; glVertex3fv(&amp;p.x);<br />
}<br />
glEnd();<&#47;pre><br />
切记：实际项目中不要用立即模式！仅限调试时使用！别忘了之后恢复到Core Profile，它可以保证不启用立即模式！</p>
<h2>利用颜色进行调试<&#47;h2><br />
调试时，将向量的值可视化很有用处。最简单的方法是把向量都写到帧缓冲。举个例子，我们把LightDirection_tangentspace可视化一下试试：</p>
<pre class="brush:fs">color.xyz = LightDirection_tangentspace;<&#47;pre><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;colordebugging.png"><img class="alignnone size-large wp-image-313" title="colordebugging" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;colordebugging-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>这说明：</p>
<ul>
<li>在圆柱体的右侧，光线（如白色线条所示）是朝上（在切线空间中）的。也就是说，光线和三角形的法线同向。<&#47;li>
<li>在圆柱体的中间部分，光线和切线方向（指向+X）同向。<&#47;li><br />
<&#47;ul><br />
一些提示：</p>
<ul>
<li>可视化前，变量是否需要归一化取决于具体情况。<&#47;li>
<li>如果结果不易理解，就逐个分量可视化。比如，只观察红色，而将绿色和蓝色分量强制设为0。<&#47;li>
<li>alpha值过于复杂，别折腾 :)<&#47;li>
<li>若想将一个负值可视化，可以采用和处理法线纹理一样的技巧：转而把`(v+1.0)&#47;2.0`可视化，于是黑色就代表-1，而白色代表+1。只不过这样做会让结果不直观。<&#47;li><br />
<&#47;ul><br />
&nbsp;</p>
<h2>利用变量名进行调试<&#47;h2><br />
前面已经讲过了，搞清楚向量所处的空间是关键。千万别用摄像机空间里的向量点乘模型空间里的向量。</p>
<p>给向量名称添加&ldquo;_modelspace&rdquo;后缀可以有效地避免这类计算错误。</p>
<h1>怎样制作法线贴图<&#47;h1><br />
作者James O&rsquo;Hare。点击图片放大。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normalMapMiniTut.jpg"><img title="normalMapMiniTut" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;normalMapMiniTut-320x1024.jpg" alt="How to create a normal map" width="320" height="1024"><&#47;a></p>
<h1>练习<&#47;h1></p>
<ul>
<li>在indexVBO_TBN函数中，做加法前先把向量归一化，观察其作用。<&#47;li>
<li>用颜色可视化其他向量（如instance、EyeDirection_tangentspace），试着解释你看到的结果。<&#47;li><br />
<&#47;ul></p>
<h1>工具和链接<&#47;h1></p>
<ul>
<li><a href="http:&#47;&#47;www.crazybump.com&#47;">Crazybump<&#47;a>制作法线纹理的好工具，付费。<&#47;li>
<li><a href="http:&#47;&#47;developer.nvidia.com&#47;nvidia-texture-tools-adobe-photoshop">Nvidia's photoshop plugin<&#47;a>免费，不过Photoshop不免费&hellip;&hellip;<&#47;li>
<li><a href="http:&#47;&#47;www.zarria.net&#47;nrmphoto&#47;nrmphoto.html">用多幅照片制作法线贴图<&#47;a><&#47;li>
<li><a href="http:&#47;&#47;www.katsbits.com&#47;tutorials&#47;textures&#47;making-normal-maps-from-photographs.php">用单幅照片制作法线贴图<&#47;a><&#47;li>
<li>关于<a href="http:&#47;&#47;www.katjaas.nl&#47;transpose&#47;transpose.html">矩阵转置<&#47;a>的详细资料<&#47;li><br />
<&#47;ul></p>
<h1>参考文献<&#47;h1></p>
<ul>
<li><a href="http:&#47;&#47;www.terathon.com&#47;code&#47;tangent.html">Lengyel, Eric. &ldquo;Computing Tangent Space Basis Vectors for an Arbitrary Mesh&rdquo;. Terathon Software 3D Graphics Library, 2001.<&#47;a><&#47;li>
<li><a href="http:&#47;&#47;www.amazon.com&#47;dp&#47;1568814240">Real Time Rendering, third edition<&#47;a><&#47;li>
<li><a href="http:&#47;&#47;www.amazon.com&#47;dp&#47;1584504250">ShaderX4<&#47;a><&#47;li><br />
<&#47;ul><br />
&nbsp;</p>
