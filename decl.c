#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "puzzles.h"

test_rec test_set[] = {
 {"maxVal", (funct_t) maxVal, (funct_t) test_maxVal, 0, "! ~ & ^ | + << >>", 4, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"negCheck", (funct_t) negCheck, (funct_t) test_negCheck, 1,
    "! ~ & ^ | + << >>", 6, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"lsbCopy", (funct_t) lsbCopy, (funct_t) test_lsbCopy, 1,
    "! ~ & ^ | + << >>", 5, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"andBits", (funct_t) andBits, (funct_t) test_andBits, 2, "| ~", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"xorBits", (funct_t) xorBits, (funct_t) test_xorBits, 2, "& ~", 14, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"setThirdBits", (funct_t) setThirdBits, (funct_t) test_setThirdBits, 0,
    "! ~ & ^ | + << >>", 8, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"byteExtract", (funct_t) byteExtract, (funct_t) test_byteExtract, 2,
    "! ~ & ^ | + << >>", 6, 2,
  {{TMin, TMax},{0,3},{TMin,TMax}}},
{"byteSwitch", (funct_t) byteSwitch, (funct_t) test_byteSwitch, 3,
     "! ~ & ^ | + << >>", 25, 2,
    {{TMin, TMax},{0,3},{0,3}}},
 {"addOverflow", (funct_t) addOverflow, (funct_t) test_addOverflow, 2,
    "! ~ & ^ | + << >>", 20, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"bitFit", (funct_t) bitFit, (funct_t) test_bitFit, 2,
    "! ~ & ^ | + << >>", 15, 3,
  {{TMin, TMax},{1,32},{TMin,TMax}}},
 {"shiftLogical", (funct_t) shiftLogical, (funct_t) test_shiftLogical,
   2, "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{0,31},{TMin,TMax}}},
 {"not", (funct_t) not, (funct_t) test_not, 1,
    "~ & ^ | + << >>", 12, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"signMagnitude", (funct_t) signMagnitude, (funct_t) test_signMagnitude, 1, "! ~ & ^ | + << >>", 15, 3,
  {{TMin+1, TMax},{TMin+1,TMax},{TMin+1,TMax}}},
 {"fp_abs", (funct_t) fp_abs, (funct_t) test_fp_abs, 1,
    "$", 10, 2,
     {{1, 1},{1,1},{1,1}}},
 {"fp_twice", (funct_t) fp_twice, (funct_t) test_fp_twice, 1,
    "$", 30, 3,
     {{1, 1},{1,1},{1,1}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
