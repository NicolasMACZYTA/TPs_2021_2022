package TD_java;

public class TestCompteur {
    public static void main(String[] args) {
        Compteur c = new Compteur();
        /* 


        ManipCompteur mc1 = new ManipCompteur(c);
        ManipCompteur mc2 = new ManipCompteur(c);

        mc1.start();
        mc2.start();
        */

        Thread mc1 = new Thread(new ManipCompteur(c));
        Thread mc2 = new Thread(new ManipCompteur(c));

        mc1.start();
        mc2.start();
    }
}
