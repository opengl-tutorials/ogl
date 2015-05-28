---
layout: page
status: publish
published: true
title: チュートリアル3：行列
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 1287
wordpress_url: http://www.opengl-tutorial.org/?page_id=1287
date: '2014-06-25 10:56:05 +0100'
date_gmt: '2014-06-25 10:56:05 +0100'
categories: []
tags: []
comments: []
language: jp
---
<br />
<blockquote><p><em>エンジンは船を動かさない。船はそこにあり、エンジンは船の周りで世界を動かす。<&#47;em><span id="content_parent" class="mceEditor wp_themeSkin"><img id="ft_1303837888870" class="foxytunes-signature-button" style="cursor: pointer;width: 30px;height: 20px;padding: 0px;margin-bottom: 5px;margin-right: 7px;border: 1px solid threedshadow threedhighlight threedhighlight threedshadow" title="Insert current track Signatune" src="&#47;&#47;foxytunes-pbulic&#47;content&#47;signatures&#47;signature-button-on-hover.png" alt="" &#47;><&#47;span><br />
フューチュラマ<&#47;blockquote><br />
<span style="color: #ff0000">これが全体のたったひとつの最も重要なチュートリアルです。少なくとも8回は読んでください。<&#47;span></p>
<h1>同次座標<&#47;h1><br />
これまで、3D頂点を(x,y,z)の3つ組としてのみ考えていました。ここでwを導入しましょう。すると(x,y,z,w)というベクトルを得ます。</p>
<p>こうする理由がもうすぐ分かるでしょう。ただしこれだけは覚えておいてください。</p>
<ul>
<li>w == 1 ならばベクトル(x,y,z,1)は空間での位置を表します。<&#47;li>
<li>w == 0 ならばベクトル(x,y,z,0)は方向を表します。<&#47;li><br />
<&#47;ul><br />
(もっと言えば、ずっと覚えておいてください。)</p>
<p>これが作り出す違いは何でしょう？例えば回転では、何も変えません。点か方向を回転させるとき、同じ結果を得られます。しかし平行移動のとき(特定の方向に点を移動させるとき)は、状況が違ってきます。"方向を平行移動させる"とはどういう意味でしょう？まぁ、気にしないでください。</p>
<p>同次座標はこれら二つのケースを一つの数式で表すことを可能にします。</p>
<h1>変換行列<&#47;h1></p>
<h2>行列入門<&#47;h2><br />
簡単に言いますと、行列は行と列の数があらかじめ決まっている、数字の配列です。例えば、2x3行列は次のようになります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;2X3.png"><img class="alignnone size-full wp-image-61 whiteborder" title="2X3" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;2X3.png" alt="" width="68" height="44" &#47;><&#47;a></p>
<p>3Dグラフィックスでは、4x4の行列しか使いません。行列は頂点(x,y,z,w)を変換するときに役に立ちます。変換は頂点にと行列を掛け合わせることで実現します。</p>
<p style="text-align: left"><strong>行列 x 頂点  (この順番！！) = 変換された頂点<&#47;strong><&#47;p><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MatrixXVect.gif"><img class="alignnone size-medium wp-image-64 whiteborder" title="MatrixXVect" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MatrixXVect-300x71.gif" alt="" width="300" height="71" &#47;><&#47;a></p>
<p>これは見た目ほどおっかなくありません。左手の指をaに、右手の指をxに乗せて下さい。これが<em>ax<&#47;em>です。左手の指を次の数字bに、右手の指を次の数字yにおいてください。すると<em>by<&#47;em>を得ます。同様に<em>cz<&#47;em>、<em>dw<&#47;em>を得ます。つまりax + by + cz + dwとなります。これで新しいxを得ました！各行で同じことをやって下さい、すると新しい(x,y,z,w)が得られます。</p>
<p>この計算はとても退屈で、しかも頻繁に行います。そこで代わりにこれを計算してくれるように頼みましょう。</p>
<p><strong>GLMを用いるC++：<&#47;strong></p>
<pre class="brush: cpp">glm::mat4 myMatrix;<br />
glm::vec4 myVector;<br />
&#47;&#47; 何らかの方法でmyMatrixとmyVector満たす。<br />
glm::vec4 transformedVector = myMatrix * myVector; &#47;&#47; もう一度言いますが、この順番です！これは重要なことです。<&#47;pre><br />
<strong>GLSL：<&#47;strong></p>
<pre class="brush: vs">mat4 myMatrix;<br />
vec4 myVector;<br />
&#47;&#47; 何らかの方法でmyMatrixとmyVector満たす。<br />
vec4 transformedVector = myMatrix * myVector; &#47;&#47; そうです、GLMととても似ています。<&#47;pre><br />
( コードにこれをコピー＆ペーストしましたか？やってみましょう。)</p>
<h2>平行移動行列<&#47;h2><br />
ここに理解するための最も簡単な平行移動行列を用意しました。平行移動行列は次のように表せます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationMatrix.png"><img class="alignnone size-full wp-image-60 whiteborder" title="translationMatrix" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationMatrix.png" alt="" width="103" height="88" &#47;><&#47;a></p>
<p>X、Y、Zは位置に加えたい値です。</p>
<p>だからベクトル(10,10,10,1)をX方向に10だけ平行移動させたいなら、次のように書けます。：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExamplePosition1.png"><img class="alignnone  wp-image-798" title="translationExamplePosition" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExamplePosition1.png" alt="" width="639" height="82" &#47;><&#47;a></p>
<p>(計算してみましょう！絶対にやりましょう。)</p>
<p>...そして新たな同次ベクトル(20,10,10,1)が得られました！1というのは方向ではなく位置を表すことを思い出してください。だから変換によって位置を扱っているというという事実は変わりません。これは良いことです。</p>
<p>それでは-z軸方向を向いているベクトルに対しては何が起こるか見てみましょう。(0,0,-1,0)：</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExampleDirection1.png"><img class="alignnone size-full wp-image-799" title="translationExampleDirection" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;translationExampleDirection1.png" alt="" width="621" height="82" &#47;><&#47;a></p>
<p>...つまりもとの(0,0,-1,0)方向は、上で言ったように、方向を動かすというのは何の意味もありません。</p>
<p>それでは、これをコードで実現するにはどうすれば良いでしょうか？</p>
<p><strong>GLMを用いるC++：<&#47;strong></p>
<pre class="brush: cpp">#include <glm&#47;transform.hpp> &#47;&#47; <glm&#47;glm.hpp>の後</p>
<p>glm::mat4 myMatrix = glm::translate(10.0f, 0.0f, 0.0f);<br />
glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);<br />
glm::vec4 transformedVector = myMatrix * myVector; &#47;&#47; guess the result<&#47;pre><br />
<strong>GLSL； <&#47;strong>実は、GLSLではこのようにはできません。ほとんどの場合、行列を計算するためにC++でglm::translate()を使い、行列をGLSLに送り、掛け算をするだけです。</p>
<pre class="brush: cpp">vec4 transformedVector = myMatrix * myVector;<&#47;pre></p>
<h2>単位行列<&#47;h2><br />
これは特別な行列です。何もしない行列です。しかし、これはA x 1.0がAとなることを知っているのと同じくらい重要なのでここで述べておきます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;identityExample.png"><img class="alignnone size-full wp-image-99 whiteborder" title="identityExample" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;identityExample.png" alt="" width="742" height="80" &#47;><&#47;a></p>
<p><strong>C++：<&#47;strong></p>
<pre class="brush: cpp">glm::mat4 myIdentityMatrix = glm::mat4(1.0f);<&#47;pre></p>
<h2>拡大縮小行列<&#47;h2><br />
拡大縮小行列も簡単です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingMatrix.png"><img class="alignnone size-full wp-image-93 whiteborder" title="scalingMatrix" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingMatrix.png" alt="" width="98" height="88" &#47;><&#47;a></p>
<p>ここで全方向に2.0だけベクトル(位置でも方向でもどちらでも)を拡大したいならば次のようにやります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingExample.png"><img class="alignnone size-full wp-image-98 whiteborder" title="scalingExample" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;scalingExample.png" alt="" width="799" height="80" &#47;><&#47;a></p>
<p>やはりwは変わりません。"方向を拡大(縮小)する"とはどういう意味か聞きたいかもしれません。えーと、まぁ聞かないでください。だから普通はこういうことはやりません。ただ一部のケースではとても便利に使えます。<br />
(単位行列は拡大縮小行列の特別な場合です。つまり(X,Y,Z) = (1,1,1)です。また単位行列は平行移動行列の特別な場合でもあります。つまり(X,Y,Z) = (0,0,0)です。)</p>
<p><strong>C++；<&#47;strong></p>
<pre class="brush: cpp">&#47;&#47; #include <glm&#47;gtc&#47;matrix_transform.hpp> と #include <glm&#47;gtx&#47;transform.hpp>を使います。<br />
glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);<&#47;pre></p>
<h2>回転行列<&#47;h2><br />
これらはとても複雑です。ここでは詳細は省きます。本当のレイアウトを知るのは、普通に使う上ではそれほど重要ではないからです。もっと知りたければ<a href="http:&#47;&#47;www.cs.princeton.edu&#47;~gewang&#47;projects&#47;darth&#47;stuff&#47;quat_faq.html">Matrices and Quaternions FAQ<&#47;a>を見てください。(人気のページです。あなたの言語でもたぶん利用可能でしょう。)</p>
<p><strong>C++：<&#47;strong></p>
<pre class="brush: cpp">&#47;&#47; #include <glm&#47;gtc&#47;matrix_transform.hpp> と #include <glm&#47;gtx&#47;transform.hpp>を使います。<br />
glm::vec3 myRotationAxis( ??, ??, ??);<br />
glm::rotate( angle_in_degrees, myRotationAxis );<&#47;pre></p>
<h2>変換の組み合わせ<&#47;h2><br />
ここまででベクトルを回転、平行移動、拡大縮小する方法を学びました。これらの変換は組み合わせることができます。行列をお互いに掛けることによって実現します。例えば次のようになります。：</p>
<pre class="brush: cpp">TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;<&#47;pre><br />
！！！ 注意 ！！！ この行は、<strong>最初に<&#47;strong>拡大縮小、<strong>次に<&#47;strong>回転、<strong>最後に<&#47;strong>平行移動です。このようにして行列の掛け算は働きます。</p>
<p>違う順番で掛け合わせても同じ結果になるとは限りません。自分で確認してみましょう。：<br />
- 前に進めてから左に回転する。<br />
- 回転させてから前に進む。</p>
<p>実は、上の順番はゲームキャラクターや他のアイテムで通常必要とするものです。必要ならば最初に拡大縮小し、次に方向を決め、そして平行移動する。例えば、船モデルを考えましょう。(回転は簡単化のため省きます。)</p>
<ul>
<ul>
<li>間違ったやり方：<&#47;li><br />
<&#47;ul><br />
<&#47;ul></p>
<p style="padding-left: 120px">- (10,0,0)だけ船を平行移動させる。今、船の中心は原点から10だけ動きました。<br />
- 船の大きさを2倍にします。<em>現原点に比例して<&#47;em>すべての方向が2倍されます。遠くに行ってしまった...最終的には大きな船を得ました。しかし中心は2*10 = 20です。これではだめでしょう。<&#47;p></p>
<ul>
<ul>
<li>正しいやり方：<&#47;li><br />
<&#47;ul><br />
<&#47;ul></p>
<p style="padding-left: 120px">- 船を2倍しましょう。すると中心が原点の大きな船を得ます。<br />
- 船を平行移動させましょう。同じ大きさで、正しい距離だけ動きました。<&#47;p></p>
<p>行列と行列の掛け算は行列とベクトルの掛け算に良く似ています。だからここでは詳細を省きます。詳しくは<a href="http:&#47;&#47;www.cs.princeton.edu&#47;~gewang&#47;projects&#47;darth&#47;stuff&#47;quat_faq.html">Matrices and Quaternions FAQ<a>を見てください。それで、コンピュータに次のように頼めばやってくれます。：</p>
<p><strong>GLMを用いたC++：<&#47;strong></p>
<pre class="brush: cpp">glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;<br />
glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;<&#47;pre><br />
<strong>GLSL：<&#47;strong></p>
<pre class="brush: vs">mat4 transform = mat2 * mat1;<br />
vec4 out_vec = transform * in_vec;<&#47;pre></p>
<h1>モデル行列、ビュー行列、射影行列<&#47;h1><br />
<em>以降のこのチュートリアルでは、Blenderの人気の3Dモデル、モンキースザンヌ、を描画する方法を知っていると仮定します。<&#47;em></p>
<p>モデル行列、ビュー行列、射影行列は変換をきれいに分けるための便利なツールです。これを使わないかもしれません。(実際、チュートリアル1と2では使いませんでした。)しかし、使うべきです。これがみんながやっている方法です。なぜなら、これから見ていくように、すべてをきれいに分けられるからです。</p>
<h2>モデル行列<&#47;h2><br />
このモデルは、愛すべき私たちの三角形と同様に、頂点のセットで定義されています。これらの頂点のX、Y、Z座標はオブジェクトの中心の相対座標で定義されています。つまり、頂点(0,0,0)はオブジェクトの中心を表します。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model.png"><img class="alignnone size-full wp-image-22" title="model" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>ユーザがキーボードやマウスでモデルを動かせるようにしたいです。簡単です、既に習ってることをやればいいんです。平行移動*回転*拡大縮小です。各フレームごとに各頂点に対してこの行列を(C++ではなくGLSLで)適用すれば、すべてが動きます。ただし、_世界の中心_は動きません。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;world.png"><img class="alignnone size-full wp-image-25" title="world" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;world.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>各頂点は今<em>ワールド空間<&#47;em>にあります。これは下の画像の黒い矢印が表しています。つまり<em>私たちはモデル空間(すべての頂点がモデルの中心の相対座標で表される)からワールド空間(すべての頂点が世界の中心の相対座標で表される)へ移ったことになります。<&#47;em></p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world.png"><img class="alignnone size-full wp-image-23" title="model_to_world" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>これは下の図のように表せます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;M.png"><img class="alignnone size-full wp-image-63 whiteborder" title="M" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;M.png" alt="" width="240" height="148" &#47;><&#47;a></p>
<h2>ビュー行列<&#47;h2><br />
フューチュラマをもう一度引用しましょう。：</p>
<blockquote><p><em>Tエンジンは船を動かさない。船はそこにあり、エンジンは船の周りで世界を動かす。<&#47;em><&#47;blockquote><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;camera.png"><img class="alignnone size-full wp-image-21" title="camera" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;camera.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>この考え方は、カメラにも適用できます。もし他の角度から山を見たいとき、カメラを動かすか...あるいは山を動かすことで実現できます。実際の世界では山を動かせませんが、コンピュータグラフィックの世界ではとてもシンプルで手軽にできます。</p>
<p>まずはじめに、カメラはワールド空間の原点にあります。世界を動かすためには、単純に行列を一つ導入すれば良いんです。それではカメラを右に3だけ(+X)動かしてみましょう。これは全世界(メッシュも含めて)を<strong>左に<&#47;strong>3だけ(-X)動かすことと同じです！混乱してるかもしれませんが、進みましょう。</p>
<pre class="brush: cpp">&#47;&#47; #include <glm&#47;gtc&#47;matrix_transform.hpp> と #include <glm&#47;gtx&#47;transform.hpp> を使います。<br />
glm::mat4 ViewMatrix = glm::translate(-3.0f, 0.0f ,0.0f);<&#47;pre><br />
再び、下の図がこの様子を表しています。<em>私たちはワールド空間(前項で説明したように、すべての頂点が世界の中心の相対座標で表される)からカメラ空間(すべての頂点がカメラの相対座標で表される)へ移りました。<&#47;em></p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera.png"><img class="alignnone size-full wp-image-24" title="model_to_world_to_camera" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>頭が爆発する前に、GLMのglm::LookAt関数を楽しんでください。</p>
<pre class="brush: cpp">glm::mat4 CameraMatrix = glm::LookAt(<br />
    cameraPosition, &#47;&#47; ワールド空間でのカメラの位置<br />
    cameraTarget,   &#47;&#47; ワールド空間での見たい位置<br />
    upVector        &#47;&#47; たぶんglm::vec3(0,1,0)です。一方で(0,-1,0)にしたら上下逆さまになります。それもまた良いでしょう。<br />
);<&#47;pre><br />
下の図のような感じになります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MV.png"><img class="alignnone size-full wp-image-65 whiteborder" title="MV" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MV.png" alt="" width="240" height="265" &#47;><&#47;a></p>
<p>しかし、まだ終わっていません。</p>
<h2>射影行列<&#47;h2><br />
私たちは今カメラ空間にいます。これは、これらの変換の後x==0とy==0である頂点はスクリーンの中心に描かれることを意味します。しかし、オブジェクトがスクリーンのどの位置に来るかを決定するのにxとy座標だけを使うわけではありません。つまりカメラからの距離zも使いたいんです！2つの頂点が同じxとyを持っているならば、より大きなz座標を持つ頂点を他の頂点よりもスクリーンの中心に置かれるでしょう。</p>
<p>これは透視投影法と呼ばれます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera_to_homogeneous.png"><img class="alignnone size-full wp-image-26" title="model_to_world_to_camera_to_homogeneous" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;model_to_world_to_camera_to_homogeneous.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>幸運なことに、4x4行列はこの射影を表せます。&sup1;:</p>
<pre class="brush: cpp">&#47;&#47; 読むのが難しい行列を作ります。それでも、普通の標準の4x4行列です。<br />
glm::mat4 projectionMatrix = glm::perspective(<br />
    FoV,         &#47;&#47; 視界の水平方向の広がり度合い(度)。つまり、"ズーム"の度合い。"カメラレンズ"を考えてください。通常90&deg;(超ワイド) と 30&deg; (とてもズームインしてる)の間です。<br />
    4.0f &#47; 3.0f, &#47;&#47; アスペクト比。ウィンドウのサイズに依存します。4&#47;3 == 800&#47;600 == 1280&#47;960となっています。<br />
    0.1f,        &#47;&#47; 近くのクリッピング平面。できるだけ大きくします。そうしないと正確さの問題が出てくるでしょう。<br />
    100.0f       &#47;&#47; 遠くのクリッピング平面。できるだけ小さくします。<br />
);<&#47;pre><br />
最後の一つです。</p>
<p><em>私たちはカメラ空間(すべての頂点がカメラの相対座標で表される)から同次空間(すべての頂点が小さな球の中で表される。球の中にある頂点がスクリーン上にある。)へ移りました。<&#47;em></p>
<p>そして、最後の説明図です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MVP.png"><img class="alignnone size-medium wp-image-66 whiteborder" title="MVP" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;MVP-235x300.png" alt="" width="235" height="300" &#47;><&#47;a></p>
<p>この射影でどんなことが起こったのかをより理解するために他の図を示します。射影の前、カメラ空間で、青いオブジェクトを得て、赤いところはカメラの四角錐台を表しています。つまり、カメラが実際に見ることのできるシーンの部分です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nondeforme.png"><img class="alignnone size-full wp-image-67" title="nondeforme" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;nondeforme.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>すべてに射影行列を掛けると次のような効果があります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;homogeneous.png"><img class="alignnone size-full wp-image-76" title="homogeneous" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;homogeneous.png" alt="" width="960" height="540" &#47;><&#47;a></p>
<p>この図では、今、四角錐台は完全な立方体となりました。(すべての軸が-1と1の間。それは少し見づらいです。)そして、青いオブジェクトは同じ方法で変形しました。そのため、カメラに近いオブジェクトは大きく(つまり私たちは見られない球の面に近い) 、他はより小さくなります。実世界と同じように！</p>
<p>四角錐台の後ろから、どのように見えるか見てみましょう。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;projected1.png"><img class="alignnone size-full wp-image-368 whiteborder" title="projected" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;projected1.png" alt="" width="602" height="588" &#47;><&#47;a></p>
<p>これで図が得られました！これは少し正方形すぎます。だから、実際のウィンドウサイズに合うように、他の数学変換を適用します。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;final1.png"><img class="alignnone size-full wp-image-367 whiteborder" title="final" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;final1.png" alt="" width="640" height="462" &#47;><&#47;a></p>
<p>そして、これが実際にレンダリングされる図です。</p>
<h2>行列の組み合わせ：モデルビュー射影行列<&#47;h2><br />
... 既に慣れ親しんだ普通の行列の掛け算のようにやります！</p>
<pre class="brush: cpp">&#47;&#47; C++：行列を計算する。<br />
glm::mat4 MVPmatrix = projection * view * model; &#47;&#47; 逆になることを思い出して!<&#47;pre></p>
<pre class="brush: vs">&#47;&#47; GLSL：適用する<br />
transformed_vertex = MVP * in_vertex;<&#47;pre></p>
<h1>すべてを合わせる<&#47;h1></p>
<ul>
<li>ステップ1：MVP(ModelViewProjection)行列を作ります。レンダリングする各モデルごとに行います。<&#47;li><br />
<&#47;ul></p>
<pre class="brush: cpp">&#47;&#47; 射影行列：45&deg;の視界、アスペクト比4:3、表示範囲：0.1単位  100単位<br />
glm::mat4 Projection = glm::perspective(45.0f, 4.0f &#47; 3.0f, 0.1f, 100.0f);<br />
&#47;&#47; カメラ行列<br />
glm::mat4 View       = glm::lookAt(<br />
    glm::vec3(4,3,3), &#47;&#47; ワールド空間でカメラは(4,3,3)にあります。<br />
    glm::vec3(0,0,0), &#47;&#47; 原点を見ています。<br />
    glm::vec3(0,1,0)  &#47;&#47; 頭が上方向(0,-1,0にセットすると上下逆転します。)<br />
);<br />
&#47;&#47; モデル行列：単位行列(モデルは原点にあります。)<br />
glm::mat4 Model      = glm::mat4(1.0f);  &#47;&#47; 各モデルを変える！<br />
&#47;&#47; Our ModelViewProjection : multiplication of our 3 matrices<br />
glm::mat4 MVP        = Projection * View * Model; &#47;&#47; 行列の掛け算は逆になることを思い出してください。<&#47;pre></p>
<ul>
<li>ステップ2：GLSLに渡します。<&#47;li><br />
<&#47;ul></p>
<pre class="brush: cpp">&#47;&#47; "MVP" uniformへのハンドルを取得します。<br />
&#47;&#47; 初期化時だけ<br />
GLuint MatrixID = glGetUniformLocation(programID, "MVP");</p>
<p>&#47;&#47; 現在バインドしているシェーダの"MVP" uniformに変換を送る<br />
&#47;&#47; レンダリングする各モデルごと、なぜならMVPが違うからです。(少なくともMの部分が違います。)<br />
glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &amp;MVP[0][0]);<&#47;pre></p>
<ul>
<li>ステップ3：頂点を変換させるためにGLSLで行列を使います。<&#47;li><br />
<&#47;ul></p>
<pre class="brush: vs">in vec3 vertexPosition_modelspace;<br />
uniform mat4 MVP;</p>
<p>void main(){</p>
<p>    &#47;&#47; クリップ空間での、頂点のアウトプット位置：MVP * 位置<br />
    vec4 v = vec4(vertexPosition_modelspace,1); &#47;&#47; 同次4Dベクトルに変換します。覚えていますか？<br />
    gl_Position = MVP * v;<br />
}<&#47;pre></p>
<ul>
<li>できました！チュートリアル2と同じ三角形ができました。原点は(0,0,0)ですが、(4,3,3,)から見て、(0,1,0)が上方向で、45&deg;の視界です。<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;perspective_red_triangle.png"><img class="alignnone size-medium wp-image-20" title="perspective_red_triangle" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;perspective_red_triangle-300x231.png" alt="" width="300" height="231" &#47;><&#47;a></p>
<p>チュートリアル6ではゲームのようなカメラを作るためにキーボードやマウスを使った動的なこれらの値の修正方法を学びます。しかしまずは、3Dモデルでの色(チュートリアル4)とテクスチャ(チュートリアル5)の付け方を学びます。</p>
<h1>演習<&#47;h1></p>
<ul>
<li>glm::perspectiveを変えてみましょう。<&#47;li>
<li>透視投影変換の変わりに、平行投影(正射影)(glm::ortho)を使ってみましょう。<&#47;li>
<li>モデル行列を三角形を平行移動、回転、拡大縮小の順になるように修正してみましょう。<&#47;li>
<li>同じものですが、違う順番で行ってみましょう。何か気づくことはありますか？キャラクターに使うならどの順番が"ベスト"でしょうか？<&#47;li><br />
<&#47;ul></p>
<address>付録<&#47;address><br />
<address> <&#47;address><br />
<address> <&#47;address><br />
<address>1 : [...]幸運なことに、4x4行列はこの射影を表せます。&sup1;；本当は、これは正しくありません。透視変換はアフィンではありません。それ自体、行列として表せません。射影行列を掛けた後、同次座標はそのW要素で割られています。これはW要素が-Zになったりするからです。(なぜなら、射影行列はこのように作られるからです。)このように、原点から遠い点は大きなZで割られます。つまりそのXとY座標はより小さくなります。つまり点同士がそれぞれより近くなります。そして、これが透視を与えます。<&#47;address></p>
