---
layout: page
status: publish
published: true
title: Home
date: '2011-05-07 11:00:04 +0200'
date_gmt: '2011-05-07 11:00:04 +0200'
categories: []
tags: []
language: ru
---
Этот сайт посвящен **урокам OpenGL 3.3** и выше!

Полный исходный код уроков доступен []здесь](({{ site.baseurl }}/ru/download))

По любым вопросам, багам, заметкам вы можете всегда обратиться по этому адресу: <a href="mailto:contact@opengl-tutorial.org">contact@opengl-tutorial.org</a>.

*От переводчика:*

*Я не являюсь профессионалом в программировании OpenGL и компьютерной графики, поэтому, пожалуйста, если вы заметите ошибку или какую-либо неточность, то сообщите мне об этом по адресу:*

*<a href="mailto:fdevrnd@mail.ru">fdevrnd@mail.ru</a>*

<div class="home">

  <h1>News</h1>

  <ul class="posts">
    {% for post in site.posts %}
      <li>
        <span class="post-date">{{ post.date | date: "%b %-d, %Y" }}</span>
        <a class="post-link" href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a>
      </li>
    {% endfor %}
  </ul>

  <p class="rss-subscribe">subscribe <a href="{{ "/feed.xml" | prepend: site.baseurl }}">via RSS</a></p>

</div>
