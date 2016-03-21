---
layout: page
status: publish
published: true
title: 'チュートリアル11:2Dテキスト'
date: '2011-05-16 22:38:44 +0200'
date_gmt: '2011-05-16 22:38:44 +0200'
categories: [tuto]
order: 30
tags: []
language: jp
---

このチュートリアルでは、3Dモデルの上に2Dテキストを表示する方法を学びます。ここではシンプルなタイマーを表示します。

![]({{site.baseurl}}/assets/images/tuto-11-2d-text/clock.png)


#API

これから以下の単純なインターフェースを実装していきます。（common/text2D.hにあります。）

``` cpp
void initText2D(const char * texturePath);
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();
```

640*480と1080pの双方で動くようなコードにするため、xとyの座標は[0-800]と[0-600]とします。この座標を頂点シェーダがスクリーンの実際のサイズに合わせてくれます。実装していくためにcommon/text2D.cppを見てみましょう。

#テクスチャ

initText2Dは単純にテクスチャといくつかのシェーダを読み込みます。特に面白い点はありませんが、テクスチャを見ておきましょう：

![]({{site.baseurl}}/assets/images/tuto-11-2d-text/fontalpha.png)


テクスチャは [CBFG](http://www.codehead.co.uk/cbfg/)を使って作りました。CBFGはフォントからテクスチャを作り出すツールのうちの一つです。背景を赤くしてPaint.NETに読み込みました。（背景が赤いのは視覚化のためです。赤い部分が透明になる部分です。）

printText2Dの目標は適切なスクリーンの位置とテクスチャの座標の四角形を作ることです。

#描画

以下のバッファを使います。

``` cpp
std::vector<glm::vec2> vertices;
std::vector<glm::vec2> UVs;
```

各文字ごとに、四角形を定義するために四個の頂点の座標を計算し、二つの三角形を追加します。

``` cpp
for ( unsigned int i=0 ; i<length ; i++ ){

    glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
    glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
    glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
    glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );

    vertices.push_back(vertex_down_right);
    vertices.push_back(vertex_up_right);
    vertices.push_back(vertex_down_left);
```

UV座標のため、左上の座標は次のように計算します。

``` cpp
    char character = text[i];
    float uv_x = (character%16)/16.0f;
    float uv_y = (character/16)/16.0f;
```

[ASCII code for A](http://www.asciitable.com/)は65なのでこれで機能します。

65%16=1、だからAは1番目の行です。(行番号は0から始まります。)

65/16=4、だからAは4番目の列です。(これは整数の割り算なので4.0625ではありません。)

OpenGLのテクスチャにあわせるために16で割って[0.0 - 1.0]となるようにします。

そして頂点以外は前にやったことと同じようにします。

``` cpp
    glm::vec2 uv_up_left    = glm::vec2( uv_x           , 1.0f - uv_y );
    glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, 1.0f - uv_y );
    glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, 1.0f - (uv_y + 1.0f/16.0f) );
    glm::vec2 uv_down_left  = glm::vec2( uv_x           , 1.0f - (uv_y + 1.0f/16.0f) );

    UVs.push_back(uv_up_left   );
    UVs.push_back(uv_down_left );
    UVs.push_back(uv_up_right  );

    UVs.push_back(uv_down_right);
    UVs.push_back(uv_up_right);
    UVs.push_back(uv_down_left);
 }
```

あとはいつもどおりやっていきます。
バッファをバインドして、満たして、シェーダプログラムを選んで、テクスチャをバインドして、頂点属性を有効化/バインド/設定し、ブレンドを有効にして、glDrawArraysを呼ぶだけです。
これで完成！

ここで重要なことを言っておきます。座標は[0,800][0,600]で作られています。言い換えればここでは行列は必要ありません。頂点シェーダは単に[-1,1][-1,1]の範囲になるように置くだけです。（これはC++で簡単に実装できます。）

^```s*glsls*
void main(){

    // クリップ空間での頂点の出力座標
    // [0..800][0..600]を[-1..1][-1..1]にマッピングする。
    vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
    vertexPosition_homoneneousspace /= vec2(400,300);
    gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

    // 頂点のUV。これに対する特別な空間はありません。
    UV = vertexUV;
}
```
{: .highlightglslvs }

フラグメントシェーダも簡単に書けます。

^```s*glsls*
void main(){
    color = texture( myTextureSampler, UV );
}
```
{: .highlightglslfs }

ところで、製品ではこのコードを使わないでください。なぜならこれはラテンアルファベットのみに対応しているからです。あるいはインドや中国、日本、（画像中に &szlig; がないのでドイツにさえ）に製品を販売しないでください。このテクスチャはフランスでは動きます。(notice the &eacute;, &agrave;, &ccedil; などがあるため。) なぜならこのテクスチャは私のロケールで作られたからです。またOpenGL2には対応していないので注意してください。残念ながらUTF-8をいい感じに扱えるライブラリを私は知りません。

ところでJoel Spolskyの [The Absolute Minimum Every Software Developer Absolutely, Positively Must Know About Unicode and Character Sets (No Excuses!)](http://www.joelonsoftware.com/articles/Unicode.html) は読んでおくべきです。

それから多くのテキストを扱うなら、 [thisValve article](http://www.valvesoftware.com/publications/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf) を読んでおくのも良いでしょう。
