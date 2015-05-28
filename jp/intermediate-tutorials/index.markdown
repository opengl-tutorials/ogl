---
layout: page
status: publish
published: true
title: 中級編チュートリアル
author:
  display_name: suzuichi
  login: suzuichi
  email: suzuichiblog@gmail.com
  url: ''
author_login: suzuichi
author_email: suzuichiblog@gmail.com
wordpress_id: 1315
wordpress_url: http://www.opengl-tutorial.org/?page_id=1315
date: '2014-07-30 03:02:42 +0100'
date_gmt: '2014-07-30 03:02:42 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>お好きな順番で読んでください。</p>

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
