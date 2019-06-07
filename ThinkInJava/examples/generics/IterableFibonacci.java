
//: generics/IterableFibonacci.java
// Adapt the Fibonacci class to make it Iterable.
import java.util.*;

// public class IterableFibonacci extends Fibonacci implements Iterable<Integer>
// {
// 	private int n;

// 	public IterableFibonacci(int count)
// 	{
// 		n = count;
// 	}

// 	public Iterator<Integer> iterator()
// 	{
// 		return new Iterator<Integer>()
// 		{
// 			public boolean hasNext()
// 			{
// 				return n > 0;
// 			}

// 			public Integer next()
// 			{
// 				n--;
// 				return IterableFibonacci.this.next();
// 			}

// 			public void remove()
// 			{ // Not implemented
// 				throw new UnsupportedOperationException();
// 			}
// 		};
// 	}

// 	public static void main(String[] args)
// 	{
// 		for (int i : new IterableFibonacci(18))
// 			System.out.print(i + " ");
// 	}
// } /*
//  * Output: 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584
//  */// :~

// exercise 15.7

public class IterableFibonacci implements Iterable<Integer>
{
	private Fibonacci gen;
	private int n;

	public IterableFibonacci(int size)
	{
		gen = new Fibonacci();
		n = size;
	}

	public Iterator<Integer> iterator()
	{
		return new Iterator<Integer>()
		{
			public boolean hasNext()
			{
				return n > 0;
			}

			public Integer next()
			{
				n--;
				return IterableFibonacci.this.gen.next();
			}
		};
	}

	public static void main(String[] args)
	{
		for (int i : new IterableFibonacci(18))
			System.out.print(i + " ");
	}
}