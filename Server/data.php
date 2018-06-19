<?php
include("head.inc");

$temp = $_GET["temp"];
$humid = $_GET["humid"];
$dust = $_GET["dust"];

echo($temp);
echo($humid);
echo($dust);

$query = "insert into sensor(s_time, temp, humid, dust) values(now(), $temp, $humid, $dust)";
if(mysqli_query($db_conn, $query) === TRUE) echo("success");
else echo("fail");
mysqli_close();
?>
