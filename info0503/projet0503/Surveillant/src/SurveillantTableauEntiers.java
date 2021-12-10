/**
 * Classe utilitaire qui surveille un tableau d'entier
 * 
 * @author Jean-Charles BOISSON 11/2021
 * 
 * @version 1.0
 * 
 */
public class SurveillantTableauEntiers extends Surveillant{

    /**
     * le tableau à surveiller
     */
    private java.util.ArrayList<Long> valeurs;

    /**
     * 
     * Constructeur d'un objet SurveillantTableauEntiers
     * 
     * @param valeurs Le tableau à surveiller
     */
    public SurveillantTableauEntiers(java.util.ArrayList<Long> valeurs) {
        super();
        
        this.valeurs=valeurs;
        
        // menu est déjà alloué dans la classe mère
        this.menu.add("Pour afficher les valeurs actuelles");
        this.menu.add("Pour ajouter une valeur aléatoire");
        this.menu.add("Pour supprimer la tête du tableau");
    }

    public void appliqueChoix(int choix) {
        switch(choix) {
            case 0 -> System.out.println("Je vais m'arrêter bye bye");
            case 1 -> System.out.println(this.valeurs);
            case 2 -> this.valeurs.add(Math.round(Math.random()*1024));
            case 3 -> this.valeurs.remove(0);
        }
    }
}