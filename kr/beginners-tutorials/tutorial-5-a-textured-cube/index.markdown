---
layout: tutorial
status: publish
published: true
title: 'Tutorial 5 : A Textured Cube'
date: '2011-04-26 07:55:58 +0200'
date_gmt: '2011-04-26 07:55:58 +0200'
categories: [tuto]
order: 50
tags: []
language: kr
---
이 튜토리얼에서는 이걸 배울거에요! :

* UV 좌표계가 뭘까요?
* 어떻게 텍스처를 로딩할까요? 
* 그리고 그것들을 OpenGL에서 어떻게 쓸까요?
* 필터링과 밉맵핑이 뭔지, 그리고 그걸 어떻게 쓸까요?
* 어떻게 GLFW를 이용해서 텍스처를 더 편하게 로드할 수 있을까요?
* 알파 채널이 도대체 뭘까요? 



# UV 좌표계에 대해서
Mesh에 텍스쳐링(텍스처를 붙이는 작업)하려면, 여러분은 각 삼각형(폴리곤)에 사용할 이미지의 일부를 OpenGL에게 전해줘야 하는 방법이 필요할거에요. 그 때 필요한 것이 UV 좌표계이랍니다. 

각각의 정점은 위치의 제일 위에서 부터 2개의 float을 가질 수 있어요. 바로 U와 V죠. 이 좌표들은 텍스처에 접근할때 필요한데, 한번 보시죠!

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/UVintro.png)

삼각형에서 텍스처를 씌우면, 어떻게 왜곡되는지 살펴보세요.


# 혼자서 .BMP 이미지들 로딩해보기
# Loading .BMP images yourself


사실 BMP 파일 형식을 아는 건 그리 중요한게 아니에요. 많은 라이브러리들은 BMP 파일을 끝장나게 로드해 줄 수 있거든요. 그래도 아주 간단하고, 새련된 인터페이스 밑에서 얼마나 추악한 짓이 일어나고 있는지 이해하는데 도움이 될거에요. 자. 그러면 BMP 파일 로더를 처음부터 만들어서. 작동 방식을 알고. <span style="text-decoration: underline;">그다음에 영원히 코드를 잠재워버립시다</span>. 이 세상에는 더 가치 있는 코드가 많으니까요! 

로딩 함수의 정의부터 살펴봐요!: 

Here is the declaration of the loading function :

``` cpp
GLuint loadBMP_custom(const char * imagepath);
```

그러면, 이렇게 쓰겠죠? : 

``` cpp
GLuint image = loadBMP_custom("./my_texture.bmp");
```

자. 그러면 어떻게 BMP 파일을 읽나 봅시다. 
먼저, 자료가 필요할 건데. 이 변수들은 파일을 읅을 때 설정될거에요. 

``` cpp
// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
// Actual RGB data
unsigned char * data;
```

우리는 이제 '진짜로' 파일을 열고 있어요!

``` cpp
// Open the file
FILE * file = fopen(imagepath,"rb");
if (!file){printf("Image could not be opened\n"); return 0;}
```

파일의 처음 부분은 54-바이트 헤더일거에요. 여기엔 "이거, 진짜 BMP파일이야?"와 같은 정보가 저장되어 있어요. 그러니까 이미지의 크기, 픽셀당 비트수 같은 거 말이에요. 자. 한번 읽어볼까요?: 


``` cpp
if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}
```

헤더는 언제나 BM으로 시작할 거에요. 진짜냐고요? 그럼 16진수 편집기로 한번 까보죠! :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/hexbmp.png)

자. 그래서 우리는 첫 두바이트가 진짜 'B'와 'M'인지 체크해야 해요. :

``` cpp
if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
}
```
그럼 이제 우리는 이미지의 크기를 읽을 수 있고, 파일의 위치나.. 그런 것들을 읽을 수 있어요. : 

``` cpp
// 바이트 배열에서 int 변수를 읽습니다. 
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);
```

몇몇 정보가 날아갔을 때도 대비해야죠! :

``` cpp
// 몇몇 BMP 파일들은 포맷이 잘못되었습니다. 정보가 누락됬는지 확인해봅니다. 
// Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
if (dataPos==0)      dataPos=54; // The BMP header is done that way
```

자, 그러면 우리는 이제 이미지의 크기를 알고 있으니까 -  이미지를 저장할 메모리를 할당한 다음 - 파일을 읽을 수 있겠네요! :

``` cpp
// 버퍼 생성
data = new unsigned char [imageSize];

// 파일에서 버퍼로 실제 데이터 넣기. 
fread(data,1,imageSize,file);

//이제 모두 메모리 안에 있으니까, 파일을 닫습니다. 
//Everything is in memory now, the file can be closed
fclose(file);
```
자. 드디어 '진짜' OpenGL 파트에 도착했어요. 텍스처 생성은 정점 버퍼 생성이랑 아주 비슷해요. 또 텍스처를 만들고, 또 바인딩 하고, 또 채우고, 또 구성하는거죠!

glTexImage2D에선. GL_RGB는 3가지 색상이라고 알려주는거고요, 그리고 GL_BGR은 RAM에 정확히 어떻게 표현되는지 알려주는거에요. 실제론, BMP는 빨강->초록->파랑 순이 아니라 파랑->초록->빨강으로 저장해요. 그래서. 우리는 그걸 OpenGL에게 알려줘야해요. 

``` cpp
// OpenGL Texture를 생성합니다. 
GLuint textureID;
glGenTextures(1, &textureID);

// 새 텍스처에 "Bind" 합니다 : 이제 모든 텍스처 함수들은 이 텍스처를 수정합니다. 
// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, textureID);

// OpenGL에게 이미지를 넘겨줍니다. 
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

마지막 두 줄은 나중에 설명할게요. 어쨌든, C++에선 이제 새 기능을 이용해 텍스처를 로드할 수 있어요! :

``` cpp
GLuint Texture = loadBMP_custom("uvtemplate.bmp");
```

> 아주 아주 중요한 점이에요! :** 2배수의 텍스처를 쓰세요! !**
>
> * 좋음 : 128\*128, 256\*256, 1024\*1024, 2\*2...
> * 나쁨 : 127\*128, 3\*5, ...
> * 괜찮은데, 이상해요. : 128\*256

# OpenGL에서 텍스처 쓰기

자. Frgament Shader를 먼저 봅시다. 간단해요! :

``` glsl
#version 330 core

// 정점 셰이더에서 넘겨준 보간 값.
in vec2 UV;

// 출력 데이터
out vec3 color;

// 한 메쉬를 그리는 동안 일정하게 유지되는 값.
uniform sampler2D myTextureSampler;

void main(){
    // Output color = 지정된 UV에서 텍스처의 색. 
    color = texture( myTextureSampler, UV ).rgb;
}
```

자. 세가지가 필요합니다! : 
* Fragment Shader는 UV 좌표가 필요한 것 같네요. 좋아요. 
* 그리고, 접근할 텍스처를 확인하려면 "Sampler" 2D가 필요한 것 같고요. (동일한 셰이더로, 여러 텍스처에 접근할 수 있어요.)
* 마지막으론, texture() 함수를 통해 텍스쳐에 접근하면, (R,G,B,A) vec4를 돌려주네요. 곧 A에 대해 알아 볼거에요. 


Vertex Shader도 간단해요, 그냥 UV 좌표들을 Fragment Shader에 전해주기만 하면 되죠! :

``` glsl
#version 330 core

// 입력 정점 데이터, 이 셰이더가 실행할 때마다 달라집니다. (각 정점마다 셰이더가 한번씩 실행되요.)
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// 출력 데이터 ; 각 픽셀마다 알아서 보간될거에요. 
out vec2 UV;

// 이 변수는 '매쉬당' 상수에요. 
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){
    // 정점의 출력 위치 = MVP(Model View Projection) * position;
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    
    // 정점의 UV. 특별한 건 없음. 
    UV = vertexUV;
}
```
튜토리얼 4에 나왔던 "layout(location = 1) in vec2 vertexUV"를 기억하세요? 뭐, 여기서도 똑같이 해야겠지만. (R,G,B) 세 개를 주는 것보단 (U,V) 를 던져주죠! 그 편이 더 예쁠꺼니까요. 

``` cpp
// 정점 당 두개의 UV 좌표. Blender에서 생성되었습니다. 곧 이걸 스스로 하는 법을 배울겁니다. 
static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};
```
위 UV 좌표는 다음 모델에 해당되요 : 

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/uv_mapping_blender.png)

자. 2번이나 했던 걸 또 해봐요. 버퍼 생성, 바인딩, 채우고, 구성하고, 그리고 평소대로 Vertex Buffer를 그리는데. 조심할 점은 glVertexAttribPointer 함수에서 두 번째 매게변수(size, 크기.)는 3이 아니라 2에요! 중요하니 다시 말할께요. glVertexAttribPointer 함수에서 두 번째 매게변수(size, 크기.)를 3에서 2로 바꿔요!


이제 결과를 볼까요? : 

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering.png)

그리고 - 줌인 버전! : 

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering_zoom.png)

# 밉맵과 필터링은 무엇이고, 어떻게 쓸까

아래 스크린 샷에 볼 수 있듯. 텍스처 품질이 구리네요. 왜일까요? 우리가 loadBMP_custom에서 이렇게 써서 그래요. :

``` cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

그러니까, 우리의 Fragment Shader에서, texture() 함수가 대충 U,V 좌표에 있는 texel(역주: Tex + Pixel)을 취하고. 계속 대충 때려박는거죠. 왜냐면 화면은 아-주 크지만. 텍스처는 아-주 크지는 않으니. 한 Texel에서 계속 똑같은 색만 들고 오는 거에요.  

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearest.png)

자. 이대로 두고 볼수만은 없겠죠?

## 선형 필터링 

선형 필터링을 쓰면, texutre() 함수는 주변의 다른 텍셀을 보기 시작하고. 각 텍셀까지의 거리에 따라 색상을 섞어요. 그렇게 하면- 아까 보이던 도트게임 같던 비주얼은 사라지겠죠!  


![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/linear1.png)

어휴, 굉장한 진전이기는 한데, 그치만 여전히 구려보인다면. 이것보단 조금 더 느린 비등방성 필터링이라는 걸 쓸 수 있어요. 

## 비등방성 필터링
이 부분은 조각을 통해 실제로 보이는 이미지 부분을 근사해요. 예를 들어, 다음 텍스처가 측면에서 보이고 조금 회전한다면, 이방성 필터링이 주 방향에 따라 고정된 수의 샘플("비등방성 레벨")을 취해 파란색 직사각형에 포함된 색깔을 계산해요. 

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/aniso.png)

## 밉맵 

선형, 비등방성 필터링은 둘 다 문제를 가지고 있어요. 만약에 텍스처가 멀리서도 잘 보이려면, 4개의 텍셀을 섞는 것만으론 충분하지 않겠죠. 실제로, 만약 우리의 3D 모델이 화면의 한 픽셀(fragment를 Pixel로 번역했습니다.) 만 차지 한다면. 이미지의 *모든* 텍셀들의 평균을 내서 최종 색깔을 결정해야해요. 점 하나 그리는데 말이에요! 그걸 누가 해요?! 아무도 안하죠! 똑똑한 사람들은 모두 MipMaps를 쓰거든요!

![](http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg)

* 초기화 때, 이미지를 2배씩 계속 축소면서 1x1 이미지(사실상 이미지 내 모든 Texel의 평균)까지 생성해요.
* 메쉬를 그릴 때, 텍셀이 얼마나 커야된지 생각하며 어느 밉맵을 쓸지 정해요. 
* 가장 가까운 밉맵을 선형이나 이방성 필터링을 써서 샘플링해요. 
* 더 괜찮은 결과를 얻으려면, 두개의 밉맵을 샘플링하고 섞어서 결과를 얻을 수도 있겠네요! 

다행히도, 위 과정은 아주 간단하게 할 수 있어요! OpenGL은 우리들을 잘 돌봐주고 있거든요. :

``` cpp
// 이미지를 확대할땐(영어로 확대는 MAGnifying. 앞글자 MAG를 따왔네요.), 선형 필터링을 사용합니다. 
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 이미지를 축소할땐(영어로 축소는 MINifying. 앞글자 MIN을 따왔네요.), 두개의 밉맵을 선형으로 블랜드하고, 선형으로 필터링합니다. 
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 그리고- 밉맵 생성. 
glGenerateMipmap(GL_TEXTURE_2D);
```

# GLFW로 텍스처 로드하기 

우리의 loadBMP_custom 함수는 괜찮아요. 물론 우리가 스스로 만든 건 치곤요. 하지만 역시 전용 라이브러리를 쓰는 게 더 좋아요. GLFW2는 훌륭한 역활을 해줄거에요!(하지만 TGA 파일 밖에 안되고. 게다가 GLFW3에선 그 기능마저 사라졌어요. 우리가 '지금' 쓰는 버전 말이에요. ) (역주: 그럼 도대체 왜 이게 있는거지;) : 

``` cpp
GLuint loadTGA_glfw(const char * imagepath){

    // OpenGL 텍스처 생성! 
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // 새롭게 생성된 텍스처를 "Bind"합니다. : 이제 앞으로 모든 Texutre 관련 함수는 이 친구를 건듭니다. 
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 파일을 읽고, 매개 변수로 glTexImage2D를 호출해요. 
    glfwLoadTexture2D(imagepath, 0);

    // 괜찮은 3중 필터링. 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 우리가 만든 Texture의 ID를 돌려줍니다! 
    return textureID;
}
```

# 압축 텍스쳐

자. 이제 TGA나, BMP처럼 멸종당한 생명체보단 JPEG 파일을 로드하는 게 궁금 할 거에요. 

짧은 답을 드리죠 : 하지마요. GPU들은 JPEG를 이해하지 못해요. 그래서 원본 이미지를 JPEG로 압축하고, 또 압축을 풀고 GPU가 이해할 수 있도록 해야하는데요. 그럼 결국 원시 이미지로 돌아왔지만. JEPG로 돌아오는 동안 화질은 떨어졌죠. 램은 그대로 먹고요. 


더 괜찮은 방법이 있어요. 

## 압축 택스쳐 만들기 


* [The Compressonator](http://gpuopen.com/gaming-product/compressonator/)를 다운로드 받으세요, AMD 툴입니다. 
* 2의 제곱 텍스처를 넣어요!
* Runtime에 밉맵들을 만들고 싶지 않으면, 지금 만들 수 있어요. 
* DXT1, DXT3나 DXT5로 압축하세요.(더 자세한 정보는 [Wikipedia](http://en.wikipedia.org/wiki/S3_Texture_Compression)) :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/TheCompressonator.png)

* .DDS 파일로 뽑습니다. 
* Export it as a .DDS file.

이 시점에서, 우리의 이미지는 GPU에 바로 박을 수 있는 포맷으로 압축되었어요. shader 안에서 texutre() 함수를 부를 때, 즉석해서 압축을 풀거에요. 압축 푸는게 느려보일 수 있지만 - 엄청나게 적은 메모리를 먹어서 적은 양의 데이터만 전송하면 되기에 - 오히려 더 빠른데요. 왜냐면 텍스처 압축해제는 무료지만(전용 하드웨어가 있어요.), 데이터 전송이 비싸기 때문이죠! 일반적으로, 텍스처 압축을 사용하면 성능이 무려 20%나 증가해요! 성능과 메모리를 절약할 수 있죠. 조금 텍스처가 구려보이겠지만. 


## 압축 텍스처 사용하기

그럼 이미지를 어떻게 불러오는 지 보자고요! BMP 로드 코드랑 유사하지만, 헤더가 다르다는게 차이점이에요. : 
``` cpp
GLuint loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* 파일 열기 시도 */
    fp = fopen(imagepath, "rb");
    if (fp == NULL)
        return 0;

    /* 파일 타입 체크 */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* 이미지의 정보를 긁어옵니다.  */
    fread(&header, 124, 1, fp);

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
```

헤더 뒤에 진짜 데이터가 있는데요. 모든 밉맵 레벨들이 포함되어 있어요! 그리고 우린 이걸 한번에 읽을 수 있고요 :

``` cpp
    unsigned char * buffer;
    unsigned int bufsize;
    /* 모든 밉맵을 포함하면 얼마나 크나요? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* 파일 포인터 닫기  */
    fclose(fp);
```

우리는 - 머리가 복잡해지기 싫으니 - 3가지 포맷들만 다룰게요 : DXT1, DXT3, 그리고 DXT5. 위에서 얻은 "fourCC" 플래그는 OpenGL이 이해할 수 없으니. OpenGL이 이해할 수 있는 값으로 바꿀게요. 

``` cpp
    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }
```

텍스처 생성은 평소 같이! :

``` cpp
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // 새롭게 생성된 텍스처를 "Bind"합니다. : 이제 앞으로 모든 Texutre 관련 함수는 이 친구를 건듭니다. 
    glBindTexture(GL_TEXTURE_2D, textureID);
```

그리고, 우리는 이제 각 밉맵을 하나씩 채워 넣기만 하면 되죠. :

``` cpp
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer);

    return textureID;
```

## UV 좌표 반전하기 

DXT 압축은 OpenGL과 V 좌표계가 반대인 DirectX에서 건너왔어요. 그래서 압축된 텍스처를 사용할 때엔 올바른 Texel을 가져 오기 위해 이 공식을 써야해요.( coord.u, 1.0 - coord.v ) 뭐, 언제 하든 상관 없어요. : 로더에서 하든, 쉐이더에서 하든... 방법은 많겠죠. 그냥 까먹지나 마요. 

# 결론

박수! 이제 OpenGL 텍스처를 만들고, 불러오고 사용하는 법을 배우셨어요! 

일반적으로 압축 된 텍스처가 저장하기에도 작고, 불러오는 데도 엄청 빠르고, 사용하기도 엄청 빨라서 사용해야해요. 뭐. 단점이 있다면 Compressonator를 이용해서 변환해야 한다는 걸까요? 귀찮죠. (아니면 다른 툴을 쓰던가요.) 

# 연습문제들

* DDS 로더는 소스코드에 구현은 되어있는데, 텍스처 좌표는 수정하지 않아요. 적절하게 코드를 변경해서 큐브를 멋지게 출력해봐요! 
* 다양한 DDS 형식으로 실험해보세요. 다른 결과를 주던가요? 다른 압축 비율이라던가? 
* Compressonator에서 밉맵을 생성하지 마세요. 어떻게 되던가요? 터졌나요? 터졌으면 해결하는 3가지 다른 방법을 만들어봐요!


# 참고문헌들


* [Using texture compression in OpenGL](http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf) , S&eacute;bastien Domine, NVIDIA


# 참고
역주 : 알파 채널 내용은 원본에서도 안 나와있습니다. 
