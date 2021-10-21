import Voitures.Voiture;

public class Place {
    private char rangee;
    private int num;
    private Voiture voiture;

    public Place(char rangee, int num){
        this.rangee = rangee;
        this.num = num;
    }

    public char getRangee(){
        return this.rangee;
    }

    public int getNumero(){
        return this.num;
    }

    public void setVoiture(Voiture v){
        this.voiture = v;
    }

    public Voiture getVoiture(){
        return this.voiture;
    }
}
