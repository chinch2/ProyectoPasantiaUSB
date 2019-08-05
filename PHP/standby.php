<?php
date_default_timezone_set("America/Caracas");

if($_GET["carro"] == 1) {
  echo "-dispBienvenido!         Pulse el boton-end";
}
else{ 
echo "-disp" . date('d/m/y   H:i') . "-end";
}
?>