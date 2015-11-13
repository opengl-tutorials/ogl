---
layout: page
status: publish
published: true
title: チュートリアル7：モデルのロード
date: '2014-07-30 03:03:25 +0100'
date_gmt: '2014-07-30 03:03:25 +0100'
categories: []
tags: []
comments: []
language: jp
order: 70
---

これまで立方体をソースコードに直接書いていました。これは扱いにくく、不便だということに同意してもらえるでしょう。

このチュートリアルでは、ファイルから3Dメッシュをどのようにロードするかを学びます。テクスチャと同じようにして実現できます。小さく、制限されたローダを書いていきます。そして私たちのものより良く出来ているライブラリでは実際にどうやっているのかという指針も与えます。

簡単化のためにここではOBJファイルフォーマットを扱います。OBJフォーマットはとてもシンプルなフォーマットです。一つの頂点に対して一つのUV座標一つの法線のみを扱います。(法線が何であるかはすぐには分からなくても大丈夫です。)

#OBJのロード

common/objloader.cppにあり、/common/objloader.hppに宣言されている私たちの関数は次のような戻り値や引数があります。
{% highlight cpp linenos %}
bool loadOBJ(
    const char * path,
    std::vector  & out_vertices,
    std::vector  & out_uvs,
    std::vector  & out_normals
)
{% endhighlight %}
loadOBJは"path"にあるファイルを読み込み、out_vertices/out_uvs/out_normalsにデータを書き込み、何かおかしなことがあればfalseを返します。std::vectorはglm::vec3の配列を表すC++での表現方法です。vectorはサイズを自由に変更できる配列です。また数学のベクトルとは何の関係もありません。ただの配列と同じです。最後に&はstd::vector変数を関数内で修正できることを意味します。

##OBJファイルの例

OBJファイルは次のような構成になっています。
{% highlight text linenos %}
# Blender3D v249 OBJ File: untitled.blend
# www.blender3d.org
mtllib cube.mtl
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -1.000000
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 0.748573 0.750412
vt 0.749279 0.501284
vt 0.999110 0.501077
vt 0.999455 0.750380
vt 0.250471 0.500702
vt 0.249682 0.749677
vt 0.001085 0.750380
vt 0.001517 0.499994
vt 0.499422 0.500239
vt 0.500149 0.750166
vt 0.748355 0.998230
vt 0.500193 0.998728
vt 0.498993 0.250415
vt 0.748953 0.250920
vn 0.000000 0.000000 -1.000000
vn -1.000000 -0.000000 -0.000000
vn -0.000000 -0.000000 1.000000
vn -0.000001 0.000000 1.000000
vn 1.000000 -0.000000 0.000000
vn 1.000000 0.000000 0.000001
vn 0.000000 1.000000 -0.000000
vn -0.000000 -1.000000 0.000000
usemtl Material_ray.png
s off
f 5/1/1 1/2/1 4/3/1
f 5/1/1 4/3/1 8/4/1
f 3/5/2 7/6/2 8/7/2
f 3/5/2 8/7/2 4/8/2
f 2/9/3 6/10/3 3/5/3
f 6/10/4 7/6/4 3/5/4
f 1/2/5 5/1/5 2/9/5
f 5/1/6 6/10/6 2/9/6
f 5/1/7 8/11/7 6/10/7
f 8/11/7 7/12/7 6/10/7
f 1/2/8 2/9/8 3/13/8
f 1/2/8 3/13/8 4/14/8
{% endhighlight %}
ここで記号の意味を説明します。

* #はコメントです。C++での//と同じ意味です。
* usemtlとmtllibモデルの外見を描写します。このチュートリアルでは使いません。
* vは頂点です。
* vtは一つの頂点のテクスチャ座標です。
* vnは一つの頂点の法線です。
* fはフェイスです。

vとvtは簡単に理解できます。fは少し複雑です。ここではf 8/11/7 7/12/7 6/10/7を例として取り上げます。

* 8/11/7は三角形の1つ目の頂点を表します。
* 7/12/7は三角形の2つ目の頂点を表します。
* 6/10/7は三角形の3つ目の頂点を表します。
* 最初の頂点において、8はどの頂点かを使うかを示します。だからこの場合-1.000000 1.000000 -1.000000の頂点です。(インデックスは1から始まります。C++のような0からではありません。)
* 11はどのテクスチャ座標を使うかを表します。ここでは0.748355 0.998230です。
* 7はどの法線を使うかを表します。ここでは0.000000 1.000000 -0.000000です。

これらの数字はインデックスと呼ばれています。この方法はいくつかの三角形が同じ位置であるときに便利です。つまりファイルに一つの"v"を書いておけば、それを繰り返し使えます。これはメモリの節約にもなります。

悪いことにOpenGLでは一つのインデックスを位置、テクスチャ、法線ごとに用意しなければなりません。だからこのチュートリアルで取り扱うのは標準的な方法、インデックスを使わないメッシュを作り、後で索引付けします。チュートリアル9では、この辺がどのように動いているかを説明します。

##BlenderでのOBJファイルの作成方法

これから作るおもちゃローダは機能がとても制限されているので、ファイルをエクスポートするときに気をつけてオプションをセットする必要があります。ここにBlenderでの方法を示します。

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/Blender.png)


##ファイルの読み込み

それでは、コードに落としていきましょう。.objのコンテンツを保存するための一時的な変数を作ります。
{% highlight cpp linenos %}
std::vector vertexIndices, uvIndices, normalIndices;
std::vector temp_vertices;
std::vector temp_uvs;
std::vector temp_normals;
{% endhighlight %}
チャプター5でやったので、ファイルのオープンの仕方は知っています。
{% highlight cpp linenos %}
FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("ファイルを開けません!n");
    return false;
}
{% endhighlight %}
このファイルを最後まで読んでみましょう。
{% highlight cpp linenos %}
while( 1 ){

    char lineHeader[128];
    // 行の最初の文字列を読み込みます。
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. ループを終了します。

    // そうでなければlineHeaderをパースします。
{% endhighlight %}
(ここでは最初の文字列が128文字以下と仮定していますが、これはとてもひどい仮定です。しかしこれはおもちゃパーサなので問題ありません。)

まずは頂点を取り扱います。
{% highlight cpp linenos %}
if ( strcmp( lineHeader, "v" ) == 0 ){
    glm::vec3 vertex;
    fscanf(file, "%f %f %fn", &vertex.x, &vertex.y, &vertex.z );
    temp_vertices.push_back(vertex);
{% endhighlight %}
つまり、行の最初の文字列が"v"であれば、残りは3つの数字です。だからglm::vec3を作り、それをvectorに追加します。
{% highlight cpp linenos %}
}else if ( strcmp( lineHeader, "vt" ) == 0 ){
    glm::vec2 uv;
    fscanf(file, "%f %fn", &uv.x, &uv.y );
    temp_uvs.push_back(uv);
{% endhighlight %}
つまり、もし"v"ではなく"vt"であれば、残りは2つの数字です。だからglm::vec2を作り、それをvectorに追加します。
i.e if it's not a "v" but a "vt", then the rest has to be 2 floats, so create a glm::vec2 and add it to the vector.

同様に法線も扱います。
{% highlight cpp linenos %}
}else if ( strcmp( lineHeader, "vn" ) == 0 ){
    glm::vec3 normal;
    fscanf(file, "%f %f %fn", &normal.x, &normal.y, &normal.z );
    temp_normals.push_back(normal);
{% endhighlight %}
ここで、"f"は少し複雑です。
{% highlight cpp linenos %}
}else if ( strcmp( lineHeader, "f" ) == 0 ){
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%dn", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9){
        printf("File can't be read by our simple parser : ( Try exporting with other optionsn");
        return false;
    }
    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices    .push_back(uvIndex[0]);
    uvIndices    .push_back(uvIndex[1]);
    uvIndices    .push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
{% endhighlight %}
このコードは、少し読み込むデータが多い点を除けば、以前のものととても似ています。

##データの処理

これまでやったことは単にデータの"形"を変えただけです。つまり文字列をstd::vector型に変換しました。しかし、これだけでは充分ではありません。OpenGLが読み込める形に直さなければなりません。すなわち、インデックスを取り除き、単純なglm::vec3型に直します。これは索引付けと呼ばれます。

各三角形("f"の行)の各頂点(v/vt/vnの行)をやります。
{% highlight cpp linenos %}
    // 各三角形の各頂点
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

{% endhighlight %}
頂点の位置へのインデックスはvertexIndices[i]です。
{% highlight cpp linenos %}
unsigned int vertexIndex = vertexIndices[i];
{% endhighlight %}
だから位置はtemp_vertices[ vertexIndex-1 ]です。(-1がありますが、これはC++ではインデックスが0から始まり、OBJでは1から始まるからです。覚えていますか？)
{% highlight cpp linenos %}
glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
{% endhighlight %}
そして、これが新たな頂点の位置を作ります。
{% highlight cpp linenos %}
out_vertices.push_back(vertex);
{% endhighlight %}
UVや法線でも同じことを行います。

#ロードしたデータの使用方法

ここまでくれば、もう変更する箇所は多くありません。いつものようなstatic const GLfloat g_vertex_buffer_data[] = {...}を宣言する代わりに、std::vector verticesを宣言します。(UVと法線も同様です。)そして正しいパラメータでloadOBJを呼びます。
{% highlight cpp linenos %}
// .objファイルを読み込みます。
std::vector vertices;
std::vector uvs;
std::vector normals; // すぐには使いません。
bool res = loadOBJ("cube.obj", vertices, uvs, normals);
{% endhighlight %}
そして配列の変わりにvectorをOpenGLに渡します。
{% highlight cpp linenos %}
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
{% endhighlight %}
以上です！

#結果

下手なテクスチャですみません。私は良いアーティストじゃないんです。 :( テクスチャの寄贈を受け付けています！
Sorry for the lame texture, I'm NOT a good artist :( Any contribution welcome !

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/ModelLoading.png)


#他のフォーマットとローダ

ここで作ったローダは勉強目的では良いかもしれませんが、実際のアプリケーションでは使いたくはないでしょう。[便利なリンクとツール](/?page_id=210)ページをみて*実際に*使ってみてください。
