#include "tako/common_include.hpp"
#include <string>
#include <vector>
#include <iostream>

//DBoW3
#include "DBoW3/DBoW3.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    //read the image
    cout << "read images" << endl;
    vector<Mat> images;
    for (int i = 0; i < 10; i++)
    {
        string path = "./data2/"+to_string(i+1)+".png";
        images.push_back( imread(path, 0) );
    }

    //detect ORB features
    cout<<"detecting ORB feature " <<endl;

    Ptr< Feature2D > detector = ORB::create();
    vector<Mat> descriptors;
    cout<<"detecting image ...."<<endl;
    for(Mat& image:images)
    {
        cout<<"image run ..." <<endl;
        vector<KeyPoint> keypoints;
        Mat descriptor;
        detector->detectAndCompute( image, Mat(), keypoints, descriptor);
        descriptors.push_back(descriptor);
    }


    //create vocabulary
    cout<< " creating Vocabulary " <<endl;
    DBoW3::Vocabulary vocab;
    vocab.create( descriptors );

    cout<<"vocabulary info:" <<vocab<<endl;
    vocab.save("vocabulary.yml.gz");
    cout<<"done"<<endl;

    return 0 ;
}