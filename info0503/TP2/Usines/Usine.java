public class Usine {
    private Parking parking;
    public Usine(int nparking, int i,int j){
        this.parking = new parking(nparking,i,j);
    }
    public void stocker(Voiture v, int i, int j){
        parking.stocker(v, i, j);
    }
}
