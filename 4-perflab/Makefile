CXX	= g++
CXXFLAGS= -g -O3 -fno-omit-frame-pointer -Wall

goals: judge
	echo "Done"

filter: FilterMain.cpp Filter.cpp cs1300bmp.cc
	$(CXX) $(CXXFLAGS) -o filter FilterMain.cpp Filter.cpp cs1300bmp.cc

filter-debug: FilterMain.cpp Filter.cpp cs1300bmp.cc
	$(CXX) $(CXXFLAGS) -o filter FilterMain.cpp Filter.cpp cs1300bmp.cc
##
## Parameters for the test run
##
FILTERS = gauss.filter vline.filter hline.filter emboss.filter
IMAGES = boats.bmp blocks-small.bmp
TRIALS = 1 2 3 4

judge: filter
	-./Judge -p ./filter -i boats.bmp -l storz-boats
	-./Judge -p ./filter -i blocks-small.bmp -l storz-blocks 
    
test:	filter
	@find filtered*bmp | xargs -I @@ bash -c 'cmp --silent @@ tests/@@ && echo @@ looks correct. || echo INCORRECT: @@ does not match the reference image tests/@@.'

clean:
	-rm -f *.o
	-rm -f filter
	-rm -f filtered-*.bmp

