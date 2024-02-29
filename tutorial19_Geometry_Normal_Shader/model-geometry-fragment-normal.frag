
// Fragment shader for simple coloured rendering of the normals

#version 330 core
//declaring the vec4 color variable

out vec4 FragColor;



void main()
{ 
    //assigning the fragment shader with the vec4 color.

    FragColor = vec4(1.0,1.0,0.5,1.0);
}