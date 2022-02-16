<?php
	if(isset($_POST['valeur'])){
		$valeur = $_POST['valeur'];
		$capteur= $_POST['capteur'];
		$req = "INSERT INTO test(capteur, valeur) VALUES(:capteur,:data);";
		$bdd = getBD();
		$cursor = $bdd->prepare($req);
		$cursor->execute(
			array(
				":data" => $valeur,
				":capteur" => $capteur
				)
			);
		echo "enregistrement termine";
		
	}
	else {
	$bdd = getBD();
		if($bdd != null){
			$req = "SELECT * FROM test;";
			$cursor = $bdd->prepare($req);
			$cursor->execute();
			while($data=$cursor->fetch())//all(PDO::FETCH_NUM);
			{
				echo "".$data['id']." ".$data['capteur']." ".$data['valeur']."<br>";
 			}
		}


	}



function getBD(){
	$req_con = "mysql:host=localhost;port=8889;dbname=tp_arduino_wifi"; //requete de connexion
		try{
			$bdd = new PDO($req_con, "root", "root"); //


		}catch(Exception $e){
			$bdd = null;
			echo "echec connexion au serveur mysql";
		}
	return $bdd;
}
?>