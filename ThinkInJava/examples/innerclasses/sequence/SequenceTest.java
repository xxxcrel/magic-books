
import static net.mindview.util.Print.*;

import java.util.ArrayList;

public class SequenceTest
{
    public static void main(String[] args)
    {
        // Sequence<String> sequence = new Sequence<>(10);
        // sequence.add("hello");
        // sequence.add("world");
        // Selector<String> seqSel = sequence.selector();
        // print(seqSel.current());
        ArrayList<String> arrayList = new ArrayList<>(10);
        arrayList.add("hello");
        print(arrayList.get(0));
    }

}