---
layout: page
status: publish
published: true
title: OpenGL基础知识
date: '2012-11-06 15:38:44 +0100'
date_gmt: '2012-11-06 15:38:44 +0100'
categories: []
tags: []
language: cn
---
<p>请按课程顺序学习！</p>
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
