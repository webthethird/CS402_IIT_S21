package lab4;

import java.util.Scanner;

public class AckermannFunction {

	public static void main(String[] args) {
		int x, y;
		Scanner input = new Scanner(System.in);
		
		System.out.print("Please enter an integer x: ");
		x = input.nextInt();
		
		System.out.print("Please enter another integer y: ");
		y = input.nextInt();
		
		System.out.println("The result of Ackermann's function for x="+x+" and y="+y+" is: "+A(x,y));
	}
	
	public static int A(int x, int y) {
		if (x == 0) return y+1;
		else if (y == 0) return A(x-1, 1);
		else return A(x-1, A(x, y-1));
	}

}
