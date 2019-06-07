package typeinfo;

import typeinfo.pets.*;
import java.util.*;
import static net.mindview.util.Print.*;

public class Test
{

    public void testClass()
    {
        Class<? extends Number> c = Integer.class;
        print(c.getSimpleName());
    }

    public static void main(String[] args)
    {
        for (Pet pet : Pets.createArray(20))
        {
            Class<? extends Pet> type = pet.getClass();
            printnb(type.getSimpleName());
            printnb(" extends " + type.getSuperclass().getSimpleName());
            print();
            new Test().testClass();
        }
    }
}