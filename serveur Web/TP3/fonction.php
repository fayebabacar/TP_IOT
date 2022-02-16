 <?php

function getBD(){
	$basename = "tp_arduino_wifi";
	$username = "root";
	$password = "root";

	$req_con = "mysql:host=localhost;dbname=" . $basename . ""; //requete de connexion
	try{
		$bdd = new PDO($req_con, $username, $password); //
		
	}catch(Exception $e){
		$bdd = null;
		echo "echec connexion au serveur mysql";
	}
	return $bdd; //retourne la connexion a la bd ou null
}

function enregistrer($bdd, $data)
{
	if($bdd != null){
		$req = "INSERT INTO test(capteur, valeur) VALUES('test',:data);";
		$cursor = $bdd->prepare($req);
		$cursor->execute(array(":data" => $data));
		echo "enregistrement termine";
	}
}

function getData($bdd){
	if($bdd != null){
		$req = "SELECT * FROM test;";
		$cursor = $bdd->prepare($req);
		$cursor->execute();
		return $cursor->fetchall(PDO::FETCH_NUM);
	}
}

?>