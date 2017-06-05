---
layout: printer
sitemap: no
permalink: /print/
---

{% assign lg = "" %}
{% if page.language %}
  {% capture lg %}{{page.language}}/{% endcapture %}
{% endif %}

{% assign sorted_pages = site.pages | sort:"order" %}
{% capture tuts_root %}/{{ lg }}beginners-tutorials/{% endcapture %}
{% for p in sorted_pages %}
  {% assign splt = p.url | split: tuts_root %}
  {% if splt.size == 2 and splt[0] == '' %}
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
