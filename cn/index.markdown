---
layout: page
status: publish
published: true
title: "主页"
date: '2012-11-15 01:43:47 +0100'
date_gmt: '2012-11-15 01:43:47 +0100'
categories: []
tags: []
language: cn
---
本站致力于为大家提供**OpenGL3.3+教程**！

所有源代码可在[这里]({{ site.baseurl }}/cn/download)下载。

您若有任何问题、建议、错误报告，可联系<a href="mailto:contact@opengl-tutorial.org">contact@opengl-tutorial.org</a>。

如果您喜欢我们的教程，别忘了帮我们宣传一下。

<div class="home">

  <h1>News</h1>

  <ul class="posts">
    {% for post in site.posts %}
      <li>
        <span class="post-date">{{ post.date | date: "%b %-d, %Y" }}</span>
        <a class="post-link" href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a>
      </li>
    {% endfor %}
  </ul>

  <p class="rss-subscribe">subscribe <a href="{{ "/feed.xml" | prepend: site.baseurl }}">via RSS</a></p>

</div>
