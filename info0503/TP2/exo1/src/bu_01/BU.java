package bu_01;

import java.util.HashMap;

/**
 * Classe représentant une BU.
 * @author Cyril Rabat & Jean-Charles BOISSON (2021-2022 small update)
 */
public class BU {
    
    private static int compteur = 0;
    
    private HashMap<Integer,Livre> livres;
    
    /**
     * Crée une BU.
     */
    public BU() {
        livres = new HashMap<Integer,Livre>();
    }
    
    /**
     * Ajoute un livre à la BU et retourne son identifiant.
     * @param l le livre à ajouter
     * @return l'identifiant du livre ajouté
     */
    public int ajouterLivre(Livre l) {
        livres.put(compteur, l);

        // La valeur est bien renvoyée avant d'être incrémentée localement.
        return compteur++;
    }
    
    /** 
     * Retourne le ième livre.
     * @param i l'indice du livre
     * @return le livre (ou null)
     */
    public Livre getLivre(int i) {
        Livre resultat = null;
        
        if(livres.containsKey(i)) {
            resultat = livres.get(i);
        }
        
        return resultat;  
    }

    /**
     * Convertit la BU en chaîne de caractères.
     * @return une chaîne de caractères
     */
    @Override
    public String toString() {
        
        if(livres.size()==0)
            return "La BU est vide pour le moment ...";
        
        String contenu_BU="Contenu actuel de la BU :\n";

        for(int cle : livres.keySet()){
            contenu_BU+="\t"+cle+" = "+livres.get(cle).toString()+"\n";
        }

        return contenu_BU;
    }
        
}