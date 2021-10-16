package src.Pokemon;

public class PokemonClass {

        private String nom;
        private String type;
        private String categorie;
        private int taille;
        private int poids;
        private String talent_1;
        private String talent_2;
        private int experience;
        private int experienceMaximale;
        private int niveau;
        private String sexe;
        private int points_de_vie;

    public PokemonClass(String nom, String type, String categorie, int taille, int poids,String talent_1,String talent_2,int experience,int experienceMaximale,int niveau,String sexe,int points_de_vie){
        //todo
    }

    public boolean attaquePokemon(PokemonClass P){
        return true;
    }

    public String getNom(){
        return this.nom;
    }

    public String getType(){
        return this.type;
    }

    public String getCategorie(){
        return this.categorie;
    }

    public int getTaille(){
        return this.taille;
    }

    public int getPoids(){
        return this.poids;
    }

    public String getTalent_1(){
        return this.talent_1;
    }

    public String getTalent_2(){
        return this.talent_2;
    }

    public int getExperience(){
        return this.experience;
    }
    public int getExperienceMax(){
        return this.experienceMaximale;
    }

    public int getNiveau(){
        return this.niveau;
    }

    public String getSexe(){
        return this.sexe;
    }

    public int getPV(){
        return this.points_de_vie;
    }
    public String toString(){
        //todo
        return "todo\n";
    }
    public void setNom(String nouveauNom){
        this.nom=nouveauNom;
    }
    public void ajouterExperience(int montant){
        this.experience+=montant;
        //ajouter mécanique monter le niveau et ne pas dépasser l'experience max
    }
    public void enleverPV(float montant){
        this.points_de_vie-=(int)montant;
    }
}