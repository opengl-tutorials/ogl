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

지금까지, 우리는 소스코드에 큐브를 하드코딩했어요. 그게 꽤 끔찍하고, 그리 괜찮은 일이 아니라는 것이라는 걸 여러분도 느꼈다고 믿고 있어요. 

이번 튜토리얼에서는 파일에서 3D 메쉬를 불러오는 법을 배울거에요. 텍스처 로딩에서 했던 것처럼 : 아주 제한적이고, 아주 작은 로더를 만들 거고- 그래서 실제 라이브러리들은 우리보다 괜찮을 거라고 확신해요. 그러니까 나중에는 라이브러리들 소개도 시켜드릴게요. 

이 튜토리얼을 가능한 한 심플하게 만들기 위해, 우리는 OBJ 파일 포맷을 사용할 거에요. 아주 간단하고 일반적인 포멧이죠. 그리고 마찬가지 이유로. 우리는 버텍스당 UV 좌표 하나, normal 좌표 하나만을 가지는 OBJ 파일만 불러올 거에요. (normal에 대해선 아직 알 필요가 없어요.) 

# OBJ 로딩하기

우리 함수는, 코드는 common/objloader.cpp에. 정의는 common/objloader.hpp에 있을거에요 - 아래 시그네쳐에요. :

``` cpp
bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
)
```

우리는 loadOBJ가 파일 "path(경로)" 를 읽기 원하고, 그 경로에서 out_vertices/out_uvs/out_normals등의 데이터를 쓰기를 원할거고. 뭐가 잘못되었으면 false 값을 돌려줬으면 좋겠어요. std::vector 는 C++에 있는 언제든지 크기를 수정할수 있는 배열이고. 템플릿이라는 것을 통해 지금은 glm::vec3 자료형을 보관중이에요. (아. 이거는 수학적인 벡터가 아니에요. 그냥 배열이라니까요? 진짜로요.) 마지막으로 알아볼건 & 인데. 이거는 '참조'라고 std::vector를 수정할 수 있다는 뜻이에요.

(역주 : JAVA등을 하던 사람은 이상하게 생각하겠지만, C++은 기본적으로 *모든* 변수를 **값**만 전달합니다. 참조형만이 순수한 call-by-reference입니다. 다만 참조형은 compile 시점에 결정되기에, 가리키는 대상을 바꿀 수 없음을 유의하세요. 바꾸고 싶으시다면, 포인터를 사용하세요.) 

## 예제 OBJ 파일

OBJ 파일은 대체로 이것보다 길거나 - 더 짧아요. : 

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

* `#` 은 그냥 주석이에요. C++로 치면 '//' 같은거요.
* usemtl 과 mtllib는 모델이 어떻게 보여지는지 묘사하지만. 이번 튜토리얼에서는 안 쓸거에요. 
* v은 정점이고. 
* vt은 정점의 텍스쳐 좌표. 
* vn은 정점의 normal 좌표고요. 
* f는 면이에요. 

v, vt 그리고 vn은 쉽게 이해할 수 있겠지만. f는 조금 더 까다로워요. 그러니까 예제를 들어봐요! 만약 f 8/11/7 7/12/7 6/10/7이 있다고 해봅시다. 

* 8/11/7은 삼각형의 첫 번째 정점을 표현한거에요. 
* 7/12/7은 삼각형의 두 번째 정점을 표현한거에요. 
* 6/10/7은 삼각형의 세 번째 정점을 표현한거에요. 
* 첫 번째 정점에서, 8은 사용할 정점의 위치에요. 그러니까 위에 나열된 정점들 중에서 8번째라는 말인데요. 8번째면 -1.000000 1.000000 -1.000000 이겠네요. (C++과 다르게 순서는 0이 아니라 1부터 시작해요.) 
* 11은 사용한 텍스쳐 좌표의 위치에요. 그러면 0.748355 0.998230가 되겠네요. 
* 7은 사용할 normal 좌표의 위치에요. 그러면 0.000000 1.000000 -0.000000이겠네요. 

이 숫자들은 'indices(인덱스들)' 라고 불려요. 이 방식은 꽤 똑똑한 방식인데 - 만약 같은 위치에 있는 정점을 공유하려면. 그냥 파일에서 v 하나를 척은 다음에 여러 번 돌려쓰면 되는 거죠. 메모리도 아끼고요. 


나쁜 소식은 텍스처에는 다른 인덱스를 쓰라하고, normal에는 다른 인덱스를 쓰라하고, position에는 다른 인덱스를 쓰라고 할 수 없다는거죠. 그래서 이 튜토리얼에서는 인덱스 안된 메쉬를 사용할게요. 인덱싱은 나중에 - 튜토리얼 9에서 해요. 그때는 어떻게 돌아가는 지 알려드릴게요. 

## Blender에서 OBJ 파일 만들기

우리의 작은 로더는 심각하게 기능이 제한되어 있어서, Blender에서 파일을 뽑을때 정확한 옵션인지 특별히 주의를 기울이셔야 해요. 여기, 어떻게 Blender에서 뽑는지 보일거에요 :

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/Blender.png)

## 파일 읽기

좋아요, 진짜 코드로 돌아가봅시다. .obj파일의 내용물을 저장하려면 임시 변수 몇몇개가 필요할 거에요 : 

``` cpp
std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;
```

튜토리얼 5 : A Textured Cube에서 어떻게 파일을 여는지 배우셨죠? :


``` cpp
FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
}
```

파일의 끝까지 읽어봐요. : 

``` cpp
while( 1 ){

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

    // else : parse lineHeader
```

(지금 우리는 첫 줄을 128바이트보다 더 못 읽는다는 걸 명심하세요. 썩 좋지 않은 조건이지만. 어차피 실제로는 쓰지 않을거니, 괜찮아요.)

그러면 정점들을 먼저 읽어볼까요? : 

``` cpp
if ( strcmp( lineHeader, "v" ) == 0 ){
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    temp_vertices.push_back(vertex);
```

즉, 만약 첫 단어가 "v" 라면, 3개의 float들이 뒤에 있을거에요. 그러니 glm::vec3를 하나 만들고, vector에 추가해줍시다. 

``` cpp
}else if ( strcmp( lineHeader, "vt" ) == 0 ){
    glm::vec2 uv;
    fscanf(file, "%f %f\n", &uv.x, &uv.y );
    temp_uvs.push_back(uv);
```

즉, 만약 "v" 가 아니라 "vt"라면, 2개의 float들이 뒤에 있을거에요. 그러니 glm::vec2를 하나 만들고, vector에 추가해줍시다. 

normals도 똑같이 해주세요 : 

``` cpp
}else if ( strcmp( lineHeader, "vn" ) == 0 ){
    glm::vec3 normal;
    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
    temp_normals.push_back(normal);
```

마지막은 "f"인데. 이건 꽤 어려워요: 

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

이 코드는 읽을 데이터가 꽤 많다는 건 빼곤, 예전에 파일을 읽는 코드들과 꽤 비슷하죠? 

## 데이터 처리하기 

자. 이제 우리는 간단하게나마 데이터의 "모양"을 바꿨어요. 아까까지는 문자열이었지만, 지금은 std::vector들에 있죠. 하지만 이걸로는 충분하지 않아요. 우리는 이걸 OpenGL이 좋아할 만한 형태로 바꿔야해요. 그러니까 indexes들을 날리고, glm::vec3를 대신 넣어야하죠. 이 작업을 indexing(인덱싱)이라고 해요. 

각 삼각형의 정점(v/vt/vn 같은 것들이요.) 들을 한번씩 돌아볼거에요. 루프를 통해서 말이죠. ( 각 라인의 "f" 마다. ) :

``` cpp
    // For each vertex of each triangle  (각 삼각형의 각 꼭지점을 순회합니다. ) 
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
```

정점 좌표의 index는 vertexIndices[i]에 있었죠. : 

``` cpp
unsigned int vertexIndex = vertexIndices[i];
```

그래서 좌표를 tmpe_vertices[vertexIndex - 1]에 담을거에요. ( -1을 빼는 이유는 C++은 index가 0부터 시작하지만, OBJ는 1부터 시작하기 때문이에요. 기억나요?)

``` cpp
glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
```

이걸로 우리의 새로운 정점에게 좌표값을 줄 수 있죠. 

``` cpp
out_vertices.push_back(vertex);
```

그리고 이 일을 UV 좌표들과, normal 좌표들에게도 적용하면 끝이에요!

# 읽어온 데이터 활용하기 

여기까지 해냈는데, 아직 바뀐 건 하나도 없어요. 이제 바꿔봐요. static const GLfloat g_vertex_buffer_data[] = {...} 를 선언하는 대신에 std::vector 정점들(텍스쳐 좌표와, normal 좌표도 똑같이요.)을 선언합시다. 그리고 loadOBJ 함수를 정확한 파라미터로 호출해봐요.  : 

``` cpp
// 우리의 .obj 파일을 읽습니다. 
std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // 지금은 안쓸거에요. 
bool res = loadOBJ("cube.obj", vertices, uvs, normals);
```

그리고 OpenGL에게 배열 대신에 vector들을 줘보세요. :

``` cpp
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
```

진짜 끝! 

# 결과

구린 텍스쳐에 미리 사과 드릴게요. 저는 **절대** 좋은 그림쟁이는 아니에요 :(  그러니까 기여는 환영할게요! 

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/ModelLoading.png)


# 다른 포맷들 / 로더들

우리가 만든 작은 로더는 초심자인 우리에게는 적합하지만, 실무에서 쓰기에는 전혀 아니죠. 한번 [유용한 링크 & 도구들](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) 페이지를 살펴보면서 사용할 만한 도구가 있는지 확인해보세요. 아. 그렇지만 *진짜로* 쓰기 전에. 튜토리얼 9까지는 참아주세요. 

