package Voitures;


public class Voiture {

    private String VIN;
    private Modele modele;
    private Moteur moteur;
    private String couleur;
    private Option[] options;
    private String dateFabrication;

    public Voiture(String VIN, Modele modele, Moteur moteur, String couleur, Option[] options, String dateFabrication){
        this.VIN=VIN;
        this.modele=modele;
        this.moteur=moteur;
        this.couleur=couleur;
        this.options=options;
        this.dateFabrication=dateFabrication;
    }

    public String getID(){
        return this.VIN;
    }

    public String getDate(){
        return this.dateFabrication;
    }

    public Modele getModele(){
        return this.modele;
    }

    public Moteur gMoteur(){
        return this.moteur;
    }

    public String getCouleur(){
        return this.couleur;
    }

    public Option[] getOptions(){
        return this.options;
    }

    public void setCouleur(String couleur){
        this.couleur=couleur;
    }

    public String toString(){
        return "Voiture : ID : "+this.VIN+" modele : "+this.modele.getNom()+this.moteur.toString()+" couleur : "+this.couleur;
    }
}
