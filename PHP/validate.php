<?php

session_start();

	require("conn.php");

$username=$_POST['user'];
$pass=$_POST['pass'];

if($username=='admin'){
	$sql="SELECT * FROM usuarios WHERE Usuario='$username'";
	$result = $conn->query($sql);
	if($result->num_rows > 0) {
		while($row = $result->fetch_assoc()){
			if($pass==$row['Clave']){
				$_SESSION['ID']=$row['UserID'];
				$_SESSION['Usuario']=$row['Usuario'];
				$_SESSION['Access']=$row['Niveldeacceso'];
				echo '<script>alert("BIENVENIDO ADMINISTRADOR")</script> ';
				echo "<script>location.href='index.php'</script>";
			}
			else{
				echo '<script>alert("Los Datos ingresados no son los correctos")</script> ';
				echo "<script>location.href='login.php'</script>";
			}
		}				
	}
}

$sql="SELECT * FROM usuarios WHERE Usuario='$username'";
$result = $conn->query($sql);
if($result->num_rows > 0){
	while($row = $result->fetch_assoc()){
		if($pass==$row['Clave']){
			$_SESSION['ID']=$row['UserID'];
			$_SESSION['Usuario']=$row['Usuario'];
			$_SESSION['Access']=$row['Niveldeacceso'];
			echo '<script>alert("BIENVENIDO SUPERVISOR")</script> ';
			echo "<script>location.href='index.php'</script>";
		}
	}
}

else{
	echo '<script>alert("Los Datos ingresados no son los correctos")</script> ';
	echo "<script>location.href='login.php'</script>";
} 

?>
