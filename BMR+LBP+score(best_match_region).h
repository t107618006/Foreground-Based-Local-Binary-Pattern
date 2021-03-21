#pragma once
#include"Palm_ROI.h"
//#include<opencv2\ml\ml.hpp>

using namespace cv::ml;

void Post_processing(Mat g_utimage_registered, Mat g_utimage_template, double &compare_score1, double &compare_score2);//����BMR���R�AMF_LBP�AChi_square distance���R�A�æ^�Ǩ�Ӥ���
Mat preprocess_ROI(char filename[1000], char ROI_savename[1000], char Hand_Region[1000], string hand_check);//ROI�{�ǡA�^��ROI�Ϲ��A�ñNROI�v���x�s
Mat preprocess_principal_curvature(Mat g_utimage_ROI, string extraction_savename);//principal_curvature,�^��principal_curvature�Ϲ��A�ñNprincipal_curvature�v���x�s
double Chi_square_distance(Mat a_thist_registered, Mat a_thist_templated);