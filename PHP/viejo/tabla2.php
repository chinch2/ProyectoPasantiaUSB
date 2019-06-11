<!DOCTYPE HTML>
<?php

session_start();
if(@!$_SESSION['Usuario']){
	header("location:login.php");
}

?>

<!DOCTYPE HTML>
<html>
    <head>
        <title>Desarrollos PNP | Dash Text</title>
    </head>
    <body>
Tabla de equipos
        <?php
        include("conn.php");
        if(isset($_POST["forma"])){
            $sql = "UPDATE sistema.equipos SET  activo = '{$_POST["activo"]}', descripcion = '{$_POST["descripcion"]}', server = '{$_POST["server"]}', printBR = '{$_POST["printBR"]}', display = '{$_POST["display"]}', tarifa = '{$_POST["tarifa"]}' WHERE Equipos = '{$_POST["equipo"]}';";
            $result = $conn->query($sql);
            unset($_GET["id"]);
        }
        ?>
	<a href="index.php">Inicio</a>
	<table border="1">
 		 <tr>
    			<th>Equipos</th>
    			<th>Tipo de estacion</th>
    			<th>Estado</th>
    			<th>Direccion IP</th>
    			<th>Descripcion</th>
    			<th>Direccion IP del servidor</th>
    			<th>Baud Rate de Impresora</th>
    			<th>Caracteristicas del Display</th>
                <th>Tipo de tarifa</th>
                <th></th>
  		</tr>
<?php
$sql = "SELECT * FROM sistema.equipos";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
	while($row = $result-> fetch_assoc()){
		echo "<tr><td>" . $row["Equipos"] . "</td><td>" . $row["tipo"] . "</td><td>" . $row["activo"] . "</td><td>" . $row["direccionIP"] . "</td><td>" . $row["descripcion"] . "</td><td>" . $row["server"] . "</td><td>" . $row["printBR"] . "</td><td>" . $row["display"] . "</td><td>" . $row["tarifa"] . "</td>";

		if($_SESSION['Access']==1){
			echo "<td><a href=\"tabla2.php?id=" . $row["Equipos"] . "\">Modificar</a></td></tr>";
		}else{
			echo "</tr>";
		}
		if($_GET["id"]==$row["Equipos"]){
        		$campo = $row;
    		}
	}
}else{
	echo "0 results";
}
echo "</table><br><br>";

if(count($campo)){
    echo '<form method="post">
     Descripcion:<br>
  <input type="text" name="descripcion" value="' . $campo["descripcion"] . '">
  <br>
    Server:<br>
  <input type="text" name="server" value="' . $campo["server"] . '">
  <br>
  <input type="hidden" name="equipo" value="' . $campo["Equipos"] . '">
  Printer Baud Rate:<br>
  <input type="text" name="printBR" value="' . $campo["printBR"] . '">
  <br>
  Printer Display:<br>
  <input type="text" name="display" value="' . $campo["display"] . '">
  <br>
  Estado:<br>
    <select name="activo">
    <option value="1" '.($campo['activo']?'selected':'').'>Activo</option>
    <option value="0" '.($campo['activo']?'':'selected').'>Inactivo</option>
  </select>
   <br>
  Tipo de tarifa:<br>
    <select name="tarifa">
    <option value="1" ' . ($campo['tarifa'] == 1?'selected':'') . '>Tipo 1</option>
    <option value="2" ' . ($campo['tarifa'] == 2?'selected':'') . '>Tipo 2</option>
    <option value="3" ' . ($campo['tarifa'] == 3?'selected':'') . '>Tipo 3</option>
  </select>
  <input type="submit" name="forma" value="Submit">
 </form>';
}
$conn->close();
?> 

	</table>
    </body>
</html>
