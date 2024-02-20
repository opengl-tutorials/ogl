---
layout: tutorial
status: publish
published: true
title: 'Урок 7 : загрузка моделей'
date: '2011-05-08 17:48:12 +0200'
date_gmt: '2011-05-08 17:48:12 +0200'
categories: [tuto]
order: 70
tags: []
language: ru
---

До этого мы задавали данные для отрисовки куба прямо в коде. Уверен, вы согласны, что это громоздко и неудобно.

В этом уроке мы научимся как загружать 3D меши из файлов. Мы сделаем это так же, как сделали с текстурами : мы напишем небольшой, узкоспециализированный загрузчик, и я дам вам ссылку на готовые библиотеки, которые делают это лучше, чем мы.

Чтобы сделать этот урок как можно проще, мы будем использовать формат файла OBJ, которые одновременно очень простой и распространённый. И ещё раз, чтобы упростить задачу, мы будем иметь дело только с файлами OBJ с одной UV координатой и одной нормалью на каждую вершину (сейчас вам необязательно знать, что такое нормаль).

# Загрузка OBJ файла

Наша функция расположена в файле common/objloader.cpp и объявлена common/objloader.hpp, и оглавление будет выглядеть примерно так :

``` cpp
bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
)
```

Мы хотим чтобы функция loadOBJ прочитала файл "path", записала данные в out_vertices/out_uvs/out_normals и вернула false если что-то пошло не так. std::vector это способ объявить массив из glm::vec3, размер которого можно изменить по желанию, он не имеет ничего общего с математическим вектором. Всего лишь массив. И наконец & значит, что функция сможет изменять std::vectors.

## Пример OBJ файла

OBJ файл выглядит примерно так :
```

# Blender3D v249 OBJ File: untitled.blend
# www.blender3d.org
mtllib cube.mtl
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -1.000000
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 0.748573 0.750412
vt 0.749279 0.501284
vt 0.999110 0.501077
vt 0.999455 0.750380
vt 0.250471 0.500702
vt 0.249682 0.749677
vt 0.001085 0.750380
vt 0.001517 0.499994
vt 0.499422 0.500239
vt 0.500149 0.750166
vt 0.748355 0.998230
vt 0.500193 0.998728
vt 0.498993 0.250415
vt 0.748953 0.250920
vn 0.000000 0.000000 -1.000000
vn -1.000000 -0.000000 -0.000000
vn -0.000000 -0.000000 1.000000
vn -0.000001 0.000000 1.000000
vn 1.000000 -0.000000 0.000000
vn 1.000000 0.000000 0.000001
vn 0.000000 1.000000 -0.000000
vn -0.000000 -1.000000 0.000000
usemtl Material_ray.png
s off
f 5/1/1 1/2/1 4/3/1
f 5/1/1 4/3/1 8/4/1
f 3/5/2 7/6/2 8/7/2
f 3/5/2 8/7/2 4/8/2
f 2/9/3 6/10/3 3/5/3
f 6/10/4 7/6/4 3/5/4
f 1/2/5 5/1/5 2/9/5
f 5/1/6 6/10/6 2/9/6
f 5/1/7 8/11/7 6/10/7
f 8/11/7 7/12/7 6/10/7
f 1/2/8 2/9/8 3/13/8
f 1/2/8 3/13/8 4/14/8
```

Так :

* #это комментарий, как // в C++
* usemtl и mtllib описывают внешний вид модели. Мы не будем использовать их в этом уроке
* v обозначает вершину
* vt - это текстурная координата вершины
* vn - это нормаль вершины
* f - это грань

v, vt и vn просты в понимании. С f все сложнее. Так для строки f 8/11/7 7/12/7 6/10/7 :

* 8/11/7 обозначает первую вершину треугольника
* 7/12/7 обозначает вторую вершину треугольника
* 6/10/7 обозначает третью вершину треугольника
* В первой вершине 8 обозначает какую вершину использовать. В данном случае -1.000000 1.000000 -1.000000 (вершины нумеруются с единицы, не с нуля как в C++)
* 11 обозначает какую текстурную координату использовать. В данном случае 0.748355 0.998230
* 7 обозначает какую использовать нормаль. В данном случае, 0.000000 1.000000 -0.000000

Эти номера называются индексами. Это удобно, потому что в случае если несколько вершин находятся в одной и той же позиции, можно написать только одну v в файле и использовать её несколько раз. Это экономит память.

Плохие новость заключается в том, что OpenGL не может использовать один индекс для вершины, другой для текстур и ещё один для нормали. 
The bad news is that OpenGL can't be told to use one index for the position, another for the texture, and another for the normal. Мой подход в этом уроке заключается в том, чтобы создать простой, неиндексированный меш, а разбираться с индексами позже, в 9 уроке, который объяснит, как с этим работать.

## Создание OBJ файла в Blender'е

Так как наш загрузчик будет иметь некоторые ограничения, мы должны быть осторожнее с настройками экспорта файла. Вот как они должны выглядеть в Blender'е :

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/Blender.png)


## Чтение файла

Хорошо, ниже приведен сам код. Нам понадобятся несколько временных переменных, в которых мы сохраним данные из .obj :

``` cpp
std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;
```

После пятого урока : текстурированный куб, вы знаете как открыть файл :

``` cpp
FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
}
```

Давайте будем читать этот файл до конца :

``` cpp
while( 1 ){

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

    // else : parse lineHeader
```

(обратите внимание, что мы предполагаем, что первое слово в строке не длиннее чем 128, что является очень глупым предположением. Но для простейшего парсера подойдет и такой вариант)

Давайте сначала разберемся с вершинами :

``` cpp
if ( strcmp( lineHeader, "v" ) == 0 ){
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    temp_vertices.push_back(vertex);
```

то есть: если первое слово в строке "v", то следующие 3 должны быть числами с плавающей точкой, так что создаем из них glm::vec3 и добавляем в vector.

``` cpp
}else if ( strcmp( lineHeader, "vt" ) == 0 ){
    glm::vec2 uv;
    fscanf(file, "%f %f\n", &uv.x, &uv.y );
    temp_uvs.push_back(uv);
```

то есть: если первое слово не "v", а "vt", тогда дальше должны идте два числа, создаем glm::vec2 из них и добавляем в vector.

То же самое для нормалей :

``` cpp
}else if ( strcmp( lineHeader, "vn" ) == 0 ){
    glm::vec3 normal;
    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
    temp_normals.push_back(normal);
```

А сейчас разберем "f", который больее сложный :

``` cpp
}else if ( strcmp( lineHeader, "f" ) == 0 ){
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9){
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
    }
    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices    .push_back(uvIndex[0]);
    uvIndices    .push_back(uvIndex[1]);
    uvIndices    .push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
```

По факту этот код очень похож на предыдущие, за исключением того, что здесь больше данных для чтения.

## Обработка данных

Итак, мы всего лишь изменили "форму" данных, у нас была строка, сейчас у нас есть набор из std::vector'ов. Но этого недостаточно, вы должны перевести всё это в форму, понятную для OpenGL. А именно, удалить индексы и использовать вместо этого просто glm::vec3. Эта операция называется индексацией.

Мы пройдемся через все вершины ( каждый из v/vt/vn ) каждого треугольника ( все строки с "f" ) :

``` cpp
    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

```

индекс позиции вершины - это vertexIndices[i] :

``` cpp
unsigned int vertexIndex = vertexIndices[i];
```

так что позиция вершины - это temp_vertices[ vertexIndex-1 ] (здесь мы отнимаем единицу, потому что индексирование в C++ начинается с нуля, а в OBJ с единицы, помните?) :

``` cpp
glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
```

Это будет позицией нашей новой вершины

``` cpp
out_vertices.push_back(vertex);
```

Делаем то же самое для UV и нормалей, готово!
The same is applied for UVs and normals, and we're done !

# Использование загруженных данных

После этого почти не нужно ничего менять. Вместо объявление нашего обычного static const GLfloat g_vertex_buffer_data[] = {...}, вы объявили std::vector из вершин вместо этого (и то же самое для UV и нормалей). Вы вызываете loadOBJ с правильными параметрами :
Once we've got this, almost nothing changes. Instead of declaring our usual static const GLfloat g_vertex_buffer_data[] = {...}, you declare a std::vector vertices instead (same thing for UVS and normals). You call loadOBJ with the right parameters :

``` cpp
// Read our .obj file
std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.
bool res = loadOBJ("cube.obj", vertices, uvs, normals);
```

и он передает ваши vector'ы OpenGL вместо массивов :

``` cpp
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
```

Вот и всё !

# Результаты

Извините за плохую текстуру, я НЕ хороший художник :( Любой вклад приветствуется !

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/ModelLoading.png)


# Другие форматы/загрузчики

Этот небольшой загрузчик должен вым дать всё необходимое для начала, но не используйте его в настоящий проектах. Посмотрите лучше наш список [Полезных ссылок и инструментов](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) с некоторыми вещами, которые вы можете использовать. Однако лучше подождать до урока 9 прежде чем *в самом деле* их использовать.

Примечание переводчика: Я не профессиональный переводчик, но мне показалось странным, что эта статья до сих пор не на русском, надеюсь я кому-нибудь помог :) 
