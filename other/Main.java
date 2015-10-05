import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;

public class Main {

    final static int maxn = 100000;

    public static int n;
    public static int a[] = new int[maxn];

    public static void func1() {}
    public static boolean ok() {}

    public static void main(String[] args) {
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
        int n = cin.nextInt();
        //while (cin.hasNext())
        //String s1 = cin.next();
        //String s2 = cin.nextLine();
        //double t1 = cin.nextDouble();
        //System.out.print(n);
        //System.out.println(n);

        double c = 123.456789, d = 0.12;
        DecimalFormat f = new DecimalFormat("#.00#");
        DecimalFormat g = new DecimalFormat("00.000");
        System.out.println(f.format(c));
        System.out.println(f.format(d));
        System.out.println(g.format(d));

        int [] arr = new int[5];
        int [] arrr = {1, 2, 3, 4, 5};
        int [][] ff = new int[n][n];
        Arrays.sort(arrr);

        BigInteger a = cin.nextBigInteger();
        BigInteger b = BigInteger.valueOf(2);

        a = a.add(b);       a = a.subtract(b);  a = a.negate();
        a = a.multiply(b);  a = a.divide(b);    a = a.mod(b);
        a = a.shiftLeft(1); a = a.shiftRight(1);
        if (a.compareTo(b) < 0)
            System.out.println("a < b");
    }

    public int sum(int a, int b) {
        return a + b;
    }
}
