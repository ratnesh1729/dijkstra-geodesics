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
    test_image_dij();
    return 0;
}
