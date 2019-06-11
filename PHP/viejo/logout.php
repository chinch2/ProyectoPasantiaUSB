<?php

session_start();
if($_SESSION['Usuario']){
	session_destroy();
	header("location:login.php");
}
else{
	header("location:login.php");
}

?>
