
src_dir := db_src

db_src := $(src_dir)/*.cpp

test_dir := db_tests

test_src := $(test_dir)/*.cpp

out_dir := libs

headers_dir := headers

cflags := "-I$(headers_dir)"

shared := $(out_dir)/libdb.so

$(shared): $(db_src)
	mkdir -p libs
	g++  $^ `xml2-config --cflags --libs` $(cflags) --shared -fPIC -o $(shared)

test: $(test_src) $(shared)
	g++  $^ `xml2-config --cflags --libs` $(cflags) -o $(test_dir)/xml

clean:
	rm -f $(shared) $(test_dir)/xml
