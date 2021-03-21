#pragma once
#include"Palm_ROI.h"
//#include<opencv2\ml\ml.hpp>

using namespace cv::ml;

void Post_processing(Mat g_utimage_registered, Mat g_utimage_template, double &compare_score1, double &compare_score2);//執行BMR分析，MF_LBP，Chi_square distance分析，並回傳兩個分數
Mat preprocess_ROI(char filename[1000], char ROI_savename[1000], char Hand_Region[1000], string hand_check);//ROI程序，回傳ROI圖像，並將ROI影像儲存
Mat preprocess_principal_curvature(Mat g_utimage_ROI, string extraction_savename);//principal_curvature,回傳principal_curvature圖像，並將principal_curvature影像儲存
double Chi_square_distance(Mat a_thist_registered, Mat a_thist_templated);