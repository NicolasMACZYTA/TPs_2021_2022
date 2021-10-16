import Voitures.Voiture;
public class Parking {
    private int nParking;
    private Place[][] places;

    public Parking(int nParking, int lenght, int width){
        this.nParking=nParking;
        this.places = new Place[lenght][width];
    }

    public void stocker(Voiture v, char i, int j){
        places[Integer.valueOf(i)][j]= new Place(i,j);
        places[Integer.valueOf(i)][j].setVoiture(v);
    }
}
