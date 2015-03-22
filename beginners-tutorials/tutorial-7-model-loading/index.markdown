---
layout: page
status: publish
published: true
title: 'Tutorial 7 : Model loading'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 185
wordpress_url: http://www.opengl-tutorial.org/?page_id=185
date: '2011-05-08 17:48:12 +0200'
date_gmt: '2011-05-08 17:48:12 +0200'
categories: [tuto]
tags: []
---
<p>Until now, we hardcoded our cube directly in the source code. I'm sure you will agree that this was cumbersome and not very handy.</p>
<p>In this tutorial we will learn how to load 3D meshes from files. We will do this just like we did for the textures : we will write a tiny, very limited loader, and I'll give you some pointers to actual libraries that can do this better that us.</p>
<p>To keep this tutorial as simple as possible, we'll use the OBJ file format, which is both very simple and very common. And once again, to keep things simple, we will only deal with OBJ files with 1 UV coordinate and 1 normal per vertex (you don't have to know what a normal is right now).</p>
<h1>Loading the OBJ</h1><br />
Our function, located in common/objloader.cpp and declared in common/objloader.hpp, will have the following signature :</p>
<pre class="brush: cpp">bool loadOBJ(<br />
    const char * path,<br />
    std::vector < glm::vec3 > &amp; out_vertices,<br />
    std::vector < glm::vec2 > &amp; out_uvs,<br />
    std::vector < glm::vec3 > &amp; out_normals<br />
)</pre><br />
We want loadOBJ to read the file "path", write the data in out_vertices/out_uvs/out_normals, and return false if something went wrong. std::vector is the C++ way to declare an array of glm::vec3 which size can be modified at will: it has nothing to do with a mathematical vector. Just an array, really. And finally, the &amp; means that function will be able to modify the std::vectors.</p>
<h2>Example OBJ file</h2><br />
An OBJ file looks more or less like this :</p>
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
f 5/1/1 1/2/1 4/3/1<br />
f 5/1/1 4/3/1 8/4/1<br />
f 3/5/2 7/6/2 8/7/2<br />
f 3/5/2 8/7/2 4/8/2<br />
f 2/9/3 6/10/3 3/5/3<br />
f 6/10/4 7/6/4 3/5/4<br />
f 1/2/5 5/1/5 2/9/5<br />
f 5/1/6 6/10/6 2/9/6<br />
f 5/1/7 8/11/7 6/10/7<br />
f 8/11/7 7/12/7 6/10/7<br />
f 1/2/8 2/9/8 3/13/8<br />
f 1/2/8 3/13/8 4/14/8</pre><br />
So :</p>
<ul>
<li># is a comment, just like // in C++</li>
<li>usemtl and mtllib describe the look of the model. We won't use this in this tutorial.</li>
<li>v is a vertex</li>
<li>vt is the texture coordinate of one vertex</li>
<li>vn is the normal of one vertex</li>
<li>f is a face</li><br />
</ul><br />
v, vt and vn are simple to understand. f is more tricky. So, for f 8/11/7 7/12/7 6/10/7 :</p>
<ul>
<li>8/11/7 describes the first vertex of the triangle</li>
<li>7/12/7 describes the second vertex of the triangle</li>
<li>6/10/7 describes the third vertex of the triangle (duh)</li>
<li>For the first vertex, 8 says which vertex to use. So in this case, -1.000000 1.000000 -1.000000 (index start to 1, not to 0 like in C++)</li>
<li>11 says which texture coordinate to use. So in this case, 0.748355 0.998230</li>
<li>7 says which normal to use. So in this case, 0.000000 1.000000 -0.000000</li><br />
</ul><br />
These numbers are called indices. It's handy because if several vertices share the same position, you just have to write one "v" in the file, and use it several times. This saves memory.</p>
<p>The bad news is that OpenGL can't be told to use one index for the position, another for the texture, and another for the normal. So the approach I took for this tutorial is to make a standard, non-indexed mesh, and deal with indexing later, in Tutorial 9, which will explain how to work around this.</p>
<h2>Creating an OBJ file in Blender</h2><br />
Since our toy loader will severely limited, we have to be extra careful to set the right options when exporting the file. Here's how it should look in Blender :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/Blender.png"><img class="alignnone size-full wp-image-697" title="Blender" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/Blender.png" alt="" width="321" height="529" /></a></p>
<h2>Reading the file</h2><br />
Ok, down with the actual code. We need some temporary variables in which we will store the contents of the .obj :</p>
<pre class="brush: cpp">std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;<br />
std::vector< glm::vec3 > temp_vertices;<br />
std::vector< glm::vec2 > temp_uvs;<br />
std::vector< glm::vec3 > temp_normals;</pre><br />
Since Tutorial 5 : A Textured Cube, you know how to open a file :</p>
<pre class="brush: cpp">FILE * file = fopen(path, "r");<br />
if( file == NULL ){<br />
    printf("Impossible to open the file !\n");<br />
    return false;<br />
}</pre><br />
Let's read this file until the end :</p>
<pre class="brush: cpp">while( 1 ){</p>
<p>    char lineHeader[128];<br />
    // read the first word of the line<br />
    int res = fscanf(file, "%s", lineHeader);<br />
    if (res == EOF)<br />
        break; // EOF = End Of File. Quit the loop.</p>
<p>    // else : parse lineHeader</pre><br />
(notice that we assume that the first word of a line won't be longer than 128, which is a very silly assumption. But for a toy parser, it's all right)</p>
<p>Let's deal with the vertices first :</p>
<pre class="brush: cpp">if ( strcmp( lineHeader, "v" ) == 0 ){<br />
    glm::vec3 vertex;<br />
    fscanf(file, "%f %f %f\n", &amp;vertex.x, &amp;vertex.y, &amp;vertex.z );<br />
    temp_vertices.push_back(vertex);</pre><br />
i.e : If the first word of the line is "v", then the rest has to be 3 floats, so create a glm::vec3 out of them, and add it to the vector.</p>
<pre class="brush: cpp">}else if ( strcmp( lineHeader, "vt" ) == 0 ){<br />
    glm::vec2 uv;<br />
    fscanf(file, "%f %f\n", &amp;uv.x, &amp;uv.y );<br />
    temp_uvs.push_back(uv);</pre><br />
i.e if it's not a "v" but a "vt", then the rest has to be 2 floats, so create a glm::vec2 and add it to the vector.</p>
<p>same thing for the normals :</p>
<pre class="brush: cpp">}else if ( strcmp( lineHeader, "vn" ) == 0 ){<br />
    glm::vec3 normal;<br />
    fscanf(file, "%f %f %f\n", &amp;normal.x, &amp;normal.y, &amp;normal.z );<br />
    temp_normals.push_back(normal);</pre><br />
And now the "f", which is more difficult :</p>
<pre class="brush: cpp">}else if ( strcmp( lineHeader, "f" ) == 0 ){<br />
    std::string vertex1, vertex2, vertex3;<br />
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];<br />
    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &amp;vertexIndex[0], &amp;uvIndex[0], &amp;normalIndex[0], &amp;vertexIndex[1], &amp;uvIndex[1], &amp;normalIndex[1], &amp;vertexIndex[2], &amp;uvIndex[2], &amp;normalIndex[2] );<br />
    if (matches != 9){<br />
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");<br />
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
    normalIndices.push_back(normalIndex[2]);</pre><br />
This code is in fact very similar to the previous one, except that there is more data to read.</p>
<h2>Processing the data</h2><br />
So what we did there was simply to change the "shape" of the data. We had a string, we now have a set of std::vectors. But it's not enough, we have to put this into a form that OpenGL likes. Namely, removing the indexes and have plain glm::vec3 instead. This operation is called indexing.</p>
<p>We go through each vertex ( each v/vt/vn ) of each triangle ( each line with a "f" ) :</p>
<pre class="brush: cpp">    // For each vertex of each triangle<br />
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){<br />
</pre><br />
the index to the vertex' position is vertexIndices[i] :</p>
<pre class="brush: cpp">unsigned int vertexIndex = vertexIndices[i];</pre><br />
so the position is temp_vertices[ vertexIndex-1 ] (there is a -1 because C++ indexing starts at 0 and OBJ indexing starts at 1, remember ?) :</p>
<pre class="brush: cpp">glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];</pre><br />
And this makes the position of our new vertex</p>
<pre class="brush: cpp">out_vertices.push_back(vertex);</pre><br />
The same is applied for UVs and normals, and we're done !</p>
<h1>Using the loaded data</h1><br />
Once we've got this, almost nothing changes. Instead of declaring our usual static const GLfloat g_vertex_buffer_data[] = {...}, you declare a std::vector vertices instead (same thing for UVS and normals). You call loadOBJ with the right parameters :</p>
<pre class="brush: cpp">// Read our .obj file<br />
std::vector< glm::vec3 > vertices;<br />
std::vector< glm::vec2 > uvs;<br />
std::vector< glm::vec3 > normals; // Won't be used at the moment.<br />
bool res = loadOBJ("cube.obj", vertices, uvs, normals);</pre><br />
and give your vectors to OpenGL instead of your arrays :</p>
<pre class="brush: cpp">glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &amp;vertices[0], GL_STATIC_DRAW);</pre><br />
And that's it !</p>
<h1>Results</h1><br />
Sorry for the lame texture, I'm NOT a good artist :( Any contribution welcome !</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/ModelLoading.png"><img class="alignnone size-medium wp-image-670" title="ModelLoading" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/ModelLoading-300x232.png" alt="" width="300" height="232" /></a></p>
<h1>Other formats/loaders</h1><br />
This tiny loader should give you enough to get started, but won't want to use this in real life. Have a look at our <a title="Useful Tools &amp; Links" href="http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/">Useful Links &amp; Tools</a> page for some tools you can use. Note, however, that you'd better wait for tutorial 9 before <em>actually </em>trying to use them.</p>
