#include <expat.h>
#include <stdio.h>
#include <string.h>

#define MAXCHARS 1000000

struct Attributes_t;
typedef struct Attributes_t Attributes;

struct XML_t;
typedef struct XML_t XML;

struct Attributes_t{
  char *key;
  char *value;
  Attributes *next;
};

struct XML_t{
    char *name;
    Attributes *head;
    Attributes *tail;
    XML *child;
    XML *siblings_head;
    XML *siblings_tail;    
    XML *parent;
};

typedef struct {
    XML *xml;
    XML_Parser parser;
}XML_UTILITIES;

typedef enum {
  false = 0,
  true = 1
}bool;

typedef void (*xml_iterate_cb) (const char *key, const char *value);

void xml_print_structure(XML *root, int level);
XML* xml_parse(char *filename);
void xml_iterate_key_value_pairs(XML *root , xml_iterate_cb callback_func);
