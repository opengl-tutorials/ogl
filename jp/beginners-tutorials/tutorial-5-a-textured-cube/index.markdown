---
layout: tutorial
status: publish
published: true
title: チュートリアル5：テクスチャされた立方体
date: '2014-07-30 03:00:11 +0100'
date_gmt: '2014-07-30 03:00:11 +0100'
categories: []
tags: []
comments: []
language: jp
order: 50
---

このチュートリアルでは次のことを学びます。

* UV座標とは何か
* テクスチャをどうやってロードするか
* それらをOpenGLでどう使うか
* フィルタリングとミップマップとは何か、そしてどう使うか
* どのようにGLFWでよりロバストにテクスチャをロードするか
* アルファチャネルとは何か


# UV座標とは

メッシュをテクスチャするとき、各三角形に画像のどの部分を使うかをOpenGLに伝える手段が必要です。これをUV座標を使って行います。

各頂点は、その位置の上に、UとVという組になっている数値を持っています。これらの座標はテクスチャにアクセスするときに次のように使います。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/UVintro.png)

三角形の上にテクスチャがどのようにゆがんでいるかを確認してください。

# BMP画像のロード

BMPファイルフォーマットは複雑でないことが知られています。また多くのライブラリも存在します。しかし、ロード作業はとてもシンプルで、ブラックボックス内でどのように動いているかを理解する助けにもなります。だから、どのように動くかを知るためにも、BMPファイルローダを書きましょう。<span style="text-decoration: underline">ただし二度と使うことはないでしょう。</span>.

ここにロード関数の宣言が在ります。

``` cpp
GLuint loadBMP_custom(const char * imagepath);
```

これは次のように使います。

``` cpp
GLuint image = loadBMP_custom("./my_texture.bmp");
```

BMPファイルをどのように読み込むかを見ていきましょう。

まず、いくつかのデータが必要です。ファイルを読むときにこれらの変数はセットされます。

``` cpp
// BMPファイルのヘッダから読み込まれるデータ
unsigned char header[54]; // 各BMPファイルは54バイトのヘッダから始まります。
unsigned int dataPos;     // 実際のデータがファイルのどの位置にあるか
unsigned int width, height;
unsigned int imageSize;   // = 横*高さ*3
// 実際のRGBデータ
unsigned char * data;
```

実際にファイルを開く必要があります。

``` cpp
// ファイルを開きます。
FILE * file = fopen(imagepath,"rb");
if (!file)							    {printf("画像が開けませんでした。n"); return 0;}
```

ファイルの始まりは、54バイトのヘッダです。それには"これが本当にBMPファイルか？"、画像のサイズ、ピクセルごとのビット数などの情報を含んでいます。このヘッダを読み込みましょう。

``` cpp
if ( fread(header, 1, 54, file)!=54 ){ // 54バイト読み込めなければ、問題があります。
    printf("BMPファイルではありません。n");
    return false;
}
```

ヘッダは常にBMで始まります。実は、16進数エディタで.BMPファイルを開いたときに得られるものが、ここにあります。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/hexbmp.png)

だから最初の2バイトが本当に'B'と'M'で始まるかを確認する必要があります。

``` cpp
if ( header[0]!='B' || header[1]!='M' ){
    printf("BMPファイルではありません。n");
    return 0;
}
```

ここで画像のサイズやデータの位置などをロードします。

``` cpp
// バイト配列から整数を読み込む
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);
```

足りない情報があれば、自分で作ります。

``` cpp
// BMPファイルの中にはミスフォーマットがあります。その情報を推測します。
if (imageSize==0)    imageSize=width*height*3; // 3 : 1バイトは赤、緑、青の各色です。
if (dataPos==0)      dataPos=54; // これでBMPヘッダは終わりです。
```

これで画像のサイズが分かったので、画像を読み込むためにメモリを確保します。そして画像を読み込みます。

``` cpp
// バッファを作る
data = new unsigned char [imageSize];

// ファイルから実際のデータをバッファに読み込む
fread(data,1,imageSize,file);

//すべてはメモリ上にあるので、ファイルは閉じます。
fclose(file);
```

ここからはOpenGLのパートです。テクスチャを作るのは頂点バッファを作るのにとても似ています。つまり、テクスチャを作り、バインドし、それを満たし、設定します。

glTexImage2Dでは、GL_RGBは3要素の色についてで、GL_BGRはRAM上で実際にどのように表現されるかを示しています。実は、BMPファイルは赤->緑->青の順ではなく、青->緑->赤の順で格納されています。だからOpenGLにそのように伝える必要があります。

``` cpp
// ひとつのOpenGLテクスチャを作ります。
GLuint textureID;
glGenTextures(1, &textureID);

// 新たに作られたテクスチャを"バインド"します。つまりここから後のテクスチャ関数はこのテクスチャを変更します。
glBindTexture(GL_TEXTURE_2D, textureID);

// OpenGLに画像を渡します。
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

最後の2行は後で説明します。ところで、C++サイドでは、テクスチャをロードする新たな関数を使えます。

``` cpp
GLuint Texture = loadBMP_custom("uvtemplate.bmp");
```

もう一つとても重要なことは、テクスチャのサイズは2のべき乗でなければなりません。

* 良い : 128*128*, 256*256, 1024*1024, 2*2...
* 悪い : 127*128, 3*5, ...
* 良いが不自然 : 128*256


# OpenGLでのテクスチャの使用

はじめにフラグメントシェーダを見ていきましょう。これは簡単です。

``` glsl
#version 330 core

// 頂点シェーダからの値を書き込みます
in vec2 UV;

// アウトプットデータ
out vec3 color;

// すべてのメッシュで一定の値
uniform sampler2D myTextureSampler;

void main(){

    // アウトプットカラー = 指定したUV座標のテクスチャの色
    color = texture( myTextureSampler, UV ).rgb;
}
```
{: .highlightglslfs }

3点述べておきます。

* フラグメントシェーダはUV座標が必要です。これは普通のことです。
* どのテクスチャにアクセスするかを知るために、フラグメントシェーダは"sample2D"も必要です。(同じシェーダで複数のテクスチャにアクセスすることも可能です。)
* 最後に、テクスチャにアクセスするのはtexture()で行います。この関数はvec4型の(R,G,B,A)を返します。Aについてはまた説明します。

頂点シェーダも簡単です。UV座標をただフラグメントシェーダに送るだけです。

``` glsl
#version 330 core

// インプット頂点データ。このシェーダの実行ごとに異なります。
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// アウトプットデータ。各フラグメントで書き込まれます。
out vec2 UV;

// すべてのメッシュで一定の値
uniform mat4 MVP;

void main(){

    // クリップ空間での頂点の出力位置。MVP&times;位置
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

    // 頂点のUV座標です。特別な空間はありません。
    UV = vertexUV;
}
```
{: .highlightglslvs }

チュートリアル4で学んだ"layout(location = 1) in vec2 vertexUV"を思い出せますか？ここでは丁度それと同じことをやろうとしています。ただし、(R,G,B)バッファの変わりに(U,V)のバッファを与えます。

``` cpp
// 各頂点に2つの値、これらはBlenderで作りました。どうやって作るかはこれから説明します。
static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};
```

上のUV座標は下のモデルに相当します。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/uv_mapping_blender.png)

ここから後は明らかです。バッファを作り、バインドし、満たし、設定し、いつもどおり頂点バッファを描くだけです。glVertexAttribPointerの2つ目のパラメータ(サイズ)に3の代わりに2を入れることを注意してください。

これが結果です。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering.png)

そして、ズームインバージョンです。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering_zoom.png)

# フィルタリングとミップマップの使い方

上でスクリーンショットで見たように、テクスチャの質はあまりよくありません。これは私たちが書いたloadBMP_customに起因します。

``` cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

これはフラグメントシェーダにおいて、texture()が(U,V)座標のテクセルを取ってそれをそのまま使うことを意味します。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearest.png)

これを改善する方法はいくつかあります。

##線形フィルタリング

線形フィルタリングでは、texture()は周りのほかのテクセルも見ます。そして各中心までの距離に応じて色を混ぜます。これは上で見たようなハードエッジを避けることが出来ます。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/linear1.png)

これでよりよくなります。そしてこれは良く使われます。しかし、とても高い質を求めるならば、少し遅いですが異方性フィルタリングを使うのがよいでしょう。

##異方性フィルタリング

これは実際にフラグメントを通してみているかのように画像の部分を近似します。例えば、下のテクスチャが横から見られて少し回転しているならば、異方性フィルタリングは、メイン方向に沿って固定した数("異方性レベル")のサンプルを取ることで、青い四角形に含まれる色を計算します。

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/aniso.png)

##ミップマップ

線形フィルタリングも異方性フィルタリングも問題を抱えています。テクスチャが遠くから見られる場合、4つのテクセルを混ぜ合わせるだけでは充分ではありません。実際、3Dモデルがスクリーン上の1フラグメントにも満たない場合、最終的な色を作るために画像の"すべて"のテクセルを平均しなければなりません。明らかにパフォーマンス上の問題があるため、この方法は使われません。代わりに、ミップマップを導入します。

![](http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg)

* 最初のタイルから、1&times;1サイズの画像になるまで、連続的に1/2で縮小していきます。(1x1の画像は事実上すべての色の平均です。)
* メッシュを描くとき、テクセルの大きさに応じて、どのミップマップを使うのが一番適しているかを決めます。
* 最も近いもの、線形フィルタリング、異方性フィルタリングのどれかを使ってミップマップからサンプルします。
* 更なる質の向上のために、二つのミップマップをサンプルし結果を混ぜることも出来ます。

幸運なことに、これらすべては簡単に実現できます。OpenGLがすべてやってくれます。

``` cpp
// 画像を拡大(MAGnifying)するときは線形(LINEAR)フィルタリングを使います。
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 画像を縮小(MINifying)するとき、線形(LINEAR)フィルタした、二つのミップマップを線形(LINEARYLY)に混ぜたものを使います。
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 次のようにしてミップマップを作ります。
glGenerateMipmap(GL_TEXTURE_2D);
```

# GLFWでのテクスチャのロード方法

自分で作ったのでloadBMP_custom関数はとても素晴らしく感じます。しかし専用のライブラリを使うほううがよいでしょう。GLFWがやってくれます。(ただしTGAファイルのみです。)

``` cpp
GLuint loadTGA_glfw(const char * imagepath){

    // 一つのOpenGLテクスチャを作ります。
    GLuint textureID;
    glGenTextures(1, &textureID);

    // 新しく作ったテクスチャを"バインド"します。これ以降の関数はすべてこのテクスチャを変更します。
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 正しいパラメータでglTexImage2Dを呼んで、ファイルを読み込みます。
    glfwLoadTexture2D(imagepath, 0);

    // 3つの線形フィルタリング
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // 作成したテクスチャのIDを返します。
    return textureID;
}
```

# 圧縮されたテクスチャ

ここで、どうやってTGAファイルの変わりにJPEGファイルを読み込もうかと考えているかと思います。

簡潔に言えば、そうすべきではありません。もっと良い方法があります。

##圧縮されたテクスチャを作る


* [The Compressonator](http://developer.amd.com/Resources/archive/ArchivedTools/gpu/compressonator/Pages/default.aspx)をダウンロードします。ATIツールです。
* 2のべき乗サイズのテクスチャをそれにロードします。
* DXT1、DXT3あるいはDXT5に圧縮します。(これらのフォーマットの違いは[Wikipedia](http://en.wikipedia.org/wiki/S3_Texture_Compression)を呼んでください。) :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/TheCompressonator.png)

* 実行時にしなくて良いようにミップマップを作ります。
* .DDSファイルとしてエクスポートします。

これで画像はGPUでの処理に適したフォーマットに圧縮されました。シェーダでtexture()を呼ぶときはいつも、すぐに解凍できます。これは遅いように感じますが、メモリの節約にもなりますし、少ないデータを転送するだけで済みます。データの転送には多くのコストがかかりますが、テクスチャの解凍はコストがかかりません。(それに適したハードウェアがあるからです。)一般に、テクスチャの圧縮は20%のパフォーマンスの向上につながります。

##圧縮されたテクスチャの使用方法

どのように画像をロードするかを見ていきましょう。ヘッダの構成が違うだけで、BMPコードとほぼ同じです。

``` cpp
GLuint loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* ファイルを開きます。 */
    fp = fopen(imagepath, "rb");
    if (fp == NULL)
        return 0;

    /* ファイルのタイプを確認します。 */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* サーフィスの説明を取得します。 */
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
```

ヘッダの後は実際のデータです。すべてのミップマップレベルは連続的です。それらは一つのバッチで読み込めます。

``` cpp
    unsigned char * buffer;
    unsigned int bufsize;
    /* 読み込もうとするミップマップの大きさはどの程度か？ */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* ファイルポインタを閉じます。 */
    fclose(fp);
```

ここでは3つの異なるフォーマットを扱います。DXT1、DXT3とDXT5です。"fourCC"フラグをOpenGLが理解できるような値に変更する必要があります。

``` cpp
    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }
```

いつもどおりテクスチャを作ります。

``` cpp
    // OpenGLテクスチャを作ります。
    GLuint textureID;
    glGenTextures(1, &textureID);

    // 新しく作ったテクスチャを"バインド"します。これ以降の関数はすべてこのテクスチャを変更します。
    glBindTexture(GL_TEXTURE_2D, textureID);
```

And now, we just have to fill each mipmap one after another :

``` cpp
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* ミップマップをロードします。 */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer); 

    return textureID;
```

## UVを逆さまにする

DXT圧縮はDirectXの世界から来ました。DirectXではVテクスチャ座標がOpenGLとは逆向きになっています。だから圧縮されたテクスチャを使う場合、正しいテクセルを取り出すために( coord.u, 1.0-coord.v)を使う必要があります。これは好きなときに出来ます。例えば、エクスポートスクリプトで、ローダで、シェーダで...。

# 結論

OpenGLでテクスチャを作り、ロードし使う方法を学びました。

一般的に、圧縮されたテクスチャのみを使うべきです。なぜならメモリの使用量が少なく、ロードも早く、使うときのスピードも速いからです。主な欠点は、Compressonatorを使って画像を変換する必要があるということです。

# 演習


* ソースコード内でDDSローダを実装しましたが、テクスチャ座標の修正は実装していません。立方体が正しく表示されるようにコードの適切な位置を変更してください。
* 異なるDDSフォーマットを実験してみてください。結果に違いがありましたか？圧縮比に違いがありましたか？
* Compressonatorでミップマップを作らないようにしてください。結果はどうなりましたか？これを直す方法を3つ挙げてください。


# 参考文献


* [OpenGLで圧縮されたテクスチャを使う](http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf) , S辿bastien Domine, NVIDIA

