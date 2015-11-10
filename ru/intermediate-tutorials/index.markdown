---
layout: page
status: publish
published: true
title: Расширенные уроки
date: '2014-04-27 12:27:37 +0100'
date_gmt: '2014-04-27 12:27:37 +0100'
categories: []
tags: []
comments: []
language: ru
---
<p>Вы можете следовать этим урокам в любом порядке</p>


{% assign sorted_pages = site.pages | sort:"order" %}
{% for p in sorted_pages %}
   {% assign splt = p.url | split: page.url %}
   {% if splt.size == 2 and splt[0] == '' %}
      {% assign slash = splt[1] | split: '/' %}
{% if slash.size == 1 %}      
- <a class="page-link" href="{{p.url | prepend: site.baseurl}}">{{p.title}}</a>
{% else %}
   - <a class="page-link" href="{{p.url | prepend: site.baseurl}}">{{p.title}}</a>
{% endif %}
   {% endif %}
{% endfor %}
