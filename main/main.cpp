#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/utility.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;


#include <dijkstra/dijkstra.h>
#include "image-graph.h"

int main (int argc, char** argv)
{
    if (argc != 2)
      {
          cout << "\n Needs an input image: Please specify an input image file" << endl;
          exit(0);
      }
    string fname = argv[1];
    test_image_dij(fname);
    return 0;
}
