package TD_java;

public class Compteur {
    private int val;


    public Compteur(){
        val =0;
    }

    public void increment(){
        synchronized(this){
            val++;
        }
    }

    public synchronized void decrement(){
        val--;
    }

    public synchronized int getVal(){
        return this.val;
    }
}
