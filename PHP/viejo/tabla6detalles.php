<!DOCTYPE HTML>
<?php

session_start();
if(@!$_SESSION['Usuario']){
        header("Location:login.php");
}

?>

<!DOCTYPE HTML>
<html>
    <head>
        <title>Desarrollos PNP | Dash Text</title>
    </head>
    <body>
Historial de movimientos
        <?php
        include("conn.php");

        ?>
	<a href="tabla6.php">Puestos fijos</a>
	<table border="1">
 		 <tr>
    			<th>IDF</th>
    			<th>Tipo de acceso</th>
    			<th>fecha</th>
                       <th>estacion</th>
  		</tr>
<?php
$sql = "SELECT * FROM sistema.fijodetalles WHERE IDF = '{$_GET['id']}'";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
while($row = $result-> fetch_assoc()){
	echo "<tr><td>" . $row["IDF"] . "</td><td>" . $row["modo"] . "</td><td>" . $row["fecha"] . "</td><td>" . $row["estacion"] . "</td></tr>";
}
}else {
	echo "0 results";
}
$conn->close();
?> 

	</table>
    </body>
</html>
