<?php
include("conn.php");

$sql = "SELECT Equipos from sistema.equipos WHERE direccionIP = '".$_SERVER['REMOTE_ADDR']."';";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
	while($row = $result->fetch_assoc()) {
		$est = $row["Equipos"];
	}
}else{
	echo "0 results";
}

if(isset($_GET["IDF"])){

	$sql = "SELECT dentro from sistema.fijos WHERE dentro = 'no' and `IDF` = '{$_GET['IDF']}';";

	$fijousado = $conn->query($sql);

	if($fijousado->num_rows > 0) {

        $sql = "UPDATE sistema.fijos SET dentro = 'si' WHERE IDF = '{$_GET['IDF']}';";

        if($conn->query($sql) == TRUE) {

        echo "-dispAbriendo barrera-end-barr1-end";
}else{
	echo "Error: " . $sql . "<br>" . $conn->error;
}

	$sql = "INSERT INTO sistema.fijodetalles (IDF, modo, estacion) VALUES ('{$_GET['IDF']}', 'entrada', '{$est}');";
	if($conn->query($sql) == TRUE) {

}else{

	echo "Error: " . $sql . "<br>" . $conn->error;

}
}else{ 
	 echo "-dispYa esta dentro-end";
}
}else{

$sql = "INSERT INTO tickets (estentrada, salio) VALUES ({$est}, 0);";

if ($conn->query($sql) === TRUE) {
    $last_id = $conn->insert_id;
    echo "-dispImprimiendo...-end";
}else{
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$sql = "SELECT fechaentrada FROM tickets WHERE (`ID` =" . $last_id . ");";
$fechaentrada = $conn->query($sql);

if ($fechaentrada->num_rows > 0) {
    // output data of each row
    while($row = $fechaentrada->fetch_assoc()) {
        echo "-prin" . $row["fechaentrada"] . "\r\n" . $last_id . "-end-barr1-end";
    }
} else {
    echo "0 results";
}
}

$conn->close();

?>
