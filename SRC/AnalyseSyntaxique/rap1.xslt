<!DOCTYPE rapport SYSTEM "rap1.dtd">
<xsl:stylesheet version="1.0" xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="rapport">
  <html><body>
    <p>Liste de nombres :</p>
    <ul>
      <xsl:apply-templates/>
    </ul>
  </body></html>
</xsl:template>

<xsl:template match="chapitre">
  <html><body>
    <p>Jean Michel Loutre :</p>
    <ul>
      <xsl:apply-templates/>
    </ul>
  </body></html>
</xsl:template>

<xsl:template match="section">
  <html><body>
    <p>TAGUEULE</p>
    <ul>
      <xsl:apply-templates/>
    </ul>
  </body></html>
</xsl:template>


<xsl:template match="titre">
    <p>Popo</p>
</xsl:template>

</xsl:stylesheet>