
//: generics/Generators.java
// A utility to use with Generators.

import java.util.*;
import static net.mindview.util.Print.*;

interface Generator<T>
{
  T next();
}

class Coffee
{
  private static long counter = 0;
  private final long id = counter++;

  public String toString()
  {
    return getClass().getSimpleName() + " " + id;
  }
}

class Breve extends Coffee
{

}

class Latte extends Coffee
{

}

class Mocha extends Coffee
{

}

class CoffeeGenerator implements Generator<Coffee>, Iterable<Coffee>
{
  private Class[] types = { Breve.class, Latte.class, Mocha.class };
  Random rand = new Random(47);
  private int n;

  public CoffeeGenerator()
  {
  }

  // for iteration
  public CoffeeGenerator(int sz)
  {
    n = sz;
  }

  public Iterator<Coffee> iterator()
  {
    return new Iterator<Coffee>()
    {
      public boolean hasNext()
      {
        return n > 0;
      }

      public Coffee next()
      {
        n--;
        return CoffeeGenerator.this.next();
      }
    };
  }

  public Coffee next()
  {
    try
    {
      return (Coffee) types[rand.nextInt(types.length)].newInstance();
    }
    catch (Exception e)
    {
      throw new RuntimeException();
    }
  }
}

class BasicGenerator<T> implements Generator<T>
{
  private Class<T> type;

  public BasicGenerator(Class<T> type)
  {
    this.type = type;
  }

  public T next()
  {
    try
    {
      return type.newInstance();
    }
    catch (Exception e)
    {
      throw new RuntimeException();
    }
  }

  public static <T> BasicGenerator<T> create(Class<T> type)
  {
    return new BasicGenerator<T>(type);
  }
}

public class Generators
{
  public static <T> Collection<T> fill(Collection<T> coll, Generator<T> gen, int n)
  {
    System.out.println(">in Collection");
    for (int i = 0; i < n; i++)
      coll.add(gen.next());
    return coll;
  }

  public static <T> List<T> fill(List<T> list, Generator<T> gen, int n)
  {
    System.out.println(">in List");
    for (int i = 0; i < n; i++)
      list.add(gen.next());
    return list;
  }

  public static <T> Set<T> fill(Set<T> list, Generator<T> gen, int n)
  {
    System.out.println(">in Set");
    for (int i = 0; i < n; i++)
      list.add(gen.next());
    return list;
  }

  public static <T> Queue<T> fill(Queue<T> list, Generator<T> gen, int n)
  {
    System.out.println(">in Queue");
    for (int i = 0; i < n; i++)
      list.add(gen.next());
    return list;
  }

  public static void main(String[] args)
  {
    Collection<Coffee> coffee = fill(new ArrayList<Coffee>(), new CoffeeGenerator(), 4);
    for (Coffee c : coffee)
      System.out.println(c);
    Collection<Integer> fnumbers = fill(new ArrayList<Integer>(), new Fibonacci(), 12);
    for (int i : fnumbers)
      System.out.print(i + ", ");
    print();

    List<Coffee> coffee1 = fill(new ArrayList<Coffee>(), new CoffeeGenerator(), 10);
    for (Coffee c : coffee1)
      System.out.println(c);
    // won't comile LikedList implementes from List and deque,
    // List<Coffee> coffee2 = fill(new LinkedList<Coffee>(), new CoffeeGenerator(),
    // 10);
    // for (Coffee c : coffee2)
    // System.out.println(c);
    List<Integer> fnumbers1 = fill(new ArrayList<Integer>(), new Fibonacci(), 10);
    for (int i : fnumbers1)
      System.out.print(i + ", ");
    print();

    Generator<CountedObject> gen = BasicGenerator.create(CountedObject.class);
    for (int i = 0; i < 4; ++i)
      System.out.println(gen.next());
  }
} /*
   * Output: Americano 0 Latte 1 Americano 2 Mocha 3 1, 1, 2, 3, 5, 8, 13, 21, 34,
   * 55, 89, 144,
   */// :~
