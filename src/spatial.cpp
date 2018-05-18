#include "tako/spatial.hpp"
/*struct NodeFind : public std::binary_function<tako::Node,tako::Node, bool>
{
    bool operator()(const tako::Node &node1, const tako::Node &node2) const
    {
        return node1.id_ == node2.id_;
    }
};
*/
namespace tako
{
    Spatial::Spatial(std::vector<tako::Node> &nodes)
    {
        int i = 0;
        for(tako::Node &node1:nodes)
        {
            float dist = 100 ;
            tako::Node node_temp1;
            for(tako::Node &node2:nodes)
            {
                if(node1.id_ == node2.id_)
                {
                    continue;
                }
                else
                {
                    if(dist > (this->getDistXY(node1, node2)))
                    {
                        dist = this->getDistXY(node1, node2);
                        node_temp1 = node2;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            float dist_s = 99;
            tako::Node node_temp2;
            for(tako::Node &node3:nodes)
            {
                if(node3.id_ == node_temp1.id_ || node1.id_ == node3.id_)
                {
                    continue;
                }
                else
                {
                    if( dist_s > (this->getDistXY(node1,node3)))
                    {
                        dist_s = this->getDistXY(node1, node3);
                        node_temp2 = node3;      
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            graph_[i].push_back(node_temp1);
            graph_[i].push_back(node_temp2);
            i++;
        }
        std::cout << " spatial init finish ! " << std::endl;
        this->getCluster();
    }

    void Spatial::getCluster()
    {
        for(int i = 0; i < k_ ; i++)
        {
            std::cout << " the node : " << i+1 << std::endl;
            for(tako::Node node:graph_[i])
            {
                std::cout << " nearest is " << node.id_ << std::endl;
            }
            std::cout << std::endl;
        }
    }
    tako::Node Spatial::getMean(std::vector<tako::Node> graph)
    {
        int num = graph.size();
        float meanX = 0;
        float meanY = 0;
        tako::Node temp;
        for(int i = 0; i < num ; i++ )
        {
            meanX += graph[i].position_.at<float>(0,3);
            meanY += graph[i].position_.at<float>(1,3);
        }
        temp.position_.at<float>(0,3) = meanX / num;
        temp.position_.at<float>(1,3) = meanY / num;
        return temp;
    }

    cv::Mat Spatial::getDescriptor(tako::Node &node)
    {
        int key;
        tako::Node temp;
        float dist = 100;
        for(int i = 0; i < k_ ; i++)
        {
           temp = this->getMean(graph_[i]) ;
           if( dist > this->getDistXY(node, temp))
           {
               key = i ;
               dist = this->getDistXY(node, temp);
           }
           else{
               continue;
           }
        }
        cv::Mat descriptor;
        int check = 0;
        for(tako::Node &nodeTemp:graph_[key])
        {
           if( check == 0 ) 
           {
               descriptor = nodeTemp.descriptor_ ; 
               check ++ ;
           }
           else
           {
               descriptor = descriptor + nodeTemp.descriptor_;
           }
        }
        cv::divide(descriptor, graph_[key].size(), descriptor);
        return descriptor;
    }

    float Spatial::spatialScoring()
    {

    }

    float Spatial::getDistXY(tako::Node &node1, tako::Node &node2)
    {
        return std::sqrt((node1.position_.at<float>(0,3) - node2.position_.at<float>(0,3))*(node1.position_.at<float>(0,3) - node2.position_.at<float>(0,3))
                        + (node1.position_.at<float>(1,3) - node2.position_.at<float>(1,3))*(node1.position_.at<float>(1,3) - node2.position_.at<float>(1,3)) );
    }
    Spatial::~Spatial()
    {
        
    }
/*
    //k means

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
        for( i =  0; i < k_  ; i++)
        {
            if(nodes[i].position_.at<float>(0,3) == 0.0 && nodes[i].position_.at<float>(1,3) == 0.0)
            {
                i++ ;
                continue;
            }
            else
            {
                means[i].position_.at<float>(0,3) = nodes[i].position_.at<float>(0,3);
                means[i].position_.at<float>(1,3) = nodes[i].position_.at<float>(1,3);
                i++;
            }
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
            std::cout << "new Var : " << newVar <<" Old var : " << oldVar << std::endl;
        }
            // test output
            for( label = 0; label < k_; label++)
            {
                std::cout << "the " << label + 1 << " cluster : " <<std::endl;
                std::cout << "the mean : " <<"("<< means[label].position_.at<float>(0,3)<<" , " <<means[label].position_.at<float>(1,3)<<")"<< std::endl;
                std::vector<tako::Node> t = clusters[label];
                for( i = 0; i < t.size(); i++)
                {
                    std::cout <<"node id : "<< t[i].id_ <<" ("<< t[i].position_.at<float>(0,3) <<" , "<< t[i].position_.at<float>(1,3)<<")"<< std::endl;
                }
                std::cout << std::endl;
            }

    }

    cv::Mat Spatial::MeanDescriptor(tako::Node &node)
    {
        //double value = 5000.0;
        int key = 0; // which cluster
        
        for( int i = 0; i < k_ ; i++)
        {
            double temp = std::sqrt((node.position_.at<float>(0,3) - means[i].position_.at<float>(0,3))*(node.position_.at<float>(0,3) - means[i].position_.at<float>(0,3))
                                +(node.position_.at<float>(1,3) - means[i].position_.at<float>(1,3))*(node.position_.at<float>(1,3) - means[i].position_.at<float>(1,3))
            );

            if(temp < value)
            {
                key = i ;
                value = temp ;
            }
            else
            {
                continue;
            }
        }
        
       for(int i = 0; i < k_; i++)
       {
           
       }

        cv::Mat mean_descriptor;
        std::vector<tako::Node> t = clusters[key];
        for( int i = 0; i < t.size(); i++)
        {
            if( i == 0)
            {
                mean_descriptor = t[i].descriptor_;
            }
            else
            {
                mean_descriptor = t[i].descriptor_ + mean_descriptor;
            }
        }
        cv::divide(mean_descriptor, t.size(), mean_descriptor);
        return mean_descriptor;
    }
*/

}