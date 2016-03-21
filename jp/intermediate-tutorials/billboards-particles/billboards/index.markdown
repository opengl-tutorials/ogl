---
layout: page
status: publish
published: true
title: ビルボード
date: '2013-10-15 17:15:15 +0200'
date_gmt: '2013-10-15 17:15:15 +0200'
categories: []
order: 110
tags: []
language: jp
---

ビルボードは3D世界にある2D要素です。他のすべての上に表示される2Dメニューではありません。またターンできるような3D面でもありません。ゲームでのHPゲージのような、それらの中間のようなものです。

ビルボードと他のものとの違いは特定の位置に配置されるが、常にカメラの方向を自動で向くように計算されています。

 

#解決策1：2Dでの方法

この方法はとっても簡単です。

画面上でのあなたの位置を計算し、この位置に2Dテキストを表示します。（チュートリアル11を見てください。）

``` cpp
// ここでやってることはすべてチュートリアル3で説明済みです。新しいことはありません。
glm::vec4 BillboardPos_worldspace(x,y,z, 1.0f);
glm::vec4 BillboardPos_screenspace = ProjectionMatrix * ViewMatrix * BillboardPos_worldspace;
BillboardPos_screenspace /= BillboardPos_screenspace.w;

if (BillboardPos_screenspace.z < 0.0f){
    // カメラの後ろにあるものは表示しません。
}
```

この方法の良い点はとても簡単で、ビルボードとカメラの距離によらず常に一定の大きさになってくれる点です。しかし2Dテキストは他のすべてのものの上に表示されるので、他のオブジェクトの上に表示されてしまいます。

 

#解決策2：3Dでの方法

この方法のほうがよりよく、またそこまで複雑でもありません。

目的はメッシュが動いてもカメラの方向に向けることです。

![]({{site.baseurl}}/assets/images/tuto-billboard/2a.gif)


これは適切なモデル行列を生成する問題と捉えることができます。

基本的な考え方は、ビルボードの各コーナーの中心を、カメラの上と横ベクトルにによって移動させることです。

 

![]({{site.baseurl}}/assets/images/tuto-billboard/principle.png)


 

もちろん、ワールド空間でのビルボードの中心座標は知っているものとして、ワールド空間でのカメラの上/右ベクトルが必要となります。

カメラ空間ではカメラの上は(0,1,0)です。これをワールド空間で表現するには単にカメラ空間からワールド空間へ移すような行列を掛ければ良いだけです。これはもちろんビュー行列の逆行列です。

これは次のように簡単に表現できます。
```

CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}
CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}
```

一度これを得れば、最終的な頂点位置を計算するのはとても簡単です。

``` glsl vs
vec3 vertexPosition_worldspace =
    particleCenter_wordspace
    + CameraRight_worldspace * squareVertices.x * BillboardSize.x
    + CameraUp_worldspace * squareVertices.y * BillboardSize.y;
```

* particleCenter_worldspaceは名前が示すとおり、ビルボードの中心位置です。これはvec3で表されます。.
* squareVerticesはオリジナルのメッシュです。左の頂点のため、squareVertices.xは-0.5です。これはカメラの左方向へ移動されます。（*CameraRight_worldspace のため。）
* BillboardSizeはワールド単位でのビルボードのサイズです。

<div><span style="font-size: medium;"><span style="line-height: 24px;">以下に結果を示します。 </span></span><span style="font-size: 16px;"> </span></div>
![]({{site.baseurl}}/assets/images/tuto-billboard/2.gif)


 

squareVerticesは次のように作ります。

``` cpp
// VBOは粒子の4つのベクトルを保持しています。
 static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
 };
```

#解決策3：固定サイズでの3Dでの方法

上で見たように、ビルボードのサイズはカメラとの距離に応じて変わります。こういう感じにしたい場合もあるでしょうが、ライフゲージのように固定サイズにしたい場合もあるでしょう。

画面空間で中心とコーナーの配置を固定したいので次のようにします。画面空間での中心位置とそのオフセットを計算します。

``` cpp
vertexPosition_worldspace = particleCenter_wordspace;
// 粒子の中心の座標を空間座標で得る。
gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);
// パースペクティブ除算を自分自身で行います。
gl_Position /= gl_Position.w;

// 頂点を直接画面空間へ移動します。CameraUp/Right_worlspaceはここではいりません。
gl_Position.xy += squareVertices.xy * vec2(0.2, 0.05);
```

描画パイプラインのこのステージは正規化デバイス座標にあることを覚えて置いてください。
つまり各軸は-1と1の間にあり、ピクセルではありません。

ピクセルでサイズを指定したい場合はBillboardSizeInScreenPercentageの代わりに(ScreenSizeInPixels / BillboardSizeInPixels)を使うだけです。

 

![]({{site.baseurl}}/assets/images/tuto-billboard/3.gif)


 

#解決策4：頂点回転だけ

遠くの木やランプをビルボードとしてモデル化してるシステムもあります。
本当に木を曲げさせたくない場合には、頂点とすべきです。
だから一つの軸の周りで回転させるようなハイブリッドシステムが必要となります。

これは演習として読者に任せます。

 

 
