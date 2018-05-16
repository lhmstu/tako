#include "tako/spatial.hpp"
namespace tako
{
    Spatial::Spatial(std::vector<tako::Node> &nodes)
    {
    }

    float Spatial::spaScoring(std::vector<tako::Node> &main_node, std::vector<tako::Node>& nodes)
    {
        
    }
    //k means
    float Spatial::getDistXY(tako::Node &node1, tako::Node &node2)
    {
        return std::sqrt((node1.position_.at<float>(0,3) - node2.position_.at<float>(0,3))*(node1.position_.at<float>(0,3) - node2.position_.at<float>(0,3))
                        + (node1.position_.at<float>(1,3) - node2.position_.at<float>(1,3))*(node1.position_.at<float>(1,3) - node2.position_.at<float>(1,3)) );
    }

    int Spatial::clusterOfNode(tako::Node means[], tako::Node &node)
    {
        float dist = this->getDistXY(means[0], node);
        float temp;
        int label = 0 ; //label (which cluster);
        for(int i = 1; i < k_ ; i++)
        {
            temp = this->getDistXY(means[i], node);
            if(temp < dist)
            {
                dist = temp ; 
                label = i;
            }
        }
        return label;
    }

    float Spatial::getVar(std::vector<tako::Node> clusters[], tako::Node means[])
    {
        float var = 0;
        for(int i = 0 ; i < k_ ; i++)
        {
            std::vector<tako::Node> t = clusters[i];
            for( int j = 0; j <t.size(); j++)
            {
                var += this->getDistXY(t[j], means[i]);
            }
        }
        return var;
    }

    tako::Node Spatial::getMeans(std::vector<tako::Node> cluster)
    {
        int num = cluster.size();
        float meansX = 0;
        float meansY = 0;
        tako::Node t;
        for(int i = 0; i < num ; i++)
        {
            meansX += cluster[i].position_.at<float>(0,3);
            meansY += cluster[i].position_.at<float>(1,3);
        }
        
        t.position_.at<float>(0,3) = meansX / num;
        t.position_.at<float>(1,3) = meansY / num;
        return t;
    }

    // kmeans kernel
    void Spatial::KMeans(std::vector<tako::Node> &nodes)
    {
        //std::vector<tako::Node> clusters[k_];
        //tako::Node means[k_];
        int i = 0;
        // initial means of mass cluster
        for( i = 0; i < k_ ; i++)
        {
            means[i].position_.at<float>(0,3) = nodes[i].position_.at<float>(0,3);
            means[i].position_.at<float>(1,3) = nodes[i].position_.at<float>(1,3);
        }

        int label = 0;
        // according initial seperate cluster
        for( i = 0; i!= nodes.size(); i++)
        {
            label = this->clusterOfNode(means, nodes[i]);
            clusters[label].push_back(nodes[i]);
        }

        float oldVar = -1;
        float newVar = this->getVar(clusters, means);
        //when new and old function error small than 1 ,so stop iterator
        while(std::abs(newVar - oldVar) >= 1 ) 
        {
            for( i = 0; i < k_ ; i++) // update every cluster's center
            {
                means[i] = this->getMeans(clusters[i]);
            }
            oldVar = newVar;
            newVar = this->getVar(clusters, means); // compute new function

            for( i = 0; i < k_ ; i++)
            {
                clusters[i].clear();
            }
            // according new mean of mass create new cluster
            for( i = 0; i!=nodes.size(); i++)
            {
                label = clusterOfNode( means, nodes[i]);
                clusters[label].push_back(nodes[i]);
            }
        }

    }

    Spatial::~Spatial()
    {
        
    }
}