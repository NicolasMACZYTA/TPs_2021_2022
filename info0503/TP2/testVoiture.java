import Voitures.*;


public class testVoiture {

    
    
    public static void main(String [] args){
        Moteur[] tMoteur = {new Moteur("XUD","diesel",90), new Moteur("XU","essence",92), new Moteur("PRV_REV2","essence",205)};
        String[] couleurs = {"vert anglais","gris métallisé", "noir laqué"};
        Option[] options = {new Option("climatisation", "climatisation"), new Option("pack confort", "sieges velours baguettes en ronce de noyer"), new Option("autoradio CD", "autoradio CD") };

        Modele modele = new Modele("406 berline");
        modele.setCouleurs(couleurs);
        modele.setMoteurs(tMoteur);
        modele.setOptions(options);

        Voiture v1 = new Voiture("AHJKDY05462JHSDF", modele, modele.getMoteurs()[0], modele.getCouleurs()[1], modele.getOptions(),"04/01/1995");

        System.out.println(v1.toString());

    }
}
