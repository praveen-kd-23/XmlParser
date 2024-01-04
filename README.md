**XmlParser**

A dynamic XML parser library designed to extract XML elements through key-value pairs.

**Requirements**

Libexpat >= 2.5.0

**Instructions**

Create a XML object for the given xml file

```
XML *root = xml_parse("filename.xml");
```

To Iterate all the key-value pairs of the elements call xml_iterate_key_value_pairs method with XML object and a callback function as parameter .
```

void callback(const char *key, const char *value, void *user_data){
    
}
xml_iterate_key_value_pairs(root, callback, user_data);
```

**Compilation**

Use make command to compile and install

```
make

make install
```

