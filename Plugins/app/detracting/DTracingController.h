//
// Created by xiaoyong on 2021/1/27.
//

#ifndef KUAFOO_VIDEO2MAT_H
#define KUAFOO_VIDEO2MAT_H

#include <opencv2/opencv.hpp>
#include "Logger.h"
#include "Utils.h"
#include "IniConfigure.hpp"

using namespace std;
using namespace cv;

class DTrackingController {
private:
    Utils* util;
    Mat Fd(Mat &front,Mat &current);
    Mat Gmm(Mat &front,Mat &current);

    //ViBE
    void ViBeRun();
    void ViBERunner(int num_sam = 20,
                    int min_match = 2,
                    int r = 20,
                    int rand_sam = 8);
    // 捕获一帧图像
    // Capture one Frame of Video
    void FrameCapture(Mat img);
    // 背景模型初始化
    // Init Background Model.
    void init();
    // 处理第一帧图像
    // Process First Frame of Video Query
    void ProcessFirstFrame();
    // 运行 ViBe+ 算法，提取前景区域并更新背景模型样本库
    // Run the ViBe+ Algorithm: Extract Foreground Areas & Update Background Model Sample Library.
    // void Run();
    // 提取分割模板
    // Extract the Segment Model
    void ExtractBG();
    // 根据已经得到的分割模板，计算更新模板；
    // Calculate Update Model from Segment Model
    void CalcuUpdateModel();
    // 更新背景模板
    // Update the Update Model
    void Update();
    // 更新当前像素点样本集方差
    // Update Variance of Sample Set of Current Pixel whose location is (i, j)
    void UpdatePixSampleSumSquare(int i, int j, int k, int val);
    // 更新当前像素点样本集平均值
    // Update Average Value of Sample Set of Current Pixel whose location is (i, j)
    void UpdatePixSampleAve(int i, int j, int k, int val);
    // 获取前景模型二值图像
    // get Foreground Model Binary Image.
    Mat getSegModel();
    // 获取更新模型二值图像
    // get Update Model Binary Image.
    Mat getUpdateModel();
    // 删除样本库及其相关信息
    // Delete Sample Library and Relative Information.
    void deleteSamples();
    // x的邻居点
    // x's neighborhood points
    int c_xoff[9] = {-1,  0,  1, -1, 1, -1, 0, 1, 0};
    // y的邻居点
    // y's neighborhood points
    int c_yoff[9] = {-1,  0,  1, -1, 1, -1, 0, 1, 0};
    Mat Dbm(Mat &front,Mat &current);
public:
    DTrackingController();
    ~DTrackingController();
    struct Params{
        Logger* logger;
        IniConfiguration* conf;
    }params;
    struct ViBEParams{
        // 当前帧图像
        // Current Raw Frame
        Mat Frame;
        // 当前帧灰度图
        // Current Gray Frame
        Mat Gray;
        // 当前帧通道数
        // Channels' Number of Current Frame
        int Channels;
        // 算法处理总帧数
        // Frame Count Process By ViBe+ Algorithm
        int count;
        //====================================================
        //        样本库相关  |  Sample Library Information Related
        //====================================================
        // 样本库
        // Sample Library, size = img.rows * img.cols *  DEFAULT_NUM_SAMPLES
        unsigned char ***samples;
        // RGB通道图像样本库
        // Sample Library, size = img.rows * img.cols *  DEFAULT_NUM_SAMPLES * 3 (The 3 values Save the pixel's [B, G, R])
        unsigned char ****samples_Frame;
        // 样本集灰度方差
        // the Gray Value Variance of Sample Set
        double **samples_sumsqr;
        // 样本集灰度均值
        // the Gray Value Average Value of Sample Set
        double **samples_ave;
        // 样本连续记为前景次数
        // the Number of Times Counted as Foreground Point Continuously
        int **samples_ForeNum;
        // 样本是否为背景内边缘?  0:  NO;  1:  YES
        // Is the Sample Background's Inner Edge?
        // 0 -- No;  1 -- Yes
        bool **samples_BGInner;
        // 样本在背景内边缘状况下，八邻域状态位
        // the Samples' State Bits of 8 Neighbor Area (If Current Pixel Belongs to Background Inner Edge)
        int **samples_InnerState;
        // 样本闪烁等级
        // Blink Level of the Samples
        int **samples_BlinkLevel;
        // 样本邻域梯度最大值
        // the Max Value of Sample
        int **samples_MaxInnerGrad;
        // 前景模型二值图像，表示分割出的前景与背景信息；
        // Foreground Model Binary Image
        // It shows Foreground and Background Information After Segmatation
        Mat SegModel;
        // 更新模型二值图像，表示参与数据更新的像素位置；
        // Update Model's Binary Image
        // It shows Pixels' Location which will join in Data Update
        Mat UpdateModel;
        // 每个像素点的样本个数
        // Number of pixel's samples
        int num_samples;
        // #min指数
        // Match Number of make pixel as Background
        int num_min_matches;
        // Sqthere半径
        // Radius of pixel value
        int radius;
        // 子采样概率
        // the probability of random sample
        int random_sample;
    } vibe;
    void run();
};

#endif //KUAFOO_VIDEO2MAT_H
