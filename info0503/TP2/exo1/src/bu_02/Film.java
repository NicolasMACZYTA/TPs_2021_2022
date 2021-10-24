package bu_02;

/**
 * Classe représentant un film.
 * @author Cyril Rabat
 */
public class Film extends Document {
    
    /** le réalisateur du film */
    private Personne realisateur;

    /** durée en minutes */
    private int duree;
    
    /**
     * Crée un film.
     * @param titre le titre
     * @param realisateur le réalisateur
     * @param duree la durée du film
     */
    public Film(String titre, Personne realisateur, int duree) {
        super(titre);
        this.realisateur = realisateur;
        this.duree = duree;
    }

    /**
     * Retourne le réalisateur.
     * @return le réalisateur
     */
    public Personne getRealisateur() {
        return realisateur;
    }

    /**
     * Retourne la durée.
     * @return la durée
     */
    public int getDuree() {
        return duree;
    }
    
    /**
     * Convertit le film en chaîne de caractères.
     * @return une chaîne de caractères
     */
    @Override
    public String toString() {
        return super.toString() + " (" + realisateur + ", " + duree + " minutes)";
    }
    
}
