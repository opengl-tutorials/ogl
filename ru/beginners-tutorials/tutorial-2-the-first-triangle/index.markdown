---
layout: page
status: publish
published: true
title: 'Урок 2: Первый треугольник'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1242
wordpress_url: http://www.opengl-tutorial.org/?page_id=1242
date: '2014-04-09 22:06:16 +0100'
date_gmt: '2014-04-09 22:06:16 +0100'
categories: []
tags: []
comments: []
language: ru
---

Настало время еще одного большого урока.

OpenGL 3 позволяет довольно легко делать сложные вещи, однако вывод простейшего треугольника может показаться немного сложной задачей.
<blockquote>
Если программа "падает" при запуске, то скорее всего это потому, что вы запускаете ее из неправильной директории. Внимательно прочитайте первый урок, чтобы узнать как настроить Visual Studio.</blockquote>

#VAO

Мы не хотим сейчас углубляться в детали, но вам необходимо создать Vertex Array Object и установить его текущим:
{% highlight text linenos %}
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
{% endhighlight %}
Сделайте это после создания окна (т. е. после создания контекста OpenGL) и до любого другого вызова OpenGL.

Если вы хотите узнать больше о VAO, то здесь есть несколько уроков, но это не так важно сейчас.

#Экранные координаты

Треугольник задается тремя точками. Когда мы говорим о точках в 3D графике, мы используем слово вершина/vertex (вершины/vertices во множественном числе). Каждая вершина имеет 3 координаты: X, Y, Z. Вы можете представить эти координаты так:

* X находится справа
* Y находится вверху
* Z выходит из вашей спины назад. Z указывает именно назад, а не вперед.

Чтобы лучше понять это используйте правило правой руки:

* X - это ваш большой палец, направленный вправо
* Y - это ваш указательный палец, направленный вверх
* Z - это ваш средний палец, направленный на вас, а не от вас.

Заметьте, что вы можете свободно перемещать вашу руку в пространстве и оси X, Y, Z будут передвигаться также, но подробнее об этом мы поговорим позже.

Итак, все что нам нужно - это 3 точки в трехмерном пространстве, чтобы создать треугольник:
{% highlight text linenos %}
// Массив 3 векторов, которые являются вершинами треугольника
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
{% endhighlight %}
Первая вершина имеет координаты (-1, -1, 0). Это означает, что пока мы не используем какие-либо трансформации вершина будет отображаться на экране в точке (-1, -1). Центр экрана имеет координаты (0, 0), ось X направлена вправо, а ось Y вверх, что показано на изображении:

[<img title="screenCoordinates" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/screenCoordinates-300x165.png" width="300" height="165" />]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png)

Это то, что встроено в вашу видео карту и то, что вы не можете изменить, поэтому точка с координатами (-1, -1) будет находиться в левом-нижнем углу экрана, точка (1, -1) в правом нижнем, а точка (0, 1) будет находиться посередине по горизонтали и вверху по вертикали. Таким образом наш треугольник заполнит экран.

#Рисуем наш треугольник

Следующим шагом будет передача данных о нашем треугольнике в OpenGL. Для этого мы создаем буфер:
{% highlight text linenos %}
 
// Это будет идентификатором нашего буфера вершин
GLuint vertexbuffer;

// Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
glGenBuffers(1, &vertexbuffer);

// Сделаем только что созданный буфер текущим
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Передадим информацию о вершинах в OpenGL
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
{% endhighlight %}
Сейчас нам необходимо сделать это только 1 раз.

Теперь, в главном цикле, где до этого мы ничего не выводили, наконец можно вывести треугольник :
{% highlight text linenos %}
// Указываем, что первым буфером атрибутов будут вершины
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
   3,                  // Размер
   GL_FLOAT,           // Тип
   GL_FALSE,           // Указывает, что значения не нормализованы
   0,                  // Шаг
   (void*)0            // Смещение массива в буфере
);

// Вывести треугольник!
glDrawArrays(GL_TRIANGLES, 0, 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник

glDisableVertexAttribArray(0);
{% endhighlight %}
Если у вас карта NVidia, то уже сейчас вы можете видеть результат (для других карт продолжайте читать):

[<img title="triangle_no_shader" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/triangle_no_shader1-300x232.png" width="300" height="232" />]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png)

Наконец мы вывели наш скучный белый треугольник. Чтобы пойти дальше и раскрасить его в красный нам понадобится нечто, что называется "шейдеры".

#Шейдеры


##Компиляция шейдеров

В простейшей возможной конфигурации нам понадобится два шейдера. Один из них называется Вершинным и выполняется для каждой вершины, а другой называется Фрагментным и выполняется для каждого фрагмента. А так как мы включили 4х сглаживание (см. первый урок), то для каждого пикселя мы имеем 4 фрагмента.

В OpenGL шейдеры программируются на языке GLSL (GL Shader Language). В отличие от C или Java, GLSL компилируется во время выполнения программы, поэтому каждый новый запуск приложения будет сопровождаться перекомпиляцией шейдеров.

Эти два шейдера как правило находятся в разных файлах. В этом примере мы имеем SimpleFragmentShader.fragmentshader и SimpleVertexShader.vertexshader. Расширение файлов не имеет значения и может быть любым, к примеру .txt или .glsl.

Итак, вот код. Сейчас вам не обязательно углубляться в понимание шейдеров и так как этот код выполняется всего 1 раз за время исполнения программы, то комментариев в коде будет достаточно. Эта функция будет использована во всех уроках и находится в отдельном файле common/loadShader.cpp . Обратите внимание на то, что также как и с буферами мы не имеем прямого доступа к шейдерам. Мы лишь имеем Идентификатор, который указывает на шейдер, а все остальное скрыто внутри драйвера.
{% highlight text linenos %}
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Создаем шейдеры
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Загружаем код Вершинного Шейдера из файла
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "n" + Line;
        VertexShaderStream.close();
    }

    // Загружаем код Фрагментного шейдера из файла
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Компилируем Вершинный шейдер
    printf("Компиляция шейдера: %sn", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Выполняем проверку Вершинного шейдера
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);

    // Компилируем Фрагментный шейдер
    printf("Компиляция шейдера: %sn", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Проверяем Фрагментный шейдер
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%sn", &FragmentShaderErrorMessage[0]);

    // Создаем шейдерную программу и привязываем шейдеры к ней
    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Проверяем шейдерную программу
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%sn", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
{% endhighlight %}

##Наш Вершинный шейдер

Итак, давайте напишем наш первый вершинный шейдер.

Первая строка в нем говорит компилятору, что мы будем использовать синтаксис OpenGL 3.
{% highlight text linenos %}
#version 330 core
{% endhighlight %}
Вторая строка объявляет входные данные:
{% highlight text linenos %}
layout(location = 0) in vec3 vertexPosition_modelspace;
{% endhighlight %}
Остановимся подробнее на этом моменте:

* "vec3&Prime; - это вектор с тремя компонентами в GLSL. Это похоже на glm::vec3, который мы использовали для описания треугольника. Главное помнить, что если мы используем 3х компонентные векторы в C++, то мы должны использовать 3х компонентные векторы в GLSL.
* "layout(location = 0)" указывает на буфер из которого мы будем получать атрибут *vertexPosition_modelspace*. Каждая вершина может иметь несколько атрибутов, такие как: позиция, один или несколько цветов, текстурные координаты и другие. OpenGL на данном этапе ничего не знает о цвете и все, что он "видит" - это vec3, т. е. вектор с тремя компонентами. Мы же в свою очередь указываем, каким входным данным соответствует какой буфер. Для этого мы устанавливаем параметр location в такое же значение, которое мы использовали в качестве первого параметра в glVertexAttribPointer. Вообще, здесь не обязательно будет 0, здесь может быть и 12 и любое другое, но не большее чем glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v), а также важно чтобы число в location было таким же, как и в glVertexAttribPointer.
* "vertexPosition_modelspace" будет содержать позицию вершины для каждого прохода вертексного шейдера. Название может быть любым.
* Ключевое слово "in" означает, что этот атрибут является входными данными. Также существует слово "out", которое указывает соответственно на выходные данные.

Функция, которая будет вызываться для каждого шейдера называется "main", также как и в C:
{% highlight text linenos %}
void main(){
{% endhighlight %}
Наша главная функция будет просто устанавливать позицию вершины в ту, которая получена из буфера. Соответственно, если мы передадим значение (1, 1), то вершина будет отображена в правом верхнем углу экрана, а в следующем уроке мы рассмотрим более интересные вычисления.
{% highlight text linenos %}
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
 }
{% endhighlight %}
gl_Position - одна из нескольких встроенных в GLSL переменных. В данном случае мы просто присваиваем ей полученное из буфера значение. Все остальное не является обязательным и будет рассмотрено в Уроке 4.

##Наш Фрагментный шейдер

Для нашего первого фрагментного шейдера мы сделаем очень простую вещь - установим цвет каждого фрагмента в красный. (Не забудьте, у нас будет 4 фрагмента на каждый пиксель, так как мы используем 4х сглаживание):
{% highlight text linenos %}
#version 330 core
out vec3 color;

void main(){
    color = vec3(1,0,0);
}
{% endhighlight %}
И да, вы правы, vec3(1, 0, 0) соответствует красному цвету. Это потому, что на экране компьютера каждый цвет представляется триплетом из Красного, Зеленого и Синего. Таким образом (1, 0, 0) показывает, что цвет является полностью красным, без зеленого и синего.

#Последние штрихи

Перед главным циклом вызываем нашу функцию LoadShaders:
{% highlight text linenos %}
// Создать и откомпилировать нашу шейдерную программу
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
{% endhighlight %}
Теперь внутри главного цикла первым делом мы будем очищать экран. Строка приведенная ниже будет заполнять экран темно-синим цветом, так как перед главным циклом мы указываем именно его glClearColor(0.0f, 0.0f, 0.4f, 0.0f):
{% highlight text linenos %}
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
{% endhighlight %}
И теперь мы сообщаем OpenGL, что хотим использовать именно наш шейдер:
{% highlight text linenos %}
// Устанавливаем наш шейдер текущим
glUseProgram(programID);

// Рисуем треугольник...
{% endhighlight %}
... и наконец получаем наш красный треугольник:

[<img title="red_triangle" alt="" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/red_triangle-300x231.png" width="300" height="231" />]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png)

В следующем уроке вы узнаете о трансформациях, т. е. узнаете как установить камеру, как перемещать объекты и т. д. Увидимся :)
