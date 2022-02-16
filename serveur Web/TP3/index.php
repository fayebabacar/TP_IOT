<?php
	require "fonction.php";

	if(isset($_GET['valeur'])){
		enregistrer(getBD(), $_GET['valeur']);
	}
	else{
		var_dump(getData(getBD()));
	}
?>

