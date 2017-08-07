#include <dijkstra/dijkstra.h>
#include "testdij.h"
#include <functional>
#include <algorithm>

vector<float> testDij();

DijTest::DijTest()
{

}

DijTest::~DijTest()
{

}

void DijTest::SetUp() {};

void DijTest::TearDown() {};

TEST_F(DijTest, UnitTest1)
{
    vector<float> distFinal = {0.0, 4.0, 12.0, 19.0, 21.0, 11.0, 9.0, 8.0, 14.0};
    vector<float> actualDist = testDij();
    ASSERT_EQ(distFinal, actualDist);
}


vector<float> testDij() //todo - move to setup and teardown
{
    /*
      ---------- testing this graph below [geeks from geeks]
     http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
               8        7      9
      ---- n1-------n2----n3-------n4
     4|    |       2|\    |         |
      no 11| ------ n8 \6 |4    10 |
     8|    |/   7    |  \ |         |
      ----n7--------n6---n5---------
               1
     */
    using vuint = vector<uint>;
    vuint n0 = {1, 7};
    vuint n1 = {0, 2, 7};
    vuint n2 = {1, 8, 5, 3};
    vuint n3 = {2, 4, 5};
    vuint n4 = {3, 5};
    vuint n5 = {2, 3, 4};
    vuint n6 = {5, 7, 8};
    vuint n7 = {0, 1, 6, 8};
    vuint n8 = {2, 6, 7};
    vector<vuint> neighbors = {n0, n1, n2, n3, n4, n5, n6, n7, n8};
    function<float(const uint, const uint)> dFunc = [](const uint id1, const uint id2)
        {
            if (id1 == id2)
              {
                  cout << "You should not be asking same Ids "<< id1 << " "
                  << id2 << endl;
                  exit(0);
              }
            // build matrix
            // provide view sort of function
            vector<vector<float>> distMatrix(9, vector<float>(9, -1.0f));
            distMatrix[0][1] = 4.0f;
            distMatrix[1][0] = 4.0f;

            distMatrix[0][7] = 8.0f;
            distMatrix[7][0] = 8.0f;

            distMatrix[1][2] = 8.0f;
            distMatrix[2][1] = 8.0f;

            distMatrix[1][7] = 11.0f;
            distMatrix[7][1] = 11.0f;

            distMatrix[2][3] = 7.0f;
            distMatrix[3][2] = 7.0f;

            distMatrix[2][8] = 2.0f;
            distMatrix[8][2] = 2.0f;

            distMatrix[2][5] = 4.0f;
            distMatrix[5][2] = 4.0f;

            distMatrix[3][4] = 9.0f;
            distMatrix[4][3] = 9.0f;

            distMatrix[3][5] = 14.0f;
            distMatrix[5][3] = 14.0f;

            distMatrix[4][5] = 10.0f;
            distMatrix[5][4] = 10.0f;

            distMatrix[5][6] = 2.0f;
            distMatrix[6][5] = 2.0f;

            distMatrix[6][8] = 6.0f;
            distMatrix[8][6] = 6.0f;

            distMatrix[6][7] = 1.0f;
            distMatrix[7][6] = 1.0f;

            distMatrix[7][8] = 7.0f;
            distMatrix[8][7] = 7.0f;

            return distMatrix[id1][id2];
        };
    function<vector<pair<float, uint>> (const uint)> fAccessNbors = [&neighbors, &dFunc](uint idx)
        {
            vector<pair<float, uint>> output;
            for (auto p : neighbors[idx])
              {
                  float d = dFunc(idx, p);
                  output.emplace_back(d, p);
              }
            return output;
        };
    // need to build a distance function
    // final distance matrix
    vector<float> distOutput;
    {
        // actual seeds
        vector<uint> seeds = {0}; //no is the source
        dijkstra dij(fAccessNbors, seeds, 9);
        distOutput = dij.runInference();
        cout << "printing output on terminal" << endl;
        for (auto&d : distOutput)
          {
              cout << d << " ";
          }
        cout << endl;
        cout << "printing seg ID " << endl;
        for (auto& p : dij.getSegmentationId())
          {
              cout << p << " ";
          }
        cout << endl;
    }
    return distOutput;
}
