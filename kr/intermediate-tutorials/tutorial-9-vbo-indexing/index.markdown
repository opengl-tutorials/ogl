---
layout: tutorial
status: publish
published: true
title: 'Tutorial 9 : VBO Indexing'
date: '2011-05-12 19:21:49 +0200'
date_gmt: '2011-05-12 19:21:49 +0200'
categories: [tuto]
order: 490
tags: []
language: kr
---

# 색인 생성 원칙

지금까지, 우리가 VBO를 만들때마다 삼각형이 같은 정점을 공유함에도 불구하고 정점을 복사했어요.

이번 튜토리얼에선 인덱싱을 소개할게요. 동일한 정점을 반복해서 사용하는 기법인데. *인덱스 버퍼*라고 불러요. 

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/indexing1.png)


인덱스 버퍼는 다양한 메시의 *속성 버퍼*(Position, Normal, UV 좌표...)를 참조하는 세 개의 정수를 저장하는 버퍼에요. OBJ 파일 형식이랑 비슷한데, 기억나요? 한가지 차이점이 있다면 인덱스 버퍼는 오직 하나고. 삼각형끼리 꼭지점을 공유하려면 모든 속성이 같아야 한다는 거에요. 

# 공유 정점 VS 분할 정점

자. 법선 예제를 들고와볼게요. 이 그림에서 두 삼각형을 만든 예술가는 매끄러운 표면을 만들고 싶어 하는 것 같아요. 그렇게 해주려면 두 삼각형의 법선을 단일 꼭지점 법선으로 합칠 수 있겠죠? 시각화를 위해 매끄러운 표면의 모습을 나타내는 빨간선을 그릴게요. 

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/goodsmooth.png)

두번째 그림에서는 어, 아티스트가 뾰족하게 보이길 원했나봐요. 하지만 만약 우리가 법선을 합친다면 - 셰이더는 평소같이 이걸 보간할 거고, 방금전이랑 비슷한 부드러운 면을 만들겠네요. 

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/badmooth.png)

그래서 이 경우에는 두 개의 다른 법선(각 꼭지점마다 하나씩이요.)을 갖는 게 더 좋아보이네요. OpenGL에서 이 작업을 하려면 전체 속성 세트과 전체 정점을 복제해야해요. 그게 유일한 방법이에요. 

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/spiky.png)


# OpenGL에서 VBO(Vertex Buffer Object) 인덱싱하기 

인덱싱을 사용하는건 아주 간단해요. 우선, 인덱스를 담을만한 추가적인 버퍼를 만드셔야 해요. 이 코드는 옛날이랑 같지만. ARRAY_BUFFER가 ELEMENT_ARRAY_BUFFER로 바뀌었어요. 

``` cpp
std::vector<unsigned int> indices;

// fill "indices" as needed

// Generate a buffer for the indices
 GLuint elementbuffer;
 glGenBuffers(1, &elementbuffer);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
```

glDrawArrays 대신, 이걸 써서 그림을 그릴게요 : 

``` cpp
// Index buffer
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

 // Draw the triangles !
 glDrawElements(
     GL_TRIANGLES,      // mode
     indices.size(),    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 );
```
(참고 : "unsighed int"를 쓰는 것보단 "unsigned short"를 쓰는 것이 더 좋을거에요. 왜냐하면 그게 더 메모리를 적게먹고, 더 빠르거든요.)

# 인덱스 버퍼 체우기 

자. 이제 진짜 문제가 생겼어요. 아까 말했듯 OpenGL은 하나의 인덱스 버퍼만 가질 수 있는데. OBJ(와, 인기있는 다른 3D 형식들은) *속성마다* 하나의 인덱스 버퍼를 쓰고 있어요. 그러니까 우리는 이 N개의 인덱스 버퍼를, 하나의 인덱스 버퍼로 만들어야해요. 

알고리즘은 다음과 같아요. : 
```

For each 입력 정점마다. 
    이미 나온 결과에서 비슷한 정점(모든 속성이 같은걸로!)을 찾아봐요.
    찾았다! :
        비슷한 정점이 이미 VBO에 있네요. 대신 사용합시다!
    못찾았다.. :
        비슷한 정점은 없으니, VBO에 추가합시다. 
```

이 구현 내용이 담긴 C++ 코드는 common/vboindexer.cpp에서 볼 수 있어요. 알고리즘을 이해시키기 위해 많은 주석이 달려져 있어요. 

유사성의 기준은, 정점의 위치, UV, 그리고 법선이 동일해야한다는 말이에요. 더 많은 속성을 추가하시면 똑같이 검사하셔야 하고요. 

유사한 정점 검사는 느린 선형 검사로 실행되요. std::map을 쓰는 것이 현업에서 쓰는데 더 적합할거에요.

# 추가 : FPS 측정기

이건 인덱싱에 관한건 아닌데,[The FPS counter](http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/)를 볼 좋은 시기인 것 같아요. 왜냐하면 우리가 오늘 한 인덱싱으로 속도가 얼마나 향상되엇나 볼 수 있거든요. 다른 성능 도구들은 [Tools - Debuggers](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/#debugging-tools)에서 볼 수 있어요.

