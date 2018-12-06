/**
 * section: Tree
 * synopsis: Navigates a tree to print element names
 * purpose: Parse a file to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and print
 *          all the element name in document order.
 * usage: tree1 filename_or_URL
 * test: tree1 test2.xml > tree1.tmp && diff tree1.tmp $(srcdir)/tree1.res
 * author: Dodji Seketeli
 * copy: see Copyright for the status of this software.
 */

#include <libxml/tree.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <string.h>

/*
 *To compile this file using gcc you can type
 *gcc `xml2-config --cflags --libs` -o xmlexample libxml2-example.c
 */

xmlChar* getNodeValue(xmlNode * a_node) {
	xmlChar* value = NULL;
	if (a_node->type == XML_TEXT_NODE) {
		value = a_node->content;
	} else {
		for (xmlNode * cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
			if(cur_node->type == XML_TEXT_NODE) {
				value = cur_node->content; 
				break;
			}
		}
	}
	return value;
}

/**
 * print_element_names:
 * @a_node: the initial xml node to consider.
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 */
void print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;
	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			const char* name = (char*)cur_node->name;
			const char* value = (char*)getNodeValue(cur_node);
			printf("name: %s\n", name);
			if(value) printf("value: %s\n", value);
		} 
		print_element_names(cur_node->children);
	}
}

void readXMLFile(char* filePath) {
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;


    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(filePath, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", filePath);
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    print_element_names(root_element);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}

