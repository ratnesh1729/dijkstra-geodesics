#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H
#include <iostream>
#include <limits>
#include <functional>
#include <set>
#include <tuple> // for returning from function
#include <algorithm>
using namespace std;

//todo can be optimized by just getting the distance mask or transform ? Yes!!
class dijkstra
{
    using dNode = pair<float, uint>; //dist and node as pair
    using nBors = vector<dNode>;
    constexpr static const float _INFINITY =  std::numeric_limits<float>::infinity();

private:
    set<dNode> _prQ; //priority queue : default less comparator
    function<nBors(const uint node)>& _getNbs; //get neighbors
    vector<uint> _seeds;
    vector<float> _distances;
    vector<uint> _propagators;
    uint _nbNodes;
    bool _inferenceCompletion;
    // push seeds onto set/Queue
    // todo take priority into account: need to modify constructor
    void setSeeds();
    void postSanityCheck();
    void preSanityCheck();

 public:
    dijkstra(function<nBors(const uint node)>& getNbs, vector<uint>& seeds,
             const uint nbNodes);
    ~dijkstra();
    vector<float>& runInference();
    vector<uint>& getSegmentationId();

};
void test_dij();

//some code for dijkstra testing
/*

#include "image-graph.h"

*/
#endif
