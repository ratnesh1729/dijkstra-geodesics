#include "dijkstra.h"
#include <cassert>
void dijkstra::setSeeds()
{
    for (auto& seed : _seeds)
      {
          _prQ.emplace(0.0f, seed);
          _distances[seed] = 0.0f;
          _propagators[seed] = seed;
      }
}
void dijkstra::postSanityCheck()
{
    for (auto& d : _distances)
      {
          if (d >= _INFINITY)
            {
                cout << "Inference Unsuccessful!! some nodes unvisited by dist!"
                     << endl;
                exit(0);
            }
      }
    for (auto& p : _propagators)
      {
          if (p < 0)
            {
                cout << "Inference Unsuccessful!! some nodes unvisited by prop!"
                     << endl;
                exit(0);
            }
          // also each element should be a number in the seeds
          bool isInSeed = false;
          for (const auto& s : _seeds)
            {
                if (s == p)
                  {
                      isInSeed = true;
                  }
            }
          if (!isInSeed)
            {
                cout << "It should not happen that a propagated value is different from a seed";
                exit(0);
            }
      }
}
void dijkstra::preSanityCheck()
{
        // check is a seedId is > seed
}
dijkstra::dijkstra(function<nBors(const uint node)>& getNbs, vector<uint>& seeds,
                   const uint nbNodes)
    : _getNbs(getNbs), _seeds(seeds), _nbNodes(nbNodes)
{
    if (seeds.size() == 0)
      {
          cout << "Seeds are needed to compute shortest paths from " << endl;
          exit(0);
      }
    // initialize tables
    _propagators.resize(_nbNodes, -1);
    _distances.resize(_nbNodes, INFINITY);
    _inferenceCompletion = false;
    setSeeds();
}
dijkstra::~dijkstra()
{
    // all are vectors - we need not empty() - RAII
}
vector<float>& dijkstra::runInference()
{
    while(!_prQ.empty())
      {
          dNode tmp = *_prQ.begin();
          _prQ.erase(_prQ.begin());
          float nodeDist = _distances[tmp.second];
          nBors neighbors = _getNbs(tmp.second);
          for (const auto& nb : neighbors) // why no compilation error here even when no const ! ?
            {
                // float dist = nodeDist + _distFunc(tmp.second, nb);
                float dist = nodeDist + nb.first;
                // assert(_distFunc(tmp.second, nb) == _distFunc(nb, tmp.second));
                if (dist < _distances[nb.second])
                  {
                      _distances[nb.second] = dist;
                      _propagators[nb.second] = _propagators[tmp.second];
                      _prQ.emplace(dist, nb.second);
                  }
            }
      }
    postSanityCheck();
    _inferenceCompletion = true;
    return _distances;
}
vector<uint>& dijkstra::getSegmentationId()
{
    assert(_inferenceCompletion == true);
    if (!_inferenceCompletion)
      {
          cout << "Cannot return unless inference is complete " << endl;
          exit(0);
      }
    return _propagators;
}
