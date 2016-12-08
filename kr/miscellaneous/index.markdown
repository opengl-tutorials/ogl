---
layout: page
type: section
status: publish
published: true
title: Miscellaneous
date: '2011-05-08 08:24:33 +0200'
date_gmt: '2011-05-08 08:24:33 +0200'
categories: []
tags: []
---

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

