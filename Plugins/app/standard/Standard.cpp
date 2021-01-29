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
            Thenengrad(list[0]);
            break;
        case 2:
            Eav(list[0]);
            break;
        case 3:
            Energy_gradient(list[0]);
            break;
        case 4:
            Brenner(list[0]);
            break;
        case 5:
            PSNR(list[0],list[1]);
            break;
        case 6:
            SSIM(list[0],list[1]);
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

void Standard::PSNR(Mat &I1, Mat &I2) {
    Mat s1;
    absdiff(I1, I2, s1);
    s1.convertTo(s1, CV_32F);//转换为32位的float类型，8位不能计算平方
    s1 = s1.mul(s1);
    Scalar s = sum(s1);  //计算每个通道的和
    double sse = s.val[0] + s.val[1] + s.val[2];
    if( sse <= 1e-10) // for small values return zero
        this->params.logger->Result(to_string(0));
    else
    {
        double mse = sse / (double)(I1.channels() * I1.total()); //  sse/(w*h*3)
        double psnr = 10.0 * log10((255*255)/mse);
        this->params.logger->Result(to_string(psnr));
    }
}

void Standard::SSIM(Mat &i1, Mat & i2) {
    const double C1 = 6.5025, C2 = 58.5225;
    int d = CV_32F;
    Mat I1, I2;
    i1.convertTo(I1, d);
    i2.convertTo(I2, d);
    Mat I1_2 = I1.mul(I1);
    Mat I2_2 = I2.mul(I2);
    Mat I1_I2 = I1.mul(I2);
    Mat mu1, mu2;
    GaussianBlur(I1, mu1, Size(11,11), 1.5);
    GaussianBlur(I2, mu2, Size(11,11), 1.5);
    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);
    Mat sigma1_2, sigam2_2, sigam12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;

    GaussianBlur(I2_2, sigam2_2, Size(11, 11), 1.5);
    sigam2_2 -= mu2_2;

    GaussianBlur(I1_I2, sigam12, Size(11, 11), 1.5);
    sigam12 -= mu1_mu2;
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigam12 + C2;
    t3 = t1.mul(t2);

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigam2_2 + C2;
    t1 = t1.mul(t2);

    Mat ssim_map;
    divide(t3, t1, ssim_map);
    Scalar mssim = mean(ssim_map);

    double ssim = (mssim.val[0] + mssim.val[1] + mssim.val[2]) /3;
    this->params.logger->Result(to_string(ssim));
}