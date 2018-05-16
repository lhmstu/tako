#ifndef SPATIAL_HPP
#define SPATIAL_HPP
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/node.hpp"
#include "tako/keypoints.hpp"
#include "tako/database.hpp"

// K means
#define k_ 80
namespace tako
{
    class Spatial
    {
        class Config;

       public:
        std::vector<tako::Node> clusters[k_];
        tako::Node means[k_];


       public:
        Spatial(std::vector<tako::Node> &nodes) ;

       //compute Dist between two node
        float getDistXY(tako::Node &node1, tako::Node &node2);
        //according center of mass, decide this node be define which cluster
        int clusterOfNode(tako::Node means[], tako::Node &node);
        //acquire the cluster's Var
        float getVar(std::vector<tako::Node> clusters[], tako::Node means[]);
        //acquire the mean about cluster
        tako::Node getMeans(std::vector<tako::Node> cluster);
        // k means kernel
        void KMeans(std::vector<tako::Node> &nodes);
        
        float spaScoring(std::vector<tako::Node> &main_node, std::vector<tako::Node>& nodes);

        ~Spatial();
    };
}

#endif // SPATIAL_HPP