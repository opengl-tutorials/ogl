---
layout: page
status: publish
published: true
title: チュートリアル６：キーボードとマウス
author:
  display_name: suzuichi
  login: suzuichi
  email: suzuichiblog@gmail.com
  url: ''
author_login: suzuichi
author_email: suzuichiblog@gmail.com
wordpress_id: 1313
wordpress_url: http://www.opengl-tutorial.org/?page_id=1313
date: '2014-07-30 03:01:09 +0100'
date_gmt: '2014-07-30 03:01:09 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>﻿6回目のチュートリアルにようこそ！</p>
<p>キーボードとマウスを使って、FPSのようにカメラを動かす方法を学びます。</p>
<h1>インターフェース<&#47;h1><br />
このコードはチュートリアルを通して使うので、別のファイルで保存します。ファイルはcommon&#47;controls.cppにあります。またtutorial06.cppにそれらを知らせるために、common&#47;controls.hppで関数を宣言しておきます。</p>
<p>tutorial06.cppのコードは前のチュートリアルからあまり変えません。大きな変更点は、MVP行列を一度計算するのではなく、毎フレーム計算する必要がある点です。だからこのコードをメインループ内に移しましょう。</p>
<pre class="brush: cpp">do{</p>
<p>    &#47;&#47; ...</p>
<p>    &#47;&#47; キーボードとマウスのインプットからMVP行列を計算する<br />
    computeMatricesFromInputs();<br />
    glm::mat4 ProjectionMatrix = getProjectionMatrix();<br />
    glm::mat4 ViewMatrix = getViewMatrix();<br />
    glm::mat4 ModelMatrix = glm::mat4(1.0);<br />
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;</p>
<p>    &#47;&#47; ...<br />
}<&#47;pre><br />
このコードには3つの新しい関数があります。</p>
<ul>
<li>computeMatricesFromInputs()はキーボードとマウスを読み込み、射影行列とビュー行列を計算します。この関数が手品のタネです。<&#47;li>
<li>getProjectionMatrix()は射影行列を返します。<&#47;li>
<li>getViewMatrix()ビュー行列を返します。<&#47;li><br />
<&#47;ul><br />
もちろん、これは実現方法の一つに過ぎません。もし気に入らなければ、ソースコードを変更してください。</p>
<p>controls.cpp内で何が起きているのか見ていきましょう。</p>
<h1>実際のコード<&#47;h1><br />
いくつかの変数が必要となります。</p>
<pre class="brush: cpp">&#47;&#47; 位置<br />
glm::vec3 position = glm::vec3( 0, 0, 5 );<br />
&#47;&#47; 水平角、-Z方向<br />
float horizontalAngle = 3.14f;<br />
&#47;&#47; 鉛直角、0、水平線を眺めている<br />
float verticalAngle = 0.0f;<br />
&#47;&#47; 初期視野<br />
float initialFoV = 45.0f;</p>
<p>float speed = 3.0f; &#47;&#47; 3 units &#47; second<br />
float mouseSpeed = 0.005f;<&#47;pre><br />
FoVはズームレベルです。80&deg;= 超広角,大きなゆがみがあります。60&deg;-45&deg;は一般的です。20&deg;はすごいズームです。</p>
<p>最初にインプットに応じて位置、水平角、鉛直角と視野を再計算します。そして、その情報を元にビュー行列と射影行列を計算します。</p>
<h2>方向<&#47;h2><br />
マウスの位置を読み込むのは簡単です。</p>
<pre class="brush: cpp">&#47;&#47; マウスの位置を取得します。<br />
int xpos, ypos;<br />
glfwGetMousePos(&amp;xpos, &amp;ypos);<&#47;pre><br />
一方で、マウスをスクリーンの中心に戻すときには注意が必要です。そうしなければ、すぐにウィンドウの外に出てしまい、それ以上動かせなくなってしまいます。</p>
<pre class="brush: cpp">&#47;&#47; 次のフレームのためにマウス位置をリセットします。<br />
glfwSetMousePos(1024&#47;2, 768&#47;2);<&#47;pre><br />
このコードはウィンドウサイズを1024&times;768と仮定しています。もちろんこのサイズでなくても良いです。必要ならばglfwGetWindowSizeを使っても良いです。</p>
<p>これで視野角を計算できます。</p>
<pre class="brush: cpp">&#47;&#47; 新たな方向を計算します。<br />
horizontalAngle += mouseSpeed * deltaTime * float(1024&#47;2 - xpos );<br />
verticalAngle   += mouseSpeed * deltaTime * float( 768&#47;2 - ypos );<&#47;pre><br />
右から左に読んでみましょう。</p>
<ul>
<li>1024&#47;2 - xpos はマウスがウィンドウの中心からどの程度離れているかを意味します。この値が大きいほど、より動かしたいということを意味します。<&#47;li>
<li>float(...) は計算がうまくいくようにfloat型に変換しています。<&#47;li>
<li>mouseSpeed は回転の速度を速めたり遅くしたりするためにあります。好きなように調整してください。あるいはユーザに選ばせるのもありです。<&#47;li>
<li>+= マウスを動かさなければ 1024&#47;2-xpos は0で、水平角は +=0 となり、水平角は変わりません。もし"+="の代わりに"="を使うと、毎フレーム、元の方向に戻ることになります。これはよくありません。<&#47;li><br />
<&#47;ul><br />
これで、ワールド空間でどちらの方向を向いているかを表現するベクトルを計算できます。</p>
<pre class="brush: cpp">&#47;&#47; 方向：球面座標から直角座標に変換します。<br />
glm::vec3 direction(<br />
    cos(verticalAngle) * sin(horizontalAngle),<br />
    sin(verticalAngle),<br />
    cos(verticalAngle) * cos(horizontalAngle)<br />
);<&#47;pre><br />
これは一般的な計算です。コサインとサインを知らないならば、ここに簡単な説明を示します。</p>
<p><img class="alignnone whiteborder" title="Trigonometric circle" src="http:&#47;&#47;www.numericana.com&#47;answer&#47;trig.gif" alt="" width="150" height="150" &#47;><br />
上の式は3Dへの一般化です。</p>
<p>今"上"ベクトルを計算したいです。気をつけてほしいのは"上"は常に+Y方向ではないということです。もし下を向いているならば"上"方向は水平方向となります。これが同じ位置にあり、同じターゲットで、しかし違う"上"方向のカメラの例です。</p>
<p>私たちのケースでは、カメラの右方向へ向かうベクトルは常に水平、ということは変化しません腕を水平にして、上や下やいろんな角度を見ることで、これを確認できるでしょう。だから"右"ベクトルを次のように定義しましょう。そのベクトルは水平なのでY座標は0で、XとYは上で示したような感じです。ただし、角度は90&deg;あるいはPi&#47;2ラジアンずつ回転しています。</p>
<pre class="brush: cpp">&#47;&#47; 右ベクトル<br />
glm::vec3 right = glm::vec3(<br />
    sin(horizontalAngle - 3.14f&#47;2.0f),<br />
    0,<br />
    cos(horizontalAngle - 3.14f&#47;2.0f)<br />
);<&#47;pre><br />
これで"右"ベクトルと"方向・前"ベクトルを持っていることになります。"上"ベクトルはこれら2つのベクトルに垂直です。外積という便利な数学ツールで簡単に計算できます。</p>
<pre class="brush: cpp">&#47;&#47; 上ベクトル：右と前ベクトルに垂直<br />
glm::vec3 up = glm::cross( right, direction );<&#47;pre><br />
外積が何をやっているか思い出してください。とてもシンプルなことを行っています。チュートリアル3の右手の法則を思い出してください。最初のベクトルは親指、2つ目は人差し指、結果は中指です。とっても便利でしょ？</p>
<h2>位置<&#47;h2><br />
コードはとても簡単です。ところで、a&#47;w&#47;s&#47;dキーの代わりに上&#47;下&#47;右&#47;左キーを使います。なぜなら私のキーボードはazertyなので、a&#47;w&#47;s&#47;dの位置ははz&#47;q&#47;s&#47;dだからです。また韓国で使われているqwerZキーボードもまた配置が異なります。実のところ韓国人がどんなキーボードを使っているかは知りませんが、たぶんawsdとは違う配置のものを使っているでしょう。</p>
<pre class="brush: cpp">&#47;&#47; 前へ動きます。<br />
if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){<br />
    position += direction * deltaTime * speed;<br />
}<br />
&#47;&#47; 後ろへ動きます。<br />
if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){<br />
    position -= direction * deltaTime * speed;<br />
}<br />
&#47;&#47; 前を向いたまま、右へ平行移動します。<br />
if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){<br />
    position += right * deltaTime * speed;<br />
}<br />
&#47;&#47; 前を向いたまま、左へ平行移動します。<br />
if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){<br />
    position -= right * deltaTime * speed;<br />
}<&#47;pre><br />
ここで特別なものはdeltaTimeです。次のような理由から、各フレームに1単位だけ動くのはあまり好ましくないでしょう。</p>
<ul>
<li>60fpsで動くような早いコンピュータを使っていると、1秒で60&times;speedだけ動きます。<&#47;li>
<li>20fpsで動くような遅いコンピュータを使っていると、1秒で20&times;speedだけ動きます。<&#47;li><br />
<&#47;ul><br />
早いコンピュータだからといって早く移動させるわけではないので、"前のフレームからの時間"あるいは"時間差"で距離をスケーリングする必要があります。</p>
<ul>
<li>60fpsで動くような早いコンピュータを使っていると、1フレームで1&#47;60&times;speed単位だけ動きます。だから1秒で1&times;speedだけ動きます。<&#47;li>
<li>20fpsで動くような遅いコンピュータを使っていると、1フレームで1&#47;20&times;speed単位だけ動きます。だから1秒で1&times;speedだけ動きます。.<&#47;li><br />
<&#47;ul><br />
こうするほうが好ましいでしょう。また、deltaTimeは簡単に計算できます。</p>
<pre class="brush: cpp">double currentTime = glfwGetTime();<br />
float deltaTime = float(currentTime - lastTime);<&#47;pre></p>
<h2>視野<&#47;h2><br />
よりおもしろくするために、マウスのホイールを視野に割り当てましょう。これにより安っぽいズーム機能を付けられます。</p>
<pre class="brush: cpp">float FoV = initialFoV - 5 * glfwGetMouseWheel();<&#47;pre></p>
<h2>行列の計算<&#47;h2><br />
行列を計算するのは簡単です。以前とは違うパラメータを使って、前と同じような関数を使います。</p>
<pre class="brush: cpp">&#47;&#47; 射影行列：視野45&deg;、4:3比、描画範囲0.1単位100単位<br />
ProjectionMatrix = glm::perspective(FoV, 4.0f &#47; 3.0f, 0.1f, 100.0f);<br />
&#47;&#47; カメラ行列<br />
ViewMatrix       = glm::lookAt(<br />
    position,           &#47;&#47; カメラの位置<br />
    position+direction, &#47;&#47; 目標地点<br />
    up                  &#47;&#47; 上方向 (0,-1,0にセットすると上下逆さまになります。)<br />
);<&#47;pre></p>
<h1>結果<&#47;h1><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;moveanim.gif"><img class="alignnone size-full wp-image-372" title="moveanim" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;moveanim.gif" alt="" width="206" height="159" &#47;><&#47;a></p>
<h2>バックフェースカリング<&#47;h2><br />
これで自由に動かせます。ただし、立方体の中へ移動しても、ポリゴンは表示されたままだということに気づくでしょう。これは明らかなように思えますが、この現象は最適化の絶好の機会です。実際、通常のアプリケーションでは立方体の中には決して移動しません。</p>
<p>カメラが三角形の後ろあるいは前にいるかどうかをGPUにチェックさせるというアイディアがあります。もし前にいれば三角形を表示します。もし後ろいて、メッシュが閉じていて、メッシュの中にいなければ、他の三角形がその前にあります。そして早く動いていることを除けば、誰も何も気づかないでしょう。平均で2倍三角形を減らせます。</p>
<p>良いことに、これはとても簡単にチェックできます。GPUは三角形の法線を計算します。(外積を使います。思い出せますか？)そしてこの法線がカメラのほうに向いてるかそうでないかをチェックします。</p>
<p>残念なことに、これはコストがかかります。つまり三角形の向きは暗黙的です。もしバッファ内の二つの頂点をひっくり返すと、間違いに終わるでしょう。しかし少しの追加の仕事をさせる価値があります。しばしば、3Dモデラーでは"法線を逆さまに"をクリックする必要があります。(実はこれは頂点を逆さまにし、そして法線です。)そしてすべてうまくいきます。</p>
<p>バックフェースカリングを有効にするのは簡単です。</p>
<pre class="brush: cpp">&#47;&#47; カメラのほうを向いていない法線の三角形をカリングします。<br />
glEnable(GL_CULL_FACE);<&#47;pre></p>
<h1>演習<&#47;h1></p>
<ul>
<li>上下に移動できないようにverticalAngleを制限してください。<&#47;li>
<li>オブジェクトの周りを回るようなカメラを作ってください。( position = ObjectCenter + ( radius * cos(time), height, radius * sin(time) ) )そして、radius&#47;height&#47;timeをキーボード&#47;マウスなどにバインドします。<&#47;li>
<li>楽しんで！<&#47;li><br />
<&#47;ul></p>
