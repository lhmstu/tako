#ifndef SPATIAL_HPP
#define SPATIAL_HPP
#include "tako/common_include.hpp"
#include "tako/config.hpp"
#include "tako/node.hpp"
#include "tako/keypoints.hpp"
#include "tako/database.hpp"

// K means
#define k_ 452
namespace tako
{
    class Spatial
    {
        class Config;

       public:
        std::vector<tako::Node> graph_[k_]; // start 0 
        tako::Node means[k_];
        //std::vector<tako::Node> clusters[k_];
        //tako::Node means[k_];


       public:
        Spatial(std::vector<tako::Node> &nodes) ;
        float getDistXY(tako::Node &node1, tako::Node &node2);
        void getCluster();
        tako::Node getMean(std::vector<tako::Node> graph);
        cv::Mat getDescriptor(tako::Node &node);
        
        float spatialScoring();
        ~Spatial();
        /*
       //compute Dist between two node
        cv::Mat MeanDescriptor(tako::Node &node); // 算出最相近的cluster中的descritpor
        //according center of mass, decide this node be define which cluster
        int clusterOfNode(tako::Node means[], tako::Node &node);
        //acquire the cluster's Var
        float getVar(std::vector<tako::Node> clusters[], tako::Node means[]);
        //acquire the mean about cluster
        tako::Node getMeans(std::vector<tako::Node> cluster);
        // k means kernel
        void KMeans(std::vector<tako::Node> &nodes);
        */
    };
}

#endif // SPATIAL_HPP