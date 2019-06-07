//: generics/GenericMethods.java

// public class GenericMethods
// {
//   public <T> void f(T x)
//   {
//     System.out.println(x.getClass().getName());
//   }

//   public static void main(String[] args)
//   {
//     GenericMethods gm = new GenericMethods();
//     gm.f("");
//     gm.f(1);
//     gm.f(1.0);
//     gm.f(1.0F);
//     gm.f('c');
//     gm.f(gm);
//   }
// } /*
//    * Output: java.lang.String java.lang.Integer java.lang.Double java.lang.Float
//    * java.lang.Character GenericMethods
//    */// :~

// exercise 15-9

public class GenericMethods
{
  public <A, B, C> void f(A a, B b, String c)
  {
    System.out.print("[ " + a.getClass().getName() + ", ");
    System.out.print(b.getClass().getName() + ", ");
    System.out.println(c.getClass().getName() + ", ]");
  }

  public static void main(String[] args)
  {
    GenericMethods gm = new GenericMethods();
    gm.f(1, " ", "he");
    gm.f('c', 1.0F, "hhh");
  }
}