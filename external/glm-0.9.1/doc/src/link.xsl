<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" media-type="text/html; charset=ISO-8859-1" />

  <xsl:include href="./util.xsl" />

  <xsl:template match="/">
    <html>
      <head>
        <title>OpenGL Mathematics: Links</title>
        <meta http-equiv="Content-Language" content="fr, be, ca, lu, ch" />
        <meta http-equiv="Content-Type" content="application/xhtml+xml; charset=iso-8859-1" />
        <meta name="copyright" content="&#65533; 2005 C-Truc Creation" />
        <link href="./common/style.css" rel="stylesheet" media="screen, print, embossed" type="text/css" />

        <script type="text/javascript">
          var _gaq = _gaq || [];
          _gaq.push(['_setAccount', 'UA-20182250-1']);
          _gaq.push(['_setDomainName', '.g-truc.net']);
          _gaq.push(['_trackPageview']);

          (function() {
          var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
          ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
          var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
          })();
        </script>
      </head>
      <body>
        <div class="title1">
          <img src="./common/title.png" alt="OpenGL Mathematics" />
        </div>
        <table>
          <tr>
            <td class="menu">
              <div class="menu1">
                <a class="menu" href="./glm/downloads/section/download/@link">
                  Download <xsl:value-of select="./glm/downloads/section/download/@name" />
                </a>
              </div>
              <hr />
              <div class="menu2">
                <a class="menu" href="./index.html">News</a>
              </div>
              <div class="menu2">
                <a class="menu" href="./download.html">Downloads</a>
              </div>
              <div class="menu2">
                <a class="menu" href="./changelog.html">Changelog</a>
              </div>
              <div class="menu2">
                <a class="menu" href="./glm-manual.pdf">User manual</a>
              </div>
              <div class="menu2">
                <a class="menu" href="./html/index.html">API Documentation</a>
              </div>
				<div class="menu2">
					<a class="menu" href="http://ogl-math.git.sourceforge.net/git/gitweb.cgi?p=ogl-math/ogl-math;a=snapshot;h=HEAD;sf=tgz">GIT HEAD snapshot</a>
				</div>
			  <div class="menu2">
                <a class="menu" href="http://ogl-math.git.sourceforge.net/git/gitweb.cgi?p=ogl-math/ogl-math;a=summary">Browse Git repository</a>
              </div>
              <div class="menu2">
                <a class="menu" href="https://sourceforge.net/projects/ogl-math/">SF.net page</a>
              </div>
              <div class="menu2">
                <a class="menu" href="https://sourceforge.net/apps/trac/ogl-math">Bug reports</a>
              </div>
              <div class="menu2">
                <a class="menu" href="./link.html">Links</a>
              </div>
              <hr />
              <div class="menu2">
                <a href="http://validator.w3.org/check/referer">
                  <img class="menu-img" src="http://www.w3.org/Icons/valid-xhtml11" alt="Valid XHTML 1.1!" />
                </a>
              </div>
              <div class="menu2">
                <a href="http://www.opengl.org">
                  <img class="menu-img" src="./common/opengl.jpg" alt="OpenGL"/>
                </a>
              </div>
              <div class="menu2">
                <a href="http://www.sourceforge.net">
                  <img class="menu-img" src="./common/sourceforge.gif" alt="SourceForge"/>
                </a>
              </div>
              <div class="menu2">
                <a href="http://www.g-truc.net">
                  <img class="menu-img" src="./common/g-truc.jpg" alt="G-Truc"/>
                </a>
              </div>
              <hr />
            </td>
            <td class="page">
              <xsl:apply-templates select="./glm/links" />
            </td>
          </tr>
        </table>
        <div class="title3">
          <xsl:value-of select="./glm/@copyright" />
          <a href="http://www.g-truc.net">G-Truc Creation</a>
        </div>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="links">
    <div>
      <div class="title2">Links</div>
      <div class="issue-content">
        This page lists all the documents that helped to develop OpenGL Mathematics.
      </div>
      <br />
      <xsl:apply-templates select="./link" />
    </div>
  </xsl:template>

  <xsl:template match="link">
    <div class="issue-title">
      <a href="{./@link}">
        <xsl:value-of select="./@name"/>
      </a>
    </div>
    <div class="issue-content">
      <xsl:value-of select="."/>
    </div>
    <br />
  </xsl:template>

</xsl:stylesheet>
