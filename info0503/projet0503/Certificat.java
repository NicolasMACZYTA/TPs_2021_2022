import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.PublicKey;
import java.security.Signature;

import org.json.JSONObject;

public class Certificat {
    private String nomMachine;
    private String ipMachine;
    private String clePublique;
    private String nomAutorite;
    private String adresseAutorite;
    private Signature signature;

    public Certificat(
        String nomMachine, 
        String ipMachine, 
        String clePublique, 
        String nomAutorite,
        String adresseAutorite, 
        Signature signature
    ) {
        this.nomMachine = nomMachine;
        this.ipMachine = ipMachine;
        this.clePublique = clePublique;
        this.nomAutorite = nomAutorite;
        this.adresseAutorite = adresseAutorite;
        this.signature = signature;
    }

    public Certificat(
        String nomMachine, 
        String ipMachine, 
        String clePublique, 
        String nomAutorite,
        String adresseAutorite
    ) {
        this.nomMachine = nomMachine;
        this.ipMachine = ipMachine;
        this.clePublique = clePublique;
        this.nomAutorite = nomAutorite;
        this.adresseAutorite = adresseAutorite;
    }

    public String getNomMachine() {
        return nomMachine;
    }

    public String getIpMachine() {
        return ipMachine;
    }

    public JSONObject toJson(){
        JSONObject res = new JSONObject();

        return res;
    }

    public static Certificat fromJson(JSONObject json){
        if(json.has("signature")){
            return new Certificat(
                json.getString("nomMachine"), 
                json.getString("ipMachine"), 
                json.getString("clePublique"), 
                json.getString("nomAutorite"), 
                json.getString("adresseAutorite"), 
                json.get("signature")
            );
        }
        else{
            return new Certificat(
                json.getString("nomMachine"), 
                json.getString("ipMachine"), 
                json.getString("clePublique"), 
                json.getString("nomAutorite"), 
                json.getString("adresseAutorite")
            );
        }
    }

    public void generateSignature(){
        try {
            signature = Signature.getInstance("SHA256withRSA");
        } catch(NoSuchAlgorithmException e) {
            System.err.println("Erreur lors de l'initialisation de la signature : " + e);
            System.exit(0);
        }

        try { 
            signature.initSign();
        } catch(InvalidKeyException e) {
            System.err.println("Clé privée invalide : " + e);
            System.exit(0);
        }

    }

    public boolean checkSignature(){

        return true;
    }
    
}