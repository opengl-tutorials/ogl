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
<p>Настало время еще одного большого урока.</p>
<p>OpenGL 3 позволяет довольно легко делать сложные вещи, однако вывод простейшего треугольника может показаться немного сложной задачей.</p>
<blockquote><p>Если программа "падает" при запуске, то скорее всего это потому, что вы запускаете ее из неправильной директории. Внимательно прочитайте первый урок, чтобы узнать как настроить Visual Studio.<&#47;blockquote></p>
<h1>VAO<&#47;h1><br />
Мы не хотим сейчас углубляться в детали, но вам необходимо создать Vertex Array Object и установить его текущим:</p>
<pre>GLuint VertexArrayID;<br />
glGenVertexArrays(1, &amp;VertexArrayID);<br />
glBindVertexArray(VertexArrayID);<&#47;pre><br />
Сделайте это после создания окна (т. е. после создания контекста OpenGL) и до любого другого вызова OpenGL.</p>
<p>Если вы хотите узнать больше о VAO, то здесь есть несколько уроков, но это не так важно сейчас.</p>
<h1>Экранные координаты<&#47;h1><br />
Треугольник задается тремя точками. Когда мы говорим о точках в 3D графике, мы используем слово вершина&#47;vertex (вершины&#47;vertices во множественном числе). Каждая вершина имеет 3 координаты: X, Y, Z. Вы можете представить эти координаты так:</p>
<ul>
<li>X находится справа<&#47;li>
<li>Y находится вверху<&#47;li>
<li>Z выходит из вашей спины назад. Z указывает именно назад, а не вперед.<&#47;li><br />
<&#47;ul><br />
Чтобы лучше понять это используйте правило правой руки:</p>
<ul>
<li>X - это ваш большой палец, направленный вправо<&#47;li>
<li>Y - это ваш указательный палец, направленный вверх<&#47;li>
<li>Z - это ваш средний палец, направленный на вас, а не от вас.<&#47;li><br />
<&#47;ul><br />
Заметьте, что вы можете свободно перемещать вашу руку в пространстве и оси X, Y, Z будут передвигаться также, но подробнее об этом мы поговорим позже.</p>
<p>Итак, все что нам нужно - это 3 точки в трехмерном пространстве, чтобы создать треугольник:</p>
<pre>&#47;&#47; Массив 3 векторов, которые являются вершинами треугольника<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
   -1.0f, -1.0f, 0.0f,<br />
   1.0f, -1.0f, 0.0f,<br />
   0.0f,&nbsp; 1.0f, 0.0f,<br />
};<&#47;pre><br />
Первая вершина имеет координаты (-1, -1, 0). Это означает, что пока мы не используем какие-либо трансформации вершина будет отображаться на экране в точке (-1, -1). Центр экрана имеет координаты (0, 0), ось X направлена вправо, а ось Y вверх, что показано на изображении:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;screenCoordinates.png"><img title="screenCoordinates" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;screenCoordinates-300x165.png" width="300" height="165" &#47;><&#47;a></p>
<p>Это то, что встроено в вашу видео карту и то, что вы не можете изменить, поэтому точка с координатами (-1, -1) будет находиться в левом-нижнем углу экрана, точка (1, -1) в правом нижнем, а точка (0, 1) будет находиться посередине по горизонтали и вверху по вертикали. Таким образом наш треугольник заполнит экран.</p>
<h1>Рисуем наш треугольник<&#47;h1><br />
Следующим шагом будет передача данных о нашем треугольнике в OpenGL. Для этого мы создаем буфер:</p>
<pre>&nbsp;<br />
&#47;&#47; Это будет идентификатором нашего буфера вершин<br />
GLuint vertexbuffer;</p>
<p>&#47;&#47; Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор<br />
glGenBuffers(1, &amp;vertexbuffer);</p>
<p>&#47;&#47; Сделаем только что созданный буфер текущим<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);</p>
<p>&#47;&#47; Передадим информацию о вершинах в OpenGL<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);<&#47;pre><br />
Сейчас нам необходимо сделать это только 1 раз.</p>
<p>Теперь, в главном цикле, где до этого мы ничего не выводили, наконец можно вывести треугольник :</p>
<pre>&#47;&#47; Указываем, что первым буфером атрибутов будут вершины<br />
glEnableVertexAttribArray(0);<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);<br />
glVertexAttribPointer(<br />
   0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.<br />
   3,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Размер<br />
   GL_FLOAT,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Тип<br />
   GL_FALSE,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Указывает, что значения не нормализованы<br />
   0,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Шаг<br />
   (void*)0&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Смещение массива в буфере<br />
);</p>
<p>&#47;&#47; Вывести треугольник!<br />
glDrawArrays(GL_TRIANGLES, 0, 3); &#47;&#47; Начиная с вершины 0, всего 3 вершины -> один треугольник</p>
<p>glDisableVertexAttribArray(0);<&#47;pre><br />
Если у вас карта NVidia, то уже сейчас вы можете видеть результат (для других карт продолжайте читать):</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;triangle_no_shader1.png"><img title="triangle_no_shader" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;triangle_no_shader1-300x232.png" width="300" height="232" &#47;><&#47;a></p>
<p>Наконец мы вывели наш скучный белый треугольник. Чтобы пойти дальше и раскрасить его в красный нам понадобится нечто, что называется "шейдеры".</p>
<h1>Шейдеры<&#47;h1></p>
<h2>Компиляция шейдеров<&#47;h2><br />
В простейшей возможной конфигурации нам понадобится два шейдера. Один из них называется Вершинным и выполняется для каждой вершины, а другой называется Фрагментным и выполняется для каждого фрагмента. А так как мы включили 4х сглаживание (см. первый урок), то для каждого пикселя мы имеем 4 фрагмента.</p>
<p>В OpenGL шейдеры программируются на языке GLSL (GL Shader Language). В отличие от C или Java, GLSL компилируется во время выполнения программы, поэтому каждый новый запуск приложения будет сопровождаться перекомпиляцией шейдеров.</p>
<p>Эти два шейдера как правило находятся в разных файлах. В этом примере мы имеем SimpleFragmentShader.fragmentshader и SimpleVertexShader.vertexshader. Расширение файлов не имеет значения и может быть любым, к примеру .txt или .glsl.</p>
<p>Итак, вот код. Сейчас вам не обязательно углубляться в понимание шейдеров и так как этот код выполняется всего 1 раз за время исполнения программы, то комментариев в коде будет достаточно. Эта функция будет использована во всех уроках и находится в отдельном файле common&#47;loadShader.cpp . Обратите внимание на то, что также как и с буферами мы не имеем прямого доступа к шейдерам. Мы лишь имеем Идентификатор, который указывает на шейдер, а все остальное скрыто внутри драйвера.</p>
<pre>GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){</p>
<p>    &#47;&#47; Создаем шейдеры<br />
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);<br />
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);</p>
<p>    &#47;&#47; Загружаем код Вершинного Шейдера из файла<br />
    std::string VertexShaderCode;<br />
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);<br />
    if(VertexShaderStream.is_open())<br />
    {<br />
        std::string Line = "";<br />
        while(getline(VertexShaderStream, Line))<br />
            VertexShaderCode += "n" + Line;<br />
        VertexShaderStream.close();<br />
    }</p>
<p>    &#47;&#47; Загружаем код Фрагментного шейдера из файла<br />
    std::string FragmentShaderCode;<br />
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);<br />
    if(FragmentShaderStream.is_open()){<br />
        std::string Line = "";<br />
        while(getline(FragmentShaderStream, Line))<br />
            FragmentShaderCode += "n" + Line;<br />
        FragmentShaderStream.close();<br />
    }</p>
<p>    GLint Result = GL_FALSE;<br />
    int InfoLogLength;</p>
<p>    &#47;&#47; Компилируем Вершинный шейдер<br />
    printf("Компиляция шейдера: %sn", vertex_file_path);<br />
    char const * VertexSourcePointer = VertexShaderCode.c_str();<br />
    glShaderSource(VertexShaderID, 1, &amp;VertexSourcePointer , NULL);<br />
    glCompileShader(VertexShaderID);</p>
<p>    &#47;&#47; Выполняем проверку Вершинного шейдера<br />
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &amp;VertexShaderErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;VertexShaderErrorMessage[0]);</p>
<p>    &#47;&#47; Компилируем Фрагментный шейдер<br />
    printf("Компиляция шейдера: %sn", fragment_file_path);<br />
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();<br />
    glShaderSource(FragmentShaderID, 1, &amp;FragmentSourcePointer , NULL);<br />
    glCompileShader(FragmentShaderID);</p>
<p>    &#47;&#47; Проверяем Фрагментный шейдер<br />
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &amp;FragmentShaderErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;FragmentShaderErrorMessage[0]);</p>
<p>    &#47;&#47; Создаем шейдерную программу и привязываем шейдеры к ней<br />
    fprintf(stdout, "Создаем шейдерную программу и привязываем шейдеры к нейn");<br />
    GLuint ProgramID = glCreateProgram();<br />
    glAttachShader(ProgramID, VertexShaderID);<br />
    glAttachShader(ProgramID, FragmentShaderID);<br />
    glLinkProgram(ProgramID);</p>
<p>    &#47;&#47; Проверяем шейдерную программу<br />
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &amp;Result);<br />
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );<br />
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &amp;ProgramErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;ProgramErrorMessage[0]);</p>
<p>    glDeleteShader(VertexShaderID);<br />
    glDeleteShader(FragmentShaderID);</p>
<p>    return ProgramID;<br />
}<&#47;pre></p>
<h2>Наш Вершинный шейдер<&#47;h2><br />
Итак, давайте напишем наш первый вершинный шейдер.</p>
<p>Первая строка в нем говорит компилятору, что мы будем использовать синтаксис OpenGL 3.</p>
<pre>#version 330 core<&#47;pre><br />
Вторая строка объявляет входные данные:</p>
<pre>layout(location = 0) in vec3 vertexPosition_modelspace;<&#47;pre><br />
Остановимся подробнее на этом моменте:</p>
<ul>
<li>&ldquo;vec3&Prime; - это вектор с тремя компонентами в GLSL. Это похоже на glm::vec3, который мы использовали для описания треугольника. Главное помнить, что если мы используем 3х компонентные векторы в C++, то мы должны использовать 3х компонентные векторы в GLSL.<&#47;li>
<li>&ldquo;layout(location = 0)&rdquo; указывает на буфер из которого мы будем получать атрибут <em>vertexPosition_modelspace<&#47;em>. Каждая вершина может иметь несколько атрибутов, такие как: позиция, один или несколько цветов, текстурные координаты и другие. OpenGL на данном этапе ничего не знает о цвете и все, что он "видит" - это vec3, т. е. вектор с тремя компонентами. Мы же в свою очередь указываем, каким входным данным соответствует какой буфер. Для этого мы устанавливаем параметр location в такое же значение, которое мы использовали в качестве первого параметра в glVertexAttribPointer. Вообще, здесь не обязательно будет 0, здесь может быть и 12 и любое другое, но не большее чем glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &amp;v), а также важно чтобы число в location было таким же, как и в glVertexAttribPointer.<&#47;li>
<li>"vertexPosition_modelspace" будет содержать позицию вершины для каждого прохода вертексного шейдера. Название может быть любым.<&#47;li>
<li>Ключевое слово "in" означает, что этот атрибут является входными данными. Также существует слово "out", которое указывает соответственно на выходные данные.<&#47;li><br />
<&#47;ul><br />
Функция, которая будет вызываться для каждого шейдера называется "main", также как и в C:</p>
<pre>void main(){<&#47;pre><br />
Наша главная функция будет просто устанавливать позицию вершины в ту, которая получена из буфера. Соответственно, если мы передадим значение (1, 1), то вершина будет отображена в правом верхнем углу экрана, а в следующем уроке мы рассмотрим более интересные вычисления.</p>
<pre>    gl_Position.xyz = vertexPosition_modelspace;<br />
    gl_Position.w = 1.0;<br />
&nbsp;}<&#47;pre><br />
gl_Position - одна из нескольких встроенных в GLSL переменных. В данном случае мы просто присваиваем ей полученное из буфера значение. Все остальное не является обязательным и будет рассмотрено в Уроке 4.</p>
<h2>Наш Фрагментный шейдер<&#47;h2><br />
Для нашего первого фрагментного шейдера мы сделаем очень простую вещь - установим цвет каждого фрагмента в красный. (Не забудьте, у нас будет 4 фрагмента на каждый пиксель, так как мы используем 4х сглаживание):</p>
<pre>#version 330 core<br />
out vec3 color;</p>
<p>void main(){<br />
    color = vec3(1,0,0);<br />
}<&#47;pre><br />
И да, вы правы, vec3(1, 0, 0) соответствует красному цвету. Это потому, что на экране компьютера каждый цвет представляется триплетом из Красного, Зеленого и Синего. Таким образом (1, 0, 0) показывает, что цвет является полностью красным, без зеленого и синего.</p>
<h1>Последние штрихи<&#47;h1><br />
Перед главным циклом вызываем нашу функцию LoadShaders:</p>
<pre>&#47;&#47; Создать и откомпилировать нашу шейдерную программу<br />
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );<&#47;pre><br />
Теперь внутри главного цикла первым делом мы будем очищать экран. Строка приведенная ниже будет заполнять экран темно-синим цветом, так как перед главным циклом мы указываем именно его glClearColor(0.0f, 0.0f, 0.4f, 0.0f):</p>
<pre>glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);<&#47;pre><br />
И теперь мы сообщаем OpenGL, что хотим использовать именно наш шейдер:</p>
<pre>&#47;&#47; Устанавливаем наш шейдер текущим<br />
glUseProgram(programID);</p>
<p>&#47;&#47; Рисуем треугольник...<&#47;pre><br />
... и наконец получаем наш красный треугольник:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;red_triangle.png"><img title="red_triangle" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;red_triangle-300x231.png" width="300" height="231" &#47;><&#47;a></p>
<p>В следующем уроке вы узнаете о трансформациях, т. е. узнаете как установить камеру, как перемещать объекты и т. д. Увидимся :)</p>
