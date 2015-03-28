---
layout: page
status: publish
published: true
title: "主页"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 720
wordpress_url: http://www.opengl-tutorial.org/?page_id=720
date: '2012-11-15 01:43:47 +0100'
date_gmt: '2012-11-15 01:43:47 +0100'
categories: []
tags: []
---
<p>本站致力于为大家提供<strong>OpenGL3.3+教程<&#47;strong>！</p>
<p>所有源代码可在<a title="Download" href="&#47;?page_id=200">这里<&#47;a>下载。</p>
<p>您若有任何问题、建议、错误报告，可联系<a href="mailto:contact@opengl-tutorial.org">contact@opengl-tutorial.org<&#47;a>。</p>
<p>如果您喜欢我们的教程，别忘了帮我们宣传一下。</p>

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
