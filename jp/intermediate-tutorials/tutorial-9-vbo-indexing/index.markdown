---
layout: page
status: publish
published: true
title: 'チュートリアル9：VBOインデックス'
date: '2011-05-12 19:21:49 +0200'
date_gmt: '2011-05-12 19:21:49 +0200'
categories: [tuto]
order: 10
tags: []
language: jp
---

#インデックスの原理

これまでVBOを構築するとき、二つの三角形が一辺を共有していたとしても、頂点を重複して作成していました。

このチュートリアルでは、インデックスを導入します。インデックスにより同じ頂点を何度でも再利用できるようになります。これは*インデックスバッファ*によって行われます。

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/indexing1.png)


インデックスバッファは複数の整数を持ちます。メッシュ内の各三角形ごとに3つ持ちます。インデックスバッファは様々な*属性のバッファ*を参照します。（頂点、色、UV座標、その他のUV座標、法線、…）これはOBJファイルのフォーマットに少し似ていますが、決定的に違うことは一つのインデックスバッファしかないことです。これは、二つの三角形間で共有されている頂点のすべての属性が同じでなければならないことを意味しています。

#共有と分離

法線を例にとって考えてみましょう。この図では、これらの二つの三角形を作った人はきっとスムーズな表面を表現することを望んでいるでしょう。だから一つの頂点の二法線を一つにまとめました。視覚化のため、スムーズな面を表現するために赤い線を追加しました。

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/goodsmooth.png)


一方で、この二つ目の図ではとがったように見せたいはずです。しかし法線を一つにしてしまうと、前の例と同様に、シェーダが補間してスムーズな面となってしまいます。

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/badmooth.png)


だからこのケースでは二つの異なる法線を使うほうが良いでしょう。これをOpenGLで行うためには、全頂点を属性のセットともに重複して作成するしかありません。

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/spiky.png)


#OpenGLでのインデックスVBO

インデックスは簡単に使うことができます。まず正しいインデックスで満たした追加のバッファを作ります。コードは以前と同じですが、ARRAY_BUFFERではなくELEMENT_ARRAY_BUDFFERです。
``` cpp
std::vector<unsigned int> indices;

// 必要に応じて"インデックス"を満たす

// インデックス用のバッファを作る
 GLuint elementbuffer;
 glGenBuffers(1, &elementbuffer);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
```
そしてメッシュを描画するために、このようにglDrawArraysを単純に置き換えます。
``` cpp
// インデックスバッファ
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

 // 三角形を描く！
 glDrawElements(
     GL_TRIANGLES,      // mode
     indices.size(),    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 );
```
（メモ：unsigned intの代わりにunsigned shortを使うほうが、メモリの節約にも高速化にもつながります。）

#インデックスバッファを満たす

インデックスバッファを満たすここで問題があります。前に言ったように、OBJ（あるいはColladaなどの他の3Dフォーマット）は*属性ごと*にひとつのインデックスバッファを使っていますが、OpenGLは一つのインデックスバッファしか使えません。このためどうにかしてN個のインデックスバッファを一つのインデックスバッファにまとめなければなりません。

これを行うアルゴリズムは以下のとおりです。
```
各頂点に対して
    すでに出力したすべての頂点と比較してまったく同じ属性を持つ頂点を探す。
    存在するならば :
        既にVBO内にあるので、そっちを使います！
    存在しないならば :
        VBOに頂点を追加します。
```
実際のC++コードはcommon/vboindexer.cppにあります。そこにはたくさんのコメントがあるので、上記のアルゴリズムを理解したなら、それで良いでしょう。

同じであるということの基準は、頂点の位置・UV・法線が等しいということです。他の属性も入れたければ、これを改造すれば良いでしょう。

同じ頂点を探す方法は単純に線形探索で行いました。std::mapのほうが実際には適しているでしょう。

#その他：FPSカウンター

インデックスには直接関係しませんが、[FPSカウンター](http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/) を見ておくのも良いでしょう。なぜならインデックスのスピードの改善を見られるからです。他のパフォーマンスツールは [Tools - Debuggers](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/#header-4).で利用可能です。
