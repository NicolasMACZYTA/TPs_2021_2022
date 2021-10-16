import java.util.Arrays;

public class Client {
    private String nom;
    private Commande[] c;

    public Client(String nom){
        this.nom = nom;
        this.c = new Commande[];
    }

    public String getNom(){
        return this.nom;
    }

    public Commandes[] getCommandes(){
        return this.c;
    }

    public void setNom(String nom){
        this.nom = nom;
    }

    public void ajouterCommande(Commande c){
        this.c = Arrays.copyOf(this.c, this.c.length +1);
        this.c[this.c.length-1]=c;
    }

    public void retirerCommande(){
        //a finir
    }
}
