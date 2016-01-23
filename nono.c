#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NELEM(A) (sizeof(A)/sizeof(A[0]))

struct elem
{
   uint32_t vals[10];
   char *cons;
   uint32_t match;
   uint32_t mask;
   uint32_t canon;
   uint32_t *expanded;
   uint32_t combs;
};

struct elem hor[]=
{
   { .vals = { 7, 3, 1, 1, 7 }, },
   { .vals = { 1, 1, 2, 2, 1, 1 }, },
   { .vals = { 1, 3, 1, 3, 1, 1, 3, 1 }, },
   { .vals = { 1, 3, 1, 1, 6, 1, 3, 1 },           .cons = "0001100000001100000001000"},
   { .vals = { 1, 3, 1, 5, 2, 1, 3, 1 }, },
   { .vals = { 1, 1, 2, 1, 1 }, },
   { .vals = { 7, 1, 1, 1, 1, 1, 7 }, },
   { .vals = { 3, 3 }, },
   { .vals = { 1, 2, 3, 1, 1, 3, 1, 1, 2 },        .cons = "0000001100100011001000000"},
   { .vals = { 1, 1, 3, 2, 1, 1 }, },
   { .vals = { 4, 1, 4, 2, 1, 2 }, },
   { .vals = { 1, 1, 1, 1, 1, 4, 1, 3 }, },
   { .vals = { 2, 1, 1, 1, 2, 5 }, },
   { .vals = { 3, 2, 2, 6, 3, 1 }, },
   { .vals = { 1, 9, 1, 1, 2, 1 }, },
   { .vals = { 2, 1, 2, 2, 3, 1 }, },
   { .vals = { 3, 1, 1, 1, 1, 5, 1 },              .cons = "0000001000010000100010000"},
   { .vals = { 1, 2, 2, 5 }, },
   { .vals = { 7, 1, 2, 1, 1, 1, 3 }, },
   { .vals = { 1, 1, 2, 1, 2, 2, 1 }, },
   { .vals = { 1, 3, 1, 4, 5, 1 }, },
   { .vals = { 1, 3, 1, 3, 10, 2 },                .cons = "0001100001100001000011000"},
   { .vals = { 1, 3, 1, 1, 6, 6 }, },
   { .vals = { 1, 1, 2, 1, 1, 2 }, },
   { .vals = { 7, 2, 1, 2, 5 }, },
};

struct elem ver[]=
{
   { .vals = { 7, 2, 1, 1, 7 }, },
   { .vals = { 1, 1, 2, 2, 1, 1 }, },
   { .vals = { 1, 3, 1, 3, 1, 3, 1, 3, 1 }, },
   { .vals = { 1, 3, 1, 1, 5, 1, 3, 1 }, },
   { .vals = { 1, 3, 1, 1, 4, 1, 3, 1 }, },
   { .vals = { 1, 1, 1, 2, 1, 1 }, },
   { .vals = { 7, 1, 1, 1, 1, 1, 7 }, },
   { .vals = { 1, 1, 3 }, },
   { .vals = { 2, 1, 2, 1, 8, 2, 1 }, },
   { .vals = { 2, 2, 1, 2, 1, 1, 1, 2 }, },
   { .vals = { 1, 7, 3, 2, 1 }, },
   { .vals = { 1, 2, 3, 1, 1, 1, 1, 1 }, },
   { .vals = { 4, 1, 1, 2, 6 }, },
   { .vals = { 3, 3, 1, 1, 1, 3, 1 }, },
   { .vals = { 1, 2, 5, 2, 2 }, },
   { .vals = { 2, 2, 1, 1, 1, 1, 1, 2, 1 }, },
   { .vals = { 1, 3, 3, 2, 1, 8, 1 }, },
   { .vals = { 6, 2, 1 }, },
   { .vals = { 7, 1, 4, 1, 1, 3 }, },
   { .vals = { 1, 1, 1, 1, 4 }, },
   { .vals = { 1, 3, 1, 3, 7, 1 }, },
   { .vals = { 1, 3, 1, 1, 1, 2, 1, 1, 4 }, },
   { .vals = { 1, 3, 1, 4, 3, 3 }, },
   { .vals = { 1, 1, 2, 2, 2, 6, 1 }, },
   { .vals = { 7, 1, 3, 2, 1, 1 }, },
};

enum
{
   DIM = NELEM(hor),
   MASK = (1 << DIM) - 1,
};

struct elem *horver[] = { hor, ver };

void dump_bin(uint32_t val)
{
   int i = 8 * sizeof(uint32_t);

   for(--i; i >= 0; --i)
   {
      printf("%c", val & 1 << i ? '1' : '0');
   }
}

void dump_match(struct elem *elem)
{
   if(elem->match)
   {
      dump_bin(elem->match);
   }
   printf("\n");
}

void dump_dir(char *dir, struct elem *elem)
{
   int i = 0;

   for(i = 0; i < DIM; ++i)
   {
      int b = 0;

      printf("%s", dir);
      for(b = DIM - 1; b >= 0; --b)
      {
         printf("%c", elem[i].mask & (1 << b) ? (elem[i].match & (1 << b) ? '1' : '0') : 'X');
      }
      printf("\n");
   }

   printf("\n");
}

void dump_elem(struct elem *elem)
{
   int verbose = 0;
   int i = 0;

   printf("vals:  ");
   for(i = 0; elem->vals[i]; ++i)
   {
      printf("%d ", elem->vals[i]);
   }
   printf("\n");
   if(elem->cons)
   {
      printf("cons:  %s\n", elem->cons);
   }
   printf("match: ");
   dump_bin(elem->match);
   printf("\n");
   printf("mask:  ");
   dump_bin(elem->mask);
   printf("\n");
   printf("canon: ");
   dump_bin(elem->canon);
   printf("\n");
   if(verbose)
   {
      for(i = 0; i < elem->combs; ++i)
      {
         printf("       ");
         dump_bin(elem->expanded[i]);
         printf("\n");
      }
   }
   else
   {
      printf("combs: %d\n", elem->combs);
   }
   printf("\n");
}

void dump_elems(void)
{
   int hv = 0;

   for(hv = 0; hv < NELEM(horver); ++hv)
   {
      int i = 0;

      for(i = 0; i < DIM; ++i)
      {
         dump_elem(horver[hv] + i);
      }
   }
}

uint32_t squish(uint32_t val)
{
   uint32_t i = 0;
   uint32_t ret = 0;
   uint32_t prev_lsb = 1;

   if(!val)
   {
      return 0;
   }

   for(; !(val & 1); val >>= 1)
   {
   }

   for(; val; val >>= 1)
   {
      int this_lsb = val & 1;

      if(this_lsb)
      {
         ret |= 1 << i++;
      }
      else
      {
         if(prev_lsb)
         {
            ++i;
         }
      }

      prev_lsb = this_lsb;
   }
   return ret;
}

uint32_t bin_to_int(char *p)
{
   uint32_t ret = 0;

   for(;;)
   {
      ret <<= 1;
      ret |= *p == '1';
      if(!*++p)
      {
         break;
      }
   }

   return ret;
}

void init_elem(struct elem *elem)
{
   int i = 0;
   int b = 0;
   uint32_t c = 0;

   for(i = 0; i < NELEM(elem->vals) && elem->vals[i]; ++i)
   {
   }

   for(--i; i >= 0; --i)
   {
      int c = 0;

      for(c = elem->vals[i]; c > 0; --c)
      {
         elem->canon |= 1 << b++;
      }
      ++b;
   }

   if(elem->cons)
   {
      elem->match = bin_to_int(elem->cons);
      elem->mask = bin_to_int(elem->cons);
   }

   elem->expanded = calloc(1 << DIM, sizeof(uint32_t));

   for(c = 0; c < 1 << DIM; ++c)
   {
      if(elem->mask && (c & elem->mask) != elem->match)
      {
         continue;
      }
      else if(squish(c) != elem->canon)
      {
         continue;
      }
      elem->expanded[elem->combs++] = c;
   }
   elem->expanded = realloc(elem->expanded, elem->combs * sizeof(uint32_t));
}

void filter(struct elem *elem)
{
   int i = 0;
   int j = 0;
   int b = 0;

   if(!elem->mask)
   {
      return;
   }
   for(i = 0; i < elem->combs; ++i)
   {
      if((elem->expanded[i] & elem->mask) == elem->match)
      {
         elem->expanded[j++] = elem->expanded[i];
      }
   }
   elem->combs = j;
   elem->expanded = realloc(elem->expanded, elem->combs * sizeof(uint32_t));

   for(b = 0; b < DIM; ++b)
   {
      int v = ! !(elem->expanded[0] & (1 << b));
      int c = 0;

      if(elem->mask & (1 << b))
      {
         continue;
      }

      for(i = 0; i < elem->combs; ++i)
      {
         if(v != ! !(elem->expanded[i] & (1 << b)))
         {
            c = 1;
            break;
         }
      }

      if(!c)
      {
         elem->mask |= (1 << b);
         elem->match |= v << b;
      }
   }
}

void check_elem(struct elem *elem)
{
   if(elem->combs == 1)
   {
      elem->mask = MASK;

      if(elem->match != elem->expanded[0])
      {
         elem->match = elem->expanded[0];
         elem->expanded = realloc(elem->expanded, sizeof(uint32_t));
      }
   }
}

void exchange(struct elem *a, struct elem *b)
{
   int ai = 0;

   for(ai = 0; ai < DIM; ++ai)
   {
      int bi = 0;

      for(bi = 0; bi < DIM; ++bi)
      {
         if(! !(a[ai].mask & (1 << (DIM - 1 - bi))))
         {
            b[bi].match |= ! !(a[ai].match & (1 << (DIM - 1 - bi))) << (DIM - 1 - ai);
            b[bi].mask |= 1 << (DIM - 1 - ai);
         }
      }
   }
}

int main()
{
   int hv = 0;
   struct elem last_ver[NELEM(ver)] = { };
   struct elem last_hor[NELEM(ver)] = { };
   int verbose = 0;

   assert(NELEM(ver) == DIM);

   for(hv = 0; hv < NELEM(horver); ++hv)
   {
      int i = 0;

      for(i = 0; i < DIM; ++i)
      {
         init_elem(horver[hv] + i);
         if(verbose)
         {
            dump_elem(horver[hv] + i);
         }
      }
   }

   for(;;)
   {
      int i = 0;

      memcpy(last_ver, ver, sizeof(last_ver));
      memcpy(last_hor, hor, sizeof(last_hor));

      for(hv = 0; hv < NELEM(horver); ++hv)
      {
         for(i = 0; i < DIM; ++i)
         {
            filter(horver[hv] + i);
         }
      }

      for(hv = 0; hv < NELEM(horver); ++hv)
      {
         for(i = 0; i < DIM; ++i)
         {
            check_elem(horver[hv] + i);
         }
      }

      exchange(hor, ver);
      exchange(ver, hor);

      if(verbose)
      {
         dump_elems();
         dump_dir("h ", hor);
         dump_dir("v ", ver);
      }

      if(!memcmp(last_ver, ver, sizeof(last_ver)) && !memcmp(last_hor, hor, sizeof(last_hor)))
      {
         break;
      }
   }

   dump_dir("", hor);

   return 0;
}
