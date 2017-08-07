#ifndef _IMAGE_GRAPH_H
#define _IMAGE_GRAPH_H

#include "CImg.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <dijkstra/dijkstra.h>

using namespace std;
using namespace cimg_library;


template<typename T1, typename T2>
pair<T1, T2> operator+ (const pair<T1, T2>& l, const pair<T1, T2>& r)
{
    return {l.first+r.first, l.second+r.second};
}

template <typename T> class image_graph
{
    using p_ii = pair<int, int>;
    typedef struct {
        float r,g,b;
    } COLOUR;
private:
    const CImg<T>& _image;

public:
    image_graph(const CImg<T>& image) : _image(image)
    {

    }
    ~image_graph()
    {

    }
    // provide an integer accessor to nodes
    uint grid2idx(const int x, const int y)
    {
        // todo add asserts
        return x + y*(_image.width()); // todo - unittest candidate
    }
    pair<int, int> idx2grid(const uint idx) //todo - unittest candidate
    {
        // todo add asserts
        int y = int (floor(float(idx) / float(_image.width())));
        int x = idx - (y * _image.width());
        return {x, y};
    }

    // provide a distance function : takes 2 inputs
    float dist2nodes(const p_ii& node1, const p_ii& node2) //todo remove float assumption: templates
    {
        float d = 0.0f;
        for (int c = 0; c < _image.spectrum(); c++) // not always a very colorful world :-)
          {
              float intensityDist = _image(node1.first, node1.second, 0, c) - _image(node2.first, node2.second, 0, c);
              if (fabs(intensityDist) < 10) // noise level
                {
                    intensityDist = 0.0f;
                }
              d += pow(intensityDist, 2);
          }
        d = sqrt(d);
        return d;
    }
    // provide a function to return neighbors
    vector<pair<float, uint>> getNeighbors(const uint idx) //todo remove 8 nborhood assumption
    {
        pair<int, int> xy = idx2grid(idx);
        assert(xy.first >= 0 && xy.first < _image.width());
        assert(xy.second >=0 && xy.second < _image.height());
        vector<pair<int, int>> stencil = {p_ii(-1, 0), p_ii(0, -1), p_ii(1, 0), p_ii(0, 1), p_ii(1, 1),
                                          p_ii(1, -1), p_ii(-1, -1), p_ii(-1, 1)}; // todo add unittest with sum
        vector<pair<float, uint>> output;
        for (const auto& offset : stencil)
          {
              p_ii loc = offset + xy; // loc is a nbor
              if (loc.first < 0 || loc.first >= _image.width() || loc.second < 0 || loc.second >= _image.height())
                {
                    continue;
                }
              float d = dist2nodes(xy, loc);
              output.emplace_back(d, grid2idx(loc.first, loc.second));
          }
        return output;
    }
    // this function is taken from stackoverflow
    COLOUR GetColour(float v, float vmin, float vmax)
    {
        assert(vmin < vmax);
        COLOUR c = {1.0,1.0,1.0}; // white
        float dv;

        if (v < vmin)
            v = vmin;
        if (v > vmax)
            v = vmax;
        dv = vmax - vmin;

        if (v < (vmin + 0.25 * dv)) {
            c.r = 0;
            c.g = 4 * (v - vmin) / dv;
        } else if (v < (vmin + 0.5 * dv)) {
            c.r = 0;
            c.b = 1 + 4 * (vmin + 0.25 * dv - v) / dv;
        } else if (v < (vmin + 0.75 * dv)) {
            c.r = 4 * (v - vmin - 0.5 * dv) / dv;
            c.b = 0;
        } else {
            c.g = 1 + 4 * (vmin + 0.75 * dv - v) / dv;
            c.b = 0;
        }

        return(c);
    }
};


// tests using dijkstra [todo: break this function]
void test_image_dij(const string& imgFname)
{
    CImg<unsigned char> image(imgFname.c_str());
    image_graph<unsigned char> ig(image);
    // function to get seeds
    CImgDisplay main_disp(image, "click for seeds");
    vector<pair<int, int>> points;
    while (!main_disp.is_closed())
      {
          main_disp.wait();
          if (main_disp.button() && main_disp.mouse_y() >= 0)
            {
                const int y = main_disp.mouse_y();
                const int x = main_disp.mouse_x();
                points.emplace_back(x, y);
            }
          main_disp.flush();
      }
    //
    assert(!points.empty());
    cout << "Number of seeds entered " << points.size() << endl;
    vector<uint> seeds;
    for (auto& p : points)
      {
          seeds.emplace_back(ig.grid2idx(p.first, p.second));
          cout <<(ig.grid2idx(p.first, p.second))  << endl;
      }
    //
    function<vector<pair<float, uint>> (const uint)> fAccessNbors = [&ig](uint idx)
        {
            return ig.getNeighbors(idx);
        };
    // ready to call Dijkstra
    uint nbNodes = image.width() * image.height();
    dijkstra dij(fAccessNbors, seeds, nbNodes);
    vector<float> distOutput = dij.runInference();
    // compute bounds for distance function : Notice auto's nice feature
    auto min_max_loc = minmax_element(distOutput.begin(), distOutput.end());
    auto min = *(min_max_loc.first);
    auto max = *(min_max_loc.second);
    // get distance map
    CImg<float> dMap(image.width(), image.height(), 1, 3, 0); //fixed nchannels = 3
    CImg<float> rawDist(image.width(), image.height(), 1, 1, 0);
    for (uint i = 0; i < distOutput.size(); i++)
      {
          auto d = distOutput[i];
          auto val = ig.GetColour(d, min, max);
          auto loc = ig.idx2grid(i);
          dMap(loc.first, loc.second, 0, 0) = val.r;
          dMap(loc.first, loc.second, 0, 1) = val.g;
          dMap(loc.first, loc.second, 0, 2) = val.b;
          rawDist(loc.first, loc.second, 0, 0) = d;
      }
    (dMap, rawDist).display("Check distance map! and raw distances (on right)");
    // lets look at segmentation IDs
    auto segIds = dij.getSegmentationId();
    CImg<uint> segMap(image.width(), image.height(), 1, 1, 0);
    for (uint i = 0; i < segIds.size(); i++)
      {
          auto loc = ig.idx2grid(i);
          auto segId = segIds[i];
          segMap(loc.first, loc.second, 0, 0) = segId;
      }
    (dMap, segMap).display("segmentation Ids on right image!");
}




#endif
