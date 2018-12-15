
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
	g++  $^ `xml2-config --cflags --libs` $(cflags) --shared -fPIC --std=c++11 -o $(shared)

test: $(test_src) $(shared)
	g++  $^ `xml2-config --cflags --libs` $(cflags) --std=c++11 -o $(test_dir)/xml
	cd db_tests; ./xml

clean:
	rm -f $(shared) $(test_dir)/xml
