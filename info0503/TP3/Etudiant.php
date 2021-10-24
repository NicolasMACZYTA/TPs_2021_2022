<?php

class Etudiant{
    public function __construct($nom,$prenom,$num,$etablissement,$diplome){
        $this->nom = $nom;
        $this->prenom = $prenom;
        $this->num = $num;
        $this->etablissement = $etablissement;
        $this->diplome = $diplome;
    }

    public function jsonSerialize(){
        $json["nom"] = $this->nom;
        $json["prenom"] = $this->prenom;
        $json["num"] = $this->num;
        $json["etablissement"] = $this->etablissement;
        $json["diplome"] = $this->diplome;

        return $json;
    }

    public function __toString(){
        return "Nom: $this->nom
        </br>Prenom: $this->prenom
        </br>Numero: $this->num
        </br>Etablissement: $this->etablissement
        </br>Diplome: $this->diplome";
    }
}

?>