//
// Created by xiaoyong on 2021/1/27.
//

#ifndef KUAFOO_VIDEO2MAT_H
#define KUAFOO_VIDEO2MAT_H

#include <opencv2/opencv.hpp>
#include "Logger.h"
#include "Utils.h"

using namespace std;
using namespace cv;

class SFMController {
private:
    Utils* util;
    void save_structure(string file_name, vector<Mat>& rotations, vector<Mat>& motions, Mat& structure, vector<Vec3b>& colors);
    void maskout_colors(vector<Vec3b>& p1, Mat& mask);
    void maskout_points(vector<Point2f>& p1, Mat& mask);
    void reconstruct(Mat& K, Mat& R, Mat& T, vector<Point2f>& p1, vector<Point2f>& p2, Mat& structure);
    void get_matched_colors(vector<Vec3b>& c1,vector<Vec3b>& c2,vector<DMatch> matches,vector<Vec3b>& out_c1,vector<Vec3b>& out_c2);
    void get_matched_points(vector<KeyPoint>& p1,vector<KeyPoint>& p2,vector<DMatch> matches,vector<Point2f>& out_p1,vector<Point2f>& out_p2);
    bool find_transform(Mat& K, vector<Point2f>& p1, vector<Point2f>& p2, Mat& R, Mat& T, Mat& mask);
    void match_features(Mat& query, Mat& train, vector<DMatch>& matches);
    void extract_features(vector<string>& image_names,vector<vector<KeyPoint>>& key_points_for_all,vector<Mat>& descriptor_for_all,vector<vector<Vec3b>>& colors_for_all);
public:
    struct Params{
        string  folder,ext = "png";
        int start = 1,stop = -1,skip = 0;
        Logger* logger;
    }params;
    void run();
};


#endif //KUAFOO_VIDEO2MAT_H
