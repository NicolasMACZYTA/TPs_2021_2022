
<?php class Commande implements JsonSerializable{
    
    private String $Moteur;
    private String $Couleur;
    private String $Option;




    public function __construct($Couleur, $Option, $Moteur){
        $this->Moteur  = $Moteur;
        $this->Couleur = $Couleur;
        $this->Option  = $Option;
    }


    public function affichage():void{
        echo "Récapitulatif : <br>";
        
        echo "Motorisation : ".$this->Moteur."<br>";
        echo "Couleur : ".$this->Couleur."<br>";
        echo "Pack : ".$this->Option."<br>";
    }


    public static function from_form():Commande{

        if(isset($_POST['Valider'])){
            if(isset($_POST['Couleur'])&&isset($_POST['Options'])&&isset($_POST['Moteur'])){
                $Moteur= $_POST['Moteur'];
                $Couleur=$_POST['Couleur'];
                $Option= $_POST['Options'];
            }
            return new Commande($Couleur,$Option,$Moteur);
        }
    }

    
    public function jsonSerialize():array{
        $tab["Moteur"]=$this->Moteur;
        $tab["Couleur"]=$this->Couleur;
        $tab["Options"]=$this->Option;

        return $tab;
    }

    public static function from_json($tab):Commande{
        return new Commande($tab["Couleur"],$tab["Options"],$tab["Moteur"]);
    }


    //selection des options a regler si on a le temps

    public static function afficher_form():void{
        echo <<< form
            <form method="post" action="#">

            <h1>Configuration peugeot 406</h1>

            <h3>MOTEUR</h3>




            <div class="form-check">
                <input class="form-check-input" type="radio" name="Moteur" id="essence-1.8_XU" value="essence-1.8_XU" checked>
                <label class="form-check-label" for="essence-1.8_XU">
                essence-1.8_XU
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Moteur" id="essence-2.0_XU" value="essence-2.0_XU">
                <label class="form-check-label" for="essence-2.0_XU">
                essence-2.0_XU
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Moteur" id="turbo_essence-2.2TCT_XU" value="turbo_essence-2.2TCT_XU">
                <label class="form-check-label" for="turbo_essence-2.2TCT_XU">
                turbo_essence-2.2TCT_XU
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Moteur" id="turbo_diesel-1.9TD_XUD" value="turbo_diesel-1.9TD_XUD">
                <label class="form-check-label" for="turbo_diesel-1.9TD_XUD">
                turbo_diesel-1.9TD_XUD
                </label>
            </div>




            <h3>COULEUR</h3>





            <div class="form-check">
                <input class="form-check-input" type="radio" name="Couleur" id="Rouge" value="Rouge">
                <label class="form-check-label" for="Rouge">
                Rouge
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Couleur" id="Bleue" value="Bleue">
                <label class="form-check-label" for="Bleue">
                Bleue
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Couleur" id="Gris" value="Gris" checked>
                <label class="form-check-label" for="Gris">
                Gris
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Couleur" id="Noir" value="Noir">
                <label class="form-check-label" for="Noir">
                Noir
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Couleur" id="Vert" value="Vert">
                <label class="form-check-label" for="Vert">
                Vert
                </label>
            </div>
            
            



            <h3>OPTION</h3>





            <div class="form-check">
                <input class="form-check-input" type="radio" name="Options" id="pack_normal" value="pack_normal" checked>
                <label class="form-check-label" for="pack_normal">
                pack_normal
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Options" id="pack_confort" value="pack_confort">
                <label class="form-check-label" for="pack_confort">
                pack_confort
                </label>
            </div>
            <div class="form-check">
                <input class="form-check-input" type="radio" name="Options" id="pack_sport" value="pack_sport">
                <label class="form-check-label" for="pack_sport">
                pack_sport
                </label>
            </div>
            <br>


            
            <button type="submit" name="Valider" class="btn btn-primary">Valider</button>
        </form>
    form;
    }

   
    public function __toString():String{
        return $this->Couleur.";".$this->Option.";".$this->Moteur;
    }
}