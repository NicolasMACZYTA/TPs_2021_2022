<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>Commande</title>
    </head>
    <body>
        <?php 
        
            include 'Commande.php';

            Commande::afficher_form();
            $commande = Commande::from_form();
            echo "<br> <br> <br>";
            $commande->affichage();


            
            echo "<br>affichage json brut : <br>";


            $commande_json = json_encode($commande);
            echo "<br>".$commande_json."<br>";
            var_dump(json_decode($commande_json,true));

            //affichage brut pour debug
            echo "<br><br>affichage json décodé : <br>";
            $valeurs_commande= Commande::from_json(json_decode($commande_json,true));
            echo "<br>".$valeurs_commande->__toString();

                
        ?>
    </body>