package bu_02;

/**
 * Classe représentant une personne.
 * @author Cyril Rabat
 */
public class Personne {

    private String nom;
    private String dateNaissance;
   
    /**
     * Crée une personne avec un nom et une date de naissance.
     * @param nom le nom
     * @param dateNaissance la date de naissance
     */
    public Personne(String nom, String dateNaissance) {
        this.nom = nom;
        this.dateNaissance = dateNaissance;
    }
    
    /**
     * Retourne le nom.
     * @return le nom
     */
    public String getNom() {
        return nom;
    }
    
    /**
     * Retourne la date de naissance.
     * @return la date de naissance
     */
    public String dateNaissance() {
        return dateNaissance;
    }
    
    /**
     * Convertit la personne en chaîne de caractères.
     * @return une chaîne de caractères
     */
    @Override
    public String toString() {
        return nom + ", " + dateNaissance;
    }

}
