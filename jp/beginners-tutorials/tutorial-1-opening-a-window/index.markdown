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

#イントロダクション

最初のチュートリアルにようこそ！

OpenGLの世界に飛び込む前に、最初に各チュートリアルで使うコードのビルドの方法、実行方法、そして最も重要な、コードを自分自身でいじる方法を学びます。

#前提条件

これ以降のチュートリアルでは特別な前提条件はありません。コードをより良く理解するためには、プログラミング(C、Java、Lisp、Javascriptなど) の経験があれば良いですが、必ずしも必要ではありません。なぜなら、二つのことを同時に学ぶことは、ただより複雑になるだけだからです。

すべてのチュートリアルは簡単なC++で書いています。テンプレートやクラス、ポインタなどを使わないで、できるだけシンプルになるようにコードを作りました。だから、Javaしか知らなくてもすべて理解できるでしょう。

#全部忘れてください

前提知識は必要ありませんが、ひとまずOpenGLに関する知識は忘れてください
特に、glBegin()などを知っているなら忘れてください。ここで学ぶのはモダンOpenGL(OpenGL3と4)です。しかし、ネット上のほとんどのチュートリアルは古いOpenGL(OpenGL1と2)に関するものです。だから、混乱しないようにOpenGLに関する知識を忘れてください。

#チュートリアルのビルド

どのチュートリアルもWindows、Linux、Mac上でビルドできます。どのプラットフォームでも、ビルドの手順はだいたい同じです。

* **ドライバを更新しましょう！！** 絶対にやってください。忠告しましたよ。
* コンパイラがないなら、コンパイラをダウンロードします。
* CMakeをインストールします。
* チュートリアルのソースコードをダウンロードします。
* CMakeを使ってプロジェクトを作ります。
* プロジェクトをビルドします。
* サンプルで遊びましょう！

各プラットフォームごとの詳しい手順を以下に示します。少しの変更は必要かもしれません。もし自信がなければ、Windowsでの導入方法を読んでから、それぞれに合うようにやってみてください。

##Windowsでのビルド


* ドライバのアップデートは簡単です。NVIDIAやAMDのウェブサイトに行ってドライバをダウンロードしてください。もしGPUモデルが分からないなら、コントロールパネル&rarr;システムとセキュリティ&rarr;システム&rarr;デバイスマネージャー&rarr;ディスプレイアダプター を確認してください。もしインテル内臓GPUならば、ドライバはOEM(Dell、HP、...)から提供されます。
* コンパイラとしてはVisual Studio 2010 Express for Desktopを使うことを推奨します。[ここから](https://www.visualstudio.com/en-US/products/visual-studio-express-vs)無料でダウンロードできます。もしMinGWを使いたいなら、[QT Creator](http://qt-project.org/)の使用をお薦めます。 そして、インストールします。これ以降のステップはVisual Studioを使って説明していきます。しかし他のIDEでも同じように進めていけるでしょう。
* ここから[CMake ](http://www.cmake.org/cmake/resources/software.html)をダウンロードして、インストールしてください。
* [ソースコードをダウンロードしてください。](/?page_id=200)そして、例えばC:UsersXYZProjectsOpenGLTutorialsなどに解凍してください。
* CMakeを起動してください。最初の項目には解凍したフォルダを指定してください。もし自信がなければ、CMakeLists.txtがあるフォルダを選んでください。次の項目にはコンパイラに関するものを置く場所を指定してください。例えば、次のように選択できます。C:UsersXYZProjectsOpenGLTutorials-build-Visual2010-32bits やC:UsersXYZProjectsOpenGLTutorialsbuildVisual2010-32bits です。ただし、必ずしも同じフォルダでなくても大丈夫です。
![]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)

* Configureボタンをクリックしてください。プロジェクトの設定をするのは初めてなので、CMakeはどのコンパイラを使うか聞いてきます。ステップ1に従って選んでください。64bit Windowsなら64bitsを選んでください。わからなければ32bitsを選んでください。
* すべての赤いラインが消えるまでConfigureをクリックしてください。Generateをクリックしてください。Visual Studioプロジェクトが作られます。CMakeの役割は終わりなのでアンインストールしてしまってもかまいません。
* C:UsersXYZProjectsOpenGLTutorials-build-Visual2010-32bitsを開いてください。すると、Tutorials.slnが見つかるので、Visual Studioで開いてください。
![]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)

In the *ビルド*メニューから*すべてをビルド*を選んでください。すべてのチュートリアルと依存関係がコンパイルされます。各exeファイルはC:UsersXYZProjectsOpenGLTutorialsにコピーされます。たぶん、エラーは出ないでしょう。
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

* Open C:UsersXYZProjectsOpenGLTutorialsplaygroundを開きplayground.exeを起動してください。黒いウィンドウが現れると思います。
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)


Visual Studioから各チュートリアルを起動できます。Playgroundを右クリックして「スタートアッププロジェクトに設定」を選びます。F5を押すことでデバッグできます。

![]({{site.baseurl}}/assets/images/tuto-1-window/WorkingDir.png)
![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)











##Linuxでのビルド

Linuxの各プラットフォームごとに説明するのは不可能なので、必要に応じて変更してください。そして各ディストリビューションのドキュメントを読むのを嫌がらないでください。

* 最新のドライバをインストールしてください。
クローズドソースのバイナリドライバを強くお薦めします。
GNUなどではありませんが、きちんと動きます。
もしディストリビューションが自動インストールを提供していないなら、[Ubuntu's guide](http://help.ubuntu.com/community/BinaryDriverHowto)を試してください。
* 必要なコンパイラ、ツール、ライブラリをすべてインストールしてください。具体的には *cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev*をインストールしてください。そして、「apt-get install *****」か「su && yum install ******」を使ってください。
* [ソースコードをダウンロード](/?page_id=200)して、例えば、~/Projects/OpenGLTutorials/に解凍してください。
* ~/Projects/OpenGLTutorials/に移動して次のコマンドを実行してください。

* mkdir build
* cd build
* cmake ..


* build/ディレクトリにmakefileが作られます。
* "make all"をタイプしてください。すべてのチュートリアルと依存関係がコンパイルされます。各実行ファイルは~/Projects/OpenGLTutorials/にコピーされます。たぶん、エラーは出ないでしょう。
* ~/Projects/OpenGLTutorials/playgroundを開いて、./playgroundを起動してください。黒いウィンドウが現れます。

[Qt Creator](http://qt-project.org/)などのIDEを使うべきです。特にこれはCMakeをビルトインでサポートしています。そしてデバッグするときにより良い体験を提供するでしょう。以下にQtCreatorでの手順を示します。

* QtCreatorでFile->Tools->Options->Compile&Execute->CMakeに行きます。
* CMakeへのパスを指定します。だいたい/usr/bin/cmakeでしょう。
* File->Open Projectでtutorials/CMakeLists.txtを選んでください。
* ビルドディレクトリを選んでください。できればチュートリアルフォルダの外にしてください。
* 任意で、-DCMAKE_BUILD_TYPE=Debugをparameters boxにセットしてください。Validateしてください。
* 下にあるハンマーをクリックしてください。tutorials/からチュートリアルが起動できるでしょう。
* QtCreatorからチュートリアルを実行するために、Projects->Execution parameters->Working Directoryをクリックし、シェーダとテクスチャとモデルがあるディレクトリを選んでください。チュートリアル2では~/opengl-tutorial/tutorial02_red_triangle/となります。


##Macでのビルド

MacOSはOpenGL3.3をサポートしていません。最新のMacOS 10.7 LionとコンパティブルGPUはOpenGL3.2は実行できます。(3.3ではありません。)代わりに、チュートリアルの2.1ポートを使用してください。それは別として、手順はWindowsと良く似ています。(MakeFileもサポートされていますが、ここでは説明しません。)

* Mac App StoreからXCodeをインストールします。
* [CMakeをダウンロード](http://www.cmake.org/cmake/resources/software.html)し、.dmgをインストールします。コマンドラインツールはインストールする必要はありません。
* [3.ソースコードをダウンロードしてください。](/?page_id=200)(バージョンは2.1！！) そして、例えば~/Projects/OpenGLTutorials/に解凍してください。
* CMake(Applications->CMake)を起動してください。最初の項目に解凍したフォルダを指定してください。(CMakeLists.txtを含むフォルダです。)次の項目にコンパイラ関係のものを置く場所を指定してください。例えば、~/Projects/OpenGLTutorials_bin_XCode/を選んでください。必ずしもこのフォルダでなくても大丈夫です。
* Configureボタンをクリックしてください。プロジェクトを設定するのが初めてなので、CMakeはどのコンパイラを使うか聞いてきます。Xcodeを選んでください。
* 赤いラインが消えるまでConfigureをクリックしてください。Generateをクリックしてください。これで、Xcodeプロジェクトが作成されます。CMakeの役割はこれで終わりなので、アンインストールしても構いません。
* ~/Projects/OpenGLTutorials_bin_XCode/を開いてください。Tutorials.xcodeproj ファイルが見つかるので、それを開いてください。
* Xcode&rsquo;s Scheme panelの中から実行したいチュートリアルを選んでください。そしてRunボタンで、コンパイルと実行をしてください。

![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)


##Code::Blocksに関するメモ

2つのバグ(ひとつはC::B、もう一つはCMake)のため、Project->Build Options->Make commandsのコマンドラインを次のように編集する必要があります。

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)


また、ワーキングディレクトリも自分で設定する必要があります。Project->Properties -> Build targets -> tutorial N -> execution working dir (これはsrc_dir/tutorial_N/です。)

#チュートリアルの実行

正しいディレクトリからチュートリアルを実行すべきです。単に実行ファイルをダブルクリックするだけです。もしコマンドラインがよければ、正しいディレクトリに移動してください。

IDEから実行したければ、上で説明したように正しいワーキングディレクトリを設定するのを忘れないでください。

#チュートリアルのたどり方
各チュートリアルはソースコードとデータからできています。tutorialXX/で見つけられると思います。ただし、これらのプロジェクトを決して編集しないでください。リファレンス用として使ってください。playground/playground.cppを開いて、代わりにこのファイルを微調整してください。このファイルを好きなように編集してください。もし迷子になったら、単純にそのファイルにコピー&ペーストしてください。それで標準に戻ります。

各チュートリアルではコードの一部を載せています。チュートリアルを読む一方で、playgroundに直接コピー&ペーストするのを嫌がらないでください。経験するのが良いのです。単純に完成したコードを読むのを避けていては、このような方法では多くは学べないでしょう。シンプルなコピー＆ペーストでさえ、多くの問題が出てくるでしょう。

#ウィンドウを開く

ついに！OpenGLのコードです！
ええと、実際は違います。すべてのチュートリアルでは、マジックを使わず、"low level"な方法を見せます。しかし、このパートはとてもつまらなく役に立ちません。だから、私たちの代わりにこれをやってくれる、外部のライブラリのGLFWを使います。もし本当にやりたいならば、WindowsではWin32 API、LinuxではX11 API、MacではCocoa APIを使ってください。あるいはSFML、FreeGLUT、SDL、... を使ってください。[Links](/?page_id=210)ページを見てください。

OK、それでは行きましょう。まず、依存関係に対処します。コンソールにメッセージを表示するための基本的なものが必要となります。
{% highlight cpp linenos %}
// 標準ヘッダをインクルードします。
#include
#include 
{% endhighlight %}
最初のGLEWです。だからこれはちょっとしたマジックです。しかし後のために残しておきましょう。
{% highlight cpp linenos %}
// GLEWをインクルードする。常にgl.hとglfw.hより先にインクルードしましょう。これはちょっとしたマジックです。
#include 
{% endhighlight %}
GLFWでウィンドウとキーボードを扱うため、次のものもインクルードしましょう。
{% highlight cpp linenos %}
// GLFWをインクルードします。
#include 
{% endhighlight %}
このライブラリは実際はすぐには使いません。これは3D数学のためのライブラリです。すぐに、とても便利なことが分かるでしょう。GLMにはマジックはありません。必要があれば自分自身でも書けます。ですが、GLMはとても使いやすいです。"using namespace"があることで"glm::vec3"と書く代わりに、"vec3"と書けます。
{% highlight cpp linenos %}
// GLMをインクルードします。
#include
using namespace glm;
{% endhighlight %}
これらの#includeをplayground.cppにコピー＆ペーストしたならば、コンパイラはmain()関数がないと言うでしょう。だから作りましょう。
{% highlight cpp linenos %}
int main(){
{% endhighlight %}
最初にGLFWを初期化します。
{% highlight cpp linenos %}
// GLFWを初期化します。
if( !glfwInit() )
{
    fprintf( stderr, "GLFWの初期化に失敗しました。n" );
    return -1;
}
{% endhighlight %}
それでは、最初のOpenGLウィンドウを作りましょう！
{% highlight cpp linenos %}
glfwWindowHint(GLFW_SAMPLES, 4); // 4x アンチエイリアス
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL3.3を使います。
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS用：必ずしも必要ではありません。
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 古いOpenGLは使いません。

// Windowを開き、OpenGLコンテキストを作ります
GLFWwindow* window; // (ソースコードではこの変数はグローバルです。)
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
if( window == NULL ){
    fprintf( stderr, "GLFWウィンドウのオープンに失敗しました。 もしIntelのGPUならば, 3.3に対応していません。チュートリアルのバージョン2.1を試してください。n" );
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // GLEWを初期化する
glewExperimental=true; // コアプロファイルで必要となります。
if (glewInit() != GLEW_OK) {
    fprintf(stderr, "GLEWの初期化に失敗しました。n");
    return -1;
}
{% endhighlight %}
するとウィンドウが出てきますが、すぐに閉じてしまいます。もちろん！ユーザがエスケープキーを押すまで待っている必要があります。
{% highlight cpp linenos %}
// 下でエスケープキーが押されるのを捉えるのを保証します。
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    // 何も描きません。チュートリアル2で会いましょう！

    // バッファをスワップする。
    glfwSwapBuffers(window);
    glfwPollEvents();

} // ESCキーが押されたかウィンドウが閉じたかをチェックする。
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0 );
{% endhighlight %}
これで最初のチュートリアルは終了です。チュートリアル2では、実際に三角形を描く方法を学びます。
// 
