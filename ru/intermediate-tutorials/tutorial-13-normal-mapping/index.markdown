---
layout: page
status: publish
published: true
title: 'Tutorial 13 : Normal Mapping'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 301
wordpress_url: http://www.opengl-tutorial.org/?page_id=301
date: '2011-05-26 06:07:04 +0200'
date_gmt: '2011-05-26 06:07:04 +0200'
categories: [tuto]
order: 50
tags: []
language: ru
---
<p>Welcome for our 13th tutorial ! Today we will talk about normal mapping.</p>
<p>Since <a title="Tutorial 8 : Basic shading" href="http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/">Tutorial 8 : Basic shading</a> , you know how to get decent shading using triangle normals. One caveat is that until now, we only had one normal per vertex : inside each triangle, they vary smoothly, on the opposite to the colour, which samples a texture. The basic idea of normal mapping is to give normals similar variations.</p>
<h1>Normal textures</h1><br />
A "normal texture" looks like this :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normal.jpg"><img class="alignnone size-full wp-image-307" title="normal" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normal.jpg" alt="" width="341" height="336" /></a></p>
<p>In each RGB texel is encoded a XYZ vector : each colour component is between 0 and 1, and each vector component is between -1 and 1, so this simple mapping goes from the texel to the normal :</p>
<pre class="brush:c">normal = (2*color)-1 // on each component</pre><br />
The texture has a general blue tone because overall, the normal is towards the "outside of the surface"; as usual, X is right and Y is up.</p>
<p>This texture is mapped just like the diffuse one; The big problem is how to convert our normal, which is expressed in the space each individual triangle ( tangent space, also called image space), in model space (since this is what is used in our shading equation).</p>
<h1>Tangent and Bitangent</h1><br />
You are now so familiar with matrices that you know that in order to define a space (in our case, the tangent space), we need 3 vectors. We already have our UP vector : it's the normal, given by Blender or computed from the triangle by a simple cross product. It's represented in blue, just like the overall color of the normal map :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/NormalVector.png"><img class="alignnone size-full wp-image-821" title="NormalVector" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/NormalVector.png" alt="" width="480" height="270" /></a></p>
<p>Next we need a tangent, T : a vector perpendicular to the surface. But there are many such vectors :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/TangentVectors.png"><img class="alignnone size-full wp-image-822" title="TangentVectors" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/TangentVectors.png" alt="" width="480" height="270" /></a></p>
<p>Which one should we choose ? In theory, any, but we have to be consistent with the neighbors to avoid introducing ugly edges. The standard method is to orient the tangent in the same direction that our texture coordinates :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/TangentVectorFromUVs.png"><img class="alignnone size-full wp-image-823" title="TangentVectorFromUVs" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/TangentVectorFromUVs.png" alt="" width="480" height="270" /></a></p>
<p>Since we need 3 vectors to define a basis, we must also compute the bitangent B (which is any other tangent vector, but if everything is perpendicular, math is simpler) :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/NTBFromUVs.png"><img class="alignnone size-full wp-image-824" title="NTBFromUVs" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/NTBFromUVs.png" alt="" width="480" height="270" /></a></p>
<p>&nbsp;</p>
<p>Here is the algorithm : if we note deltaPos1 and deltaPos2 two edges of our triangle, and deltaUV1 and deltaUV2 the corresponding differences in UVs, we can express our problem with the following equation :</p>
<pre class="brush:c">deltaPos1 = deltaUV1.x * T + deltaUV1.y * B<br />
deltaPos2 = deltaUV2.x * T + deltaUV2.y * B</pre><br />
Just solve this system for T and B, and you have your vectors ! (See code below)</p>
<p>Once we have our T, B, N vectors, we also have this nice matrix which enables us to go from&nbsp;Tangent Space to Model Space :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/TBN.png"><img class="alignnone size-full wp-image-308 whiteborder" title="TBN" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/TBN.png" alt="" width="107" height="66" /></a></p>
<p>With this TBN matrix, we can transform normals (extracted from the texture) into model space. However, it's usually done the other way around : transform everything from Model Space to Tangent Space, and keep the extracted normal as-is. All computations are done in Tangent Space, which doesn't changes anything.</p>
<p>Do have this inverse transformation, we simply have to take the matrix inverse, which in this case (an orthogonal matrix, i.e each vector is perpendicular to the others. See "going further" below) is also its transpose, much cheaper to compute :</p>
<pre class="brush:c">invTBN = transpose(TBN)</pre><br />
, i.e. :<br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transposeTBN.png"><img class="alignnone size-full wp-image-309 whiteborder" title="transposeTBN" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/transposeTBN.png" alt="" width="262" height="70" /></a></p>
<h1>Preparing our VBO</h1></p>
<h2>Computing the tangents and bitangents</h2><br />
Since we need our tangents and bitangents on top of our normals, we have to compute them for the whole mesh. We'll do this in a separate function :</p>
<pre class="brush: cpp">void computeTangentBasis(<br />
    // inputs<br />
    std::vector<glm::vec3> &amp; vertices,<br />
    std::vector<glm::vec2> &amp; uvs,<br />
    std::vector<glm::vec3> &amp; normals,<br />
    // outputs<br />
    std::vector<glm::vec3> &amp; tangents,<br />
    std::vector<glm::vec3> &amp; bitangents<br />
){</pre><br />
For each triangle, we compute the edge (deltaPos) and the deltaUV</p>
<pre class="brush: cpp">    for ( int i=0; i<vertices.size(); i+=3){</p>
<p>        // Shortcuts for vertices<br />
        glm::vec3 &amp; v0 = vertices[i+0];<br />
        glm::vec3 &amp; v1 = vertices[i+1];<br />
        glm::vec3 &amp; v2 = vertices[i+2];</p>
<p>        // Shortcuts for UVs<br />
        glm::vec2 &amp; uv0 = uvs[i+0];<br />
        glm::vec2 &amp; uv1 = uvs[i+1];<br />
        glm::vec2 &amp; uv2 = uvs[i+2];</p>
<p>        // Edges of the triangle : postion delta<br />
        glm::vec3 deltaPos1 = v1-v0;<br />
        glm::vec3 deltaPos2 = v2-v0;</p>
<p>        // UV delta<br />
        glm::vec2 deltaUV1 = uv1-uv0;<br />
        glm::vec2 deltaUV2 = uv2-uv0;</pre><br />
We can now use our formula to compute the tangent and the bitangent :</p>
<pre class="brush: cpp">        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);<br />
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;<br />
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;</pre><br />
Finally, we fill the <em>tangents </em>and <em>bitangents </em>buffers. Remember, these buffers are not indexed yet, so each vertex has its own copy.</p>
<pre class="brush: cpp">        // Set the same tangent for all three vertices of the triangle.<br />
        // They will be merged later, in vboindexer.cpp<br />
        tangents.push_back(tangent);<br />
        tangents.push_back(tangent);<br />
        tangents.push_back(tangent);</p>
<p>        // Same thing for binormals<br />
        bitangents.push_back(bitangent);<br />
        bitangents.push_back(bitangent);<br />
        bitangents.push_back(bitangent);</p>
<p>    }</pre></p>
<h2>Indexing</h2><br />
Indexing our VBO is very similar to what we used to do, but there is a subtle difference.</p>
<p>If we find a similar vertex (same position, same normal, same texture coordinates), we don't want to use its tangent and binormal too ; on the contrary, we want to average them. So let's modify our old code a bit :</p>
<pre class="brush: cpp">        // Try to find a similar vertex in out_XXXX<br />
        unsigned int index;<br />
        bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);</p>
<p>        if ( found ){ // A similar vertex is already in the VBO, use it instead !<br />
            out_indices.push_back( index );</p>
<p>            // Average the tangents and the bitangents<br />
            out_tangents[index] += in_tangents[i];<br />
            out_bitangents[index] += in_bitangents[i];<br />
        }else{ // If not, it needs to be added in the output data.<br />
            // Do as usual<br />
            [...]<br />
        }</pre><br />
Note that we don't normalize anything here. This is actually handy, because this way, small triangles, which have smaller tangent and bitangent vectors, will have a weaker effect on the final vectors than big triangles (which contribute more to the final shape).</p>
<h1>The shader</h1></p>
<h2>Additional buffers &amp; uniforms</h2><br />
We need two new buffers : one for the tangents, and one for the bitangents :</p>
<pre class="brush: cpp">    GLuint tangentbuffer;<br />
    glGenBuffers(1, &amp;tangentbuffer);<br />
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);<br />
    glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &amp;indexed_tangents[0], GL_STATIC_DRAW);</p>
<p>    GLuint bitangentbuffer;<br />
    glGenBuffers(1, &amp;bitangentbuffer);<br />
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);<br />
    glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &amp;indexed_bitangents[0], GL_STATIC_DRAW);</pre><br />
We also need a new uniform for our new normal texture :</p>
<pre class="brush: cpp">    [...]<br />
    GLuint NormalTexture = loadTGA_glfw("normal.tga");<br />
    [...]<br />
    GLuint NormalTextureID  = glGetUniformLocation(programID, "NormalTextureSampler");</pre><br />
And one for the 3x3 ModelView matrix. This is strictly speaking not necessary, but it's easier ; more about this later. We just need the 3x3 upper-left part because we will multiply directions, so we can drop the translation part.</p>
<pre class="brush: cpp">    GLuint ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");</pre><br />
So the full drawing code becomes :</p>
<pre class="brush: cpp">        // Clear the screen<br />
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);</p>
<p>        // Use our shader<br />
        glUseProgram(programID);</p>
<p>        // Compute the MVP matrix from keyboard and mouse input<br />
        computeMatricesFromInputs();<br />
        glm::mat4 ProjectionMatrix = getProjectionMatrix();<br />
        glm::mat4 ViewMatrix = getViewMatrix();<br />
        glm::mat4 ModelMatrix = glm::mat4(1.0);<br />
        glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;<br />
        glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); // Take the upper-left part of ModelViewMatrix<br />
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;</p>
<p>        // Send our transformation to the currently bound shader,<br />
        // in the "MVP" uniform<br />
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &amp;MVP[0][0]);<br />
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &amp;ModelMatrix[0][0]);<br />
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &amp;ViewMatrix[0][0]);<br />
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &amp;ViewMatrix[0][0]);<br />
        glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &amp;ModelView3x3Matrix[0][0]);</p>
<p>        glm::vec3 lightPos = glm::vec3(0,0,4);<br />
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);</p>
<p>        // Bind our diffuse texture in Texture Unit 0<br />
        glActiveTexture(GL_TEXTURE0);<br />
        glBindTexture(GL_TEXTURE_2D, DiffuseTexture);<br />
        // Set our "DiffuseTextureSampler" sampler to user Texture Unit 0<br />
        glUniform1i(DiffuseTextureID, 0);</p>
<p>        // Bind our normal texture in Texture Unit 1<br />
        glActiveTexture(GL_TEXTURE1);<br />
        glBindTexture(GL_TEXTURE_2D, NormalTexture);<br />
        // Set our "Normal    TextureSampler" sampler to user Texture Unit 0<br />
        glUniform1i(NormalTextureID, 1);</p>
<p>        // 1rst attribute buffer : vertices<br />
        glEnableVertexAttribArray(0);<br />
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);<br />
        glVertexAttribPointer(<br />
            0,                  // attribute<br />
            3,                  // size<br />
            GL_FLOAT,           // type<br />
            GL_FALSE,           // normalized?<br />
            0,                  // stride<br />
            (void*)0            // array buffer offset<br />
        );</p>
<p>        // 2nd attribute buffer : UVs<br />
        glEnableVertexAttribArray(1);<br />
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);<br />
        glVertexAttribPointer(<br />
            1,                                // attribute<br />
            2,                                // size<br />
            GL_FLOAT,                         // type<br />
            GL_FALSE,                         // normalized?<br />
            0,                                // stride<br />
            (void*)0                          // array buffer offset<br />
        );</p>
<p>        // 3rd attribute buffer : normals<br />
        glEnableVertexAttribArray(2);<br />
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);<br />
        glVertexAttribPointer(<br />
            2,                                // attribute<br />
            3,                                // size<br />
            GL_FLOAT,                         // type<br />
            GL_FALSE,                         // normalized?<br />
            0,                                // stride<br />
            (void*)0                          // array buffer offset<br />
        );</p>
<p>        // 4th attribute buffer : tangents<br />
        glEnableVertexAttribArray(3);<br />
        glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);<br />
        glVertexAttribPointer(<br />
            3,                                // attribute<br />
            3,                                // size<br />
            GL_FLOAT,                         // type<br />
            GL_FALSE,                         // normalized?<br />
            0,                                // stride<br />
            (void*)0                          // array buffer offset<br />
        );</p>
<p>        // 5th attribute buffer : bitangents<br />
        glEnableVertexAttribArray(4);<br />
        glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);<br />
        glVertexAttribPointer(<br />
            4,                                // attribute<br />
            3,                                // size<br />
            GL_FLOAT,                         // type<br />
            GL_FALSE,                         // normalized?<br />
            0,                                // stride<br />
            (void*)0                          // array buffer offset<br />
        );</p>
<p>        // Index buffer<br />
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);</p>
<p>        // Draw the triangles !<br />
        glDrawElements(<br />
            GL_TRIANGLES,      // mode<br />
            indices.size(),    // count<br />
            GL_UNSIGNED_INT,   // type<br />
            (void*)0           // element array buffer offset<br />
        );</p>
<p>        glDisableVertexAttribArray(0);<br />
        glDisableVertexAttribArray(1);<br />
        glDisableVertexAttribArray(2);<br />
        glDisableVertexAttribArray(3);<br />
        glDisableVertexAttribArray(4);</p>
<p>        // Swap buffers<br />
        glfwSwapBuffers();</pre></p>
<h2>Vertex shader</h2><br />
As said before, we'll do everything in camera space, because it's simpler to get the fragment's position in this space. This is why we multiply our T,B,N vectors with the ModelView matrix.</p>
<pre class="brush:fs">    vertexNormal_cameraspace = MV3x3 * normalize(vertexNormal_modelspace);<br />
    vertexTangent_cameraspace = MV3x3 * normalize(vertexTangent_modelspace);<br />
    vertexBitangent_cameraspace = MV3x3 * normalize(vertexBitangent_modelspace);</pre><br />
These three vector define a the TBN matrix, which is constructed this way :</p>
<pre>    mat3 TBN = transpose(mat3(<br />
        vertexTangent_cameraspace,<br />
        vertexBitangent_cameraspace,<br />
        vertexNormal_cameraspace<br />
    )); // You can use dot products instead of building this matrix and transposing it. See References for details.</pre><br />
This matrix goes from camera space to tangent space (The same matrix, but with XXX_modelspace instead, would go from model space to tangent space). We can use it to compute the light direction and the eye direction, in tangent space :</p>
<pre>    LightDirection_tangentspace = TBN * LightDirection_cameraspace;<br />
    EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;</pre></p>
<h2>Fragment shader</h2><br />
Our normal, in tangent space, is really straightforward to get : it's our texture :</p>
<pre class="brush:fs">    // Local normal, in tangent space<br />
    vec3 TextureNormal_tangentspace = normalize(texture2D( NormalTextureSampler, UV ).rgb*2.0 - 1.0);</pre><br />
&nbsp;</p>
<p>So we've got everything we need now. Diffuse lighting uses <em>clamp( dot( n,l ), 0,1 )</em>, with n and l expressed in tangent space (it doesn't matter in which space you make your dot and cross products; the important thing is that n and l are both expressed in the same space). Specular lighting uses <em>clamp( dot( E,R ), 0,1 )</em>, again with E and R expressed in tangent space. Yay !</p>
<h1>Results</h1><br />
Here is our result so far. You can notice that :</p>
<ul>
<li>The bricks look bumpy because we have lots of variations in the normals</li>
<li>Cement looks flat because the&nbsp; normal texture is uniformly blue</li><br />
</ul><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normalmapping.png"><img class="alignnone size-large wp-image-315" title="normalmapping" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normalmapping-1024x793.png" alt="" width="640" height="495" /></a></p>
<h1>Going further</h1></p>
<h2>Orthogonalization</h2><br />
In our vertex shader we took the transpose instead of the inverse because it's faster. But it only works if the space that the matrix represents is orthogonal, which is not yet the case. Luckily, this is very easy to fix : we just have to make the tangent perpendicular to the normal at he end of computeTangentBasis() :</p>
<pre class="brush:vs">t = glm::normalize(t - n * glm::dot(n, t));</pre><br />
This formula may be hard to grasp, so a little schema might help :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/gramshmidt.png"><img class="alignnone size-full wp-image-319 whiteborder" title="gramshmidt" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/gramshmidt.png" alt="" width="300" height="157" /></a></p>
<p>n and t are almost perpendicular, so we "push" t in the direction of -n by a factor of dot(n,t)</p>
<p><a href="http://www.cse.illinois.edu/iem/least_squares/gram_schmidt/">Here</a>'s a little applet that explains it too (Use only 2 vectors).</p>
<h2>Handedness</h2><br />
You usually don't have to worry about that, but in some cases, when you use symmetric models, UVs are oriented in the wrong way, and your T has the wrong orientation.</p>
<p>To check whether it must be inverted or not, the check is simple : TBN must form a right-handed coordinate system, i.e. cross(n,t) must have the same orientation than b.</p>
<p>In mathematics, "Vector A has the same orientation as Vector B" translates as dot(A,B)>0, so we need to check if dot( cross(n,t) , b ) > 0.</p>
<p>If it's false, just invert t :</p>
<pre class="brush: c">if (glm::dot(glm::cross(n, t), b) < 0.0f){<br />
&nbsp;&nbsp;&nbsp;&nbsp; t = t * -1.0f;<br />
 }</pre><br />
This is also done for each vertex at the end of computeTangentBasis().</p>
<h2>Specular texture</h2><br />
Just for fun, I added a specular texture to the code. It looks like this :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/specular.jpg"><img class="alignnone size-full wp-image-317" title="specular" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/specular.jpg" alt="" width="351" height="335" /></a></p>
<p>and is used instead of the simple "vec3(0.3,0.3,0.3)" grey that we used as specular color.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normalmappingwithspeculartexture.png"><img class="alignnone size-large wp-image-316" title="normalmappingwithspeculartexture" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normalmappingwithspeculartexture-1024x793.png" alt="" width="640" height="495" /></a></p>
<p>Notice that now, cement is always black : the texture says that it has no specular component.</p>
<h2>Debugging with the immediate mode</h2><br />
The real aim of this website is that you DON'T use immediate mode, which is deprecated, slow, and problematic in many aspects.</p>
<p>However, it also happens to be really handy for debugging :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/immediatemodedebugging.png"><img class="alignnone size-large wp-image-314" title="immediatemodedebugging" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/immediatemodedebugging-1024x793.png" alt="" width="640" height="495" /></a></p>
<p>Here we visualize our tangent space with lines drawn in immediate mode.</p>
<p>For this, you need to abandon the 3.3 core profile :</p>
<pre class="brush: cpp">glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);</pre><br />
then give our matrices to OpenGL's old-school pipeline (you can write another shader too, but it's simpler this way, and you're hacking anyway) :</p>
<pre class="brush: cpp">glMatrixMode(GL_PROJECTION);<br />
glLoadMatrixf((const GLfloat*)&amp;ProjectionMatrix[0]);<br />
glMatrixMode(GL_MODELVIEW);<br />
glm::mat4 MV = ViewMatrix * ModelMatrix;<br />
glLoadMatrixf((const GLfloat*)&amp;MV[0]);</pre><br />
Disable shaders :</p>
<pre class="brush: cpp">glUseProgram(0);</pre><br />
And draw your lines (in this case, normals, normalized and multiplied by 0.1, and applied at the correct vertex) :</p>
<pre class="brush: cpp">glColor3f(0,0,1);<br />
glBegin(GL_LINES);<br />
for (int i=0; i<indices.size(); i++){<br />
&nbsp;&nbsp;&nbsp; glm::vec3 p = indexed_vertices[indices[i]];<br />
&nbsp;&nbsp;&nbsp; glVertex3fv(&amp;p.x);<br />
&nbsp;&nbsp;&nbsp; glm::vec3 o = glm::normalize(indexed_normals[indices[i]]);<br />
&nbsp;&nbsp;&nbsp; p+=o*0.1f;<br />
&nbsp;&nbsp;&nbsp; glVertex3fv(&amp;p.x);<br />
}<br />
glEnd();</pre><br />
Remember : don't use immediate mode in real world ! Only for debugging ! And don't forget to re-enable the core profile afterwards, it will make sure that you don't do such things.</p>
<h2>Debugging with colors</h2><br />
When debugging, it can be useful to visualize the value of a vector. The easiest way to do this is to write it on the framebuffer instead of the actual colour. For instance, let's visualize LightDirection_tangentspace :</p>
<pre class="brush:fs">color.xyz = LightDirection_tangentspace;</pre><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/colordebugging.png"><img class="alignnone size-large wp-image-313" title="colordebugging" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/colordebugging-1024x793.png" alt="" width="640" height="495" /></a></p>
<p>This means :</p>
<ul>
<li>On the right part of the cylinder, the light (represented by the small white line) is UP (in tangent space). In other words, the light is in the direction of the normal of the triangles.</li>
<li>On the middle part of the cylinder, the light is in the direction of the tangent (towards +X)</li><br />
</ul><br />
A few tips :</p>
<ul>
<li>Depending on what you're trying to visualize, you may want to normalize it.</li>
<li>If you can't make sense of what you're seeing, visualize all components separately by forcing for instance green and blue to 0.</li>
<li>Avoid messing with alpha, it's too complicated :)</li>
<li>If you want to visualize negative value, you can use the same trick that our normal textures use : visualize (v+1.0)/2.0 instead, so that black means -1 and full color means +1. It's hard to understand what you see, though.</li><br />
</ul><br />
&nbsp;</p>
<h2>Debugging with variable names</h2><br />
As already stated before, it's crucial to exactly know in which space your vectors are. Don't take the dot product of a vector in camera space and a vector in model space.</p>
<p>Appending the space of each vector in their names ("..._modelspace") helps fixing math bugs tremendously.</p>
<h2>How to create a normal map</h2><br />
Created by James O'Hare. Click to enlarge.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normalMapMiniTut.jpg"><img title="normalMapMiniTut" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/normalMapMiniTut-320x1024.jpg" alt="How to create a normal map" width="320" height="1024" /></a></p>
<h1>Exercises</h1></p>
<ul>
<li>Normalize the vectors in indexVBO_TBN before the addition and see what it does.</li>
<li>Visualize other vectors (for instance, EyeDirection_tangentspace) in color mode, and try to make sense of what you see</li><br />
</ul></p>
<h1>Tools &amp; Links</h1></p>
<ul>
<li><a href="http://www.crazybump.com/">Crazybump</a> , a great tool to make normal maps. Not free.</li>
<li><a href="http://developer.nvidia.com/nvidia-texture-tools-adobe-photoshop">Nvidia's photoshop plugin</a>. Free, but photoshop isn't...</li>
<li><a href="http://www.zarria.net/nrmphoto/nrmphoto.html">Make your own normal maps out of several photos</a></li>
<li><a href="http://www.katsbits.com/tutorials/textures/making-normal-maps-from-photographs.php">Make your own normal maps out of one photo</a></li>
<li>Some more info on <a href="http://www.katjaas.nl/transpose/transpose.html">matrix transpose</a></li><br />
</ul></p>
<h1>References</h1></p>
<ul>
<li><a href="http://www.terathon.com/code/tangent.html">Lengyel, Eric. &ldquo;Computing Tangent Space Basis Vectors for an Arbitrary Mesh&rdquo;. Terathon Software 3D Graphics Library, 2001.</a></li>
<li><a href="http://www.amazon.com/dp/1568814240">Real Time Rendering, third edition</a></li>
<li><a href="http://www.amazon.com/dp/1584504250">ShaderX4</a></li><br />
</ul></p>
<h2></h2></p>
