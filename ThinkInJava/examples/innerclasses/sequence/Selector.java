
public interface Selector<T>
{
    boolean end();

    void next();

    T current();
}