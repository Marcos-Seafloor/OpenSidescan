#ifndef SIDESCANIMAGER_H
#define SIDESCANIMAGER_H

#include "../thirdParty/MBES-lib/src/datagrams/DatagramParserFactory.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

/**
 * @brief The SidescanImager class
 *
 * Creates images out of sidescan data
 */
class SidescanImager : public DatagramEventHandler
{
public:


    SidescanImager(){

    }

    ~SidescanImager(){

    }

    void processSidescanData(unsigned int channel,std::vector<double> & data){

        if(channels.size() < channel+1){
            std::vector<std::vector<double>*> * u = new std::vector<std::vector<double>*>();
            channels.push_back(u);
        }

        std::vector<double> * v = new std::vector<double>();

        for(auto i=data.begin();i!=data.end();i++){
            //std::cerr << *i << " ";
            v->push_back(*i);
        }

        //std::cerr << std::endl;

        channels[channel]->push_back(v);
    }

    std::list<cv::Mat *> * generateImages(){
        std::list<cv::Mat *> * matrixes = new std::list<cv::Mat*>();

        std::cerr << "Generating images for " << channels.size() << " channels" << std::endl;

        for(unsigned int i=0;i<channels.size();i++){
            std::cerr << "Channel " << i << std::endl;

            cv::Mat img(channels[i]->size(),channels[i]->at(0)->size(), CV_64F,cv::Scalar(0));

            std::cerr << "Rows: " << channels[i]->size() << " Cols: " << channels[i]->at(0)->size() << std::endl;

            for(unsigned int j=0;j<channels[i]->size();j++){ //j indexes rows
                for(unsigned int k=0;k<channels[i]->at(j)->size();k++){ //k indexes cols
                    img.at<double>(j, k, 0) = channels[i]->at(j)->at(k);
                }
            }

            /*
            cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);
            cv::imshow("Image",img);
            cv::waitKey(0);
            cv::destroyWindow("Image");
            */
            cv::normalize(img,img,200000,0);
            cv::Mat * I = new cv::Mat();
            img.convertTo(*I, CV_8UC1);

            //post-process greyscale

            equalizeHist(*I,*I);
            fastNlMeansDenoising(*I,*I);
            blur(*I,*I,cv::Size(2,2));

            matrixes->push_back(I);
            //imwrite(ss.str(), I);
        }

        return matrixes;
    }

private:

    std::vector<  std::vector<std::vector<double> * > * > channels;
};

#endif // SIDESCANIMAGER_H