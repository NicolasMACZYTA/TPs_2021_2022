import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import Voitures.*;
import java.net.Socket;
import java.net.UnknownHostException;

import org.json.JSONObject;


/**
 * @author Cyril Rabat
 * Modifié par Nicolas MACZYTA et Lug Brunet
 */
public class Usine {
    
    public static final int portEcoute = 5101;

    public static void main(String[] args) {
        Moteur[] tMoteur = {new Moteur("XUD","diesel",90), new Moteur("XU","essence",92), new Moteur("PRV_REV2","essence",205)};
        String[] couleurs = {"vert anglais","gris métallisé", "noir laqué"};
        Option[] options = {new Option("climatisation", "climatisation"), new Option("pack confort", "sieges velours baguettes en ronce de noyer"), new Option("autoradio CD", "autoradio CD") };
        Modele modele = new Modele("406 berline");
        modele.setCouleurs(couleurs);
        modele.setMoteurs(tMoteur);
        modele.setOptions(options);



        // Création de la socket
        Socket socket = null;
        try {
            socket = new Socket("localhost", portEcoute);
        } catch(UnknownHostException e) {
            System.err.println("Erreur sur l'hôte : " + e);
            System.exit(0);
        } catch(IOException e) {
            System.err.println("Création de la socket impossible : " + e);
            System.exit(0);
        }

        // Association d'un flux d'entrée et de sortie
        BufferedReader input = null;
        PrintWriter output = null;
        try {
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
        } catch(IOException e) {
            System.err.println("Association des flux impossible : " + e);
            System.exit(0);
        }

        // Envoi de du premier message
        String message = "Usine en attente de commande :";
        System.out.println("Envoi: " + message);
        output.println(message);

        // Lecture de la commande
        try {
            message = input.readLine();
        } catch(IOException e) {
            System.err.println("Erreur lors de la lecture : " + e);
            System.exit(0);
        }
        System.out.println("Lu: " + message);

        // Envoi des voitures construites

        //TODO : construction de plusieurs objets voiture

        Voiture v1 = new Voiture("AHJKDY05462JHSDF", modele, modele.getMoteurs()[0], modele.getCouleurs()[1], modele.getOptions(),"04/01/1995");
        
        message = ""+new JSONObject(v1);
        System.out.println("Envoi: " + message);
        output.println(message);

        // Lecture de la confirmation
        try {
            message = input.readLine();
        } catch(IOException e) {
            System.err.println("Erreur lors de la lecture : " + e);
            System.exit(0);
        }
        System.out.println("Lu: " + message);

        // Fermeture des flux et de la socket
        try {
            input.close();
            output.close();
            socket.close();
        } catch(IOException e) {
            System.err.println("Erreur lors de la fermeture des flux et de la socket : " + e);
            System.exit(0);
        }
    }

}