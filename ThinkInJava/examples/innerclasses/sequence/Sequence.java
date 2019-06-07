
//exercies 15.4 of Thinking in java 4s

public class Sequence<T>
{
    private T[] item;
    private int next = 0;

    public Sequence(int size)
    {
        if (size < 0)
            throw ArrayIndexOutOfBoundsException("size:" + size);
        else
            item = new I[size];
    }

    public T add(T a)
    {
        if (next < item.length)
            item[next++] = a;
        return item[next - 1];
    }

    private class SequenceSelector implements Selector<T>
    {
        private int i = 0;

        public boolean end()
        {
            return i == item.length;
        }

        public void next()
        {
            if (i < item.length)
                i++;
        }

        public T current()
        {
            return item[i];
        }
    }

    public SequenceSelector selector()
    {
        return new SequenceSelector();
    }
}