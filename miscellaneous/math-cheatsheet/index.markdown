---
layout: page
status: publish
published: true
title: Math Cheatsheet
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 209
wordpress_url: http://www.opengl-tutorial.org/?page_id=209
date: '2011-05-11 20:04:48 +0200'
date_gmt: '2011-05-11 20:04:48 +0200'
categories: []
order: 20
tags: []
---
<h1>Trigonometry</h1></p>
<h2>Pi</h2><br />
const float pi = 3.14159265f; // but an infinity of digits in reality</p>
<h2>Cosinus &amp; Sinus</h2><br />
<img class="alignnone" title="Sine_cosine_one_period" src="http://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/600px-Sine_cosine_one_period.svg.png" alt="" width="600" height="240" /></p>
<address>(From http://commons.wikimedia.org/wiki/User:Geek3 , under GNU Free Documentation License )</address></p>
<h2>Unit circle</h2><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/UnitCircle.png"><img class="alignnone size-full wp-image-213 whiteborder" title="UnitCircle" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/UnitCircle.png" alt="" width="300" height="300" /></a></p>
<address>( Modified from http://en.wikipedia.org/wiki/User:Gustavb under Crative Commons 3.0 )</address>t is an angle in radians.</p>
<p>0 radians = 0 degrees</p>
<p>180 degrees = Pi radians</p>
<p>360 degrees ( full circle ) = 2*Pi radians</p>
<p>90 degrees = Pi/2 radians</p>
<h1>Vectors</h1><br />
ALWAYS know in which coordinates your vector is. See section 3 for details.</p>
<h2>Homogeneous coordinates</h2><br />
A 3D vector is (x,y,z), but a homogeneous 3D vector is (x,y,z,w).</p>
<ul>
<li>w=0 : it's a direction</li>
<li>w=1 : it's a position</li>
<li>else : it may still be correct, but you'd better know what you're doing.</li><br />
</ul><br />
You can only multiply a 4x4 matrix with a homogeneous vector.</p>
<h2>Length</h2><br />
Just like cartesian distance : sqrt( x&sup2; + y&sup2; + z&sup2; ). w doesn't count.</p>
<h2>Cross product</h2><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/Right_hand_rule_cross_product.png"><img class="alignnone size-full wp-image-211" title="Right_hand_rule_cross_product" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/Right_hand_rule_cross_product.png" alt="" width="400" height="353" /></a></p>
<address>( Modified from http://en.wikipedia.org/wiki/User:Acdx , former image under Creative Commons 3.0 )</address>The X is the notation for the cross product. length( a x b ) == length(a) * length(b) * sin(&theta;), so you may want to normalize() the result.</p>
<h2>Dot product</h2></p>
<h2><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/DotProduct.png"><img class="alignnone size-full wp-image-212 whiteborder" title="DotProduct" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/05/DotProduct.png" alt="" width="500" height="133" /></a></h2></p>
<address>( from http://en.wikipedia.org/wiki/File:Dot_Product.svg )</address>A.B = length(A)*cos(Theta) , but most likely computed as A.x*B.x +A.y*B.y +A.z*B.z</p>
<h2>Addition and substraction</h2><br />
compontent-wise :</p>
<pre>res.x = A.x + B.x<br />
res.y = A.y + B.y<br />
...</pre><br />
&nbsp;</p>
<h2>Multiplication</h2><br />
compontent-wise :</p>
<pre>res.x = A.x * B.x<br />
res.y = A.y * B.y<br />
...</pre></p>
<h2>Normalization</h2><br />
Divide the vector by its length :</p>
<pre>normalizedVector = vec * ( 1.0f / vec.length() )</pre></p>
<h1>Matrices</h1></p>
<h2>Matrix-Matrix multiplication</h2><br />
example for a translation matrix :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationExamplePosition1.png"><img class="alignnone size-full wp-image-798" title="translationExamplePosition" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/translationExamplePosition1.png" alt="" width="639" height="82" /></a></p>
<p>&nbsp;</p>
<h2>Matrix-Vector multiplication</h2><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MatrixXVect.gif"><img class="alignnone size-full wp-image-64 whiteborder" title="MatrixXVect" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MatrixXVect.gif" alt="" width="367" height="88" /></a></p>
<h1>Usual Transformations</h1><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MVP.png"><img class="alignnone size-full wp-image-66 whiteborder" title="MVP" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/MVP.png" alt="" width="300" height="382" /></a></p>
<p>... but in your shaders, you can also represent your vectors in tangent space. And in image-space when you do post-effects.</p>
<div id="_mcePaste" class="mcePaste" style="position: absolute; left: -10000px; top: 1254px; width: 1px; height: 1px; overflow: hidden;">res.x = A.x + B.x</div></p>
