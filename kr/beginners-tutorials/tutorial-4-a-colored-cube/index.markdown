---
layout: tutorial
status: publish
published: true
title: 'Tutorial 4 :  색깔이 입혀진 육면체'
date: '2011-04-26 07:55:37 +0200'
date_gmt: '2011-04-26 07:55:37 +0200'
categories: [tuto]
order: 40
tags: []
language: kr
---

네번째 튜토리얼에 오신 것을 환영합니다! 이번에는 다음 내용들을 배워보겠습니다. :

* 단순한 삼각형 대신 육면체를 그리기
* 좀 멋진 색깔 입히기
* Z-Buffer가 무엇인지 배우기


# 육면체 그리기

하나의 육면체는 6개의 사각형으로 되어 있습니다. OpenGL은 삼각형만 처리할 수 있기 때문에, 우리는 12개의 삼각형을 그려야 합니다. 사각면 하나 당 2개의 삼각형이 필요합니다. 삼각형을 그릴 때와 같은 방법으로 Vertex들을 정의합니다.

``` cpp
// 우리 Vertex들입니다. 3개의 연속 된 float 숫자가 하나의 3차원 Vertex입니다.
// 3개의 연속 된 Vertex들이 하나의 삼각형을 정의합니다.
// 하나의 육면체는 2개의 삼각형으로 이루어진 면 6개를 가지고 있고,
// 그래서 총 6*2=12개의 삼각형, 12*3 개의 Vertex를 가지고 있습니다.
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
```

 OpenGL 버퍼는 표준 함수들을(glGenBuffers, glBindBuffer, glBufferData, glVertexAttribPointer) 이용해서 생성되고, 연결되고(bound), 채워지고, 설정됩니다. 잠시 Tutorial 2를 복습 겸 살펴보셔도 좋습니다. draw call도 같습니다. 그냥 그려져야 할 정확한 Vertex의 개수만 설정 해 주면 됩니다.:

``` cpp
// 삼각형 그리기
glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
```

이 코드에서 주목 할 몇 가지 :

* 지금은 우리 3D 모델이 고정되어 있습니다. 모델을 수정하려면 소스 코드를 고치고 다시 어플리케이션을 컴파일한 뒤 잘 되길 바래야 합니다. Tutorial 7에서 동적인 모델을 로딩하는 방법을 배우게 됩니다.
* 실제로는 각 Vertex가 적어도 3번 적혀 있습니다.("-1.0f,-1.0f,-1.0f"을 위 코드에서 한번 찾아보세요.). 이건 정말 심각한 메모리 낭비입니다. Tutorial 9에서 어떻게 다룰 지 배우겠습니다. 

이제 흰 바탕에 육면체를 그리는데 필요한 것은 다 준비 되었습니다. 셰이더를 써보세요! 겁먹지 말고 한번 시도해 보세요.

# 색 추가하기

색은 개념적으로 위치와 완전히 같은 데이터일 뿐입니다. OpenGL에서는 이들을 "Attribute"라 부릅니다. 사실 우리는 이미 glEnableVertexAttribArray()와 glVertexAttribPointer() 에서 그것을 사용했습니다. 코드도 아주 비슷한 형태가 될 것입니다.

가장 먼저 원하는 색상을 선언하세요. vertex 하나 당 RGB를 나타내는  세 숫자가 필요합니다. 여기에선 색을 무작위로 생성해서 보기 나쁘지만, vertex의 위치를 자신의 색상으로 설정하는 등의 다른 방법을 사용하면 더 좋게 만들 수 있습니다.

``` cpp
// vertex당 색상 하나 씩. 색상은 무작위로 생성되었음
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
```

이전과 완전히 같은 방식으로 버퍼가 생성되고, 연결된 뒤 채워집니다.

``` cpp
GLuint colorbuffer;
glGenBuffers(1, &colorbuffer);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
```

설정도 동일합니다,

``` cpp
// 두번째 attribute 버퍼 : 색상들
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glVertexAttribPointer(
    1,                                // attribute. 1인 특별한 이유는 없지만, 셰이더의 레이아웃과 같아야 합니다 
    3,                                // 크기
    GL_FLOAT,                         // 타입
    GL_FALSE,                         // 정규화 여부
    0,                                // 건너뛰기(stride)
    (void*)0                          // 배열 버퍼 여백(offset)
);
```

이제 정점(vertex) 셰이더에서 이 새로운 버퍼에 접근할 수 있습니다.

``` glsl
// 여기의 "1"이 glVertexAttribPointer의 "1"과 같습니다
layout(location = 1) in vec3 vertexColor;
```

{: .highlightglslvs }

이 예제에서는 정점 셰이더로 멋진 일들은 안 할 겁니다. 바로 프래그먼트 셰이더로 전달해 주세요.

``` glsl
// 출력 데이터. 각 fragment마다 보간(interpolate)될 예정입니다
out vec3 fragmentColor;

void main(){

    [...]

    // 보간될 vertex의 색상
    // 각 fragment의 색상을 만든다
    fragmentColor = vertexColor;
}
```
{: .highlightglslvs }

프래그먼드 셰이더에서 fragmentColor을 다시 선언합니다.

``` glsl
// 정점 셰이더에서 가져온 보간된 값
in vec3 fragmentColor;
```
{: .highlightglslfs }

... 그리고 그 값을 최종 출력 색상으로 복사합니다.

``` glsl
// 출력 데이터
out vec3 color;

void main(){
    // Output color = color 정점 셰이더에 명시되어 있습니다 specified in the vertex shader,
    // 주변 3개의 vertex 로 보간됩니다
    color = fragmentColor;
}
```
{: .highlightglslfs }

그 결과는 이렇습니다.

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/missing_z_buffer.png)


못생겼죠. 무슨 일이 일어났는지 이해하기 위해, "먼"삼각형과 "가까운"삼각형을 그릴 때 어떻게 되는지 살펴봅시다. 

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/FarNear.png)


지금은 괜찮아 보이죠. 이번엔 "먼"삼각형을 먼저 그립시다.

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/NearFar.png)


"가까운"삼각형을 덮어 버립니다! 원래는 그 뒤에 있어야 하는데 말이죠. 우리의 육면체에도 같은 일이 생깁니다. 어떤 면들은 숨겨져야 하는데, 나중에 그리면 보이게 되는 거죠. Z-Buffer의 도움이 필요합니다!

*참고 1* : 문제가 보이지 않는다면 카메라 위치를 (4,3,-3)으로 바꿔 보세요.

*참고 2* : 색상도 위치도 attribute라면, 왜 색상을 위해서만 out vec3 fragmentColor; 과 in vec3 fragmentColor; 을 선언할까요? 사실 위치는 조금 특별하기 때문입니다. 위치는 유일하게 강제적인 attribute (이게 없으면 OpenGL은 삼각형을 어디에 그려야 할 지 모릅니다!). 따라서 gl_Position은 정점 셰이더에 "내장된"(Built-in) 변수입니다.

# Z-Buffer

이 문제의 해결 방법은 각 fragment의 깊이(Z) 컴포넌트를 버퍼에 저장하고, fragment에 쓸 때마다 그 값을 (새 fragment가 이전에 그려진 것보다 가까이 있는지)확인하는 것입니다. 

직접 할 수도 있지만, 하드웨어에게 부탁하는 편이 훨씬 간단하죠.

``` cpp
// 깊이 검사(depth test)를 활성화
glEnable(GL_DEPTH_TEST);
// 먼저 그려진 것보다 fragment가 가까이 있을 때 그린다
glDepthFunc(GL_LESS);
```

그리고 깊이 버퍼를 매 프레임마다 비워야 합니다.

``` cpp
// 화면을 비운다
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

이렇게 문제를 모두 해결할 수 있습니다.

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/one_color_per_vertex.png)

# 연습

* 육면체와 삼각형을 서로 다른 위치에 한번에 그리세요. 메인 루프 안에서 draw call 2번을 수행하기 위해 MVP 매트리스 2개가 필요하지만, 셰이더는 하나만 있으면 됩니다.


* 색상을 직접 설정해 보세요. 예를 들어, 무작위로 실행할 때마다 바뀌게 하거나, vertex의 위치에 따라 색상이 정해지도록 해 보세요. 둘을 섞어 보기도 하고요. 다른 창의적인 아이디어도 시험해 보세요 :)  C언어를 잘 모르신다면, 이 코드를 참고하세요.

``` cpp
static GLfloat g_color_buffer_data[12*3*3];
for (int v = 0; v < 12*3 ; v++){
    g_color_buffer_data[3*v+0] = your red color here;
    g_color_buffer_data[3*v+1] = your green color here;
    g_color_buffer_data[3*v+2] = your blue color here;
}
```

* 해 보셨다면, 매 프레임 색이 바뀌도록 만들어 보세요. 매 프레임 glBufferData를 호출해야 합니다. 알맞은 버퍼가 연결(glBindBuffer)되어 있는지 꼭 확인하세요!
