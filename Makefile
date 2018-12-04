
dom: parse.c 
	@#make clean
	@gcc $^ `xml2-config --cflags --libs` -o $@

sax: sax_parser.c
	@#make clean
	@gcc $^ -o $@ `xml2-config --cflags --libs`

clean:
	@rm -f sax dom
