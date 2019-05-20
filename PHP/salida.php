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

if(isset($_GET["IDF"])){

	$sql = "SELECT dentro from sistema.fijos WHERE dentro = 'si' and `IDF` = '{$_GET['IDF']}';";

	$fijousado = $conn->query($sql);

	if($fijousado->num_rows > 0) {

        $sql = "UPDATE sistema.fijos SET dentro = 'no' WHERE IDF = '{$_GET['IDF']}';";
        
	if($conn->query($sql) == TRUE) {
        
	echo "-dispAbriendo barrera-end-barr1-end";
}else{
        echo "Error: " . $sql . "<br>" . $conn->error;
}

	$sql = "INSERT INTO sistema.fijodetalles (IDF, modo, estacion) VALUES ('{$_GET['IDF']}', 'salida', '{$est}');";
        if($conn->query($sql) == TRUE) {

}else{

        echo "Error: " . $sql . "<br>" . $conn->error;

}
}else{
	echo "-dispYa salio-end";
}
}else{


//Verificar que el ticket no sea usado
$sql = "SELECT salio,estpago FROM tickets WHERE (`ID` = '".$_GET["id"]."');";
$ticketusado = $conn->query($sql);

if ($ticketusado->num_rows > 0) {
    // output data of each row
    while($row = $ticketusado->fetch_assoc()) {
        //echo "-dispEscaneando...   -end";
        $sql = "SELECT salio,estpago FROM tickets WHERE salio < 1 and estpago > 0 and (`ID` = '".$_GET["id"]."');";
        $sale = $conn->query($sql);

        if($sale->num_rows > 0) {


$sql = "UPDATE tickets SET tiempoensalir = TIMESTAMPDIFF(MINUTE,fechapago,CURRENT_TIMESTAMP) WHERE (`ID` = '".$_GET["id"]."');";

if ($conn->query($sql) === TRUE) {
    //echo "Tardó un tiempo de";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$sql = "SELECT tiempoensalir FROM tickets WHERE (`ID` = '".$_GET["id"]."');";
$tiempoensalir = $conn->query($sql);

if ($tiempoensalir->num_rows > 0) {
    // output data of each row
    while($row = $tiempoensalir->fetch_assoc()) {
	//echo "-disp: " . $row["tiempoensalir"] . " minutos    -end";
	$sql = "SELECT tiempoensalir FROM tickets WHERE tiempoensalir < tiempoparasalir and (`ID` = '".$_GET["id"]."');";
	$sale = $conn->query($sql);

        if($sale->num_rows > 0) {
			echo "-dispHasta luego!-end-barr1-end";
			$sql = "UPDATE tickets SET estsalida = " . $est . " WHERE (`ID` = '".$_GET["id"]."');";
			if ($conn->query($sql) === TRUE) {
   						 //echo ".<br>\n";
						} else {
    							echo "Error: " . $sql . "<br>" . $conn->error;
							}
			$sql = "UPDATE tickets SET fechasalida = CURRENT_TIMESTAMP WHERE (`ID` = '".$_GET["id"]."');";
				if ($conn->query($sql) === TRUE) {
                                                 //echo ".<br>\n";
                                                } else {
                                                        echo "Error: " . $sql . "<br>" . $conn->error;
                                                        }
			$sql = "UPDATE tickets SET salio = 1 WHERE (`ID` = '".$_GET["id"]."');";
			if ($conn->query($sql) === TRUE) {
                                                 //echo ".<br>\n";
                                                } else {
                                                        echo "Error: " . $sql . "<br>" . $conn->error;
                                                        }

	}else {
		echo "-dispTiempo de salida    excedido.-end";
		$sql = "UPDATE tickets SET fechamulta = CURRENT_TIMESTAMP WHERE (`ID` = '".$_GET["id"]."');";
		if ($conn->query($sql) === TRUE) {
                                                 //echo ".<br>\n";
                                                } else {
                                                        echo "Error: " . $sql . "<br>" . $conn->error;
                                                        }

		}
    }
} else {
    echo "0 results";
}

} else{
	echo "-dispNo ha pagado o      Ticket usado-end";
}
}
} else {
	echo "0 results";
}
}

$conn->close();

?>

