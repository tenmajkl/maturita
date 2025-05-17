package zoo.zvirata;

import zoo.Zvire;

public class Slon extends Zvire {

    public Slon(int vek, String jmeno) {
        super(vek, jmeno);
    }

    public String getDruh() {
        return "Slon";
    }

    @Override
    public String zvuk() {
        return "TUUUUUU";
    }
}
