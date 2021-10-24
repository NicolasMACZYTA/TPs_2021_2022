import Voitures.Voiture;
public class Parking {
    private int nParking;
    private Place[][] places;

    public Parking(int nParking, int lenght, int width){
        this.nParking = nParking;
        this.places = new Place[lenght][width];
    }

    public void stockerVoiture(Voiture v, char i, int j){
        places[Integer.valueOf(i)][j]= new Place(i,j);
        places[Integer.valueOf(i)][j].setVoiture(v);
    }

    public Voiture getVoiture(char i, int j){
        return places[Integer.valueOf(i)][j].getVoiture();
    }
}
