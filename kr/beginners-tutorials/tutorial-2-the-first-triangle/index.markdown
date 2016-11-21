---
layout: page
status: publish
published: true
title: 'Tutorial 2 : 첫 삼각형"
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

Now this is some boring white. Let's see how we can improve it by painting it in red. This is done by using something called shaders.

## Shaders

# Shader Compilation

In the simplest possible configuration, you will need two shaders : one called Vertex Shader, which will be executed for each vertex, and one called Fragment Shader, which will be executed for each sample. And since we use 4x antialising, we have 4 samples in each pixel.

Shaders are programmed in a language called GLSL : GL Shader Language, which is part of OpenGL. Unlike C or Java, GLSL has to be compiled at run time, which means that each and every time you launch your application, all your shaders are recompiled.

The two shaders are usually in separate files. In this example, we have SimpleFragmentShader.fragmentshader and SimpleVertexShader.vertexshader . The extension is irrelevant, it could be .txt or .glsl .

So here's the code. It's not very important to fully understand it, since you often do this only once in a program, so comments should be enough. Since this function will be used by all other tutorials, it is placed in a separate file : common/loadShader.cpp . Notice that just as buffers, shaders are not directly accessible : we just have an ID. The actual implementation is hidden inside the driver.

``` cpp
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
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


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
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

# Our Vertex Shader

Let's write our vertex shader first.
The first line tells the compiler that we will use OpenGL 3's syntax.

``` glsl
#version 330 core
```

The second line declares the input data :

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```

Let's explain this line in detail :

- "vec3" is a vector of 3 components in GLSL. It is similar (but different) to the glm::vec3 we used to declare our triangle. The important thing is that if we use 3 components in C++, we use 3 components in GLSL too.
- "layout(location = 0)" refers to the buffer we use to feed the *vertexPosition_modelspace* attribute. Each vertex can have numerous attributes : A position, one or several colours, one or several texture coordinates, lots of other things. OpenGL doesn't know what a colour is : it just sees a vec3. So we have to tell him which buffer corresponds to which input. We do that by setting the layout to the same value as the first parameter to glVertexAttribPointer. The value "0" is not important, it could be 12 (but no more than glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) ), the important thing is that it's the same number on both sides.
- "vertexPosition_modelspace" could have any other name. It will contain the position of the vertex for each run of the vertex shader.
- "in" means that this is some input data. Soon we'll see the "out" keyword.

The function that is called for each vertex is called main, just as in C :

``` glsl
void main(){
```

Our main function will merely set the vertex' position to whatever was in the buffer. So if we gave (1,1), the triangle would have one of its vertices at the top right corner of the screen. We'll see in the next tutorial how to do some more interesting computations on the input position.

``` glsl
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
```

gl_Position is one of the few built-in variables : you *have *to assign some value to it. Everything else is optional; we'll see what "everything else" means in Tutorial 4.

# Our Fragment Shader

For our first fragment shader, we will do something really simple : set the color of each fragment to red. (Remember, there are 4 fragment in a pixel because we use 4x AA)

``` glsl
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
```

So yeah, vec3(1,0,0) means red. This is because on computer screens, colour is represented by a Red, Green, and Blue triplet, in this order. So (1,0,0) means Full Red, no green and no blue.

## Putting it all together

Before the main loop, call our LoadShaders function :

```cpp
// Create and compile our GLSL program from the shaders
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

Now inside the main loop, first clear the screen. This will change the background color to dark blue because of the previous glClearColor(0.0f, 0.0f, 0.4f, 0.0f) call:

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

and then tell OpenGL that you want to use your shader:

``` cpp
// Use our shader
glUseProgram(programID);
// Draw triangle...
```

... and presto, here's your red triangle !

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

In the next tutorial we'll learn transformations : How to setup your camera, move your objects, etc.
