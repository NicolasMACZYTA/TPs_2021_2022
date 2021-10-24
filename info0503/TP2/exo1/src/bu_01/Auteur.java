package bu_01;
import org.json.JSONObject;

/**
 * Classe représentant un auteur de livre.
 * @author Cyril Rabat
 */
public class Auteur {

    private String nom;
    private String dateNaissance;
   
    /**
     * Crée un auteur avec un nom et une date de naissance.
     * @param nom le nom
     * @param dateNaissance la date de naissance
     */
    public Auteur(String nom, String dateNaissance) {
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
     * Convertit l'auteur en chaîne de caractères.
     * @return une chaîne de caractères
     */
    @Override
    public String toString() {
        return nom + ", " + dateNaissance;
    }

    public JSONObject toJson(){
        var json = new JSONObject();
        json.put("nomComplet",this.nom);
        json.put("date de naissance",this.dateNaissance);
        return json;
    }
    public static Auteur fromJSON(String json){
        var JSONObject = new JSONObject(json);
        String nom=JSONObject.getString("nomComplet");
        String dateNaissance=JSONObject.getString("date de naissance");
        return new Auteur(nom, dateNaissance);
    }
}