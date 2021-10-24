import Voitures.Voiture;
import org.json.JSONObject;
import org.json.JSONArray;

public class Parking {
    private static int id;
    private int idparking;
    private Place[][] places;
    private int length, width; //length = ranger, width = numero

    /*public Parking(){
		Parking.id++;
        this.nParking = id;
		this.length=3;
		this.width=10;
		this.places = new Place[length][width];
	}*/

    public Parking(int idparking, int length, int width){
        this.idparking = idparking;
        this.length = length;
        this.width = width;
        this.places = new Place[length][width];
    }

    public Parking(int length, int width){
        Parking.id++;
        this.idparking = id;
        this.length = length;
        this.width = width;
        this.places = new Place[length][width];
    }

    public void stockerVoiture(Voiture v, char i, int j){
        places[Integer.valueOf(i)][j]= new Place(i,j);
        places[Integer.valueOf(i)][j].setVoiture(v);
    }

    public Voiture getVoiture(char i, int j){
        return places[Integer.valueOf(i)][j].getVoiture();
    }

    public void libererPlace(int i, int j){
		this.places[i][j] = null;
	}

    public JSONObject toJSON(){
		JSONObject json= new JSONObject();
		
		json.put("idparking",this.idparking);
        json.put("length",this.length);
        json.put("width",this.width);
		for(int i=0;i<length;i++){
            for(int j=0;j<width;j++){
			    json.put("places",this.places[i]);
            }
		}

		return json;
	}

	public static Parking fromJSON(String source){
		JSONObject parkingJson = new JSONObject(source);

		int idparking = parkingJson.getInt("idparking");
        int length = parkingJson.getInt("length");
        int width = parkingJson.getInt("width");
		JSONArray place = parkingJson.getJSONArray("places");

		return new Parking(idparking,length,width);
	}

}
