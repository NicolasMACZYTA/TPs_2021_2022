import java.util.Date;

public class Commande {
    private int id;
    private Modele modele;
    private Option[] options;
    private String couleur;
    private Moteur moteur;
    private Date date;

    public Commande(int id, Modele modele, Option[] options, String couleur, Moteur moteur){
        this.date = date.getTime();
        this.id = id;
        this.modele = modele;
        this.options = options;
        this.couleur = couleur;
        this.moteur = moteur;
    }

    public int getID(){
        return this.id;
    }

    public Modele getModele(){
        return this.modele;
    }

    public Option[] getOptions(){
        return this.options;
    }

    public String getCouleur(){
        return this.couleur;
    }

    public Moteur getMoteur(){
        return this.moteur;
    }

    public Date getDate(){
        return this.date;
    }

}
