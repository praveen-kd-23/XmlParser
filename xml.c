#include <xml.h>

void add_siblings(XML *cur , XML *sibling){

    if(!cur->siblings_head) {
        cur->siblings_head = cur->siblings_tail = sibling ;
    }
    else {
        cur->siblings_tail->siblings_tail = sibling ;
        cur->siblings_tail = cur->siblings_tail->siblings_tail ;
    }
}

void start_handler(void *user_data, const char *el, const char **attr)
{
    XML_UTILITIES *utility = (XML_UTILITIES*)user_data;
    XML *cur = utility->xml;
    XML *xml;
    Attributes *iter;

    xml = (XML*)malloc(sizeof(XML));

    xml->name = strdup(el);

    for(int i=0; attr[i] ; i+=2){
        iter = (Attributes*)malloc(sizeof(Attributes));

        iter->key = strdup(attr[i]);
        iter->value = strdup(attr[i+1]);

        if(!xml->head) {
            xml->head = xml->tail = iter;
        }
        else{
           xml->tail->next = iter ;
           xml->tail = xml->tail->next;
        }
    }

    if(!cur->child) {
      cur->child = xml;
    }
    else {
      add_siblings(cur->child,xml);
    }

    xml->parent = cur;

    utility->xml = xml;

    XML_SetUserData(utility->parser,utility);
}

void end_handler(void *user_data, const char *el)
{
    XML_UTILITIES *utility = (XML_UTILITIES*)user_data;
    XML *cur = utility->xml;

    utility->xml = cur->parent;

    XML_SetUserData(utility->parser,utility);
}              

XML* xml_parse(char *filename){
     
     XML_Parser parser;
     XML_UTILITIES *user_data;
     char *xmlstring ;
     FILE *fp = NULL;
     XML *root;

     fp = fopen(filename,"r");

     if(!fp) {
        fprintf(stderr, "File %s does not Exists\n",filename);
        return NULL ;
     }

     xmlstring = malloc(MAXCHARS);

     fread(xmlstring,sizeof(char),MAXCHARS,fp);

     parser = XML_ParserCreate(NULL);

     if(!parser) {
        fprintf(stderr, "Parser not created\n");
        return NULL ;
     }

     root = (XML*)malloc(sizeof(XML));

     user_data = (XML_UTILITIES*)malloc(sizeof(XML_UTILITIES));

     user_data->xml = root;
     user_data->parser = parser;
     
     XML_SetUserData(parser,user_data);
     XML_SetElementHandler(parser, start_handler, end_handler);

     if(XML_Parse(parser,xmlstring,strlen(xmlstring),XML_TRUE) == XML_STATUS_ERROR){
       fprintf(stderr, "XML not well formed\n");
       free(root);
       return NULL ;
     }

     fclose(fp);
     XML_ParserFree(parser);

     return root;
}