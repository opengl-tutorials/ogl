//geometry shader used for debugging the general position of the normals of the texture wrapping.
//Used to decide whether the normals have been loaded properly.

#version 330 core
//vertex attributes position and normals

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


//interface block to be passed to the geometry shader 
//passing only the normal attribute to the geometry shader

out VS_OUT{

 vec3 normal;
}vs_out;

//MVP matrix loading

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{   //generate normal matrix to convert to NDC (Normalized Device Coordinates)
     mat3 normalMatrix= mat3(transpose(inverse(view*model)));
     //normalizing the normals of the vertices 
     vs_out.normal=normalize(vec3(projection * vec4(normalMatrix * aNormal,0.0)));  
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
