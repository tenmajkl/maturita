package zoo.zvirata;

import zoo.Zvire;

public class Ovce extends Zvire {

    public Ovce(int vek, String jmeno) {
        super(vek, jmeno);
    }

    public String getDruh() {
        return "Ovce";
    }

    @Override
    public String zvuk() {
        return "BEEEEEE";
    }
}
