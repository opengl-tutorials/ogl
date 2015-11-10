---
layout: page
status: publish
published: true
title: Базовые уроки
date: '2014-05-05 22:37:09 +0100'
date_gmt: '2014-05-05 22:37:09 +0100'
categories: []
tags: []
comments: []
language: ru
---
<p>Здесь представлены базовые уроки OpenGL.<br />
Пожалуйста, изучайте их в строгом порядке.</p>

<ul class="tuto">
{% assign sorted_pages = site.pages | sort:"order" %}
{% for p in sorted_pages %}
  {% assign splt = p.url | split: page.url %}
  {% if splt.size == 2 and splt[0] == '' %}
    <li>
      <a class="page-link" href="{{p.url | prepend: site.baseurl}}">{{p.title}}</a>
    </li>
  {% endif %}
{% endfor %}
</ul>
