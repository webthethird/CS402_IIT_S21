package hw1;

public class multiplyRealMatrices {
	
	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		// set large values for n, m, and k
		int n = 1500;
		int m = 1000;
		int k = 500;
		
		// instantiate A, B
		double[][] A = new double[n][m];
		double[][] B = new double[m][k];
		
		// populate A and B with random integers from 0-100
		System.out.println("Generating A:");
		for (int i = 0; i < n; i++) {
			for (int  j = 0; j < m; j++) {
				A[i][j] = Math.random()*100;
//				System.out.print("["+A[i][j]+"]");
			}
//			System.out.print("\n");
		}
		long aTime = System.currentTimeMillis();
		System.out.println("Time to generate: "+ (aTime-startTime) + " ms");
		System.out.println("Generating B:");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				B[i][j] = Math.random()*100;
//				System.out.print("["+B[i][j]+"]");
			}
//			System.out.print("\n");
		}
		long bTime = System.currentTimeMillis();
		System.out.println("Time to generate: "+ (bTime-aTime) + " ms");
		
		// multiply matrices and print the results
		System.out.println("Calculating C:");
		double[][] c = multDoubleMatrix(A, B);
		long cTime = System.currentTimeMillis();
		System.out.println("Time to multiply: "+ (cTime-bTime) + " ms");
		System.out.println("Total runtime: "+ (cTime-startTime) + " ms");
//		for(int i = 0; i < n; i++) {
//			for(int j = 0; j < k; j++) {
//				System.out.print("["+c[i][j]+"]");
//			}
//			System.out.print("\n");
//		}
	}
	
	public static double[][] multDoubleMatrix(double[][] A, double[][] B) {
		// first check that matrices are compatible, i.e A.columns = B.rows
		for (int i = 0; i < A.length; i++) {
			if (A[i].length != B.length) return null;
		}
		// Create an array with same # rows as A & same # columns as B
		int n = A.length;
		int m = B.length;
		int k = B[0].length;
		double[][] C = new double[n][k];
		// Calculate matrix values using dot product - requires a loop within a loop within a loop
		// Modified for part b
		for (int j = 0; j < k; j++) {
			for (int i = 0; i < n; i++) {
				double value = 0;
				for (int h = 0; h < m; h++) {
					value += A[i][h] * B[h][j];
				}
				C[i][j] = value;
			}
		}
		return C;
	}
}
