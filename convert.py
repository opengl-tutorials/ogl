# example usage
# cd ......\tutorials-github
# C:\Python27\python.exe convert.py beginners-tutorials\tutorial-4-a-colored-cube\index.markdown /assets/images/tuto-4-colored-cube/


import fileinput
import sys

p = sys.argv[1]
newimagespath = sys.argv[2]

import re

for line in fileinput.FileInput(p,inplace=1):

    # fixing WPML's stupidity
    line = line.replace("&#47;","/")
    line = line.replace("&rdquo;", "\"")
    line = line.replace("&ldquo;", "\"")
    line = line.replace("&mdash;", "-")
    line = line.replace("&hellip;", "...")
    line = line.replace("<!-- Include required JS files -->", "/")
    line = line.replace("&#47;","/")
    line = line.replace("<!-- At least one brush, here we choose JS. You need to include a brush for every     language you want to highlight -->", "")
    line = line.replace(" style=\"text-align: left\"", "")
    line = line.replace(" style=\"padding-left: 120px\"", "")
    line = line.replace("<div></div>", "");

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

    line = line.replace("<address>", "*")
    line = line.replace("</address>", "*")

    
    line = line.replace("<pre class=\"brush: cpp\">","``` cpp\n")
    line = line.replace("<pre class=\"brush: cpp;\">","``` cpp\n")
    line = line.replace("<pre class=\"brush:cpp\">","``` cpp\n")
    line = line.replace("<pre class=\"brush:vs\">","``` glsl vs\n")
    line = line.replace("<pre class=\"brush: vs\">","``` glsl vs\n")
    line = line.replace("<pre class=\"brush:fs\">","``` glsl fs\n")
    line = line.replace("<pre class=\"brush: fs\">","``` glsl fs\n")
    line = line.replace("<pre class=\"brush:plain\">","```\n")
    line = line.replace("<pre class=\"brush: plain\">","```\n")
    line = line.replace("<pre style=\"background-color: white; color: black;\">","{% highlight text %}\n")
    line = line.replace("<pre class=\"brush:c\">","{% highlight c linenos %}\n")
    line = line.replace("<pre class=\"brush: c\">","{% highlight c linenos %}\n")
    line = line.replace("<pre class=\"brush:fs; highlight: [4, 6]\">","``` glsl fs\n")
    line = line.replace("<pre class=\"brush:fs; highlight: [1,3] \">","``` glsl fs\n")
	
    line = line.replace("<pre>","```\n")
	
	
    line = line.replace("</pre>","\n```")


	
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