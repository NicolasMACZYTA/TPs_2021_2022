package Voitures;
import org.json.JSONObject;

public class Voiture {

    private String VIN;
    private Modele modele;
    private Moteur moteur;
    private String couleur;
    private Option[] options;
    private String dateFabrication;

    public Voiture(String VIN, Modele modele, Moteur moteur, String couleur, Option[] options, String dateFabrication){
        this.VIN=VIN;
        this.modele=modele;
        this.moteur=moteur;
        this.couleur=couleur;
        this.options=options;
        this.dateFabrication=dateFabrication;
    }

    public String getID(){
        return this.VIN;
    }

    public String getDate(){
        return this.dateFabrication;
    }

    public Modele getModele(){
        return this.modele;
    }

    public Moteur gMoteur(){
        return this.moteur;
    }

    public String getCouleur(){
        return this.couleur;
    }

    public Option[] getOptions(){
        return this.options;
    }

    public void setCouleur(String couleur){
        this.couleur=couleur;
    }

    public String toString(){
        return "Voiture : ID : "+this.VIN+" modele : "+this.modele.getNom()+this.moteur.toString()+" couleur : "+this.couleur;
    }

    /*public JSONObject toJSON(){
		JSONObject json = new JSONObject();
		json.put("VIN",this.VIN);
		json.put("modele",this.modele);
		json.put("moteur",this.moteur.toJSON());
		json.put("couleur",this.couleur.toJSON());
		json.put("options",this.options.toJSON());
		json.put("dateFabrication",this.dateFabrication);

		return json;
	}*/

	/*public static Voiture fromJSON(String source){
		JSONObject voitureJson = new JSONObject(source);
		
		String VIN = voitureJson.getInt("VIN");
		Moteur moteur = voitureJson.?("moteur");
		Couleur couleur = voitureJson.?("couleur");
		Options options = voitureJson.?("options");
		int dateFabrication = voitureJson.getInt("dateFabrication");
		
		return new Voiture(...);
	}*/
}
