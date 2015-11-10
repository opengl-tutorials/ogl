---
layout: page
status: publish
published: true
title: OpenGLの基礎
date: '2014-06-25 08:41:20 +0100'
date_gmt: '2014-06-25 08:41:20 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>上から順番に読んでください！</p>
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
