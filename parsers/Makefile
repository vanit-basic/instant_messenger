
dom: dom.o parse.o 
	g++ $^ `xml2-config --libs` -o $@

dom.o : dom.cpp
	g++ -c $^ -o $@

parse.o: parse.c
	gcc -c $^ `xml2-config --cflags` -o $@

sax: sax_parser.c
	gcc $^ -o $@ `xml2-config --cflags --libs`

clean:
	rm -f sax dom *.o
