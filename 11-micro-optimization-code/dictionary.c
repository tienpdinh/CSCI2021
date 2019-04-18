// Bryant/O'Hallaron Ch 5 word-counting program to demonstrate
// profiling. From CS:APP 3rd Ed. Pasted in options.c file and header
// to make this file self-contained.
//
// Compile and demo with Makefile

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
// options functions
// #include "options.h"
void add_int_option(char *name, int *var);
void add_double_option(char *name, double *var);
void add_string_option(char *name, char **var);     
void usage(char *prog);
int parse_options(int argc, char *argv[], char *otherargs[]);
void parse_option_file(char *prog, FILE *option_file);
void show_options(FILE *outfile);


////////////////////////////////////////////////////////////////////////////////
// original dictionary.c file
#define USESTRLEN 1
size_t Strlen(const char *s);


/* Some statistics */
int wcnt = 0; /* Number of words */
int ucnt = 0; /* Number of unique words */
int mcnt = 0; /* Count of Most frequent word */
int scnt = 0; /* Count of number of singletons */
char *mstring = ""; /* Most frequent word */
int llen = 0; /* Length of the longest word */
char *lstring = ""; /* A longest string */
int lcnt = 0; /* Number of words having maximum length */

/* Use function pointers to keep track of which options we are using */
typedef void (*lower_fun_t)(char *s);

/* Lower case conversion routines */

/* Convert string to lower case: slow */
void lower1(char *s)
{
    int i;

    for (i = 0; i < Strlen(s); i++)
	if (s[i] >= 'A' && s[i] <= 'Z')
	    s[i] -= ('A' - 'a');
}

/* Convert string to lower case: faster */
void lower2(char *s)
{
    int i;
    int len = Strlen(s);

    for (i = 0; i < len; i++)
	if (s[i] >= 'A' && s[i] <= 'Z')
	    s[i] -= ('A' - 'a');
}

/* Set of lower case functions */
#define LCNT 2
lower_fun_t lower_fun_set[LCNT] = {lower1, lower2};
char *lower_fun_names[LCNT] = {"lower1", "lower2"};

/* Implementation of library function strlen */
/* Compute length of string */
size_t Strlen(const char *s)
{
#ifdef USESTRLEN
    return strlen(s);
#else
    int length = 0;
    while (*s != '\0') {
	s++; 
	length++;
    }
    return length;
#endif
}

/* The hash table */

typedef struct HELE {
    char *word;
    int freq;
    struct HELE *next;
} h_rec, *h_ptr;

/* The hash table */
h_ptr *htable;
int tsize;

static void new_table(int size)
{
    tsize = size;
    htable = (h_ptr *) calloc(size, sizeof(h_ptr));
    if (!htable) {
	fprintf(stderr, "Couldn't allocate hash array, exiting\n");
	exit(1);
    }
}

static h_ptr new_ele(char *s)
{
    h_ptr result = (h_ptr) malloc(sizeof(h_rec));
    int wlen = Strlen(s);
    if (wlen > llen) {
	lstring = s;
	llen = wlen;
	lcnt = 1;
    } else if (wlen == llen)
	lcnt++;
    if (!result) {
	fprintf(stderr, "Couldn't allocate hash element, exiting\n");
	exit(1);
    }

    result->word = s;
    result->freq = 1;
    return result;
}

/* Some hash functions */

/* Division hashing */

typedef unsigned (*hash_fun_t)(char *s);

unsigned h_mod(char *s)
{
    unsigned val = 0;
    int c;
    while ((c = *s++))
	val = (val * 128 + c) % tsize;
    return val;
}

/* Simply add characters together */
unsigned h_add(char *s)
{
    unsigned val = 0;
    int c;
    while ((c = *s++))
	val += c;
    return val % tsize;
}

/* Combine with Xors */
unsigned h_xor(char *s)
{
    unsigned val = 0;
    int c;
    while ((c = *s++))
	val = ((val ^ c)<<4) | ((val >> 28) & 0xF);
    return val % tsize;
}

#define HCNT 3
hash_fun_t hash_fun_set[HCNT] = {h_mod, h_add, h_xor};
char *hash_fun_names[HCNT] = {"h_mod", "h_add", "h_xor"};

char *save_string(char *s)
{
    char *result = (char *) malloc(Strlen(s)+1);
    if (!result) {
	fprintf(stderr, "Couldn't allocate space for string, exiting\n");
	exit(1);
    }
    strcpy(result,s);
    return result;
}
  
/* Recursively find string in list.  Add to end if not found */
h_ptr find_ele_rec(h_ptr ls, char *s)
{
    if (!ls) {
	/* Come to end of list.  Insert this one */
	ucnt++;
	return new_ele(save_string(s));
    }
    if (strcmp(s,ls->word) == 0) {
	ls->freq++;
	if (ls->freq > mcnt) {
	    mcnt = ls->freq;
	    mstring = ls->word;
	}
	return ls;
    }
    ls->next = find_ele_rec(ls->next, s);
    return ls;
}

/* Iteratively find string in list.  Add to front if not found */
h_ptr find_ele_iter_f(h_ptr ls, char *s)
{
    h_ptr ele = ls;
    for (ele = ls; ele; ele = ele->next) {
	char *word = ele->word;
	if (strcmp(s, word) == 0) {
	    int freq = ++ele->freq;
	    if (freq > mcnt) {
		mcnt = freq;
		mstring = word;
	    }
	    return ls;
	}
    }
    ele = new_ele(save_string(s));
    ucnt++;
    ele->next = ls;
    return ele;
}

/* Iteratively find string in list.  Add to end if not found */
h_ptr find_ele_iter_r(h_ptr ls, char *s)
{
    h_ptr ele = ls;
    h_ptr last = NULL;
    for (ele = ls; ele; ele = ele->next) {
	char *word = ele->word;
	if (strcmp(s, word) == 0) {
	    int freq = ++ele->freq;
	    if (freq > mcnt) {
		mcnt = freq;
		mstring = word;
	    }
	    return ls;
	}
	last = ele;
    }
    ele = new_ele(save_string(s));
    ucnt++;
    ele->next = NULL;
    if (last) {
	last->next = ele;
	return ls;
    } else
	return ele;
}


typedef h_ptr (*find_ele_fun_t)(h_ptr, char *);

#define FCNT 3
find_ele_fun_t find_ele_fun_set[FCNT] =
    {find_ele_rec, find_ele_iter_f, find_ele_iter_r};
char *find_ele_fun_names[FCNT] = 
    {"find_ele_rec", "find_ele_iter_f", "find_ele_iter_r"};

/* Comparision function for sorting */
int compare_ele(const void *vele1, const void *vele2) {
    h_ptr ele1 = *(h_ptr *) vele1;
    h_ptr ele2 = *(h_ptr *) vele2;
    return ele2->freq - ele1->freq;
}


/* Sort hash table elements by frequency */
h_ptr sort_words(int quick)
{
    h_ptr ls = NULL;
    h_ptr ele;
    h_ptr *array = calloc(ucnt, sizeof(h_ptr));
    int i, j;
    int cnt = 0;
    scnt = 0; /* Count singletons */
    for (i = 0; i < tsize; i++)
	for (ele = htable[i]; ele; ele = ele->next) {
	    if (ele->freq == 1)
		scnt++;
	    if (quick)
		array[cnt] = ele;
	    else {
		for (j = cnt; j > 0 && ele->freq > array[j-1]->freq; j--)
		    array[j] = array[j-1];
		array[j] = ele;
	    }
	    cnt++;
	}
    if (quick) {
	qsort((void *) array, cnt, sizeof(h_ptr), compare_ele);
    }
    ls = array[0];
    for (j = 0; j < cnt-1; j++)
	array[j]->next = array[j+1];
    array[cnt-1]->next = NULL;
    free ((void *) array);
    return ls;
}


void insert_string(char *s,
		   hash_fun_t hash_fun, lower_fun_t lower_fun,
		   find_ele_fun_t find_ele_fun)
{
    int index;
    lower_fun(s);
    index = hash_fun(s);
    htable[index] = find_ele_fun(htable[index], s);  
}

/* Extract word from file */
#define BSIZE 1024
char buf[BSIZE];
int bufvalid = 0;
FILE *infile;

void init_token(FILE *in) {
    bufvalid = 0;
    infile = in;
}

/* Added some non-ASCII characters encountered in European parliament corpus */
static char *skipchar = " \t\n\r.,:;/<>()[]{}?!\"-'\0xc2\0xa0";

/* Keep getting tokens.  Return NULL when no more */
char *get_word()
{
    char *s = NULL;
    while (1) {
	if (bufvalid) {
	    s = strtok(NULL, skipchar);
	    if (s)
		break;
	}
	if (!fgets(buf, BSIZE, infile))
	    return NULL;
	bufvalid = 1;
	s = strtok(buf, skipchar);
	if (s)
	    break;
    }
    wcnt++;
    return s;
}


#define MAXNG 10

char *get_token(int ngram)
{
    /* Buffer of last ngram-1 tokens */
    static char token_buf[MAXNG][BSIZE];
    static int first = 1;
    static int bindex = 0; /* In which buffer to insert next token */
    static char sbuf[BSIZE];
    char *nextpos = sbuf;
    int i; int index;

    if (ngram == 1)
	return get_word();
    if (first) {
	/* Get ngram-1 tokens */
	while (bindex < ngram-1) {
	    char *word = get_word();
	    if (!word) {
		return NULL; /* Document doesn't have enough tokens */
	    }
	    strcpy(token_buf[bindex++], word);
	}
	first = 0;
    }
    /* Get new token */
    char *word = get_word();
    if (!word) {
	return NULL; /* No more ngrams */
    }
    strcpy (token_buf[bindex++], word);
    if (bindex >= MAXNG)
	bindex = 0;
    /* Generate string of last ngram-1 tokens */
    index = bindex - ngram;
    if (index < 0)
	index += MAXNG;
    for (i = 0; i < ngram; i++) {
	if (i != 0)
	    *nextpos++ = ' ';
	word = token_buf[index];
	strcpy(nextpos, word);
	nextpos += Strlen(word);
	index++;
	if (index >= MAXNG)
	    index = 0;
    }
#if 0
     printf("Next n-gram = '%s'\n", sbuf);
#endif
    return sbuf;
}



/* Find statistics of word frequency in document */
void word_freq(FILE *src, int verbose, int ngram, int size, int quick,
	       hash_fun_t hash_fun, lower_fun_t lower_fun,
	       find_ele_fun_t find_ele_fun)
{
    char *s;
    h_ptr ls;

    init_token(src);
    new_table(size);

    while ((s = get_token(ngram))) {
	insert_string(s, hash_fun, lower_fun, find_ele_fun);
    }
    if (verbose > 0) {
	ls = sort_words(quick);
	while (ls && verbose--) {
	    printf("%d\t'%s'\n", ls->freq, ls->word);
	    ls = ls->next;
	}
    }
    printf("%d n-grams, %d unique, %d singletons.  Most common (%d) = '%s'.  Longest (%d have length %d) = '%s'\n",
	   wcnt, ucnt, scnt, mcnt, mstring, lcnt, llen, lstring);
}

int main(int argc, char *argv[])
{
    int verbose = 1;
    int size = 1024;
    int hash_fun_index = 0;
    int lower_fun_index = 0;
    int find_fun_index = 0;
    int ngram = 1;
    int quick = 0;
    char *fname = NULL;
    FILE *infile = stdin;
    add_int_option("verbose", &verbose);
    add_int_option("size", &size);
    add_int_option("hash", &hash_fun_index);
    add_int_option("lower", &lower_fun_index);
    add_int_option("find", &find_fun_index);
    add_int_option("ngram", &ngram);
    add_int_option("quicksort", &quick);
    add_string_option("file", &fname);
    parse_options(argc, argv, NULL);
    show_options(stdout);
    printf("N-gram size %d\n", ngram);
    printf("Lower case function %s\n", lower_fun_names[lower_fun_index]);
    printf("Hash function %s\n", hash_fun_names[hash_fun_index]);
    printf("Find element function %s\n", find_ele_fun_names[find_fun_index]);
    if ((unsigned) hash_fun_index >= HCNT) {
	fprintf(stderr, "Invalid hash function index %d\n", hash_fun_index);
	exit(1);
    }
    if ((unsigned) lower_fun_index >= LCNT) {
	fprintf(stderr, "Invalid lower function index %d\n", lower_fun_index);
	exit(1);
    }
    if ((unsigned) find_fun_index >= FCNT) {
	fprintf(stderr, "Invalid find function index %d\n", find_fun_index);
	exit(1);
    }
    if (fname) {
	infile = fopen(fname, "r");
	if (!infile) {
	    fprintf(stderr, "Couldn't open file '%s'\n", fname);
	    exit(1);
	}
    }
    word_freq(infile, verbose, ngram, size, quick,
	      hash_fun_set[hash_fun_index],
	      lower_fun_set[lower_fun_index],
	      find_ele_fun_set[find_fun_index]);
    printf("Total time = %f seconds\n", (double) clock() / CLOCKS_PER_SEC);
    fclose(infile);
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// options functions
/*
 * Code to process options from command line arguments.
 * Option values can be integers,
 * floats, or strings.   Allow prefix of option name, as long as
 * unambiguous.  Also support printing of usage information.
 */


typedef enum {INT_OPTION, DOUBLE_OPTION, STRING_OPTION} option_t;

typedef struct {
  char *name;
  option_t type;
  union {
    int *i;
    double *d;
    char **s;
  } valp;
} option_entry;

#define MAX_OPTION 100
static option_entry options[MAX_OPTION];

static int option_count = 0;

/* Determine length of string match */
static int match_length(char *s, char *t)
{
  int result = 0;
  while (*s == *t) {
    result ++;
    if (*s == '\0')
      break;
    s++; t++;
  }
  return result;
}

void usage(char *prog)
{
  int j;
  fprintf(stderr, "Usage: %s", prog);
  for (j = 0; j < option_count; j++) {
    switch(options[j].type) {
    case INT_OPTION:
      fprintf(stderr, " [-%s (%d)]", options[j].name, *(options[j].valp.i));
      break;
    case DOUBLE_OPTION:
      fprintf(stderr, " [-%s (%.2f)]", options[j].name, *(options[j].valp.d));
      break;
    case STRING_OPTION:
      fprintf(stderr, " [-%s (%s)]", options[j].name, *(options[j].valp.s));
      break;
    }
  }
  fprintf(stderr, "\n");
  exit(1);
}

/* Determine which option is best match. */
static int find_option(char *prog, char *name)
{
  int sofar = -1;
  int sofar_length = 0;
  int i;
  int ambiguous = 0;
  for (i = 0; i < option_count; i++) {
    int length = match_length(options[i].name, name);
    if (length > sofar_length) {
      sofar = i;
      sofar_length = length;
      ambiguous = 0;
    } else if (length > 0 && length == sofar_length) {
      ambiguous = 1;
    }
  }
  if (sofar_length == 0) {
    fprintf(stderr, "No match found to option '%s'\n", name);
    usage(prog);
  } else if (ambiguous) {
    fprintf(stderr, "Ambiguous option: '%s'\n", name);
    usage(prog);
  }
  return sofar;
}


void add_int_option(char *name, int *var)
{
  options[option_count].name = name;
  options[option_count].type = INT_OPTION;
  options[option_count].valp.i = var;
  option_count++;
}

void add_double_option(char *name, double *var)
{
  options[option_count].name = name;
  options[option_count].type = DOUBLE_OPTION;
  options[option_count].valp.d = var;
  option_count++;
}

void add_string_option(char *name, char **var)
{
  options[option_count].name = name;
  options[option_count].type = STRING_OPTION;
  options[option_count].valp.s = var;
  option_count++;
}

int parse_options(int argc, char *argv[], char *otherargs[])
{
  int i, j;
  int ocount = 0;
  float f;
  char *prog = argv[0];
  for (i = 1; i < argc; i++) {
    /* Look for options */
    if (*argv[i] != '-') {
      /* Must be another class of argument */
      if (otherargs)
	otherargs[ocount] = argv[i];
      ocount++;
      continue;
    }
    j = find_option(prog, argv[i]+1);
    i++; /* Move to next argument */
    if (i >= argc) {
      fprintf(stderr, "Missing value for option %s\n", options[j].name);
      usage(prog);
    }
    switch(options[j].type) {
    case INT_OPTION:
      if (sscanf(argv[i], "%d", options[j].valp.i) != 1) {
	fprintf(stderr, "Can't parse argument '%s' as integer\n", argv[i]);
	usage(prog);
      }
      break;
    case DOUBLE_OPTION:
      if (sscanf(argv[i], "%f", &f) != 1) {
	fprintf(stderr, "Can't parse argument '%s' as double\n", argv[i]);
	usage(prog);
      }
      *options[j].valp.d = f;
      break;
    case STRING_OPTION:
      *(options[j].valp.s) = argv[i];
      break;
    default:
      fprintf(stderr,
	      "Internal error.  Don't know option type %d\n", options[j].type);
      exit(1);
    }
  }
  return ocount;
}


static char *strsave(char *s)
{
  char *result = (char *) malloc(strlen(s)+1);
  strcpy (result, s);
  return result;
}

void parse_option_file(char *prog, FILE *option_file)
{
  int j;
  float f;
  char name[50], val[50];
  while (fscanf(option_file, "%s %s", name, val) == 2) {
    if (name[0] != '-') {
      fprintf(stderr, "Need '-' before option '%s'\n", name);
      usage(prog);
    }
    j = find_option(prog, name+1);
    switch(options[j].type) {
    case INT_OPTION:
      if (sscanf(val, "%d", options[j].valp.i) != 1) {
	fprintf(stderr, "Can't parse argument '%s' as integer\n", val);
	usage(prog);
      }
      break;
    case DOUBLE_OPTION:
      if (sscanf(val, "%f", &f) != 1) {
	fprintf(stderr, "Can't parse argument '%s' as double\n", val);
	usage(prog);
      }
      *options[j].valp.d = f;
      break;
    case STRING_OPTION:
      *(options[j].valp.s) = strsave(val);
      break;
    default:
      fprintf(stderr,
	      "Internal error.  Don't know option type %d\n", options[j].type);
      exit(1);
    }
  }
}

void show_options(FILE *outfile)
{
  int i;
  for (i = 0; i < option_count; i++) {
    switch(options[i].type) {
    case INT_OPTION:
      fprintf(outfile, "%s\t%d\n", options[i].name, *(options[i].valp.i));
      break;
    case DOUBLE_OPTION:
      fprintf(outfile, "%s\t%f\n", options[i].name, *(options[i].valp.d));
      break;
    case STRING_OPTION:
      if (*options[i].valp.s)
	fprintf(outfile, "%s\t%s\n", options[i].name, *(options[i].valp.s));
      break;
    }
  }
}


