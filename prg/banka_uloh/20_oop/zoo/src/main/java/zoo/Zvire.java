package zoo;

public abstract class Zvire {
    private int vek;
    private String jmeno;

    public Zvire(int vek, String jmeno) {
        this.vek = vek;
        this.jmeno = jmeno;
    }

    public int getVek() {
        return vek; 
    }

    public Zvire zvysVek() {
        vek++;
        return this;
    }

    public String getJmeno() {
        return jmeno;
    }

    public Zvire setJmeno(String jmeno) {
        this.jmeno = jmeno;
        return this;
    }

    abstract public String getDruh();

    abstract public String zvuk();
}
