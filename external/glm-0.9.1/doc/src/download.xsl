<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" media-type="text/html; charset=ISO-8859-1" />

  <xsl:include href="./util.xsl" />

  <xsl:template match="/">
    <html>
      <head>
        <title>OpenGL Mathematics: Downloads</title>
        <meta http-equiv="Content-Language" content="en" />
        <meta http-equiv="Content-Type" content="application/xhtml+xml; charset=iso-8859-1" />
        <meta name="copyright" content="G-Truc Creation" />
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
        <table>
          <tr>
            <td class="menu">
              <xsl:apply-templates select="./glm/menu" />
            </td>
            <td class="page">
              <div class="title1">
                <img src="./common/title.png" alt="OpenGL Mathematics" />
              </div>
              <xsl:apply-templates select="./glm/about-short" />
              <br />
              <div>
                <div class="title4">Current release</div>
                <xsl:apply-templates select="./download" />
              </div>
              <div class="issue-content">
                <xsl:value-of select="/glm/downloads/section/download/@date"/>:
                <a href="{/glm/downloads/section/download/@link}">
                  <xsl:value-of select="/glm/downloads/section/download/@name" />
                </a>
                (<xsl:value-of select="/glm/downloads/section/download/@size"/>)
              </div>
              <div class="news-separator">_________________</div>
              <br />
              <xsl:apply-templates select="./glm/downloads/section" />

              <div class="email">
                <img src="./common/email.png" alt="email not available as text" />
              </div>
              <div class="news-separator">_________________</div>
              <br />
              <div class="title3">
                <xsl:value-of select="./glm/@copyright" />
                <a href="http://www.g-truc.net">G-Truc Creation</a>
              </div>
            </td>
          </tr>
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="section">
    <div>
      <div class="title4">
        <xsl:value-of select="./@name"/>
      </div>
      <xsl:apply-templates select="./download" />
    </div>
    <div class="news-separator">_________________</div>
    <br />
  </xsl:template>

  <xsl:template match="download">
    <div class="issue-content">
      <xsl:value-of select="./@date"/>: <a href="{./@link}">
        <xsl:value-of select="./@name"/>
      </a> (<xsl:value-of select="./@size"/>)
    </div>
  </xsl:template>

</xsl:stylesheet>
