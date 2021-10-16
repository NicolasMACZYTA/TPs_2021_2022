public class Parking {
    private int nParking;
    private Place[][] places;

    public Parking(int nParking, int lenght, int width){
        this.nParking=nParking;
        this.places = new Place[lenght][width];
    }

    public void stocker(Voiture v, int i, int j){
        places[i][j]= new Place((char)i,j);
        places[i][j].setVoiture(v);
    }
}
