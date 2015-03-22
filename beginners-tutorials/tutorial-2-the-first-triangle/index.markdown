---
layout: page
status: publish
published: true
title: 'Tutorial 2 : The first triangle'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 14
wordpress_url: http://www.dreamyourgame.com/wordpress/?page_id=14
date: '2011-04-07 18:54:11 +0200'
date_gmt: '2011-04-07 18:54:11 +0200'
categories: [tuto]
order: 20
tags: []
---
<p><!-- Include required JS files --><br />
<script src="js/shCore.js"></script><!--     At least one brush, here we choose JS. You need to include a brush for every     language you want to highlight --><script src="css/shBrushCpp.js"></script></p>
<p>This will be another long tutorial.</p>
<p>OpenGL 3 makes it easy to write complicated stuff, but at the expense that drawing a simple triangle is actually quite difficult.</p>
<p>Don't forget to cut'n paste the code on a regular basis.</p>
<blockquote><p><span style="color: #ff0000;">If the program crashes at startup, you're probably running from the wrong directory. Read CAREFULLY the first tutorial on how to configure Visual Studio !</span></blockquote></p>
<h1>The VAO</h1><br />
I won't dig into details now, but you need to create a Vertex Array Object and set it as the current one :</p>
<pre class="brush: cpp">GLuint VertexArrayID;<br />
glGenVertexArrays(1, &amp;VertexArrayID);<br />
glBindVertexArray(VertexArrayID);</pre><br />
Do this once your window is created (= after the OpenGL Context creation) and before any other OpenGL call.</p>
<p>If you really want to know more about VAOs, there are a few other tutorials out there, but this is not very important.</p>
<h1>Screen Coordinates</h1><br />
A triangle is defined by three points. When talking about "points" in 3D graphics, we usually use the word "vertex" ( "vertices" on the plural ). A vertex has 3 coordinates : X, Y and Z. You can think about these three coordinates in the following way :</p>
<ul>
<li>X in on your right</li>
<li>Y is up</li>
<li>Z is towards your back (yes, behind, not in front of you)</li><br />
</ul><br />
But here is a better way to visualize this : use the Right Hand Rule</p>
<ul>
<li>X is your thumb</li>
<li>Y is your index</li>
<li>Z is your middle finger. If you put your thumb to the right and your index to the sky, it will point to your back, too.</li><br />
</ul><br />
Having the Z in this direction is weird, so why is it so ? Short answer : because 100 years of Right Hand Rule Math will give you lots of useful tools. The only downside is an unintuitive Z.</p>
<p>On a side note, notice that you can move your hand freely : your X, Y and Z will be moving, too. More on this later.</p>
<p>So we need three 3D points in order to make a triangle ; let's go :</p>
<pre class="brush: cpp">// An array of 3 vectors which represents 3 vertices<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
   -1.0f, -1.0f, 0.0f,<br />
   1.0f, -1.0f, 0.0f,<br />
   0.0f,&nbsp; 1.0f, 0.0f,<br />
};</pre><br />
The first vertex is (-1,-1,0). This means that <em>unless we transform it in some way</em>, it will be displayed at (-1,-1) on the screen. What does this mean ? The screen origin is in the middle, X is on the right, as usual, and Y is up. This is what it gives on a wide screen :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/screenCoordinates.png"><img class="alignnone size-medium wp-image-16" title="screenCoordinates" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/screenCoordinates-300x165.png" alt="" width="300" height="165" /></a></p>
<p>This is something you can't change, it's built in your graphics card. So (-1,-1) is the bottom left corner of your screen. (1,-1) is the bottom right, and (0,1) is the middle top. So this triangle should take most of the screen.</p>
<h1>Drawing our triangle</h1><br />
The next step is to give this triangle to OpenGL. We do this by creating a buffer:</p>
<pre class="brush: cpp">&nbsp;<br />
// This will identify our vertex buffer<br />
GLuint vertexbuffer;</p>
<p>// Generate 1 buffer, put the resulting identifier in vertexbuffer<br />
glGenBuffers(1, &amp;vertexbuffer);</p>
<p>// The following commands will talk about our 'vertexbuffer' buffer<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);</p>
<p>// Give our vertices to OpenGL.<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);</pre><br />
This needs to be done only once.</p>
<p>Now, in our main loop, where we used to draw "nothing", we can draw our magnificent triangle :</p>
<pre class="brush: cpp">// 1rst attribute buffer : vertices<br />
glEnableVertexAttribArray(0);<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);<br />
glVertexAttribPointer(<br />
   0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // attribute 0. No particular reason for 0, but must match the layout in the shader.<br />
   3,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // size<br />
   GL_FLOAT,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // type<br />
   GL_FALSE,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // normalized?<br />
   0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // stride<br />
   (void*)0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; // array buffer offset<br />
);</p>
<p>// Draw the triangle !<br />
glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle</p>
<p>glDisableVertexAttribArray(0);</pre><br />
If you're on lucky, you can see the result (<span style="color: #ff0000;">don't panic if you don't</span>) :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/triangle_no_shader1.png"><img class="alignnone size-medium wp-image-858" title="triangle_no_shader" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/triangle_no_shader1-300x232.png" alt="" width="300" height="232" /></a></p>
<p>&nbsp;</p>
<p>Now this is some boring white. Let's see how we can improve it by painting it in red. This is done by using something called shaders.</p>
<h1>Shaders</h1></p>
<h2>Shader Compilation</h2><br />
In the simplest possible configuration, you will need two shaders : one called Vertex Shader, which will be executed for each vertex, and one called Fragment Shader, which will be executed for each sample. And since we use 4x antialising, we have 4 samples in each pixel.</p>
<p>Shaders are programmed in a language called GLSL : GL Shader Language, which is part of OpenGL. Unlike C or Java, GLSL has to be compiled at run time, which means that each and every time you launch your application, all your shaders are recompiled.</p>
<p>The two shaders are usually in separate files. In this example, we have SimpleFragmentShader.fragmentshader and SimpleVertexShader.vertexshader . The extension is irrelevant, it could be .txt or .glsl .</p>
<p>So here's the code. It's not very important to fully understand it, since you often do this only once in a program, so comments should be enough. Since this function will be used by all other tutorials, it is placed in a separate file : common/loadShader.cpp . Notice that just as buffers, shaders are not directly accessible : we just have an ID. The actual implementation is hidden inside the driver.</p>
<pre class="brush: cpp">GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){</p>
<p>    // Create the shaders<br />
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);<br />
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);</p>
<p>    // Read the Vertex Shader code from the file<br />
    std::string VertexShaderCode;<br />
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);<br />
    if(VertexShaderStream.is_open())<br />
    {<br />
        std::string Line = "";<br />
        while(getline(VertexShaderStream, Line))<br />
            VertexShaderCode += "\n" + Line;<br />
        VertexShaderStream.close();<br />
    }</p>
<p>    // Read the Fragment Shader code from the file<br />
    std::string FragmentShaderCode;<br />
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);<br />
    if(FragmentShaderStream.is_open()){<br />
        std::string Line = "";<br />
        while(getline(FragmentShaderStream, Line))<br />
            FragmentShaderCode += "\n" + Line;<br />
        FragmentShaderStream.close();<br />
    }</p>
<p>    GLint Result = GL_FALSE;<br />
    int InfoLogLength;</p>
<p>    // Compile Vertex Shader<br />
    printf("Compiling shader : %s\n", vertex_file_path);<br />
    char const * VertexSourcePointer = VertexShaderCode.c_str();<br />
    glShaderSource(VertexShaderID, 1, &amp;VertexSourcePointer , NULL);<br />
    glCompileShader(VertexShaderID);</p>
<p>    // Check Vertex Shader<br />
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &amp;VertexShaderErrorMessage[0]);<br />
    fprintf(stdout, "%s\n", &amp;VertexShaderErrorMessage[0]);</p>
<p>    // Compile Fragment Shader<br />
    printf("Compiling shader : %s\n", fragment_file_path);<br />
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();<br />
    glShaderSource(FragmentShaderID, 1, &amp;FragmentSourcePointer , NULL);<br />
    glCompileShader(FragmentShaderID);</p>
<p>    // Check Fragment Shader<br />
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &amp;FragmentShaderErrorMessage[0]);<br />
    fprintf(stdout, "%s\n", &amp;FragmentShaderErrorMessage[0]);</p>
<p>    // Link the program<br />
    fprintf(stdout, "Linking program\n");<br />
    GLuint ProgramID = glCreateProgram();<br />
    glAttachShader(ProgramID, VertexShaderID);<br />
    glAttachShader(ProgramID, FragmentShaderID);<br />
    glLinkProgram(ProgramID);</p>
<p>    // Check the program<br />
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &amp;Result);<br />
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );<br />
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &amp;ProgramErrorMessage[0]);<br />
    fprintf(stdout, "%s\n", &amp;ProgramErrorMessage[0]);</p>
<p>    glDeleteShader(VertexShaderID);<br />
    glDeleteShader(FragmentShaderID);</p>
<p>    return ProgramID;<br />
}</pre></p>
<h2>Our Vertex Shader</h2><br />
Let's write our vertex shader first.<br />
The first line tells the compiler that we will use OpenGL 3's syntax.</p>
<pre class="brush: vs">#version 330 core</pre><br />
The second line declares the input data :</p>
<pre class="brush: vs">layout(location = 0) in vec3 vertexPosition_modelspace;</pre><br />
Let's explain this line in detail :</p>
<ul>
<li>"vec3" is a vector of 3 components in GLSL. It is similar (but different) to the glm::vec3 we used to declare our triangle. The important thing is that if we use 3 components in C++, we use 3 components in GLSL too.</li>
<li>"layout(location = 0)" refers to the buffer we use to feed the <em>vertexPosition_modelspace</em> attribute. Each vertex can have numerous attributes : A position, one or several colours, one or several texture coordinates, lots of other things. OpenGL doesn't know what a colour is : it just sees a vec3. So we have to tell him which buffer corresponds to which input. We do that by setting the layout to the same value as the first parameter to glVertexAttribPointer. The value "0" is not important, it could be 12 (but no more than&nbsp;glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &amp;v) ), the important thing is that it's the same number on both sides.</li>
<li>"vertexPosition_modelspace" could be anything else. It will contain the position of the vertex for each run of the vertex shader.</li>
<li>"in" means that this is some input data. Soon we'll see the "out" keyword.</li><br />
</ul><br />
&nbsp;</p>
<p>The function that is called for each vertex is called main, just as in C :</p>
<pre class="brush: vs">void main(){</pre><br />
Our main function will merely set the vertex' position to whatever was in the buffer. So if we gave (1,1), the triangle would have one of its vertices at the top right corner of the screen. We'll see in the next tutorial how to do some more interesting computations on the input position.</p>
<pre class="brush: vs">    gl_Position.xyz = vertexPosition_modelspace;<br />
    gl_Position.w = 1.0;<br />
&nbsp;}</pre><br />
gl_Position is one of the few built-in variables : you <em>have </em>to assign some value to it. Everything else is optional; we'll see what "everything else" means in Tutorial 4.</p>
<h2>Our Fragment Shader</h2><br />
For our first fragment shader, we will do something really simple : set the color of each fragment to red. (Remember, there are 4 fragment in a pixel because we use 4x AA)</p>
<pre class="brush: fs">#version 330 core<br />
out vec3 color;</p>
<p>void main(){<br />
    color = vec3(1,0,0);<br />
}</pre><br />
So yeah, vec3(1,0,0) means red. This is because on computer screens, colour is represented by a Red, Green, and Blue triplet, in this order. So (1,0,0) means Full Red, no green and no blue.</p>
<h1>Putting it all together</h1><br />
Before the main loop, call our LoadShaders function :</p>
<pre class="brush: cpp">// Create and compile our GLSL program from the shaders<br />
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );</pre><br />
Now inside the main loop, first clear the screen. This will change the background color to dark blue because of the glClearColor(0.0f, 0.0f, 0.4f, 0.0f) call above the main loop&nbsp;:</p>
<pre class="brush: cpp">glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);</pre><br />
and then tell OpenGL that you want to use your shader :</p>
<pre class="brush: cpp">// Use our shader<br />
glUseProgram(programID);</p>
<p>// Draw triangle...</pre><br />
... and presto, here's your red triangle !</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/red_triangle.png"><img class="alignnone size-medium wp-image-15" title="red_triangle" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/red_triangle-300x231.png" alt="" width="300" height="231" /></a></p>
<p>In the next tutorial we'll learn transformations : How to setup your camera, move your objects, etc.</p>
