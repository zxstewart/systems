#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"


//supplemental functions from Filter.cpp, inline functions reduce the function call overhead
//did not need to include in cpp file, could've just added "inline" in the original function definition
inline int Filter::getDivisor()
{
    return divisor;
}
inline int Filter::getSize()
{
    return dim;
}
inline int Filter::get(int r, int c)
{
    return data[ r * dim + c ];
}

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}

//modified
double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> height = input -> height;
  output -> width = input -> width;

//reordered loops to traverse more efficiently with a stride of 1
    //original program had stride of 1025 (max image size) due to traversing through columns first
  for(int row = 1; row < (input -> height)-1; row++)
  {
    for(int col = 1; col < (input -> width)-1; col++)
    {

      int R = 0;
      int G = 0;
      int B = 0;

      for (int i = 0; i < 3; i++)
      {
          for (int j = 0; j < 3; j++)
          {
        //loop unrolling to reduce iterations and number of checks that occur (easier to see when looking at assembly breakdown)
          R += input->color[COLOR_RED][row + i - 1][col + j - 1] * filter->get(i, j);
          G += input->color[COLOR_GREEN][row + i - 1][col + j - 1] * filter->get(i, j);
          B += input->color[COLOR_BLUE][row + i - 1][col + j - 1] * filter->get(i, j);
          }
      }

      R /= filter->getDivisor();
      G /= filter->getDivisor();
      B /= filter->getDivisor();

    //separate if statements are faster than trying to combine into one long one
    //long chained expression performs an extra cast to bool after every comparison
      if (R < 0)
      {
          R = 0;
      }
      if (G < 0)
      {
          G = 0;
      }
      if (B < 0)
      {
          B = 0;
      }
      if (R > 255)
      {
          R = 255;
      }
      if (G > 255)
      {
          G = 255;
      }
      if (B > 255)
      {
          B = 255;
      }

      output->color[COLOR_RED][row][col] = R;
      output->color[COLOR_GREEN][row][col] = G;
      output->color[COLOR_BLUE][row][col] = B;
      
    }
  }
//untouched from original code
  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
