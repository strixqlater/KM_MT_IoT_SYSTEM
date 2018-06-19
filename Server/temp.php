<?php
 include("head.inc");
?>
<!DOCTYPE HTML>
<html>
<head>
 <meta charset="utf-8">
 <meta http-equiv="refresh" content="5">
 <title>codegazer.NET</title>
 <script type="text/javascript" src="https://www.google.com/jsapi"></script>
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
 <script type="text/javascript">
 google.load("visualization", "1", {packages:["corechart"]});
 google.setOnLoadCallback(drawChart);
 function drawChart() {
 var data = google.visualization.arrayToDataTable([

 ['Time','Temp'],
 <?php 
			$query = "select s_time, temp from sensor order by s_time desc limit 30";

			 $exec = mysqli_query($db_conn,$query);
			 while($row = mysqli_fetch_array($exec)){

			 echo "['".$row['s_time']."',".$row['temp']."],";
			 }
			 ?> 
 
 ]);

 var options = {
 title: 'Temperature Data',
  pieHole: 0.5,
          pieSliceTextStyle: {
            color: 'black',
          },
          legend: 'none'
 };
 var chart = new google.visualization.LineChart(document.getElementById("columnchart12"));
 chart.draw(data,options);
 }
	
    </script>

</head>
<body>
 <div class="container-fluid">
 <div id="columnchart12" style="width: 100%; height: 500px;"></div>
 </div>

</body>
</html>
