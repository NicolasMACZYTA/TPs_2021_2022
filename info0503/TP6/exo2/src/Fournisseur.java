import java.io.IOException;

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.SocketException;
import java.net.InetAddress;
import java.net.UnknownHostException;

import java.util.Scanner;

/**
 * Classe correspondant à un serveur UDP.
 * La chaine de caractères "Bonjour" est envoyée au serveur.
 * Le port d'écoute du serveur est indiqué dans la classe ServeurUDP.
 * @author Cyril Rabat
 * modifié par Nicolas MACZYTA et Lug BRUNET
 */
public class Fournisseur {

    public static int portEcoute = 9876;
    public static int portEnvoie = 9877;


    public static void main(String[] args) {
        
        System.out.print("\nCtrl + C   Pour quitter\n");
        boolean found;
        // dans l'ideal il faudrait acceder a une base de données
        String[] items = {"capot","phares","calandre","roues","volant","tableau de bord"};
        int[] quantities = {10,2,0,5,4,0};

        Scanner clavier = new Scanner(System.in);
        // Création de la socket
        DatagramSocket socket = null;
        try {        
            System.out.println("\nETAT socket : on \n\t\tport Ecoute : " + portEcoute + "\n\t\tport Envoie : " + portEnvoie);
            socket = new DatagramSocket(portEcoute);
        } catch(SocketException e) {
            System.err.println("Erreur lors de la création de la socket : " + e);
            System.exit(0);
        }

        String message = "blabla";

        while(!message.equals("end")){

            // Création du message Client
            byte[] tampon = new byte[1024];
            DatagramPacket msg = new DatagramPacket(tampon, tampon.length);

            // Lecture du message du Client
            try {
                int i;
                socket.receive(msg);
                String texte = new String(msg.getData(), 0, msg.getLength());
                System.out.println("\nMessage Usine " + texte);
                found = false;
                for(i = 0; i < items.length; i++)
                {
                    if(items[i].equals(texte))
                    {
                        found = true;
                        break;
                    }
                }
                if(found){

                    message = "article : "+items[i]+"\nQuantité disponible : "+quantities[i]+"\n";

                }
                else{

                    message = "nous ne proposons pas cet article";


                }
            } catch(IOException e) {
                System.err.println("Erreur lors de la réception du message : " + e);
                System.exit(0);
            }

            

            // Création du message Serveur
            msg = null;
            try {
                InetAddress adresse = InetAddress.getByName(null);
                byte[] tampon2 = message.getBytes();
                msg = new DatagramPacket(tampon2, tampon2.length, adresse, portEnvoie);            
            } catch(UnknownHostException e) {
                System.err.println("Erreur lors de la création du message : " + e);
                System.exit(0);
            }

            // Envoi du message Serveur
            try {
                //System.out.println("\nEnvoie du message au client : " + message);
                socket.send(msg);
            } catch(IOException e) {
                System.err.println("Erreur lors de l'envoi du message : " + e);
                System.exit(0);
            }
        }

        clavier.close();

        // Fermeture de la socket
        System.out.println("\nETAT socket : off");
        socket.close();
    }

}