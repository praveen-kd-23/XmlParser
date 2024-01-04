
#include <xml.h>

bool x_strcmp(const char *a, const char *b){

    if(!a || !b || (strlen(a) != strlen(b))){
        return false;
    }

    return strcmp(a,b) == 0 ? true : false;
}
void xml_iterate_key_value_pairs(XML *root , xml_iterate_cb callback_func, void *user_data){
     
     if(!root) return ;
     
     /* Iterate the attributes for the current element */
     if(root->head){
       Attributes *attr = root->head;
       const char *key = NULL;
       const char *value = NULL;

       while(attr) {
         
         if(x_strcmp(attr->key, "key")){
            key = attr->value;
         }
         else if(x_strcmp(attr->key, "value")){
            value = attr->value;
         }
         attr = attr->next;
        }
       
        if(key && value){
         callback_func(key, value, user_data);
        }
     }

     if(root->child){
       xml_iterate_key_value_pairs(root->child, callback_func, user_data);
     }

     XML *siblings = root->siblings_head;

     while(siblings){
      xml_iterate_key_value_pairs(siblings, callback_func, user_data);
      siblings = siblings->siblings_tail;
     }
}