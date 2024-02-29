//geometry shader to draw the normals

#version 330 core

//Since the normals are to be drawn at the 3 vertices of the raster triangle,the vertices have an upper bound of 3
//line_strip specifies the normals to be drawn adjacent to each other on each of the 3 vertices of a triangle


layout(triangles) in;
layout(line_strip,max_vertices=3) out;

//interface block inherited from the vertex shader

in VS_OUT{

vec3 normal;

}gs_in[];

//magnitude of the length of the normals
float magnitude=0.4;

//generator function which will assign the normals based on the 3 indices (0,1,2) of each triangle
void generateLine(int index)
{
//gets the position and draws the normal from the vertices 
   gl_Position=gl_in[index].gl_Position;


   EmitVertex();
   gl_Position=gl_in[index].gl_Position + vec4(gs_in[index].normal,0.0)*magnitude;
   EmitVertex();
   EndPrimitive(); 

}

void main()
{
//line is generated from the vertices
  generateLine(0);
  generateLine(1);
  generateLine(2);
}
