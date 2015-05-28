---
layout: page
status: publish
published: true
title: チュートリアル5：テクスチャされた立方体
author:
  display_name: suzuichi
  login: suzuichi
  email: suzuichiblog@gmail.com
  url: ''
author_login: suzuichi
author_email: suzuichiblog@gmail.com
wordpress_id: 1312
wordpress_url: http://www.opengl-tutorial.org/?page_id=1312
date: '2014-07-30 03:00:11 +0100'
date_gmt: '2014-07-30 03:00:11 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>このチュートリアルでは次のことを学びます。</p>
<ul>
<li>UV座標とは何か<&#47;li>
<li>テクスチャをどうやってロードするか<&#47;li>
<li>それらをOpenGLでどう使うか<&#47;li>
<li>フィルタリングとミップマップとは何か、そしてどう使うか<&#47;li>
<li>どのようにGLFWでよりロバストにテクスチャをロードするか<&#47;li>
<li>アルファチャネルとは何か<&#47;li><br />
<&#47;ul></p>
<h1>UV座標とは<&#47;h1><br />
メッシュをテクスチャするとき、各三角形に画像のどの部分を使うかをOpenGLに伝える手段が必要です。これをUV座標を使って行います。</p>
<p>各頂点は、その位置の上に、UとVという組になっている数値を持っています。これらの座標はテクスチャにアクセスするときに次のように使います。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;UVintro.png"><img class="alignnone size-full wp-image-116" title="UVintro" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;UVintro.png" width="662" height="337" &#47;><&#47;a></p>
<p>三角形の上にテクスチャがどのようにゆがんでいるかを確認してください。</p>
<h1>BMP画像のロード<&#47;h1><br />
BMPファイルフォーマットは複雑でないことが知られています。また多くのライブラリも存在します。しかし、ロード作業はとてもシンプルで、ブラックボックス内でどのように動いているかを理解する助けにもなります。だから、どのように動くかを知るためにも、BMPファイルローダを書きましょう。<span style="text-decoration: underline">ただし二度と使うことはないでしょう。<&#47;span>.</p>
<p>ここにロード関数の宣言が在ります。</p>
<pre class="brush: cpp">GLuint loadBMP_custom(const char * imagepath);<&#47;pre><br />
これは次のように使います。</p>
<pre class="brush: cpp">GLuint image = loadBMP_custom(".&#47;my_texture.bmp");<&#47;pre><br />
BMPファイルをどのように読み込むかを見ていきましょう。</p>
<p>まず、いくつかのデータが必要です。ファイルを読むときにこれらの変数はセットされます。</p>
<pre class="brush: cpp">&#47;&#47; BMPファイルのヘッダから読み込まれるデータ<br />
unsigned char header[54]; &#47;&#47; 各BMPファイルは54バイトのヘッダから始まります。<br />
unsigned int dataPos;     &#47;&#47; 実際のデータがファイルのどの位置にあるか<br />
unsigned int width, height;<br />
unsigned int imageSize;   &#47;&#47; = 横*高さ*3<br />
&#47;&#47; 実際のRGBデータ<br />
unsigned char * data;<&#47;pre><br />
実際にファイルを開く必要があります。</p>
<pre class="brush: cpp">&#47;&#47; ファイルを開きます。<br />
FILE * file = fopen(imagepath,"rb");<br />
if (!file)							    {printf("画像が開けませんでした。n"); return 0;}<&#47;pre><br />
ファイルの始まりは、54バイトのヘッダです。それには"これが本当にBMPファイルか？"、画像のサイズ、ピクセルごとのビット数などの情報を含んでいます。このヘッダを読み込みましょう。</p>
<pre class="brush: cpp">if ( fread(header, 1, 54, file)!=54 ){ &#47;&#47; 54バイト読み込めなければ、問題があります。<br />
    printf("BMPファイルではありません。n");<br />
    return false;<br />
}<&#47;pre><br />
ヘッダは常にBMで始まります。実は、16進数エディタで.BMPファイルを開いたときに得られるものが、ここにあります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;hexbmp.png"><img class="alignnone size-full wp-image-662" title="hexbmp" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;hexbmp.png" width="541" height="128" &#47;><&#47;a></p>
<p>だから最初の2バイトが本当に'B'と'M'で始まるかを確認する必要があります。</p>
<pre class="brush: cpp">if ( header[0]!='B' || header[1]!='M' ){<br />
    printf("BMPファイルではありません。n");<br />
    return 0;<br />
}<&#47;pre><br />
ここで画像のサイズやデータの位置などをロードします。</p>
<pre class="brush: cpp">&#47;&#47; バイト配列から整数を読み込む<br />
dataPos    = *(int*)&amp;(header[0x0A]);<br />
imageSize  = *(int*)&amp;(header[0x22]);<br />
width      = *(int*)&amp;(header[0x12]);<br />
height     = *(int*)&amp;(header[0x16]);<&#47;pre><br />
足りない情報があれば、自分で作ります。</p>
<pre class="brush: cpp">&#47;&#47; BMPファイルの中にはミスフォーマットがあります。その情報を推測します。<br />
if (imageSize==0)    imageSize=width*height*3; &#47;&#47; 3 : 1バイトは赤、緑、青の各色です。<br />
if (dataPos==0)      dataPos=54; &#47;&#47; これでBMPヘッダは終わりです。<&#47;pre><br />
これで画像のサイズが分かったので、画像を読み込むためにメモリを確保します。そして画像を読み込みます。</p>
<pre class="brush: cpp">&#47;&#47; バッファを作る<br />
data = new unsigned char [imageSize];</p>
<p>&#47;&#47; ファイルから実際のデータをバッファに読み込む<br />
fread(data,1,imageSize,file);</p>
<p>&#47;&#47;すべてはメモリ上にあるので、ファイルは閉じます。<br />
fclose(file);<&#47;pre><br />
ここからはOpenGLのパートです。テクスチャを作るのは頂点バッファを作るのにとても似ています。つまり、テクスチャを作り、バインドし、それを満たし、設定します。</p>
<p>glTexImage2Dでは、GL_RGBは3要素の色についてで、GL_BGRはRAM上で実際にどのように表現されるかを示しています。実は、BMPファイルは赤->緑->青の順ではなく、青->緑->赤の順で格納されています。だからOpenGLにそのように伝える必要があります。</p>
<pre class="brush: cpp">&#47;&#47; ひとつのOpenGLテクスチャを作ります。<br />
GLuint textureID;<br />
glGenTextures(1, &amp;textureID);</p>
<p>&#47;&#47; 新たに作られたテクスチャを"バインド"します。つまりここから後のテクスチャ関数はこのテクスチャを変更します。<br />
glBindTexture(GL_TEXTURE_2D, textureID);</p>
<p>&#47;&#47; OpenGLに画像を渡します。<br />
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);</p>
<p>glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);<&#47;pre><br />
最後の2行は後で説明します。ところで、C++サイドでは、テクスチャをロードする新たな関数を使えます。</p>
<pre class="brush: cpp">GLuint Texture = loadBMP_custom("uvtemplate.bmp");<&#47;pre><br />
もう一つとても重要なことは、テクスチャのサイズは2のべき乗でなければなりません。</p>
<ul>
<li>良い : 128*128*, 256*256, 1024*1024, 2*2...<&#47;li>
<li>悪い : 127*128, 3*5, ...<&#47;li>
<li>良いが不自然 : 128*256<&#47;li><br />
<&#47;ul></p>
<h1>OpenGLでのテクスチャの使用<&#47;h1><br />
はじめにフラグメントシェーダを見ていきましょう。これは簡単です。</p>
<pre class="brush: fs">#version 330 core</p>
<p>&#47;&#47; 頂点シェーダからの値を書き込みます<br />
in vec2 UV;</p>
<p>&#47;&#47; アウトプットデータ<br />
out vec3 color;</p>
<p>&#47;&#47; すべてのメッシュで一定の値<br />
uniform sampler2D myTextureSampler;</p>
<p>void main(){</p>
<p>    &#47;&#47; アウトプットカラー = 指定したUV座標のテクスチャの色<br />
    color = texture( myTextureSampler, UV ).rgb;<br />
}<&#47;pre><br />
3点述べておきます。</p>
<ul>
<li>フラグメントシェーダはUV座標が必要です。これは普通のことです。<&#47;li>
<li>どのテクスチャにアクセスするかを知るために、フラグメントシェーダは"sample2D"も必要です。(同じシェーダで複数のテクスチャにアクセスすることも可能です。)<&#47;li>
<li>最後に、テクスチャにアクセスするのはtexture()で行います。この関数はvec4型の(R,G,B,A)を返します。Aについてはまた説明します。<&#47;li><br />
<&#47;ul><br />
頂点シェーダも簡単です。UV座標をただフラグメントシェーダに送るだけです。</p>
<pre class="brush: vs">#version 330 core</p>
<p>&#47;&#47; インプット頂点データ。このシェーダの実行ごとに異なります。<br />
layout(location = 0) in vec3 vertexPosition_modelspace;<br />
layout(location = 1) in vec2 vertexUV;</p>
<p>&#47;&#47; アウトプットデータ。各フラグメントで書き込まれます。<br />
out vec2 UV;</p>
<p>&#47;&#47; すべてのメッシュで一定の値<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>    &#47;&#47; クリップ空間での頂点の出力位置。MVP&times;位置<br />
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);</p>
<p>    &#47;&#47; 頂点のUV座標です。特別な空間はありません。<br />
    UV = vertexUV;<br />
}<&#47;pre><br />
チュートリアル4で学んだ"layout(location = 1) in vec2 vertexUV"を思い出せますか？ここでは丁度それと同じことをやろうとしています。ただし、(R,G,B)バッファの変わりに(U,V)のバッファを与えます。</p>
<pre class="brush: cpp">&#47;&#47; 各頂点に2つの値、これらはBlenderで作りました。どうやって作るかはこれから説明します。<br />
static const GLfloat g_uv_buffer_data[] = {<br />
    0.000059f, 1.0f-0.000004f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    1.000023f, 1.0f-0.000013f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.999958f, 1.0f-0.336064f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.667969f, 1.0f-0.671889f,<br />
    1.000023f, 1.0f-0.000013f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.000059f, 1.0f-0.000004f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.336098f, 1.0f-0.000071f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    1.000004f, 1.0f-0.671847f,<br />
    0.999958f, 1.0f-0.336064f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.667979f, 1.0f-0.335851f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.668104f, 1.0f-0.000013f,<br />
    0.336098f, 1.0f-0.000071f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.000004f, 1.0f-0.671870f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.000103f, 1.0f-0.336048f,<br />
    0.336024f, 1.0f-0.671877f,<br />
    0.335973f, 1.0f-0.335903f,<br />
    0.667969f, 1.0f-0.671889f,<br />
    1.000004f, 1.0f-0.671847f,<br />
    0.667979f, 1.0f-0.335851f<br />
};<&#47;pre><br />
上のUV座標は下のモデルに相当します。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;uv_mapping_blender.png"><img class="alignnone size-medium wp-image-115" title="uv_mapping_blender" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;uv_mapping_blender-300x222.png" width="300" height="222" &#47;><&#47;a></p>
<p>ここから後は明らかです。バッファを作り、バインドし、満たし、設定し、いつもどおり頂点バッファを描くだけです。glVertexAttribPointerの2つ目のパラメータ(サイズ)に3の代わりに2を入れることを注意してください。</p>
<p>これが結果です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering.png"><img class="alignnone size-full wp-image-119" title="nearfiltering" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering.png" width="533" height="557" &#47;><&#47;a></p>
<p>そして、ズームインバージョンです。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering_zoom.png"><img class="alignnone size-full wp-image-120" title="nearfiltering_zoom" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearfiltering_zoom.png" width="348" height="340" &#47;><&#47;a></p>
<h1>フィルタリングとミップマップの使い方<&#47;h1><br />
上でスクリーンショットで見たように、テクスチャの質はあまりよくありません。これは私たちが書いたloadBMP_customに起因します。</p>
<pre class="brush: cpp">glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);<&#47;pre><br />
これはフラグメントシェーダにおいて、texture()が(U,V)座標のテクセルを取ってそれをそのまま使うことを意味します。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearest.png"><img class="alignnone size-full wp-image-130" title="nearest" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nearest.png" width="440" height="240" &#47;><&#47;a></p>
<p>これを改善する方法はいくつかあります。</p>
<h2>線形フィルタリング<&#47;h2><br />
線形フィルタリングでは、texture()は周りのほかのテクセルも見ます。そして各中心までの距離に応じて色を混ぜます。これは上で見たようなハードエッジを避けることが出来ます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;linear1.png"><img class="alignnone size-full wp-image-133" title="linear" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;linear1.png" width="440" height="240" &#47;><&#47;a></p>
<p>これでよりよくなります。そしてこれは良く使われます。しかし、とても高い質を求めるならば、少し遅いですが異方性フィルタリングを使うのがよいでしょう。</p>
<h2>異方性フィルタリング<&#47;h2><br />
これは実際にフラグメントを通してみているかのように画像の部分を近似します。例えば、下のテクスチャが横から見られて少し回転しているならば、異方性フィルタリングは、メイン方向に沿って固定した数("異方性レベル")のサンプルを取ることで、青い四角形に含まれる色を計算します。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;aniso.png"><img class="alignnone size-full wp-image-131" title="aniso" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;aniso.png" width="440" height="240" &#47;><&#47;a></p>
<h2>ミップマップ<&#47;h2><br />
線形フィルタリングも異方性フィルタリングも問題を抱えています。テクスチャが遠くから見られる場合、4つのテクセルを混ぜ合わせるだけでは充分ではありません。実際、3Dモデルがスクリーン上の1フラグメントにも満たない場合、最終的な色を作るために画像の"すべて"のテクセルを平均しなければなりません。明らかにパフォーマンス上の問題があるため、この方法は使われません。代わりに、ミップマップを導入します。</p>
<p><a href="http:&#47;&#47;en.wikipedia.org&#47;wiki&#47;File:MipMap_Example_STS101.jpg"><img class="alignnone" title="An original image and its mipmaps. Image by Tokigun under Creative Commons" alt="" src="http:&#47;&#47;upload.wikimedia.org&#47;wikipedia&#47;commons&#47;5&#47;5c&#47;MipMap_Example_STS101.jpg" width="384" height="256" &#47;><&#47;a></p>
<ul>
<li>最初のタイルから、1&times;1サイズの画像になるまで、連続的に1&#47;2で縮小していきます。(1x1の画像は事実上すべての色の平均です。)<&#47;li>
<li>メッシュを描くとき、テクセルの大きさに応じて、どのミップマップを使うのが一番適しているかを決めます。<&#47;li>
<li>最も近いもの、線形フィルタリング、異方性フィルタリングのどれかを使ってミップマップからサンプルします。<&#47;li>
<li>更なる質の向上のために、二つのミップマップをサンプルし結果を混ぜることも出来ます。<&#47;li><br />
<&#47;ul><br />
幸運なことに、これらすべては簡単に実現できます。OpenGLがすべてやってくれます。</p>
<pre class="brush: cpp">&#47;&#47; 画像を拡大(MAGnifying)するときは線形(LINEAR)フィルタリングを使います。<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);<br />
&#47;&#47; 画像を縮小(MINifying)するとき、線形(LINEAR)フィルタした、二つのミップマップを線形(LINEARYLY)に混ぜたものを使います。<br />
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);<br />
&#47;&#47; 次のようにしてミップマップを作ります。<br />
glGenerateMipmap(GL_TEXTURE_2D);<&#47;pre></p>
<h1>GLFWでのテクスチャのロード方法<&#47;h1><br />
自分で作ったのでloadBMP_custom関数はとても素晴らしく感じます。しかし専用のライブラリを使うほううがよいでしょう。GLFWがやってくれます。(ただしTGAファイルのみです。)</p>
<pre class="brush: cpp">GLuint loadTGA_glfw(const char * imagepath){</p>
<p>    &#47;&#47; 一つのOpenGLテクスチャを作ります。<br />
    GLuint textureID;<br />
    glGenTextures(1, &amp;textureID);</p>
<p>    &#47;&#47; 新しく作ったテクスチャを"バインド"します。これ以降の関数はすべてこのテクスチャを変更します。<br />
    glBindTexture(GL_TEXTURE_2D, textureID);</p>
<p>    &#47;&#47; 正しいパラメータでglTexImage2Dを呼んで、ファイルを読み込みます。<br />
    glfwLoadTexture2D(imagepath, 0);</p>
<p>    &#47;&#47; 3つの線形フィルタリング<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);<br />
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);<br />
    glGenerateMipmap(GL_TEXTURE_2D);</p>
<p>    &#47;&#47; 作成したテクスチャのIDを返します。<br />
    return textureID;<br />
}<&#47;pre></p>
<h1>圧縮されたテクスチャ<&#47;h1><br />
ここで、どうやってTGAファイルの変わりにJPEGファイルを読み込もうかと考えているかと思います。</p>
<p>簡潔に言えば、そうすべきではありません。もっと良い方法があります。</p>
<h2>圧縮されたテクスチャを作る<&#47;h2></p>
<ul>
<li><a href="http:&#47;&#47;developer.amd.com&#47;Resources&#47;archive&#47;ArchivedTools&#47;gpu&#47;compressonator&#47;Pages&#47;default.aspx">The Compressonator<&#47;a>をダウンロードします。ATIツールです。<&#47;li>
<li>2のべき乗サイズのテクスチャをそれにロードします。<&#47;li>
<li>DXT1、DXT3あるいはDXT5に圧縮します。(これらのフォーマットの違いは<a href="http:&#47;&#47;en.wikipedia.org&#47;wiki&#47;S3_Texture_Compression">Wikipedia<&#47;a>を呼んでください。) :<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;TheCompressonator.png"><img class="alignnone size-full wp-image-358" title="TheCompressonator" alt="" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;TheCompressonator.png" width="806" height="688" &#47;><&#47;a></p>
<ul>
<li>実行時にしなくて良いようにミップマップを作ります。<&#47;li>
<li>.DDSファイルとしてエクスポートします。<&#47;li><br />
<&#47;ul><br />
これで画像はGPUでの処理に適したフォーマットに圧縮されました。シェーダでtexture()を呼ぶときはいつも、すぐに解凍できます。これは遅いように感じますが、メモリの節約にもなりますし、少ないデータを転送するだけで済みます。データの転送には多くのコストがかかりますが、テクスチャの解凍はコストがかかりません。(それに適したハードウェアがあるからです。)一般に、テクスチャの圧縮は20%のパフォーマンスの向上につながります。</p>
<h2>圧縮されたテクスチャの使用方法<&#47;h2><br />
どのように画像をロードするかを見ていきましょう。ヘッダの構成が違うだけで、BMPコードとほぼ同じです。</p>
<pre class="brush: cpp">GLuint loadDDS(const char * imagepath){</p>
<p>    unsigned char header[124];</p>
<p>    FILE *fp;</p>
<p>    &#47;* ファイルを開きます。 *&#47;<br />
    fp = fopen(imagepath, "rb");<br />
    if (fp == NULL)<br />
        return 0;</p>
<p>    &#47;* ファイルのタイプを確認します。 *&#47;<br />
    char filecode[4];<br />
    fread(filecode, 1, 4, fp);<br />
    if (strncmp(filecode, "DDS ", 4) != 0) {<br />
        fclose(fp);<br />
        return 0;<br />
    }</p>
<p>    &#47;* サーフィスの説明を取得します。 *&#47;<br />
    fread(&amp;header, 124, 1, fp); </p>
<p>    unsigned int height      = *(unsigned int*)&amp;(header[8 ]);<br />
    unsigned int width         = *(unsigned int*)&amp;(header[12]);<br />
    unsigned int linearSize     = *(unsigned int*)&amp;(header[16]);<br />
    unsigned int mipMapCount = *(unsigned int*)&amp;(header[24]);<br />
    unsigned int fourCC      = *(unsigned int*)&amp;(header[80]);<&#47;pre><br />
ヘッダの後は実際のデータです。すべてのミップマップレベルは連続的です。それらは一つのバッチで読み込めます。</p>
<pre class="brush: cpp">    unsigned char * buffer;<br />
    unsigned int bufsize;<br />
    &#47;* 読み込もうとするミップマップの大きさはどの程度か？ *&#47;<br />
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;<br />
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));<br />
    fread(buffer, 1, bufsize, fp);<br />
    &#47;* ファイルポインタを閉じます。 *&#47;<br />
    fclose(fp);<&#47;pre><br />
ここでは3つの異なるフォーマットを扱います。DXT1、DXT3とDXT5です。"fourCC"フラグをOpenGLが理解できるような値に変更する必要があります。</p>
<pre class="brush: cpp">    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;<br />
    unsigned int format;<br />
    switch(fourCC)<br />
    {<br />
    case FOURCC_DXT1:<br />
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;<br />
        break;<br />
    case FOURCC_DXT3:<br />
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;<br />
        break;<br />
    case FOURCC_DXT5:<br />
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;<br />
        break;<br />
    default:<br />
        free(buffer);<br />
        return 0;<br />
    }<&#47;pre><br />
いつもどおりテクスチャを作ります。</p>
<pre class="brush: cpp">    &#47;&#47; OpenGLテクスチャを作ります。<br />
    GLuint textureID;<br />
    glGenTextures(1, &amp;textureID);</p>
<p>    &#47;&#47; 新しく作ったテクスチャを"バインド"します。これ以降の関数はすべてこのテクスチャを変更します。<br />
    glBindTexture(GL_TEXTURE_2D, textureID);<&#47;pre><br />
And now, we just have to fill each mipmap one after another :</p>
<pre class="brush: cpp">    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;<br />
    unsigned int offset = 0;</p>
<p>    &#47;* ミップマップをロードします。 *&#47;<br />
    for (unsigned int level = 0; level < mipMapCount &amp;&amp; (width || height); ++level)<br />
    {<br />
        unsigned int size = ((width+3)&#47;4)*((height+3)&#47;4)*blockSize;<br />
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,<br />
            0, size, buffer + offset);</p>
<p>        offset += size;<br />
        width  &#47;= 2;<br />
        height &#47;= 2;<br />
    }<br />
    free(buffer); </p>
<p>    return textureID;<&#47;pre></p>
<h2>UVを逆さまにする<&#47;h2><br />
DXT圧縮はDirectXの世界から来ました。DirectXではVテクスチャ座標がOpenGLとは逆向きになっています。だから圧縮されたテクスチャを使う場合、正しいテクセルを取り出すために( coord.u, 1.0-coord.v)を使う必要があります。これは好きなときに出来ます。例えば、エクスポートスクリプトで、ローダで、シェーダで...。</p>
<h1>結論<&#47;h1><br />
OpenGLでテクスチャを作り、ロードし使う方法を学びました。</p>
<p>一般的に、圧縮されたテクスチャのみを使うべきです。なぜならメモリの使用量が少なく、ロードも早く、使うときのスピードも速いからです。主な欠点は、Compressonatorを使って画像を変換する必要があるということです。</p>
<h1>演習<&#47;h1></p>
<ul>
<li>ソースコード内でDDSローダを実装しましたが、テクスチャ座標の修正は実装していません。立方体が正しく表示されるようにコードの適切な位置を変更してください。<&#47;li>
<li>異なるDDSフォーマットを実験してみてください。結果に違いがありましたか？圧縮比に違いがありましたか？<&#47;li>
<li>Compressonatorでミップマップを作らないようにしてください。結果はどうなりましたか？これを直す方法を3つ挙げてください。<&#47;li><br />
<&#47;ul></p>
<h1>参考文献<&#47;h1></p>
<ul>
<li><a href="http:&#47;&#47;www.oldunreal.com&#47;editing&#47;s3tc&#47;ARB_texture_compression.pdf">OpenGLで圧縮されたテクスチャを使う<&#47;a> , S辿bastien Domine, NVIDIA<&#47;li><br />
<&#47;ul></p>
