<?php
include('conn.php');

$sql = "SELECT * FROM `sistema`.`equipos` WHERE direccionIP = '".$_SERVER['REMOTE_ADDR']."';";
$ipreg = $conn->query($sql);

if($ipreg->num_rows > 0) {

		$row = $ipreg->fetch_assoc();
		if($row["activo"] == "1"){
			echo "-conf".$row["server"].",".$row["printBR"].",".$row["display"].",-end";
		} else{

			echo "-dispNo conf-end";
		}
	
} else {

	$sql = "INSERT INTO `sistema`.`equipos` (`direccionIP`,`tipo`) VALUES ('".$_SERVER['REMOTE_ADDR']."','".$_GET["t"]."');";

	if ($conn->query($sql) === TRUE) {
    echo "-dispNo conf-end";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
}

$conn->close();
?>
