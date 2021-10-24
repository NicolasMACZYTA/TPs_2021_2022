import Voitures.Voiture;
public class Usine {
    public Parking parking;
    public Usine(int nparking, int i,int j){
        this.parking = new Parking(nparking,i,j);
    }
    public void stocker(Voiture v, char i, int j){
        parking.stocker(v, i, j);
    }
}
