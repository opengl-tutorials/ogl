# example usage
# cd ......\tutorials-github
# C:\Python27\python.exe convert.py beginners-tutorials\tutorial-4-a-colored-cube\index.markdown /assets/images/tuto-4-colored-cube/


import fileinput
import sys

p = sys.argv[1]
newimagespath = sys.argv[2]

import re

for line in fileinput.FileInput(p,inplace=1):
    line = line.replace("</h1>","\n")
    line = line.replace("<h1>","\n#")
    line = line.replace("</h2>","\n")
    line = line.replace("<h2>","\n##")
    line = line.replace("</h3>","\n")
    line = line.replace("<h3>","\n###")
    
    line = line.replace("</p>","")
    line = line.replace("<br />","")
    

    line = line.replace("<ul>","")
    line = line.replace("</ul>","")

    line = line.replace("<li>","* ")
    line = line.replace("</li>","")
    
    line = line.replace("&nbsp;"," ")
    line = line.replace("<p>","\n")
    
    line = line.replace("<em>","*")
    line = line.replace("</em>","*")
    line = line.replace("<strong>","**")
    line = line.replace("</strong>","**")
    
    
    line = line.replace("<ol>","")
    line = line.replace("</ol>","")
	
    line = line.replace("&amp;","&")

    
    line = line.replace("<pre class=\"brush: cpp\">","{% highlight cpp linenos %}\n")
    line = line.replace("<pre class=\"brush: cpp;\">","{% highlight cpp linenos %}\n")
    line = line.replace("<pre class=\"brush:cpp\">","{% highlight cpp linenos %}\n")
    line = line.replace("<pre class=\"brush:vs\">","{% highlight glsl linenos cssclass=highlightglslvs %}\n")
    line = line.replace("<pre class=\"brush: vs\">","{% highlight glsl linenos cssclass=highlightglslvs %}\n")
    line = line.replace("<pre class=\"brush:fs\">","{% highlight glsl linenos cssclass=highlightglslfs %}\n")
    line = line.replace("<pre class=\"brush: fs\">","{% highlight glsl linenos cssclass=highlightglslfs %}\n")
    line = line.replace("<pre class=\"brush:plain\">","{% highlight text linenos %}\n")
    line = line.replace("<pre class=\"brush: plain\">","{% highlight text linenos %}\n")
    line = line.replace("<pre class=\"brush:c\">","{% highlight c linenos %}\n")
    line = line.replace("<pre class=\"brush: c\">","{% highlight c linenos %}\n")
    line = line.replace("<pre class=\"brush:fs; highlight: [4, 6]\">","{% highlight glsl linenos cssclass=highlightglslfs %}\n")
    line = line.replace("<pre class=\"brush:fs; highlight: [1,3] \">","{% highlight glsl linenos cssclass=highlightglslfs %}\n")
	
    line = line.replace("<pre>","{% highlight text linenos %}\n")
	
	
    line = line.replace("</pre>","\n{% endhighlight %}")


	
    line = line.replace("<script>// <![CDATA[","")
    line = line.replace("SyntaxHighlighter.all()","")
    line = line.replace("// ]]></script>","")
	
	
    line = line.replace("layout: default","layout: page")
	

    line = line.replace("##\n","\n")

	
	
	
	

	# image with link
	#<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/WorkingDir.png"><img class="size-medium wp-image-546 alignnone" title="WorkingDir" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/WorkingDir-300x211.png" alt="" width="300" height="211" /></a>
	#<a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/04/StartupProject.png"><img class="size-medium wp-image-544 alignright" title="StartupProject" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/04/StartupProject-185x300.png" alt="" width="185" height="300" /></a>
    #<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/CMake.png"><img class="alignnone size-medium wp-image-8" title="CMake" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/CMake.png" alt="" width="846" height="392" /></a>
    line = re.sub(r"<a.*?href=\".*?\".*?><img .*?src=\"(.*?)\" alt.*?/></a>", r"![](\1)\n", line)

	
	#link with text
	#<a href="http://qt-project.org/">Qt Creator</a>
    line = re.sub(r"<a.*?href=\"(.*?)\".*?>(.+?)</a>", r"[\2](\1)", line)
	
	#image path
	#http://www.opengl-tutorial.org/wp-content/uploads/2011/04/WorkingDir-300x211.png
	#http://www.opengl-tutorial.org/wp-content/uploads/2011/04/WorkingDir.png
    line = re.sub(r"\(http://www.opengl-tutorial.org/wp-content/uploads/20[0-9][0-9]/[0-9][0-9]/(.+?)-[0-9]+x[0-9]+(\.[a-zA-Z]+)\)", r"({{site.baseurl}}"+newimagespath+r"\1\2)", line)
    line = re.sub(r"\(http://www.opengl-tutorial.org/wp-content/uploads/20[0-9][0-9]/[0-9][0-9]/(.+?)(\.[a-zA-Z]+)\)", r"({{site.baseurl}}"+newimagespath+r"\1\2)", line)

    print line,