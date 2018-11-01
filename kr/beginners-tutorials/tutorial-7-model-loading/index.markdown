---
layout: tutorial
status: publish
published: true
title: 'Tutorial 7 : Model loading'
date: '2011-05-08 17:48:12 +0200'
date_gmt: '2011-05-08 17:48:12 +0200'
categories: [tuto]
order: 70
tags: []
language: kr
---

지금까지, 우리는 소스코드에 큐브를 하드코딩했어요. 그게 꽤 끔찍하고, 그리 괜찮은 일이 아니라는 것이라는 걸 여러분도 이해했으리라 믿어요. 
Until now, we hardcoded our cube directly in the source code. I'm sure you will agree that this was cumbersome and not very handy.

이번 튜토리얼에서는 파일에서 3D 메쉬를 불러오는 법을 배울거에요. 텍스처 로딩에서 했던 것처럼 : 아주 제한적이고, 아주 작은 로더를 만들 거고. 실제 라이브러리들은 우리보다 괜찮을 거라고 확신할게요. 그러니까 나중에는 그 라이브러리 쓰는 방법도 알려줄게요. 
In this tutorial we will learn how to load 3D meshes from files. We will do this just like we did for the textures : we will write a tiny, very limited loader, and I'll give you some pointers to actual libraries that can do this better that us.

이 튜토리얼을 가능한 한 심플하게 만들기 위해, 우리는 OBJ 파일 포맷을 사용할 거에요. 아주 간단하고 일반적인 포멧이죠. 그리고 마찬가지 이유로. 우리는 버텍스당 UV 좌표 하나, normal 좌표 하나만을 가지는 OBJ 파일만 불러올 거에요. (normal에 대해선 아직 알 필요가 없어요.) 
To keep this tutorial as simple as possible, we'll use the OBJ file format, which is both very simple and very common. And once again, to keep things simple, we will only deal with OBJ files with 1 UV coordinate and 1 normal per vertex (you don't have to know what a normal is right now).

# OBJ 로딩하기

우리 함수는, 코드는 common/objloader.cpp에. 정의는 common/objloader.hpp에 있을거에요 - 아래 시그네쳐에요. :
Our function, located in common/objloader.cpp and declared in common/objloader.hpp, will have the following signature :

``` cpp
bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
)
```

우리는 loadOBJ가 파일 "path(경로)" 를 읽기 원하고, 그 경로에서 out_vertices/out_uvs/out_normals등의 데이터를 쓰기를 원할거고. 뭐가 잘못되었으면 false 값을 돌려줬으면 좋겠어요. std::vector 는 C++에 있는, 언제든지 크기를 수정할수 있는 배열이고. 템플릿이라는 것을 통해 지금은 glm::vec3 자료형을 보관중이에요. : 아. 이거는 수학적인 벡터가 아니에요. 그냥 배열이라니까요? 진짜로요. 마지막으로 알아볼건 & 인데. 이거는 '참조'라고 std::vector를 수정할 수 있다는 말이에요. 

(역주 : JAVA등을 하던 사람은 이상하게 생각하겠지만, C++은 기본적으로 '모든' 변수를 '값'만 전달합니다. ) 

We want loadOBJ to read the file "path", write the data in out_vertices/out_uvs/out_normals, and return false if something went wrong. std::vector is the C++ way to declare an array of glm::vec3 which size can be modified at will: it has nothing to do with a mathematical vector. Just an array, really. And finally, the & means that function will be able to modify the std::vectors.

## 예제 OBJ 파일

OBJ 파일은 대체로 이것보다 길거나 - 더 짧아요. : 
An OBJ file looks more or less like this :

```
# Blender3D v249 OBJ File: untitled.blend
# www.blender3d.org
mtllib cube.mtl
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -1.000000
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 0.748573 0.750412
vt 0.749279 0.501284
vt 0.999110 0.501077
vt 0.999455 0.750380
vt 0.250471 0.500702
vt 0.249682 0.749677
vt 0.001085 0.750380
vt 0.001517 0.499994
vt 0.499422 0.500239
vt 0.500149 0.750166
vt 0.748355 0.998230
vt 0.500193 0.998728
vt 0.498993 0.250415
vt 0.748953 0.250920
vn 0.000000 0.000000 -1.000000
vn -1.000000 -0.000000 -0.000000
vn -0.000000 -0.000000 1.000000
vn -0.000001 0.000000 1.000000
vn 1.000000 -0.000000 0.000000
vn 1.000000 0.000000 0.000001
vn 0.000000 1.000000 -0.000000
vn -0.000000 -1.000000 0.000000
usemtl Material_ray.png
s off
f 5/1/1 1/2/1 4/3/1
f 5/1/1 4/3/1 8/4/1
f 3/5/2 7/6/2 8/7/2
f 3/5/2 8/7/2 4/8/2
f 2/9/3 6/10/3 3/5/3
f 6/10/4 7/6/4 3/5/4
f 1/2/5 5/1/5 2/9/5
f 5/1/6 6/10/6 2/9/6
f 5/1/7 8/11/7 6/10/7
f 8/11/7 7/12/7 6/10/7
f 1/2/8 2/9/8 3/13/8
f 1/2/8 3/13/8 4/14/8
```

그래서, 뭔 뜻일까요?: 
So :

* '#' 은 그냥 주석이에요. C++로 치면 '//' 같은거요.
* usemtl 과 mtllib는 모델이 어떻게 보여지는지 묘사하지만. 이번 튜토리얼에서는 안 쓸거에요. 
* v은 정점이고. 
* vt은 정점의 텍스쳐 좌표. 
* vn은 정점의 normal 좌표고요. 
* f는 면이에요. 

* `#` is a comment, just like // in C++
* usemtl and mtllib describe the look of the model. We won't use this in this tutorial.
* v is a vertex
* vt is the texture coordinate of one vertex
* vn is the normal of one vertex
* f is a face

v, vt 그리고 vn은 쉽게 이해할 수 있겠지만. f는 조금 더 까다로워요. 그러니까 예제를 들어봐요! 만약 f 8/11/7 7/12/7 6/10/7이 있다고 해봅시다. 
v, vt and vn are simple to understand. f is more tricky. So, for f 8/11/7 7/12/7 6/10/7 :

* 8/11/7은 삼각형의 첫 번째 정점을 표현한거에요. 
* 7/12/7은 삼각형의 두 번째 정점을 표현한거에요. 
* 6/10/7은 삼각형의 세 번째 정점을 표현한거에요. 
* 첫 번째 정점에서, 8은 사용할 정점의 위치에요. 그러니까 위에 나열된 정점들 중에서 8번째라는 말인데요. 8번째면 -1.000000 1.000000 -1.000000 이겠네요. (C++과 다르게 순서는 0이 아니라 1부터 시작해요.) 
* 11은 사용한 텍스쳐 좌표의 위치에요. 그러면 0.748355 0.998230가 되겠네요. 
* 7은 사용할 normal 좌표의 위치에요. 그러면 0.000000 1.000000 -0.000000이겠네요. 

* 8/11/7 describes the first vertex of the triangle
* 7/12/7 describes the second vertex of the triangle
* 6/10/7 describes the third vertex of the triangle (duh)
* For the first vertex, 8 says which vertex to use. So in this case, -1.000000 1.000000 -1.000000 (index start to 1, not to 0 like in C++)
* 11 says which texture coordinate to use. So in this case, 0.748355 0.998230
* 7 says which normal to use. So in this case, 0.000000 1.000000 -0.000000

이 숫자들은 'indices(인덱스들)' 라고 불려요. 이 방식은 꽤 똑똑한 방식인데 - 만약 같은 위치에 있는 정점을 공유하려면. 그냥 파일에서 v 하나를 척은 다음에 여러 번 돌려쓰면 되는 거죠. 메모리도 아끼고요. 

These numbers are called indices. It's handy because if several vertices share the same position, you just have to write one "v" in the file, and use it several times. This saves memory.

나쁜 소식은 텍스처에는 다른 인덱스를 쓰라하고, normal에는 다른 인덱스를 쓰라하고, position에는 다른 인덱스를 쓰라고 할 수 없다는거죠. 그래서 이 튜토리얼에서는 인덱스 안된 메쉬를 사용할게요. 인덱싱은 나중에 - 튜토리얼 9에서 해요. 그때는 어떻게 돌아가는 지 알려드릴게요. 

The bad news is that OpenGL can't be told to use one index for the position, another for the texture, and another for the normal. So the approach I took for this tutorial is to make a standard, non-indexed mesh, and deal with indexing later, in Tutorial 9, which will explain how to work around this.

## Blender에서 OBJ 파일 만들기


우리의 작은 로더는 심각하게 기능이 제한되어 있어서, Blender에서 파일을 뽑을때 정확한 옵션인지 특별히 주의를 기울이셔야 해요. 여기, 어떻게 Blender에서 뽑는지 보일거에요 :
Since our toy loader will be severely limited, we have to be extra careful to set the right options when exporting the file. Here's how it should look in Blender :

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/Blender.png)


## Reading the file

Ok, down with the actual code. We need some temporary variables in which we will store the contents of the .obj :

``` cpp
std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;
```

Since Tutorial 5 : A Textured Cube, you know how to open a file :

``` cpp
FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
}
```

Let's read this file until the end :

``` cpp
while( 1 ){

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

    // else : parse lineHeader
```

(notice that we assume that the first word of a line won't be longer than 128, which is a very silly assumption. But for a toy parser, it's all right)

Let's deal with the vertices first :

``` cpp
if ( strcmp( lineHeader, "v" ) == 0 ){
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    temp_vertices.push_back(vertex);
```

i.e : If the first word of the line is "v", then the rest has to be 3 floats, so create a glm::vec3 out of them, and add it to the vector.

``` cpp
}else if ( strcmp( lineHeader, "vt" ) == 0 ){
    glm::vec2 uv;
    fscanf(file, "%f %f\n", &uv.x, &uv.y );
    temp_uvs.push_back(uv);
```

i.e if it's not a "v" but a "vt", then the rest has to be 2 floats, so create a glm::vec2 and add it to the vector.

same thing for the normals :

``` cpp
}else if ( strcmp( lineHeader, "vn" ) == 0 ){
    glm::vec3 normal;
    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
    temp_normals.push_back(normal);
```

And now the "f", which is more difficult :

``` cpp
}else if ( strcmp( lineHeader, "f" ) == 0 ){
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9){
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
    }
    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices    .push_back(uvIndex[0]);
    uvIndices    .push_back(uvIndex[1]);
    uvIndices    .push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
```

This code is in fact very similar to the previous one, except that there is more data to read.

## Processing the data

So what we did there was simply to change the "shape" of the data. We had a string, we now have a set of std::vectors. But it's not enough, we have to put this into a form that OpenGL likes. Namely, removing the indexes and have plain glm::vec3 instead. This operation is called indexing.

We go through each vertex ( each v/vt/vn ) of each triangle ( each line with a "f" ) :

``` cpp
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
```

the index to the vertex position is vertexIndices[i] :

``` cpp
unsigned int vertexIndex = vertexIndices[i];
```

so the position is temp_vertices[ vertexIndex-1 ] (there is a -1 because C++ indexing starts at 0 and OBJ indexing starts at 1, remember ?) :

``` cpp
glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
```

And this makes the position of our new vertex

``` cpp
out_vertices.push_back(vertex);
```

The same is applied for UVs and normals, and we're done !

# Using the loaded data

Once we've got this, almost nothing changes. Instead of declaring our usual static const GLfloat g_vertex_buffer_data[] = {...}, you declare a std::vector vertices instead (same thing for UVS and normals). You call loadOBJ with the right parameters :

``` cpp
// Read our .obj file
std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
bool res = loadOBJ("cube.obj", vertices, uvs, normals);
```

and give your vectors to OpenGL instead of your arrays :

``` cpp
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
```

And that's it !

# Results

Sorry for the lame texture, I'm NOT a good artist :( Any contribution welcome !

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/ModelLoading.png)


# Other formats/loaders

This tiny loader should give you enough to get started, but won't want to use this in real life. Have a look at our [Useful Links & Tools](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) page for some tools you can use. Note, however, that you'd better wait for tutorial 9 before *actually *trying to use them.
