#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout << " usage: feature_extraction img1 and img2 " << endl;
        return 1;
    }

    Mat img_1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

    // init
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

    // step 1 keypoints
    orb->detect(img_1, keypoints_1);
    orb->detect(img_2, keypoints_2);

    // step 2 descriptors
    orb->compute(img_1, keypoints_1, descriptors_1);
    orb->compute(img_2, keypoints_2, descriptors_2);

    Mat outimg1;
    drawKeypoints(img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imwrite("orb_keypoint.png", outimg1);
    imshow("orb keypoint", outimg1);
    waitKey(0);

    // step 3 : using hamming distance
    vector<DMatch> matches;
    BFMatcher matcher (NORM_HAMMING);
    matcher.match( descriptors_1, descriptors_2, matches);


    // step 4 : matching  check
    double min_dist = 10000 , max_dist = 0;

    // find max distance and min distance
    for(int i = 0; i < descriptors_1.rows; i++)
    {
        double dist = matches[i].distance;
        if(dist < min_dist) min_dist = dist ;
        if(dist > max_dist) max_dist = dist ; 
    }

    cout << "max_dist : " << max_dist << endl;
    cout << "min_dist : " << min_dist << endl;

    // check
    std::vector<DMatch> good_matches;
    for(int i = 0 ; i < descriptors_1.rows; i++)
    {
        if(matches[i].distance <= max(2*min_dist, 30.0))
        {
            good_matches.push_back(matches[i]);
        }
    }

    // step 5 : draw the match final
    Mat img_match;
    Mat img_goodmatch;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match);
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
    imwrite("img_match.png",img_match);
    imwrite("img_goodmatch.png",img_goodmatch);
    
    imshow("img_match",img_match);
    imshow("img_goodmatch",img_goodmatch);
    waitKey(0);
    return 0 ;
}