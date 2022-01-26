package TD_java;

public class ManipCompteur extends Thread{
    private Compteur compteur;

    public ManipCompteur(Compteur c){
        compteur = c;
    }
    public void run(){
        for(int i =0;i<10000;i++){
            compteur.increment();
        }
        System.out.println(compteur.getVal());
    }
}
