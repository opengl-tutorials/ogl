<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:strip-space elements="*" />

	<xsl:output 
		method="xml"
		media-type="application/xhtml+xml; charset=iso-8859-1"
		version="1.0"
		encoding="iso-8859-1"
		standalone="no"
		omit-xml-declaration="no"
		doctype-public="-//W3C//DTD XHTML 1.1//EN" 
		doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
		indent="no" />

	<xsl:template match="link">
		<a href="{./@href}"><xsl:value-of select="." /></a>
	</xsl:template>

	<xsl:template match="image">
		<xsl:choose>
			<xsl:when test="./@href">
				<xsl:element name="a">
					<xsl:attribute name="class">menu-titre2</xsl:attribute>
					<xsl:attribute name="href"><xsl:value-of select="./@href" /></xsl:attribute>
					<xsl:element name="img">
						<xsl:attribute name="src"><xsl:value-of select="@file" /></xsl:attribute>
						<xsl:attribute name="alt"><xsl:value-of select="@file" /></xsl:attribute>
					</xsl:element>
				</xsl:element>
			</xsl:when>
			<xsl:otherwise>
				<xsl:element name="img">
					<xsl:attribute name="src"><xsl:value-of select="@file" /></xsl:attribute>
					<xsl:attribute name="alt"><xsl:value-of select="@file" /></xsl:attribute>
				</xsl:element>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	  <xsl:template match="image-list">
		<div class="news-image">
		  <xsl:apply-templates select="./image-element" />
		</div>
	  </xsl:template>

	  <xsl:template match="image-element">
		<a href="{./@normal}">
		  <img src="{./@small}" alt="{./@title}" />
		</a>
	  </xsl:template>

	<xsl:template match="list">
		<div xmlns="http://www.w3.org/1999/xhtml">
			<xsl:if test="./@name">
				<xsl:choose>
					<xsl:when test="./@href">
						<span class="list">
							<a href="{./@href}">
								<xsl:value-of select="./@name" />
							</a>
						</span>
					</xsl:when>
					<xsl:otherwise>
						<span class="list">
							<xsl:value-of select="./@name" />
						</span>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:if>
			<ul>
				<xsl:apply-templates select="./list-element"/>
			</ul>
		</div>
	</xsl:template>

	<xsl:template match="list-element">
		<li xmlns="http://www.w3.org/1999/xhtml">
			<xsl:choose>
				<xsl:when test="./@href">
					<a href="{./@href}">
						<xsl:apply-templates />
					</a>
				</xsl:when>
				<xsl:otherwise>
					<xsl:apply-templates />
				</xsl:otherwise>
			</xsl:choose>
		</li>
	</xsl:template>

	<xsl:template match="element">
		<xsl:apply-templates /><br />
	</xsl:template>

	<xsl:template match="paragraph">
		<p><xsl:text /><xsl:apply-templates /><xsl:text /></p>
	</xsl:template>

	<xsl:template match="about-short">
	  <div class="title3">
		<xsl:apply-templates select="./element" />
	  </div>
	  <br />
	</xsl:template>
	  
	<xsl:template match="source">
		<xsl:value-of select="./@type"/>: <a href="{./@href}"><xsl:value-of select="."/></a><br />
	</xsl:template>

	<xsl:template match="menu">
	  <div class="menu1">
		<br />
		<div>
		  <a href="./goodies/logo1920x1200.png">
			<img class="menu-img" src="./common/logo.png" alt="GLM Logo"/>
		  </a>
		</div>
		<br />
		<div>
		  <a class="menu" href="{/glm/downloads/section/download/@link}">
			Download <xsl:value-of select="/glm/downloads/section/download/@name" />
		  </a>
		</div>
	  </div>
	  <br />
	  <xsl:apply-templates select="./menu-group"/>
	  <br />
	  <xsl:apply-templates select="./menu-link"/>
	  <br />
	  <!--div>
		<script type="text/javascript" src="http://feedjit.com/map/?bc=FFFFFF&amp;tc=494949&amp;brd1=FFFFFF&amp;lnk=494949&amp;hc=FF8000&amp;dot=FF8000"></script>
		<noscript>
		  <a href="http://feedjit.com/">Feedjit Live Blog Stats</a>
		</noscript>
	  </div-->
	</xsl:template>

	<xsl:template match="menu-pic">
	  <div class="menu2">
		<a href="{@href}">
		  <img class="menu-img" src="{@image}" alt="{@name}"/>
		</a>
	  </div>
	</xsl:template>

	<xsl:template match="menu-link">
	  <xsl:apply-templates select="./menu-pic"/>
	</xsl:template>
	  
	<xsl:template match="menu-image">
	  <div class="menu2">
		<a href="./common/glm.jpg">
		  <img class="menu-img" src="./common/logo.jpg" alt="G-Truc"/>
		</a>
	  </div>
	</xsl:template>
	  
	<xsl:template match="menu-group">
	  <xsl:apply-templates select="./menu-entry"/>
	  <br />
	</xsl:template>

	<xsl:template match="menu-entry">
	  <div class="menu2">
		<a href="{./@href}">
		  <xsl:value-of select="./@name"/>
		</a>
	  </div>
	</xsl:template>

	<xsl:template match="code">
		<xsl:choose>
			<xsl:when test="./@href">
				<span xmlns="http://www.w3.org/1999/xhtml" class="code-title">
					<a href="{./@href}">
						<xsl:value-of select="./@author" />
					</a>
				</span>
			</xsl:when>
			<xsl:otherwise>
				<span xmlns="http://www.w3.org/1999/xhtml" class="code-title">
					<xsl:value-of select="./@title" />
				</span>
			</xsl:otherwise>
		</xsl:choose>
		<ul xmlns="http://www.w3.org/1999/xhtml" class="code-list">
			<xsl:apply-templates select="./line" />
		</ul>
	</xsl:template>

	<xsl:template match="line">
		<li xmlns="http://www.w3.org/1999/xhtml" class="code-line">
			<xsl:choose>
				<xsl:when test="@align">
					<span class="code-line-content" style="padding-left:{@align}">
						<xsl:apply-templates />
					</span>
				</xsl:when>
				<xsl:otherwise>
					<span class="code-line-content">
						<xsl:apply-templates />
					</span>
				</xsl:otherwise>
			</xsl:choose>
		</li>
	</xsl:template>

	<xsl:template match="progword">
		<xsl:choose>
			<xsl:when test="./@href">
				<span xmlns="http://www.w3.org/1999/xhtml" class="progword">
					<a href="{./@href}">
						<xsl:apply-templates />
					</a>
				</span>
			</xsl:when>
			<xsl:otherwise>
				<span xmlns="http://www.w3.org/1999/xhtml" class="progword">
					<xsl:apply-templates />
				</span>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="keyword">
		<span xmlns="http://www.w3.org/1999/xhtml" class="keyword">
			<xsl:apply-templates />
		</span>
	</xsl:template>

	<xsl:template match="userword">
		<span xmlns="http://www.w3.org/1999/xhtml" class="userword">
			<xsl:apply-templates />
		</span>
	</xsl:template>

	<xsl:template match="codeword">
		<span xmlns="http://www.w3.org/1999/xhtml" class="codeword">
			<xsl:apply-templates />
		</span>
	</xsl:template>

	<xsl:template match="string">
		<span xmlns="http://www.w3.org/1999/xhtml" class="string">
			<xsl:apply-templates />
		</span>
	</xsl:template>

	<xsl:template match="comment">
		<span xmlns="http://www.w3.org/1999/xhtml" class="comment">
			<xsl:apply-templates />
		</span>
	</xsl:template>
	
</xsl:stylesheet>
