---
layout: printer
sitemap: no
permalink: /print/
---

{% assign lg = "" %}
{% if page.language %}
  {% capture lg %}{{page.language}}/{% endcapture %}
{% endif %}

<div style="font-size:3em;text-align:center;">Beginners Tutorials</div>
<div style="page-break-before:always"> </div>

{% assign sorted_pages = site.pages | sort:"order" %}
{% capture tuts_root %}/{{ lg }}beginners-tutorials/{% endcapture %}
{% for p in sorted_pages %}
  {% assign splt = p.url | split: tuts_root %}
  {% if splt.size == 2 and splt[0] == '' and p.layout == 'tutorial' %}
  <div class="post">
    <header class="post-header">
      <h1>{{ p.title }}</h1>
    </header>
    <article class="post-content">
      {{ p.content | markdownify }}
    </article>
  </div>
  <div style="page-break-before:always"> </div>
  {% endif %}
{% endfor %}

<div style="font-size:3em;text-align:center;">Intermediate Tutorials</div>
<div style="page-break-before:always"> </div>

{% assign sorted_pages = site.pages | sort:"order" %}
{% capture tuts_root %}/{{ lg }}intermediate-tutorials/{% endcapture %}
{% for p in sorted_pages %}
  {% assign splt = p.url | split: tuts_root %}
  {% if splt.size == 2 and splt[0] == '' and p.layout == 'tutorial' %}
  <div class="post">
    <header class="post-header">
      <h1>{{ p.title }}</h1>
    </header>
    <article class="post-content">
      {{ p.content | markdownify }}
    </article>
  </div>
  <div style="page-break-before:always"> </div>
  {% endif %}
{% endfor %}

<div style="font-size:3em;text-align:center;">Miscellaneous</div>
<div style="page-break-before:always"> </div>

{% assign sorted_pages = site.pages | sort:"order" %}
{% capture tuts_root %}/{{ lg }}miscellaneous/{% endcapture %}
{% for p in sorted_pages %}
  {% assign splt = p.url | split: tuts_root %}
  {% if splt.size == 2 and splt[0] == '' and p.print == true %}
  <div class="post">
    <header class="post-header">
      <h1>{{ p.title }}</h1>
    </header>
    <article class="post-content">
      {{ p.content | markdownify }}
    </article>
  </div>
  <div style="page-break-before:always"> </div>
  {% endif %}
{% endfor %}
