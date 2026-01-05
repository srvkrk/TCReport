<?xml version="1.0" encoding="utf-8"?> 
<xsl:stylesheet version="1.0"  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" > 
<xsl:output method="html"/> 
<xsl:template match="/"> 

<!-- 
*****************************************************************************************************************
Author : Ujjawal Kumar
Date   : August-2024 

Pls do not copy this code. Copyright@2024.
*****************************************************************************************************************
-->

<html> 
  <head> 
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.9.1/chart.min.js"></script>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js"></script>
	
 <link rel = "stylesheet" href = "//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css"></link>
 <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" />
			
<!-- <script type = "text/javascript"      src = "https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>-->
		
    <script type = "text/javascript" src = "https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.3/jquery-ui.min.js"></script>
	<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>


	  
	<style>
	  h2   {color: blue;}
	  
	  h4 {
	  font-family: Tahoma, Geneva, sans-serif;
	  }
	  
	  p {
		color: #006699;
		font-family: Tahoma, Geneva, sans-serif;
		text-align: center;
		font-size: 14px;
		}
	  
	  table, th, td {
		  border: 0.25px solid #dddfe1;
		  border-collapse: collapse;
		  color: #636363;
		  font-size: 11px;
		  font-family: Tahoma, Geneva, sans-serif;
		  padding: 3px;
		  <!-- white-space: nowrap;   -->
	  }
	  
	  th{
		  background-color: #AED6F1;
		  <!-- white-space: nowrap; -->
		  color: #636363;
		  padding: 5px;
		  text-align: center;
		  <!-- writing-mode: vertical-lr;
		  transform: scale(-1); -->
	  }
	  
	  thlib{
		  background-color: #FFE633;
		  white-space: nowrap;
		  color: #636363;
		  padding: 5px;
		  text-align: center;
		  <!-- writing-mode: vertical-lr;
		  transform: scale(-1); -->
	  }
	  
	  tr:nth-child(even) {
		background-color: #f9fafb;
	  
	  }
	  
	  td:hover {background-color: #ffff99;}
	  tr:hover {background-color: #CDF5FF;}


<!-- 	 .row > div {
		  
		  border: 1px solid grey;
		} -->
		
	.col-md-12 {
		font-size: 16px;
		<!-- font-weight: bold; -->
		background-color: #006699;
		white-space: nowrap;
		color: white;
		text-align: center;
		vertical-align: middle;
		padding-top: 5px;
		padding-bottom: 5px;
	}
	.col-md-6 {
		font-size: 10px;
		<!-- font-weight: bold; -->
		background-color: #006699;
		white-space: nowrap;
		color: white;
		text-align: center;
		vertical-align: middle;
		padding-top: 5px;
		padding-bottom: 5px;
	}
	
	.col-sm-6 {
		font-size: 14px;
		<!-- font-weight: bold; -->
		<!-- background-color: #006699; -->
		white-space: nowrap;
		<!-- color: white; -->
		text-align: center;
		vertical-align: middle;
		padding-top: 2px;
		padding-bottom: 2px;
	}
	
	div.wrap {
	  word-wrap: break-word;
	}
	  
	  
	  	  .label {
		  color: white;
		  padding: 20px;
		}

		.success {background-color: #04AA6D;} /* Green */
		.info {background-color: #2196F3;} /* Blue */
		.warning {background-color: #ff9800;} /* Orange */
		.danger {background-color: #f44336;} /* Red */
		.other {background-color: #e7e7e7; color: black;} /* Gray */
		
.card {
  /* Add shadows to create the "card" effect */
  box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2);
  transition: 0.3s;
  border-radius: 20px; /* 5px rounded corners */
}

/* On mouse-over, add a deeper shadow */
<!-- .card:hover { 
  box-shadow: 0 8px 10px 0 #006699;
}
.card_container:hover {
  color : #dee2e6; 
} -->

/* Add some padding inside the card container */
.card_container {
  padding: 6px 6px;
  <!-- background-color: #006699; -->
  <!-- background-color: #006487; -->
  background-color: white;
<!--   height: 200px;
  width: 500px; -->
<!-- 
#005f87
#006487
#0f789b
#afd7e1
#cde6eb
#f8f9fa
#f0f0f0
#daecf0  
#e9ecef
#dee2e6 -->

  color: #636363;
  font-size: 12px;
  border: 1.25px solid #006699;
  border-radius: 10px; /* 5px rounded corners */
}

/* Add some padding inside the card container */
.grey_div {
  padding: 20px;
  background-color: #f0f0f0;
  color: #f0f0f0;
}


.awc_label {
  padding: 5px;
  margin-top: 10px;
  background-color: #006699;
  color: white;
  <!-- width: 200px;  00E78C #04D401		 -->
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 15px;
  text-align: right;
}

.veh_label_lat {
  padding: 5px;
  margin-top: 10px;
  background-color: #006699;
  color: white;
  <!-- width: 200px;  00E78C #04D401		 -->
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 15px;
  text-align: center;
}

.veh_label_pre {
  padding: 5px;
  margin-top: 10px;
  background-color: #666868;
  color: white;
  <!-- width: 200px;  00E78C #04D401		 -->
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 15px;
  text-align: center;
}

.deep_green {
  padding: 5px;
  margin-top: 10px;
  background-color: #04D401;
  color: green;
  <!-- width: 200px;  00E78C #04D401		 -->
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 12px;
  text-align: center;
}
.light_green {
  padding: 5px;
  margin-top: 10px;
  background-color: #99FAD2;
  color: green;
  <!-- width: 200px;  		 -->
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 12px;
  text-align: center;
}
.yellow {
  padding: 5px;
  margin-top: 10px;
  background-color: #ffff99;
  color: #C48F01;
  <!-- width: 200px;  		 -->
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 12px;
  text-align: center;
}

.grey {
  padding: 5px;
  background-color: #f0f0f0;
  color: black;
  width: 200px;  		
  font-family: Tahoma, Geneva, sans-serif;		
  font-size: 20px;
}


/* Add some padding inside the card container */
.card_container_top {
  padding: 4px 16px;
  background-color: #154360;
  color: white;
}

div.wrap {
	word-wrap: break-word;
}
	
	</style>
		
<script>
	$(document).ready(function(){
	 <!--  $("#linebtn").click(function(){
		$("#myChart1").toggle();
	  });
	  $("#barbtn").click(function(){
		$("#myChart2").toggle();
	  }); -->
		  
	$("#myInput1AR").on("keyup", function() {
		var value = $(this).val().toLowerCase();
		$("#myTableAPPENGGReport tr").filter(function() {
		  $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1)
		});
	  });

	$("#tabs").tabs();	  
	  
	});		
	
</script>	

  </head> 
  <body> 
    <!--<canvas id="myChart" style="width:100%;max-width:600px"></canvas> -->	
		 
<div class="container">
			
<div class="row m-2">
	<div class="col-sm-12">
		<center><font color="#006699"><h5><b>MCC Vehicle Compare Report</b></h5></font></center>

		<!-- <hr style="height:5px;border-width:0;color:gray;background-color:gray"></hr> -->
	</div>
</div>	
	    
<!--  <PreviousCompare>
<PVehNo>55551233R</PVehNo>
<PVehRev>L</PVehRev>
<PVehSeq>2</PVehSeq>
<PVehDesc>407G GOLD SFCDCR33CBC85B6M5</PVehDesc>
<PVehDrAr>DR3</PVehDrAr>
<PRevRule>ERC release and above</PRevRule>
<PClosureRule>BOMViewClosureRuleERC</PClosureRule>
<PTotalMod>185</PTotalMod>
<PPresentMod>185</PPresentMod>
<PNotPresentMod>0</PNotPresentMod>
<PAboveMod>182</PAboveMod>
<PBelowMod>3</PBelowMod>
<PMaxPercent>98.38</PMaxPercent>
<PAllPercent>100.00</PAllPercent>
<PTimeStamp>01_Sep_2024_21_31_06</PTimeStamp>
</PreviousCompare> -->

<div class="row">   
  
	<div class="col-sm-6"><b>LATEST RELEASED VEHICLE</b></div>
  	<div class="col-sm-6"><b>PREVIOUS RELEASED VEHICLE</b></div>

	
</div>
  
<div class="row">   
  
  		
	<div class="col-sm-6">	
		<center>
		<div class="veh_label_lat">
			
				
				<xsl:for-each select="VehCompare/LatestCompare">				

					<div class="row">	
						<!-- <div class="col-sm-6" style="text-align:right;">Vehicle Number : </div> -->
						<div class="col-sm-12">
							
							<xsl:value-of select="LVehNo"/>,<xsl:value-of select="LVehRev"/>,<xsl:value-of select="LVehSeq"/>
							[ <xsl:value-of select="LVehDesc"/> ]
							
						</div>
					</div>				
					<!-- <div class="row">	
						<div class="col-sm-6" style="text-align:right;">Vehicle Description : </div>
						<div class="col-sm-6"  style="text-align:left;"><h4><b><xsl:value-of select="VehDesc"/></b></h4></div>
					</div> -->
				
					<div class="row">							
						<div class="col-sm-12">
							<xsl:value-of select="LVehDrAr"/>							
						</div>
					</div>					
				</xsl:for-each>					
						
		</div>
		</center>			
	</div>
		
	
	<div class="col-sm-6">	
		<center>
		<div class="veh_label_pre">
			
				
				<xsl:for-each select="VehCompare/PreviousCompare">				

					<div class="row">	
						<!-- <div class="col-sm-6" style="text-align:right;">Vehicle Number : </div> -->
						<div class="col-sm-12">
							
							<xsl:value-of select="PVehNo"/>,<xsl:value-of select="PVehRev"/>,<xsl:value-of select="PVehSeq"/>
							[ <xsl:value-of select="PVehDesc"/> ]
							
						</div>
					</div>				
					<!-- <div class="row">	
						<div class="col-sm-6" style="text-align:right;">Vehicle Description : </div>
						<div class="col-sm-6"  style="text-align:left;"><h4><b><xsl:value-of select="VehDesc"/></b></h4></div>
					</div> -->
				
					<div class="row">							
						<div class="col-sm-12">
							<xsl:value-of select="PVehDrAr"/>							
						</div>
					</div>					
				</xsl:for-each>					
							
		</div>
		</center>			
	</div>
	

	
</div>	
		
		<div class="grey_div">
		
			<div class="row"> 
			
			
			<xsl:for-each select="VehCompare/LatestCompare">
				
				<!-- <div class="col-sm-2"></div> -->
					<div class="col-sm-3">
				
						<div class="card">
						<div class="card_container">
							
						<!-- <xsl:for-each select="VehCompliance/ComplianceStatus"> -->
						
						<div class="row m-3">
								<div class="col-sm-12" style="text-align:center;">
									<!-- <h5><b>Compliance Score : [ As per Max-DR (DR4/DR5) ]</b></h5> -->
									<b>DR4 and Above<br></br>Vehicle Compliance Score</b>
								</div>
							</div>				

							<div class="row">	
								<div class="col-sm-8" style="text-align:right;">Total Submodules: </div>
								<div class="col-sm-4"  style="text-align:left;"><b><xsl:value-of select="LTotalMod"/></b></div>
							</div>
							<div class="row">	
								<div class="col-sm-8" style="text-align:right;">No. of Max-DR4: </div>
								<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="LAboveMod"/></b></h8></div>
							</div>
							<div class="row">	
								<div class="col-sm-8" style="text-align:right;">No. of Below DR4: </div>
								<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="LBelowMod"/></b></h8></div>
							</div>
							
							<div class="row">	
								<div class="col-sm-12" style="text-align:center;">Compliance Score : </div>								
							</div>
							<div class="row">								
								<div class="col-sm-12"  style="text-align:center;">
									<h4><font color="#006699"><b><xsl:value-of select="LMaxPercent"/> % </b></font></h4></div>
							</div>

							<!-- </xsl:for-each>					 -->
							</div>				
						</div>
				
					</div>
					<div class="col-sm-3">
					
						<div class="card">
						<div class="card_container">
							
						<!-- <xsl:for-each select="VehCompliance/ComplianceStatus"> -->
						
							<div class="row m-3">
								<div class="col-sm-12" style="text-align:center;">
									<b>All DR-Status<br></br>Vehicle Compliance Score</b>
								</div>
							</div>	
						
							<div class="row">	
								<div class="col-sm-8" style="text-align:right;">Total Submodules: </div>
								<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="LTotalMod"/></b></h8></div>
							</div>
							<div class="row">	
								<div class="col-sm-8" style="text-align:right;">No. of All DR-Status: </div>
								<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="LPresentMod"/></b></h8></div>
							</div>
											<div class="row">	
								<div class="col-sm-8" style="text-align:right;">No. of Not Present: </div>
								<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="LNotPresentMod"/></b></h8></div>
							</div>
							
							<div class="row">	
								<div class="col-sm-12" style="text-align:center;">Compliance Score: </div>
							</div>
							
							<div class="row">	
								<div class="col-sm-12"  style="text-align:center;">
									<h4><font color="#006699"><b><xsl:value-of select="LAllPercent"/> % </b></font></h4></div>
							</div>

							<!-- </xsl:for-each>					 -->
							</div>				
						</div>
					
					</div>
					
				</xsl:for-each>	
						
				<xsl:for-each select="VehCompare/PreviousCompare">
			
					<!-- <div class="col-sm-2"></div> -->
					<div class="col-sm-3">
					
							<div class="card">
							<div class="card_container">
								
							<!-- <xsl:for-each select="VehCompliance/ComplianceStatus"> -->
							
								<div class="row m-3">
									<div class="col-sm-12" style="text-align:center;">
										<!-- <h5><b>Compliance Score : [ As per Max-DR (DR4/DR5) ]</b></h5> -->
										<b>DR4 and Above<br></br>Vehicle Compliance Score</b>
									</div>
								</div>				

								<div class="row">	
									<div class="col-sm-8" style="text-align:right;">Total Submodules: </div>
									<div class="col-sm-4"  style="text-align:left;"><b><xsl:value-of select="PTotalMod"/></b></div>
								</div>
								<div class="row">	
									<div class="col-sm-8" style="text-align:right;">No. of Max-DR4: </div>
									<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="PAboveMod"/></b></h8></div>
								</div>
								<div class="row">	
									<div class="col-sm-8" style="text-align:right;">No. of Below DR4: </div>
									<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="PBelowMod"/></b></h8></div>
								</div>
								
								<div class="row">	
									<div class="col-sm-12" style="text-align:center;">Compliance Score : </div>								
								</div>
								<div class="row">								
									<div class="col-sm-12"  style="text-align:center;">
										<h4><font color="#006699"><b><xsl:value-of select="PMaxPercent"/> % </b></font></h4></div>
								</div>

								<!-- </xsl:for-each>					 -->
								</div>				
							</div>
					
					</div>
					<div class="col-sm-3">
						
							<div class="card">
							<div class="card_container">
								
							<!-- <xsl:for-each select="VehCompliance/ComplianceStatus"> -->
							
								<div class="row m-3">
									<div class="col-sm-12" style="text-align:center;">
										<b>All DR-Status<br></br>Vehicle Compliance Score</b>
									</div>
								</div>	
							
								<div class="row">	
									<div class="col-sm-8" style="text-align:right;">Total Submodules: </div>
									<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="PTotalMod"/></b></h8></div>
								</div>
								<div class="row">	
									<div class="col-sm-8" style="text-align:right;">No. of All DR-Status: </div>
									<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="PPresentMod"/></b></h8></div>
								</div>
												<div class="row">	
									<div class="col-sm-8" style="text-align:right;">No. of Not Present: </div>
									<div class="col-sm-4"  style="text-align:left;"><h8><b><xsl:value-of select="PNotPresentMod"/></b></h8></div>
								</div>
								
								<div class="row">	
									<div class="col-sm-12" style="text-align:center;">Compliance Score: </div>
								</div>
								
								<div class="row">	
									<div class="col-sm-12"  style="text-align:center;">
										<h4><font color="#006699"><b><xsl:value-of select="PAllPercent"/> % </b></font></h4></div>
								</div>

								<!-- </xsl:for-each>					 -->
								</div>				
							</div>
						
					</div>	

				</xsl:for-each>						

			</div>
			
			<div class="row">						
				
				
				<xsl:for-each select="VehCompare/LatestCompare">
				
					<div class="col-sm-2">
						<div class="deep_green">
						DR4 and above : <b><xsl:value-of select="LAboveMod"/></b>
						</div>	
					</div>
					<div class="col-sm-2">
						<div class="light_green">
						Below DR4 : <b><xsl:value-of select="LBelowMod"/></b>
						</div>
					</div>
					<div class="col-sm-2">
						<div class="yellow">
						Exclusive Submodules : <b><xsl:value-of select="LNotPresentMod"/></b>
						</div>
					</div>
					
				</xsl:for-each>
								
				<xsl:for-each select="VehCompare/PreviousCompare">
				
					<div class="col-sm-2">
						<div class="deep_green">
						DR4 and above : <b><xsl:value-of select="PAboveMod"/></b>
						</div>	
					</div>
					<div class="col-sm-2">
						<div class="light_green">
						Below DR4 : <b><xsl:value-of select="PBelowMod"/></b>
						</div>
					</div>
					<div class="col-sm-2">
						<div class="yellow">
						Exclusive Submodules : <b><xsl:value-of select="PNotPresentMod"/></b>
						</div>
					</div>
					
				</xsl:for-each>
				
			</div>	

		</div>
		
</div>
<div class="container-fluid">
				 		 
	<div class="row">			
			
			<div class="col-sm-12">	
					<center>
						Search : <input class="m-2" id="myInput1AR" type="text" placeholder="Type here to search in below table.." style="width: 300px;"></input>
					
					<table>	
							<!-- 
							<tr bgcolor="#006699">
							  <td colspan="13" bgcolor="#D6D6D6"><center><b>Vehicle Data</b></center></td>
							  <th></th>
							  <td colspan="4" bgcolor="#94DFFF"><center><b>MCC Library Data</b></center></td>
							<th><font color="#006699"><b>DR-Status<br></br>in MCC-Library</b></font></th>	
								<th><font color="#006699"><b>Revision<br></br>in MCC-Library</b></font></th>	
								<th><font color="#006699"><b>Sequence<br></br>in MCC-Library</b></font></th>
								<th><font color="#006699"><b>Max DR-Status<br></br>in MCC-Library</b></font></th>											
								<th></th>								 
							</tr>
							 --> 						 
							 
							 <tr bgcolor="#006699">
							 <th></th>
							 <th></th>
							 								
							<xsl:for-each select="VehCompare/LatestCompare">
								<td colspan="4" bgcolor="#006699">
									<center><b><font color="white">
										LATEST RELEASED VEHICLE<br></br>
										<xsl:value-of select="LVehNo"/>,<xsl:value-of select="LVehRev"/>,<xsl:value-of select="LVehSeq"/>
										<br></br><xsl:value-of select="LVehDrAr"/>	
									</font></b></center>
								</td>	
							</xsl:for-each>	
							 
							 							  						  
							 <th></th>
							  
							<xsl:for-each select="VehCompare/PreviousCompare">
								<td colspan="4" bgcolor="#666868">
									<center><b><font color="white">
										PREVIOUS RELEASED VEHICLE<br></br>
										<xsl:value-of select="PVehNo"/>,<xsl:value-of select="PVehRev"/>,<xsl:value-of select="PVehSeq"/>
										<br></br><xsl:value-of select="PVehDrAr"/>	
									</font></b></center>
								</td>
							</xsl:for-each>							  
							  
							  <th></th>
							  
							  <td colspan="9" bgcolor="#94DFFF"><center><b>Vehicle Data</b></center></td>
							  <td colspan="3" bgcolor="#94DFFF"><center><b>MCC Library Data</b></center></td>
							  <th></th>
							  														 
							</tr>						
														
							<!-- <ChildDetails>
							<PartNo>2647F5B0240001</PartNo>
							<PartRev>NR</PartRev>
							<PartSeq>1</PartSeq>
							<PartDesc>WHEEL MOUNTING</PartDesc>
							<PartAddr>F5B02</PartAddr>
							<PartProd>ILCV</PartProd>
							<PartPlat>ILCV</PartPlat>
							<PartProj>2647</PartProj>
							<PartDesGrp>40</PartDesGrp>
							<PartDrAr>DR4</PartDrAr>
							<PartType>Module</PartType>
							<LatestPartQty>4</LatestPartQty>
							<PreviousPartQty>4</PreviousPartQty>
							<PartUOM>each</PartUOM>
							<PartStatus>Same</PartStatus>
							<PartData>55551233R-M-2-DR4 / 55551233R-L-2-DR3</PartData>
							</ChildDetails> -->						
							
														
							<tr bgcolor="#006699">
							  <th><b>Diff</b></th>
							   <th></th>
							  <th><b>Module No.</b></th>
							  <th><b>Rev</b></th>
							  <th><b>Seq</b></th>
							  <th><b> Qty</b></th>
							  <th></th>
							  <th><b>Module No.</b></th>
							  <th><b>Rev</b></th>
							  <th><b>Seq</b></th>
							  <th><b>Qty</b></th>
							  <th></th>
							  <th word-wrap="break-word"><b>Module Description</b></th>	
							  <th><b>Module<br></br>Address</b></th>							   
							  <th><b>Product Line</b></th>
							  <th><b>Platform</b></th>
							  <th><b>Project<br></br>Code</b></th>
							  <th><b>Design<br></br>Group</b></th>
							  <th><b>DR-Status</b></th>
							  <th><b>Part Type</b></th>							 
							  <th><b>UOM</b></th>
							 
							  <th><b>In<br></br>MCC-Lib?</b></th>	
							  <th><b>Veh<br></br>Freq</b></th>							 
							  <th><b>Max<br></br>DR</b></th>
							  <th style="width: 250px;"><b>In-Vehicle-Filter</b></th>
							</tr>
							
<!-- 							<tr bgcolor="#006699">
							  <th><b>Module No.</b></th>
							  <th><b>Rev</b></th>
							  <th><b>Seq</b></th>
							  <th word-wrap="break-word"><b>Module Description</b></th>	
							  <th><b>Module<br></br>Address</b></th>							   
							  <th><b>Product Line</b></th>
							  <th><b>Platform</b></th>
							  <th><b>Project<br></br>Code</b></th>
							  <th><b>Design<br></br>Group</b></th>
							  <th><b>DR-Status</b></th>
							  <th><b>Part Type</b></th>
							  <th><b>Latest Qty</b></th>
							  <th><b>Previos Qty</b></th>
							  <th><b>UOM</b></th>
							  <th><b>A/D/U/Same Status</b></th>
							  <th style="width: 250px;"><b>In Vehicle Filter</b></th>
							</tr> -->
							
							<tbody id="myTableAPPENGGReport">							
														
								<xsl:for-each select="VehCompare/ChildDetails">							
								
									<tr>									   			   
									   									   
										<xsl:if test="PartStatus = 'Added'">
										
										<td bgcolor="#76D7C4" align="center"><font color="green"><xsl:value-of select="PartStatus"/></font></td>
										<td bgcolor="#AED6F1"></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartNo"/></td>
										   <td bgcolor="#76D7C4" align="center"><xsl:value-of select="PartRev"/></td>
										   <td bgcolor="#76D7C4" align="center"><xsl:value-of select="PartSeq"/></td>
										   <td bgcolor="#76D7C4" align="center"><xsl:value-of select="LatestPartQty"/></td>
										   <td bgcolor="#AED6F1"></td>
										   <td></td>
										   <td></td>
										   <td></td>
										   <td></td>
										   <td bgcolor="#AED6F1"></td>
										   
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartDesc"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartAddr"/></td>								   
										   <td bgcolor="#76D7C4"><b><xsl:value-of select="PartProd"/></b></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartPlat"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartProj"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartDesGrp"/></td>									   
										   <td bgcolor="#76D7C4" align="center"><xsl:value-of select="PartDrAr"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartType"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartUOM"/></td>
										   
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartInLib"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartFreq"/></td>
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartMaxDRAR"/></td>	
										     
										   <td bgcolor="#76D7C4"><xsl:value-of select="PartData"/></td>	
										
										</xsl:if>	
										
									</tr>
									
								</xsl:for-each>
																
								<xsl:for-each select="VehCompare/ChildDetails">							
								
									<tr>
										
										<xsl:if test="PartStatus = 'Deleted'">
											
										   <td bgcolor="#FEB9B9" align="center"><font color="red"><xsl:value-of select="PartStatus"/></font></td>
										   <td bgcolor="#AED6F1"></td>
										   <td></td>
										   <td></td>
										   <td></td>
										   <td></td>
										   <td bgcolor="#AED6F1"></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartNo"/></td>
										   <td bgcolor="#FEB9B9" align="center"><xsl:value-of select="PartRev"/></td>
										   <td bgcolor="#FEB9B9" align="center"><xsl:value-of select="PartSeq"/></td>
										   <td bgcolor="#FEB9B9" align="center"><xsl:value-of select="PreviousPartQty"/></td>	
										   <td bgcolor="#AED6F1"></td>
										   
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartDesc"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartAddr"/></td>								   
										   <td bgcolor="#FEB9B9"><b><xsl:value-of select="PartProd"/></b></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartPlat"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartProj"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartDesGrp"/></td>									   
										   <td bgcolor="#FEB9B9" align="center"><xsl:value-of select="PartDrAr"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartType"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartUOM"/></td>
										   
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartInLib"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartFreq"/></td>
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartMaxDRAR"/></td>									   
										     
										   <td bgcolor="#FEB9B9"><xsl:value-of select="PartData"/></td>	

										</xsl:if>	
										
									</tr>
									
								</xsl:for-each>
								
								
								<xsl:for-each select="VehCompare/ChildDetails">							
								
									<tr>   
																				
										<xsl:if test="PartStatus = 'Updated'">
										
											 <td bgcolor="#FDFAD2" align="center"><font color="C48F01"><xsl:value-of select="PartStatus"/></font></td>
											 <td bgcolor="#AED6F1"></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartNo"/></td>
										   <td bgcolor="#FDFAD2" align="center"><xsl:value-of select="PartRev"/></td>
										   <td bgcolor="#FDFAD2" align="center"><xsl:value-of select="PartSeq"/></td>
										   <td bgcolor="#FDEED2" align="center"><font color="C48F01"><xsl:value-of select="LatestPartQty"/></font></td>
										   <td bgcolor="#AED6F1"></td>
										   
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartNo"/></td>
										   <td bgcolor="#FDFAD2" align="center"><xsl:value-of select="PartRev"/></td>
										   <td bgcolor="#FDFAD2" align="center"><xsl:value-of select="PartSeq"/></td>
										   <td bgcolor="#FDEED2" align="center"><font color="C48F01"><xsl:value-of select="PreviousPartQty"/></font></td>	
										   <td bgcolor="#AED6F1"></td>
											
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartDesc"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartAddr"/></td>								   
										   <td bgcolor="#FDFAD2"><b><xsl:value-of select="PartProd"/></b></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartPlat"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartProj"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartDesGrp"/></td>									   
										   <td bgcolor="#FDFAD2" align="center"><xsl:value-of select="PartDrAr"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartType"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartUOM"/></td>
										   
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartInLib"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartFreq"/></td>
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartMaxDRAR"/></td>	
										    
										   <td bgcolor="#FDFAD2"><xsl:value-of select="PartData"/></td>
										 										 										 										 
										 </xsl:if>	
																											  
									</tr>
									
								</xsl:for-each>						

								
								<xsl:for-each select="VehCompare/ChildDetails">							
								
									<tr>
									
										<xsl:if test="PartStatus = 'Same'">
										 
										    <td bgcolor="white" align="center"><font color="black"><xsl:value-of select="PartStatus"/></font></td>
											<td bgcolor="#AED6F1"></td>
										   <td><xsl:value-of select="PartNo"/></td>
										   <td align="center"><xsl:value-of select="PartRev"/></td>
										   <td align="center"><xsl:value-of select="PartSeq"/></td>
										   <td align="center"><xsl:value-of select="LatestPartQty"/></td>
										   <td bgcolor="#AED6F1"></td>
										   
										   <td><xsl:value-of select="PartNo"/></td>
										   <td align="center"><xsl:value-of select="PartRev"/></td>
										   <td align="center"><xsl:value-of select="PartSeq"/></td>
										   <td align="center"><xsl:value-of select="PreviousPartQty"/></td>
										   <td bgcolor="#AED6F1"></td>
											
										   <td><xsl:value-of select="PartDesc"/></td>
										   <td><xsl:value-of select="PartAddr"/></td>								   
										   <td><b><xsl:value-of select="PartProd"/></b></td>
										   <td><xsl:value-of select="PartPlat"/></td>
										   <td><xsl:value-of select="PartProj"/></td>
										   <td><xsl:value-of select="PartDesGrp"/></td>									   
										   <td align="center"><xsl:value-of select="PartDrAr"/></td>
										   <td><xsl:value-of select="PartType"/></td>	
										   <td><xsl:value-of select="PartUOM"/></td>
										   
										   <td><xsl:value-of select="PartInLib"/></td>
										   <td><xsl:value-of select="PartFreq"/></td>
										   <td><xsl:value-of select="PartMaxDRAR"/></td>	
										    
										   <td><xsl:value-of select="PartData"/></td>
																	 
										 									 
										 
										 </xsl:if>
										
										
																											  
									</tr>
									
								</xsl:for-each>
								
								
							</tbody>
						</table>
					</center>
			</div>
		</div>	
<br></br>

<hr style="height:5px;border-width:0;color:gray;background-color:gray"></hr>

		<center>
		<font size="2px">Copyright@2024 (PLM ERC Team)</font>
		</center>
		
</div>
	
<script>

	const xValues = ["CLUTCH CONTROL SYSTEM", "ACCELERATOR PEDAL ASSY", "REAR RADAR MODULE", "ENGINE MOUNT ASSY", "REAR BUMPER"];
	const yValues = [29, 31, 44, 24, 11];
	const barColors = [
	  "#b91d47",
	  "#00aba9",
	  "#2b5797",
	  "#e8c3b9",
	  "#1e7145"
	];

	new Chart("myChart", {
	  type: "pie",
	  data: {
		labels: xValues,
		datasets: [{
		  backgroundColor: barColors,
		  data: yValues
		}]
	  },
	  options: {
		title: {
		  display: true,
		  text: "Test Pie Chart- SAP BOM Report"
		}
	  }
	});

	
	const barColors1 = [
	  "#b91d47",
	  "#00aba9",
	  "#2b5797",
	  "#e8c3b9",
	  "#1e7145"
	];
	
	console.log('11111111111111111');
	
	var xValues2 = [ 
	<xsl:for-each select="ALTROZ">	
		<xsl:for-each select="DateRange">
			<xsl:for-each select="DateData">
				<xsl:choose>
					<xsl:when test = "position() != last()">
						<xsl:text>"</xsl:text>
						<xsl:value-of select="@Date"/>
						<xsl:text>"</xsl:text>
						<xsl:text>,</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text>"</xsl:text>
						<!-- <xsl:value-of select="@moduleName"/> -->
						<xsl:value-of select="@Date"/>
						<xsl:text>"</xsl:text>					
					</xsl:otherwise>
				</xsl:choose>
			</xsl:for-each>
		</xsl:for-each>	
		
	</xsl:for-each>
	];
	
	console.log('xValues2 : ' + xValues2);
	
	const yValues2 = [ 
	<xsl:for-each select="ModuleReport/MD">
	<xsl:choose>
		<xsl:when test = "position() != last()">
			<xsl:value-of select="@modulecount"/>
			<xsl:text>,</xsl:text>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="@modulecount"/>
			
		</xsl:otherwise>
	</xsl:choose>	
	</xsl:for-each>
	];
	
	const barColors2 = [ 
	<xsl:for-each select="ModuleReport/MD">
	<xsl:choose>
		<xsl:when test = "position() != last()">
			<xsl:choose>
				<xsl:when test = "position() mod 2 = 0">
					"#b91d47",
				</xsl:when>
				<xsl:otherwise>
					"#1e7145",			
				</xsl:otherwise>
			</xsl:choose>
		  
		</xsl:when>
		<xsl:otherwise>
			"#b91d47"		
		</xsl:otherwise>
	</xsl:choose>	
	</xsl:for-each>
	];

<!-- 	new Chart("myChart2", {
	  type: "bar",
	  data: {
		labels: xValues2,
		datasets: [{
		  backgroundColor: ['red'],
		  data: yValues2
		}]
	  },
	  options: {
		title: {
		  display: true,
		  text: "Test Bar Chart- SAP BOM Report"
		}
	  }
	});	 -->
	
	
	
	var xValues1 = [ 
	<xsl:for-each select="ModuleReport/MD">
	
	<xsl:choose>
		<xsl:when test = "position() != last()">
			<xsl:value-of select="@modulecount"/>
			<xsl:text>,</xsl:text>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="@modulecount"/>
			
		</xsl:otherwise>
	</xsl:choose>
	
	</xsl:for-each>
	];
	
	var yValues1 = [ 
	<xsl:for-each select="ModuleReport/MD">
	<xsl:choose>
		<xsl:when test = "position() != last()">
			<xsl:value-of select="@modulecount"/>
			<xsl:text>,</xsl:text>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="@modulecount"/>
			
		</xsl:otherwise>
	</xsl:choose>	
	</xsl:for-each>
	];
	
	var yValues22 = [ 
	
	<xsl:for-each select="ModuleReport/MD">	
	
		<xsl:if test="position() = 6">	
			<xsl:choose>
				<xsl:when test = "position() != last()">
					<xsl:value-of select="@modulecount"/>
					<xsl:text>,</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="@modulecount"/>
					
				</xsl:otherwise>
			</xsl:choose>	
		</xsl:if>
			
	</xsl:for-each>
	];
	
	console.log('yValues22 : ' + yValues22);
	
	
	var LabelArrayALTROZ1 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 1">						
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ1 = LabelArrayALTROZ1[0];
	console.log('LabelStrALTROZ1 : ' + LabelStrALTROZ1);
	
	var LabelArrayALTROZ2 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 2">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ2 = LabelArrayALTROZ2[0];
	console.log('LabelStrALTROZ2 : ' + LabelStrALTROZ2);
	
	var LabelArrayALTROZ3 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 3">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ3 = LabelArrayALTROZ3[0];
	console.log('LabelStrALTROZ3 : ' + LabelStrALTROZ3);
	
	var LabelArrayALTROZ4 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 4">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ4 = LabelArrayALTROZ4[0];
	console.log('LabelStrALTROZ4 : ' + LabelStrALTROZ4);
	
	var LabelArrayALTROZ5 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 5">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ5 = LabelArrayALTROZ5[0];
	console.log('LabelStrALTROZ5 : ' + LabelStrALTROZ5);
	
	var LabelArrayALTROZ6 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 6">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ6 = LabelArrayALTROZ6[0];
	console.log('LabelStrALTROZ6 : ' + LabelStrALTROZ6);
	
	var LabelArrayALTROZ7 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 7">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ7 = LabelArrayALTROZ7[0];
	console.log('LabelStrALTROZ7 : ' + LabelStrALTROZ7);
	
	var LabelArrayALTROZ8 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 8">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ8 = LabelArrayALTROZ8[0];
	console.log('LabelStrALTROZ8 : ' + LabelStrALTROZ8);
	
	var LabelArrayALTROZ9 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 9">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ9 = LabelArrayALTROZ9[0];
	console.log('LabelStrALTROZ9 : ' + LabelStrALTROZ9);
	
	var LabelArrayALTROZ10 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 10">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrALTROZ10 = LabelArrayALTROZ10[0];
	console.log('LabelStrALTROZ10 : ' + LabelStrALTROZ10);
	
	
	var LabelArrayHARRIER1 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 1">						
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER1 = LabelArrayHARRIER1[0];
	console.log('LabelStrHARRIER1 : ' + LabelStrHARRIER1);
	
	var LabelArrayHARRIER2 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 2">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER2 = LabelArrayHARRIER2[0];
	console.log('LabelStrHARRIER2 : ' + LabelStrHARRIER2);
	
	var LabelArrayHARRIER3 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 3">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER3 = LabelArrayHARRIER3[0];
	console.log('LabelStrHARRIER3 : ' + LabelStrHARRIER3);
	
	var LabelArrayHARRIER4 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 4">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER4 = LabelArrayHARRIER4[0];
	console.log('LabelStrHARRIER4 : ' + LabelStrHARRIER4);
	
	var LabelArrayHARRIER5 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 5">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER5 = LabelArrayHARRIER5[0];
	console.log('LabelStrHARRIER5 : ' + LabelStrHARRIER5);
	
	var LabelArrayHARRIER6 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 6">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER6 = LabelArrayHARRIER6[0];
	console.log('LabelStrHARRIER6 : ' + LabelStrHARRIER6);
	
	var LabelArrayHARRIER7 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 7">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER7 = LabelArrayHARRIER7[0];
	console.log('LabelStrHARRIER7 : ' + LabelStrHARRIER7);
	
	var LabelArrayHARRIER8 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 8">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER8 = LabelArrayHARRIER8[0];
	console.log('LabelStrHARRIER8 : ' + LabelStrHARRIER8);
	
	var LabelArrayHARRIER9 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 9">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER9 = LabelArrayHARRIER9[0];
	console.log('LabelStrHARRIER9 : ' + LabelStrHARRIER9);
	
	var LabelArrayHARRIER10 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 10">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrHARRIER10 = LabelArrayHARRIER10[0];
	console.log('LabelStrHARRIER10 : ' + LabelStrHARRIER10);
	
	
		var LabelArrayPUNCH1 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 1">						
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH1 = LabelArrayPUNCH1[0];
	console.log('LabelStrPUNCH1 : ' + LabelStrPUNCH1);
	
	var LabelArrayPUNCH2 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 2">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH2 = LabelArrayPUNCH2[0];
	console.log('LabelStrPUNCH2 : ' + LabelStrPUNCH2);
	
	var LabelArrayPUNCH3 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 3">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH3 = LabelArrayPUNCH3[0];
	console.log('LabelStrPUNCH3 : ' + LabelStrPUNCH3);
	
	var LabelArrayPUNCH4 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 4">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH4 = LabelArrayPUNCH4[0];
	console.log('LabelStrPUNCH4 : ' + LabelStrPUNCH4);
	
	var LabelArrayPUNCH5 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 5">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH5 = LabelArrayPUNCH5[0];
	console.log('LabelStrPUNCH5 : ' + LabelStrPUNCH5);
	
	var LabelArrayPUNCH6 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 6">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH6 = LabelArrayPUNCH6[0];
	console.log('LabelStrPUNCH6 : ' + LabelStrPUNCH6);
	
	var LabelArrayPUNCH7 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 7">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH7 = LabelArrayPUNCH7[0];
	console.log('LabelStrPUNCH7 : ' + LabelStrPUNCH7);
	
	var LabelArrayPUNCH8 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 8">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH8 = LabelArrayPUNCH8[0];
	console.log('LabelStrPUNCH8 : ' + LabelStrPUNCH8);
	
	var LabelArrayPUNCH9 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 9">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH9 = LabelArrayPUNCH9[0];
	console.log('LabelStrPUNCH9 : ' + LabelStrPUNCH9);
	
	var LabelArrayPUNCH10 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 10">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrPUNCH10 = LabelArrayPUNCH10[0];
	console.log('LabelStrPUNCH10 : ' + LabelStrPUNCH10);	
	
	
		var LabelArraySAFARI1 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 1">						
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI1 = LabelArraySAFARI1[0];
	console.log('LabelStrSAFARI1 : ' + LabelStrSAFARI1);
	
	var LabelArraySAFARI2 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 2">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI2 = LabelArraySAFARI2[0];
	console.log('LabelStrSAFARI2 : ' + LabelStrSAFARI2);
	
	var LabelArraySAFARI3 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 3">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI3 = LabelArraySAFARI3[0];
	console.log('LabelStrSAFARI3 : ' + LabelStrSAFARI3);
	
	var LabelArraySAFARI4 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 4">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI4 = LabelArraySAFARI4[0];
	console.log('LabelStrSAFARI4 : ' + LabelStrSAFARI4);
	
	var LabelArraySAFARI5 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 5">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI5 = LabelArraySAFARI5[0];
	console.log('LabelStrSAFARI5 : ' + LabelStrSAFARI5);
	
	var LabelArraySAFARI6 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 6">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI6 = LabelArraySAFARI6[0];
	console.log('LabelStrSAFARI6 : ' + LabelStrSAFARI6);
	
	var LabelArraySAFARI7 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 7">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI7 = LabelArraySAFARI7[0];
	console.log('LabelStrSAFARI7 : ' + LabelStrSAFARI7);
	
	var LabelArraySAFARI8 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 8">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI8 = LabelArraySAFARI8[0];
	console.log('LabelStrSAFARI8 : ' + LabelStrSAFARI8);
	
	var LabelArraySAFARI9 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 9">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI9 = LabelArraySAFARI9[0];
	console.log('LabelStrSAFARI9 : ' + LabelStrSAFARI9);
	
	var LabelArraySAFARI10 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">		
		<xsl:if test="position() = 10">
					<xsl:text>'</xsl:text>	
					<xsl:text>[</xsl:text>					
					<xsl:value-of select="@ModuleAdd"/>
					<xsl:text>:</xsl:text>						
					<xsl:value-of select="@ModuleName"/>
					<xsl:text>]</xsl:text>	
					<xsl:text>'</xsl:text>										
					</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];	
	const LabelStrSAFARI10 = LabelArraySAFARI10[0];
	console.log('LabelStrSAFARI10 : ' + LabelStrSAFARI10);
	
	var custyALTROZ1 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 1">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ1 : ' + custyALTROZ1);	
	var colorALTROZ1 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyALTROZ2 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 2">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ2 : ' + custyALTROZ2);	
	var colorALTROZ2 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyALTROZ3 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 3">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ3 : ' + custyALTROZ3);	
	var colorALTROZ3 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyALTROZ4 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 4">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ4 : ' + custyALTROZ4);	
	var colorALTROZ4 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();	
	
	var custyALTROZ5 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 5">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ5 : ' + custyALTROZ5);	
	var colorALTROZ5 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyALTROZ6 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 6">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ6 : ' + custyALTROZ6);	
	var colorALTROZ6 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyALTROZ7 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 7">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ7 : ' + custyALTROZ7);	
	var colorALTROZ7 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyALTROZ8 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 8">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ8 : ' + custyALTROZ8);	
	var colorALTROZ8 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();

	var custyALTROZ9 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 9">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ9 : ' + custyALTROZ9);	
	var colorALTROZ9 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();	
	
	var custyALTROZ10 = [ 	
	<xsl:for-each select="ALTROZ">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 10">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyALTROZ10 : ' + custyALTROZ8);	
	var colorALTROZ10 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	
	var custyHARRIER1 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 1">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER1 : ' + custyHARRIER1);
	var colorHARRIER1 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER2 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 2">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER2 : ' + custyHARRIER2);	
	var colorHARRIER2 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER3 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 3">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER3 : ' + custyHARRIER3);	
	var colorHARRIER3 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER4 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 4">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER4 : ' + custyHARRIER4);	
	var colorHARRIER4 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	
	var custyHARRIER5 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 5">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER5 : ' + custyHARRIER5);
	var colorHARRIER5 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER6 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 6">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER6 : ' + custyHARRIER6);	
	var colorHARRIER6 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER7 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 7">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER7 : ' + custyHARRIER7);	
	var colorHARRIER7 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER8 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 8">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER8 : ' + custyHARRIER8);	
	var colorHARRIER8 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	
	var custyHARRIER9 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 9">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER9 : ' + custyHARRIER9);	
	var colorHARRIER9 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyHARRIER10 = [ 	
	<xsl:for-each select="HARRIER">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 10">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyHARRIER10 : ' + custyHARRIER10);	
	var colorHARRIER10 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();

    var custyPUNCH1 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 1">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH1 : ' + custyPUNCH1);
	var colorPUNCH1 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH2 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 2">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH2 : ' + custyPUNCH2);	
	var colorPUNCH2 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH3 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 3">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH3 : ' + custyPUNCH3);	
	var colorPUNCH3 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH4 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 4">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH4 : ' + custyPUNCH4);	
	var colorPUNCH4 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		
	var custyPUNCH5 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 5">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH5 : ' + custyPUNCH5);
	var colorPUNCH5 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH6 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 6">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH6 : ' + custyPUNCH6);	
	var colorPUNCH6 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH7 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 7">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH7 : ' + custyPUNCH7);	
	var colorPUNCH7 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH8 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 8">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH8 : ' + custyPUNCH8);	
	var colorPUNCH8 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH9 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 9">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH9 : ' + custyPUNCH9);	
	var colorPUNCH9 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custyPUNCH10 = [ 	
	<xsl:for-each select="PUNCH">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 10">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custyPUNCH10 : ' + custyPUNCH10);	
	var colorPUNCH10 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		
	var custySAFARI1 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 1">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI1 : ' + custySAFARI1);
	var colorSAFARI1 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI2 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 2">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI2 : ' + custySAFARI2);	
	var colorSAFARI2 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI3 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 3">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI3 : ' + custySAFARI3);	
	var colorSAFARI3 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI4 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 4">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI4 : ' + custySAFARI4);	
	var colorSAFARI4 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI5 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 5">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI5 : ' + custySAFARI5);
	var colorSAFARI5 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI6 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 6">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI6 : ' + custySAFARI6);	
	var colorSAFARI6 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI7 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 7">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI7 : ' + custySAFARI7);	
	var colorSAFARI7 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI8 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 8">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI8 : ' + custySAFARI8);	
	var colorSAFARI8 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI9 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 9">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI9 : ' + custySAFARI9);	
	var colorSAFARI9 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
	
	var custySAFARI10 = [ 	
	<xsl:for-each select="SAFARI">		
		<xsl:for-each select="TopNode">	
			<xsl:if test="position() = 10">
				<xsl:for-each select="TopNodeTrend">	
					<xsl:choose>
						<xsl:when test = "position() != last()">
							<xsl:value-of select="@moduleCount"/>
							<xsl:text>,</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@moduleCount"/>					
						</xsl:otherwise>
					</xsl:choose> 
				</xsl:for-each>
			</xsl:if>	
		</xsl:for-each>		
	</xsl:for-each>	 	
	];
	console.log('custySAFARI10 : ' + custySAFARI10);	
	var colorSAFARI10 = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		
	const ALTROZTrendDBData = [{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ1,
			  borderColor: colorALTROZ1,
			  label: LabelStrALTROZ1,
			  data: custyALTROZ1
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ2,
			  borderColor: colorALTROZ2,
			  label: LabelStrALTROZ2,
			  <!-- data: [25, 45, 65, 85, 98, 100, 70,77,87,97], -->
			  data: custyALTROZ2
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ3,
			  borderColor: colorALTROZ3,
			  label: LabelStrALTROZ3,
			  data: custyALTROZ3
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ4,
			  borderColor:colorALTROZ4,
			  label: LabelStrALTROZ4,
			  data: custyALTROZ4
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ5,
			  borderColor:colorALTROZ5,
			  label: LabelStrALTROZ5,
			  data: custyALTROZ5
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ6,
			  borderColor:colorALTROZ6,
			  label: LabelStrALTROZ6,
			  data: custyALTROZ6
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ7,
			  borderColor:colorALTROZ7,
			  label: LabelStrALTROZ7,
			  data: custyALTROZ7
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ8,
			  borderColor:colorALTROZ8,
			  label: LabelStrALTROZ8,
			  data: custyALTROZ8
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ9,
			  borderColor:colorALTROZ9,
			  label: LabelStrALTROZ9,
			  data: custyALTROZ9
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorALTROZ10,
			  borderColor:colorALTROZ10,
			  label: LabelStrALTROZ10,
			  data: custyALTROZ10
			}			
		];
		
		const HARRIERTrendDBData = [{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER1,
			  borderColor: colorHARRIER1,
			  label: LabelStrHARRIER1,
			  data: custyHARRIER1
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER2,
			  borderColor: colorHARRIER2,
			  label: LabelStrHARRIER2,
			  <!-- data: [25, 45, 65, 85, 98, 100, 70,77,87,97], -->
			  data: custyHARRIER2
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER3,
			  borderColor: colorHARRIER3,
			  label: LabelStrHARRIER3,
			  data: custyHARRIER3
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER4,
			  borderColor:colorHARRIER4,
			  label: LabelStrHARRIER4,
			  data: custyHARRIER4
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER5,
			  borderColor: colorHARRIER5,
			  label: LabelStrHARRIER5,
			  <!-- data: [25, 45, 65, 85, 98, 100, 70,77,87,97], -->
			  data: custyHARRIER5
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER6,
			  borderColor: colorHARRIER6,
			  label: LabelStrHARRIER6,
			  data: custyHARRIER6
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER7,
			  borderColor:colorHARRIER7,
			  label: LabelStrHARRIER7,
			  data: custyHARRIER7
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER8,
			  borderColor: colorHARRIER8,
			  label: LabelStrHARRIER8,
			  <!-- data: [25, 45, 65, 85, 98, 100, 70,77,87,97], -->
			  data: custyHARRIER8
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER9,
			  borderColor: colorHARRIER9,
			  label: LabelStrHARRIER9,
			  data: custyHARRIER9
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorHARRIER10,
			  borderColor:colorHARRIER10,
			  label: LabelStrHARRIER10,
			  data: custyHARRIER10
			}				
		];
		
		
		const PUNCHTrendDBData = [{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH1,
			  borderColor: colorPUNCH1,
			  label: LabelStrPUNCH1,
			  data: custyPUNCH1
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH2,
			  borderColor: colorPUNCH2,
			  label: LabelStrPUNCH2,
			  data: custyPUNCH2
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH3,
			  borderColor: colorPUNCH3,
			  label: LabelStrPUNCH3,
			  data: custyPUNCH3
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH4,
			  borderColor:colorPUNCH4,
			  label: LabelStrPUNCH4,
			  data: custyPUNCH4
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH5,
			  borderColor: colorPUNCH5,
			  label: LabelStrPUNCH5,
			  data: custyPUNCH5
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH6,
			  borderColor: colorPUNCH6,
			  label: LabelStrPUNCH6,
			  data: custyPUNCH6
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH7,
			  borderColor:colorPUNCH7,
			  label: LabelStrPUNCH7,
			  data: custyPUNCH7
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH8,
			  borderColor: colorPUNCH8,
			  label: LabelStrPUNCH8,
			  data: custyPUNCH8
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH9,
			  borderColor: colorPUNCH9,
			  label: LabelStrPUNCH9,
			  data: custyPUNCH9
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorPUNCH10,
			  borderColor:colorPUNCH10,
			  label: LabelStrPUNCH10,
			  data: custyPUNCH10
			}		
		];
		
		
		const SAFARITrendDBData = [{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI1,
			  borderColor: colorSAFARI1,
			  label: LabelStrSAFARI1,
			  data: custySAFARI1
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI2,
			  borderColor: colorSAFARI2,
			  label: LabelStrSAFARI2,
			  data: custySAFARI2
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI3,
			  borderColor: colorSAFARI3,
			  label: LabelStrSAFARI3,
			  data: custySAFARI3
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI4,
			  borderColor:colorSAFARI4,
			  label: LabelStrSAFARI4,
			  data: custySAFARI4
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI5,
			  borderColor: colorSAFARI5,
			  label: LabelStrSAFARI5,
			  data: custySAFARI5
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI6,
			  borderColor: colorSAFARI6,
			  label: LabelStrSAFARI6,
			  data: custySAFARI6
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI7,
			  borderColor:colorSAFARI7,
			  label: LabelStrSAFARI7,
			  data: custySAFARI7
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI8,
			  borderColor: colorSAFARI8,
			  label: LabelStrSAFARI8,
			  data: custySAFARI8
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI9,
			  borderColor: colorSAFARI9,
			  label: LabelStrSAFARI9,
			  data: custySAFARI9
			},
			{
			  fill: false,
			  lineTension: 0,
			  backgroundColor: colorSAFARI10,
			  borderColor:colorSAFARI10,
			  label: LabelStrSAFARI10,
			  data: custySAFARI10
			}		
		];
		
	const ALTROZTrendSingleGraph = new Chart(document.getElementById('ALTROZTrendSingle'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: ALTROZTrendDBData
	  },
	  options: {
		legend: {display: false, position: 'right'},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});

	

	const HARRIERTrendSingleGraph = new Chart(document.getElementById('HARRIERTrendSingle'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: HARRIERTrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
	
	
	const PUNCHTrendSingleGraph = new Chart(document.getElementById('PUNCHTrendSingle'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: PUNCHTrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
	
	const SAFARITrendSingleGraph = new Chart(document.getElementById('SAFARITrendSingle'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: SAFARITrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
		

	const myChart1UK = new Chart(document.getElementById('myChart1'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: ALTROZTrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
	
	
	const myChart1UKPF2 = new Chart(document.getElementById('myChartPF2'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: HARRIERTrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
	
	const myChart1UKPF3 = new Chart(document.getElementById('myChartPF3'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: PUNCHTrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
	
	const myChart1UKPF4 = new Chart(document.getElementById('myChartPF4'), {
	  type: "line",
	  data: {
		labels: xValues2,
		datasets: SAFARITrendDBData
	  },
	  options: {
		legend: {display: false},
		scales: {
		  yAxes: [{ticks: {min: 6, max:16}}],
		}
	  }
	});
	
    
	
	new Chart("myChart3", {
	 type: 'line',
	 data: {
		labels: xValues2,
		datasets: [{
		   label: "HARRIER SAP BOM Report",
		   data: yValues2,
		   backgroundColor: ['yellow', 'aqua', 'pink', 'lightgreen', 'lightblue', 'gold'],
		   borderColor: ['black'],
		   borderWidth: 2,
		   pointRadius: 5,
		}],
	 },
	 options: {
		responsive: false,
	 },
	});
	
	
<!--     Custom Functions. -->

	function addDatasetALTROZ(val,modname)
	{	
		alert('Ujjawal..Passed ModAddr value is: ' + val);		
			
		const ModValPassed = val;		
		const yy = "";				
		var yValStr = [];
		var graphlabel = "";

		<!-- fetch("PV_Platforms_SAP_Data.xml").then(response => { -->
		alert('Fetching from http://localhost:55556/XMLTRY/PV_Platforms_SAP_Data.xml');
		fetch("http://localhost:55556/XMLTRY/PV_Platforms_SAP_Data.xml").then(response => {
		
			return response.text();
		}).then(xmlString => {
		
		console.log('222..Fetched XML file..');			
	
		const xmlDocument = new DOMParser().parseFromString(xmlString, "text/xml");
		const PlatformNodes = xmlDocument.querySelectorAll("ALTROZ");
		
		for (const PlatformNode of PlatformNodes) 
		{			
			const MDTrendNodes = PlatformNode.querySelectorAll("MDTrend");	
			
			for (const MDTrendNode of MDTrendNodes) 
			{
				const id = MDTrendNode.getAttribute("moduleID").toString();
				const title = MDTrendNode.getAttribute("moduleName").toString();			
				
				if(id == val)
				{
					console.log('Id ' + id + 'is equal to val ' + val);					
					i = 0;flag = 0;
					
					const ReportDates = MDTrendNode.querySelectorAll("ReportDate");
					
					for (const RepDate of ReportDates) 
					{					
						i = i + 1;						
						const RDate = RepDate.getAttribute("repDate");
						const MCount1 = RepDate.getAttribute("moduleCount").toString();						
						const MCount = parseInt(MCount1);
						
						console.log(RDate,MCount,ReportDates.length);						
						console.log('Index :' + i + ' of ' + ReportDates.length);						

						if ( i == ReportDates.length)
						{
							console.log('Last Node..position: ' + i);							
							yValStr.push(MCount);								
						}
						else
						{
							yValStr.push(MCount);							
						}							
					}
					
					console.log('Just before break :' + yValStr);					
					graphlabel = "["+ val +" : "+ modname +"]";									
					console.log('graphlabel : ' + graphlabel);						
					flag  = 1;					
					break;						
				}
				else
				{
				   console.log('Id ' + id + 'is NOT equal to val ' + val);
				}
			}
		}
		
		console.log('Value of flag :' + flag);		
		console.log('Just before return :' + yValStr);		
		
		var custyValues1 = yValStr;	
	
		console.log('custyValues1 from XML Parsing.. : ' + custyValues1);
		console.log('Just before custyValues1 : ' + custyValues1);
	
		const rancol = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		console.log('Randon colour : ' + rancol );
	
		const newDataset = {		
			fill: false,
			lineTension: 0,
			backgroundColor: rancol,
			borderColor: rancol,
			label: graphlabel,
			data: custyValues1
			}
			
			alert('Set to Data : For Mod-Addr : '+val+' custyValues1 = '+custyValues1);
			
			const myChartUjjPush = document.getElementById('myChart1');
			
			ALTROZTrendDBData.push(newDataset);
			ALTROZTrendSingleGraph.update();			
			
		})		
	}
<!-- End of function addDatasetALTROZ() -->

<!--     Custom Functions. -->

	function addDatasetHARRIER(val,modname)
	{	
		alert('Ujjawal..Passed ModAddr value is: ' + val);		
			
		const ModValPassed = val;		
		const yy = "";				
		var yValStr = [];
		var graphlabel = "";

		fetch("PV_Platforms_SAP_Data.xml").then(response => {
			return response.text();
		}).then(xmlString => {
		
		console.log('222..Fetched XML file..');			
	
		const xmlDocument = new DOMParser().parseFromString(xmlString, "text/xml");
		const PlatformNodes = xmlDocument.querySelectorAll("HARRIER");
		
		for (const PlatformNode of PlatformNodes) 
		{			
			const MDTrendNodes = PlatformNode.querySelectorAll("MDTrend");	
			
			for (const MDTrendNode of MDTrendNodes) 
			{
				const id = MDTrendNode.getAttribute("moduleID").toString();
				const title = MDTrendNode.getAttribute("moduleName").toString();			
				
				if(id == val)
				{
					console.log('Id ' + id + 'is equal to val ' + val);					
					i = 0;flag = 0;
					
					const ReportDates = MDTrendNode.querySelectorAll("ReportDate");
					
					for (const RepDate of ReportDates) 
					{					
						i = i + 1;						
						const RDate = RepDate.getAttribute("repDate");
						const MCount1 = RepDate.getAttribute("moduleCount").toString();						
						const MCount = parseInt(MCount1);
						
						console.log(RDate,MCount,ReportDates.length);						
						console.log('Index :' + i + ' of ' + ReportDates.length);						

						if ( i == ReportDates.length)
						{
							console.log('Last Node..position: ' + i);							
							yValStr.push(MCount);								
						}
						else
						{
							yValStr.push(MCount);							
						}							
					}
					
					console.log('Just before break :' + yValStr);					
					graphlabel = "["+ val +" : "+ modname +"]";									
					console.log('graphlabel : ' + graphlabel);						
					flag  = 1;					
					break;						
				}
				else
				{
				   console.log('Id ' + id + 'is NOT equal to val ' + val);
				}
			}
		}
		
		console.log('Value of flag :' + flag);		
		console.log('Just before return :' + yValStr);		
		
		var custyValues1 = yValStr;	
	
		console.log('custyValues1 from XML Parsing.. : ' + custyValues1);
		console.log('Just before custyValues1 : ' + custyValues1);
	
		const rancol = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		console.log('Randon colour : ' + rancol );
	
		const newDataset = {		
			fill: false,
			lineTension: 0,
			backgroundColor: rancol,
			borderColor: rancol,
			label: graphlabel,
			data: custyValues1
			}
			
			alert('Set to Data : For Mod-Addr : '+val+' custyValues1 = '+custyValues1);
			
			const myChartUjjPush = document.getElementById('myChart1');
			
			HARRIERTrendDBData.push(newDataset);
			HARRIERTrendSingleGraph.update();			
			
		})		
	}
<!-- End of function addDatasetHARRIER() -->

	function addDatasetPUNCH(val,modname)
	{	
		alert('Ujjawal..Passed ModAddr value is: ' + val);		
			
		const ModValPassed = val;		
		const yy = "";				
		var yValStr = [];
		var graphlabel = "";

		fetch("PV_Platforms_SAP_Data.xml").then(response => {
			return response.text();
		}).then(xmlString => {
		
		console.log('222..Fetched XML file..');			
	
		const xmlDocument = new DOMParser().parseFromString(xmlString, "text/xml");
		const PlatformNodes = xmlDocument.querySelectorAll("PUNCH");
		
		for (const PlatformNode of PlatformNodes) 
		{			
			const MDTrendNodes = PlatformNode.querySelectorAll("MDTrend");	
			
			for (const MDTrendNode of MDTrendNodes) 
			{
				const id = MDTrendNode.getAttribute("moduleID").toString();
				const title = MDTrendNode.getAttribute("moduleName").toString();			
				
				if(id == val)
				{
					console.log('Id ' + id + 'is equal to val ' + val);					
					i = 0;flag = 0;
					
					const ReportDates = MDTrendNode.querySelectorAll("ReportDate");
					
					for (const RepDate of ReportDates) 
					{					
						i = i + 1;						
						const RDate = RepDate.getAttribute("repDate");
						const MCount1 = RepDate.getAttribute("moduleCount").toString();						
						const MCount = parseInt(MCount1);
						
						console.log(RDate,MCount,ReportDates.length);						
						console.log('Index :' + i + ' of ' + ReportDates.length);						

						if ( i == ReportDates.length)
						{
							console.log('Last Node..position: ' + i);							
							yValStr.push(MCount);								
						}
						else
						{
							yValStr.push(MCount);							
						}							
					}
					
					console.log('Just before break :' + yValStr);					
					graphlabel = "["+ val +" : "+ modname +"]";									
					console.log('graphlabel : ' + graphlabel);						
					flag  = 1;					
					break;						
				}
				else
				{
				   console.log('Id ' + id + 'is NOT equal to val ' + val);
				}
			}
		}
		
		console.log('Value of flag :' + flag);		
		console.log('Just before return :' + yValStr);		
		
		var custyValues1 = yValStr;	
	
		console.log('custyValues1 from XML Parsing.. : ' + custyValues1);
		console.log('Just before custyValues1 : ' + custyValues1);
	
		const rancol = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		console.log('Randon colour : ' + rancol );
	
		const newDataset = {		
			fill: false,
			lineTension: 0,
			backgroundColor: rancol,
			borderColor: rancol,
			label: graphlabel,
			data: custyValues1
			}
			
			alert('Set to Data : For Mod-Addr : '+val+' custyValues1 = '+custyValues1);
			
			const myChartUjjPush = document.getElementById('myChart1');
			
			PUNCHTrendDBData.push(newDataset);
			PUNCHTrendSingleGraph.update();			
			
		})		
	}
<!-- End of function addDatasetPUNCH() -->


	function addDatasetSAFARI(val,modname)
	{	
		alert('Ujjawal..Passed ModAddr value is: ' + val);		
			
		const ModValPassed = val;		
		const yy = "";				
		var yValStr = [];
		var graphlabel = "";

		fetch("PV_Platforms_SAP_Data.xml").then(response => {
			return response.text();
		}).then(xmlString => {
		
		console.log('222..Fetched XML file..');			
	
		const xmlDocument = new DOMParser().parseFromString(xmlString, "text/xml");
		const PlatformNodes = xmlDocument.querySelectorAll("SAFARI");
		
		for (const PlatformNode of PlatformNodes) 
		{			
			const MDTrendNodes = PlatformNode.querySelectorAll("MDTrend");	
			
			for (const MDTrendNode of MDTrendNodes) 
			{
				const id = MDTrendNode.getAttribute("moduleID").toString();
				const title = MDTrendNode.getAttribute("moduleName").toString();			
				
				if(id == val)
				{
					console.log('Id ' + id + 'is equal to val ' + val);					
					i = 0;flag = 0;
					
					const ReportDates = MDTrendNode.querySelectorAll("ReportDate");
					
					for (const RepDate of ReportDates) 
					{					
						i = i + 1;						
						const RDate = RepDate.getAttribute("repDate");
						const MCount1 = RepDate.getAttribute("moduleCount").toString();						
						const MCount = parseInt(MCount1);
						
						console.log(RDate,MCount,ReportDates.length);						
						console.log('Index :' + i + ' of ' + ReportDates.length);						

						if ( i == ReportDates.length)
						{
							console.log('Last Node..position: ' + i);							
							yValStr.push(MCount);								
						}
						else
						{
							yValStr.push(MCount);							
						}							
					}
					
					console.log('Just before break :' + yValStr);					
					graphlabel = "["+ val +" : "+ modname +"]";									
					console.log('graphlabel : ' + graphlabel);						
					flag  = 1;					
					break;						
				}
				else
				{
				   console.log('Id ' + id + 'is NOT equal to val ' + val);
				}
			}
		}
		
		console.log('Value of flag :' + flag);		
		console.log('Just before return :' + yValStr);		
		
		var custyValues1 = yValStr;	
	
		console.log('custyValues1 from XML Parsing.. : ' + custyValues1);
		console.log('Just before custyValues1 : ' + custyValues1);
	
		const rancol = "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
		console.log('Randon colour : ' + rancol );
	
		const newDataset = {		
			fill: false,
			lineTension: 0,
			backgroundColor: rancol,
			borderColor: rancol,
			label: graphlabel,
			data: custyValues1
			}
			
			alert('Set to Data : For Mod-Addr : '+val+' custyValues1 = '+custyValues1);
			
			const myChartUjjPush = document.getElementById('myChart1');
			
			SAFARITrendDBData.push(newDataset);
			SAFARITrendSingleGraph.update();			
			
		})		
	}
<!-- End of function addDatasetSAFARI() -->
	
	
const randColor = () =>  {
    return "#" + Math.floor(Math.random()*16777215).toString(16).padStart(6, '0').toUpperCase();
}


	
	
	function getCustyVal(val1)
	{
	
		console.log('1111111111111' + val1);
		
		const yy = "";
		
		var zz = "UJJ";
		
		let yValStr = "[";

		fetch("testsan.xml").then(response => {
			return response.text();
		}).then(xmlString => {
		
		console.log('2222222222222222222222');
		
		
		
	
		const xmlDocument = new DOMParser().parseFromString(xmlString, "text/xml");
		const tutorials = xmlDocument.querySelectorAll("MDTrend");
		
		<!-- console.log(tutorials); -->
		
		for (const tutorial of tutorials) {
			const id = tutorial.getAttribute("moduleID");
			const title = tutorial.getAttribute("moduleName");
			
		    
			<!-- console.log(id,title); -->
			
			if(id == val1)
			{
				console.log('Id ' + id + 'is equal to val1 ' + val1);
				
				
				i = 0;
				flag = 0;
				
				const ReportDates = tutorial.querySelectorAll("ReportDate");
				
				for (const RepDate of ReportDates) 
				{
				
					i = i + 1;
					
					const RDate = RepDate.getAttribute("repDate");
					const MCount = RepDate.getAttribute("moduleCount");
					
					console.log(RDate,MCount,ReportDates.length);
					
					console.log('Index :' + i + ' of ' + ReportDates.length);

					if ( i == ReportDates.length)
					{
						console.log('Last Node..position: ' + i);
						
						yValStr = yValStr + MCount + "];";
					}
					else
					{
						yValStr = yValStr + MCount + ",";
					}
					
					
					<!-- console.log(yValStr); -->
					
					
				}

				console.log('Just before breaking...');
				console.log('Just before break :' + yValStr);
				
				flag  = 1;
				
				break;
				
				
				
			}
			else
			{
			   console.log('Id ' + id + 'is NOT equal to val1 ' + val1);
			}
		}
		
		console.log('Value of flag :' + flag);
		
		console.log('Just before return :' + yValStr);
	
		console.log('Value of zz :' + zz);
		
		return zz;		
		
		
		<!-- //yy = yValStr; -->
	 
		
		
	})
	

  
	
	}



	
	<!-- function getRandomColor() {
	  var letters = '0123456789ABCDEF';
	  var color = '#';
	  for (var i = 0; i < 6; i++) {
		color += letters[Math.floor(Math.random() * 16)];
	  }
	  return color;
	}
	 -->
	
	</script>
	
  </body> 
</html> 

</xsl:template>
</xsl:stylesheet> 