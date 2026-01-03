<?xml version="1.0" encoding="utf-8"?> 
<xsl:stylesheet version="1.0"  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" > 
<xsl:output method="html"/> 
<xsl:template match="/"> 
<!-- 
*****************************************************************************************************************
Pls do not copy this code. Copyright@2026.
*****************************************************************************************************************
-->
<html> 
  <head> 
		<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/3.9.1/chart.min.js"></script>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js"></script>	
		<link rel = "stylesheet" href = "//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css"></link>
		<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" />			
		<!-- <script type = "text/javascript" src = "https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>-->		
		<script type = "text/javascript" src = "https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.3/jquery-ui.min.js"></script>
		<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
	  
	<style>
	
	body {

    background-color: #F2F3F4;
	color: #636363;
	font-size: 11px;
	font-family: Tahoma, Geneva, sans-serif;
   
	}
	
	  h2   {color: blue;}
	  h6   {
		color: #004465;
		<!-- color: #006699; -->
		font-size: 12px;
		font-family: Tahoma, Geneva, sans-serif;
		font-weight: bold;
	  }
	  
	  h6_NPR   {
		color: #e67e22;
		<!-- color: #006699; -->
		font-size: 12px;
		font-family: Tahoma, Geneva, sans-serif;
		font-weight: bold;
	  }
	  
	  h4 {
	  font-family: Tahoma, Geneva, sans-serif;
	  }
	  
	  p {
		color: #006699;
		font-family: Tahoma, Geneva, sans-serif;
		text-align: center;
		}
	  
	  td {
		  border: 0.25px solid #dddfe1;
		  border-collapse: collapse;
		  color: #636363;
		  font-size: 12px;
		  font-family: Tahoma, Geneva, sans-serif;
		  padding: 3px;
		  text-align: center;
		  <!-- white-space: nowrap; -->	  
	  }
	  
	  th{
		  border: 0.25px solid #dddfe1;
		  background-color: #AED6F1;
		  white-space: nowrap;
		  <!-- color: #636363; -->
		  color: #006699;
		  padding: 3px;
		  text-align: center;
		  font-size: 11px;
		  font-family: Tahoma, Geneva, sans-serif;
		  
		  writing-mode: vertical-rl;
		  transform: scale(-1);
		  <!-- writing-mode: vertical-lr;
		  transform: scale(-1); -->
	  }
	  
	  th_awc{
		  border: 0.25px solid #dddfe1;
		  background-color: #006699;
		  white-space: nowrap;
		  color: white;
		  padding: 3px;
		  text-align: center;
		  font-size: 12px;
		  font-family: Tahoma, Geneva, sans-serif;
		  <!-- writing-mode: vertical-lr;
		  transform: scale(-1); -->
	  }
	  
	  tr:nth-child(even) {
		background-color: #f9fafb;
	  
	  }
	  
	  <!-- tr:hover {background-color: #ffff99;} -->
	  
	  <!-- tr:hover td {background:#ffff99; color:#006699; font-weight:bold;} -->
	  tr:hover td {background:#ffff99; color:#006699;}

<!-- 	 .row > div {
		  
		  border: 1px solid grey;
		} -->
		
		
	.td_header {
		  border: 0.25px solid #dddfe1;
		  border-collapse: collapse;
		  color: white;
		  font-size: 12px;
		  font-family: Tahoma, Geneva, sans-serif;
		  padding: 3px;
		  text-align: center;
		  pointer-events: none;
		  <!-- white-space: nowrap; -->	  
	  }
	  
	.tr_nohover{
	  pointer-events: none;
	  }
	  
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
		font-size: 16px;
		font-weight: bold;
		background-color: #006699;
		white-space: nowrap;
		color: white;
		text-align: center;
		vertical-align: middle;
		padding-top: 5px;
		padding-bottom: 5px;
	}
	
	.col-md-1 {
		font-size: 16px;
		font-weight: bold;
		background-color: #EBEDEF;
		white-space: nowrap;
		color: white;
		text-align: center;
		vertical-align: middle;
		padding-top: 5px;
		padding-bottom: 5px;
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
	
.cardInAggGrpPage {
  /* Add shadows to create the "card" effect */
  box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2);
  background-color: #04AA6D;
  transition: 0.3s;
  font-size: 12px;
  border-radius: 10px; /* 5px rounded corners */
}
		
.card {
  /* Add shadows to create the "card" effect */
<!--   height: 100px;
  width: 300px; -->
  <!-- box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2); -->
  transition: 0.3s;
  border-radius: 10px; /* 5px rounded corners */
}

/* On mouse-over, add a deeper shadow */
.card:hover { 
  box-shadow: 0 2px 10px 0 #006699;
}
<!-- .card_container:hover {
  color : #ffff99; 
} -->

/* Add some padding inside the card container */
.card_container {
  padding: 4px 16px;
  <!-- background-color: #F2F3F4; -->
  background-color: white;
  color: #626567;
  font-size: 11px;
}

/* Add some padding inside the card container */
.card_container_top {
  padding: 40px 16px;
  height: 250px;
  background-color: #154360;
  color: white;
  vertical-align: middle;
  font-size: 11px;
}
	  
	div.wrap {
	  word-wrap: break-word;
	}  	

.label_alert{
  <!-- display: flex;   -->
  <!-- background-color: #dddfe1; -->
  <!-- background-color: #ffff99; -->
  width: 1000px;
  height: 250px;
  background-color: #f0fbff;
  <!-- background-color: #ffe2a9; -->
  <!-- background-color: white; ffffc5 ffd071-->
  <!-- color: #636363;  -->
  <!-- color: #004465; -->
  color: #004465;
  <!-- font-weight: bold; -->
  <!-- text-shadow: 0 0 5px #00ff00, 0 0 5px #00ff00, 0 0 5px #00ff00; -->
  padding: 5px;
  margin-bottom: 5px;  
  <!-- font-size: 13px; -->
  border: 1.25px solid #dddfe1;
  <!-- font-weight: bold; -->
  <!-- box-shadow: 0 0 5px 0 #006699; -->
}

/* On mouse-over, add a deeper shadow */
.label_alert:hover { 
  background-color: #ffff99;
  <!-- font-weight: bold; -->
  box-shadow: 0 0 3px 0 #006699;
}

.label_NPR{
  display: flex;  
  <!-- background-color: #fffcbf; -->
  <!-- background-color: #dddfe1; -->
  <!-- background-color: #f5cba7; -->
  <!-- background-color: #1a5276; -->
    background-color: #fad7a0;
  <!-- background-color: #005078; -->
  <!-- background-color: #fcf3cf; -->
  
  <!-- color: #ffff99;   -->
  color: #7e5109;  
  <!-- color: #fffcbf;   -->
  font-size: 12px;
  font-weight: bold;
  padding: 2px;
  <!-- border: 0.25px solid #abb2b9; -->

  font-family: Tahoma, Geneva, sans-serif;
  
  <!-- font-weight: bold; -->
}

.label_MCC{
  display: flex;  
  <!-- background-color: #fffcbf; -->
  <!-- background-color: #dddfe1; -->
  background-color: #006699;
  <!-- background-color: white; -->
  <!-- background-color: #005078; -->
  <!-- background-color: #fcf3cf; -->
  
  <!-- color: #636363;  -->
  color: white;   
  <!-- color: #004465;   -->
  <!-- color: #fffcbf;   -->
  font-size: 12px;
  font-weight: bold;
  padding: 2px;
  <!-- border: 0.25px solid #abb2b9; -->

  font-family: Tahoma, Geneva, sans-serif;
  
  <!-- font-weight: bold; -->
}

.label1{
  <!-- display: flex;   -->
  width: 1000px;
  height: 40px;
  <!-- background-color: #fffcbf; -->
  <!-- background-color: #dddfe1; -->
  background-color: #004465;
  <!-- background-color: white; -->
  <!-- background-color: #005078; -->
  <!-- background-color: #fcf3cf; -->
  
  color: #33ff4c;  
  <!-- color: #004465;   -->
  <!-- color: #fffcbf;   -->
  font-size: 14px;
  align-content : center;
  <!-- font-weight: bold; -->
  padding: 5px;
  border: 1.25px solid #abb2b9;
  <!-- font-weight: bold; -->
}

.label2{
  <!-- display: flex;   -->
  <!-- text-align: center; -->
  text-align: center;
  align-content: space-evenly;
  background-color: #006699;
  color: white;
  font-weight: bold;
  padding: 5px;
  margin-top: 2px;
  <!-- font-weight: bold; -->
}

.label_info{
  <!-- display: flex;   -->
  <!-- text-align: center; -->
  text-align: left;
  align-content: space-evenly;
  <!-- background-color: #f0fbff; -->
  <!-- background-color: #AED6F1;   -->
  <!-- background-color: #f0fbff;   -->
  background-color: #f0fbff;  
  <!-- color: #006699; -->
  color: #004465;  
  <!-- font-weight: bold; -->
  padding: 5px;
  margin-bottom: 5px;
  border: 1.25px solid #dddfe1;
  <!-- font-weight: bold; -->
}

.label_info:hover { 
  background-color: #ffff99;
  <!-- font-weight: bold; -->
  box-shadow: 0 0 3px 0 #006699;
}

.label_info_header{
  <!-- display: flex;   -->
  <!-- text-align: center; -->
  text-align: left;
  align-content: space-evenly;
  <!-- background-color: #f0fbff; -->
  background-color: #ffff99;  
  <!-- background-color: #ffff99;   -->
  <!-- color: #006699; -->
  color: #641e16;
  <!-- font-weight: bold; -->
  padding: 5px;
  margin-bottom: 5px;
  border: 1.25px solid #f9e79f;
  <!-- font-weight: bold; -->
}

.grid-container {
  display: grid;
  grid-template-columns: auto auto auto auto;
  gap: 10px;
  <!-- background-color: #F2F3F4; -->
  background-color: white;
  padding: 5px;
  border: 1.25px solid #dddfe1;
  
}

.grid-container > div {
  <!-- background-color: rgba(255, 255, 255, 0.8); -->
  <!-- text-align: center; -->
  padding: 5px 5px;
  font-size: 11px;
  border: 1.25px solid #006699;
  border-radius: 5px;    

 }
 
 .grid-container > div:hover { 
  box-shadow: 0 2px 10px 0 #006699;
}

.grid-container-2 {
  display: grid;
  grid-template-columns: auto auto auto auto auto auto auto;
  gap: 5px;
  <!-- background-color: #F2F3F4; -->
  background-color: white;
  padding: 5px;
   border: 1.25px solid #dddfe1;
  
}

.grid_sm_usage_freq {
  display: grid;
  grid-template-columns: 200px auto;
  gap: 5px;
  <!-- background-color: #F2F3F4; -->
  background-color: white;
  padding: 5px;
   border: 1.25px solid #dddfe1;
  
}

.grid-container-2 > div {
  <!-- background-color: white; -->
  <!-- text-align: center; -->
  padding: 10px 10px;
  <!-- font-size: 11px; -->
  border: 2.25px solid #dddfe1;
  border-radius: 5px;
  <!-- border-radius: 10px;     -->

 }
 
 .grid-container-2 > div:hover { 
  box-shadow: 0 2px 10px 0 #006699;
}

.item1 {
  grid-row-start: 1;
  grid-row-end: 3;
  align-content: space-evenly; 
  background-color: #AED6F1;
  <!-- color: white;   -->
}

.item2 {
  grid-row-start: 1;
  grid-row-end: 3;
  align-content: space-evenly;
  background-color: #f9e79f;
  <!-- color: white;   -->
}
.itemg2cell {
  align-content: space-evenly;
  background-color: #fff8de;  
}

.itemg2cell_lb {
  align-content: space-evenly;
  background-color: #e0f3ff;  
}

.item21 { 
  text-align: center;
  align-content: space-evenly;
  background-color: #006699;
  color: white;
  font-size: 14px;  
}

.itemUF1 { 
  text-align: center;
  align-content: space-evenly;
  background-color: #006699;
  color: white; 
  vertical-align: middle;
  border-radius: 50px;  
}

.itemg1_1 { 
  text-align: left;
  background-color: #F2F3F4;
  <!-- color: white;   -->
}

.item27{
  text-align: center;
  background-color: #f0fbff;
  font-size: 12px;
  font-weight: bold;
  border: 0.25px solid #dddfe1;
  align-content: space-evenly;
}

</style>

</head> 

<body> 
    <!--<canvas id="myChart" style="width:100%;max-width:600px"></canvas> -->

<div class="container">	
		<!-- tabs-1 Dashboard. -->
		<div id = "tabs-1">	
			<div class="row m-3"> 
				<div class="col-sm-12">
					<center><h5><b>Part Applicability Matrix Report</b></h5></center>					
				</div>
			</div>			
			<br></br>
			<center>
			<div class="label1">
			Report Initiated Successfully !!
			</div>
			
			<div class="label_alert" style="font-size: 14px;">
			<br></br>
				<xsl:for-each select="MCCSCRReport/DataRefreshDate">						
					<xsl:value-of select="LastDate"/>							
				</xsl:for-each>	
				<br></br>
				Report initiated successfully in background for Part List:
				
				<xsl:for-each select="MCCSCRReport/DataSheet1">						
					<b><xsl:value-of select="Input_ModAddr"/></b>						
				</xsl:for-each>	
				<br></br><br></br>
				<u>Report will take time (~Hrs) depending on the number of Modules present in TCUA for given Input Part List.</u>
				<br></br>
				Report will run in background and will get delivered to your mail as well as will be attached on your TCUA login ID's Home Folder as a Dataset(Login -> View -> Refresh Window): 
				<xsl:for-each select="MCCSCRReport/DataSheet1">						
					<b><xsl:value-of select="Input_EmaiID"/></b>						
				</xsl:for-each>
				<br></br><br></br>
				Kindly check your Mailbox & TCUA Home Folder after a few hours.
				<br></br><br></br>
				<font size="1px">
				For any queries/support pls get in touch with:
				<br></br>
				karaksourav94@gmail.com
				</font>
			</div>		
				
			</center>			
			
	
<br></br>
<hr style="height:5px;border-width:0;color:gray;background-color:gray"></hr>

		<center>
		<font size="2px">Copyright@2026 (PLM Team)</font>
		</center>
			
	</div> 	
			

	<!-- </div> -->
		
		 
</div>
	
	 <!--<canvas id="chartId" aria-label="chart" heigth="350" width="580"></canvas>-->
<!-- 	 <canvas id="myChart3" style="width:100%"></canvas>-->
	
	<script>
	
	
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

