---
layout: tutorial
status: publish
published: true
title: 'Туторіал 2 : Перший трикутник'
date: '2011-04-07 18:54:11 +0200'
date_gmt: '2011-04-07 18:54:11 +0200'
categories: [tuto]
order: 20
tags: []
language: uk
---

* TOC
{:toc}

Це буде ще один довгий туторіал.

OpenGL 3 робить простим написання складних штук, але малювання одного трикутника достатньо складне.

Не забувайте копіювати та вставляти собі код регулярно.

**<span style="color: red">Якщо програма падає, то можливо її запускають з неправильного каталогу. Прочитайте уважно [перший туторіал]({{ site.baseurl }}/beginners-tutorials/tutorial-1-opening-a-window/) і [FAQ]({{ site.baseurl }}/miscellaneous/faq/), що б налаштувати Visual Studio!</span>**

# VAO

Я не хочу сильно заглиблюватись зараз в деталі , але для початку потрібно створити об'єкт "масив вершин" (Vertex Array Object):

``` cpp
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
```

Зробіть це після того, як створено вікно (після того, як створено контекст OpenGL) та перед викликом будь-якої функції OpenGL.

Якщо ви дійсно хочете знати більше про VAO, тут є декілька інших туторіалів, але це не дуже важливо.

# Екранні координати

Трикутник визначається трьома точками. Коли говорять про "точки" в 3D графіці, ми зазвичай використовуємо слово "вершина" (вертекс). Вершина має три координати - X, Y та Z. Ви можете думати про ці три координати наступним чином:

- X вправо від вас
- Y вгору
- Z до вас (так, назад, а не вперед)

Та є гарний спосіб уявити собі це  - використовуйте правило правої руки

- X - великий палець
- Y вказівний
- Z середній палець. Якщо великий палець направити вправо, вказівний вгору (в небо), то середній палець буде показувати назад.

Напрям для осі Z виглядає трішки дивно, чому воно так? Коротка відповідь - тому що сотні років використання правила "правої руки" дало багато корисних інструментів. Єдиний недолік цього - не інтуїтивний напрямок осі Z.

Зверніть увагу, що ви можете вільно переміщувати вашу руку - ваші X, Y та Z теж будуть переміщуватись. Детальніше про це пізніше.

Отже нам потрібно три 3D точки для того, що б зробити трикутник, отже почнемо:


``` cpp
// вектор з трьох векторів, який являє собою 3 вершини
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
```
Перша вершина це (-1, -1, 0). Це значить що (_якщо тільки ми не трансформували це в якийсь спосіб_), ця вершина буде знаходитись в координатах (-1, -1) екрана. Що це значить? Початок координат екрана знаходиться в центрі, вісь X правлена вправо, я зазвичай і Y направлена вгору. Ось як це виглядає на широкому екрані:

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}

Це те, що ви не можете змінити, це вбудовано в вашу відеокарту. Отже (-1, -1) є нижньою лівою межею вашого екрана. (1, -1) це нижня права межа, (0, 1) - середина зверху. Отже, цей трикутник повинен займати більшу частину екрана.

# Малюємо наш трикутник

Наступний крок потрібен для передачі трикутника до OpenGL. Ми зробимо це, створивши буфер:

```cpp
// Це ідентифікатор нашого вершинного буфера
GLuint vertexbuffer;
// Згенеруємо буфер і збережемо його ідентифікатор в vertexbuffer
glGenBuffers(1, &vertexbuffer);
// Наступна команда зробить наш буфер 'vertexbuffer' активним (поточним)
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
// Передамо наші данні в активний буфер OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
```

Це потрібно зробити тільки раз.

Тепер, в нашому головному циклі, де ми малювали "нічого", можемо намалювати наш чудовий трикутник:

``` cpp
// перший атрибут в буфері : вершини
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // атрибут номер 0. Нема ніякої причини, чому 0, але він повинен збігатись з номером в layout в шейдері.
   3,                  // розмір
   GL_FLOAT,           // тип
   GL_FALSE,           // нормалізувати?
   0,                  // крок/stride
   (void*)0            // початок в масиву в буфері
);
// Малюємо трикутник !
glDrawArrays(GL_TRIANGLES, 0, 3); //Починаючи з вершини 0; малюємо 3 вершини -> 1 трикутник
glDisableVertexAttribArray(0);
```

Яко ви щасливчик, то ви можете побачити білий трикутник. (<span style="color: red">**Не панікуйте, якщо не бачите**</span> деякі системи вимагають шейдер для малювання) :

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}

Тепер воно сумно-біле. Давайте покращимо це, намалювавши його в червоному кольорі. Це можна зробити використавши "шейдери".

# Шейдер

## Компіляція шейдера

В найпростішому можливому варіанті вам потрібно два шейдери - один називається вершинний шейдер, який буде виконуватись для кожної вершини і другий, який називається фрагментний шейдер, який буде виконуватись для кожної вибірки (sample). І якщо ми використовуємо 4 кратне згладжування, у нас буде 4 вибірки на кожний піксель.

Шейдери пишуться на мові, яка називається GLSL - GL Shader Language, який є частиною OpenGL. На відміну від С чи Java, GLSL компілюється під час виконання, що значить, что кожний шейдер компілюється кожний раз, коли ваша програма запускається.

Ці два шейдери зазвичай знаходяться в різних файлах. В нашому прикладі, ми маємо SimpleFragmentShader.fragmentshader та SimpleVertexShader.vertexshader. Розширення файлу не має значення, це може бути .txt чи .glsl.

Отже ось код. Не обов'язково повністю зрозуміти їх, ми робимо це один раз в програмі, коментарів буде достатньо. Так як ця функція буде використовуватись в всіх наших прикладах, код розташований в окремому файлі - common/loadShader.cpp . Зауважте, що шейдери це просто буфери, вони не доступні напряму - у нас просто є ідентифікатор. Справжня реалізація схована в драйвері.

``` cpp
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Створимо шейдери
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Прочитаємо код вершинного шейдера з файлу
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Прочитаємо фрагментний шейдер
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Скомпілюємо вершинний шейдер
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Перевіримо вершинний шейдер
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Скомпілюємо фрагментний шейдер
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Перевіримо фрагментний шейдер
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Зв'яжемо (злінкуємо) шейдери в програму
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// перевіримо всю програму
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

## Наш вершинний шейдер

Давайте спочатку напишемо наш вершинний шейдер.
Перший рядок повідомляє компілятору, що ми хочемо синтаксис третьої версії.

``` glsl
#version 330 core
```
{: .highlightglslvs }

Другий рядок оголошує вхідні дані:

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```
{: .highlightglslvs }

Давайте розберемо цей рядок детальніше:

- `vec3` - це вектор з 3 елементів GLSL. Це подібно (але відрізняється) до `glm::vec3`, який ми  використовували для оголошення нашого трикутника. Важливо те, що якщо ми використовуємо вектор з трьох елементів в с++, то ми повинні використовувати такий же в GLSL.
- `layout(location = 0)` відноситься до буфера, який поставляє дані для атрибуту `vertexPosition_modelspace` . Кожна вершина може містити багато атрибутів - позицію, один чи декілька кольорів, текстурні координати (і не одні), багато інших даних. OpenGL  не знає, що це колір, для нього це просто `vec3`. Тому ми повинні прив'язати буфери до вхідних даних.  Ми робимо це, вказавши налаштування <<layout>> таким же, як і перший параметр `glVertexAttribPointer`. Значення "0" не є чимось особливим, можна взяти, наприклад, 12 (але не більше, ніж поверне виклик функції `glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v)`), важливо тільки що б ці числа були однакові.
- `vertexPosition_modelspace` може мати будь-яке ім'я.  Воно буде містити позицію поточної вершини для кожного запуску шейдера.
- `in` значить, що це вхідні дані. Скоро ми побачимо ключове слово `out`.

Функція, яка викликається для кожної вершини має ім'я `main`, так само як і в C:

``` glsl
void main(){
```
{: .highlightglslvs }

Наша функція `main` просто встановить позицію вершини з того, що було в буфері. Отже, якщо ми маємо (1,1), трикутник буде мати одну з його вершин на краю екрана зверху справа. В наступному тутоіалі ми побачимо, як зробити дещо більш цікавіше з вхідною позицією.

``` glsl
  gl_Position.xyz = vertexPosition_modelspace;
  gl_Position.w = 1.0;
}
```
{: .highlightglslvs }

`gl_Position` - одна з декількох вбудованих змінних - ви *повинні* присвоїти їй якесь значення. Все інше не є обов'язковим, ми дізнаємось, що таке "все інше" в туторіалі 4.

## Наш фрагментний шейдер


Для нашого першого фрагментного шейдера ми зробимо одну просту річ - виставимо колір для кожного фрагмента в червоне. (Пам'ятаєте, що є чотири фрагменти на один піксель, тому що ми використовуємо 4х згладжування).

``` glsl
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
```
{: .highlightglslfs }

Так, `vec3(1,0,0)` - це червоний колір. Це тому, що на екрані колір представлений трійкою чисел для червоного, зеленого та синього кольору. Отже (1,0,0) значить чистий червоний, відсутній зелений і синій.

# Складаємо все докупи

Імпортуємо нашу функцію `LoadShaders`, додавши include:

```cpp
#include <common/shader.hpp>
```

Перед головним циклом викличемо нашу функцію `LoadShaders`:

```cpp
// Створимо та скомпілюємо нашу GLSL програму з шейдерів
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

Тепер в основному циклі, спочатку очистимо екран. Це змінить колір тла на темно-синій, тому що перед цим був виклик `glClearColor(0.0f, 0.0f, 0.4f, 0.0f)`:

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

і скажемо OpenGL, що ми хочемо використовувати наш шейдер:

``` cpp
// Використовуємо наш шейдер
glUseProgram(programID);
// Малюємо трикутник...
```

... і ось ваш червоний трикутник !

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}

В наступному туторіалі ми вивчимо трансформації - як налаштувати камеру, переміщувати об'єкти, то що.