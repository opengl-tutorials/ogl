---
layout: page
status: publish
published: true
title: 'Урок 3: Матрицы'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1248
wordpress_url: http://www.opengl-tutorial.org/?page_id=1248
date: '2014-04-24 10:10:50 +0100'
date_gmt: '2014-04-24 10:10:50 +0100'
categories: []
tags: []
comments: []
language: ru
---
<blockquote>Движок не перемещает корабль. Корабль остается на месте, а движок перемещает вселенную относительно его.</p>
<p>Futurama<&#47;blockquote><br />
Это очень важная часть уроков, убедитесь что прочитали ее несколько раз и хорошо поняли.</p>
<h1>Однородные координаты<&#47;h1><br />
До текущего момента мы оперировали 3х-мерными вершинами как (x, y, z) триплетами. Введем еще один параметр w и будем оперировать векторами вида (x, y, z, w).</p>
<p>Запомните навсегда, что:</p>
<ul>
<li>Если w == 1, то вектор (x, y, z, 1) - это позиция в пространстве.<&#47;li>
<li>Если же w == 0, то вектор (x, y, z, 0) - это направление.<&#47;li><br />
<&#47;ul><br />
Что это дает нам? Ок, для поворота это ничего не меняет, так как и в случае поворота точки и в случае поворота вектора направления вы получаете один и тот же результат. Однако в случае переноса есть разница. Перенос вектора направления даст тот же самый вектор. Подробнее об этом остановимся позднее.</p>
<p>Однородные координаты позволяют нам с помощью одной математической формулы оперировать векторами в обоих случаях.</p>
<h1>Матрицы трансформаций<&#47;h1></p>
<h2>Введение в матрицы<&#47;h2><br />
Проще всего представить матрицу, как массив чисел, со строго определенным количеством строк и столбцов. К примеру, матрица 2x3 выглядит так:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;2X3.png"><img title="2X3" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;2X3.png" width="68" height="44" &#47;><&#47;a></p>
<p>Однако в трехмерной графике мы будем использовать только матрицы 4x4, которые позволят нам трансформировать наши вершины (x, y, z, w). Трансформированная вершина является результатом умножения матрицы на саму вершину:</p>
<p><strong>Матрица x Вершина&nbsp; (именно в этом порядке!!) = Трансформир. вершина<br />
<&#47;strong></p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MatrixXVect.gif"><img title="MatrixXVect" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MatrixXVect-300x71.gif" width="300" height="71" &#47;><&#47;a></p>
<p>Довольно просто. Мы будем использовать это довольно часто, так что имеет смысл поручить это компьютеру:</p>
<p><strong>В C++, используя GLM:<&#47;strong></p>
<pre>glm::mat4 myMatrix;<br />
glm::vec4 myVector;<br />
&#47;&#47; Не забудьте тут заполнить матрицу и вектор необходимыми значениями<br />
glm::vec4 transformedVector = myMatrix * myVector; &#47;&#47; Обратите внимание на порядок! Он важен!<&#47;pre><br />
<strong>В GLSL :<&#47;strong></p>
<pre>mat4 myMatrix;<br />
vec4 myVector;<br />
&#47;&#47; Не забудьте тут заполнить матрицу и вектор необходимыми значениями<br />
vec4 transformedVector = myMatrix * myVector; &#47;&#47; Да, это очень похоже на GLM :)<&#47;pre><br />
Попробуйте поэкспериментировать с этими фрагментами.</p>
<h2>Матрица переноса<&#47;h2><br />
Матрица переноса выглядит так:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationMatrix.png"><img title="translationMatrix" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationMatrix.png" width="103" height="88" &#47;><&#47;a></p>
<p>где X, Y, Z - это значения, которые мы хотим добавить к нашему вектору.</p>
<p>Значит, если мы захотим перенести вектор (10, 10, 10, 1) на 10 юнитов в направлении X, то мы получим:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExamplePosition1.png"><img title="translationExamplePosition" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExamplePosition1.png" width="639" height="82" &#47;><&#47;a></p>
<p>&hellip; получим (20, 10, 10, 1) однородный вектор! Не забывайте, что 1 в параметре w, означает позицию, а не направление и наша трансформация не изменила того, что мы работаем с позицией.</p>
<p>Теперь посмотрим, что случится, если вектор (0, 0, -1, 0) представляет собой направление:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExampleDirection1.png"><img title="translationExampleDirection" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExampleDirection1.png" width="621" height="82" &#47;><&#47;a></p>
<p>... и получаем наш оригинальный вектор (0, 0, -1, 0). Как было сказано раньше, вектор с параметром w = 0 нельзя перенести.</p>
<p>И самое время перенести это в код.</p>
<p><strong>В C++, с GLM:<&#47;strong></p>
<pre>#include <glm&#47;transform.hpp> &#47;&#47; после <glm&#47;glm.hpp></p>
<p>glm::mat4 myMatrix = glm::translate(10.0f, 0.0f, 0.0f);<br />
glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);<br />
glm::vec4 transformedVector = myMatrix * myVector;<&#47;pre><br />
<strong>В GLSL :<br />
<&#47;strong>По факту, вы никогда не будете делать это в шейдере, чаще всего вы будете выполнять glm::translate() в C++, чтобы вычислить матрицу, передать ее в GLSL, а уже в шейдере выполнить умножение:</p>
<pre>vec4 transformedVector = myMatrix * myVector;<&#47;pre></p>
<h2>Единичная матрица<&#47;h2><br />
Это специальная матрица, которая не делает ничего, но мы затрагиваем ее, так как важно помнить, что A умноженное на 1.0 дает A:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;identityExample.png"><img title="identityExample" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;identityExample.png" width="742" height="80" &#47;><&#47;a></p>
<p><strong>В C++ :<&#47;strong></p>
<pre>glm::mat4 myIdentityMatrix = glm::mat4(1.0f);<&#47;pre></p>
<h2>Матрица масштабирования<&#47;h2><br />
Выглядит также просто:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingMatrix.png"><img title="scalingMatrix" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingMatrix.png" width="98" height="88" &#47;><&#47;a></p>
<p>Значит, если вы хотите применить масштабирование вектора (позицию или направление - это не важно) на 2.0 во всех направлениях, то вам необходимо:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingExample.png"><img title="scalingExample" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingExample.png" width="799" height="80" &#47;><&#47;a></p>
<p>Обратите внимание, что w не меняется, а также обратите внимание на то, что единичная матрица - это частный случай матрицы масштабирования с коэффициентом масштаба равным 1 по всем осям. Также единичная матрица - это частный случай матрицы переноса, где (X, Y, Z) = (0, 0, 0) соответственно.</p>
<p><strong>В C++ :<&#47;strong></p>
<pre>&#47;&#47; добавьте #include <glm&#47;gtc&#47;matrix_transform.hpp> и #include <glm&#47;gtx&#47;transform.hpp><br />
glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);<&#47;pre></p>
<h2>Матрица поворота<&#47;h2><br />
Сложнее чем рассмотренные ранее. Мы опустим здесь детали, так как вам не обязательно знать это точно для ежедневного использования. Для получения более подробной информации можете перейти по ссылке <a href="http:&#47;&#47;www.cs.princeton.edu&#47;%7Egewang&#47;projects&#47;darth&#47;stuff&#47;quat_faq.html">Matrices and Quaternions FAQ<&#47;a> (довольно популярный ресурс и возможно там доступен ваш язык)</p>
<p><strong>В C++ :<&#47;strong></p>
<pre>&#47;&#47; добавьте #include <glm&#47;gtc&#47;matrix_transform.hpp> и #include <glm&#47;gtx&#47;transform.hpp><br />
glm::vec3 myRotationAxis( ??, ??, ??);<br />
glm::rotate( angle_in_degrees, myRotationAxis );<&#47;pre></p>
<h2>Собираем трансформации вместе<&#47;h2><br />
Итак, теперь мы умеем поворачивать, переносить и масштабировать наши векторы. Следующий шагом было бы неплохо объединить трансформации, что реализуется по следующей формуле:</p>
<pre>TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;<&#47;pre><br />
ВНИМАНИЕ! Эта формула на самом деле показывает, что сначала выполняется масштабирование, потом поворот и только в самую последнюю очередь выполняется перенос. Именно так работает перемножение матриц.</p>
<p>Обязательно запомните в каком порядке все это выполняется, потому что порядок действительно важен, в конце концов вы можете сами это проверить:</p>
<ul>
<li>Сделайте шаг вперед и повернитесь влево<&#47;li>
<li>Повернитесь влево и сделайте шаг вперед<&#47;li><br />
<&#47;ul><br />
Разницу действительно важно понимать, так как вы постоянно будете с этим сталкиваться. К примеру, когда вы будете работать с игровыми персонажами или какими-то объектами, то всегда сначала выполняйте масштабирование, потом поворот и только потом перенос.</p>
<p>Перемножение двух матриц очень похоже на перемножение матрицы и вектора, поэтому мы опустим описание, а если вы хотите узнать больше, то можете опять перейти по ссылке <a href="http:&#47;&#47;www.cs.princeton.edu&#47;%7Egewang&#47;projects&#47;darth&#47;stuff&#47;quat_faq.html">Matrices and Quaternions FAQ<&#47;a>.</p>
<p><strong>В C++, с GLM :<&#47;strong></p>
<pre>glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;<br />
glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;<&#47;pre><br />
<strong>В GLSL :<&#47;strong></p>
<pre>mat4 transform = mat2 * mat1;<br />
vec4 out_vec = transform * in_vec;<&#47;pre></p>
<h1>Мировая, видовая и проекционная матрицы<&#47;h1><br />
<em>До конца этого урока мы будем полагать, что знаем как отображать любимую 3D модель из Blender - обезьянку Suzanne.<&#47;em></p>
<p>Мировая, видовая и проекционная матрицы - это удобный инструмент для разделения трансформаций.</p>
<h2>Мировая матрица<&#47;h2><br />
Эта модель, также, как и наш красный треугольник задается множеством вершин, координаты которых заданы относительно центра объекта, т. е. вершина с координатами (0, 0, 0) будет находиться в центре объекта.</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model.png"><img title="model" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model.png" width="960" height="540" &#47;><&#47;a></p>
<p>&nbsp;</p>
<p>Далее мы бы хотели перемещать нашу модель, так как игрок управляет ей с помощью клавиатуры и мышки. Все, что мы делаем - это применяем масштабирование, потом поворот и перенос. Эти действия выполняются для каждой вершины, в каждом кадре (выполняются в GLSL, а не в C++!) и тем самым наша модель перемещается на экране.</p>
<p>&nbsp;</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;world.png"><img title="world" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;world.png" width="960" height="540" &#47;><&#47;a></p>
<p>&nbsp;</p>
<p>Теперь наши вершины в мировом пространстве. Это показывает черная стрелка на рисунке. Мы перешли из пространства объекта (все вершины заданы относительно центра объекта) к мировому пространству (все вершины заданы относительно центра мира)</p>
<p>&nbsp;</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world.png"><img title="model_to_world" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world.png" width="960" height="540" &#47;><&#47;a></p>
<p>Схематично это показывается так:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;M.png"><img title="M" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;M.png" width="240" height="148" &#47;><&#47;a></p>
<p>&nbsp;</p>
<h2>Видовая матрица<&#47;h2><br />
Еще раз процитируем Футураму:</p>
<blockquote><p>Движок не перемещает корабль. Корабль остается на том же месте, а движок перемещает вселенную вокруг него.<&#47;blockquote><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;camera.png"><img title="camera" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;camera.png" width="960" height="540" &#47;><&#47;a></p>
<p>Попробуйте представить это применительно к камере. Например, если вы хотите сфотографировать гору, то вы не перемещаете камеру, а перемещаете гору. Это не возможно в реальной жизни, но это невероятно просто в компьютерной графике.</p>
<p>Итак, изначально ваша камера находится в центре мировой системы координат. Чтобы переместить мир вам необходимо ввести еще одну матрицу. Допустим, что вы хотите переместить камеру на 3 юнита вправо (+X), что будет эквивалентом перемещения всего мира на 3 юнита влево (-X). В коде это выглядит так:</p>
<pre>&#47;&#47; Добавьте #include <glm&#47;gtc&#47;matrix_transform.hpp> и #include <glm&#47;gtx&#47;transform.hpp><br />
glm::mat4 ViewMatrix = glm::translate(-3.0f, 0.0f ,0.0f);<&#47;pre><br />
Опять же, изображение ниже полностью показывает это. Мы перешли из мировой системы координат (все вершины заданы относительно центра мировой системы) к системе координат камеры (все вершины заданы относительно камеры):</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera.png"><img title="model_to_world_to_camera" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera.png" width="960" height="540" &#47;><&#47;a></p>
<p>Ну и пока ваш мозг переваривает это, мы посмотрим на функцию, которую предоставляет нам GLM, а точнее на glm::LookAt:</p>
<pre>glm::mat4 CameraMatrix = glm::LookAt(<br />
    cameraPosition, &#47;&#47; Позиция камеры в мировом пространстве<br />
    cameraTarget,&nbsp;&nbsp; &#47;&#47; Указывает куда вы смотрите в мировом пространстве<br />
    upVector&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Вектор, указывающий направление вверх. Обычно (0, 1, 0)<br />
);<&#47;pre><br />
А вот диаграмма, которая показывает то, что мы делаем:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MV.png"><img title="MV" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MV.png" width="240" height="265" &#47;><&#47;a></p>
<p>&nbsp;</p>
<h2>Проекционная матрица<&#47;h2><br />
Итак, теперь мы находимся в пространстве камеры. Это означает, что вершина, которая получит координаты x == 0 и y == 0 будет отображаться по центру экрана. Однако, при отображении объекта огромную роль играет также дистанция до камеры (z). Для двух вершин, с одинаковыми x и y, вершина имеющая большее значение по z будет отображаться ближе, чем другая.</p>
<p>Это называется перспективной проекцией:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera_to_homogeneous.png"><img title="model_to_world_to_camera_to_homogeneous" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera_to_homogeneous.png" width="960" height="540" &#47;><&#47;a></p>
<p>&nbsp;</p>
<p>И к счастью для нас, матрица 4х4 может выполнить эту проекцию&sup1; :</p>
<pre>glm::mat4 projectionMatrix = glm::perspective(<br />
    FoV,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Горизонтальное поле обзора в градусах. Обычно между 90&deg; (очень широкое) и 30&deg; (узкое)<br />
    4.0f &#47; 3.0f, &#47;&#47; Отношение сторон. Зависит от размеров вашего окна. Заметьте, что 4&#47;3 == 800&#47;600 == 1280&#47;960<br />
    0.1f,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Ближняя плоскость отсечения. Должна быть больше 0.<br />
    100.0f&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &#47;&#47; Дальняя плоскость отсечения.<br />
);<&#47;pre><br />
Еще раз:</p>
<p>Мы перешли из Пространства Камеры (все вершины заданы относительно камеры) в Однородное пространство (все вершины находятся в небольшом кубе. Все, что находится внутри куба - выводится на экран).</p>
<p>Схема:</p>
<p>&nbsp;</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MVP.png"><img title="MVP" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MVP-235x300.png" width="235" height="300" &#47;><&#47;a></p>
<p>&nbsp;</p>
<p>Теперь посмотрим на следующие изображения, чтобы вы могли лучше понять что же происходит с проекцией. До проецирования мы имеем синие объекты в пространстве камеры, в то время как красная фигура показывает обзор камеры, т. е. все то, что камера видит.</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nondeforme.png"><img title="nondeforme" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nondeforme.png" width="960" height="540" &#47;><&#47;a></p>
<p>Применение Проекционной матрицы дает следующий эффект:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;homogeneous.png"><img title="homogeneous" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;homogeneous.png" width="960" height="540" &#47;><&#47;a></p>
<p>На этом изображении обзор камеры представляет собой куб и все объекты деформируются. Объекты, которые находятся ближе к камере отображаются большими, а те, которые дальше - маленькими. Прямо как в реальности!</p>
<p>Вот так это будет выглядеть:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;projected1.png"><img title="projected" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;projected1.png" width="602" height="588" &#47;><&#47;a></p>
<p>Изображение является квадратным, поэтому следующие математические трансформации применяются, чтобы растянуть изображение согласно актуальным размерам окна:</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;final1.png"><img title="final" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;final1.png" width="640" height="462" &#47;><&#47;a></p>
<p>И это изображение является тем, что на самом деле будет выведено.</p>
<h2>Объединяем трансформации : матрица ModelViewProjection<&#47;h2><br />
... Просто стандартные матричные преобразования, которые вы уже полюбили!</p>
<pre>&#47;&#47; C++ : вычисление матрицы<br />
glm::mat4 MVPmatrix = projection * view * model; &#47;&#47; Запомните! В обратном порядке!<&#47;pre></p>
<pre>&#47;&#47; GLSL : применение матрицы<br />
transformed_vertex = MVP * in_vertex;<&#47;pre></p>
<h1>Совмещаем все вместе<&#47;h1></p>
<ul>
<li>Первый шаг - создание нашей MVP матрицы. Это должно быть сделано для каждой модели, которую вы отображаете.<&#47;li><br />
<&#47;ul></p>
<pre>&#47;&#47; Проекционная матрица : 45&deg; поле обзора, 4:3 соотношение сторон, диапазон : 0.1 юнит <-> 100 юнитов<br />
glm::mat4 Projection = glm::perspective(45.0f, 4.0f &#47; 3.0f, 0.1f, 100.0f);<br />
&#47;&#47; Матрица камеры<br />
glm::mat4 View&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = glm::lookAt(<br />
    glm::vec3(4,3,3), &#47;&#47; Камера находится в мировых координатах (4,3,3)<br />
    glm::vec3(0,0,0), &#47;&#47; И направлена в начало координат<br />
    glm::vec3(0,1,0)&nbsp; &#47;&#47; "Голова" находится сверху<br />
);<br />
&#47;&#47; Матрица модели : единичная матрица (Модель находится в начале координат)<br />
glm::mat4 Model&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = glm::mat4(1.0f);&nbsp; &#47;&#47; Индивидуально для каждой модели</p>
<p>&#47;&#47; Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц<br />
glm::mat4 MVP&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; = Projection * View * Model;<&#47;pre></p>
<ul>
<li>Второй шаг - передать это в GLSL:<&#47;li><br />
<&#47;ul></p>
<pre>&#47;&#47; Получить хэндл переменной в шейдере<br />
&#47;&#47; Только один раз во время инициализации.<br />
GLuint MatrixID = glGetUniformLocation(programID, "MVP");</p>
<p>&#47;&#47; Передать наши трансформации в текущий шейдер<br />
&#47;&#47; Для каждой модели, которую вы выводите MVP будет различным (как минимум часть M)<br />
glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &amp;MVP[0][0]);<&#47;pre></p>
<ul>
<li>Третий шаг - используем полученные данные в GLSL, чтобы трансформировать наши вершины.<&#47;li><br />
<&#47;ul></p>
<pre>in vec3 vertexPosition_modelspace;<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>    &#47;&#47; Выходная позиция нашей вершины: MVP * position<br />
    vec4 v = vec4(vertexPosition_modelspace,1); &#47;&#47; Переводим в однородный 4D вектор, помните?<br />
    gl_Position = MVP * v;<br />
}<&#47;pre></p>
<ul>
<li>Готово! Теперь у нас есть такой же треугольник как и в Уроке 2, все так же находящийся в начале координат (0, 0, 0), но теперь мы его видим в перспективе из точки (4, 3, 3).<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;perspective_red_triangle.png"><img title="perspective_red_triangle" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;perspective_red_triangle-300x231.png" width="300" height="231" &#47;><&#47;a></p>
<p>В Уроке 6 вы научитесь изменять эти значения динамически, используя клавиатуру и мышь, чтобы создать камеру, которую вы привыкли видеть в играх. Но для начала мы узнаем как придать нашем моделям цвета (Урок 4) и текстуры (Урок 5).</p>
<h1>Задания<&#47;h1></p>
<ul>
<li>Попробуйте поменять значения glm::perspective<&#47;li>
<li>Вместо использования перспективной проекции попробуйте использовать ортогональную (glm:ortho)<&#47;li>
<li>Измените ModelMatrix для перемещения, поворота и масштабирования треугольника<&#47;li>
<li>Используйте предыдущее задание, но с разным порядком операций. Обратите внимание на результат.<&#47;li><br />
<&#47;ul></p>
