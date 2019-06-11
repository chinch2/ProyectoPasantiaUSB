<!DOCTYPE HTML>
<html> 
	<head> 
		<title>Pagina de inicio</title> 
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"> 
	</head> 
		<body> 
		<form id="formu" action="validate.php" method="post">
		 Inicia Sesion
		<br><br> Usuario: <input type="text" id="user" name="user" value="Usuario" onclick="if(this.value=='Usuario') this.value=''" onblur="if(this.value=='') this.value='Usuario'" />
		<br><br> Clave: <input type="password" id="pass" name="pass" value="Clave" onclick="if(this.value=='Clave') this.value=''" onblur="if(this.value=='') this.value='Clave'" />
		<br><br> <input type="submit" value="Entrar"> </form>
		</body> 
</html>
