package Voitures;

public class Modele {

    private String nomModele;
    private Option options[];
    private String couleurs[];
    private Moteur moteurs[];

    public Modele(String nomModele){
        this.nomModele = nomModele;
    }

    public void setCouleurs(String couleurs[]){
        this.couleurs = couleurs;
    }

    public void setOptions(Option[] options){
        this.options = options;
    }

    public void setMoteurs(Moteur[] moteurs){
        this.moteurs = moteurs;
    }

    public Option[] getOptions(){
        return this.options;
    }

    public String[] getCouleurs(){
        return this.couleurs;
    }

    public Moteur[] getMoteurs(){
        return this.moteurs;
    }
    public String getNom(){
        return this.nomModele;
    }
}
