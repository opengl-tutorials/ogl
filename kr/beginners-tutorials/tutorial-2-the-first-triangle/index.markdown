---
layout: page
status: publish
published: true
title: 'Tutorial 2 : 첫 삼각형'
date: '2011-04-07 18:54:11 +0200'
date_gmt: '2011-04-07 18:54:11 +0200'
categories: [tuto]
order: 20
tags: []
language: kr
---
{:TOC}

이부분 또한 긴 튜토리얼이 될것입니다.

OpenGL 3 은 복잡한 것을 작성하기 쉽지만, 간단한 삼각형을 그리는 것은 오히려 어렵습니다.

습관적으로 코드를 복사 붙여넣는 것을 잊지마세요.
**<span style="color: red">만약 실행에 프로그램 크래쉬를 겪는다면, 잘못된 디렉토리에서 실행중인 것일 수 있습니다. 주.의.깊.게 첫번째 튜토리얼을 읽고 어떻게 비주얼 스튜디오를 설정하는지 보세요!</span>**

## VAO

지금은 자세한 설명은 하지않겠습니다. 일단 Vertex Array Object 를 생성해야 하고, 이들을 현재 사용중인 것으로 지정해야 합니다. :

``` cpp
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
```

다른 OpenGL 호출이 일어나기 전, 즉 새 창을 생성했을 때 (= OpenGL 컨텍스트가 생성된 후) 한번 이부분을 수헹해주세요.

VAO에 관해 정말로 더 알고 싶다면, 인터넷에 다른 몇몇 튜토리얼들이 있겠지만, 이것은 별로 중요한 부분이 아닙니다.

## 화면 좌표

삼각형은 세가지 점으로 정의됩니다. 3D 그래픽에서 "점"을 얘기할때는 보통 "버텍스(정점;vertex)" 이라는 단어를 사용합니다. 버텍스는 세 좌표를 가집니다: X, Y 그리고 Z. 이 세 좌표들을 아래와 같이 생각할 수 있습니다:

- X 는 당신의 오른쪽
- Y 는 위쪽
- Z 당신의 뒤쪽 (그래요, 뒤쪽, 당신의 앞쪽 말구요)

하지만 이것을 좀더 명확하게 떠올릴 수 있는 방법이 있습니다 : 오른손 법칙을 사용하세요

- X 는 엄지 손가락입니다.
- Y 는 집게 손가락입니다.
- Z 는 가운데 손가락입니다. 만약 엄지를 오른쪽으로 향하게 하고, 검지를 하늘로 향한다면, 가운데 손가락은 당연이 등뒤를 가리키겠죠.

Z 를 이러한 방향으로 둔다는게 이상할 수 있어요. 왜 그렇게 해야하지 ? 간단히 답하면 : 100여년간 이어진 오른손 법칙 계산법은 당신에게 유용한 도구를 많이 제공해주거든요. 단점이라곤 Z 방향이 직관적이지 않다 하나 뿐이죠.

참고로, 당신의 손을 자유롭게 이동할수 있음을 알아 두세요 : 당연히, 당신의 X, Y 그리고 Z 는 움직일 수 있습니다. 이에 대해선 나중에 논하죠.

So we need three 3D points in order to make a triangle ; let's go :
이제 우리는 삼각형을 만들기 위해 세개의 3D 점들이 필요합니다 ; 이제 시작해보죠 :

``` cpp
// 3 버텍스들을 표현하는 3 벡터들의 배열
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
```

가장 처음 베턱스는 (-1,-1,0) 입니다. 이는 우리가 _어떤 방법으로 변환(트랜스폼;Transform) 하기 전에는_, 화면상에는 (-1,-1)로 표시되죠. 이게 무슨 의미라는 거죠? 화면의 원점은 정중앙, 일반적으로 X는 오른쪽, Y는 상단입니다. 이는 와이드 화면에서 아래와 같이 표현됩니다.

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}

이는 당신이 바꿀 수 없는 것입니다. 그래픽 카드에 이미 내장된 것이죠. 즉 (-1,-1) 은 당신의 화면 좌측 최하단입니다. (1,-1) 은 당신의 화면 우측 최하단이구요. (0,1) 은 중앙 최상단 입니다. 그러니 우리가 그릴 삼각형은 분명 화면 대부분을 차지할거에요.

## 삼각형 그리기

다음 스탭은 이 삼각형을 OpenGL 로 넘겨주는 것입니다. 이를 버퍼를 생성해서 합니다:

```cpp
// 이것이 우리의 버텍스 버퍼를 가리킵니다.
GLuint vertexbuffer;
// 버퍼를 하나 생성합니다. vertexbuffer 에 결과 식별자를 넣습니다
glGenBuffers(1, &vertexbuffer);
// 아래의 명령어들은 우리의 "vertexbuffer" 버퍼에 대해서 다룰겁니다
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// 우리의 버텍스들을 OpenGL로 넘겨줍니다
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
```

이 부분은 단 한번만 해주면 됩니다

우리가 "아무것도 그리지 않은" 메인 루프에서, 이제 우리의 웅장한 삼각형을 그려봅시다 :

``` cpp
// 버퍼의 첫번째 속성값(attribute) : 버텍스들
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // 0번째 속성(attribute). 0 이 될 특별한 이유는 없지만, 쉐이더의 레이아웃(layout)와 반드시 맞추어야 합니다.
   3,                  // 크기(size)
   GL_FLOAT,           // 타입(type)
   GL_FALSE,           // 정규화(normalized)?
   0,                  // 다음 요소 까지 간격(stride)
   (void*)0            // 배열 버퍼의 오프셋(offset; 옮기는 값)
);
// 삼각형 그리기!
glDrawArrays(GL_TRIANGLES, 0, 3); // 버텍스 0에서 시작해서; 총 3개의 버텍스로 -> 하나의 삼각형
glDisableVertexAttribArray(0);
```

운이 좋다면, 결과를 볼 수 있을겁니다. (<span style="color: red">**그렇지 못했다고 패닉에 빠지지 마세요**</span>) :

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}

지금은 좀 시시한 하얀 색이죠. 어떻게 하면 붉은색으로 칠해서 좀더 멋지게 만들 수 있는지 봅시다. 이것은 쉐이더(shader) 라는 것에 의해 가능해요.

## 쉐이더

# 쉐이더 편집

가능한 최대한 간단하게 편집하는데 있어, 두가지 쉐이더가 필요할겁니다 : 하나는 버텍스 쉐이더로 각각의 버텍스 마다 실행되죠. 그리고 다른 하나는 프래그먼트 쉐이더로 불리는데, 각각의 샘플 단위 마다 동작합니다. 우리가 4x 안티앨리언싱을 사용했으니, 우리는 각각의 픽셀마다 4개 샘플을 가지고 있는거죠.

쉐이더는 GLSL 이라는 언어로 작성됩니다 : GL Shader Language 라 하며, OpenGL의 구성요소 중 하나죠. C 나 Java 와 달리, GLSL 은 런타임에서 컴파일됩니다. 이는 당신의 어플리케이션을 실행할때 마다 매번, 당신의 모든 쉐이더가 다시 컴파일 된다는 거죠.

이 두가지 쉐이더들은 보통 각각 분리된 파일로 들어갑니다. 이 예제에서는 SimpleFragmentShader.fragmentshader 와 SimpleVertexShader.vertexshader 라는 파일이 있죠. 확장자 명은 뭐라도 상관없습니다. .txt나 .glsl 이 될 수도 있어요.

자, 이제 여기 코드들입니다. 전부다 이해 못해도 딱히 상관없습니다. 왜냐면 대개 프로그램마다 이부분은 한번만 하고 말거거든요. 그러니 주석을 잘 보는 것 만으로 충분할겁니다. 이 함수는 다른 모든 튜토리얼에서도 사용될거라서, 개별 파일에 위치합니다: common/loadShader.cpp . 참고할 점은, 버퍼와 같이 쉐이더 또한 바로 접근은 되지 않습니다 : 그저 ID 만 알고 있을 뿐이죠. 실제 구현부는 드라이버의 내부에 숨겨져 있습니다.

``` cpp
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // 버텍스 쉐이더 코드를 파일에서 읽기
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", vertex_file_path);
		getchar();
		return 0;
	}

  // 프래그먼트 쉐이더 코드를 파일에서 읽기
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// 버텍스 쉐이더를 컴파일
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// 프래그먼트 쉐이더를 컴파일
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// 프로그램에 링크
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
```

# 우리의 버텍스 쉐이더

먼저 우리의 버텍스 쉐이더를 한번 작성해봅시다.
가장 첫번째 줄은 컴파일러에게 OpenGL 3 의 문법을 사용할거라 알려줍니다.

``` glsl
#version 330 core
```

두번째 줄은 입력 값을 선언합니다 :

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```

이 줄을 자세히 설명해볼게요 :

- "vec3" 는 GLSL에서 3 가지 컴포넌트를 지닌 벡터입니다. 이것은 우리가 삼각형을 선언하기 위해 사용한 glm::vec3 보다 비슷한 (하지만 다른) 것입니다. 중요한 점은, 만약 우리가 3가지 컴포넌트를 C++에서 사용한다면, GLSL에서도 3가지 컴포넌트를 사용합니다.
- "layout(location = 0)" 는 *vertexPosition_modelspae* 속성을 채우기 위해 사용한 버퍼를 가리킵니다. 각각의 버텍스는 많은 속성을 가질 수 있습니다 : 위치, 하나 혹은 그 이상의 색깔, 하나 혹은 그 이상의 텍스쳐 좌표들, 그외 많은 것들. OpenGL 은 색깔이 뭔지 모릅니다 : 그저 vec3 를 살펴보는 거죠. 그러니 녀석에게 어던 버퍼가 어떤 입력값에 해당하는지 알려줘야 합니다. 이는 glVertexAttribPointer 의 첫번째 입력으로 준 값과 똑같은 값으로 레이아웃을 설정해서 할 수 있습니다. 값 "0" 은 별로 중요하지 않습니다. 값이 12가 될수도 (하지만  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) 보다 클 순 없습니다) 있습니다, 중요한 것은 양쪽 모두 같은 숫자이어야 한다는 거죠.
- "vertexPosition_modelspace" 는 다른 어떠한 이름도 가질수 있습니다. 이 녀석은 각각의 버텍스 쉐이더가 실행될때 마다 해당 버텍스의 위치를 가지고 있을 겁니다.
- "in" 은, 이것은 어떤 입력 데이터다, 라는 뜻입니다. 곧, 우리는 "out" 키워드도 보게 되겠죠.

각각의 버텍스를 위해 호출되는 이 함수는, 메인(main)에서 호출됩니다. C 에서 같이요 :

``` glsl
void main(){
```

우리의 main 함수는 그저 단순이 버텍스의 위치를, 버퍼에 무엇이 있었든 간에 그 값들로 설정할겁니다. 그러니 만약 우리가 (1,1) 을 주었었다면, 삼각형은 아마 그중 하나의 버텍스가 화면의 상단 우측 코너에 있겠죠. 우리는 다음 튜토리얼에서 어떻게 입력 위치값에 흥미로운 연산들을 추가하는지 볼겁니다.

``` glsl
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
```

gl_Position 은 몇 안되는 내장(built-in) 변수 입니다 : 당신은 *반드시* 어떤 값을 할당해야 합니다. 다른 모든 것은 필수는 아닙니다; 우리는 "다른 모든 것들"의 의미를 튜토리얼 4 에서 볼겁니다.

# 우리의 프래그먼트 쉐이더

우리의 프래그먼트 쉐이더에 대해서는, 정말 간단한 일만 해주면 됩니다 : 각 프래그먼트를 붉은 색으로 설정합니다. (기억하세요. 우리는 4x AA 를 사용하기에 픽셀당 4개의 프래그먼트가 존재합니다)

``` glsl
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
```

네 그래서, vec(1,0,0) 은 붉은 색을 뜻하게 됬습니다. 왜냐면 컴퓨터 화면에서, 컬러는 빨강, 초록, 그리고 파랑 트리플렛(triplet;세 쌍둥이), 이런 순서로 이루어지거든요. 그러니 (1,0,0) 은 완전 레드를 뜻하죠. 어떠한 그린이나 블루도 없는.

## 죄다 한군데 몰아 넣기

main 루프를 시작하기 전에, 우리의 LoadShaders 함수를 호출합니다 :

```cpp
// 쉐이더들에서 우리의 GLSL 프로그램을 생성하고 컴파일하기
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

이제 메인 루프에서, 먼저 화면을 정리(clear) 합니다. 이것은 배경 컬러를 검파랑으로 바꿀 것인데 이것은 glClearColor(0.0f, 0.0f, 0.4f, 0.0f) 호출 때문이죠 :

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

그리고 나서 OpenGL 에게 당신의 쉐이더를 사용하고 싶다고 알려주세요:

``` cpp
// 우리의 쉐이더를 사용하기
glUseProgram(programID);
// 삼각형 그리기...
```

... 그리고 얍, 여기 당신의 붉은 삼각형이 있네요 !

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

다음번 튜토리얼에서 우리는 변환transformations 에 대해 배울 겁니다 : 어떻게 카메라를 설정하고, 당신의 오브젝트를 움직이는지 등 을요.
