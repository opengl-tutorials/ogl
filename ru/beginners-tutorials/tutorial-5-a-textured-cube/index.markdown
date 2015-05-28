---
layout: page
status: publish
published: true
title: 'Урок 5: Текстурированный куб'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1258
wordpress_url: http://www.opengl-tutorial.org/?page_id=1258
date: '2014-05-01 13:22:53 +0100'
date_gmt: '2014-05-01 13:22:53 +0100'
categories: []
tags: []
comments: []
language: ru
---
<p>Добро пожаловать на наш пятый урок. В этом уроке вы узнаете:</p>
<ul>
<li>Что такое UV-координаты<&#47;li>
<li>Как самостоятельно загружать текстуры<&#47;li>
<li>Как использовать их в OpenGL<&#47;li>
<li>Что такое фильтрация и мип-маппинг и как их использовать<&#47;li>
<li>Как загружать текстуры с помощью GLFW<&#47;li>
<li>Что такое Alpha-канал<&#47;li><br />
<&#47;ul></p>
<h1>UV-координаты<&#47;h1><br />
Когда вы текстурируете какой-то объект, то вам необходимо как-то сообщить OpenGL, какая часть изображения прикрепляется к каждому треугольнику. Именно для этого и используются UV-координаты</p>
<p>Каждая вершина помимо позиции имеет несколько дополнительных полей, а также U и V. Эти координаты используются применительно к текстуре, как показано на рисунке:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;UVintro.png"><img title="UVintro" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;UVintro.png" width="662" height="337" &#47;><&#47;a></p>
<p>Обратите внимание, как текстура искажается на треугольнике.</p>
<h1>Загрузка Bitmap-изображений<&#47;h1><br />
Знание формата файлов BMP не является критичным, так как многие библиотеки могут сделать загрузку за вас. Однако, чтобы лучше понимать то, что происходит в таких библиотеках мы разберем ручную загрузку.</p>
<p>Объявляем функцию для загрузки изображений:</p>
<pre>GLuint loadBMP_custom(const char * imagepath);<&#47;pre><br />
Вызываться она будет так:</p>
<pre>GLuint image = loadBMP_custom(".&#47;my_texture.bmp");<&#47;pre><br />
Теперь перейдем непосредственно к чтению файла.</p>
<p>Для начала, нам необходимы некоторые данные. Эти переменные будут установлены когда мы будем читать файл:</p>
<pre>&#47;&#47; Данные, прочитанные из заголовка BMP-файла<br />
unsigned char header[54]; &#47;&#47; Каждый BMP-файл начинается с заголовка, длиной в 54 байта<br />
unsigned int dataPos;     &#47;&#47; Смещение данных в файле (позиция данных)<br />
unsigned int width, height;<br />
unsigned int imageSize;   &#47;&#47; Размер изображения = Ширина * Высота * 3<br />
&#47;&#47; RGB-данные, полученные из файла<br />
unsigned char * data;<&#47;pre><br />
Открываем файл:</p>
<pre>FILE * file = fopen(imagepath,"rb");<br />
if (!file) {<br />
  printf("Изображение не может быть открытоn");<br />
  return 0;<br />
}<&#47;pre><br />
Первым, в BMP-файлах идет заголовок, размером в 54 байта. Он содержит информацию о том, что файл действительно является файлом BMP, размер изображение, количество бит на пиксель и т. п., поэтому читаем его:</p>
<pre>if ( fread(header, 1, 54, file) != 54 ) { &#47;&#47; Если мы прочитали меньше 54 байт, значит возникла проблема<br />
    printf("Некорректный BMP-файлn");<br />
    return false;<br />
}<&#47;pre><br />
Заголовок всегда начинается с букв BM. Вы можете открыть файл в HEX-редакторе и убедиться в этом самостоятельно, а можете посмотреть на наш скриншот:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;hexbmp.png"><img title="hexbmp" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;hexbmp.png" width="541" height="128" &#47;><&#47;a></p>
<p>Итак, мы проверяем первые два байта и если они не являются буквами "BM", то файл не является BMP-файлом или испорчен:</p>
<pre>if ( header[0]!='B' || header[1]!='M' ){<br />
    printf("Некорректный BMP-файлn");<br />
    return 0;<br />
}<&#47;pre><br />
Теперь мы читаем размер изображения, смещение данных изображения в файле и т. п.:</p>
<pre>&#47;&#47; Читаем необходимые данные<br />
dataPos    = *(int*)&amp;(header[0x0A]); &#47;&#47; Смещение данных изображения в файле<br />
imageSize  = *(int*)&amp;(header[0x22]); &#47;&#47; Размер изображения в байтах<br />
width      = *(int*)&amp;(header[0x12]); &#47;&#47; Ширина<br />
height     = *(int*)&amp;(header[0x16]); &#47;&#47; Высота<&#47;pre><br />
Проверим и исправим полученные значения:</p>
<pre>&#47;&#47; Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их<br />
if (imageSize==0)    imageSize=width*height*3; &#47;&#47; Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)<br />
if (dataPos==0)      dataPos=54; &#47;&#47; В таком случае, данные будут следовать сразу за заголовком<&#47;pre><br />
Теперь, так как мы знаем размер изображения, то можем выделить область памяти, в которую поместим данные:</p>
<pre>&#47;&#47; Создаем буфер<br />
data = new unsigned char [imageSize];</p>
<p>&#47;&#47; Считываем данные из файла в буфер<br />
fread(data,1,imageSize,file);</p>
<p>&#47;&#47; Закрываем файл, так как больше он нам не нужен<br />
fclose(file);<&#47;pre><br />
<em>Примечание переводчика: <&#47;em></p>
<blockquote><p>Следует отметить, что приведенный код может быть использован только для загрузки 24-битных изображений (т. е. где на каждый пиксель изображения отводится 3 байта). С другими форматами BMP-файла вам следует познакомиться самостоятельно.<&#47;blockquote><br />
Мы вплотную подошли к части, касающейся OpenGL. Создание текстур очень похоже на создание вершинных буферов:</p>
<ul>
<li>Создайте текстуру<&#47;li>
<li>Привяжите ее<&#47;li>
<li>Заполните<&#47;li>
<li>Сконфигурируйте<&#47;li><br />
<&#47;ul><br />
GL_RGB в glTextImage2D указывает на то, что мы работает с 3х компонентным цветом. А GL_BGR указывает на то, как данные представлены в памяти. На самом деле в BMP-файлах цветовые данные хранятся не в RGB, а в BGR (если быть точным, то это связано с тем, как хранятся числа в памяти), поэтому необходимо сообщить об этом OpenGL:</p>
<pre>&#47;&#47; Создадим одну текстуру OpenGL<br />
GLuint textureID;<br />
glGenTextures(1, &amp;textureID);</p>
<p>&#47;&#47; Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой<br />
glBindTexture(GL_TEXTURE_2D, textureID);</p>
<p>&#47;&#47; Передадим изображение OpenGL<br />
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);</p>
<p>glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);<&#47;pre><br />
Последние две строки мы поясним позднее, а пока в части C++ мы должны использовать нашу функцию для загрузки текстуры:</p>
<pre>GLuint Texture = loadBMP_custom("uvtemplate.bmp");<&#47;pre><br />
<strong>Очень важное замечание: <&#47;strong>используйте текстуры с шириной и высотой степени двойки! То есть:</p>
<ul>
<li>Хорошие: 128*128*, 256*256, 1024*1024, 2*2&hellip;<&#47;li>
<li>Плохие: 127*128, 3*5, &hellip;<&#47;li>
<li>Приемлемые: 128*256<&#47;li><br />
<&#47;ul></p>
<h1>Использование текстуры в OpenGL<&#47;h1><br />
Что же, давайте посмотрим на наш Фрагментный шейдер:</p>
<pre>#version 330 core</p>
<p>&#47;&#47; Интерполированные значения из вершинного шейдера<br />
in vec2 UV;</p>
<p>&#47;&#47; Выходные данные<br />
out vec3 color;</p>
<p>&#47;&#47; Значения, которые остаются неизменными для объекта.<br />
uniform sampler2D myTextureSampler;</p>
<p>void main(){</p>
<p>    &#47;&#47; Выходной цвет = цвету текстуры в указанных UV-координатах<br />
    color = texture( myTextureSampler, UV ).rgb;<br />
}<&#47;pre><br />
Три замечания:</p>
<ul>
<li>Фрагментному шейдеру требуются UV-координаты. Это понятно.<&#47;li>
<li>Также, ему необходим "sampler2D", чтобы знать, с какой текстурой работать (вы можете получить доступ к нескольким текстурам в одном шейдере т. н. мультитекстурирование)<&#47;li>
<li>И наконец, доступ к текстуре завершается вызовом texture(), который возвращает vec4 (R, G, B, A). A-компоненту мы разберем немного позднее.<&#47;li><br />
<&#47;ul><br />
Вершинный шейдер также прост. Все, что мы делаем - это передаем полученные UV-координаты в фрагментный шейдер:</p>
<pre>#version 330 core</p>
<p>&#47;&#47; Входные данные вершин, различные для всех запусков этого шейдера<br />
layout(location = 0) in vec3 vertexPosition_modelspace;<br />
layout(location = 1) in vec2 vertexUV;</p>
<p>&#47;&#47; Выходные данные, которые будут интерполированы для каждого фрагмента<br />
out vec2 UV;</p>
<p>&#47;&#47; Значения, которые останутся неизменными для всего объекта<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>    &#47;&#47; Выходная позиция вершины<br />
    gl_Position =&nbsp; MVP * vec4(vertexPosition_modelspace,1);</p>
<p>    &#47;&#47; UV-координаты вершины.<br />
    UV = vertexUV;<br />
}<&#47;pre><br />
Помните "layout(location = 1) in vec3 vertexColor" из Урока 4? Здесь мы делаем абсолютно тоже самое, только вместо передачи буфера с цветом каждой вершины мы будем передавать буфер с UV-координатами каждой вершины:</p>
<pre>&#47;&#47; Две UV-координаты для каждой вершины. Они были созданы с помощью Blender. Мы коротко расскажем о том, как сделать это самостоятельно.<br />
static const GLfloat g_uv_buffer_data[] = {<br />
    0.000059f, 1.0f-0.000004f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    1.000023f, 1.0f-0.000013f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.999958f, 1.0f-0.336064f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.667969f, 1.0f-0.671889f,<br />
    1.000023f, 1.0f-0.000013f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.000059f, 1.0f-0.000004f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.336098f, 1.0f-0.000071f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    1.000004f, 1.0f-0.671847f,<br />
    0.999958f, 1.0f-0.336064f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.336098f, 1.0f-0.000071f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.000004f, 1.0f-0.671870f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.667969f, 1.0f-0.671889f,<br />
    1.000004f, 1.0f-0.671847f,<br />
    0.667979f, 1.0f-0.335851f<br />
};<&#47;pre><br />
Указанные UV-координаты относятся к такой модели:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;uv_mapping_blender.png"><img title="uv_mapping_blender" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;uv_mapping_blender-300x222.png" width="300" height="222" &#47;><&#47;a></p>
<p>Остальное очевидно. Мы создаем буфер, привязываем его, заполняем, настраиваем и выводим Буфер Вершин как обычно. Только будьте осторожны, так как в glVertexAttribPointer для буфера текстурных координат второй параметр (размер) будет не 3, а 2.</p>
<p>И вот такой результат мы получим:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering.png"><img title="nearfiltering" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering.png" width="533" height="557" &#47;><&#47;a></p>
<p>в увеличенном варианте:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering_zoom.png"><img title="nearfiltering_zoom" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering_zoom.png" width="348" height="340" &#47;><&#47;a></p>
<h1>Фильтрация и мип-маппинг.<&#47;h1><br />
Как вы можете видеть на скриншоте выше, качество текстуры не очень хорошее. Это потому, что в нашей процедуре загрузки BMP-изображения (loadBMP_custom) мы указали:</p>
<pre>glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);<&#47;pre><br />
Это означает, что в нашем фрагментном шейдере, texture() возвращает строго тексель, который находится по указанным текстурным координатам:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearest.png"><img title="nearest" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearest.png" width="440" height="240" &#47;><&#47;a></p>
<p>Есть несколько решений, которые позволят улучшить ситуацию.</p>
<h2>Линейная фильтрация<&#47;h2><br />
При помощи линейной фильтрации texture() будет смешивать цвета находящихся рядом текселей в зависимости от дистанции до их центра, что позволит предотвратить резкие границы, которые вы видели выше:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;linear1.png"><img title="linear" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;linear1.png" width="440" height="240" &#47;><&#47;a></p>
<p>Это будет выглядить значительно лучше и используется часто, но если вы хотите очень высокого качества, то вам понадобится анизотропная фильтрация, которая работает несколько медленнее.</p>
<h2>Анизотропная фильтрация<&#47;h2><br />
Аппроксимирует часть изображения, которая действительно видна через фрагмент. К примеру, если указанная текстура просматривается сбоку и немного повернута, то анизотропная фильтрация будет вычислять цвет, который находится в синем прямоугольнике, с помощью&nbsp; фиксированного количество сэмплов (Уровень анизотропии) вдоль его направления:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;aniso.png"><img title="aniso" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;aniso.png" width="440" height="240" &#47;><&#47;a></p>
<h2>Мип-маппинг<&#47;h2><br />
И линейная, и анизотропная фильтрация имеют недостаток. Если текстура просматривается с большого расстояния, то смешивать 4 текселя будет недостаточно. То есть, если ваша 3D модель находится так далеко, что занимает на экране всего 1 фрагмент, то фильный цвет фрагмента будет являться средним всех текселей текстуры. Естественно, это не реализовано из-за соображений производительности. Для этой цели существует так называемый мип-маппинг:</p>
<p><a href="http:&#47;&#47;en.wikipedia.org&#47;wiki&#47;File:MipMap_Example_STS101.jpg"><img title="An original image and its mipmaps. Image by Tokigun under Creative Commons" alt="" src="http:&#47;&#47;upload.wikimedia.org&#47;wikipedia&#47;commons&#47;5&#47;5c&#47;MipMap_Example_STS101.jpg" width="384" height="256" &#47;><&#47;a></p>
<ul>
<li>При инициализации вы уменьшаете масштаб текстуры до тех пор, пока не получите изображение 1х1 (которое по сути будет являться средним значением всех текселей текстуры)<&#47;li>
<li>Когда вы выводите объект, то вы выбираете тот мип-мап, который наиболее приемлем в данной ситуации.<&#47;li>
<li>Вы применяете к этому мип-мапу фильтрацию<&#47;li>
<li>А для большего качества вы можете использовать 2 мип-мапа и смешать результат.<&#47;li><br />
<&#47;ul><br />
К счастью для нас, все это делается очень просто с помощью OpenGL:</p>
<pre>&#47;&#47; Когда изображение увеличивается, то мы используем обычную линейную фильтрацию<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);<br />
&#47;&#47; Когда изображение уменьшается, то мы используем линейной смешивание 2х мипмапов, к которым также применяется линейная фильтрация<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);<br />
&#47;&#47; И генерируем мипмап<br />
glGenerateMipmap(GL_TEXTURE_2D);<&#47;pre></p>
<h1>Загрузка текстур с помощью GLFW<&#47;h1><br />
Наша процедура loadBMP_custom великолепна, так как мы сделали ее сами, но использование специальных библиотек может быть предпочтительнее (в конечном итоге мы в своей процедуре многое не учли). GLFW может сделать это лучше (но только для TGA-файлов):</p>
<pre>GLuint loadTGA_glfw(const char * imagepath){</p>
<p>    &#47;&#47; Создаем одну OpenGL текстуру<br />
    GLuint textureID;<br />
    glGenTextures(1, &amp;textureID);</p>
<p>    &#47;&#47; "Привязываем" только что созданную текстуру и таким образом все последующие операции будут производиться с ней<br />
    glBindTexture(GL_TEXTURE_2D, textureID);</p>
<p>    &#47;&#47; Читаем файл и вызываем glTexImage2D с необходимыми параметрами<br />
    glfwLoadTexture2D(imagepath, 0);</p>
<p>    &#47;&#47; Трилинейная фильтрация.<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);<br />
    glGenerateMipmap(GL_TEXTURE_2D);</p>
<p>    &#47;&#47; Возвращаем идентификатор текстуры который мы создали<br />
    return textureID;<br />
}<&#47;pre></p>
<h1>Сжатые текстуры<&#47;h1><br />
На этом шаге вы наверное хотите узнать, как же все-таки загружать JPEG файлы вместо TGA?</p>
<p>Короткий ответ: даже не думайте об этом. Есть идея получше.</p>
<h2>Создание сжатых текстур<&#47;h2></p>
<ul>
<li>Скачайте <a href="http:&#47;&#47;developer.amd.com&#47;Resources&#47;archive&#47;ArchivedTools&#47;gpu&#47;compressonator&#47;Pages&#47;default.aspx">The Compressonator<&#47;a>, утилита от ATI<&#47;li>
<li>Загрузите в нее текстуру, размер которой является степенью двойки<&#47;li>
<li>Сожмите ее в DXT1, DXT3 или в DXT5 (о разнице между форматами можете почитать на <a href="http:&#47;&#47;en.wikipedia.org&#47;wiki&#47;S3_Texture_Compression">Wikipedia<&#47;a>)<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;TheCompressonator.png"><img title="TheCompressonator" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;TheCompressonator.png" width="806" height="688" &#47;><&#47;a></p>
<ul>
<li>Создайте мипмапы, чтобы не создавать их во время выполнения программы.<&#47;li>
<li>Экспортируйте это как .DDS файл<&#47;li><br />
<&#47;ul><br />
После этих шагов вы имеете сжатое изображение, которое прямо совместимо с GPU. И когда вы вызовите texture() в шейдере, то текстура будет распакована на лету. Это может показаться более медленным, однако это требует гораздо меньше памяти, а значит пересылаемых данных будет меньше. Пересылка данных всегда будет дорогой операцией, в то время как декомпрессия является практически бесплатной. Как правило, использование сжатия текстур повышает быстродействие на 20%.</p>
<h2>Использование сжатой текстуры<&#47;h2><br />
Теперь перейдем непосредственно к загрузке нашей сжатой текстуры. Процедура будет очень похожа на загрузку BMP, с тем исключением, что заголовок файла будет организован немного иначе:</p>
<pre>GLuint loadDDS(const char * imagepath){</p>
<p>&nbsp;&nbsp;&nbsp; unsigned char header[124];</p>
<p>&nbsp;&nbsp;&nbsp; FILE *fp;</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* пробуем открыть файл *&#47;<br />
&nbsp;&nbsp;&nbsp; fp = fopen(imagepath, "rb");<br />
&nbsp;&nbsp;&nbsp; if (fp == NULL)<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; return 0;</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* проверим тип файла *&#47;<br />
&nbsp;&nbsp;&nbsp; char filecode[4];<br />
&nbsp;&nbsp;&nbsp; fread(filecode, 1, 4, fp);<br />
&nbsp;&nbsp;&nbsp; if (strncmp(filecode, "DDS ", 4) != 0) {<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; fclose(fp);<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; return 0;<br />
&nbsp;&nbsp;&nbsp; }</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* читаем заголовок *&#47;<br />
&nbsp;&nbsp;&nbsp; fread(&amp;header, 124, 1, fp); </p>
<p>&nbsp;&nbsp;&nbsp; unsigned int height&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = *(unsigned int*)&amp;(header[8 ]);<br />
&nbsp;&nbsp;&nbsp; unsigned int width&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; = *(unsigned int*)&amp;(header[12]);<br />
&nbsp;&nbsp;&nbsp; unsigned int linearSize&nbsp;&nbsp;&nbsp; &nbsp;= *(unsigned int*)&amp;(header[16]);<br />
&nbsp;&nbsp;&nbsp; unsigned int mipMapCount = *(unsigned int*)&amp;(header[24]);<br />
&nbsp;&nbsp;&nbsp; unsigned int fourCC&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = *(unsigned int*)&amp;(header[80]);<&#47;pre><br />
После заголовку идут данные, в которые входят все уровни мип-мап. К слову, мы можем прочитать их все сразу:</p>
<pre>&nbsp;&nbsp;&nbsp; unsigned char * buffer;<br />
&nbsp;&nbsp;&nbsp; unsigned int bufsize;<br />
&nbsp;&nbsp;&nbsp; &#47;* вычисляем размер буфера *&#47;<br />
&nbsp;&nbsp;&nbsp; bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;<br />
&nbsp;&nbsp;&nbsp; buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));<br />
&nbsp;&nbsp;&nbsp; fread(buffer, 1, bufsize, fp);<br />
&nbsp;&nbsp;&nbsp; &#47;* закрываем файл *&#47;<br />
&nbsp;&nbsp;&nbsp; fclose(fp);<&#47;pre><br />
Сделано. Так как мы можем использовать 3 разных формата (DXT1, DXT3, DXT5), то необходимо в зависимости от флага "fourCC", сказать OpenGL о формате данных.</p>
<pre>&nbsp;&nbsp;&nbsp; unsigned int components&nbsp; = (fourCC == FOURCC_DXT1) ? 3 : 4;<br />
&nbsp;&nbsp;&nbsp; unsigned int format;<br />
&nbsp;&nbsp;&nbsp; switch(fourCC)<br />
&nbsp;&nbsp;&nbsp; {<br />
&nbsp;&nbsp;&nbsp; case FOURCC_DXT1:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; break;<br />
&nbsp;&nbsp;&nbsp; case FOURCC_DXT3:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; break;<br />
&nbsp;&nbsp;&nbsp; case FOURCC_DXT5:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; break;<br />
&nbsp;&nbsp;&nbsp; default:<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; free(buffer);<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; return 0;<br />
&nbsp;&nbsp;&nbsp; }<&#47;pre><br />
Создание текстуры выполняется как обычно:</p>
<pre>&nbsp;&nbsp;&nbsp; &#47;&#47; Создаем одну OpenGL текстуру<br />
&nbsp;&nbsp;&nbsp; GLuint textureID;<br />
&nbsp;&nbsp;&nbsp; glGenTextures(1, &amp;textureID);</p>
<p>&nbsp;&nbsp;&nbsp; &#47;&#47; "Привязываем" текстуру.<br />
&nbsp;&nbsp;&nbsp; glBindTexture(GL_TEXTURE_2D, textureID);<&#47;pre><br />
Следующим шагом мы загружаем мип-мапы:</p>
<pre>&nbsp;&nbsp;&nbsp; unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;<br />
&nbsp;&nbsp;&nbsp; unsigned int offset = 0;</p>
<p>&nbsp;&nbsp;&nbsp; &#47;* загрузка мип-мапов *&#47;<br />
&nbsp;&nbsp;&nbsp; for (unsigned int level = 0; level < mipMapCount &amp;&amp; (width || height); ++level)<br />
&nbsp;&nbsp;&nbsp; {<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; unsigned int size = ((width+3)&#47;4)*((height+3)&#47;4)*blockSize;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,&nbsp;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; 0, size, buffer + offset);</p>
<p>&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; offset += size;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; width&nbsp; &#47;= 2;<br />
&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; height &#47;= 2;<br />
&nbsp;&nbsp;&nbsp; }<br />
&nbsp;&nbsp;&nbsp; free(buffer); </p>
<p>&nbsp;&nbsp;&nbsp; return textureID;<&#47;pre></p>
<h2>Инверсия V-координаты<&#47;h2><br />
DXT компрессия пришла к нам из DirectX, где координатная текстура V является инвертированной по сравнению с OpenGL. Поэтому, если вы используете сжатые текстуры, то вам необходимо использовать (coord.u, 1.0 - coord.v), чтобы исправить тексель. Вы можете выполнять это как при экспорте текстуры, так и в загрузчике или в шейдере.</p>
<h1>Заключение<&#47;h1><br />
В данном уроке вы узнали как создавать, загружать и использовать текстуры в OpenGL.</p>
<p>Стоит отметить, что в своих проектах мы настоятельно рекомендуем вам использовать только сжатые текстуры, так как они занимают меньше места, быстрее загружаются и используются. Для этих целей можете также использовать The Compressonator.</p>
<h1>Упражнения<&#47;h1></p>
<ul>
<li>В исходный код к урокам включен загрузчик DDS, но без исправления текстурных координат. Модифицируйте код так, чтобы корректно выводить куб.<&#47;li>
<li>Поэкспериментируйте с разными DDS форматами. Дают ли они разный результат или разную степень сжатия?<&#47;li>
<li>Попробуйте не создавать мип-мапы в The Compressonator. Каков результат? Создайте 3 пути решения этих проблем.<&#47;li><br />
<&#47;ul></p>
<h1>Полезные ссылки<&#47;h1></p>
<ul>
<li><a href="http:&#47;&#47;www.oldunreal.com&#47;editing&#47;s3tc&#47;ARB_texture_compression.pdf">Using texture compression in OpenGL<&#47;a> , S&eacute;bastien Domine, NVIDIA<&#47;li><br />
<&#47;ul></p>
