<?php

include("conn.php");

$sql = "SELECT PHP from sistema.tarifas left join sistema.equipos on codigo = tarifa WHERE PHP != '' and direccionIP = '".$_SERVER['REMOTE_ADDR']."';";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
	while($row = $result->fetch_assoc()) {
		echo "Ejecutando codigo auxiliar <br>";
		eval($row["PHP"]);
	}
} else {

	$sql = "SELECT tiempoensalir FROM tickets WHERE tiempoensalir >= tiempoparasalir and (`ID` = '".$_GET["id"]."');";
	$result = $conn->query($sql);

        if($result->num_rows > 0) {
        	$sql = "SELECT fechamulta, CURRENT_TIMESTAMP from sistema.tickets WHERE (`ID` = '".$_GET["id"]."');";

	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
    	// output data of each row
		while($row = $result->fetch_assoc()) {
			$tdiff = strtotime($row["CURRENT_TIMESTAMP"]) - strtotime($row["fechamulta"]);
		}
	} else {
		echo "0 results";
}

        } else {

	$sql = "SELECT fechaentrada, CURRENT_TIMESTAMP from sistema.tickets WHERE (`ID` = '".$_GET["id"]."');";

	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
    	// output data of each row
		while($row = $result->fetch_assoc()) {
			$tdiff = strtotime($row["CURRENT_TIMESTAMP"]) - strtotime($row["fechaentrada"]);
		}
	} else {
		echo "0 results";
		}
}

$sql = "SELECT preciohora1, tiempohora1, preciohora2, tiempohora2, preciohora3 from sistema.tarifas left join sistema.equipos on codigo = tarifa WHERE direccionIP = '".$_SERVER['REMOTE_ADDR']."';";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
	while($row = $result->fetch_assoc()) {

		$tdh = $tdiff/3600;
		$ph1 = $row["preciohora1"];
		$ph2 = $row["preciohora2"];
		$ph3 = $row["preciohora3"];
		$th1 = $row["tiempohora1"];
		$th2 = $row["tiempohora2"];

		if (round($tdh) <= $th1) {
			
			$tarifa = round($tdh * $ph1);
		}

		if (round($tdh) > $th1 && round($tdh) <= $th2) {

			$tarifa = round($tdh * $ph2);
		}

		if (round($tdh) > $th2) {

			$tarifa = round($tdh * $ph3);
		}

	}
} else {
	echo "0 results";
}
	}

echo "-dispMonto: " . $tarifa . "-end-pago" . $tarifa . "-end";

$conn->close();

?>
