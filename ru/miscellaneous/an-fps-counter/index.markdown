---
layout: page
status: publish
published: true
title: Счетчик кадров в секунду (FPS)
date: '2012-01-28 16:24:41 +0100'
date_gmt: '2012-01-28 16:24:41 +0100'
categories: []
order: 40
tags: []
language: ru
---

В графике реального времени важно следить за производительностью. Хорошая практика: выбрать целевой FPS (обычно 60 или 30) и сделать все возможное, чтобы придерживаться его.

Счетчик FPS выглядит так :
```

 double lastTime = glfwGetTime();
 int nbFrames = 0;

 do{

     // Measure speed
     double currentTime = glfwGetTime();
     nbFrames++;
     if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
         // printf and reset timer
         printf("%f ms/frame\n", 1000.0/double(nbFrames));
         nbFrames = 0;
         lastTime += 1.0;
     }

     ... rest of the main loop
```

В этом коде есть странная вещь. Он отображает время в миллисекундах, необходимое для отрисовки кадра (усредненного на 1 секунду) вместо количества кадров, которое было нарисовано за последнюю секунду.

Это на самом деле **намного лучше**. Не полагайтесь на FPS. Никогда. FramesPerSecond = 1 / SecondsPerFrame, так что это обратная связь, и мы, люди, плохо понимаем это отношение. Давайте рассмотрим пример.

Вы пишете отличную функцию рендеринга, которая работает при 1000 FPS (1 мс/кадр). Но вы забыли небольшое вычисление в шейдере, что добавляет дополнительную расходы в 0,1 мс. И бум, 1 / 0.0011 = 900. Вы просто потеряли 100FPS. Мораль: **никогда не использовать FPS для анализа производительности.**

Если вы хотите сделать игру с 60 кадрами в секунду, ваша цель - 16.6666 мс; Если вы хотите сделать игру с 30 fps, ваша цель - 33.3333 мс. Это все, что вам нужно знать.

Этот код доступен во всех учебниках, начиная с [Tutorial 9 : VBO indexing](http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/); см. tutorial09_vbo_indexing/tutorial09.cpp . Другие инструменты производительности доступны в [Tools - Debuggers](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/#header-4).
