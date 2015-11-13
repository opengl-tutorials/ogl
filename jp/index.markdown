---
layout: page
status: publish
published: true
title: Home
date: '2011-05-07 11:00:04 +0200'
date_gmt: '2011-05-07 11:00:04 +0200'
categories: []
tags: []
language: jp
---
このサイトは **OpenGL 3.3** 以降の **チュートリアル** を扱っています！

完全なソースコードは[ここ]({{ site.baseurl }}/jp/download)から利用可能です。

何か質問や意見、バグ報告、その他何かあればお気軽にご連絡ください : <a href="mailto:contact@opengl-tutorial.org">contact@opengl-tutorial.org</a>.

日本語に関する意見などは私(翻訳者)の[ブログ](http://suzuichibolgpg.blog.fc2.com&#47;blog-entry-155.html)か<a href="mailto:suzuichiblog+mot@gmail.com">メール</a>へご連絡ください。

このサイトが気に入ったなら、どうぞ世界に広めてください！

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
