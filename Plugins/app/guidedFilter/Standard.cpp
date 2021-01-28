//
// Created by xiaoyong on 2021/1/27.
//

#include "Standard.h"

void Standard::run() {
    if (!(util->exist(this->params.file))) {
        this->params.logger->Info("file not exist!");
        return;
    }

    this->params.logger->Info("start...");

    if (util->exist(this->params.file)) {
        this->list.push_back(imread(this->params.file, IMREAD_UNCHANGED));
    } else {

    }

    runAction(this->params.action);

    this->params.logger->Info("stop...");
}

void Standard::runAction(int i) {
    switch (i) {
        case 1:
            for (int j = 0; j < list.size(); ++j)
                Thenengrad(list[j]);
            break;
        case 2:
            for (int j = 0; j < list.size(); ++j)
                Eav(list[j]);
            break;
        case 3:
            for (int j = 0; j < list.size(); ++j)
                Energy_gradient(list[j]);
            break;
        case 4:
            for (int j = 0; j < list.size(); ++j)
                Brenner(list[j]);
            break;
        default:
            this->params.logger->Info("method unrecognized.");
            break;
    }
}

void Standard::Thenengrad(Mat &img) {
    cv::Mat gray_img, sobel_x, sobel_y, G;
    if (img.channels() == 3) {
        cv::cvtColor(img, gray_img, COLOR_BGR2GRAY);
    }

    //分别计算x/y方向梯度
    cv::Sobel(gray_img, sobel_x, CV_32FC1, 1, 0);
    cv::Sobel(gray_img, sobel_y, CV_32FC1, 0, 1);
    cv::multiply(sobel_x, sobel_x, sobel_x);
    cv::multiply(sobel_y, sobel_y, sobel_y);
    cv::Mat sqrt_mat = sobel_x + sobel_y;
    cv::sqrt(sqrt_mat, G);

    auto res = to_string(cv::mean(G)[0]);

    this->params.logger->Result(res);
}

/**
* EAV点锐度算法函数
*
* Inputs:
* @param image:
* Return: double
*/
void Standard::Eav(Mat &image) {

    cv::Mat gray_img, smd_image_x, smd_image_y, G;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray_img, COLOR_BGR2GRAY);
    }

    double result = .0f;
    for (int i = 1; i < gray_img.rows - 1; ++i) {
        uchar *prev = gray_img.ptr<uchar>(i - 1);
        uchar *cur = gray_img.ptr<uchar>(i);
        uchar *next = gray_img.ptr<uchar>(i + 1);
        for (int j = 0; j < gray_img.cols; ++j) {
            result += (abs(prev[j - 1] - cur[i]) * 0.7 + abs(prev[j] - cur[j]) + abs(prev[j + 1] - cur[j]) * 0.7 +
                       abs(next[j - 1] - cur[j]) * 0.7 + abs(next[j] - cur[j]) + abs(next[j + 1] - cur[j]) * 0.7 +
                       abs(cur[j - 1] - cur[j]) + abs(cur[j + 1] - cur[j]));
        }
    }
    auto res = to_string(result / gray_img.total());

    this->params.logger->Result(res);
}


/**
* 能量梯度函数
*
* Inputs:
* @param image:
* Return: double
*/
void Standard::Energy_gradient(Mat &image) {

    cv::Mat gray_img, smd_image_x, smd_image_y, G;
    if (image.channels() == 3){
        cv::cvtColor(image, gray_img, COLOR_BGR2GRAY);
    }

    cv::Mat kernel_x(3, 3, CV_32F, cv::Scalar(0));
    kernel_x.at<float>(1, 2) = -1.0;
    kernel_x.at<float>(1, 1) = 1.0;
    cv::Mat kernel_y(3, 3, CV_32F, cv::Scalar(0));
    kernel_y.at<float>(1, 1) = 1.0;
    kernel_y.at<float>(2, 1) = -1.0;
    cv::filter2D(gray_img, smd_image_x, gray_img.depth(), kernel_x);
    cv::filter2D(gray_img, smd_image_y, gray_img.depth(), kernel_y);

    cv::multiply(smd_image_x, smd_image_x, smd_image_x);
    cv::multiply(smd_image_y, smd_image_y, smd_image_y);
    G = smd_image_x + smd_image_y;

    this->params.logger->Result(to_string(cv::mean(G)[0]));
}

/**
* Brenner梯度方法
*
* Inputs:
* @param image:
* Return: double
*/
void Standard::Brenner(Mat &image) {
    cv::Mat gray_img;
    if (image.channels() == 3){
        cv::cvtColor(image, gray_img, COLOR_BGR2GRAY);
    }

    double result = .0f;
    for (int i = 0; i < gray_img.rows; ++i){
        uchar *data = gray_img.ptr<uchar>(i);
        for (int j = 0; j < gray_img.cols - 2; ++j){
            result += pow(data[j + 2] - data[j], 2);
        }
    }

    this->params.logger->Result(to_string(result/gray_img.total()));
}