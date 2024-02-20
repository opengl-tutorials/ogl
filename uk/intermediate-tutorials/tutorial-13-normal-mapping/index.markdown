---
layout: tutorial
status: publish
published: true
title: 'Tutorial 13 : Normal Mapping'
date: '2011-05-26 06:07:04 +0200'
date_gmt: '2011-05-26 06:07:04 +0200'
categories: [tuto]
order: 530
tags: []
language: uk
---

* TOC
{:toc}

Ласкаво просимо до нашого 13 туторіла! Сьогодні ми дізнаємося про роботу з нормалями <<normal mapping>>

З часів [Туторіалу 8 : базове затінення]({{site.baseurl}}/uk/beginners-tutorials/tutorial-8-basic-shading/), отримати гарне затінення, використовуючи нормалі трикутників. До цих пір у нас була одна нормаль на вершину - в середині трикутника вона плавно змінювалась, а ось з кольором все по іншому - там є текстури. Базова ідея відображення нормалей (normal mapping) полягає в наданні нормалям такої же гнучкості.

# Текстури нормалей

"Текстура нормалей" зазвичай виглядає десь так:


![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normal.jpg)

В кожному RGB текселі закодовано XYZ вектор: кожна кольорова компонента знаходиться в діапазоні 0..1 і кожний компонент вектора в діапазоні -1..1, отже це просте відображення з текселів в нормалі:

``` c
normal = (2*color)-1 // для кожного компонента
```

Ці текстури в основному сині, тому що в основному нормалі направлені "з поверхні". Зазвичай, X координата вказує вправо на площині, Y - вгору (в контексті зображення  текстури), отже за правилом правої руки, Z направлено назовні площини текстури.

Ця текстура використовується точнісінько так само, як і дифузна. Та проблема полягає в тому, як конвертувати наші нормалі, які виражені в просторі кожного індивідуального трикутника (дотичний (tangent) простір, також "простір зображення"), в простір моделі (так як він використовується в нашому рівнянні затінення).

# Tangent and Bitangent

Тепер Ви достатньо знайомі з матрицями, тому Ви знаєте, що щоби визначити простір (в нашому випадку, дотичний простір), нам потрібно 3 вектори. Ми вже маємо наш "вгору" вектор - це нормаль, яку нам надає Blender чи розраховується на основі трикутника просто векторним добутком. Цей вектор представлений синім кольором, таким, який в середньому колір на карті нормалей :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/NormalVector.png)

Також нам потрібна дотична, T - вектор, який паралельний поверхні. Але є багато таких векторів :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/TangentVectors.png)

Який з них нам потрібно використовувати? В теорії, будь-який, але нам потрібно, щоб він був узгоджений з  сусідніми, що б уникнути потворних країв. Стандартний спосіб полягає в тому, що б орієнтувати так само, як і текстурні координати:

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/TangentVectorFromUVs.png)

Так як нам потрібно 3 вектори, що б визначити базис, нам потрібно розрахувати <<бідотичний вектор>> B (який насправді може бути  будь-яким із дотичних векторів, але математика стає простою, коли все перпендикулярне) :

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/NTBFromUVs.png)


 Ось алгоритм: якщо ми позначимо через deltaPos1 та deltaPos2 два ребра нашого трикутника, а також deltaUV1 та deltaUV2 відповідні різниці в UV, то ми можемо виразити нашу проблему наступним рівнянням:

``` c
deltaPos1 = deltaUV1.x * T + deltaUV1.y * B
deltaPos2 = deltaUV2.x * T + deltaUV2.y * B
```

Потрібно просто розв'язати це рівняння відносно T і B і у Вас будуть Ваші вектора! (дивіться код нижче)

Як тільки ми маємо вектора T, B, N, ми також маємо цю гарну матрицю яка дозволяє нам перейти від дотичного простору в простір моделі:

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/TBN.png)

За допомогою цієї TBN матриці ми можемо трансформувати нормалі (які отримали з текстури) в простір моделі. Та зазвичай це робиться навпаки - трансформуємо все з простору моделі в дотичний простір і зберігаємо отримані нормалі такими, як вони є. Всі обчислення робляться в дотичному просторі, що нічого не змінює.

<<Це зворотня трансформація, ми просто беремо інвертовану матрицю, яка в даному випадку (ортогональна матриця, тобто кожний вектор є перпендикулярний до інших. Дивіться розділ "йдемо далі" нижче) є просто транспонованою матрицею, що значно спрощує наші розрахунки:>>


``` c
invTBN = transpose(TBN)
```

, тобто :
![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/transposeTBN.png)


# Підготовка нашого VBO


## Розрахунок дотичної і бідотичної

Оскільки нам потрібні дотичні і бідотичні поверх наших нормалей, ми розрахуємо їх для всього меша. Ми зробимо це в окремій функції:

``` cpp
void computeTangentBasis(
    // вхідні
    std::vector<glm::vec3> & vertices,
    std::vector<glm::vec2> & uvs,
    std::vector<glm::vec3> & normals,
    // вихідні
    std::vector<glm::vec3> & tangent,
    std::vector<glm::vec3> & bitangent
){
```

для кожного трикутника ми розраховуємо ребро (deltaPos) та deltaUV

``` cpp
    for ( int i=0; i<vertices.size(); i+=3){

        // скорочення для вершин
        glm::vec3 & v0 = vertices[i+0];
        glm::vec3 & v1 = vertices[i+1];
        glm::vec3 & v2 = vertices[i+2];

        // скорочення для UVs
        glm::vec2 & uv0 = uvs[i+0];
        glm::vec2 & uv1 = uvs[i+1];
        glm::vec2 & uv2 = uvs[i+2];

        // ребра трикутника : position delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // дельта UV
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;
```

Тепер ми можемо використовувати нашу формулу для обчислення дотичної та бідотичної:

``` cpp
        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
```

В кінці кінців ми заповнюємо `tangents` та `bitangents` буфери. Пам'ятайте, ці буфери ще не індексовані, тому кожна вершина має свою копію.

``` cpp
        // Виставимо однакову дотичну для всіх трьох вершин цього трикутника.
        // вони будуть об'єднанні пізніше, в vboindexer.cpp
        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        // те саме для бідотичних данних
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);

    }
```

## Індексування

Індексування нашого VBO дуже подібне до того, що ми робили раніше, але є невеличка різниця.

Якщо ми знайшли подібні вершини (та сама позиція, та сама нормаль, та сама текстурна координата), ми не хочемо використовувати його дотичну і бідотичну, ми будемо знаходить середнє. Отже трішки модифікуємо наш старий код:


``` cpp
        // Спробуємо знайти подібну вершину в out_XXXX
        unsigned int index;
        bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);

        if ( found ){ // Подібна вершина вже є в VBO, використовуємо !
            out_indices.push_back( index );

            // знаходимо середнє для дотичної і бідотичної
            out_tangents[index] += in_tangents[i];
            out_bitangents[index] += in_bitangents[i];
        }else{ // Якщо нічого не знайшли.
            // працюємо як зазвичай
            [...]
        }
```

Як бачите, ми нічого не нормалізуємо тут. Це достатньо зручно, тому що таким чином, маленькі трикутники, які мають маленькі дотичні і бідотичні вектори, буде мати слабкий ефект на результуючий вектор ніж великий трикутник (який внесе більше в результат). 

# Шейдери


## Additional buffers & uniforms

Ми маємо два нових буфера - один для дотичних і один для бідотичних:

``` cpp
    GLuint tangentbuffer;
    glGenBuffers(1, &tangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), &indexed_tangents[0], GL_STATIC_DRAW);

    GLuint bitangentbuffer;
    glGenBuffers(1, &bitangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), &indexed_bitangents[0], GL_STATIC_DRAW);
```

Нам також потрібна нова uniform зміна для нових нормалей текстури:

``` cpp
    [...]
    GLuint NormalTexture = loadTGA_glfw("normal.tga");
    [...]
    GLuint NormalTextureID  = glGetUniformLocation(programID, "NormalTextureSampler");
```

<<І одна для 3х3 матриці виду моделі. Строго говорячи це не є необхідним, але це просто - більше про це пізніше. Нам просто потрібна 3х3 верхня ліва частина  тому що ми будемо множити напрямки, отже ми можемо викинути частину трансляції (перенесення).>>

``` cpp
    GLuint ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");
```

І повний код, що малює зображення буде наступним:

``` cpp
        // Очистимо екран
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Наші шейдери
        glUseProgram(programID);

        // Розрахуємо MVP матрицю з клавіатури і матриці
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
        glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); // Візьмемо ліву верхню частинку матриці ModelViewMatrix
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

        // Відправимо нашу матрицю до поточного шейдера,
        // через змінну "MVP"
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);

        glm::vec3 lightPos = glm::vec3(0,0,4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // Прив'яжемо нашу дифузну текстуру в текстурний юніт 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
        // Set our "DiffuseTextureSampler" sampler to user Texture Unit 0
        glUniform1i(DiffuseTextureID, 0);

        // Прив'яжемо нашу текстуру з нормалями в текстурний юніт 1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, NormalTexture);
        // Set our "Normal    TextureSampler" sampler to user Texture Unit 0
        glUniform1i(NormalTextureID, 1);

        // перший атрибут в буфері: вершини
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // атрибут
            3,                  // розмір
            GL_FLOAT,           // тип
            GL_FALSE,           // нормалізовано?
            0,                  // крок
            (void*)0            // зміщення початку в буфері
        );

        // другий атрибут в буфері : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                                // атрибут
            2,                                // розмір
            GL_FLOAT,                         // тип
            GL_FALSE,                         // нормалізовано?
            0,                                // крок
            (void*)0                          // зміщення початку в буфері
        );

        // 3 атрибут в буфері : нормалі
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                                // атрибут
            3,                                // розмір
            GL_FLOAT,                         // тип
            GL_FALSE,                         // нормалізовано?
            0,                                // крок
            (void*)0                          // зміщення початку в буфері
        );

        // 4 атрибут в буфері: дотична
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
        glVertexAttribPointer(
            3,                                // атрибут
            3,                                // розмір
            GL_FLOAT,                         // тип
            GL_FALSE,                         // нормалізовано?
            0,                                // крок
            (void*)0                          // зміщення початку в буфері
        );

        // 5 атрибут в буфері: бідотична
        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
        glVertexAttribPointer(
            4,                                // атрибут
            3,                                // розмір
            GL_FLOAT,                         // тип
            GL_FALSE,                         // нормалізовано?
            0,                                // крок
            (void*)0                          // зміщення початку в буфері
        );

        // Індексний буфер
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Намалюємо трикутники !
        glDrawElements(
            GL_TRIANGLES,      // режим
            indices.size(),    // кількість
            GL_UNSIGNED_INT,   // тип
            (void*)0           // зміщення початку в буфері
        );

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);

        // обміняємо буфери
        glfwSwapBuffers();
```

## Вершинний шейдер

Як було сказано раніше, ми робили все в просторі камери, тому що так простіше отримати позицію фрагмента в цьому просторі. Ось чому ми множимо наші T,B,N вектори на матрицю вида моделі.

``` glsl
    vertexNormal_cameraspace = MV3x3 * normalize(vertexNormal_modelspace);
    vertexTangent_cameraspace = MV3x3 * normalize(vertexTangent_modelspace);
    vertexBitangent_cameraspace = MV3x3 * normalize(vertexBitangent_modelspace);
```
{: .highlightglslfs }

Ці три вектора визначають матрицю TBN, яка конструюється наступним чином:
```

    mat3 TBN = transpose(mat3(
        vertexTangent_cameraspace,
        vertexBitangent_cameraspace,
        vertexNormal_cameraspace
    )); // Ви можете використовувати векторний добуток замість побудови цієї матриці та транспонування. Дивіться Посилання для деталей.
```
Ця матриця йде від простору камери до дотичного простору (Подібна матриця, але з XXX_modelspace, буде від моделі в дотичний простір). Ми можемо використати її для розрахунку напрямку світла та напрямку очей в дотичному просторі:

```

    LightDirection_tangentspace = TBN * LightDirection_cameraspace;
    EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;
```

## Фрагментний шейдер

Наші нормалі в дотичному просторі дуже легко отримати - це є наша текстура:

``` glsl
    // Локальна нормаль, в дотичному просторі
    vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, UV ).rgb*2.0 - 1.0);
```
{: .highlightglslfs }

Отже, тепер у нас є все, що нам потрібно. Дифузне світло використовує *clamp( dot( n,l ), 0,1 )*, з `n` та `l`, які виражені в дотичному просторі (не має значення, в якому просторі ви зробите Ваші векторні та скалярні добутки, головне, щоб  `n` та `l` були в одному просторі ).  Дзеркальне освітлення використовує *clamp( dot( E,R ), 0,1 )* з `E` та `R`, які виражені в дотичному просторі. Так!

# Результати

Ось наш результат. Ви можете помітити, що:

* Цеглини виглядають горбиками, тому що ми маємо багато різних нормалей
* Цемент виглядає плоским, тому що текстура в основаному синя


![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normalmapping.png)


# Йдемо далі


## Ортогоналізація

В нашому вершинному шейдері ми транспонуємо, а не робимо інверсію, тому, що це швидше. Але це працює тільки якщо простір, який представлений матрицею є ортогональним, чого ще немає. На щастя, це дуже легко виправити - ми просто робимо дотичну перпендикулярну до нормалі в кінці `computeTangentBasis()`:


``` glsl
t = glm::normalize(t - n * glm::dot(n, t));
```
{: .highlightglslvs }

Ця формула може бути складною для розуміння, ця маленька схема може допомогти:

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/gramshmidt.png)

`n` та `t` майже перпендикулярні, отже ми можемо "проштовхнути" `t` в напрямку `-n` помноженному на `dot(n,t)`

[Ось](http://www.cse.illinois.edu/iem/least_squares/gram_schmidt/)' маленький аплет, який це також пояснює (Використовується тільки два вектори).

## <<Handedness>> "Правша-лівша"

Зазвичай Вам не потрібно турбуватись про це, але в деяких випадках, коли Ви використовуєте симетричні моделі, UV орієнтовано в невірному напрямку і Ваш `T` має невірну орієнтацію.

Перевірка необхідності інвертування дуже проста: `TBN` має бути в правій системі координат, тобто `cross(n,t)` має мати ту саму орієнтацію, що і `b`.

Мовою математики - "вектор A має ту саму орієнтацію, що і вектор B" значить, что `dot(A,B)>0`, отже нам потрібно перевірити `dot(cross(n,t), b) > 0`

Якщо це не так, просто інвертуйте `t`:

``` c
if (glm::dot(glm::cross(n, t), b) < 0.0f){
     t = t * -1.0f;
 }
```

Це також робиться для кожної вершини в кінці `computeTangentBasis()`.

## Дзеркальна текстура

Для задоволення, я просто додав дзеркальну текстуру в код. Це виглядає так:


![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/specular.jpg)

і використав це замість простого сірого `vec3(0.3,0.3,0.3)`, що використовувалось як дзеркальний колір.

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normalmappingwithspeculartexture.png)

Зверніть увагу, що зараз цемент завжди чорний - текстура говорить, що він не має дзеркальної компоненти.

## Налагодження за допомогою immediate (безпосереднього) режиму

Реальна ціль цього вебсайту в тому, що би Ви НЕ ВИКОРИСТОВУВАЛИ режим immediate (безпосередній), який є застарілим, повільним та проблематичним з багатьох причин.

Проте цей режим іноді дуже зручний для налагодження:

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/immediatemodedebugging.png)

Ось приклад візуалізації нашого дотичного простору за допомогою ліній, що намальовані в цьому режимі.

Для цього Вам потрібно буде відмовитись від core профілю 3.3 :

``` cpp
glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
```
далі передамо наші матриці до OpengGl в старий спосіб (Ви можете написати інший шейдер, але це значно простіше зробити в цей спосіб, Ви все одно <<хачите>>):

``` cpp
glMatrixMode(GL_PROJECTION);
glLoadMatrixf((const GLfloat*)&ProjectionMatrix[0]);
glMatrixMode(GL_MODELVIEW);
glm::mat4 MV = ViewMatrix * ModelMatrix;
glLoadMatrixf((const GLfloat*)&MV[0]);
```

Заборонимо шейдери :

``` cpp
glUseProgram(0);
```
І намалюємо Ваші лінії (в данному випадку, нормалі, які були нормалізовані, помножені на 0.1 і прикладені до правильних вершин):

``` cpp
glColor3f(0,0,1);
glBegin(GL_LINES);
for (int i=0; i<indices.size(); i++){
    glm::vec3 p = indexed_vertices[indices[i]];
    glVertex3fv(&p.x);
    glm::vec3 o = glm::normalize(indexed_normals[indices[i]]);
    p+=o*0.1f;
    glVertex3fv(&p.x);
}
glEnd();
```
Запам'ятайте: ніколи не використовуйте режим immediate в реальному коді! Тільки для налагодження! І не забувайте заново дозволити core профайл (режим). Це допоможе переконатись, що Ви більше не використовуєте старих речей.

## Налагождення з кольорами

Іноді при налагодженні буває корисно візуалізувати значення вектору. Найпростіший спосіб зробити це - записати це значення в буфер кадру замість справжнього кольору. Наприклад, давайте візуалізуємо `LightDirection_tangentspace`:


``` glsl
color.xyz = LightDirection_tangentspace;
```
{: .highlightglslfs }

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/colordebugging.png)

Це означає:

* В правій частині циліндра, світло (яке позначено маленькою біло лінією) направлено вгору (в дотичному просторі). Іншими словами, світло направлено в напрямку нормалі трикутника.
* В середній частині циліндра світло направлене в напрямку дотичної (протилежно напрямку осі X).

Декілька порад:

* Залежно від того, що Ви хочете візуалізувати, Ви напевне захочете нормалізувати це.
* Якщо ви не можете надати сенсу тому, що Ви бачите, візуалізуйте кожну компоненту окремо, занулючи інші кольорові складові (наприклад зелену та синю).
* Уникайте альфа каналу, це може бути сильно складно :)
* Якщо Ви хочете візуалізувати негативні значення, Ви можете використати цей самий трюк, що наші нормалі використовують - візуалізуйте '(v+1.0)/2.0'. В цьому випадку чорний буде значити -1, повний колір (білий) це будет +1. Хоча це все ще важко зрозуміти, що Ви бачите.
 

## <<Налагодження з іменами змінних>>

Як вже зазначалось раніше, дуже важливо точно знати, в якому саме просторі знаходятся Ваші вектори. Не беріть скалярний добуток в просторі камери та векторний в просторі моделі.

Додайте суффікси з назвою простору до до імен векторів (наприклад `..._modelspace`) і це допоможе виявити проблеми дуже легко.

## Як створити карту нормалей

Створено James O'Hare. Натисніть для збільшення.

![]({{site.baseurl}}/assets/images/tuto-13-normal-mapping/normalMapMiniTut.jpg)


# Вправи

* Нормалізуйте вектори в indexVBO_TBN перед тим як додавати і подивіться, що вийде.
* Візуалізуйте інші вектори (наприклад `EyeDirection_tangentspace`) в режимі кольорів і спробуйте знайти пояснення тому що Ви бачите.

# Інструменти та посилання


* [Crazybump](http://www.crazybump.com/) , чудовий інструмент для створення карти нормалей. Не безкоштовний.
* [Плагін для photoshop від Nvidia](http://developer.nvidia.com/nvidia-texture-tools-adobe-photoshop). Безкоштовний, проте photoshop ні...
* [Створіть свої карти нормалей з декількох фотографій](http://www.zarria.net/nrmphoto/nrmphoto.html)
* [Створіть свої карти нормалей з однієї фотографії](http://www.katsbits.com/tutorials/textures/making-normal-maps-from-photographs.php)
* Більше інформації про [транспонування матриць](http://www.katjaas.nl/transpose/transpose.html)


# Посилання


* [Lengyel, Eric. "Computing Tangent Space Basis Vectors for an Arbitrary Mesh". Terathon Software 3D Graphics Library, 2001.](http://www.terathon.com/code/tangent.html)
* [Real Time Rendering, third edition](http://www.amazon.com/dp/1568814240)
* [ShaderX4](http://www.amazon.com/dp/1584504250)




