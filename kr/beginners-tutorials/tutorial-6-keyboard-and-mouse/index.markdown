---
layout: tutorial
status: publish
published: true
title: 'Tutorial 6 : 키보드와 '
date: '2011-05-08 08:26:13 +0200'
date_gmt: '2011-05-08 08:26:13 +0200'
categories: [tuto]
order: 60
tags: []
language: kr
---
6번째 튜토리얼에 오신 걸 환영합니다! 

오늘은 FPS 처럼 마우스와 키보드를 이용해 카매라를 어떻게 움직이는 지 알아볼거에요! 

# 인터페이스

이 코드는 이제 튜토리얼을 하는 동안 계속 우려먹을 거니까, 파일 분할을 해봐요. : common/controls.cpp에 코드를 추가하고, common/controls.hpp에 함수들을 선언해서 tutorial06.cpp가 코드를 인식하게 하세요. 

tutorial06.cpp은 저번 튜토리얼과 변경점이 크게 없어요. 주 변경점은 이제 MVP 메트릭스를 한번만 계산하는 대신에, 이제 매 프레임 계산하는 거에요. 그래서, 이 코드를 메인-루프에 추가해봐요 ! :

``` cpp
do{

    // ...

    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    // ...
}
```
이 코드는 3가지 새로운 함수가 필요해요 : 

* computeMatricesFromInputs()는 키보드와 마우스, 그리고 Projection 행렬과 View 행력의 계산을 담당하고 있어요. 여기서 모든 일이 일어날거에요!
* getProjectionMatrix()는, 계산한 Projection 행렬을 돌려주기만 합니다. 
* getViewMatrix()도, 계산한 View 행렬을 돌려주기만 합니다. 

물론, 이건 수많은 방법 중에 한 개일 뿐이에요. 이 함수들이 마음에 안드신다면, 계속해서 변경해보세요! 

자. 그러면 controls.cpp안으로 가봅시다!

# 진-짜 코드

몇몇 변수가 필요할거에요. 

``` cpp
// 좌표 
glm::vec3 position = glm::vec3( 0, 0, 5 );
// 수평각 : -Z 방향으로
float horizontalAngle = 3.14f;
// 수직각 : 0, 수직을 바라봅니다. 
float verticalAngle = 0.0f;
// 초기 FOV값
float initialFoV = 45.0f;

float speed = 3.0f; // 초당 3 unitsl
float mouseSpeed = 0.005f;
```

FoV는 줌의 단계에요. 80&deg; = 아주 넓은 각도고, 변형이 심해요. 60&deg; - 45&deg; : 표준이고. 20&deg; : 크게 확대되요.

우린 이제 입력에 따라 position, horizontalAngle, verticalAngle, 그리고 Fov를 수정하고, View, Projection 행렬을 position, horizontalAngle, verticalAngle, 그리고 Fov에 따라 계산할 거에요. 

## 방향 결정

마우스 좌표를 읽는 건 쉬워요.  :

``` cpp
// 마우스 좌표 받기 
int xpos, ypos;
glfwGetMousePos(&xpos, &ypos);
```
하지만, 커서를 화면의 중앙에 되돌려 놓지 않으면 커서가 화면 바깥을 나가게 되버리는데. 그러면 게임을 할 수 없겠죠? 다시 돌려놓읍시다!

``` cpp
// 매 프레임마다, 화면의 중앙으로 마우스 커서를 움직입니다.  
glfwSetMousePos(1024/2, 768/2);
```

아. 이 코드는 1024*768에 맞춰져 있어요. 화면 크기가 다르시다고요? glfwGetWindowSize를 이용하면 현재 화면 크기를 받아 오실 수 있어요. 

자. 이제 각도를 계산할 수 있겠네요. :
``` cpp
// 새로운 방향 계산
horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
```

그러면, 오른쪽에서 부터 왼쪽으로 읽어볼까요? :

* 1024/2 - xpos 는 : 얼마나 마우스가 윈도우에 중앙에서 부터 멀어졌는가? 에요. 더 돌고 싶으면, 이 값이 크면 되요.
* float(...)는 곱샘이 잘 되도록 정수형에서 실수형으로 바꿔줘요. 
* mouseSpeed는 회전 속도를 높이거나, 낮출 수 있어요. 괜찮게 튜닝하거나, 그냥 유저가 정하게 내버려둬요. 
* += : 만약 마우스를 움직이지 않으면, 1024/2-xpos는 0이 될거고, horizontalAngle+=0이 되어 horizontalAngle이 바뀌지 않겠죠. 만약에 "+="이 아니라, "="을 대신 사용한다면 매 프레임마다 원 상태로 복귀할건데. 그거, 별로 보기 안 좋아요. 

이제 우리는 바라보고 있는 방향을 가지고 있는 벡터를 계산할 수 있어요!

``` cpp
// 방향 : 구면 좌표를 데카르트 좌표로 변환 
glm::vec3 direction(
    cos(verticalAngle) * sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle) * cos(horizontalAngle)
);
```
이게 계산이기는 한데. 코사인과 사인에 대해서 잘 모르시는 분도 있을거에요. 그런 분을 위해 간단한 설명을 드릴게요. : 

<img class="alignnone whiteborder" title="Trigonometric circle" src="http://www.numericana.com/answer/trig.gif" alt="" width="150" height="150" />

위 공식은 3D에 대한 일반화에요. 

이제 "Up"벡터를 계산해봐요. "Up"은 항상 +Y 방향을 향하는 건 아닌데 - 가령, 아래를 바라본다면. "Up" 벡터가 수평이 되겠네요.  - 아래는 동일 위치, 동일 타겟, 그렇지만 다른 "Up" 벡터를 가지는 두개의 카메라를 보여주고 있어요. :

![]({{site.baseurl}}/assets/images/tuto-6-mouse-keyboard/CameraUp.png)

지금 우리의 유일한 상수는 카메라의 오른쪽으로 가는 벡터에요. 수평으로 설정되어 있는데... 팔을 수평으로 놓고, 어떤 방향으로든 아래를 내려다보시거나- 올려다 보시면 알 수 있을거에요. 오른쪽 벡터는 바뀌지 않겠죠? 하지만 몸을 돌리면 이야기가 달라지죠. 

이제 한번 "오른쪽" 벡터를 정의해봐요. Y 좌표는 수평이니 0이고, X 와 Z 좌표는 위의 그림과 같지만 각도는 90&deg;나 Pi/2 라디안으로 회전할거에요. 

``` cpp
// 오른쪽 벡터 
glm::vec3 right = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
);
```

"Right"벡터와 "Direction" 벡터, "Front"벡터가 있어요. "Up"벡터는 이 둘에 대해 수직인 벡터에요. 유용한 수학 함수를 사용하면이 작업을 매우 간단하게 처리 할 수 있어요. : 바로. 외적이에요!


``` cpp
// Up vector : Direction 과 Right에 대해 직각
glm::vec3 up = glm::cross( right, direction );
```

외적이 기억이 안나신다고요? 간단해요. 튜토리얼 3에서 보셨던 오른손 법칙을 생각해보세요. 첫 번쨰 벡터는 엄지 손가락, 두 번째 손가락은 검지 손가락. 그리고 답은 가운데 손가락이에요. 어때요. 참 쉽죠?

## 위치
코드는 간단해요. 그런데, 저는 WASD 대신 Up/Down/Right/Left 키들을 사용했는데. 왜냐하면- 저는 qwerty가 아니라 azerty 키보드를 쓰고 있고, awsd는 저에겐 zqsd로 보여요. 그리고 qwerZ 키보드들에게는 또 다르게 보일거고. 한글 키보드도 똑같을 거에요. 전 한국인 여러분들이 어떤 키보드 레이아웃을 쓰는지는 모르겠지만. 다를 것이라 생각해요. 

``` cpp
// 앞으로
if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
    position += direction * deltaTime * speed;
}
// 뒤로
if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
    position -= direction * deltaTime * speed;
}
// 오른쪽
if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
    position += right * deltaTime * speed;
}
// 왼쪽
if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
    position -= right * deltaTime * speed;
}
```

오. 다 괜찮은데.. deltaTime은 처음보네요. 이걸 왜 썼을까요? 용도를 알기전에 우선 간단한 예로 특별한 방법 없이는 일정하게 움직이는게 불가능하다는 걸 설명드릴게요 : 

* 좋은 컴퓨터를 가지고 게시면, 60프레임으로 실행시키실 거고, 그러면 1초에 60*speed를 이동합니다. 
* 느린 컴퓨터를 가지고 계시면, 20프레임으로 실행시키실 거고, 그러면 1초에 20*speed를 이동합니다.

더 좋은 컴퓨터를 사용한다고 더 빨라지면 안되죠! 그래서 일정하게 움직이려면 "마지막 프레임 이후의 시간" - 즉. "deltaTime" 만큼 거리를 조정해주는거에요! 

* 좋은 컴퓨터를 가지고 게시면, 60프레임으로 실행시키실 거고, 그러면 1 프레임당 1/ 60 * speed 을 움직일 거고, 그래서 1 * speed를 1초에 움직입니다.
* 느린 컴퓨터를 가지고 게시면, 20프레임으로 실행시키실 거고, 그러면 1 프레임당 1/ 20 * speed 을 움직일 거고, 그래서 1 * speed를 1초에 움직입니다.

뭐가 더 괜찮은진 명백해 보이네요. deltaTime은 계산하기도 아주 간단해요. 

``` cpp
double currentTime = glfwGetTime();
float deltaTime = float(currentTime - lastTime);
```

## Field Of View (FOV 값, 시야각)

심심하시면, 마우슬 휠을 Fov에 바인딩해서 아주 쉽게 확대 / 축소를 할 수 있습니다. 

``` cpp
float FoV = initialFoV - 5 * glfwGetMouseWheel();
```

## 행렬 계산하기 

행렬을 게산하는 건 이제 간단하죠. 예전이랑 똑같은 함수를 쓰지만, 새로운 매게변수를 넣을거에요. 
``` cpp
// Projection 행렬 : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
// 카메라 행렬
ViewMatrix       = glm::lookAt(
    position,           // 카메라는 여기 있고, 
    position+direction, // 보는 좌표도 여기 있어요.  : 같은 위치에서, "direction"만 더해주세요. 
    up                  // 머리는 여기있고요. (set to 0,-1,0 to look upside-down)
);
```

# 결과 

![]({{site.baseurl}}/assets/images/tuto-6-mouse-keyboard/moveanim.gif)


## 후면 컬링(날리기) 

이제 자유롭게 이동할 수 있는데, 큐브 안에 들어가도 폴리곤들이 계속 그려지네요. 지금은 볼 수 있긴 한데. 게임중에 큐브 '안'으로 들어가는 경우가 어디 있겠어요? 평소에도 사람 안으로 들어가는 일이 없다시피한데요. 그러니까 안은 그리지 맙시다. 최적화를 해요. 그 성능으로 더 많은 일을 할 수 있을거에요. 

아이디어는 간단해요. 카메라가 삼각형의 뒤에 있는지, 아니면 앞에 있는지 GPU가 확인하는 거에요. 앞에 있으면 삼각형을 그리는 거고. 뒤에 있고 - 매쉬가 닫혀있고, 그리고 우리가 매쉬안에 없고, 그리고 다른 삼각형이 앞에 있어서 아무도 볼 수 없다면 그걸 그리지 않는 거죠. 그러면 엄청나게 빨라질 거에요! : 평균적으로, 2배나 그릴 일이 없어요! 

게다가. 가장 좋은 점은 그걸 확인 하는 것도 아주 쉽다는 거에요. GPU는 삼각형의 법선을 계산하고(외적 쓰는 법, 기억하시죠?), 이 법선이 카메라를 향하고 있는지 확인하는 거에요. 

하지만 비용은 발생해요. 삼각형의 방향은 암시적이죠. 즉, 버퍼에서 두 개의 정점을 뒤집는다면 구멍이 생길 거에요. 하지만 못할 만한 일은 아니죠. 문제가 생긴다면 3D 모델러에서 "반전 법선(invert normals)"을 클릭한다면 (실제로 정점을 뒤집어서 법선도 뒤집어요. ) 다 잘 될거에요. 


컬링을 활성화 하는 건 아주 쉬워요! : 


``` cpp
// 카메라를 향하지 않은 삼각형을 렌더링 하지 않습니다. 
glEnable(GL_CULL_FACE);
```

# 연습문제 


* verticalAngle을 뒤집지 못하도록 제한하세요. 
* 오브젝트 주변을 도는 카메라를 만들어보세요. ( position = ObjectCenter + ( radius * cos(time), height, radius * sin(time) ) ); 회전 넓이나, 높이나, 시간을 키보드/마우스에 바인드 해보시고요. 음. 더 괜찮은 아이디어가 있으면 더 좋죠.
* 즐겨 보세요!

