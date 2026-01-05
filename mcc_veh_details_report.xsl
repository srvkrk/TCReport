<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:plm="http://www.plmxml.org/Schemas/PLMXMLSchema"
    xmlns="urn:schemas-microsoft-com:office:spreadsheet"
    xmlns:o="urn:schemas-microsoft-com:office:office"
    xmlns:x="urn:schemas-microsoft-com:office:excel"
    xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
    xmlns:html="http://www.w3.org/TR/REC-html40" >
    
    <xsl:output method="xml" version="1.0" indent="yes" />
    <xsl:strip-space elements="*"/>
    
    <xsl:template match="/">
        <xsl:call-template name="ReportHeader"></xsl:call-template>
    </xsl:template>
    
    <xsl:template name="ReportHeader">
        <xsl:processing-instruction name="mso-application">progid="Excel.Sheet"</xsl:processing-instruction>
        <Workbook xmlns="urn:schemas-microsoft-com:office:spreadsheet"
            xmlns:o="urn:schemas-microsoft-com:office:office"
            xmlns:x="urn:schemas-microsoft-com:office:excel"
            xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
            xmlns:html="http://www.w3.org/TR/REC-html40">
            
            <Styles>
                <Style ss:ID="s21" ss:Name="ReportHeader">
                    <Interior ss:Color="#696969" ss:Pattern="Solid"/>
                    <Borders>
                        <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                        <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                        <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                        <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                    </Borders>
                    <Alignment ss:Horizontal="Center"/>
                    <Font ss:Color="#FFFFFF" ss:Bold="1" ss:FontName="Cambria" ss:Size="18"/>
                </Style>
                <Style ss:ID="s22" ss:Name="PropertyCell">
                    <Interior ss:Color="#98CAFF" ss:Pattern="Solid"/>
                    <Borders>
                        <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                        <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                        <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                        <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="2.5"/>
                    </Borders>
                    <Font ss:Color="#000000" ss:Bold="1" ss:Size="11" ss:FontName="Calibri"/>
                    <Alignment ss:Horizontal="Center"/>
                </Style>
                <Style ss:ID="s23" ss:Name="ReportInputs">
                    <Font ss:Color="#000000" ss:Bold="1" ss:FontName="Cambria" ss:Size="12"/>
                    <Borders>
                        <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="1"/>
                    </Borders>
                </Style>
                <Style ss:ID="s24" ss:Name="DataCell">
                    <Font ss:Color="#000000" ss:FontName="Calibri" ss:Size="11"/>
                    <Borders>
                        <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="1"/>
                    </Borders>
                    <!--<Alignment ss:Horizontal="Right"/>-->
                </Style>
                <Style ss:ID="s25" ss:Name="L1DataCell">
                    <Font ss:Color="#000000" ss:FontName="Calibri" ss:Size="11"/>
                    <Borders>
                        <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="1"/>
                    </Borders>
                    <Interior ss:Color="#FFD1B3" ss:Pattern="Solid"/>
                </Style>
                <Style ss:ID="s26" ss:Name="PropertyNameCell">
                    <Font ss:Color="#000000" ss:Bold="1" ss:FontName="Calibri" ss:Size="11"/>
                    <Borders>
                        <Border ss:Position="Left" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Top" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Right" ss:LineStyle="Continuous" ss:Weight="1"/>
                        <Border ss:Position="Bottom" ss:LineStyle="Continuous" ss:Weight="1"/>
                    </Borders>
                    <Interior ss:Color="#FFFFFF" ss:Pattern="Solid"/>
                </Style>                
            </Styles>
            
            <Worksheet ss:Name="Sheet1">
                <Table>
                    <Column ss:AutoFitWidth="0" ss:Width="50"/>
                    <Column ss:AutoFitWidth="0" ss:Width="100" AutoFitWidth="1"/>
                    <Column ss:AutoFitWidth="0" ss:Width="100" AutoFitWidth="1"/>
                    <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
                    <Column ss:AutoFitWidth="0" ss:Width="300" AutoFitWidth="1"/>
                    <Column ss:AutoFitWidth="0" ss:Width="100" AutoFitWidth="1"/>
                    <Column ss:AutoFitWidth="0" ss:Width="80" AutoFitWidth="1"/>
                    <Row>  
                        <Cell ss:StyleID="s22" ss:MergeAcross='5'>
                            <Data ss:Type='String'>Vehicle/CR_VC Details Report</Data>
                        </Cell>
                    </Row>
                    <Row></Row>
                    <Row>
                        <Cell ss:StyleID="s26">
                            <Data ss:Type='String'>SR_NO</Data>
                        </Cell>
						<Cell ss:StyleID="s26">
                            <Data ss:Type='String'>VEHICLE/CRVC_NO</Data>
                        </Cell>
						<Cell ss:StyleID="s26">
                            <Data ss:Type='String'>REVISION</Data>
                        </Cell>
						<Cell ss:StyleID="s26">
                            <Data ss:Type='String'>SEQUENCE</Data>
                        </Cell>
                        <Cell ss:StyleID="s26">
                            <Data ss:Type='String'>DESCRIPTION</Data>
                        </Cell>
                        <Cell ss:StyleID="s26">
                            <Data ss:Type='String'>LATEST_RELEASED_GATEWAY</Data>
                        </Cell>
						<Cell ss:StyleID="s26">
                            <Data ss:Type='String'>PRODUCT_LINE</Data>
                        </Cell>
						<Cell ss:StyleID="s26">
                            <Data ss:Type='String'>PLATFORM</Data>
                        </Cell>
						<Cell ss:StyleID="s26">
                            <Data ss:Type='String'>ERC_RELEASE_DATE</Data>
                        </Cell>
                    </Row>
                    <xsl:call-template name="generateDesignRevPartsList"></xsl:call-template>
                    <Row></Row>
                    <Row></Row>
                </Table>
            </Worksheet>
        </Workbook>
    </xsl:template>
    
    <xsl:template name="generateDesignRevPartsList">
        <xsl:for-each select="DetailsRpt/DataList">
			<Row>
				<Cell ss:StyleID="s24">
					<Data ss:Type='String'><xsl:value-of select="SrNo"/></Data>
				</Cell>
			    <Cell ss:StyleID="s24">
					<Data ss:Type='String'><xsl:value-of select="PartNo"/></Data>
				</Cell>
				<Cell ss:StyleID="s24">
					<Data ss:Type='String'><xsl:value-of select="PartRev"/></Data>
				</Cell>
                <Cell ss:StyleID="s24">
                    <Data ss:Type='String'><xsl:value-of select="PartSeq"/></Data>
                </Cell>
				<Cell ss:StyleID="s24">
                    <Data ss:Type='String'><xsl:value-of select="Desc"/></Data>
                </Cell>
				<Cell ss:StyleID="s24">
                    <Data ss:Type='String'><xsl:value-of select="DRAR"/></Data>
                </Cell>
				<Cell ss:StyleID="s24">
                    <Data ss:Type='String'><xsl:value-of select="Prod"/></Data>
                </Cell>
				<Cell ss:StyleID="s24">
                    <Data ss:Type='String'><xsl:value-of select="Plat"/></Data>
                </Cell>
				<Cell ss:StyleID="s24">
                    <Data ss:Type='String'><xsl:value-of select="NormalRlzd"/></Data>
                </Cell>
			</Row>
        </xsl:for-each>
    </xsl:template>
    
</xsl:stylesheet>