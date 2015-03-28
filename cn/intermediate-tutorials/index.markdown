---
layout: page
status: publish
published: true
title: "中级教程"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 834
wordpress_url: http://www.opengl-tutorial.org/?page_id=834
date: '2014-12-08 20:44:21 +0100'
date_gmt: '2014-12-08 20:44:21 +0100'
categories: []
tags: []
language: cn
---
<p>在任何順序做教程</p>
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
