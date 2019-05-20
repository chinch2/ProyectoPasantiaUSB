<?php
include("conn.php");

$sql = "SELECT Equipos from sistema.equipos WHERE direccionIP = '".$_SERVER['REMOTE_ADDR']."';";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
	while($row = $result->fetch_assoc()) {
		$est = $row["Equipos"];
	}
} else{
	echo "0 results";
}

$sql = "UPDATE sistema.tickets SET fechapago = CURRENT_TIMESTAMP, estpago = " . $est . ", tarjeta = tarjeta + '".$_GET["pa"]."', efectivo = efectivo + '".$_GET["pb"]."', otros = otros + '".$_GET["pc"]."', cambio = cambio + '".$_GET["cambio"]."' WHERE (`ID` = '".$_GET["id"]."');";

if ($conn->query($sql) === TRUE) {
	
	echo "-dispGracias! Bs " .$_GET["cambio"]. "-end";
} else {
	echo "Error: " . $sql . "<br>" . $conn->error;
}

$sql = "INSERT INTO transacciones (ticket, equipo, fecha, tarjeta, efectivo, otros, cambio) VALUES ('".$_GET["id"]."', " . $est . ", CURRENT_TIMESTAMP, '".$_GET["pa"]."', '".$_GET["pb"]."', '".$_GET["pc"]."', '".$_GET["cambio"]."');";

if ($conn->query($sql) === TRUE) {
    //echo ""
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
