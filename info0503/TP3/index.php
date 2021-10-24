<?php

spl_autoload_register(function($class_name){
    include $class_name . '.php';
});

$etu = new Etudiant("Jean","Paul","007","SpaceChem","AVoir");
$etuJSON = json_encode($etu);
echo $etuJSON;
echo "</br>";
var_dump(json_decode($etuJson));
echo "</br>";
var_dump(json_decode($etuJson,true));

//$etu2 = new Etudiant("Bob","Bob","285361","Fraise","Oui");

?>