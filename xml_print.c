#include <xml.h>

void print_element(XML *root, int level){

    for(int i=0;i<level;i++) {
        printf(" ");
    }
     
    printf("%s",root->name);

    if(root->head){
        Attributes *attr = root->head;

        while(attr) {
            printf(" ");
            printf("%s=%s",attr->key,attr->value);
            attr = attr->next;
        }

    }

    printf("\n");
}

void xml_print_structure(XML *root, int level) {
     
    if(!root) return ;

    print_element(root, level);
     
    if(root->child){
       xml_print_structure(root->child, level+1);
    }

    XML *siblings = root->siblings_head;

    while(siblings){
      xml_print_structure(siblings, level);
      siblings = siblings->siblings_tail;
    }

}