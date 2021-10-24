package Voitures;

public class Option {
    private String nomOption;
    private String description;

    public Option(String nom, String description){
        this.nomOption = nom;
        this.description = description;
    }

    public String getNom(){
        return this.nomOption;
    }
    
    public String getDescription(){
        return this.description;
    }

    public void setNom(String nom){
        this.nomOption=nom;
    }

    public void setDescription(String description){
        this.description = description;
    }
}
