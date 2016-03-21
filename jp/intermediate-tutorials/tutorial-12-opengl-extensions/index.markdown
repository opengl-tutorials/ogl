---
layout: page
status: publish
published: true
title: 'チュートリアル12：OpenGLの拡張'
date: '2012-02-03 20:46:21 +0100'
date_gmt: '2012-02-03 20:46:21 +0100'
categories: [tuto]
order: 40
tags: []
language: jp
---

#拡張

最近はGPUの性能向上などによりより多くの三角形やピクセルの描画が可能となっています。しかし、そのような単純な性能向上だけに関心があるわけではありません。NVIDIAやAMD、Intelはよりよい機能を提供することでグラフィックカードの性能を向上させています。その例を見ていきましょう。

##ARB_fragment_program

2002年当時のGPUは頂点シェーダやフラグメントシェーダがありませんでした。すべてはチップ内でハードコードされていました。これは固定機能パイプライン（FFP)と呼ばれていました。そのため当時の最新のAPI(OpenGL1.3)では”シェーダ”と呼ばれるものの作成、演算、使用はできませんでした。なぜならそもそも存在していないからです。しかしNVIDIAは、多くのフラグや状態変数の代わりに、実際のコードを使いレンダリングプロセスを表現することを決めました。このようにしてARB_fragment_programが生まれました。GLSLはありませんが、代わりに以下のように書くことができます。
```
!!ARBfp1.0 MOV result.color, fragment.color; END
```
しかしOpenGLで上記のようなコードを使うには、OpenGLにはない特別な関数が必要でした。

##ARB_debug_output

ARB_fragment_programは昔のものだからもう必要ないでしょ？といいたいのは分かります。しかしより使いやすくなった新しい拡張があります。そのうちの一つがARB_debug_outputで、OpenGL3.3にはない機能を提供します。それはGL_DEBUG_OUTPUT_SYNCHRONOUS_ARB orGL_DEBUG_SEVERITY_MEDIUM_ARBなどのトークンやDebugMessageCallbackARBの関数を定義しています。この機能の良い点は下のような間違ったコードを書いたときに、エラーメッセージや問題の場所を教えてくれます。
``` cpp
glEnable(GL_TEXTURE); // 間違い! GL_TEXTURE_2Dが正しいのでは？
```
エラーメッセージと問題の場所を教えてくれます：

・この拡張は最新のOpenGL3.3でさえとても便利です。
・ARB_debug_outputを使ってみましょう！

![]({{site.baseurl}}/assets/images/tuto-12-ogl-ext/breakpoint.png)


##拡張機能を取得するー難しい方法

”手作業”で拡張機能をチェックする方法を下のコードに示します。 ([OpenGL.org wiki](http://www.opengl.org/wiki/GlGetString)にあります。) :
``` cpp
int NumberOfExtensions;
glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
for(i=0; i<NumberOfExtensions; i++) {
  const GLubyte *ccc=glGetStringi(GL_EXTENSIONS, i);
  if ( strcmp(ccc, (const GLubyte *)"GL_ARB_debug_output") == 0 ){
    // この拡張機能はハードウェアとドライバでサポートされています。
    // "glDebugMessageCallbackARB"関数を取得してみましょう。
    glDebugMessageCallbackARB  = (PFNGLDEBUGMESSAGECALLBACKARBPROC) wglGetProcAddress("glDebugMessageCallbackARB");
  }
}
```

##拡張機能をすべて取得するー簡単な方法

拡張機能をすべて取得するー簡単な方法すべての機能を上記のような方法で取得するのは面倒です。GLEW、GLee、gl3wなどのライブラリはもっと簡単な方法を提供しています。例えばGLEWでは、ウィンドウを作った後でglewInit()を呼ぶだけで、便利な変数が作られます。
``` cpp
if (GLEW_ARB_debug_output){ // Ta-Dah ! }
```
（debug_outputは特殊で、コンテキストの作成時に有効にしないといけません。GLFWでは、glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1); とします。）

##ARB vs EXT vs ...

拡張機能の名前には機能情報が込められています。

GL_ : すべてのプラットフォーム;
GLX_ : LinuxとMacだけ(X11);
WGL_ : Windowsだけ

EXT : 一般的な拡張
ARB : OpenGL Architecture Review Boardで受け入れられた拡張機能
NV/AMD/INTEL : これはそのままの意味 =)

#拡張機能によるデザイン


##問題

OpenGL3.3のアプリケーションで膨大な量の線を描画ることを考えましょう。複雑な頂点シェーダを書くことでも実現できます。あるいは複雑な処理をあなたの代わりにやってくれる [GL_NV_path_rendering](http://www.opengl.org/registry/specs/NV/path_rendering.txt)に頼ることでも実現できます。

以下のようなコードを書くことになるでしょう。
``` cpp
if ( GLEW_NV_path_rendering ){
    glPathStringNV( ... ); // シェイプを描画するだけ！
}else{
    // 古いNVIDEAハードウェアやAMD、INTEL上では自分で実装しなければなりません！
}
```

##制限の選択

一般的には、場合わけを維持するコストと描画のクオリティやパフォーマンスによるメリットを秤にかけて拡張機能を使うかどうかを決めます。

例えば2DゲームのBraidは、古いハードウェアでは単純には描画できないような種類のエフェクトがあります。

OpenGL3.3以降では、あなたが必要な機能の99%は用意されてます。たしかにGL_AMD_pinned_memoryのような拡張機能は便利ですが、数年前には好まれていませんでした。

古いハードウェアを扱う必要があるなら、OpenGL3+は使えません。代わりにOpenGL2+を使う必要があります。拡張機能を使うことはできませんが、そこはうまいことやってくしかありません。

より詳しく知りたいなら[OpenGL 2.1 version of Tutorial  14 - Render To Texture, line 152](http://code.google.com/p/opengl-tutorial-org/source/browse/tutorial14_render_to_texture/tutorial14.cpp?name=2.1%20branch#152)や [FAQ](http://www.opengl-tutorial.org/miscellaneous/faq/)を見てください。

#結論

あなたのGPU次第ではありますが、OpenGLの機能性を拡張するような良い拡張機能があることがわかりました。

多くの機能が既にOpenGLに組み込まれているので、最近では拡張機能のほとんどが高度な使用のためのものとなっています。しかし、それらがどう動くかや、それらを使うことでソフトウェアの性能を向上させることができるということを知っておくことは重要です。同時にメンテナンスコストも発生しますが。

#参考文献


* [debug_output tutorial by Aks](http://sites.google.com/site/opengltutorialsbyaks/introduction-to-opengl-4-1---tutorial-05 ) GLEWのおかげでステップ1は飛ばせます。
* [The OpenGL extension registry](http://www.opengl.org/registry/) すべての拡張機能が載ってます。バイブルです。
* [GLEW](http://glew.sourceforge.net/) OpenGLの拡張機能ライブラリです。
* [gl3w](https://github.com/skaslev/gl3w) シンプルなOpenGL3/4コアプロファイルローディングです。

