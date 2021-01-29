//
// Created by xiaoyong on 2021/1/27.
//

#include "SuperR.h"
#include <opencv2/superres.hpp>
#include <opencv2/superres/optical_flow.hpp>


void SuperR::run() {
    /*定义参数*/
    const string inputVideoName = "sr_input_by_read.avi";
    const int scale = 2;
    const int iterations = 5;
    const int temporalAreaRadius = 4;
    const string optFlow = "farneback";  //使用的算法：farneback, tvl1, brox, pyrlk
    const bool gpu = false;

    Ptr<SuperResolution> superRes;

    if ( gpu )
        superRes = createSuperResolution_BTVL1_CUDA();
    else
        superRes = createSuperResolution_BTVL1();

    //optFlow指定使用的超分辨算法
    Ptr<cv::superres::DenseOpticalFlowExt> of = createOptFlow(optFlow, gpu);

    if (of.empty())
        return;

    //设置使用的超分辨算法
    superRes->setOpticalFlow( of );
    superRes->setScale(scale);
    superRes->setIterations(iterations);
    superRes->setTemporalAreaRadius(temporalAreaRadius);

    Ptr<FrameSource> frameSource;
    //设置要使用的超分辨算法
    if( gpu )
    {
        //如果要使用gpu的话，要将视频进行gpu编码
        try
        {
            frameSource = createFrameSource_Video_CUDA(inputVideoName);
            Mat frame;
            frameSource->nextFrame(frame);
        }
        catch (const cv::Exception&)
        {
            frameSource.release();
        }
    }

    if (!frameSource)
    {
        frameSource = createFrameSource_Video(inputVideoName);
    }

    // skip first frame, it is usually corrupted
    Mat frame;
    frameSource->nextFrame(frame);

    superRes->setInput(frameSource);

    VideoWriter writer;

    for (int i = 0;; ++i)
    {
        //cout << flush; 无条件的将缓冲区中的输出信息送至显示器
        cout << '[' << setw(3) << i << "] : " << flush;
        Mat result, src_frame;

        frameSource->nextFrame( src_frame );
        resize( src_frame, src_frame, Size(src_frame.cols*2, src_frame.rows*2) );

        //nextFrame(result)的作用是处理下一帧，同时利用result返回当前真的额处理结果
        // MEASURE_TIME(superRes->nextFrame(result));

        if (result.empty())
            break;

        imshow("src_frame", src_frame);
        imshow("Super Resolution", result);
        waitKey( 0 );
    }

}