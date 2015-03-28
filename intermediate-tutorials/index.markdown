---
layout: page
type: section
status: publish
published: true
title: Intermediate Tutorials
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 140
wordpress_url: http://www.opengl-tutorial.org/?page_id=140
date: '2011-05-07 10:45:46 +0200'
date_gmt: '2011-05-07 10:45:46 +0200'
categories: []
tags: []
---
<p>Follow them in any order</p>
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
