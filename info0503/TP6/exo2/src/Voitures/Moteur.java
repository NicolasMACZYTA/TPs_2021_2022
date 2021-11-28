package Voitures;

public class Moteur {
    
    private String idMoteur;
    private String Carburation;
    private int puissance;

    public Moteur(String id, String carburation, int puissance){
        this.idMoteur=id;
        this.Carburation = carburation;
        this.puissance = puissance;
    }

    public String getID(){
        return this.idMoteur;
    }

    public String getCarburation(){
        return this.Carburation;
    }

    public int getPuissance(){
        return this.puissance;
    }

    public String toString(){
        return "ID moteur  : "+this.idMoteur+" carburation : "+this.Carburation+" puissance (BHP) : "+this.puissance;
    }
}
