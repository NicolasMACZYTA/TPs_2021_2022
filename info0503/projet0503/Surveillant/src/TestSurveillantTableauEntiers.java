/**
 * Test de la classe SurveillantTableauEntiers
 * 
 * @author Jean-Charles BOISSON 11/2021
 * 
 * @version 1.0
 * 
 */
public class TestSurveillantTableauEntiers {
    /**
     * Code de test : crée un tableau d'entier et le confie au surveillant
     * 
     * @param args Les arguments de la ligne de commande
     */
    public static void main(String[] args) {
        
        //Un petit tableau de 10 valeurs
        var tab=new java.util.ArrayList<Long>();
        for(int i=0;i<10;i++) {
            tab.add(Math.round(Math.random()*1024));
        }

        var thread = new Thread(new SurveillantTableauEntiers(tab));

        // Dès que mon Thread démarre, le reste du code fonctionne indépendemment
        thread.start();

        // Le thread principal va ajouter une valeur au tableau
        // toutes les secondes pendant 30s
        for(int i=0;i<30;i++) {
        
            try {Thread.sleep(1000);}catch(InterruptedException ie){}
            
            tab.add(Math.round(Math.random()*1024));
        }
    }
}
