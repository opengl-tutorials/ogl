---
layout: tutorial
status: publish
published: true
title: 'Tutorial 10 : 투명도'
date: '2011-05-13 23:00:42 +0200'
date_gmt: '2011-05-13 23:00:42 +0200'
categories: [tuto]
order: 500
tags: []
language: kr
---

# 알파 채널

알파 채널에 대한 개념은 꽤 간단해요. RGB 대신에, RGBA를 써보세요.

``` glsl
// Output Data ; 이제는 vec4에요.
// Ouput data : it's now a vec4
out vec4 color;
```

{: .highlightglslfs }

처음 .xyz는 옛날이랑 똑같고, 대신 뒤에 .a가 더 붙었어요.

``` glsl
color.a = 0.3;
```

{: .highlightglslfs }

비직관적이지만. 알파 = 불투명도에요. 그래서 알파가 = 1이면 완전히 불투명하고요. 알파가 = 0 이면 완전히 투명하다는 말이에요.

여기, 우리는 간단하게 알파 채널을 0.3으로 하드코딩했어요, 하지만 당연히 우리는 uniform으로 알파 값을 읽거나, 정 안되면 RGBA 텍스쳐에서 읽기를 원하죠. ( TGA는 알파 채널을 지원하고, GLFW2는 TGA를 지원해요. 다만 GLFW3은 안돼요.)

여기 결과에요. 아. 백페이스 컬링은 꺼주세요. (glDisable(GL_CULL_FACE)) 왜냐하면 우리는 이제 메쉬를 뚫어서 볼 수 있어서, 우리가 못 볼 수 없는 "뒷면"은 이제 없거든요.

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyok.png)


# 순서 문제

아까 스크린샷은 괜찮아 보이는데. 우리가 그냥 운이 좋아서 그래요. 실체를 봅시다.

## 문제

자, 50프로의 알파로 두 개의 사각형을 그렸어요. 하나는 초록색이고, 하나는 빨간색이죠. 여기서 순서가 중요하다는 걸 확인하실 수 있을건데, 결과로 나오는 색깔은 두 사각형에 깊이에 따라 차이가 있다는 걸 확인할 수 있을거에요.

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyorder.png)

위 현상은 우리에게도 발생하는데, 카메라 위치를 바꿔볼까요? :

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencybad.png)

옆에서 보면 엄청 심각한 문제라는걸 확인할 수 있어요. 사실 게임에서 투명도 많이 쓰는 거 못봤잖아요, 안 그래요? 있어도 진짜 투명이거나. 적어도 색깔은 안 입혔죠.

## 주 해결책

주 해결책은 모든 투명도가 적용된 삼각형을 정렬하는거에요. 네. **모든** 투명도가 적용된 삼각형을. **정렬**해야해요.

* 깊이 버퍼가 우선 세계의 불투명한 부분을 먼저 그려요. 그러면 안보이는 투명 삼각형은 자연스럽게 없앨 수 있겠죠?
* 가장 멀리 떨어져있는 것부터, 가장 가까운 것까지 투명 삼각형을 정렬해요.
* 투명 삼각형을 그려요.

qsort(C)나 std::sort(C++)를 이용해 정렬을 할 수 있을거에요. 하지만 더 자세히는 파고 싶지는 않네요. 왜냐하면...

## 경고

그렇게 하면 될건데, (다음 섹터에 더 자세히 설명하겠지만.) 하지만 :

* 속도가 느려질거에요. 각 픽셀들은 10번, 20번, 혹은 훨씬 더 그려야할건데. 안 그래도 모자른 메모리 버스엔 너무 많은 일이에요. 게다가 일반적으론 깊이 버퍼는 먼 픽셀들을 그리지 않을 수 있는데. 여기서는 명시적으로 정렬했으니 깊이 버퍼는 쓸모가 없어요. 
* 엄청 똑똑한 최적화를 쓰지 않는 이상, 픽셀당 4번(4xMSAA를 쓰고 있어요.) 이 작업을 해야해요. 
* 모든 투명 삼각형을 정렬하는데도 시간이 걸리고요. 
* 만약에 텍스쳐를 바꿔야만 하거나, 더 나쁜 경우로는 쉐이더를 삼각형 하나 하나마다 바꿔야 하면 성능에 심각한 문제가 있을거에요. 하지 마세요.

괜찮은 해결책은 주로 :

* 투명 폴리곤의 숫자를 제한하세요.
* 이 친구들을 그릴 때엔 같은 쉐이더, 같은 텍스쳐를 쓰세요.
* 그들이 엄청 다르게 보이면, 텍스쳐를 쓰세요! 쉐이더는 건들지 말고!
* 정렬을 안해도 *적당히* 괜찮다면. 그냥 행운이라 생각하고 넘어가세요.

## 순서 - 독립 투명성

만약에 엔진이 진짜, 진짜 최신 기술의 투명성이 필요하면. 다른 기법들을 조사해볼 가치가 있네요.

* [The original 2001 Depth Peeling paper](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.9286&rep=rep1&type=pdf): 픽셀 - 퍼펙트로 결과가 나와요. 그리 빠르진 않아요.
* [Dual Depth Peeling](http://developer.download.nvidia.com/SDK/10/opengl/src/dual_depth_peeling/doc/DualDepthPeeling.pdf) : bucket 정렬에 대한 여러 논문. 픽셀의 배열을 사용해요. 셰이더에서 깊이별로 정렬하고요. 
* [ATI's Mecha Demo](http://fr.slideshare.net/hgruen/oit-and-indirect-illumination-using-dx11-linked-lists) : 훌륭하고, 빠르지만 구현하기 까다롭고. 최신 하드웨어가 필요해요. 연결된 프래그먼트 목록을 사용해요.
* [Cyril Crassin's variation on the ATI's  technique](http://blog.icare3d.org/2010/07/opengl-40-abuffer-v20-linked-lists-of.html) : 더 어려운 구현!

강력한 콘솔에서 돌아가는 Liitle Big Planet 같은 게임도, 투명도를 1층만 사용한다는 걸 잊지마세요.

# 블랜드 함수

저번 코드에서 이어서 할게요. 블랜드 함수를 설정해주셔야 할 거에요.

``` cpp
// 블랜딩 활성화
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

뭔 말이냐면 :

``` text
프레임 버퍼의 새로운 색깔 =
        현재 프레임 버퍼의 알파 * 현재 프레임 버퍼의 색깔 + (1 - 현재 프레임 버퍼의 알파값)
        * 쉐이더 결과 색깔
```

예를 하나 보여드릴게요. :

``` cpp
new color = 0.5*(0,1,0) + (1-0.5)*(1,0.5,0.5); // (빨간 색은 이미 하얀색 배경화면과 섞였어요.)
new color = (1, 0.75, 0.25) = the same orange
```
