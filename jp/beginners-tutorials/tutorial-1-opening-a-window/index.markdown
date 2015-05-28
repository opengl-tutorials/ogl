---
layout: page
status: publish
published: true
title: チュートリアル1：ウィンドウを開く
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1285
wordpress_url: http://www.opengl-tutorial.org/?page_id=1285
date: '2014-06-20 01:15:11 +0100'
date_gmt: '2014-06-20 01:15:11 +0100'
categories: []
tags: []
comments: []
language: jp
---
<h1>イントロダクション<&#47;h1><br />
最初のチュートリアルにようこそ！</p>
<p>OpenGLの世界に飛び込む前に、最初に各チュートリアルで使うコードのビルドの方法、実行方法、そして最も重要な、コードを自分自身でいじる方法を学びます。</p>
<h1>前提条件<&#47;h1><br />
これ以降のチュートリアルでは特別な前提条件はありません。コードをより良く理解するためには、プログラミング(C、Java、Lisp、Javascriptなど) の経験があれば良いですが、必ずしも必要ではありません。なぜなら、二つのことを同時に学ぶことは、ただより複雑になるだけだからです。</p>
<p>すべてのチュートリアルは簡単なC++で書いています。テンプレートやクラス、ポインタなどを使わないで、できるだけシンプルになるようにコードを作りました。だから、Javaしか知らなくてもすべて理解できるでしょう。</p>
<h1>全部忘れてください<&#47;h1><br />
前提知識は必要ありませんが、ひとまずOpenGLに関する知識は忘れてください<br />
特に、glBegin()などを知っているなら忘れてください。ここで学ぶのはモダンOpenGL(OpenGL3と4)です。しかし、ネット上のほとんどのチュートリアルは古いOpenGL(OpenGL1と2)に関するものです。だから、混乱しないようにOpenGLに関する知識を忘れてください。</p>
<h1>チュートリアルのビルド<&#47;h1><br />
どのチュートリアルもWindows、Linux、Mac上でビルドできます。どのプラットフォームでも、ビルドの手順はだいたい同じです。</p>
<ol>
<li><strong>ドライバを更新しましょう！！<&#47;strong> 絶対にやってください。忠告しましたよ。<&#47;li>
<li>コンパイラがないなら、コンパイラをダウンロードします。<&#47;li>
<li>CMakeをインストールします。<&#47;li>
<li>チュートリアルのソースコードをダウンロードします。<&#47;li>
<li>CMakeを使ってプロジェクトを作ります。<&#47;li>
<li>プロジェクトをビルドします。<&#47;li>
<li>サンプルで遊びましょう！<&#47;li><br />
<&#47;ol><br />
各プラットフォームごとの詳しい手順を以下に示します。少しの変更は必要かもしれません。もし自信がなければ、Windowsでの導入方法を読んでから、それぞれに合うようにやってみてください。</p>
<h2>Windowsでのビルド<&#47;h2></p>
<ol>
<li>ドライバのアップデートは簡単です。NVIDIAやAMDのウェブサイトに行ってドライバをダウンロードしてください。もしGPUモデルが分からないなら、コントロールパネル&rarr;システムとセキュリティ&rarr;システム&rarr;デバイスマネージャー&rarr;ディスプレイアダプター を確認してください。もしインテル内臓GPUならば、ドライバはOEM(Dell、HP、&hellip;)から提供されます。<&#47;li>
<li>コンパイラとしてはVisual Studio 2010 Expressを使うことを推奨します。<a href="http:&#47;&#47;www.visualstudio.com&#47;downloads&#47;download-visual-studio-vs" target="_blank">ここから<&#47;a>無料でダウンロードできます。もしMinGWを使いたいなら、<a href="http:&#47;&#47;qt-project.org&#47;">QT Creator<&#47;a>の使用をお薦めます。 そして、インストールします。これ以降のステップはVisual Studioを使って説明していきます。しかし他のIDEでも同じように進めていけるでしょう。<&#47;li>
<li>ここから<a href="http:&#47;&#47;www.cmake.org&#47;cmake&#47;resources&#47;software.html" target="_blank">CMake <&#47;a>をダウンロードして、インストールしてください。<&#47;li>
<li><a title="Download" href="&#47;?page_id=200" target="_blank">ソースコードをダウンロードしてください。<&#47;a>そして、例えばC:UsersXYZProjectsOpenGLTutorialsなどに解凍してください。<&#47;li>
<li>CMakeを起動してください。最初の項目には解凍したフォルダを指定してください。もし自信がなければ、CMakeLists.txtがあるフォルダを選んでください。次の項目にはコンパイラに関するものを置く場所を指定してください。例えば、次のように選択できます。C:UsersXYZProjectsOpenGLTutorials-build-Visual2010-32bits やC:UsersXYZProjectsOpenGLTutorialsbuildVisual2010-32bits です。ただし、必ずしも同じフォルダでなくても大丈夫です。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CMake.png"><img class="alignnone size-medium wp-image-8" title="CMake" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CMake.png" alt="" width="846" height="392" &#47;><&#47;a><&#47;li></p>
<li>Configureボタンをクリックしてください。プロジェクトの設定をするのは初めてなので、CMakeはどのコンパイラを使うか聞いてきます。ステップ1に従って選んでください。64bit Windowsなら64bitsを選んでください。わからなければ32bitsを選んでください。<&#47;li>
<li>すべての赤いラインが消えるまでConfigureをクリックしてください。Generateをクリックしてください。Visual Studioプロジェクトが作られます。CMakeの役割は終わりなのでアンインストールしてしまってもかまいません。<&#47;li>
<li>C:UsersXYZProjectsOpenGLTutorials-build-Visual2010-32bitsを開いてください。すると、Tutorials.slnが見つかるので、Visual Studioで開いてください。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;directories.png"><img class="alignnone size-medium wp-image-9" title="directories" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;directories.png" alt="" width="560" height="302" &#47;><&#47;a><br />
In the <em>ビルド<&#47;em>メニューから<em>すべてをビルド<&#47;em>を選んでください。すべてのチュートリアルと依存関係がコンパイルされます。各exeファイルはC:UsersXYZProjectsOpenGLTutorialsにコピーされます。たぶん、エラーは出ないでしょう。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;visual_2010.png"><img class="alignnone size-medium wp-image-11" title="visual_2010" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;visual_2010-300x212.png" alt="" width="300" height="212" &#47;><&#47;a><&#47;li></p>
<li>Open C:UsersXYZProjectsOpenGLTutorialsplaygroundを開きplayground.exeを起動してください。黒いウィンドウが現れると思います。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;empty_window.png"><img class="alignnone size-medium wp-image-10" title="empty_window" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;empty_window-300x231.png" alt="" width="300" height="231" &#47;><&#47;a><&#47;li><br />
<&#47;ol><br />
Visual Studioから各チュートリアルを起動できます。Playgroundを右クリックして「スタートアッププロジェクトに設定」を選びます。F5を押すことでデバッグできます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;WorkingDir.png"><img class="size-medium wp-image-546 alignnone" title="WorkingDir" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;WorkingDir-300x211.png" alt="" width="300" height="211" &#47;><&#47;a><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2012&#47;04&#47;StartupProject.png"><img class="size-medium wp-image-544 alignright" title="StartupProject" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2012&#47;04&#47;StartupProject-185x300.png" alt="" width="185" height="300" &#47;><&#47;a></p>
<h2><&#47;h2></p>
<h2><&#47;h2></p>
<h2><&#47;h2></p>
<h2>Linuxでのビルド<&#47;h2><br />
Linuxの各プラットフォームごとに説明するのは不可能なので、必要に応じて変更してください。そして各ディストリビューションのドキュメントを読むのを嫌がらないでください。</p>
<ol>
<li>最新のドライバをインストールしてください。<br />
クローズドソースのバイナリドライバを強くお薦めします。<br />
GNUなどではありませんが、きちんと動きます。<br />
もしディストリビューションが自動インストールを提供していないなら、<a href="http:&#47;&#47;help.ubuntu.com&#47;community&#47;BinaryDriverHowto" target="_blank">Ubuntu's guide<&#47;a>を試してください。<&#47;li></p>
<li>必要なコンパイラ、ツール、ライブラリをすべてインストールしてください。具体的には <em>cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev<&#47;em>をインストールしてください。そして、「apt-get install *****」か「su &amp;&amp; yum install ******」を使ってください。<&#47;li>
<li><a title="Download" href="&#47;?page_id=200" target="_blank">ソースコードをダウンロード<&#47;a>して、例えば、~&#47;Projects&#47;OpenGLTutorials&#47;に解凍してください。<&#47;li>
<li>~&#47;Projects&#47;OpenGLTutorials&#47;に移動して次のコマンドを実行してください。
<ul>
<li>mkdir build<&#47;li>
<li>cd build<&#47;li>
<li>cmake ..<&#47;li><br />
<&#47;ul><br />
<&#47;li></p>
<li>build&#47;ディレクトリにmakefileが作られます。<&#47;li>
<li>"make all"をタイプしてください。すべてのチュートリアルと依存関係がコンパイルされます。各実行ファイルは~&#47;Projects&#47;OpenGLTutorials&#47;にコピーされます。たぶん、エラーは出ないでしょう。<&#47;li>
<li>~&#47;Projects&#47;OpenGLTutorials&#47;playgroundを開いて、.&#47;playgroundを起動してください。黒いウィンドウが現れます。<&#47;li><br />
<&#47;ol><br />
<a href="http:&#47;&#47;qt-project.org&#47;">Qt Creator<&#47;a>などのIDEを使うべきです。特にこれはCMakeをビルトインでサポートしています。そしてデバッグするときにより良い体験を提供するでしょう。以下にQtCreatorでの手順を示します。</p>
<ol>
<li>QtCreatorでFile->Tools->Options->Compile&amp;Execute->CMakeに行きます。<&#47;li>
<li>CMakeへのパスを指定します。だいたい&#47;usr&#47;bin&#47;cmakeでしょう。<&#47;li>
<li>File->Open Projectでtutorials&#47;CMakeLists.txtを選んでください。<&#47;li>
<li>ビルドディレクトリを選んでください。できればチュートリアルフォルダの外にしてください。<&#47;li>
<li>任意で、-DCMAKE_BUILD_TYPE=Debugをparameters boxにセットしてください。Validateしてください。<&#47;li>
<li>下にあるハンマーをクリックしてください。tutorials&#47;からチュートリアルが起動できるでしょう。<&#47;li>
<li>QtCreatorからチュートリアルを実行するために、Projects->Execution parameters->Working Directoryをクリックし、シェーダとテクスチャとモデルがあるディレクトリを選んでください。チュートリアル2では~&#47;opengl-tutorial&#47;tutorial02_red_triangle&#47;となります。<&#47;li><br />
<&#47;ol></p>
<h2>Macでのビルド<&#47;h2><br />
MacOSはOpenGL3.3をサポートしていません。最新のMacOS 10.7 LionとコンパティブルGPUはOpenGL3.2は実行できます。(3.3ではありません。)代わりに、チュートリアルの2.1ポートを使用してください。それは別として、手順はWindowsと良く似ています。(MakeFileもサポートされていますが、ここでは説明しません。)</p>
<ol>
<li>Mac App StoreからXCodeをインストールします。<&#47;li>
<li><a href="http:&#47;&#47;www.cmake.org&#47;cmake&#47;resources&#47;software.html">CMakeをダウンロード<&#47;a>し、.dmgをインストールします。コマンドラインツールはインストールする必要はありません。<&#47;li>
<li><a title="Download" href="&#47;?page_id=200" target="_blank">3.ソースコードをダウンロードしてください。<&#47;a>(バージョンは2.1！！) そして、例えば~&#47;Projects&#47;OpenGLTutorials&#47;に解凍してください。<&#47;li>
<li>CMake(Applications->CMake)を起動してください。最初の項目に解凍したフォルダを指定してください。(CMakeLists.txtを含むフォルダです。)次の項目にコンパイラ関係のものを置く場所を指定してください。例えば、~&#47;Projects&#47;OpenGLTutorials_bin_XCode&#47;を選んでください。必ずしもこのフォルダでなくても大丈夫です。<&#47;li>
<li>Configureボタンをクリックしてください。プロジェクトを設定するのが初めてなので、CMakeはどのコンパイラを使うか聞いてきます。Xcodeを選んでください。<&#47;li>
<li>赤いラインが消えるまでConfigureをクリックしてください。Generateをクリックしてください。これで、Xcodeプロジェクトが作成されます。CMakeの役割はこれで終わりなので、アンインストールしても構いません。<&#47;li>
<li>~&#47;Projects&#47;OpenGLTutorials_bin_XCode&#47;を開いてください。Tutorials.xcodeproj ファイルが見つかるので、それを開いてください。<&#47;li>
<li>Xcode&rsquo;s Scheme panelの中から実行したいチュートリアルを選んでください。そしてRunボタンで、コンパイルと実行をしてください。<&#47;li><br />
<&#47;ol><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;Xcode-projectselection.png"><img class="alignnone size-full wp-image-643" title="Xcode-projectselection" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;Xcode-projectselection.png" alt="" width="826" height="330" &#47;><&#47;a></p>
<h2>Code::Blocksに関するメモ<&#47;h2><br />
2つのバグ(ひとつはC::B、もう一つはCMake)のため、Project->Build Options->Make commandsのコマンドラインを次のように編集する必要があります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CodeBlocksFix.png"><img class="alignnone size-full wp-image-712" title="CodeBlocksFix" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CodeBlocksFix.png" alt="" width="746" height="340" &#47;><&#47;a></p>
<p>また、ワーキングディレクトリも自分で設定する必要があります。Project->Properties -> Build targets -> tutorial N -> execution working dir (これはsrc_dir&#47;tutorial_N&#47;です。)</p>
<h1>チュートリアルの実行<&#47;h1><br />
正しいディレクトリからチュートリアルを実行すべきです。単に実行ファイルをダブルクリックするだけです。もしコマンドラインがよければ、正しいディレクトリに移動してください。</p>
<p>IDEから実行したければ、上で説明したように正しいワーキングディレクトリを設定するのを忘れないでください。</p>
<h1>チュートリアルのたどり方<&#47;h1>各チュートリアルはソースコードとデータからできています。tutorialXX&#47;で見つけられると思います。ただし、これらのプロジェクトを決して編集しないでください。リファレンス用として使ってください。playground&#47;playground.cppを開いて、代わりにこのファイルを微調整してください。このファイルを好きなように編集してください。もし迷子になったら、単純にそのファイルにコピー&amp;ペーストしてください。それで標準に戻ります。</p>
<p>各チュートリアルではコードの一部を載せています。チュートリアルを読む一方で、playgroundに直接コピー&amp;ペーストするのを嫌がらないでください。経験するのが良いのです。単純に完成したコードを読むのを避けていては、このような方法では多くは学べないでしょう。シンプルなコピー＆ペーストでさえ、多くの問題が出てくるでしょう。</p>
<h1>ウィンドウを開く<&#47;h1><br />
ついに！OpenGLのコードです！<br />
ええと、実際は違います。すべてのチュートリアルでは、マジックを使わず、"low level"な方法を見せます。しかし、このパートはとてもつまらなく役に立ちません。だから、私たちの代わりにこれをやってくれる、外部のライブラリのGLFWを使います。もし本当にやりたいならば、WindowsではWin32 API、LinuxではX11 API、MacではCocoa APIを使ってください。あるいはSFML、FreeGLUT、SDL、&hellip; を使ってください。<a title="Useful Tools &amp; Links" href="&#47;?page_id=210" target="_blank">Links<&#47;a>ページを見てください。</p>
<p>OK、それでは行きましょう。まず、依存関係に対処します。コンソールにメッセージを表示するための基本的なものが必要となります。</p>
<pre class="brush:cpp">&#47;&#47; 標準ヘッダをインクルードします。<br />
#include<br />
#include <&#47;pre><br />
最初のGLEWです。だからこれはちょっとしたマジックです。しかし後のために残しておきましょう。</p>
<pre class="brush:cpp">&#47;&#47; GLEWをインクルードする。常にgl.hとglfw.hより先にインクルードしましょう。これはちょっとしたマジックです。<br />
#include <&#47;pre><br />
GLFWでウィンドウとキーボードを扱うため、次のものもインクルードしましょう。</p>
<pre class="brush: cpp">&#47;&#47; GLFWをインクルードします。<br />
#include <&#47;pre><br />
このライブラリは実際はすぐには使いません。これは3D数学のためのライブラリです。すぐに、とても便利なことが分かるでしょう。GLMにはマジックはありません。必要があれば自分自身でも書けます。ですが、GLMはとても使いやすいです。"using namespace"があることで"glm::vec3"と書く代わりに、"vec3"と書けます。</p>
<pre class="brush: cpp">&#47;&#47; GLMをインクルードします。<br />
#include<br />
using namespace glm;<&#47;pre><br />
これらの#includeをplayground.cppにコピー＆ペーストしたならば、コンパイラはmain()関数がないと言うでしょう。だから作りましょう。</p>
<pre class="brush: cpp">int main(){<&#47;pre><br />
最初にGLFWを初期化します。</p>
<pre class="brush: cpp">&#47;&#47; GLFWを初期化します。<br />
if( !glfwInit() )<br />
{<br />
    fprintf( stderr, "GLFWの初期化に失敗しました。n" );<br />
    return -1;<br />
}<&#47;pre><br />
それでは、最初のOpenGLウィンドウを作りましょう！</p>
<pre class="brush: cpp">glfwWindowHint(GLFW_SAMPLES, 4); &#47;&#47; 4x アンチエイリアス<br />
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); &#47;&#47; OpenGL3.3を使います。<br />
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);<br />
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); &#47;&#47; MacOS用：必ずしも必要ではありません。<br />
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); &#47;&#47; 古いOpenGLは使いません。</p>
<p>&#47;&#47; Windowを開き、OpenGLコンテキストを作ります<br />
GLFWwindow* window; &#47;&#47; (ソースコードではこの変数はグローバルです。)<br />
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);<br />
if( window == NULL ){<br />
    fprintf( stderr, "GLFWウィンドウのオープンに失敗しました。 もしIntelのGPUならば, 3.3に対応していません。チュートリアルのバージョン2.1を試してください。n" );<br />
    glfwTerminate();<br />
    return -1;<br />
}<br />
glfwMakeContextCurrent(window); &#47;&#47; GLEWを初期化する<br />
glewExperimental=true; &#47;&#47; コアプロファイルで必要となります。<br />
if (glewInit() != GLEW_OK) {<br />
    fprintf(stderr, "GLEWの初期化に失敗しました。n");<br />
    return -1;<br />
}<&#47;pre><br />
するとウィンドウが出てきますが、すぐに閉じてしまいます。もちろん！ユーザがエスケープキーを押すまで待っている必要があります。</p>
<pre class="brush: cpp">&#47;&#47; 下でエスケープキーが押されるのを捉えるのを保証します。<br />
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);</p>
<p>do{<br />
    &#47;&#47; 何も描きません。チュートリアル2で会いましょう！</p>
<p>    &#47;&#47; バッファをスワップする。<br />
    glfwSwapBuffers(window);<br />
    glfwPollEvents();</p>
<p>} &#47;&#47; ESCキーが押されたかウィンドウが閉じたかをチェックする。<br />
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &amp;&amp;<br />
glfwWindowShouldClose(window) == 0 );<&#47;pre><br />
これで最初のチュートリアルは終了です。チュートリアル2では、実際に三角形を描く方法を学びます。<br />
&#47;&#47; </p>
