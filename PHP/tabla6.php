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
Tabla de puestos fijos
        <?php
        include("conn.php");

        if(isset($_GET["del"])){

          $sql = "DELETE FROM sistema.fijos WHERE IDF = '".$_GET["id"]."';";

          if ($conn->query($sql) === TRUE) {
          
          $last_id = $conn->insert_id;

          $_GET["id"] = $last_id;

          } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
            }
        unset($_GET["del"]);

        }

        if(isset($_GET["insert"])){

        $sql = "INSERT INTO fijos (nombre, telefono, puesto, vehiculo) VALUES ('nombre', 'telefono', 'puesto', 'vehiculo');";

          if ($conn->query($sql) === TRUE) {
          
          $last_id = $conn->insert_id;

          $_GET["id"] = $last_id;

          } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
            }
      }
 
        if(isset($_POST["forma"])){
            $sql = "UPDATE sistema.fijos SET  nombre = '{$_POST["nombre"]}', telefono = '{$_POST["telefono"]}', puesto = '{$_POST["puesto"]}', vehiculo = '{$_POST["vehiculo"]}' WHERE IDF = '{$_POST["IDF"]}';";
            $result = $conn->query($sql);
            unset($_GET["id"]);
        }
        ?>
  <a href="index.php">Inicio</a>
  <table border="1">
     <tr>
	  <th>ID</th>
          <th>Nombre</th>
          <th>Telefono</th>
          <th>Ubicacion del puesto</th>
          <th>Vehiculo</th>
       	  <th>Puesto ocupado</th>
      </tr>
<?php
$sql = "SELECT * FROM sistema.fijos";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
	while($row = $result-> fetch_assoc()){
  		echo "<tr><td>{$row["IDF"]}</td><td>{$row["nombre"]}</td><td>{$row["telefono"]}</td><td>{$row["puesto"]}</td><td>{$row["vehiculo"]}</td><td>{$row["dentro"]}</td>";
		if($_SESSION['Access'] <= 2){
			echo "<td><a href=\"tabla6.php?id={$row["IDF"]}\">Modificar</a></td><td><a href=\"tabla6.php?id={$row["IDF"]}&del=1\">Eliminar</a></td><td><a href=\"tabla6detalles.php?id={$row["IDF"]}\">Detalles</a></td></tr>";
		}else{
		echo "</tr>";
		}

		if($_GET["id"]==$row["IDF"]){
        		$campo = $row;
    		}
	}
}else{
  echo "0 results <br><br>";
}

echo "</table><br><br>";

if(count($campo)){
    echo '<form action= "tabla6.php" method="post">
  ID:<br>
  <input type="text" name="IDF" value="' . $campo["IDF"] . '">
  <br>
  Nombre:<br>
  <input type="text" name="nombre" value="' . $campo["nombre"] . '">
  <br>
  <input type="hidden" name="IDF" value="' . $campo["IDF"] . '">
  Telefono:<br>
  <input type="text" name="telefono" value="' . $campo["telefono"] . '">
  <br>
  Puesto:<br>
  <input type="text" name="puesto" value="' . $campo["puesto"] . '">
  <br>
  Vehiculo:<br>
  <input type="text" name="vehiculo" value="' . $campo["vehiculo"] . '">
  <br>
  <br>
  <input type="submit" name="forma" value="Submit">
 </form>';
}
if(!isset($_GET["insert"]) && $_SESSION['Access'] <= 2){

  echo '<a href="tabla6.php?insert=1">Ingresar nuevo registro</a>';
}


$conn->close();
?> 

  </table>
    </body>
</html>
