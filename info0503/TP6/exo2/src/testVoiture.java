import Voitures.*;
import java.util.*;
import org.json.JSONObject;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
 

public class testVoiture {
    public static void main(String [] args){
        Moteur[] tMoteur = {new Moteur("XUD","diesel",90), new Moteur("XU","essence",92), new Moteur("PRV_REV2","essence",205)};
        String[] couleurs = {"vert anglais","gris métallisé", "noir laqué"};
        Option[] options = {new Option("climatisation", "climatisation"), new Option("pack confort", "sieges velours baguettes en ronce de noyer"), new Option("autoradio CD", "autoradio CD") };
        //Usine u = new Usine("JJLand", 1, 250, 250);
        Modele modele = new Modele("406 berline");
        modele.setCouleurs(couleurs);
        modele.setMoteurs(tMoteur);
        modele.setOptions(options);
        Voiture v2;
        Voiture v1 = new Voiture("AHJKDY05462JHSDF", modele, modele.getMoteurs()[0], modele.getCouleurs()[1], modele.getOptions(),"04/01/1995");

        System.out.println(v1.toString());
        System.out.println("\n stockage : ");
        //u.stockerVoiture(v1, 'A', 1);
        //v2 = u.parking.getVoiture('A', 1);
        //System.out.println(v2.toString());

        //TEST JSON
        System.out.println("Usine\n");
        System.out.println(new JSONObject(v1));

        String str = ""+new JSONObject(v1);

            File file = new File("data1.txt");
             
            String data = str;
             
            try(FileOutputStream fos = new FileOutputStream(file);
                    BufferedOutputStream bos = new BufferedOutputStream(fos)) {
                byte[] bytes = data.getBytes();
                bos.write(bytes);
                bos.close();
                fos.close();
                System.out.print("fichier écrit dans le fichier avec succès.");
            } catch (IOException e) {
                e.printStackTrace();
            }
        
    }
}
