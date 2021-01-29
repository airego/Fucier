//
// Created by xiaoyong on 2021/1/27.
//

#include "Filters.h"

void Filters::run() {
    Mat I = imread("C:\\Users\\xiaoyong\\Desktop\\f\\images\\0.png",IMREAD_UNCHANGED);
    Mat P = imread("C:\\Users\\xiaoyong\\Desktop\\f\\images\\1.png",IMREAD_UNCHANGED);
    Mat res = guidedFilterAction(I,P,10,100);
    imwrite("guided.png",res);
}

Mat Filters::guidedFilterAction(cv::Mat guidedImg, cv::Mat inputImg, int radius, double eps) {
    CV_Assert(guidedImg.channels() == 3);
    CV_Assert(inputImg.channels() == 1 || inputImg.channels() == 3);
    CV_Assert(guidedImg.cols == inputImg.cols && guidedImg.rows == inputImg.rows);
    int type = CV_64F;
    int channel = inputImg.channels();
    cv::Mat I, P, output;
    guidedImg.convertTo(I, type);
    inputImg.convertTo(P, type);

    //判断输入图像是单通道还是三通道
    switch (channel)
    {
        case 1:
            output = guidedFilter(I, P, type, radius, eps);
            break;
        case 3:
        {
            cv::Mat bgr[3], bgrFilter[3];
            cv::split(P, bgr);
            for (int chan = 0; chan < channel; chan++)
            {
                bgrFilter[chan] = guidedFilter(I, bgr[chan], type, radius, eps);
            }
            cv::merge(bgrFilter, channel, output);
            break;
        }
        default:
            cout << "err! input image channel should be 1 or 3! " << endl;
            break;
    }

    output.convertTo(output, CV_8U);
    return output;
}

//引导图I为三通道图像
cv::Mat Filters::guidedFilter(cv::Mat I, cv::Mat P, int type, int radius, double eps)
{
    cv::Size winSize(2 * radius + 1, 2 * radius + 1);
    int channel = I.channels();
    int H = I.rows;
    int W = I.cols;

    cv::Mat bgr[3], meanI[3];
    //引导图各通道的均值
    split(I, bgr);
    for (int chan = 0; chan < channel; chan++)
    {
        boxFilter(bgr[chan], meanI[chan], type, winSize);
    }
    //输入图像均值
    cv::Mat meanP;
    boxFilter(P, meanP, type, winSize);
    //引导图各通道与输入图像相乘并求均值
    cv::Mat meanIP[3], IP;
    for (int chan = 0; chan < channel; chan++)
    {
        multiply(bgr[chan], P, IP);
        boxFilter(IP, meanIP[chan], type, winSize);
    }
    //引导图各通道与输入图协方差
    cv::Mat covIP[3], meanImulP;
    for (int chan = 0; chan < channel; chan++)
    {
        multiply(meanI[chan], meanP, meanImulP);
        covIP[chan] = meanIP[chan] - meanImulP;
    }

    //求引导图协方差矩阵
    cv::Mat varI[9], tmp, mean2Tmp, meanTmp2;
    int varIdx = 0;
    for (int i = 0; i < channel; i++)
    {
        for (int j = 0; j < channel; j++)
        {
            multiply(bgr[i], bgr[j], tmp);
            boxFilter(tmp, meanTmp2, type, winSize);//mean(I*I)
            multiply(meanI[i], meanI[j], mean2Tmp);//meanI*meanI
            varI[varIdx] = meanTmp2 - mean2Tmp;
            varIdx++;
        }
    }
    //求a，三通道
    cv::Mat a[3];
    for (int chan = 0; chan < channel; chan++)
    {
        a[chan] = cv::Mat::zeros(I.size(), type);
    }
    cv::Mat epsEye = cv::Mat::eye(3, 3, type);
    epsEye *= eps;
    //公式(19)
    for (int y = 0; y < H; y++)
    {
        double* vData[9];
        for (int v = 0; v < 9; v++)
        {
            vData[v] = (double*)varI[v].ptr<double>(y);
        }
        double* cData[3];
        for (int c = 0; c < 3; c++)
        {
            cData[c] = (double *)covIP[c].ptr<double>(y);
        }
        double* aData[3];
        for (int c = 0; c < 3; c++)
        {
            aData[c] = (double*)a[c].ptr<double>(y);
        }
        for (int x = 0; x < W; x++)
        {
            cv::Mat sigma = (cv::Mat_<double>(3, 3) <<
                                                    vData[0][x], vData[1][x], vData[2][x],
                    vData[3][x], vData[4][x], vData[5][x],
                    vData[6][x], vData[7][x], vData[8][x]
            );
            sigma += epsEye;
            cv::Mat cov_Ip_13 = (cv::Mat_<double>(3, 1) <<
                                                        cData[0][x], cData[1][x], cData[2][x]);
            cv::Mat tmpA = sigma.inv()*cov_Ip_13;
            double* tmpData = tmpA.ptr<double>(0);
            for (int c = 0; c < 3; c++)
            {
                aData[c][x] = tmpData[c];
            }
        }
    }

    //求b
    cv::Mat b = meanP - a[0].mul(meanI[0]) - a[1].mul(meanI[1]) - a[2].mul(meanI[2]);
    //b的均值
    cv::Mat meanB;
    boxFilter(b, meanB, type, winSize);
    //a的均值
    cv::Mat meanA[3];
    for (int c = 0; c < channel; c++)
    {
        boxFilter(a[c], meanA[c], type, winSize);
    }
    cv::Mat output = (meanA[0].mul(bgr[0]) + meanA[1].mul(bgr[1]) + meanA[2].mul(bgr[2])) + meanB;

    return output;
}