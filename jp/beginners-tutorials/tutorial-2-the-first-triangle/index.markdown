---
layout: tutorial
status: publish
published: true
title: チュートリアル2：最初の三角形
date: '2014-06-20 01:16:14 +0100'
date_gmt: '2014-06-20 01:16:14 +0100'
categories: [tuto]
tags: []
language: jp
order: 20
---

* TOC
{:toc}

これはもう一つの長いチュートリアルです。

OpenGL3は複雑なものを簡単に書くことができます。しかし、単純な三角形を描くことが実際とても難しくなります。

習慣的にコードをコピー＆ペーストするのを忘れないでください。

**<span style="color: red">もし始めの段階でプログラムがクラッシュするなら、間違ったディレクトリで実行しているかもしれません。チュートリアル1のVisual Studioの設定方法を注意深く読んでください！</span>**

# VAO

ここでは詳しく述べません。しかし配列バッファオブジェクト(Vertex Array Object)を作り、現在のものとしてセットする必要があります。

``` cpp
GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);
```

ウィンドウが作られたときにいったんこれを行います。(つまりOpenGLコンテキストを作った後です。)そしてどのOpenGLのコールも呼ぶ前です。

VAOについて詳しく知りたいならば、他のチュートリアルもあります。ただし、これはそれほど重要ではありません。

# スクリーン座標

三角形は3つの点で定義されています。3Dグラフィックで"点"というとき、通常"頂点"という言葉を使います。一つの頂点は3つの座標を持ちます。つまりX、Y、Zです。これらの3つの座標は次のように考えられます。

* Xは右方向
* Yは上方向
* Zはあなたの後ろの方向(後ろであって、前ではありません。)

しかしこれを視覚化するより良い方法があります。右手の法則を使います。

* Xは親指
* Yは人差し指
* Zは中指。親指を右方向に、人差し指を上方向に向ければ、中指はあなたの後ろ方向を指すでしょう。

Zをこの方向にするのは奇妙に感じます。なぜそうしたのでしょう？端的に言えば、数学の右手の法則の100年が便利なツールをいろいろ与えてくれるからです。この方法のマイナス面はZが直感的でないことです。

ところで、右手を自由に動かすことができます。つまりX、Y、Zも同様に動きます。詳しくは後で述べます。

だから三角形を作るためには、3つの3Dの点が必要となります。それでは見ていきましょう。

``` cpp
// 3頂点を表す3つのベクトルの配列
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};
```

最初の点は(-1,-1,0)です。これは、*何らかの方法で変換しなければ*、スクリーン上の(-1,-1)に表示されることを意味します。これはどういう意味でしょう？スクリーンの原点は中心にあり、Xはいつもどおり右側にあり、Yは上側にあります。これはワイドスクリーン上を指すものとなります。

![screenCoordinates]({{site.baseurl}}/assets/images/tuto-2-first-triangle/screenCoordinates.png){: height="165px" width="300px"}


これは変えることができません。グラフィックカードにビルトインされています。だから(-1,-1)はスクリーンの左下です。(1,-1)は右下、(0,1)は中央上です。だから三角形はスクリーンの大部分を占めます。

# 三角形を描く

次のステップはこの三角形をOpenGLに渡すことです。これはバッファを作ることで行います。

``` cpp

// これが頂点バッファを指し示すものとなります。
GLuint vertexbuffer;

// バッファを1つ作り、vertexbufferに結果IDを入れます。
glGenBuffers(1, &vertexbuffer);

// 次のコマンドは'vertexbuffer'バッファについてです。
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// 頂点をOpenGLに渡します。
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
```

これは一度だけ行われる必要があります。

今、メインループ内の、"何も描かなかった"場所に、私たちの素晴らしい三角形を描けます。

``` cpp
// 最初の属性バッファ：頂点
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
   3,                  // サイズ
   GL_FLOAT,           // タイプ
   GL_FALSE,           // 正規化？
   0,                  // ストライド
   (void*)0            // 配列バッファオフセット
);

// 三角形を描きます！
glDrawArrays(GL_TRIANGLES, 0, 3); // 頂点0から始まります。合計3つの頂点です。&rarr;1つの三角形です。

glDisableVertexAttribArray(0);
```

もし運がよければ、次のような結果を見られます。 (<span style="color: #ff0000">出てこなくてもあせらないでください。</span>) :

![triangle_no_shader]({{site.baseurl}}/assets/images/tuto-2-first-triangle/triangle_no_shader1.png){: height="232px" width="300px"}


これは、つまらない白色です。そこで赤に塗ることで改善しましょう。これはシェーダと呼ばれるものを使うことで実現できます。

# シェーダ


## シェーダのコンパイル

最も簡単で可能な設定では、2つのシェーダが必要となります。一つは頂点シェーダで、各頂点で実行されます。もう一つはフラグメントシェーダで書くサンプルで実行されます。4xアンチエイリアスを使うので、各ピクセルで4つのサンプルがあります。

シェーダは、GLSLと呼ばれる言語でプログラムできます。GLシェーダ言語(GL Shader Language)はOpenGLの一部です。CやJavaとは異なり、GLSLは実行時にコンパイルされます。これはアプリケーションを起動するたびにシェーダは再度コンパイルされることを意味します。

2つのシェーダは通常異なるファイルに書きます。この例では、SimpleFragmentShader.fragmentshaderとSimpleVertexShader.vertexshaderです。拡張子は重要ではありません。だから.txtや.glslでも良いです。

ここでコードを示します。完全に理解するのは重要では在りません。なぜならこれはプログラム内で一度しか使わないからです。だからコメントだけで充分でしょう。これは他のすべてのチュートリアルで使われます。そのため別のファイル(common/loadShader.cpp)に置いておきます。バッファのように、シェーダは直接アクセスできませんないことに注意してください。IDがあります。実際の実装はドライバの中に隠されています。

``` cpp
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // シェーダを作ります。
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // ファイルから頂点シェーダのコードを読み込みます。
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }

    // ファイルからフラグメントシェーダを読み込みます。
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // 頂点シェーダをコンパイルします。
    printf("Compiling shader : %sn", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // 頂点シェーダをチェックします。
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);

    // フラグメントシェーダをコンパイルします。
    printf("Compiling shader : %sn", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // フラグメントシェーダをチェックします。
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%sn", &FragmentShaderErrorMessage[0]);

    // プログラムをリンクします。
    fprintf(stdout, "Linking programn");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // プログラムをチェックします。
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector ProgramErrorMessage( max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%sn", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
```

## 頂点シェーダ

まず頂点シェーダを書いていきましょう。
最初の行はコンパイラにOpenGL3のシンタックスを使うことを知らせています。

``` glsl
#version 330 core
```
{: .highlightglslvs }

2行目はインプットデータを宣言します。

``` glsl
layout(location = 0) in vec3 vertexPosition_modelspace;
```
{: .highlightglslvs }

これをより詳しく説明しましょう。

* "vec3"はGLSLでの3つの要素を持つベクトルです。三角形を宣言するときに使ったglm::vec3と似ていますが違うものです。重要なことはC++で3要素を使ったら、GLSLでも3要素を使わなければいけないことです。
* "layout(location = 0)はバッファを表し、*vertexPosition_modelspace*属性に与えるために使います。各頂点は複数の属性を持つことができます。例えば、位置やいくつかの色、いくつかのテクスチャ座標などです。OpenGLは何色か知りません。だからvec3を見ます。だからOpenGLにどのインプットがどのバッファに相当するかを知らせる必要があります。layoutとglVertexAttribPointerの最初のパラメータと同じとなるようにセットすることで行います。"0"という値にいみはなく12(glGetIntegerv(GL_MAX_VERTEX_TATTRIBS,&v)を超えなければ)でも良いです。重要なことは両方で同じ数字を使うことです。
* "vertexPosition_modelspace"は他の名前でも良いです。頂点シェーダの実行後とに頂点の座標を持ちます。
* "in"はこれがインプットデータであることを表します。少し後で"out"キーワードも出てきます。


各頂点で呼ばれるこの関数はmainで呼ばれます。Cのように。

``` glsl
void main(){
```
{: .highlightglslvs }

メイン関数では単に頂点位置にバッファ内に何があるかをセットします。だから(1,1)を与えれば、三角形はスクリーンの右上を頂点の一つとして持つということになります。次のチュートリアルでは、インプット位置上の、より興味深い処理を見ていきます。

``` glsl
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
 }
```
{: .highlightglslvs }

gl_Position is one of the few built-in variables : you *have *to assign some value to it. Everything else is optional; we'll see what "everything else" means in Tutorial 4.

## フラグメントシェーダ

最初のフラグメントシェーダは、とてもシンプルなものとなります。各フラグメントに赤をセットします。(注意してほしいのは、4x AAを使っているので、各ピクセルごとに4つのフラグメントがあります。)

``` glsl
#version 330 core
out vec3 color;

void main(){
    color = vec3(1,0,0);
}
```
{: .highlightglslfs }

だから、vec3(1,0,0)は赤を意味します。これはコンピュータスクリーンでは色は赤、緑、青の順番の3つ組で表されるからです。だから(1,0,0)はすべて赤で、緑と青はありません。

# すべてを合わせる

メインループの前で、LoadShaders関数を呼びましょう。

``` cpp
// シェーダからGLSLプログラムを作りコンパイルする。
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
```

メインループの中で、まずスクリーンをクリアしています。これは背景色をダークブルーに変更しています。なぜならメインループの上でglClearColor(0.0f, 0.0f, 0.4f, 0.0f)を読んでいるからです。

``` cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

そしてOpenGLに使いたいシェーダを伝えます。

``` cpp
// シェーダを使う
glUseProgram(programID);

// 三角形を描く...
```

... さぁ、ここに赤い三角形があります！

![red_triangle]({{site.baseurl}}/assets/images/tuto-2-first-triangle/red_triangle.png){: height="231px" width="300px"}


次のチュートリアルは変換を学びます。つまりどのようにカメラをセットアップし、オブジェクトを動かすかなどを学びます。
