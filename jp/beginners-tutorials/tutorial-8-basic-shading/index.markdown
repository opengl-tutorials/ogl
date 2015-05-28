---
layout: page
status: publish
published: true
title: チュートリアル8：シェーディングの基礎
author:
  display_name: suzuichi
  login: suzuichi
  email: suzuichiblog@gmail.com
  url: ''
author_login: suzuichi
author_email: suzuichiblog@gmail.com
wordpress_id: 1317
wordpress_url: http://www.opengl-tutorial.org/?page_id=1317
date: '2014-07-30 03:04:02 +0100'
date_gmt: '2014-07-30 03:04:02 +0100'
categories: []
tags: []
comments: []
language: jp
---
<p>チュートリアル8では、基本的なシェーディングについて学びます。ここでは次のことを学びます。<br />
In this 8th tutorial, we will learn how to do some basic shading. This includes :</p>
<ul>
<li>光源に近ければより光らせます。<&#47;li>
<li>光の反射によるハイライト(鏡面光)<&#47;li>
<li>光が直接向かっていなければ暗く見えます。(拡散光)<&#47;li>
<li>その他（環境光）<&#47;li><br />
<&#47;ul><br />
次のことは学びません。</p>
<ul>
<li>影、複数のチュートリアルで扱います。<&#47;li>
<li>鏡のような反射(水も含みます。)<&#47;li>
<li>表面に広がったような洗練された光るもの(ワックスのようなものです。)<&#47;li>
<li>異方性の物質(磨かれた物体のようなものです。)<&#47;li>
<li>より現実に近いものを表現しようとする物理ベースのシェーディング<&#47;li>
<li>アンビエントオクルージョン(洞窟のなかのようなものです。)<&#47;li>
<li>色のブレンド(赤いカーペットは白い天井をほんのすこし赤くします。)<&#47;li>
<li>透明<&#47;li>
<li>大域照明(上で挙げたものをまとめた名前です。)<&#47;li><br />
<&#47;ul><br />
要するに基礎だけです。</p>
<h1>法線<&#47;h1><br />
これまでのチュートリアルでは、法線の本当の意味を理解せずに使ってきました。</p>
<h2>三角形の法線<&#47;h2><br />
平面の法線とはその平面に垂直な長さが1のベクトルです。</p>
<p>三角形の法線とはこの三角形に垂直で長さが1のベクトルです。法線は三角形の辺の2つの外積を取ることで簡単に計算できます。(aとbの外積はその二つに垂直なベクトルを作ります。覚えていますか？)そして正規化します。つまりそのベクトルの長さを1にします。擬似コードは次のとおりです。</p>
<pre>triangle ( v1, v2, v3 )<br />
edge1 = v2-v1<br />
edge2 = v3-v1<br />
triangle.normal = cross(edge1, edge2).normalize()<&#47;pre><br />
法線(normal)と正規化(normalize())を混同しないでください。normalize()は(法線とは限らない)ベクトルの長さでそのベクトル自身を割ることで長さを1にします。法線(normal)とは垂直線のベクトルを表す名前です。</p>
<h2>頂点法線<&#47;h2><br />
三角形の法線の拡張で、ある頂点の周辺の三角形の法線の組み合わせを頂点の法線と呼びます。頂点シェーダでは三角形ではなく頂点を扱うので、これはとても便利です。だから頂点ごとに情報があるほうが良いのです。なにより、OpenGLでは三角形上の情報を持てません。擬似コードは次のとおりです。</p>
<pre>vertex v1, v2, v3, ....<br />
triangle tr1, tr2, tr3 &#47;&#47; all share vertex v1<br />
v1.normal = normalize( tr1.normal + tr2.normal + tr3.normal )<&#47;pre></p>
<h2>OpenGLでの頂点法線の使用方法<&#47;h2><br />
OpenGLで法線を使うのはとても簡単です。法線は頂点の属性です。だから位置や色、UV座標と同じようにいつもどおりやっていきます。チュートリアル7で作ったloadOBJローダはOBJファイルから既に法線情報を読み込んでいます。</p>
<pre class="brush: cpp">GLuint normalbuffer;<br />
 glGenBuffers(1, &amp;normalbuffer);<br />
 glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);<br />
 glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &amp;normals[0], GL_STATIC_DRAW);<&#47;pre><br />
and</p>
<pre class="brush: cpp"> &#47;&#47; 3つ目の属性：法線<br />
 glEnableVertexAttribArray(2);<br />
 glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);<br />
 glVertexAttribPointer(<br />
     2,                                &#47;&#47; 属性<br />
     3,                                &#47;&#47; サイズ<br />
     GL_FLOAT,                         &#47;&#47; タイプ<br />
     GL_FALSE,                         &#47;&#47; 正規化？<br />
     0,                                &#47;&#47; ストライド<br />
     (void*)0                          &#47;&#47; 配列バッファオフセット<br />
 );<&#47;pre><br />
はじめるにはこれで充分です。</p>
<h1>拡散光<&#47;h1></p>
<h2>表面法線の重要性<&#47;h2></p>
<p>光が物に当たったとき、その一部は全方向に反射されます。これが拡散光です。(他の部分がどのようになるかは後で見ていきます。)</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuseWhite1.png"><img class="alignnone size-full wp-image-225" title="diffuseWhite" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuseWhite1.png" alt="" width="500" height="303" &#47;><&#47;a></p>
<p>特定の光の束が表面に到着したとき、光が到達した角度に応じて違うように照らされます。</p>
<p>もし光が表面に垂直ならば、狭い表面上に集中します。もし光が熟視角で到達したならば、同じ量の光がより広い表面に広がっていきます。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuseAngle.png"><img class="alignnone size-full wp-image-227" title="diffuseAngle" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuseAngle.png" alt="" width="600" height="500" &#47;><&#47;a></p>
<p>これは、熟視角で到達し光の場合、表面の各点はより暗く見えることを意味します。(ただし、より広い範囲が照らされます。つまり光の総量は変わりません。)</p>
<p>これは、ピクセルの色を計算するときに、光の入ってきた角度と表面の法線との角度が重要になることを意味します。次のことを得ます。</p>
<pre class="brush: fs">&#47;&#47; 法線と光の方向の角度のコサイン<br />
&#47;&#47; 0以上に固定します。<br />
&#47;&#47;  - 光が三角形に水平の場合 -> 1<br />
&#47;&#47;  - 光が三角形に垂直の場合 -> 0<br />
float cosTheta = dot( n,l );</p>
<p>color = LightColor * cosTheta;<&#47;pre><br />
ここでnは表面の法線で、lは表面から光に向かう方向の単位ベクトルを表します。(反対の方向ではありません。直感的ではありませんが、計算を簡単にします。)</p>
<h2>符号に関する注意<&#47;h2><br />
上のcosThetaの式では何か忘れています。もし光が三角形の後ろにあると、nとlは反対になります。だからnとlは負になります。これは"色＝負の数"を意味しますがこれでは意味が分かりません。だからcosThetaの下限を0に固定します。</p>
<pre class="brush: fs">&#47;&#47; 法線と光の方向の角度のコサイン<br />
&#47;&#47; clamped above 0<br />
&#47;&#47;  - 光が三角形に水平の場合 -> 1<br />
&#47;&#47;  - 光が三角形に垂直の場合 -> 0<br />
&#47;&#47;  - 光が三角形の裏側の場合 -> 0<br />
float cosTheta = clamp( dot( n,l ), 0,1 );</p>
<p>color = LightColor * cosTheta;<&#47;pre></p>
<h2>物体の色<&#47;h2><br />
もちろん、アウトプットカラーは物体の色にも影響されます。この画像では白い光は緑・赤・青の光から構成されています。光が赤い物体にあたったとき、緑と青の光は吸収され、赤い光だけが残ります。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuseRed.png"><img class="alignnone size-full wp-image-226" title="diffuseRed" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuseRed.png" alt="" width="500" height="303" &#47;><&#47;a></p>
<p>簡単な計算式でこれを実現できます。</p>
<pre class="brush: fs">color = MaterialDiffuseColor * LightColor * cosTheta;<&#47;pre></p>
<h2>光のモデル化<&#47;h2><br />
ろうそくのように空間の全方向に放出されるような光であると仮定します。</p>
<p>そのような光の場合、表面に到達する光束は光との距離に依存します。つまり遠くでは少ない光しか届きません。実際、光の量は距離の2乗で少なくなります。</p>
<pre class="brush: fs">color = MaterialDiffuseColor * LightColor * cosTheta &#47; (distance*distance);<&#47;pre><br />
最後に、光の強さを調節するようなパラメータも必要です。これはLightColorにエンコードされます。(後のチュートリアルで見ます。)しかし、ここではただ色(例えば白色)と強さ(例えば60ワット)を持っていることとします。</p>
<pre class="brush: fs">color = MaterialDiffuseColor * LightColor * LightPower * cosTheta &#47; (distance*distance);<&#47;pre></p>
<h2>すべてを合わせる<&#47;h2><br />
このコードを動かすには、いくつかのパラメータ(色や強さ)とコードが必要です。</p>
<p>MaterialDiffuseColorは単純にテクスチャから取り出します。</p>
<p>LightColorとLightPowerはGLSL uniformを通してシェーダでセットします。</p>
<p>cosThetaはnとlに依存します。どの空間でも表現できますが、ここではカメラ空間を選びます。なぜならカメラ空間だと光の位置を計算するのが簡単だからです。</p>
<pre class="brush: fs">&#47;&#47; カメラ空間で、計算されたフラグメントの法線<br />
 vec3 n = normalize( Normal_cameraspace );<br />
 &#47;&#47; 光の方向(フラグメントから光の方向)<br />
 vec3 l = normalize( LightDirection_cameraspace );<&#47;pre><br />
Normal_cameraspaceとLightDirection_cameraspaceは頂点シェーダで計算され、フラグメントシェーダへ送られます。</p>
<pre class="brush: vs">&#47;&#47; クリップ空間での頂点の出力位置、MVP&times;位置<br />
gl_Position =  MVP * vec4(vertexPosition_modelspace,1);</p>
<p>&#47;&#47; ワールド空間での頂点の位置、M&times;位置<br />
Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;</p>
<p>&#47;&#47; カメラ空間で、頂点からカメラへ向かうベクトル<br />
&#47;&#47; カメラ空間ではカメラは原点(0,0,0)にあります。<br />
vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;<br />
EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;</p>
<p>&#47;&#47; カメラ空間で、頂点から光へ向かうベクトル。Mは単位行列なので除外します。<br />
vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;<br />
LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;</p>
<p>&#47;&#47; カメラ空間での、頂点の法線<br />
Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz; &#47;&#47; Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.<&#47;pre><br />
このコードは難しそうに見えますが、チュートリアル3で習ったこと以外は使っていません。各ベクトルの名前に空間の名前が入れるように注意しました。だから、何が起こっているかを追っていくのがより簡単になります。<strong>あなたもそういう記法を取るべきです。<&#47;strong></p>
<p>MとVはモデル行列とビュー行列で、MVP行列と同じようにシェーダへ送られます。</p>
<h2>実行<&#47;h2><br />
拡散光を実装する上で必要となる情報はすべて出ました。やってみて、苦労しながら学びましょう。 :)</p>
<h2>結果<&#47;h2><br />
拡散光要素のみで、次のような結果を得ます。(またまたひどいテクスチャですみません。)</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuse_only.png"><img class="alignnone size-large wp-image-228" title="diffuse_only" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuse_only-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>前よりはよくなりましたが、まだ足りないものがあります。特に、clamp()を使ったのでスザンヌの後ろ側が真っ黒です。</p>
<h1>環境光<&#47;h1><br />
環境光ではずるをします。</p>
<p>スザンヌの後ろ側はもう少し明るくなることを期待しています。なぜなら実生活ではランプは壁の後ろも照らすからです。それは物体の後ろ側を(より少ない)光で照らしています。</p>
<p>これを計算するには計算コストが高すぎます。</p>
<p>だから一般的な方法は単純に光を偽装します。実は、3Dモデルの後ろ側が真っ黒にならないようにするために、単純に3Dモデルに<em>発光<&#47;em>させるだけです。</p>
<p>これは次のように実現できます。</p>
<pre class="brush: fs">vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;<&#47;pre></p>
<pre class="brush: fs">color =<br />
 &#47;&#47; 環境光：直接当たらない光をシミュレートします。<br />
 MaterialAmbientColor +<br />
 &#47;&#47; 拡散光：物体の"色"<br />
 MaterialDiffuseColor * LightColor * LightPower * cosTheta &#47; (distance*distance) ;<&#47;pre><br />
どうなったか見てみましょう。</p>
<h2>結果<&#47;h2><br />
OK、少しよくなりました。より良い結果を得るために(0.1, 0.1, 0.1)を調整するのもよいでしょう。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuse_ambiant.png"><img class="alignnone size-large wp-image-229" title="diffuse_ambiant" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuse_ambiant-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<h1>鏡面光<&#47;h1><br />
反射する光のほかの部分は表面の光の反射する方向へ大部分反射します。これが鏡面光です。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;specular.png"><img class="alignnone size-full wp-image-232" title="specular" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;specular.png" alt="" width="500" height="251" &#47;><&#47;a></p>
<p>画像で見たように、葉のような形をしています。極端なケースでは、拡散光はなくその葉はとても狭い範囲で(すべての光は一つの方向へ反射し)鏡のようになります。</p>
<p>(<em>鏡を得るためにパラメータを微調整することも出来ますが、ここでは、この鏡で考慮すべきことはランプだけです。だから風変わりな鏡のようになります。<&#47;em>)</p>
<pre class="brush: fs">&#47;&#47; アイ(目)ベクトル(カメラのほうへ向かう)<br />
vec3 E = normalize(EyeDirection_cameraspace);<br />
&#47;&#47; 三角形が光を反射する方向<br />
vec3 R = reflect(-l,n);<br />
&#47;&#47; アイベクトルと反射ベクトルの間の角度のコサイン<br />
&#47;&#47; 0以上に固定します。<br />
&#47;&#47;  - 反射する方向を向いている -> 1<br />
&#47;&#47;  - 他の方向を見ている -> < 1<br />
float cosAlpha = clamp( dot( E,R ), 0,1 );</p>
<p>color =<br />
    &#47;&#47; 環境光：直接当たらない光をシミュレートします。<br />
    MaterialAmbientColor +<br />
    &#47;&#47; 拡散光：物体の"色"<br />
    MaterialDiffuseColor * LightColor * LightPower * cosTheta &#47; (distance*distance) ;<br />
    &#47;&#47; 鏡面光：鏡のように反射したハイライト<br />
    MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) &#47; (distance*distance);<&#47;pre><br />
Rは光が反射する方向です。Eは目の方向とは逆です。("l"と同じです。)もし二つの角度が小さければ、反射する方向を見ていることを意味します。</p>
<p>pow(cosAlpha,5)は反射する"葉"の広さを調整するために使います。薄い"葉"を得るために5乗しています。</p>
<h2>Final result<&#47;h2><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuse_ambiant_specular.png"><img class="alignnone size-large wp-image-233" title="diffuse_ambiant_specular" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;05&#47;diffuse_ambiant_specular-1024x793.png" alt="" width="640" height="495" &#47;><&#47;a></p>
<p>鼻や眉の鏡面光のハイライトに注目してください。</p>
<p>このシェーディングモデルは長い間簡単化のために使われてきました。しかし、これには多くの問題があります。だからmicrofacet BRDFのような物理ベースのモデルに置き換えられます。しかし、それは後のチュートリアルで見ます。</p>
<p>次のチュートリアルでは、VBOの性能を向上させる方法を学びます。これがはじめての中級編のチュートリアルです！</p>
