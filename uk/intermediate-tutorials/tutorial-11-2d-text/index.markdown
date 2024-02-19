---
layout: tutorial
status: publish
published: true
title: 'Tutorial 11 : 2D text'
date: '2011-05-16 22:38:44 +0200'
date_gmt: '2011-05-16 22:38:44 +0200'
categories: [tuto]
order: 510
tags: []
language: uk
---

* TOC
{:toc}

В цьому туторіалі ми вивчимо як намалювати 2D текст поверх Вашого 3D зображення. В нашому випадку це буде звичайний таймер:

![]({{site.baseurl}}/assets/images/tuto-11-2d-text/clock.png)


# API

Зараз ми реалізуємо наступний простий інтерфейс (в common/text2D.h):

``` cpp
void initText2D(const char * texturePath);
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();
```

Щоб даний код працював на 640х480 і на 1080p, `x` та `y` координати повинні бути в діапазоні [0-800][0-600]. Вершинний шейдер прилаштує ще до дійсних розмірів екрану.

Загляньте в common/text2D.cpp для повної реалізації.

# Текстура

initText2D просто читає текстуру і пару шейдерів. Тут нічого цікавого, та поглянемо на цю текстуру:

![]({{site.baseurl}}/assets/images/tuto-11-2d-text/fontalpha.png)

Ця текстура була згенерована за допомогою [CBFG](http://www.codehead.co.uk/cbfg/), одним з багатьох інструментів, що створють текстури з шрифтів. Потім це зображення було завантажено в Paint.NET, де я додав червоне тло (виключно для візуалізації - все що намальовано червоним буде прозорим).

Таким чином, завданням printText2D буде створення чотирикутників з правильними екранними координатами і текстурними координатами.

# Малюємо

Ми маємо заповнити ці буфери:

``` cpp
std::vector<glm::vec2> vertices;
std::vector<glm::vec2> UVs;
```

Для кожного символу ми розраховуємо координати чотирьох вершин що будуть вершинами чотирикутника і додамо два трикутники:

``` cpp
for ( unsigned int i=0 ; i<length ; i++ ){

    glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
    glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
    glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
    glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );

    vertices.push_back(vertex_down_right);
    vertices.push_back(vertex_up_right);
    vertices.push_back(vertex_down_left);
```

Тепер для UV. Верхня ліва координата розраховується наступним чином:

``` cpp
    char character = text[i];
    float uv_x = (character%16)/16.0f;
    float uv_y = (character/16)/16.0f;
```

Це працює ( дивіться нижче ), тому що [ASCII код для A](http://www.asciitable.com/) це 65.

65%16 = 1, отже A в стовбчику №1 (ми рахуємо з 0 !).

65/16 = 4, отже A в рядку №4 ( це цілочисленне ділення, тому це не 4.0625 як зазвичай буває)

Обидва числа поділено на 16.0, що б вписати в діапазон [0.0 - 1.0] - діапазон, який використовують текстури в OpenGL.

І тепер нам потрібно зробити цю саму дуже просту річ для вершин:

``` cpp
    glm::vec2 uv_up_left    = glm::vec2( uv_x           , 1.0f - uv_y );
    glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, 1.0f - uv_y );
    glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, 1.0f - (uv_y + 1.0f/16.0f) );
    glm::vec2 uv_down_left  = glm::vec2( uv_x           , 1.0f - (uv_y + 1.0f/16.0f) );

    UVs.push_back(uv_up_left   );
    UVs.push_back(uv_down_left );
    UVs.push_back(uv_up_right  );

    UVs.push_back(uv_down_right);
    UVs.push_back(uv_up_right);
    UVs.push_back(uv_down_left);
 }
```
І залишилась звичайна робота - прив'язати буфери, заповнити їх, обрати шейдер, прив'язати текстури, дозволити/прив'язати/налаштувати вершинні атрибути, дозволити змішування і викликати `glDrawArrays`. Ура! Ви це зробили.

Важлива річ - координати у нас в діапазоні [0,800][0,600]. Іншими словами, нам не потрібні тут матричні перетворення. Вершинний шейдер просто перетворює цей діапазон в [-1,1][-1,1] за допомогою дуже простої математики (це може бути зроблено і в С++ також)

``` glsl
void main(){

    // вихідні позиції для вершини, в <<clip>> просторі
    // перетворюємо [0..800][0..600] в [-1..1][-1..1]
    vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
    vertexPosition_homoneneousspace /= vec2(400,300);
    gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

    // UV для вершин. ніяких перетворень
    UV = vertexUV;
}
```
{: .highlightglslvs }

Фрагментний шейдер теж робить трішки роботи:

``` glsl
void main(){
    color = texture( myTextureSampler, UV );
}
```
{: .highlightglslfs }

Не використовуйте цей код для чогось серйозного, так як він оперує тільки латинським алфавітом. Або не продавайте свої програми в Індію, Китай, Японію чи Україну (та навіть Німеччину, тому що на малюнку немає символу &szlig;). Ця текстура буде працювати для Франції (тут є символи &eacute;, &agrave;, &ccedil;, та інші), тому що це було згенеровано на моїй локалі.  Також будьте обережними з кодом з інших бібліотек - вони зазвичай використовують OpenGL другої версії, яка не сумісна. На жаль я не знаю жодної гарної бібліотеки, що вміє працювати з UTF-8.



Скоріш за все Вам буде цікаво прочитати [The Absolute Minimum Every Software Developer Absolutely, Positively Must Know About Unicode and Character Sets (No Excuses!)](http://www.joelonsoftware.com/articles/Unicode.html) від Джоела Спольскі.

Також подивіться [цю статтью від Valve](http://www.valvesoftware.com/publications/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf) якщо Вам потрібен великий текст.
