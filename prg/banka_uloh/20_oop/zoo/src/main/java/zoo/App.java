package zoo;

import zoo.zvirata.Lev;
import zoo.zvirata.Ovce;
import zoo.zvirata.Slon;

public class App {
    public static void main(String[] args) {
        Zvire zvirata[] = {new Lev(5, "Simba"), new Slon(10, "Dumbo"), new Ovce(3, "Shaun")};
        for (Zvire zvire : zvirata) {
            System.out.println("Druh: " + zvire.getDruh());
            System.out.println("Vek: " + zvire.getVek());
            System.out.println("Jmeno: " + zvire.getJmeno());
            System.out.println(zvire.zvuk());
        }
    }
}
