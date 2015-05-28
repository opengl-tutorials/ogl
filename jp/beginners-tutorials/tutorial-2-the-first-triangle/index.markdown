---
layout: page
status: publish
published: true
title: チュートリアル2：最初の三角形
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1286
wordpress_url: http://www.opengl-tutorial.org/?page_id=1286
date: '2014-06-20 01:16:14 +0100'
date_gmt: '2014-06-20 01:16:14 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p><!-- Include required JS files --><br />
<!--     At least one brush, here we choose JS. You need to include a brush for every     language you want to highlight --></p>
<p>これはもう一つの長いチュートリアルです。</p>
<p>OpenGL3は複雑なものを簡単に書くことができます。しかし、単純な三角形を描くことが実際とても難しくなります。</p>
<p>習慣的にコードをコピー＆ペーストするのを忘れないでください。</p>
<blockquote><p><span style="color: #ff0000">もし始めの段階でプログラムがクラッシュするなら、間違ったディレクトリで実行しているかもしれません。チュートリアル1のVisual Studioの設定方法を注意深く読んでください！<&#47;span><&#47;blockquote></p>
<h1>VAO<&#47;h1><br />
ここでは詳しく述べません。しかし配列バッファオブジェクト(Vertex Array Object)を作り、現在のものとしてセットする必要があります。</p>
<pre class="brush: cpp">GLuint VertexArrayID;<br />
glGenVertexArrays(1, &amp;VertexArrayID);<br />
glBindVertexArray(VertexArrayID);<&#47;pre><br />
ウィンドウが作られたときにいったんこれを行います。(つまりOpenGLコンテキストを作った後です。)そしてどのOpenGLのコールも呼ぶ前です。</p>
<p>VAOについて詳しく知りたいならば、他のチュートリアルもあります。ただし、これはそれほど重要ではありません。</p>
<h1>スクリーン座標<&#47;h1><br />
三角形は3つの点で定義されています。3Dグラフィックで"点"というとき、通常"頂点"という言葉を使います。一つの頂点は3つの座標を持ちます。つまりX、Y、Zです。これらの3つの座標は次のように考えられます。</p>
<ul>
<li>Xは右方向<&#47;li>
<li>Yは上方向<&#47;li>
<li>Zはあなたの後ろの方向(後ろであって、前ではありません。)<&#47;li><br />
<&#47;ul><br />
しかしこれを視覚化するより良い方法があります。右手の法則を使います。</p>
<ul>
<li>Xは親指<&#47;li>
<li>Yは人差し指<&#47;li>
<li>Zは中指。親指を右方向に、人差し指を上方向に向ければ、中指はあなたの後ろ方向を指すでしょう。<&#47;li><br />
<&#47;ul><br />
Zをこの方向にするのは奇妙に感じます。なぜそうしたのでしょう？端的に言えば、数学の右手の法則の100年が便利なツールをいろいろ与えてくれるからです。この方法のマイナス面はZが直感的でないことです。</p>
<p>ところで、右手を自由に動かすことができます。つまりX、Y、Zも同様に動きます。詳しくは後で述べます。</p>
<p>だから三角形を作るためには、3つの3Dの点が必要となります。それでは見ていきましょう。</p>
<pre class="brush: cpp">&#47;&#47; 3頂点を表す3つのベクトルの配列<br />
static const GLfloat g_vertex_buffer_data[] = {<br />
   -1.0f, -1.0f, 0.0f,<br />
   1.0f, -1.0f, 0.0f,<br />
   0.0f,  1.0f, 0.0f,<br />
};<&#47;pre><br />
最初の点は(-1,-1,0)です。これは、<em>何らかの方法で変換しなければ<&#47;em>、スクリーン上の(-1,-1)に表示されることを意味します。これはどういう意味でしょう？スクリーンの原点は中心にあり、Xはいつもどおり右側にあり、Yは上側にあります。これはワイドスクリーン上を指すものとなります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;screenCoordinates.png"><img class="alignnone size-medium wp-image-16" title="screenCoordinates" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;screenCoordinates-300x165.png" alt="" width="300" height="165" &#47;><&#47;a></p>
<p>これは変えることができません。グラフィックカードにビルトインされています。だから(-1,-1)はスクリーンの左下です。(1,-1)は右下、(0,1)は中央上です。だから三角形はスクリーンの大部分を占めます。</p>
<h1>三角形を描く<&#47;h1><br />
次のステップはこの三角形をOpenGLに渡すことです。これはバッファを作ることで行います。</p>
<pre class="brush: cpp">
&#47;&#47; これが頂点バッファを指し示すものとなります。<br />
GLuint vertexbuffer;</p>
<p>&#47;&#47; バッファを1つ作り、vertexbufferに結果IDを入れます。<br />
glGenBuffers(1, &amp;vertexbuffer);</p>
<p>&#47;&#47; 次のコマンドは'vertexbuffer'バッファについてです。<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);</p>
<p>&#47;&#47; 頂点をOpenGLに渡します。<br />
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);<&#47;pre><br />
これは一度だけ行われる必要があります。</p>
<p>今、メインループ内の、"何も描かなかった"場所に、私たちの素晴らしい三角形を描けます。</p>
<pre class="brush: cpp">&#47;&#47; 最初の属性バッファ：頂点<br />
glEnableVertexAttribArray(0);<br />
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);<br />
glVertexAttribPointer(<br />
   0,                  &#47;&#47; 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。<br />
   3,                  &#47;&#47; サイズ<br />
   GL_FLOAT,           &#47;&#47; タイプ<br />
   GL_FALSE,           &#47;&#47; 正規化？<br />
   0,                  &#47;&#47; ストライド<br />
   (void*)0            &#47;&#47; 配列バッファオフセット<br />
);</p>
<p>&#47;&#47; 三角形を描きます！<br />
glDrawArrays(GL_TRIANGLES, 0, 3); &#47;&#47; 頂点0から始まります。合計3つの頂点です。&rarr;1つの三角形です。</p>
<p>glDisableVertexAttribArray(0);<&#47;pre><br />
もし運がよければ、次のような結果を見られます。 (<span style="color: #ff0000">出てこなくてもあせらないでください。<&#47;span>) :</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;triangle_no_shader1.png"><img class="alignnone size-medium wp-image-858" title="triangle_no_shader" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;triangle_no_shader1-300x232.png" alt="" width="300" height="232" &#47;><&#47;a></p>
<p>これは、つまらない白色です。そこで赤に塗ることで改善しましょう。これはシェーダと呼ばれるものを使うことで実現できます。</p>
<h1>シェーダ<&#47;h1></p>
<h2>シェーダのコンパイル<&#47;h2><br />
最も簡単で可能な設定では、2つのシェーダが必要となります。一つは頂点シェーダで、各頂点で実行されます。もう一つはフラグメントシェーダで書くサンプルで実行されます。4xアンチエイリアスを使うので、各ピクセルで4つのサンプルがあります。</p>
<p>シェーダは、GLSLと呼ばれる言語でプログラムできます。GLシェーダ言語(GL Shader Language)はOpenGLの一部です。CやJavaとは異なり、GLSLは実行時にコンパイルされます。これはアプリケーションを起動するたびにシェーダは再度コンパイルされることを意味します。</p>
<p>2つのシェーダは通常異なるファイルに書きます。この例では、SimpleFragmentShader.fragmentshaderとSimpleVertexShader.vertexshaderです。拡張子は重要ではありません。だから.txtや.glslでも良いです。</p>
<p>ここでコードを示します。完全に理解するのは重要では在りません。なぜならこれはプログラム内で一度しか使わないからです。だからコメントだけで充分でしょう。これは他のすべてのチュートリアルで使われます。そのため別のファイル(common&#47;loadShader.cpp)に置いておきます。バッファのように、シェーダは直接アクセスできませんないことに注意してください。IDがあります。実際の実装はドライバの中に隠されています。</p>
<pre class="brush: cpp">GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){</p>
<p>    &#47;&#47; シェーダを作ります。<br />
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);<br />
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);</p>
<p>    &#47;&#47; ファイルから頂点シェーダのコードを読み込みます。<br />
    std::string VertexShaderCode;<br />
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);<br />
    if(VertexShaderStream.is_open())<br />
    {<br />
        std::string Line = "";<br />
        while(getline(VertexShaderStream, Line))<br />
            VertexShaderCode += "n" + Line;<br />
        VertexShaderStream.close();<br />
    }</p>
<p>    &#47;&#47; ファイルからフラグメントシェーダを読み込みます。<br />
    std::string FragmentShaderCode;<br />
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);<br />
    if(FragmentShaderStream.is_open()){<br />
        std::string Line = "";<br />
        while(getline(FragmentShaderStream, Line))<br />
            FragmentShaderCode += "n" + Line;<br />
        FragmentShaderStream.close();<br />
    }</p>
<p>    GLint Result = GL_FALSE;<br />
    int InfoLogLength;</p>
<p>    &#47;&#47; 頂点シェーダをコンパイルします。<br />
    printf("Compiling shader : %sn", vertex_file_path);<br />
    char const * VertexSourcePointer = VertexShaderCode.c_str();<br />
    glShaderSource(VertexShaderID, 1, &amp;VertexSourcePointer , NULL);<br />
    glCompileShader(VertexShaderID);</p>
<p>    &#47;&#47; 頂点シェーダをチェックします。<br />
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector VertexShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &amp;VertexShaderErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;VertexShaderErrorMessage[0]);</p>
<p>    &#47;&#47; フラグメントシェーダをコンパイルします。<br />
    printf("Compiling shader : %sn", fragment_file_path);<br />
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();<br />
    glShaderSource(FragmentShaderID, 1, &amp;FragmentSourcePointer , NULL);<br />
    glCompileShader(FragmentShaderID);</p>
<p>    &#47;&#47; フラグメントシェーダをチェックします。<br />
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &amp;Result);<br />
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector FragmentShaderErrorMessage(InfoLogLength);<br />
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &amp;FragmentShaderErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;FragmentShaderErrorMessage[0]);</p>
<p>    &#47;&#47; プログラムをリンクします。<br />
    fprintf(stdout, "Linking programn");<br />
    GLuint ProgramID = glCreateProgram();<br />
    glAttachShader(ProgramID, VertexShaderID);<br />
    glAttachShader(ProgramID, FragmentShaderID);<br />
    glLinkProgram(ProgramID);</p>
<p>    &#47;&#47; プログラムをチェックします。<br />
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &amp;Result);<br />
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &amp;InfoLogLength);<br />
    std::vector ProgramErrorMessage( max(InfoLogLength, int(1)) );<br />
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &amp;ProgramErrorMessage[0]);<br />
    fprintf(stdout, "%sn", &amp;ProgramErrorMessage[0]);</p>
<p>    glDeleteShader(VertexShaderID);<br />
    glDeleteShader(FragmentShaderID);</p>
<p>    return ProgramID;<br />
}<&#47;pre></p>
<h2>頂点シェーダ<&#47;h2><br />
まず頂点シェーダを書いていきましょう。<br />
最初の行はコンパイラにOpenGL3のシンタックスを使うことを知らせています。</p>
<pre class="brush: vs">#version 330 core<&#47;pre><br />
2行目はインプットデータを宣言します。</p>
<pre class="brush: vs">layout(location = 0) in vec3 vertexPosition_modelspace;<&#47;pre><br />
これをより詳しく説明しましょう。</p>
<ul>
<li>"vec3"はGLSLでの3つの要素を持つベクトルです。三角形を宣言するときに使ったglm::vec3と似ていますが違うものです。重要なことはC++で3要素を使ったら、GLSLでも3要素を使わなければいけないことです。<&#47;li>
<li>"layout(location = 0)はバッファを表し、<em>vertexPosition_modelspace<&#47;em>属性に与えるために使います。各頂点は複数の属性を持つことができます。例えば、位置やいくつかの色、いくつかのテクスチャ座標などです。OpenGLは何色か知りません。だからvec3を見ます。だからOpenGLにどのインプットがどのバッファに相当するかを知らせる必要があります。layoutとglVertexAttribPointerの最初のパラメータと同じとなるようにセットすることで行います。"0"という値にいみはなく12(glGetIntegerv(GL_MAX_VERTEX_TATTRIBS,&amp;v)を超えなければ)でも良いです。重要なことは両方で同じ数字を使うことです。<&#47;li>
<li>"vertexPosition_modelspace"は他の名前でも良いです。頂点シェーダの実行後とに頂点の座標を持ちます。<&#47;li>
<li>"in"はこれがインプットデータであることを表します。少し後で"out"キーワードも出てきます。<&#47;li><br />
<&#47;ul></p>
<p>各頂点で呼ばれるこの関数はmainで呼ばれます。Cのように。</p>
<pre class="brush: vs">void main(){<&#47;pre><br />
メイン関数では単に頂点位置にバッファ内に何があるかをセットします。だから(1,1)を与えれば、三角形はスクリーンの右上を頂点の一つとして持つということになります。次のチュートリアルでは、インプット位置上の、より興味深い処理を見ていきます。</p>
<pre class="brush: vs">    gl_Position.xyz = vertexPosition_modelspace;<br />
    gl_Position.w = 1.0;<br />
 }<&#47;pre><br />
gl_Position is one of the few built-in variables : you <em>have <&#47;em>to assign some value to it. Everything else is optional; we'll see what "everything else" means in Tutorial 4.</p>
<h2>フラグメントシェーダ<&#47;h2><br />
最初のフラグメントシェーダは、とてもシンプルなものとなります。各フラグメントに赤をセットします。(注意してほしいのは、4x AAを使っているので、各ピクセルごとに4つのフラグメントがあります。)</p>
<pre class="brush: fs">#version 330 core<br />
out vec3 color;</p>
<p>void main(){<br />
    color = vec3(1,0,0);<br />
}<&#47;pre><br />
だから、vec3(1,0,0)は赤を意味します。これはコンピュータスクリーンでは色は赤、緑、青の順番の3つ組で表されるからです。だから(1,0,0)はすべて赤で、緑と青はありません。</p>
<h1>すべてを合わせる<&#47;h1><br />
メインループの前で、LoadShaders関数を呼びましょう。</p>
<pre class="brush: cpp">&#47;&#47; シェーダからGLSLプログラムを作りコンパイルする。<br />
GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );<&#47;pre><br />
メインループの中で、まずスクリーンをクリアしています。これは背景色をダークブルーに変更しています。なぜならメインループの上でglClearColor(0.0f, 0.0f, 0.4f, 0.0f)を読んでいるからです。</p>
<pre class="brush: cpp">glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);<&#47;pre><br />
そしてOpenGLに使いたいシェーダを伝えます。</p>
<pre class="brush: cpp">&#47;&#47; シェーダを使う<br />
glUseProgram(programID);</p>
<p>&#47;&#47; 三角形を描く...<&#47;pre><br />
... さぁ、ここに赤い三角形があります！</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;red_triangle.png"><img class="alignnone size-medium wp-image-15" title="red_triangle" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;red_triangle-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<p>次のチュートリアルは変換を学びます。つまりどのようにカメラをセットアップし、オブジェクトを動かすかなどを学びます。</p>
