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
Tabla de tarifas
        <?php
        include("conn.php");

        if(isset($_GET["del"])){

          $sql = "DELETE FROM sistema.tarifas WHERE codigo = '".$_GET["id"]."';";

          if ($conn->query($sql) === TRUE) {
          
          $last_id = $conn->insert_id;

          $_GET["id"] = $last_id;

          } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
            }
        unset($_GET["del"]);

        }

        if(isset($_GET["insert"])){

        $sql = "INSERT INTO tarifas (preciohora1, tiempohora1, preciohora2, tiempohora2, preciohora3) VALUES (0, 0, 0, 0, 0);";

          if ($conn->query($sql) === TRUE) {
          
          $last_id = $conn->insert_id;

          $_GET["id"] = $last_id;

          } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
            }
      }
 
        if(isset($_POST["forma"])){
            $sql = "UPDATE sistema.tarifas SET  preciohora1 = '{$_POST["preciohora1"]}', tiempohora1 = '{$_POST["tiempohora1"]}', preciohora2 = '{$_POST["preciohora2"]}', tiempohora2 = '{$_POST["tiempohora2"]}', preciohora3 = '{$_POST["preciohora3"]}', PHP = '{$_POST["PHP"]}' WHERE codigo = '{$_POST["codigo"]}';";
            $result = $conn->query($sql);
            unset($_GET["id"]);
        }
        ?>
  <a href="index.php">Inicio</a>
  <table border="1">
     <tr>
	  <th>Tarifa</th>
          <th>Precio por hora 1</th>
          <th>Duracion 1 </th>
          <th>Precio por hora 2</th>
          <th>Duracion 2</th>
          <th>Precio por hora 3</th>
          <th>Codigo auxiliar</th>
      </tr>
<?php
$sql = "SELECT * FROM sistema.tarifas";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
	while($row = $result-> fetch_assoc()){
  		echo "<tr><td>{$row["codigo"]}</td><td>{$row["preciohora1"]}</td><td>{$row["tiempohora1"]}</td><td>{$row["preciohora2"]}</td><td>{$row["tiempohora2"]}</td><td>{$row["preciohora3"]}</td><td>{$row["PHP"]}</td>";
		if($_SESSION['Access']==1){
			echo "<td><a href=\"tabla3.php?id={$row["codigo"]}\">Modificar</a></td><td><a href=\"tabla3.php?id={$row["codigo"]}&del=1\">Eliminar</a></td></tr>";
		}else{
		echo "</tr>";
		}

		if($_GET["id"]==$row["codigo"]){
        		$campo = $row;
    		}
	}
}else{
  echo "0 results <br><br>";
}

echo "</table><br><br>";

if(count($campo)){
    echo '<form action= "tabla3.php" method="post">
  Precio por hora 1:<br>
  <input type="text" name="preciohora1" value="' . $campo["preciohora1"] . '">
  <br>
  Duracion 1:<br>
  <input type="text" name="tiempohora1" value="' . $campo["tiempohora1"] . '">
  <br>
  <input type="hidden" name="codigo" value="' . $campo["codigo"] . '">
  Precio por hora 2:<br>
  <input type="text" name="preciohora2" value="' . $campo["preciohora2"] . '">
  <br>
  Duracion 2:<br>
  <input type="text" name="tiempohora2" value="' . $campo["tiempohora2"] . '">
  <br>
  Precio por hora 3:<br>
  <input type="text" name="preciohora3" value="' . $campo["preciohora3"] . '">
  <br>
  <textarea name="PHP" rows="4" cols="50" value="' . $campo["PHP"] . '">
</textarea>
   <br>
  <input type="submit" name="forma" value="Submit">
 </form>';
}
if(!isset($_GET["insert"]) && $_SESSION['Access']==1){

  echo '<a href="tabla3.php?insert=1">Ingresar nuevo registro</a>';
}


$conn->close();
?> 

  </table>
    </body>
</html>
