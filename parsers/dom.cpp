extern "C" {
#include "parse.h"
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return(1);
	
    readXMLFile(argv[1]);
    return 0;
}
