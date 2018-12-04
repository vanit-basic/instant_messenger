#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <iostream>
#include <fstream>

#ifdef LIBXML_TREE_ENABLED

std::ofstream file("text.txt");

void edit(xmlNode* a_node) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            const char* name = (char*)cur_node->name;
             if (0 == strcmp(name, "login")) {
                xmlNodeSetContent(cur_node->children, "signin");
            }
            const char* value = (xmlNodeGetContent(cur_node->children);
            if (0 == strcmp(value, "Mane")) {
                xmlNodeSetContent(cur_node->children, "Kolibri");
            }
        }
        edit(cur_node->children);
    }
    
}

void print_element_names(xmlNode * a_node) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            const char* name = (char*)cur_node->name;
            const char* value = (char*)xmlNodeGetContent(cur_node->children);
            std::cout << name << std::endl;
            std::cout << value << std::endl;
        }
        print_element_names(cur_node->children);
    }

}

int main(int argc, char **argv) {
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    if (argc == 3) {
        xmlSaveFormatFileEnc(argv[2], doc, "UTF-8", 1);
    } else {
        print_element_names(root_element);
    }

    LIBXML_TEST_VERSION

        /*parse the file and get the DOM */
        doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    print_element_names(root_element);

    /*free the document */
    xmlFreeDoc(doc);

    xmlCleanupParser();

    return 0;
}

#else

int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}

#endif
