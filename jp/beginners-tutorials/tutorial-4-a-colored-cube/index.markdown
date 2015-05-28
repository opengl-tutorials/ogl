---
layout: page
status: publish
published: true
title: チュートリアル4：色つきの立方体
author:
  display_name: suzuichi
  login: suzuichi
  email: suzuichiblog@gmail.com
  url: ''
author_login: suzuichi
author_email: suzuichiblog@gmail.com
wordpress_id: 1311
wordpress_url: http://www.opengl-tutorial.org/?page_id=1311
date: '2014-07-30 02:59:12 +0100'
date_gmt: '2014-07-30 02:59:12 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>4回目のチュートリアルにようこそ！ここでは次のことを行います。</p>
<ul>
<li>単純な三角形ではなく、立方体を描きます。<&#47;li>
<li>ファンシーな色を塗ります。<&#47;li>
<li>Zバッファとは何かを学びます。<&#47;li><br />
<&#47;ul></p>
<h1>立方体の描画<&#47;h1><br />
立方体は6枚の正方形から構成されています。OpenGLは三角形しか認識しないので、12枚の三角形を描く必要があります。つまり各面に2枚の三角形です。三角形でしたように、頂点を定義します。</p>
<pre class="brush: cpp">&#47;&#47; 頂点。3つの連続する数字は3次元の頂点です。3つの連続する頂点は三角形を意味します。<br />
&#47;&#47; 立方体は、それぞれが2枚の三角形からなる6面から成ります。だから6*2=12枚の三角形と12*3個の頂点を作ります。<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
    -1.0f,-1.0f,-1.0f, &#47;&#47; 三角形1:開始<br />
    -1.0f,-1.0f, 1.0f,<br />
    -1.0f, 1.0f, 1.0f, &#47;&#47; 三角形1:終了<br />
    1.0f, 1.0f,-1.0f, &#47;&#47; 三角形2:開始<br />
    -1.0f,-1.0f,-1.0f,<br />
    -1.0f, 1.0f,-1.0f, &#47;&#47; 三角形2:終了<br />
    1.0f,-1.0f, 1.0f,<br />
    -1.0f,-1.0f,-1.0f,<br />
    1.0f,-1.0f,-1.0f,<br />
    1.0f, 1.0f,-1.0f,<br />
    1.0f,-1.0f,-1.0f,<br />
    -1.0f,-1.0f,-1.0f,<br />
    -1.0f,-1.0f,-1.0f,<br />
    -1.0f, 1.0f, 1.0f,<br />
    -1.0f, 1.0f,-1.0f,<br />
    1.0f,-1.0f, 1.0f,<br />
    -1.0f,-1.0f, 1.0f,<br />
    -1.0f,-1.0f,-1.0f,<br />
    -1.0f, 1.0f, 1.0f,<br />
    -1.0f,-1.0f, 1.0f,<br />
    1.0f,-1.0f, 1.0f,<br />
    1.0f, 1.0f, 1.0f,<br />
    1.0f,-1.0f,-1.0f,<br />
    1.0f, 1.0f,-1.0f,<br />
    1.0f,-1.0f,-1.0f,<br />
    1.0f, 1.0f, 1.0f,<br />
    1.0f,-1.0f, 1.0f,<br />
    1.0f, 1.0f, 1.0f,<br />
    1.0f, 1.0f,-1.0f,<br />
    -1.0f, 1.0f,-1.0f,<br />
    1.0f, 1.0f, 1.0f,<br />
    -1.0f, 1.0f,-1.0f,<br />
    -1.0f, 1.0f, 1.0f,<br />
    1.0f, 1.0f, 1.0f,<br />
    -1.0f, 1.0f, 1.0f,<br />
    1.0f,-1.0f, 1.0f<br />
};<&#47;pre><br />
OpenGLバッファは、標準の関数によって作成され、バインドされ、満たされ、設定されます。(glGenBuffers, glBindBuffer, glBufferData, glVertexAttribPointer):記憶が怪しければチュートリアル2を見てください。描画コールはどれも変更しません。あなたはただ描画したい頂点の正しい数値をセットする必要があるだけです。</p>
<pre class="brush: cpp">&#47;&#47; 三角形の描画！<br />
glDrawArrays(GL_TRIANGLES, 0, 12*3); &#47;&#47; 12*3頂点は0から始まる -> 12枚の三角形 -> 6枚の正方形<&#47;pre><br />
このコードについて少し説明します。</p>
<ul>
<li>ここでは固定した3Dモデルを扱います。モデルを変更するためには、ソースコードを変更し、再コンパイルし、うまくいくことを望むことです。チュートリアル7では動的にモデルをロードする方法を学びます。<&#47;li>
<li>各頂点は少なくとも3回書く必要があります。(上のコードで"-1.0f,-1.0f,-1.0f"を検索してみてください)。これはメモリの無駄使いです。チュートリアル9ではこれに対処する方法を学びます。<&#47;li><br />
<&#47;ul><br />
これで真っ白な三角形を描く準備が整いました。シェーダを動かしましょう！トライしてみましょう:)</p>
<h1>色の追加<&#47;h1><br />
色は、概念的には、位置とまったく同じです。つまりただのデータです。OpenGLの用語でいえば"属性"です。実は、glEnableVertexAttribArray() と glVertexAttribPointer()で、既に使っています。他の属性も追加しましょう。コードは同じように書けます。</p>
<p>最初に、色を宣言します。各頂点に3つ組のRGBが一つあります。ここでは、私がランダムに作りました。だから見栄えはあまりよくありません。しかし、あなたはよりよくすることができるでしょう。例えば、頂点の位置をそれ自身の色にコピーすることでも実現できるでしょう。</p>
<pre class="brush: cpp">&#47;&#47; 各頂点に一つの色。これらはランダムに作られました。<br />
static const GLfloat g_color_buffer_data[] = {<br />
    0.583f,  0.771f,  0.014f,<br />
    0.609f,  0.115f,  0.436f,<br />
    0.327f,  0.483f,  0.844f,<br />
    0.822f,  0.569f,  0.201f,<br />
    0.435f,  0.602f,  0.223f,<br />
    0.310f,  0.747f,  0.185f,<br />
    0.597f,  0.770f,  0.761f,<br />
    0.559f,  0.436f,  0.730f,<br />
    0.359f,  0.583f,  0.152f,<br />
    0.483f,  0.596f,  0.789f,<br />
    0.559f,  0.861f,  0.639f,<br />
    0.195f,  0.548f,  0.859f,<br />
    0.014f,  0.184f,  0.576f,<br />
    0.771f,  0.328f,  0.970f,<br />
    0.406f,  0.615f,  0.116f,<br />
    0.676f,  0.977f,  0.133f,<br />
    0.971f,  0.572f,  0.833f,<br />
    0.140f,  0.616f,  0.489f,<br />
    0.997f,  0.513f,  0.064f,<br />
    0.945f,  0.719f,  0.592f,<br />
    0.543f,  0.021f,  0.978f,<br />
    0.279f,  0.317f,  0.505f,<br />
    0.167f,  0.620f,  0.077f,<br />
    0.347f,  0.857f,  0.137f,<br />
    0.055f,  0.953f,  0.042f,<br />
    0.714f,  0.505f,  0.345f,<br />
    0.783f,  0.290f,  0.734f,<br />
    0.722f,  0.645f,  0.174f,<br />
    0.302f,  0.455f,  0.848f,<br />
    0.225f,  0.587f,  0.040f,<br />
    0.517f,  0.713f,  0.338f,<br />
    0.053f,  0.959f,  0.120f,<br />
    0.393f,  0.621f,  0.362f,<br />
    0.673f,  0.211f,  0.457f,<br />
    0.820f,  0.883f,  0.371f,<br />
    0.982f,  0.099f,  0.879f<br />
};<&#47;pre><br />
バッファは前とまったく同じ方法で、作成され、バインドされ、満たされます。</p>
<pre class="brush: cpp">GLuint colorbuffer;<br />
glGenBuffers(1, &amp;colorbuffer);<br />
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);<&#47;pre><br />
設定も同様です。</p>
<pre class="brush: cpp">&#47;&#47; 2nd attribute buffer : colors<br />
glEnableVertexAttribArray(1);<br />
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);<br />
glVertexAttribPointer(<br />
    1,                                &#47;&#47; 属性。1という数字に意味はありません。ただしシェーダのlayoutとあわせる必要があります。<br />
    3,                                &#47;&#47; サイズ<br />
    GL_FLOAT,                         &#47;&#47; タイプ<br />
    GL_FALSE,                         &#47;&#47; 正規化？<br />
    0,                                &#47;&#47; ストライド<br />
    (void*)0                          &#47;&#47; 配列バッファオフセット<br />
);<&#47;pre><br />
ここで、頂点バッファ内で、追加のバッファへのアクセスするために次のものを書きます。</p>
<pre class="brush: vs">&#47;&#47; ここでの "1" はglVertexAttribPointerの "1" と同じにします。<br />
layout(location = 1) in vec3 vertexColor;<&#47;pre><br />
今回は、頂点シェーダではファンシーにするための作業は何もしません。ただフラグメントシェーダへ送るだけです。</p>
<pre class="brush: vs">&#47;&#47; アウトプットデータ。各頂点に書き込まれます。<br />
out vec3 fragmentColor;</p>
<p>void main(){</p>
<p>    [...]</p>
<p>    &#47;&#47; 各フラグメントの色を作るために<br />
    &#47;&#47; 各頂点の色は書き込まれます。<br />
    fragmentColor = vertexColor;<br />
}<&#47;pre><br />
フラグメントシェーダでは再びfragmentColorを宣言します。</p>
<pre class="brush: fs">&#47;&#47; 頂点シェーダから書き込まれた色<br />
in vec3 fragmentColor;<&#47;pre><br />
...そして、最終的なアウトプットカラーにコピーします。</p>
<pre class="brush: fs">&#47;&#47; アウトプットデータ<br />
out vec3 color;</p>
<p>void main(){<br />
    &#47;&#47; アウトプットカラー = 頂点シェーダで指定された、<br />
    &#47;&#47; 周辺の3つの頂点間で書き込まれた色<br />
    color = fragmentColor;<br />
}<&#47;pre><br />
これが出力結果です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;missing_z_buffer.png"><img class="alignnone size-medium wp-image-107" title="missing_z_buffer" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;missing_z_buffer-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<p>なんともひどい出来です。この現象を理解するために、"遠く"の三角形と"近く"の三角形を描いたときに何が起こるかを見ましょう。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;FarNear.png"><img class="alignnone size-full wp-image-109" title="FarNear" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;FarNear.png" alt="" width="189" height="94" &#47;><&#47;a></p>
<p>OKでしょう。では、"遠く"の三角形を最後に書いた場合はどうでしょう。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;NearFar.png"><img class="alignnone size-full wp-image-110" title="NearFar" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;NearFar.png" alt="" width="189" height="94" &#47;><&#47;a></p>
<p>"近く"の三角形に上書きされます。たとえその後ろにあると想定していてもです。これが私たちの立方体でも起きています。隠れると想定されている面がありますが、最後に描画されたために見えてしまっています。Zバッファに助けを求めましょう！</p>
<p><em>メモ１<&#47;em> : 問題がないように見えるなら、カメラの位置を(4,3,-3)に変更してください。</p>
<p><em>メモ2<&#47;em> : "色は位置のように属性だ"というのなら、なぜ位置ではしなかったout vec3 fragmentColorとin vec3 fragmentColorを宣言する必要があるのでしょうか？なぜなら、実は位置は少し特別だからです。位置は唯一強制されるものだからです。(もし位置を宣言しなければ、OpenGLはどこに三角形を描けばいいのか分かりません！)だから頂点シェーダでは、gl_Positionは"組み込み"の変数です。</p>
<h1>Zバッファ<&#47;h1><br />
この問題を解決するには、バッファ内の各フラグメントのデプス(例えば"Z")要素を保存することです。そして描画するごとに、まず描画すべきかどうかをチェックします。(例えば、新しいフラグメントは以前のものよりも近いかどうか。)</p>
<p>自分自身でも出来ますが、ハードウェア自身にその作業をさせるほうがよりシンプルです。</p>
<pre class="brush: cpp">&#47;&#47; デプステストを有効にする<br />
glEnable(GL_DEPTH_TEST);<br />
&#47;&#47; 前のものよりもカメラに近ければ、フラグメントを受け入れる<br />
glDepthFunc(GL_LESS);<&#47;pre><br />
色だけでなくデプスも毎フレームクリアする必要があります。</p>
<pre class="brush: cpp">&#47;&#47; スクリーンをクリアする<br />
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);<&#47;pre><br />
この問題を解決するにはこれで充分です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;one_color_per_vertex.png"><img class="alignnone size-medium wp-image-108" title="one_color_per_vertex" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;one_color_per_vertex-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<h1>演習<&#47;h1></p>
<ul>
<li>立方体と三角形を異なった位置に描画しましょう。そのためには、2つのMVP行列を作り、メインループで2回描画コールするでしょう。しかしシェーダは一つだけのはずです。<&#47;li><br />
<&#47;ul></p>
<ul>
<li>自分自身で色の値を作りましょう。例：実行ごとに変わるようにランダムにする、頂点の位置によって変わるようにする、その2つを合わせるなどです。他にもクリエイティブなアイディアがあるでしょう。 :) C言語を知らない人のために、文法を示しておきます。<&#47;li><br />
<&#47;ul></p>
<pre class="brush: cpp">static GLfloat g_color_buffer_data[12*3*3];<br />
for (int v = 0; v < 12*3 ; v++){<br />
    g_color_buffer_data[3*v+0] = ここに赤色<br />
    g_color_buffer_data[3*v+1] = ここに緑色<br />
    g_color_buffer_data[3*v+2] = ここに青色<br />
}<&#47;pre></p>
<ul>
<li>それが出来たら、フレームごとに色を変えてみましょう。glBufferDataを毎フレーム呼ぶ必要があるでしょう。適切なバッファをバインド(glBindBuffer)したかを確かめましょう！<&#47;li><br />
<&#47;ul></p>
