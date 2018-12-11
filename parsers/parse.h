

struct xmlChar;
struct xmlNode;

xmlChar* getNodeValue(xmlNode * a_node);

void print_element_names(xmlNode * a_node);

void readXMLFile(char* filePath);
