
//: generics/LimitsOfInference.java
import java.util.*;
import net.mindview.util.*;

class New
{
  public static <K, V> Map<K, V> map()
  {
    return new HashMap<K, V>();
  }
}

class MyClass
{

}

class MyClass1 extends MyClass
{

}

public class LimitsOfInference
{
  static void f(Map<String, List<? extends MyClass>> petPeople)
  {
    petPeople.put("string", Arrays.asList(new MyClass(), new MyClass1()));
    // petPeople.get("string").add(new MyClass1());
    System.out.println(petPeople.get("string").get(0).getClass().getName());
    System.out.println(petPeople.get("string").get(1).getClass().getName());

  }

  public static void main(String[] args)
  {
    Map<String, List<? extends MyClass>> pet = New.map();
    f(pet);
    f(New.map()); // Does not compile
    // ArrayList<? extends MyClass> arrayList = new ArrayList<? extends MyClass>();
    // MyClass1 myClass1 = new MyClass1();
    // arrayList.add(myClass1);
    ArrayList<String> as = new ArrayList<>();
    as.add("hello");
    List<? extends MyClass> arr = Arrays.asList(new MyClass(), new MyClass1());
    ArrayList<MyClass> arm = new ArrayList<MyClass>()
    {
      {
        add(new MyClass());
        add(new MyClass());
      }
    };
  }
} /// :~
