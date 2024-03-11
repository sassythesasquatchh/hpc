#include <stdlib.h>

const char *dgemm_desc = "Blocked dgemm.";
const int s = 32; // Determined from L3 cache of 32000 bytes and double
                  // precision size of 8 bytes. Rounded down to close power of 2

/* This routine performs a dgemm operation
 *
 *  C := C + A * B
 *
 * where A, B, and C are lda-by-lda matrices stored in column-major format.
 * On exit, A and B maintain their input values.
 */

// Optimisation ideas:
//  - Blocking [implemented here]
//  - Unit stride in inner loop [implemented here]
//  - Use higher level optimization [used here]
void square_dgemm(int n, double *A, double *B, double *C) {

  int padded_n = (n + 31) & ~31; // Round up to the nearest multiple of 32
  int b = padded_n / s;          // number of blocks

  // Create padded matrices
  double *padded_A = (double *)malloc(padded_n * padded_n * sizeof(double));
  double *padded_B = (double *)malloc(padded_n * padded_n * sizeof(double));
  double *padded_C = (double *)malloc(padded_n * padded_n * sizeof(double));

  // Initialize padded matrices with zeros
  for (int i = 0; i < padded_n * padded_n; ++i) {
    padded_A[i] = 0.0;
    padded_B[i] = 0.0;
    padded_C[i] = 0.0;
  }

  // Copy data to padded matrices
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < n; ++i) {
      padded_A[i + j * padded_n] = A[i + j * n];
      padded_B[i + j * padded_n] = B[i + j * n];
    }
  }

  // block loop
  for (int kk = 0; kk < b; kk++) {
    for (int jj = 0; jj < b; jj++) {
      for (int ii = 0; ii < b; ii++) {
        // Perform MM
        for (int k = kk * s; k < (kk + 1) * s; ++k) {
          for (int j = jj * s; j < (jj + 1) * s; ++j) {
            for (int i = ii * s; i < (ii + 1) * s; ++i) {
              padded_C[i + j * padded_n] +=
                  padded_A[i + k * padded_n] * padded_B[k + j * padded_n];
            }
          }
        }
      }
    }
  }

  // Copy results back to the original matrix C
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < n; ++i) {
      C[i + j * n] = padded_C[i + j * padded_n];
    }
  }

  // // Clean up loops
  // int offset = b * s;
  // for (int k = offset; k < n; ++k) {
  //   for (int j = offset; j < n; ++j) {
  //     for (int i = offset; i < n; ++i) {
  //       C[i + j * n] += A[i + k * n] * B[k + j * n];
  //     }
  //   }
  // }

  // for (int k = 0; k < n; ++k) {
  //   for (int j = offset; j < n; ++j) {
  //     for (int i = 0; i < offset; ++i) {
  //       C[i + j * n] += A[i + k * n] * B[k + j * n];
  //     }
  //   }
  // }

  // for (int k = 0; k < n; ++k) {
  //   for (int j = 0; j < offset; ++j) {
  //     for (int i = offset; i < n; ++i) {
  //       C[i + j * n] += A[i + k * n] * B[k + j * n];
  //     }
  //   }
  // }
  // Free allocated memory for padded matrices
  free(padded_A);
  free(padded_B);
  free(padded_C);
}
