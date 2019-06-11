<!DOCTYPE HTML>
<?php

session_start();
if(@!$_SESSION['Usuario']){
        header("location:login.php");
}
if($_SESSION['Usuario']!='admin'){
	header("Location:logout.php");
}

?>

<!DOCTYPE HTML>
<html>
    <head>
        <title>Desarrollos PNP | Dash Text</title>
    </head>
    <body>
Tabla de usuarios
        <?php
        include("conn.php");

        if(isset($_GET["del"])){

          $sql = "DELETE FROM sistema.usuarios WHERE UserID = '".$_GET["id"]."';";

          if ($conn->query($sql) === TRUE) {

          $last_id = $conn->insert_id;

          $_GET["id"] = $last_id;

          } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
            }
        unset($_GET["del"]);

        }

        if(isset($_GET["insert"])){

        $sql = "INSERT INTO usuarios (Usuario, Clave, Niveldeacceso) VALUES ('supervisor', '240295', 0);";

          if ($conn->query($sql) === TRUE) {

          $last_id = $conn->insert_id;

          $_GET["id"] = $last_id;

          } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
            }
      }
 
        if(isset($_POST["forma"])){
            $sql = "UPDATE sistema.usuarios SET Usuario = '{$_POST["Usuario"]}', Clave = '{$_POST["Clave"]}', Niveldeacceso = '{$_POST["Niveldeacceso"]}' WHERE UserID = '{$_POST["UserID"]}';";
            if($conn->query($sql)===TRUE){
            	unset($_GET["id"]);
	    }else{
			echo "Error: " . $sql . "<br>" . $conn->error;
	 	 } 
        }
        ?>
  <a href="index.php">Inicio</a>
  <table border="1">
     <tr>
          <th>Usuario</th>
          <th>Clave</th>
          <th>Nivel de acceso</th>
      </tr>
<?php
$sql = "SELECT * FROM sistema.usuarios";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
        while($row = $result-> fetch_assoc()){
                echo "<tr><td>{$row["Usuario"]}</td><td>{$row["Clave"]}</td><td>{$row["Niveldeacceso"]}</td>";
                if($_SESSION['Access']==1){
                        echo "<td><a href=\"tabla5.php?id={$row["UserID"]}\">Modificar</a></td><td><a href=\"tabla5.php?id={$row["UserID"]}&del=1\">Eliminar</a></td></tr>";
                }else{
                echo "</tr>";
                }

                if($_GET["id"]==$row["UserID"]){
                        $campo = $row;
                }
        }
}else{
  echo "0 results <br><br>";
}

echo "</table><br><br>";

if(count($campo)){
    echo '<form action= "tabla5.php" method="post">
 Usuario:<br>
  <input type="text" name="Usuario" value="' . $campo["Usuario"] . '">
  <br>
  <input type="hidden" name="UserID" value="' . $campo["UserID"] . '">
  Clave:<br>
  <input type="password" name="Clave" value="' . $campo["Clave"] . '">
  <br>
  Nivel de acceso:
  <input type="text" name="Niveldeacceso" value="' . $campo["Niveldeacceso"] . '">
  <br>
  <input type="submit" name="forma" value="Submit">
 </form>';
}
if(!isset($_GET["insert"]) && $_SESSION['Access']==1){

  echo '<a href="tabla5.php?insert=1">Ingresar nuevo registro</a>';
}


$conn->close();
?> 

  </table>
    </body>
</html>

