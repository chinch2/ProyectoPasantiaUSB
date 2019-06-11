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
Tabla de transacciones
        <?php
        include("conn.php");

        ?>
	<a href="index.php">Inicio</a>
	<table border="1">
 		 <tr>
    			<th>ID</th>
    			<th>Estacion</th>
    			<th>Fecha</th>
                <th>Pago en tarjeta</th>
                <th>Pago en efectivo</th>
                <th>Pago en otros</th>
                <th>Cambio</th>

  		</tr>
<?php
$sql = "SELECT * FROM sistema.transacciones";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
while($row = $result-> fetch_assoc()){
	echo "<tr><td>" . $row["ticket"] . "</td><td>" . $row["equipo"] . "</td><td>" . $row["fecha"] . "</td><td>" . $row["tarjeta"] . "</td><td>" . $row["efectivo"] . "</td><td>" . $row["otros"] . "</td><td>" . $row["cambio"] . "</td></tr>";
}
}else {
	echo "0 results";
}
$conn->close();
?> 

	</table>
    </body>
</html>
