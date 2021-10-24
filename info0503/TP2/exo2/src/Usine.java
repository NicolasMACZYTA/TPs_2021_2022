import Voitures.Voiture;
import org.json.JSONObject;

public class Usine {
    private String nomUsine;
    public Parking parking;

    public Usine(){
        this.nomUsine = "Usine Non Defini";
        this.parking = new Parking(5,10); //Un petit parking predefini
    }

    public Usine(String nom, int idparking, int i, int j){
        this.nomUsine = nom;
        this.parking = new Parking(idparking,i,j);
    }

    public Usine(String nom, Parking parking){
        this.nomUsine = nom;
        this.parking = parking;
    }

    public String getNom(){
        return this.nomUsine;
    }
    
    public void stockerVoiture(Voiture v, char i, int j){
        parking.stockerVoiture(v, i, j);
    }

    public void enleverVoiture(char i, int j){
        parking.libererPlace(i, j);
    }

    public JSONObject toJSON(){
		JSONObject json = new JSONObject();

		json.put("nomUsine",this.nomUsine);
		json.put("parking",this.parking.toJSON());
		
		return json;
	}

	public static Usine fromJSON(String source){
		JSONObject usineJson = new JSONObject(source);

        String nomUsine = usineJson.getString("nomUsine");
		JSONObject parking = usineJson.getJSONObject("parking");
		
		return new Usine(nomUsine, Parking.fromJSON(parking.toString()));
	}
}
