
dom: parse.c
	@gcc $^ `xml2-config --cflags --libs` -o $@

sax: sax_parser.c
	@gcc $^ -o $@ `xml2-config --cflags --libs`

clean:
	@rm sax dom
