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
Tabla de tickets
        <?php
        include("conn.php");

        ?>
	<a href="index.php">Inicio</a>
	<table border="1">
 		 <tr>
    			<th>ID</th>
    			<th>Fecha de entrada</th>
    			<th>Fecha de salida</th>
    			<th>Fecha de pago</th>
    			<th>Estacion de entrada</th>
    			<th>Estacion de salida</th>
    			<th>Estacion de pago</th>
    			<th>Salio</th>
    			<th>Tiempo en salir</th>
    			<th>Tiempo para salir</th>
                <th>Pago en tarjeta</th>
                <th>Pago en efectivo</th>
                <th>Pago en otros</th>
                <th>Cambio</th>

  		</tr>
<?php
$sql = "SELECT * FROM sistema.tickets";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
while($row = $result-> fetch_assoc()){
	echo "<tr><td>" . $row["ID"] . "</td><td>" . $row["fechaentrada"] . "</td><td>" . $row["fechasalida"] . "</td><td>" . $row["fechapago"] . "</td><td>" . $row["estentrada"] . "</td><td>" . $row["estsalida"] . "</td><td>" . $row["estpago"] . "</td><td>" . $row["salio"] . "</td><td>" . $row["tiempoensalir"] . "</td><td>" . $row["tiempoparasalir"] . "</td><td>" . $row["tarjeta"] . "</td><td>" . $row["efectivo"] . "</td><td>" . $row["otros"] . "</td><td>" . $row["cambio"] . "</td></tr>";
}
}else {
	echo "0 results";
}
$conn->close();
?> 

	</table>
    </body>
</html>
