#include "tako/object_detect.hpp"

namespace tako
{
    ObjectDetect::ObjectDetect()
    {
        cfg_ = tako::Config::get<cv::String> ("object_cfg");
        model_ = tako::Config::get<cv::String> ("object_model");
        confidThr_ = tako::Config::get<float> ("min_confidence");
        //preprocess net
        net_ = cv::dnn::readNetFromDarknet(cfg_, model_);
        std::cout<<"cfg : " << cfg_ <<std::endl;
        std::cout<<"model : " << model_ <<std::endl;
        std::cout<<"confidence Threshold : " <<confidThr_ <<std::endl;
        if(net_.empty())
        {
            std::cerr<<"Can't load network by using the following files:" <<std::endl;
            std::cerr<<"cfg-file:"<< cfg_ << std::endl;
            std::cerr<<"weight-file:" <<model_<< std::endl;
            std::cerr<<"Model can downloaded here:" <<std::endl;
            std::cerr<<"https://pjreddie.com/darknet/yolo/"<<std::endl;
            exit(-1);
        }
        //preprocess
        std::string classNames = tako::Config::get<std::string> ("object_classnames");
        std::ifstream classNamesFile(classNames.c_str());
        if(classNamesFile.is_open())
        {
            std::string className = "";
            while(std::getline(classNamesFile, className))
            {
                classNamesVec_.push_back(className);
            }
        }
        else
        {
           std::cerr<<"Cant load classnames" <<std::endl;
           exit(-1);
        }
        classNamesFile.close();
    }

    std::vector<tako::Object> ObjectDetect::object_detect(cv::Mat frame)
    {
        
        if(frame.empty())
        {
            std::cerr<<"image is empty" <<std::endl;
            cv::waitKey();
            exit(-1);
        }

        if(frame.channels() == 4)
        {
            cv::cvtColor(frame, frame, cv::COLOR_BGRA2BGR);
        }
        // Convert Mat to batch of images
        cv::Mat inputBlob = cv::dnn::blobFromImage(frame, 1 / 255.F, cv::Size(416,416), cv::Scalar(), true, false);

        net_.setInput(inputBlob, "data");//set the network input

        cv::Mat detectionMat = net_.forward("detection_out"); // compute output

        //store object class
        cv::VideoWriter writer;
        std::vector<tako::Object> node_object;
        for(int i = 0; i <detectionMat.rows; i++)
        {
            const int probability_index = 5; // the confidence probability
            const int probability_size = detectionMat.cols - probability_index;

            //std::cout << "probability_size="<<probability_size<<std::endl;

            float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);

            size_t objectClass = std::max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
            float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);

            if( confidence > confidThr_)
            {
                tako::Object item;
                float x_center = detectionMat.at<float>(i, 0) * frame.cols;// restore normalize
                float y_center = detectionMat.at<float>(i, 1) * frame.rows;
                
                float width = detectionMat.at<float>(i, 2) * frame.cols;
                float height = detectionMat.at<float>(i, 3) * frame.rows;
                /*cv::Point p1(cvRound(x_center - width/2), cvRound(y_center - height / 2));
                cv::Point p2(cvRound(x_center + width/2), cvRound(y_center + height / 2));
                cv::Rect object(p1, p2);

                cv::Scalar object_roi_color(0, 255, 0);

                if(true)
                {
                    cv::rectangle(frame, object, object_roi_color);
                }
                else
                {
                    cv::Point p_center(cvRound(x_center), cvRound(y_center));
                    cv::line(frame, object.tl(), p_center, box, 1);
                }
                
                cv::String className = objectClass < classNamesVec_.size() ? classNamesVec_[objectClass] : cv::format("unknown(%d)", objectClass);
                cv::String label = cv::format("%s: %.2f", className.c_str(), confidence);
                int baseLine = 0;
                cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                cv::rectangle(frame, cv::Rect(p1, cv::Size(labelSize.width, labelSize.height + baseLine)), object_roi_color, cv::FILLED);
                cv::putText(frame, label, p1 + cv::Point(0, labelSize.height), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0));
                */
                // output
                item.storeVarious(className, confidence, width, height);
                node_object.push_back(item);
            }
            /*if(writer.isOpened())
            {
                writer.write(frame);
            }
            cv::imshow("YOLO: Detections, " , frame);
            */
        }
        return node_object;
    }

    ObjectDetect::~ObjectDetect()
    {

    }
}