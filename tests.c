/* Testing Code */

#include <limits.h>
#include <math.h>
#include <stdio.h>

/* Routines used by floating point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

int test_maxVal(void) {
  return 0x7FFFFFFF;
}

int test_negCheck(int x) {
  return x < 0;
}

int test_lsbCopy(int x) {
  return (x & 0x1) ? -1 : 0;
}

int test_andBits(int x, int y) {
  return x&y;
}

int test_xorBits(int x, int y) {
  return x^y;
}

int test_setThirdBits(void) {
  int result = 0;
  int i;
  for (i = 0; i < 32; i+=3)
    result |= 1<<i;
  return result;
}

int test_byteExtract(int x, int n) {
    unsigned char byte;
    switch(n) {
    case 0:
      byte = x;
      break;
    case 1:
      byte = x >> 8;
      break;
    case 2:
      byte = x >> 16;
      break;
    default:
      byte = x >> 24;
      break;
    }
    return (int) (unsigned) byte;
}

int test_byteSwitch(int x, int n, int m) {
    /* little endiamachine */
    /* least significant byte stored first */
    unsigned int nmask, mmask;
    switch(n) {
    case 0:
      nmask = x & 0xFF;
      x &= 0xFFFFFF00;
      break;
    case 1:
      nmask = (x & 0xFF00) >> 8;
      x &= 0xFFFF00FF;
      break;
    case 2:
      nmask = (x & 0xFF0000) >> 16;
      x &= 0xFF00FFFF;
      break;
    default:
      nmask = ((unsigned int)(x & 0xFF000000)) >> 24;
      x &= 0x00FFFFFF;
      break;
    }
    switch(m) {
    case 0:
      mmask = x & 0xFF;
      x &= 0xFFFFFF00;
      break;
    case 1:
      mmask = (x & 0xFF00) >> 8;
      x &= 0xFFFF00FF;
      break;
    case 2:
      mmask = (x & 0xFF0000) >> 16;
      x &= 0xFF00FFFF;
      break;
    default:
      mmask = ((unsigned int)(x & 0xFF000000)) >> 24;
      x &= 0x00FFFFFF;
      break;
    }
    nmask <<= 8*m;
    mmask <<= 8*n;
    return x | nmask | mmask;
}

int test_addOverflow(int x, int y) {
    long long lsum = (long long) x + y;
    return lsum == (int) lsum;
}

int test_bitFit(int x, int n) {
  int TMin_n = -(1 << (n-1));
  int TMax_n = (1 << (n-1)) - 1;

  // I cannot even speculate what's going on here.
  // Printing out TMax_n (to terminal or like this) ensures that result is properly 0.
  // Otherwise, the 'correct' result given is 1 (which is wrong).
  FILE* hack = fopen("/dev/null", "w");
  fprintf(hack, "%d\n", TMax_n);
  fclose(hack);

  return x >= TMin_n && x <= TMax_n;
}

int test_shiftLogical(int x, int n) {
  unsigned u = (unsigned) x;
  unsigned shifted = u >> n;
  return (int) shifted;
}

int test_not(int x) {
  return !x;
}

int test_signMagnitude(int x) {
  int sign = x < 0;
  int mag = x < 0 ? -x : x;
  return (sign << 31) | mag;
}

unsigned test_fp_abs(unsigned uf) {
  float f = u2f(uf);
  unsigned unf = f2u(-f);
  if (isnan(f))
    return uf;
  /* An unfortunate hack to get around a limitation of the BDD Checker */
  if ((int) uf < 0)
      return unf;
  else
      return uf;
}

unsigned test_fp_twice(unsigned uf) {
  float f = u2f(uf);
  float tf = 2*f;
  if (isnan(f))
    return uf;
  else
    return f2u(tf);
}
