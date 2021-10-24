import bu_01.*;
public class testbu {
    public static void main(String[] args) {

        Auteur auteur = new Auteur("Nicolas SARKOZY", "1955");
        System.out.println(auteur);
        Livre livre = new Livre("le temps des tempêtes", auteur);
        System.out.println(livre);

        Auteur auteur2=Auteur.fromJSON(auteur.toJson().toString());
        System.out.println(auteur2);

    }

    
}