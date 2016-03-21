---
layout: page
status: publish
published: true
title: 'チュートリアル14：テクスチャへのレンダー'
date: '2011-05-26 19:33:15 +0200'
date_gmt: '2011-05-26 19:33:15 +0200'
categories: [tuto]
order: 60
tags: []
language: jp
---

テクスチャへのレンダー（Render-To-Texture）は様々な効果を作り出せる数少ない方法です。基本的な考え方は、いつもどおりシーンを描画します。しかしこのとき後で再利用できるテクスチャに描画します。

in-gameカメラや後処理、多くのGFXのようなアプリケーションを含みます。

#テクスチャへのレンダー

これを実行するには3つの作業があります。描画しようとするテクスチャの作成。そこに何かを描画する。できたテクスチャを使用する。

##描画対象の作成

これから描画しようとするものはフレームバッファと呼ばれています。これはテクスチャ用のコンテナで、オプションのデプスバッファです。OpenGLでは他のオブジェクトと同様の方法で作られます。

``` cpp
// フレームバッファ、0か1かあるいはそれ以上のテクスチャと0か1のデプスバッファを再編成する。
GLuint FramebufferName = 0;
glGenFramebuffers(1, &FramebufferName);
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
```

そしてシェーダのRGB出力を格納するテクスチャを作ります。このコードはとても古典的なものです。

``` cpp
// 描画しようとするテクスチャ
GLuint renderedTexture;
glGenTextures(1, &renderedTexture);

// 新しく作ったテクスチャを"バインド"する。：以降のすべてのテクスチャ関数はこのテクスチャを修正する。
glBindTexture(GL_TEXTURE_2D, renderedTexture);

// 空の画像をOpenGLに渡す。（最後が"0"）
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

// 貧弱なフィルタリング。
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

またデプスバッファも必要です。これはオプションで、テクスチャに何を描画しようとするかに依存します。しかし、スザンヌを描画しようとしているので、デプステストが必要です。

``` cpp
// デプスバッファ
GLuint depthrenderbuffer;
glGenRenderbuffers(1, &depthrenderbuffer);
glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
```

最後にフレームバッファの設定をします。

``` cpp
// "renderedTexture"を0番目の付属物としてセットします。
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

//描画バッファのリストをセットする
GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
glDrawBuffers(1, DrawBuffers); // "1"はDrawBuffersのサイズです。
```

GPUの性能次第ですが、処理中に何かおかしなことが起こるかもしれません。それは次のようにチェックできます。

``` cpp
// 常にフレームバッファがokかをチェックします。
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
return false;
```

##テクスチャへの描画

テクスチャへの描画は直接的です。単にフレームバッファをバインドして、いつもどおりシーンを描画するだけです。

``` cpp
// フレームバッファに描画する。
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
glViewport(0,0,1024,768); // フレームバッファ全体に描画する。左下隅から右上隅へ。
```

フラグメントシェーダにちょっとした変更が必要です。

``` cpp
layout(location = 0) out vec3 color;
```

これは"color"変数を書くときに描画対象0（この場合はテクスチャ）に描くことを意味します。
なぜならDrawBuffers[0]はGL_COLOR_ATTACHMENT *i* であり、この場合 *renderedTexture* に相当します。

要点：

* layout(location=0)なので *color* は最初のバッファに書かれます。
* DrawBuffers[1] = {GL_COLOR_ATTACHMENT0}なので、最初のバッファはGL_COLOR_ATTACHMENT0です。
* GL_COLOR_ATTACHMENT0はrenderedTextureを持っています。だからこれが色が書かれる場所です。
* 言い換えればGL_COLOR_ATTACHMENT0をGL_COLOR_ATTACHMENT2に入れ替えても機能します。

メモ：OpenGL3.3より前のバージョンではlayout(location=i)がありません。しかしglFragData[i] = mvvalueが使えます。
<div><span style="font-size: medium;"><span style="line-height: 24px;">
</span></span></div>

##描画されたテクスチャを使う

スクリーンにぴったり合う単純な四角形を描画しましょう。いつものようにバッファやシェーダID…などが必要です。

``` cpp
// フルスクリーン四角形のFBO
GLuint quad_VertexArrayID;
glGenVertexArrays(1, &quad_VertexArrayID);
glBindVertexArray(quad_VertexArrayID);

static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
};

GLuint quad_vertexbuffer;
glGenBuffers(1, &quad_vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

// シェーダからGLSLプログラムを作りコンパイルする。
GLuint quad_programID = LoadShaders( "Passthrough.vertexshader", "SimpleTexture.fragmentshader" );
GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
GLuint timeID = glGetUniformLocation(quad_programID, "time");
```

もうスクリーンに描画したいでしょう。glBindFramebufferの2番目のパラメータを0にすることで実行されます。

``` cpp
// スクリーンに描画する。
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glViewport(0,0,1024,768); //フレームバッファ全体に描画する。左下隅から右上隅へ。
```

次のようなシェーダでフルスクリーン四角形を描画できます。

``` glsl

#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;

void main(){
    color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz;
}
```
{: .highlightglslfs }

このコードは単純にテクスチャをサンプルします。ただし、時刻に応じて小さなオフセットを追加します。

#結果

 

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvy.png)


#さらに先へ


##デプスを使う

描画されたテクスチャを使うときにデプスが必要な場合があるかもしれません。その場合には、以下のように作られたテクスチャに単純に描画するだけです。

``` cpp
glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
```

("24"はビットの精度です。必要に応じて16と24、32のうちから選べます。通常は24です。)

提供したソースコードにもこのように実装されています。

これは少し遅いです。なぜならドライバが [Hi-Z](http://fr.slideshare.net/pjcozzi/z-buffer-optimizations).のような最適化を使用できないからです。

このスクリーンショットでは、デプスレベルを人工的にきれいにしています。通常は、デプステクスチャ上のものを見るのはもっと難しいです。近くのZは0なので黒色、遠くのZは1なので白色です。

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvydepth.png)


##マルチサンプリング

基本的なテクスチャの変わりに複数サンプルしたテクスチャを書けます。C++コードのglTexImage2Dを [glTexImage2DMultisample](http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage2DMultisample.xml) に置き換え、そしてフラグメントシェーダのsampler2D/textureをsampler2DMS/texelFetchに置き換えるだけです。

ただし注意することがあります。texelFetchには取り出すサンプルの数が必要です。言い換えれば自動的な"filtering"はありません。（正確にはマルチサンプリングという場合には"resolution"です。）

だからMSテクスチャを自分自身で何とかしないといけません。

難しくはありませんが面倒です。

##複数の描画対象

同時に複数のテクスチャを書きたい場合もあるでしょう。

単純に複数の（同じサイズの）テクスチャを作り、それぞれ別のアタッチメントでglFramebufferTextureを呼び、更新したパラメータでglDrawBuffersを呼びます。（たとえば (2,{GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1}})のように。）そしてフラグメントシェーダにもう一方の出力変数を加えます。

``` glsl

layout(location = 1) out vec3 normal_tangentspace; // or whatever
```
{: .highlightglslfs }

ヒント：テクスチャで効果的にベクトルを出力したいなら、浮動小数点テクスチャがあります。
それは8ビットの代わりに16ビットや32ビットの精度です。 [glTexImage2D](http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml)のリファレンスを見てください。（GL_FLOATで検索）

ヒント2：以前のバージョンのOpenGLでは、代わりにglFragData[1] = myvalueを使います。

#演習


* glViewport(0,0,1024,768);の代わりにglViewport(0,0,512,768);を使いましょう。（フレームバッファとスクリーンの両方で試しましょう。）
* 最後のフラグメントシェーダで他のUV座標で実験して見ましょう。
* 四角形をリアルな変換行列で変換してみましょう。まずはハードコードで、そして次にcontrols.hppの関数を使って。
