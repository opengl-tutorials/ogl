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

Добро пожаловать на наш пятый урок. В этом уроке вы узнаете:

* Что такое UV-координаты
* Как самостоятельно загружать текстуры
* Как использовать их в OpenGL
* Что такое фильтрация и мип-маппинг и как их использовать
* Как загружать текстуры с помощью GLFW
* Что такое Alpha-канал


#UV-координаты

Когда вы текстурируете какой-то объект, то вам необходимо как-то сообщить OpenGL, какая часть изображения прикрепляется к каждому треугольнику. Именно для этого и используются UV-координаты

Каждая вершина помимо позиции имеет несколько дополнительных полей, а также U и V. Эти координаты используются применительно к текстуре, как показано на рисунке:

[<img title="UVintro" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/UVintro.png" width="662" height="337" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/UVintro.png)

Обратите внимание, как текстура искажается на треугольнике.

#Загрузка Bitmap-изображений

Знание формата файлов BMP не является критичным, так как многие библиотеки могут сделать загрузку за вас. Однако, чтобы лучше понимать то, что происходит в таких библиотеках мы разберем ручную загрузку.

Объявляем функцию для загрузки изображений:
{% highlight text linenos %}
GLuint loadBMP_custom(const char * imagepath);
{% endhighlight %}
Вызываться она будет так:
{% highlight text linenos %}
GLuint image = loadBMP_custom("./my_texture.bmp");
{% endhighlight %}
Теперь перейдем непосредственно к чтению файла.

Для начала, нам необходимы некоторые данные. Эти переменные будут установлены когда мы будем читать файл:
{% highlight text linenos %}
// Данные, прочитанные из заголовка BMP-файла
unsigned char header[54]; // Каждый BMP-файл начинается с заголовка, длиной в 54 байта
unsigned int dataPos;     // Смещение данных в файле (позиция данных)
unsigned int width, height;
unsigned int imageSize;   // Размер изображения = Ширина * Высота * 3
// RGB-данные, полученные из файла
unsigned char * data;
{% endhighlight %}
Открываем файл:
{% highlight text linenos %}
FILE * file = fopen(imagepath,"rb");
if (!file) {
  printf("Изображение не может быть открытоn");
  return 0;
}
{% endhighlight %}
Первым, в BMP-файлах идет заголовок, размером в 54 байта. Он содержит информацию о том, что файл действительно является файлом BMP, размер изображение, количество бит на пиксель и т. п., поэтому читаем его:
{% highlight text linenos %}
if ( fread(header, 1, 54, file) != 54 ) { // Если мы прочитали меньше 54 байт, значит возникла проблема
    printf("Некорректный BMP-файлn");
    return false;
}
{% endhighlight %}
Заголовок всегда начинается с букв BM. Вы можете открыть файл в HEX-редакторе и убедиться в этом самостоятельно, а можете посмотреть на наш скриншот:

[<img title="hexbmp" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/hexbmp.png" width="541" height="128" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/hexbmp.png)

Итак, мы проверяем первые два байта и если они не являются буквами "BM", то файл не является BMP-файлом или испорчен:
{% highlight text linenos %}
if ( header[0]!='B' || header[1]!='M' ){
    printf("Некорректный BMP-файлn");
    return 0;
}
{% endhighlight %}
Теперь мы читаем размер изображения, смещение данных изображения в файле и т. п.:
{% highlight text linenos %}
// Читаем необходимые данные
dataPos    = *(int*)&(header[0x0A]); // Смещение данных изображения в файле
imageSize  = *(int*)&(header[0x22]); // Размер изображения в байтах
width      = *(int*)&(header[0x12]); // Ширина
height     = *(int*)&(header[0x16]); // Высота
{% endhighlight %}
Проверим и исправим полученные значения:
{% highlight text linenos %}
// Некоторые BMP-файлы имеют нулевые поля imageSize и dataPos, поэтому исправим их
if (imageSize==0)    imageSize=width*height*3; // Ширину * Высоту * 3, где 3 - 3 компоненты цвета (RGB)
if (dataPos==0)      dataPos=54; // В таком случае, данные будут следовать сразу за заголовком
{% endhighlight %}
Теперь, так как мы знаем размер изображения, то можем выделить область памяти, в которую поместим данные:
{% highlight text linenos %}
// Создаем буфер
data = new unsigned char [imageSize];

// Считываем данные из файла в буфер
fread(data,1,imageSize,file);

// Закрываем файл, так как больше он нам не нужен
fclose(file);
{% endhighlight %}
*Примечание переводчика: *
<blockquote>
Следует отметить, что приведенный код может быть использован только для загрузки 24-битных изображений (т. е. где на каждый пиксель изображения отводится 3 байта). С другими форматами BMP-файла вам следует познакомиться самостоятельно.</blockquote>
Мы вплотную подошли к части, касающейся OpenGL. Создание текстур очень похоже на создание вершинных буферов:

* Создайте текстуру
* Привяжите ее
* Заполните
* Сконфигурируйте

GL_RGB в glTextImage2D указывает на то, что мы работает с 3х компонентным цветом. А GL_BGR указывает на то, как данные представлены в памяти. На самом деле в BMP-файлах цветовые данные хранятся не в RGB, а в BGR (если быть точным, то это связано с тем, как хранятся числа в памяти), поэтому необходимо сообщить об этом OpenGL:
{% highlight text linenos %}
// Создадим одну текстуру OpenGL
GLuint textureID;
glGenTextures(1, &textureID);

// Сделаем созданную текстуру текущий, таким образом все следующие функции будут работать именно с этой текстурой
glBindTexture(GL_TEXTURE_2D, textureID);

// Передадим изображение OpenGL
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
{% endhighlight %}
Последние две строки мы поясним позднее, а пока в части C++ мы должны использовать нашу функцию для загрузки текстуры:
{% highlight text linenos %}
GLuint Texture = loadBMP_custom("uvtemplate.bmp");
{% endhighlight %}
**Очень важное замечание: **используйте текстуры с шириной и высотой степени двойки! То есть:

* Хорошие: 128*128*, 256*256, 1024*1024, 2*2...
* Плохие: 127*128, 3*5, ...
* Приемлемые: 128*256


#Использование текстуры в OpenGL

Что же, давайте посмотрим на наш Фрагментный шейдер:
{% highlight text linenos %}
#version 330 core

// Интерполированные значения из вершинного шейдера
in vec2 UV;

// Выходные данные
out vec3 color;

// Значения, которые остаются неизменными для объекта.
uniform sampler2D myTextureSampler;

void main(){

    // Выходной цвет = цвету текстуры в указанных UV-координатах
    color = texture( myTextureSampler, UV ).rgb;
}
{% endhighlight %}
Три замечания:

* Фрагментному шейдеру требуются UV-координаты. Это понятно.
* Также, ему необходим "sampler2D", чтобы знать, с какой текстурой работать (вы можете получить доступ к нескольким текстурам в одном шейдере т. н. мультитекстурирование)
* И наконец, доступ к текстуре завершается вызовом texture(), который возвращает vec4 (R, G, B, A). A-компоненту мы разберем немного позднее.

Вершинный шейдер также прост. Все, что мы делаем - это передаем полученные UV-координаты в фрагментный шейдер:
{% highlight text linenos %}
#version 330 core

// Входные данные вершин, различные для всех запусков этого шейдера
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Выходные данные, которые будут интерполированы для каждого фрагмента
out vec2 UV;

// Значения, которые останутся неизменными для всего объекта
uniform mat4 MVP;

void main(){

    // Выходная позиция вершины
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

    // UV-координаты вершины.
    UV = vertexUV;
}
{% endhighlight %}
Помните "layout(location = 1) in vec3 vertexColor" из Урока 4? Здесь мы делаем абсолютно тоже самое, только вместо передачи буфера с цветом каждой вершины мы будем передавать буфер с UV-координатами каждой вершины:
{% highlight text linenos %}
// Две UV-координаты для каждой вершины. Они были созданы с помощью Blender. Мы коротко расскажем о том, как сделать это самостоятельно.
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
{% endhighlight %}
Указанные UV-координаты относятся к такой модели:

[<img title="uv_mapping_blender" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/uv_mapping_blender-300x222.png" width="300" height="222" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/uv_mapping_blender.png)

Остальное очевидно. Мы создаем буфер, привязываем его, заполняем, настраиваем и выводим Буфер Вершин как обычно. Только будьте осторожны, так как в glVertexAttribPointer для буфера текстурных координат второй параметр (размер) будет не 3, а 2.

И вот такой результат мы получим:

[<img title="nearfiltering" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nearfiltering.png" width="533" height="557" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering.png)

в увеличенном варианте:

[<img title="nearfiltering_zoom" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nearfiltering_zoom.png" width="348" height="340" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering_zoom.png)

#Фильтрация и мип-маппинг.

Как вы можете видеть на скриншоте выше, качество текстуры не очень хорошее. Это потому, что в нашей процедуре загрузки BMP-изображения (loadBMP_custom) мы указали:
{% highlight text linenos %}
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
{% endhighlight %}
Это означает, что в нашем фрагментном шейдере, texture() возвращает строго тексель, который находится по указанным текстурным координатам:

[<img title="nearest" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/nearest.png" width="440" height="240" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearest.png)

Есть несколько решений, которые позволят улучшить ситуацию.

##Линейная фильтрация

При помощи линейной фильтрации texture() будет смешивать цвета находящихся рядом текселей в зависимости от дистанции до их центра, что позволит предотвратить резкие границы, которые вы видели выше:

[<img title="linear" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/linear1.png" width="440" height="240" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/linear1.png)

Это будет выглядить значительно лучше и используется часто, но если вы хотите очень высокого качества, то вам понадобится анизотропная фильтрация, которая работает несколько медленнее.

##Анизотропная фильтрация

Аппроксимирует часть изображения, которая действительно видна через фрагмент. К примеру, если указанная текстура просматривается сбоку и немного повернута, то анизотропная фильтрация будет вычислять цвет, который находится в синем прямоугольнике, с помощью  фиксированного количество сэмплов (Уровень анизотропии) вдоль его направления:

[<img title="aniso" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/aniso.png" width="440" height="240" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/aniso.png)

##Мип-маппинг

И линейная, и анизотропная фильтрация имеют недостаток. Если текстура просматривается с большого расстояния, то смешивать 4 текселя будет недостаточно. То есть, если ваша 3D модель находится так далеко, что занимает на экране всего 1 фрагмент, то фильный цвет фрагмента будет являться средним всех текселей текстуры. Естественно, это не реализовано из-за соображений производительности. Для этой цели существует так называемый мип-маппинг:

[<img title="An original image and its mipmaps. Image by Tokigun under Creative Commons" alt="" src="http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg" width="384" height="256" />](http://en.wikipedia.org/wiki/File:MipMap_Example_STS101.jpg)

* При инициализации вы уменьшаете масштаб текстуры до тех пор, пока не получите изображение 1х1 (которое по сути будет являться средним значением всех текселей текстуры)
* Когда вы выводите объект, то вы выбираете тот мип-мап, который наиболее приемлем в данной ситуации.
* Вы применяете к этому мип-мапу фильтрацию
* А для большего качества вы можете использовать 2 мип-мапа и смешать результат.

К счастью для нас, все это делается очень просто с помощью OpenGL:
{% highlight text linenos %}
// Когда изображение увеличивается, то мы используем обычную линейную фильтрацию
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// Когда изображение уменьшается, то мы используем линейной смешивание 2х мипмапов, к которым также применяется линейная фильтрация
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// И генерируем мипмап
glGenerateMipmap(GL_TEXTURE_2D);
{% endhighlight %}

#Загрузка текстур с помощью GLFW

Наша процедура loadBMP_custom великолепна, так как мы сделали ее сами, но использование специальных библиотек может быть предпочтительнее (в конечном итоге мы в своей процедуре многое не учли). GLFW может сделать это лучше (но только для TGA-файлов):
{% highlight text linenos %}
GLuint loadTGA_glfw(const char * imagepath){

    // Создаем одну OpenGL текстуру
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Привязываем" только что созданную текстуру и таким образом все последующие операции будут производиться с ней
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Читаем файл и вызываем glTexImage2D с необходимыми параметрами
    glfwLoadTexture2D(imagepath, 0);

    // Трилинейная фильтрация.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Возвращаем идентификатор текстуры который мы создали
    return textureID;
}
{% endhighlight %}

#Сжатые текстуры

На этом шаге вы наверное хотите узнать, как же все-таки загружать JPEG файлы вместо TGA?

Короткий ответ: даже не думайте об этом. Есть идея получше.

##Создание сжатых текстур


* Скачайте [The Compressonator](http://developer.amd.com/Resources/archive/ArchivedTools/gpu/compressonator/Pages/default.aspx), утилита от ATI
* Загрузите в нее текстуру, размер которой является степенью двойки
* Сожмите ее в DXT1, DXT3 или в DXT5 (о разнице между форматами можете почитать на [Wikipedia](http://en.wikipedia.org/wiki/S3_Texture_Compression))

[<img title="TheCompressonator" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/TheCompressonator.png" width="806" height="688" />]({{site.baseurl}}/assets/images/tuto-5-textured-cube/TheCompressonator.png)

* Создайте мипмапы, чтобы не создавать их во время выполнения программы.
* Экспортируйте это как .DDS файл

После этих шагов вы имеете сжатое изображение, которое прямо совместимо с GPU. И когда вы вызовите texture() в шейдере, то текстура будет распакована на лету. Это может показаться более медленным, однако это требует гораздо меньше памяти, а значит пересылаемых данных будет меньше. Пересылка данных всегда будет дорогой операцией, в то время как декомпрессия является практически бесплатной. Как правило, использование сжатия текстур повышает быстродействие на 20%.

##Использование сжатой текстуры

Теперь перейдем непосредственно к загрузке нашей сжатой текстуры. Процедура будет очень похожа на загрузку BMP, с тем исключением, что заголовок файла будет организован немного иначе:
{% highlight text linenos %}
GLuint loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* пробуем открыть файл */
    fp = fopen(imagepath, "rb");
    if (fp == NULL)
        return 0;

    /* проверим тип файла */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* читаем заголовок */
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
{% endhighlight %}
После заголовку идут данные, в которые входят все уровни мип-мап. К слову, мы можем прочитать их все сразу:
{% highlight text linenos %}
    unsigned char * buffer;
    unsigned int bufsize;
    /* вычисляем размер буфера */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* закрываем файл */
    fclose(fp);
{% endhighlight %}
Сделано. Так как мы можем использовать 3 разных формата (DXT1, DXT3, DXT5), то необходимо в зависимости от флага "fourCC", сказать OpenGL о формате данных.
{% highlight text linenos %}
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
{% endhighlight %}
Создание текстуры выполняется как обычно:
{% highlight text linenos %}
    // Создаем одну OpenGL текстуру
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Привязываем" текстуру.
    glBindTexture(GL_TEXTURE_2D, textureID);
{% endhighlight %}
Следующим шагом мы загружаем мип-мапы:
{% highlight text linenos %}
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* загрузка мип-мапов */
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
{% endhighlight %}

##Инверсия V-координаты

DXT компрессия пришла к нам из DirectX, где координатная текстура V является инвертированной по сравнению с OpenGL. Поэтому, если вы используете сжатые текстуры, то вам необходимо использовать (coord.u, 1.0 - coord.v), чтобы исправить тексель. Вы можете выполнять это как при экспорте текстуры, так и в загрузчике или в шейдере.

#Заключение

В данном уроке вы узнали как создавать, загружать и использовать текстуры в OpenGL.

Стоит отметить, что в своих проектах мы настоятельно рекомендуем вам использовать только сжатые текстуры, так как они занимают меньше места, быстрее загружаются и используются. Для этих целей можете также использовать The Compressonator.

#Упражнения


* В исходный код к урокам включен загрузчик DDS, но без исправления текстурных координат. Модифицируйте код так, чтобы корректно выводить куб.
* Поэкспериментируйте с разными DDS форматами. Дают ли они разный результат или разную степень сжатия?
* Попробуйте не создавать мип-мапы в The Compressonator. Каков результат? Создайте 3 пути решения этих проблем.


#Полезные ссылки


* [Using texture compression in OpenGL](http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf) , S&eacute;bastien Domine, NVIDIA

