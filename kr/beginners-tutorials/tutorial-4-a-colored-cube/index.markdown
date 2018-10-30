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

하나의 육면체는 6개의 사각 면으로 되어 있습니다. OpenGL은 삼각형만 처리 할 수 있기 때문에, 우리는 12개의 삼각형을 그려야 합니다. 사각면 하나 당 2개의 삼각형이 필요합니다. 삼각형을 그릴 때와 같은 방법으로 Vertex들을 정의합니다.

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

 OpenGL 버퍼는 표준 함수들을(glGenBuffers, glBindBuffer, glBufferData, glVertexAttribPointer) 이용해서 생성되고, 연결되고(bound), 채워지고, 설정 됩니다. 잠시 Tutorial 2를 복습 겸 살펴보셔도 좋겠습니다. draw call(억지로 한글로 번역하면 이상해서 그냥 draw call 그대로 사용)도 같습니다. 그냥 그려져야 할 정확한 Vertex의 개수만 설정 해 주면 됩니다.:

``` cpp
// 삼각형 그리기
glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
```

이 코드에서 주목 할 몇 가지 :

* 지금은 우리 3D 모델이 고정되어 있습니다. 모델을 수정하려면 소스 코드를 고치고 다시 어플리케이션을 컴파일하고~~ 잘 되길 바래야 합니다.^^  Tutorial 7에서 동적인 모델을 로딩 하는 방법을 배우게 됩니다.

* 실제로는 각 Vertex가 적어도 3번 적혀 있습니다.("-1.0f,-1.0f,-1.0f"을 위 코드에서 한번 찾아보세요.). 이건 정말 심각한 메모리 낭비입니다.  Tutorial 9에서 어떻게 다룰 지 배우겠습니다. 

이제 흰 바탕에 육면체를 그리는데 필효한 것은 다 준비 되었습니다. 쉐이더를 써보세요! 쫄지말고 한번 시도해 보세요. ^^

# 색깔 추가하기 
색깔은 - 개념적으론! - 위치와 일치합니다. 그냥 데이터고, OpenGL 용어로는 "속성"이지요. 사실 우리는 이미 glEnableVertexAttribArray()와 glVertexAttribPointer()를 통해 사용해 봤습니다. 그러면 다른 속성을 추가해보죠. 예전과 비슷할 거에요. 

자. 색상을 선언해 볼께요. 정점 하나당 RGB 하나씩입니다. 저는 색깔들을 무작위 생성을 했어요. 그리 예쁘게 보이지는 않겠지만 말이에요. - 하지만 여러분은 더 괜찮게 만들 수 있을 거에요! 예를 들면 정점 위치를 기반으로 색을 만들거나.. 그러면요! 


``` cpp
// 정점당 색상 하나. 랜덤하게 생성되었습니다. 
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
버퍼는 Vertex 버퍼 만든 방식이랑 똑같이 만들어 주시면 됩니다 : 

``` cpp
GLuint colorbuffer;
glGenBuffers(1, &colorbuffer);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
```

물론. 구성도 똑같이요! :

``` cpp
// 2nd attribute buffer : colors
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glVertexAttribPointer(
    1,                                // 속성값, 1일 이유는 없지만. Shader와는 반드시 일치해야해요. 
    3,                                // 크기
    GL_FLOAT,                         // 타입
    GL_FALSE,                         // 정규화?
    0,                                // 간격
    (void*)0                          // 배열 버퍼 offset
);
```

자, 이제 Vertex Shader에서 추가 버퍼를 엑세스 할 수 있게 되었습니다. :


``` glsl
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;
```

{: .highlightglslvs }
하지만, 우린 Vertex Shader 안에서는 그리 멋진일은 하지 않을거에요. 진짜는 Fragment Shader에서부터죠!  

``` glsl
// 출력 데이터; 각 조각에 대해 보간됩니다. 
out vec3 fragmentColor;

void main(){

    [...]

    // 각 정점의 색깔만 입력해도, 나머지 색상은 자동으로 보간될거에요!
    fragmentColor = vertexColor;
}
```
{: .highlightglslvs }

Fragment Shader 안에서, fragmentColor을 다시 선언합시다! 

``` glsl
// 정점 셰이더 보간값 
in vec3 fragmentColor;
```
{: .highlightglslfs }

그리고 최종 출력 색상을 복사해봐요! : 

``` glsl
// Ouput data
out vec3 color;

void main(){
    // 출력 색상 = 정점 셰이더에서 지정된 색상, 주변에 있는 3개의 정점으로 보간됩니다. 
    color = fragmentColor;
}
```
{: .highlightglslfs }

그러면 우리는 여기까지 된거죠! :
![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/missing_z_buffer.png)

어유. 못생겼다. 무슨 일이 일어났는지 알아볼까요?  

여러분이 "멀리 있는" 삼각형을 그리고, "근처에 있는" 삼각형을 그리면 이렇게 나올거에요 : 
![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/FarNear.png)

오. 괜찮아 보이네요. 그럼 "멀리 있는" 삼각형을 나중에 그려볼까요?
![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/NearFar.png)

어. "가까이 있는"게 덮어 씌워지네요, 마치 뒤에 있는 것처럼 말이에요! 이게 우리의 정-사각형에 일어난 일이에요 : 일부 면들이 숨겨져야 하지만 - 그러니까. 뒤에 있는 친구들 말이에요. - 하지만 그리는 순서가 꼬여서 보이는거에요. (이걸 화가 알고리즘이라고 해요.) 어유. 어쩌죠? 그리는 순서를 다시 하나하나 배치해볼까요? 그럴 바엔 그냥 Z-Buffer에게 도움을 요청합시다!  

*Quick Note 1* : 문제가 없는 것처럼 보이시면, 카메라 위치를 (4,3,-3)으로 바꿔보세요. 

*Quick Note 2* : "색상은 위치랑 비슷하고, 속성도 마찬가지에요." 라면, 왜 우리는 out vec3 fragmentColor와 in vec3 fragmentColor를 색상에만 정의해주고, 위치에는 해주지 않을 걸까요? 왜냐하면 position이 조금 더 특별하기 때문인데. 그 '특별한 부분'은 유일하게 강제적인 부분이기도 해요. (gl_Position에 넣지 않으면 OpenGL은 도대체 어디서 그릴지 모르거든요!) 그래서 Vertex Shader안에서는, gl_Position은 "빌트-인" 변수입니다. 이미 박혀있는 변수라고요. 


# Z-Buffer

이 문제를 해결할 방법 바로 깊이를 (줄여서. "Z") 버퍼에 저장하고,  픽셀을 하나 그릴 때마다, 이걸 버퍼에 저장할 지 여부를 확인하는거에요. 

(역주 : OpenGL에선 fragment, 파편이라고 번역해요. DirectX는 Pixel이라고하고요. 파편이라고 하면 못 알아들을 것 같아 픽셀이라고 번역하고 있는데. 더 좋은 의견 가지고 계시나요?)

스스로 해볼 수는 있는데, 그냥 하드웨어에 맡기는 게 속 편해요: 

``` cpp
// Depth Test 활성화.
glEnable(GL_DEPTH_TEST);
// 테스트 받을 깊이 값이 저장되있는 깊이 값보다 작으면 통과. 
// Accept fragment if it closer to the camera than the former one
glDepthFunc(GL_LESS);
```
이제 버퍼를 매 프레임마다 초기화합시다, 컬러만 초기화 하지 말고요! : 

``` cpp
// Clear the screen
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

그러면 짜잔. 이제 모든 문제를 해결했네요! 축하드려요!

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/one_color_per_vertex.png)

# 연습 문제

* 큐브 '와!' 삼각형을 그려봐요, 물론. 다른 위치에서요. 두개의 MVP 행렬을 만들 필요가 있을거고요, 메인 루프에서 2번의 그리기가 필요하겠지만, 쉐이더는 딱 하나만 필요할 거에요. 

* 색상 값을 스스로 만들어 봅시다. 힌트를 주면 : 랜덤으로, 실행할 때마다 색깔이 바뀐다! 라던가. 정점의 위치를 따라가게 하던가; 아니면 두개를 섞어버려요! 그리고 다른 개쩌는 아이디어가 많을거에요! :) 아. C 스타일 코딩을 모르신다면, 여기 예제 코드가 있어요 :

``` cpp
static GLfloat g_color_buffer_data[12*3*3];
for (int v = 0; v < 12*3 ; v++){
    g_color_buffer_data[3*v+0] = 빨간색 여기 넣으세요!
    g_color_buffer_data[3*v+1] = 초록색 여기 넣으세요!
    g_color_buffer_data[3*v+2] = 파란색 여기 넣으세요!
}
```
* 위에 문제를 해결하셨으면, 이제 매 프레임마다 색깔들을 바꿔보세요! glBufferData를 매 프레임마다 호출하셔야 할거에요. 아. 그 전에 적절한 버퍼가 바인딩된 건지는 확인하시고요!  
