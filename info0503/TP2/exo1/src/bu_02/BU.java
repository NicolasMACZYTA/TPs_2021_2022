package bu_02;

import java.util.HashMap;

/**
 * Classe représentant une BU.
 * @author Cyril Rabat & Jean-Charles BOISSON (small update in 2021-2022)
 */
public class BU {
    
    private static int compteur = 0;
    
    private HashMap<Integer,Document> documents;
    
    /**
     * Crée une médiathèque.
     */
    public BU() {
        documents = new HashMap<Integer,Document>();
    }
    
    /**
     * Ajoute un document à la médiathèque et retourne son identifiant.
     * @param d le document à ajouter
     * @return l'identifiant du document ajouté
     */
    public int ajouterDocument(Document d) {
        documents.put(compteur, d);
        return compteur++;
    }
    
    /** 
     * Retourne le ième document.
     * @param i l'indice du document
     * @return le document (ou null)
     */
    public Document getDocument(int i) {
        Document resultat = null;
        
        if(documents.containsKey(i)) {
            resultat = documents.get(i);
        }
        
        return resultat;
    }
        
    /**
     * Convertit la BU en chaîne de caractères.
     * @return une chaîne de caractères
     */
    @Override
    public String toString() {
        
        if(documents.size()==0)
            return "La BU est vide pour le moment ...";
        
        String contenu_BU="Contenu actuel de la BU :\n";

        for(int cle : documents.keySet()){
            contenu_BU+="\t"+cle+" = "+documents.get(cle).toString()+"\n";
        }

        return contenu_BU;
    }

}
