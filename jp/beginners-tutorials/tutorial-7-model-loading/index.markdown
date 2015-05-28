---
layout: page
status: publish
published: true
title: チュートリアル7：モデルのロード
author:
  display_name: suzuichi
  login: suzuichi
  email: suzuichiblog@gmail.com
  url: ''
author_login: suzuichi
author_email: suzuichiblog@gmail.com
wordpress_id: 1316
wordpress_url: http://www.opengl-tutorial.org/?page_id=1316
date: '2014-07-30 03:03:25 +0100'
date_gmt: '2014-07-30 03:03:25 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>これまで立方体をソースコードに直接書いていました。これは扱いにくく、不便だということに同意してもらえるでしょう。</p>
<p>このチュートリアルでは、ファイルから3Dメッシュをどのようにロードするかを学びます。テクスチャと同じようにして実現できます。小さく、制限されたローダを書いていきます。そして私たちのものより良く出来ているライブラリでは実際にどうやっているのかという指針も与えます。</p>
<p>簡単化のためにここではOBJファイルフォーマットを扱います。OBJフォーマットはとてもシンプルなフォーマットです。一つの頂点に対して一つのUV座標一つの法線のみを扱います。(法線が何であるかはすぐには分からなくても大丈夫です。)</p>
<h1>OBJのロード<&#47;h1><br />
common&#47;objloader.cppにあり、&#47;common&#47;objloader.hppに宣言されている私たちの関数は次のような戻り値や引数があります。</p>
<pre class="brush: cpp">bool loadOBJ(<br />
    const char * path,<br />
    std::vector  &amp; out_vertices,<br />
    std::vector  &amp; out_uvs,<br />
    std::vector  &amp; out_normals<br />
)<&#47;pre><br />
loadOBJは"path"にあるファイルを読み込み、out_vertices&#47;out_uvs&#47;out_normalsにデータを書き込み、何かおかしなことがあればfalseを返します。std::vectorはglm::vec3の配列を表すC++での表現方法です。vectorはサイズを自由に変更できる配列です。また数学のベクトルとは何の関係もありません。ただの配列と同じです。最後に&amp;はstd::vector変数を関数内で修正できることを意味します。</p>
<h2>OBJファイルの例<&#47;h2><br />
OBJファイルは次のような構成になっています。</p>
<pre># Blender3D v249 OBJ File: untitled.blend<br />
# www.blender3d.org<br />
mtllib cube.mtl<br />
v 1.000000 -1.000000 -1.000000<br />
v 1.000000 -1.000000 1.000000<br />
v -1.000000 -1.000000 1.000000<br />
v -1.000000 -1.000000 -1.000000<br />
v 1.000000 1.000000 -1.000000<br />
v 0.999999 1.000000 1.000001<br />
v -1.000000 1.000000 1.000000<br />
v -1.000000 1.000000 -1.000000<br />
vt 0.748573 0.750412<br />
vt 0.749279 0.501284<br />
vt 0.999110 0.501077<br />
vt 0.999455 0.750380<br />
vt 0.250471 0.500702<br />
vt 0.249682 0.749677<br />
vt 0.001085 0.750380<br />
vt 0.001517 0.499994<br />
vt 0.499422 0.500239<br />
vt 0.500149 0.750166<br />
vt 0.748355 0.998230<br />
vt 0.500193 0.998728<br />
vt 0.498993 0.250415<br />
vt 0.748953 0.250920<br />
vn 0.000000 0.000000 -1.000000<br />
vn -1.000000 -0.000000 -0.000000<br />
vn -0.000000 -0.000000 1.000000<br />
vn -0.000001 0.000000 1.000000<br />
vn 1.000000 -0.000000 0.000000<br />
vn 1.000000 0.000000 0.000001<br />
vn 0.000000 1.000000 -0.000000<br />
vn -0.000000 -1.000000 0.000000<br />
usemtl Material_ray.png<br />
s off<br />
f 5&#47;1&#47;1 1&#47;2&#47;1 4&#47;3&#47;1<br />
f 5&#47;1&#47;1 4&#47;3&#47;1 8&#47;4&#47;1<br />
f 3&#47;5&#47;2 7&#47;6&#47;2 8&#47;7&#47;2<br />
f 3&#47;5&#47;2 8&#47;7&#47;2 4&#47;8&#47;2<br />
f 2&#47;9&#47;3 6&#47;10&#47;3 3&#47;5&#47;3<br />
f 6&#47;10&#47;4 7&#47;6&#47;4 3&#47;5&#47;4<br />
f 1&#47;2&#47;5 5&#47;1&#47;5 2&#47;9&#47;5<br />
f 5&#47;1&#47;6 6&#47;10&#47;6 2&#47;9&#47;6<br />
f 5&#47;1&#47;7 8&#47;11&#47;7 6&#47;10&#47;7<br />
f 8&#47;11&#47;7 7&#47;12&#47;7 6&#47;10&#47;7<br />
f 1&#47;2&#47;8 2&#47;9&#47;8 3&#47;13&#47;8<br />
f 1&#47;2&#47;8 3&#47;13&#47;8 4&#47;14&#47;8<&#47;pre><br />
ここで記号の意味を説明します。</p>
<ul>
<li>#はコメントです。C++での&#47;&#47;と同じ意味です。<&#47;li>
<li>usemtlとmtllibモデルの外見を描写します。このチュートリアルでは使いません。<&#47;li>
<li>vは頂点です。<&#47;li>
<li>vtは一つの頂点のテクスチャ座標です。<&#47;li>
<li>vnは一つの頂点の法線です。<&#47;li>
<li>fはフェイスです。<&#47;li><br />
<&#47;ul><br />
vとvtは簡単に理解できます。fは少し複雑です。ここではf 8&#47;11&#47;7 7&#47;12&#47;7 6&#47;10&#47;7を例として取り上げます。</p>
<ul>
<li>8&#47;11&#47;7は三角形の1つ目の頂点を表します。<&#47;li>
<li>7&#47;12&#47;7は三角形の2つ目の頂点を表します。<&#47;li>
<li>6&#47;10&#47;7は三角形の3つ目の頂点を表します。<&#47;li>
<li>最初の頂点において、8はどの頂点かを使うかを示します。だからこの場合-1.000000 1.000000 -1.000000の頂点です。(インデックスは1から始まります。C++のような0からではありません。)<&#47;li>
<li>11はどのテクスチャ座標を使うかを表します。ここでは0.748355 0.998230です。<&#47;li>
<li>7はどの法線を使うかを表します。ここでは0.000000 1.000000 -0.000000です。<&#47;li><br />
<&#47;ul><br />
これらの数字はインデックスと呼ばれています。この方法はいくつかの三角形が同じ位置であるときに便利です。つまりファイルに一つの"v"を書いておけば、それを繰り返し使えます。これはメモリの節約にもなります。</p>
<p>悪いことにOpenGLでは一つのインデックスを位置、テクスチャ、法線ごとに用意しなければなりません。だからこのチュートリアルで取り扱うのは標準的な方法、インデックスを使わないメッシュを作り、後で索引付けします。チュートリアル9では、この辺がどのように動いているかを説明します。</p>
<h2>BlenderでのOBJファイルの作成方法<&#47;h2><br />
これから作るおもちゃローダは機能がとても制限されているので、ファイルをエクスポートするときに気をつけてオプションをセットする必要があります。ここにBlenderでの方法を示します。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;Blender.png"><img class="alignnone size-full wp-image-697" title="Blender" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;Blender.png" alt="" width="321" height="529" &#47;><&#47;a></p>
<h2>ファイルの読み込み<&#47;h2><br />
それでは、コードに落としていきましょう。.objのコンテンツを保存するための一時的な変数を作ります。</p>
<pre class="brush: cpp">std::vector vertexIndices, uvIndices, normalIndices;<br />
std::vector temp_vertices;<br />
std::vector temp_uvs;<br />
std::vector temp_normals;<&#47;pre><br />
チャプター5でやったので、ファイルのオープンの仕方は知っています。</p>
<pre class="brush: cpp">FILE * file = fopen(path, "r");<br />
if( file == NULL ){<br />
    printf("ファイルを開けません!n");<br />
    return false;<br />
}<&#47;pre><br />
このファイルを最後まで読んでみましょう。</p>
<pre class="brush: cpp">while( 1 ){</p>
<p>    char lineHeader[128];<br />
    &#47;&#47; 行の最初の文字列を読み込みます。<br />
    int res = fscanf(file, "%s", lineHeader);<br />
    if (res == EOF)<br />
        break; &#47;&#47; EOF = End Of File. ループを終了します。</p>
<p>    &#47;&#47; そうでなければlineHeaderをパースします。<&#47;pre><br />
(ここでは最初の文字列が128文字以下と仮定していますが、これはとてもひどい仮定です。しかしこれはおもちゃパーサなので問題ありません。)</p>
<p>まずは頂点を取り扱います。</p>
<pre class="brush: cpp">if ( strcmp( lineHeader, "v" ) == 0 ){<br />
    glm::vec3 vertex;<br />
    fscanf(file, "%f %f %fn", &amp;vertex.x, &amp;vertex.y, &amp;vertex.z );<br />
    temp_vertices.push_back(vertex);<&#47;pre><br />
つまり、行の最初の文字列が"v"であれば、残りは3つの数字です。だからglm::vec3を作り、それをvectorに追加します。</p>
<pre class="brush: cpp">}else if ( strcmp( lineHeader, "vt" ) == 0 ){<br />
    glm::vec2 uv;<br />
    fscanf(file, "%f %fn", &amp;uv.x, &amp;uv.y );<br />
    temp_uvs.push_back(uv);<&#47;pre><br />
つまり、もし"v"ではなく"vt"であれば、残りは2つの数字です。だからglm::vec2を作り、それをvectorに追加します。<br />
i.e if it's not a "v" but a "vt", then the rest has to be 2 floats, so create a glm::vec2 and add it to the vector.</p>
<p>同様に法線も扱います。</p>
<pre class="brush: cpp">}else if ( strcmp( lineHeader, "vn" ) == 0 ){<br />
    glm::vec3 normal;<br />
    fscanf(file, "%f %f %fn", &amp;normal.x, &amp;normal.y, &amp;normal.z );<br />
    temp_normals.push_back(normal);<&#47;pre><br />
ここで、"f"は少し複雑です。</p>
<pre class="brush: cpp">}else if ( strcmp( lineHeader, "f" ) == 0 ){<br />
    std::string vertex1, vertex2, vertex3;<br />
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];<br />
    int matches = fscanf(file, "%d&#47;%d&#47;%d %d&#47;%d&#47;%d %d&#47;%d&#47;%dn", &amp;vertexIndex[0], &amp;uvIndex[0], &amp;normalIndex[0], &amp;vertexIndex[1], &amp;uvIndex[1], &amp;normalIndex[1], &amp;vertexIndex[2], &amp;uvIndex[2], &amp;normalIndex[2] );<br />
    if (matches != 9){<br />
        printf("File can't be read by our simple parser : ( Try exporting with other optionsn");<br />
        return false;<br />
    }<br />
    vertexIndices.push_back(vertexIndex[0]);<br />
    vertexIndices.push_back(vertexIndex[1]);<br />
    vertexIndices.push_back(vertexIndex[2]);<br />
    uvIndices    .push_back(uvIndex[0]);<br />
    uvIndices    .push_back(uvIndex[1]);<br />
    uvIndices    .push_back(uvIndex[2]);<br />
    normalIndices.push_back(normalIndex[0]);<br />
    normalIndices.push_back(normalIndex[1]);<br />
    normalIndices.push_back(normalIndex[2]);<&#47;pre><br />
このコードは、少し読み込むデータが多い点を除けば、以前のものととても似ています。</p>
<h2>データの処理<&#47;h2><br />
これまでやったことは単にデータの"形"を変えただけです。つまり文字列をstd::vector型に変換しました。しかし、これだけでは充分ではありません。OpenGLが読み込める形に直さなければなりません。すなわち、インデックスを取り除き、単純なglm::vec3型に直します。これは索引付けと呼ばれます。</p>
<p>各三角形("f"の行)の各頂点(v&#47;vt&#47;vnの行)をやります。</p>
<pre class="brush: cpp">    &#47;&#47; 各三角形の各頂点<br />
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){<br />
<&#47;pre><br />
頂点の位置へのインデックスはvertexIndices[i]です。</p>
<pre class="brush: cpp">unsigned int vertexIndex = vertexIndices[i];<&#47;pre><br />
だから位置はtemp_vertices[ vertexIndex-1 ]です。(-1がありますが、これはC++ではインデックスが0から始まり、OBJでは1から始まるからです。覚えていますか？)</p>
<pre class="brush: cpp">glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];<&#47;pre><br />
そして、これが新たな頂点の位置を作ります。</p>
<pre class="brush: cpp">out_vertices.push_back(vertex);<&#47;pre><br />
UVや法線でも同じことを行います。</p>
<h1>ロードしたデータの使用方法<&#47;h1><br />
ここまでくれば、もう変更する箇所は多くありません。いつものようなstatic const GLfloat g_vertex_buffer_data[] = {...}を宣言する代わりに、std::vector verticesを宣言します。(UVと法線も同様です。)そして正しいパラメータでloadOBJを呼びます。</p>
<pre class="brush: cpp">&#47;&#47; .objファイルを読み込みます。<br />
std::vector vertices;<br />
std::vector uvs;<br />
std::vector normals; &#47;&#47; すぐには使いません。<br />
bool res = loadOBJ("cube.obj", vertices, uvs, normals);<&#47;pre><br />
そして配列の変わりにvectorをOpenGLに渡します。</p>
<pre class="brush: cpp">glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &amp;vertices[0], GL_STATIC_DRAW);<&#47;pre><br />
以上です！</p>
<h1>結果<&#47;h1><br />
下手なテクスチャですみません。私は良いアーティストじゃないんです。 :( テクスチャの寄贈を受け付けています！<br />
Sorry for the lame texture, I'm NOT a good artist :( Any contribution welcome !</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;ModelLoading.png"><img class="alignnone size-medium wp-image-670" title="ModelLoading" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;ModelLoading-300x232.png" alt="" width="300" height="232" &#47;><&#47;a></p>
<h1>他のフォーマットとローダ<&#47;h1><br />
ここで作ったローダは勉強目的では良いかもしれませんが、実際のアプリケーションでは使いたくはないでしょう。<a title="便利なツールとリンク" href="&#47;?page_id=210">便利なリンクとツール<&#47;a>ページをみて<em>実際に<&#47;em>使ってみてください。</p>
