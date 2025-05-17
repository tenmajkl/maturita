package zoo.zvirata;

import zoo.Zvire;

public class Lev extends Zvire {

    public Lev(int vek, String jmeno) {
        super(vek, jmeno);
    }

    public String getDruh() {
        return "Lev";
    }

    @Override
    public String zvuk() {
        return "AAAAAAA";
    }
}
