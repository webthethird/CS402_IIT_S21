package hw1;

public class multiplyMatrices {

	public static void main(String[] args) {
		long startTime = System.currentTimeMillis();
		// set large values for n, m, and k
		int n = 1500;
		int m = 5000;
		int k = 2500;
		
		// instantiate A, B
		int[][] A = new int[n][m];
		int[][] B = new int[m][k];
		
		// populate A and B with random integers from 0-100
		System.out.println("Generating A:");
		for (int i = 0; i < n; i++) {
			for (int  j = 0; j < m; j++) {
				A[i][j] = (int) (Math.random()*100);
//				System.out.print("["+A[i][j]+"]");
			}
//			System.out.print("\n");
		}
		long aTime = System.currentTimeMillis();
		System.out.println("Time to generate: "+ (aTime-startTime) + " ms");
		System.out.println("Generating B:");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < k; j++) {
				B[i][j] = (int) (Math.random()*100);
//				System.out.print("["+B[i][j]+"]");
			}
//			System.out.print("\n");
		}
		long bTime = System.currentTimeMillis();
		System.out.println("Time to generate: "+ (bTime-aTime) + " ms");
		
		// multiply matrices and print the results
		System.out.println("Calculating C:");
		int[][] c = multIntMatrix(A, B);
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
	
	public static int[][] multIntMatrix(int[][] A, int[][] B) {
		// first check that matrices are compatible, i.e A.columns = B.rows
		for (int i = 0; i < A.length; i++) {
			if (A[i].length != B.length) return null;
		}
		// Create an array with same # rows as A & same # columns as B
		int n = A.length;
		int m = B.length;
		int p = B[0].length;
		int[][] C = new int[n][p];
		// Calculate matrix values using dot product - requires a loop within a loop within a loop
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < p; j++) {
//				int value = 0;
//				for (int k = 0; k < m; k++) {
//					value += A[i][k] * B[k][j];
//				}
//				C[i][j] = value;
//			}
//		}
		for (int k = 0; k < m; k++) {
			for (int i = 0; i < n; i++) {
				int value = A[i][k];
				for (int j = 0; j < p; j++) {
					C[i][j] += value * B[k][j];
				}
			}
		}
		return C;
	}

}
