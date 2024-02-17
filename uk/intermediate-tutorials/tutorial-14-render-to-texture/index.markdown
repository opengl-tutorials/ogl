---
layout: tutorial
status: publish
published: true
title: 'Туторіал 14 : Рендер в текстуру'
date: '2011-05-26 19:33:15 +0200'
date_gmt: '2011-05-26 19:33:15 +0200'
categories: [tuto]
order: 540
tags: []
language: uk
---

* TOC
{:toc}

Рендер (малювання) в текстуру - це зручний метод для створення різноманітних ефектів. Основна ідея полягає в тому, що Ви малюєте сцену як зазвичай, але в текстуру, яку потім можна буде використати.

Може використовуватися для "камери в грі", подальшої обробки і багатьох GFX яких тільки Ви можете собі уявити. 

# Рендер в текстуру

У нас є три задачі: створити текстуру, в яку будемо малювати, намалювати щось в неї та використати готову намальовану текстуру.


## Створення цілі рендеру

Ми будемо малювати в те, що називається буфером фрейму. Це контейнер для текстур та необов'язкового буферу глибини. Він створюється точнісінько так само, як і будь-який інший об'єкт OpenGL:

``` cpp
// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
GLuint FramebufferName = 0;
glGenFramebuffers(1, &FramebufferName);
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
```

Тепер нам потрібно створити текстуру, яка буде містити RGB результат нашого шейдера. Цей код виглядає достатньо класично:

``` cpp
// Текстура, куди будемо малювати
GLuint renderedTexture;
glGenTextures(1, &renderedTexture);

// Прив'яжемо новостворену текстуру - все подальші функції, що працюють з текстурами, будуть її використовувати
glBindTexture(GL_TEXTURE_2D, renderedTexture);

// Дамо OpenGL пусте зображення ( останній "0" )
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

// Погана фільтрація. Потрібно!
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

Також нам потрібен буфер глибини. Це не є обов'язковим, все залежить від того, що насправді потрібно намалювати в текстуру. Але так як ми хочемо намалювати Сюзанну, нам потрібен буфер глибини.

``` cpp
// Буфер глибини
GLuint depthrenderbuffer;
glGenRenderbuffers(1, &depthrenderbuffer);
glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
```

І в кінці налаштуємо буфер фрейму:

``` cpp
// Налаштуємо "renderedTexture" як кольоровий <<"attachement">> №0
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

// Встановимо буфер для малювання
GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
glDrawBuffers(1, DrawBuffers); // "1" - це розмір DrawBuffers
```

Дещо може піти не так на протязі цього процесу, це залежить від можливостей GPU. Ось як можна перевірити це:

``` cpp
// Завжди перевіряйте, що з нашим буфером фрейму все гаразд
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
return false;
```

## Рендер в текстуру

Rendering to the texture is straightforward. Simply bind your framebuffer, and draw your scene as usual. Easy !

``` cpp
// Малюємо в фрейм буферу
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
glViewport(0,0,1024,768); // Намалюємо весь буфер фрейму, заповнивши від нижнього лівого края до верхнього правого
```

Наш фрагментний шейдер потребує маленької адаптації:

``` cpp
layout(location = 0) out vec3 color;
```

Це значить, що коли відбувається запис в змінну `color`, ми насправді записуємо в ціль для малювання №0, яка є нашою текстурою, тому що `DrawBuffers[0]` це GL_COLOR_ATTACHMENT*i*, що в нашому випадку *renderedTexture*.

Підсумуємо :

* *color* буде записано в перший буфер так як `layout(location=0)`.
* Перший буфер є `GL_COLOR_ATTACHMENT0` тому що `DrawBuffers[1] = {GL_COLOR_ATTACHMENT0}`
* GL_COLOR_ATTACHMENT0 має приєднане *renderedTexture* - сюди буде записуватись колір.
* Іншими словами, Ви можете замінити `GL_COLOR_ATTACHMENT0` на `GL_COLOR_ATTACHMENT2` і це все ще буде працювати.

Зауважте: в OpenGL < 3.3 немає `layout(location=i)`, тому використовуйте `glFragData[i] = mvvalue`.


## Використання текстури, в яку відбувся малювання

Ми збираємося намалювати простий чотирикутник, який заповнить екран. Нам потрібні звичайні буфери, шейдери, ідентифікатори...

``` cpp
// FBO повноекранного чотирикутника
GLuint quad_VertexArrayID;
glGenVertexArrays(1, &quad_VertexArrayID);
glBindVertexArray(quad_VertexArrayID);

static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
};

GLuint quad_vertexbuffer;
glGenBuffers(1, &quad_vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

// Створимо та скомпілюємо GLSL програму з наших шейдерів
GLuint quad_programID = LoadShaders( "Passthrough.vertexshader", "SimpleTexture.fragmentshader" );
GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
GLuint timeID = glGetUniformLocation(quad_programID, "time");
```

Тепер Ви хочете намалювати це на екран. Це можна зробити, використовуючи 0 як другий параметр `glBindFramebuffer`.

``` cpp
// Малюємо на екран
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glViewport(0,0,1024,768); // Намалюємо весь буфер фрейму, з лівого нижнього кута в верхній правий
```
Ми можемо намалювати наш повноекранний чотирикутник таким шейдером:

``` glsl
#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;

void main(){
    color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz;
}
```
{: .highlightglslfs }

Цей код просто показує текстуру, але додає невеликий зсув, який залежить від часу.

# Результат

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvy.png)

# Йдемо далі

## Використання глибини

В деяких випадках Вам може знадобиться глибина, коли Ви малюєте текстуру. В цьому випадку, просто малюйте в текстуру, яку створіть наступним чином:

``` cpp
glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
```
(24 - це точність в бітах. Ви можете обирати поміж 16, 24 та 32 в залежності від Ваших потреб. 24 зазвичай хороший вибір)

Цього повинно буди достатньо для Вас, що б почати використовувати, але ось Вам код, який це реалізує.

Зауважте, даний код може бути трішки повільний, тому що драйвер може не могти використовувати певні оптимізації, такі як [Hi-Z](http://fr.slideshare.net/pjcozzi/z-buffer-optimizations).

На цьому знімку екрана, рівень глибини штучно "покращено". Зазвичай, це буває дуже складно побачити щоь в текстурі глибин. <<Близька координата Z біля нуля - чорна, дальня координата Z поблизу 1 - біла.>>

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvydepth.png)


## Multisampling

Ви можете записувати в <<мультисемпл>> текстури а не в "базові" - просто потрібно замінити `glTexImage2D` на [glTexImage2DMultisample](http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage2DMultisample.xml) в C++ коді та `sampler2D`/`texture` на `sampler2DMS`/`texelFetch` в фрагментному шейдері.

Та тут є одне застереження - `texelFetch` потребує інший аргумент, який я кількістью <<семплів|зразків>> для отримання. Іншими словами, нема автоматичної "фільтрації" (коректний термін, коли ми говоримо про <<multisampling|мальтисеспл>> є ""роздільна здатність").

Тому, можливо Вам доведеться вирішити це для мультисемпл текстури самостійно в іншу, не мультисемпл текстуру, використовуючи інший шейдер.

Нічого складного, просто трішки громіздко.

## Кілька цілей рендеру

Ви можете записувати декілька текстур одночасно.

Просто створіть декілька текстур (всі з правильними та однаковими розмірами !), викличте `glFramebufferTexture` з різними <<кольоровими вкладеннями>>, викличте `glDrawBuffers` з оновленими параметрами (щось виду `(2,{GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1}})`) і додайте ще одну змінну в Ваш фрагментний шейдер:

``` glsl
layout(location = 1) out vec3 normal_tangentspace; // або що завгодно
```
{: .highlightglslfs }

Підказка 1: якщо Вам потрібно виводити вектор в текстуру, існують текстури з дійсними числами, з 16 чи 32 бітами точності в замін 8... Дивіться за посиланням [glTexImage2D](http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml) (шукайте `GL_FLOAT`).

Підказка 2: для попередньої версії OpenGL використовуйте `glFragData[1] = myvalue`.


# Вправи

* Спробуйте використати `glViewport(0,0,512,768);` замість `glViewport(0,0,1024,768);` (<<спробуйте обидва буфера фрейма та екрана>>)
* Поекспериментуйте з іншими UB координатами в останньому фрагментному шейдері.
* Перетворіть квад використовуючи дійсну матрицю трансформації. Спочатку "захадркодьте", а потом спробуйте використати функції з controls.hpp. Що Ви помітили?

