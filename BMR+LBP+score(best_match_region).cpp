#include"Palm_ROI.h"

#include<opencv2\ml\ml.hpp>

using namespace cv::ml;

double maximal_MPR(Mat a_timage_registered, Mat a_timage_template, Mat &BMR_registered, Mat &BMR_template, int start, int step);
Mat main_local_binary_pattern(Mat a_timage_in, int radius, int neighborhood);//LBP
Mat image_or_operator(Mat a_timage_in1, Mat a_timage_in2);//將兩張圖片做OR運算並回傳結果
Mat image_multiply(Mat a_timage_in1, Mat a_timage_in2);
Mat image_sub_region_histogram(Mat a_timage_in, Size sub_size, Mat &hist);//將圖片切成sub_size的大小，並個別計算值方圖後，水平拼接起來，回傳拼接後的圖片
Mat drawHistImg(const Mat &src);
double Chi_square_distance(Mat a_thist_registered, Mat a_thist_templated);

Mat preprocess_principal_curvature(Mat g_utimage_ROI,string extraction_savename)
{
	double min, max;
	double ori_min = 0, ori_max = 0;
	GaussianBlur(g_utimage_ROI, g_utimage_ROI, Size(5, 5), 0, 0);
	minMaxIdx(g_utimage_ROI, &ori_min, &ori_max);
	Mat g_utprincipal_curvature = curvature_k1(g_utimage_ROI);
	Mat g_utpric_8U = g_utprincipal_curvature.clone();
	normalize(g_utprincipal_curvature, g_utpric_8U, 0, 255, NORM_MINMAX);
	g_utpric_8U.convertTo(g_utpric_8U, CV_8U);
	minMaxIdx(g_utpric_8U, &min, &max);
//	imwrite("eigen_value.bmp", g_utpric_8U);
	Mat g_utprincipal_OTSU;
	threshold(g_utpric_8U, g_utprincipal_OTSU, 10, 255, CV_THRESH_OTSU);
//	imwrite("principal_OTSU.tif", g_utprincipal_OTSU);
	Mat g_utcurvature_erode;
	Mat erodeStruct = getStructuringElement(MORPH_RECT, Size(2, 2));
	erode(g_utprincipal_OTSU, g_utcurvature_erode, erodeStruct);
	Mat input_image_th;
	cv::threshold(g_utimage_ROI, input_image_th, 0.85, 255, CV_THRESH_OTSU);
	Mat output_image(g_utimage_ROI.size(), CV_8U, Scalar(0));
	for (int i = 0; i < g_utcurvature_erode.rows; i++)
	{
		for (int j = 0; j < g_utcurvature_erode.cols; j++)
		{
			if (input_image_th.at<uchar>(i, j) == 255)
			{
				output_image.at<uchar>(i, j) = g_utcurvature_erode.at<uchar>(i, j);
			}
		}
	}
	imwrite(extraction_savename, output_image);
	return output_image;
}


Mat preprocess_ROI(char filename[1000], char ROI_savename[1000], char Hand_Region[1000], string hand_check)
{
	Mat g_utimage_in = imread(filename, 0);
	hand_check = "l";
	resize(g_utimage_in, g_utimage_in, Size(768, 576));
	cout << filename << endl;
	Mat g_utimage_OTSU;
	double thresh = 0.85;
	Mat g_utimage_gaussian;
	GaussianBlur(g_utimage_in, g_utimage_gaussian, Size(5, 5), 0, 0);
	threshold(g_utimage_gaussian, g_utimage_OTSU, thresh, 255, CV_THRESH_OTSU);
	for (int i = 0; i < g_utimage_OTSU.rows; i++)
	{
		for (int j = 0; j < g_utimage_OTSU.cols; j++)
		{
			if (g_utimage_OTSU.at<uchar>(i, j) == 255)
			{
				g_utimage_OTSU.at<uchar>(i, j) = 0;
			}
			else if (g_utimage_OTSU.at<uchar>(i, j) == 0)
			{
				g_utimage_OTSU.at<uchar>(i, j) = 255;
			}
		}
	}
	Mat g_utimage_label;
	labeling(g_utimage_OTSU, g_utimage_label);
	g_utimage_label = labeling_replace(g_utimage_label);
	medianBlur(g_utimage_label, g_utimage_label, 9);
	//	imwrite("007_l_940_03_binary.png", g_utimage_label);
	Mat g_utstrong_img;
 	Mat g_utimage_ROI = capture_plam_image(g_utimage_label, g_utimage_in, hand_check, g_utstrong_img);
	hconcat(g_utimage_label, g_utimage_in, g_utimage_label);
	cvtColor(g_utimage_label, g_utimage_label, CV_GRAY2BGR);
	vconcat(g_utstrong_img, g_utimage_label, g_utimage_label);
	imwrite(ROI_savename, g_utimage_ROI);
	imwrite(Hand_Region, g_utimage_label);
	return g_utimage_ROI;
}


void Post_processing(Mat g_utimage_registered, Mat g_utimage_template,double &compare_score1, double &compare_score2)//執行BMR分析，MF_LBP，Chi_square distance分析，並回傳兩個分數
{
//	Mat g_utimage_registered;// = imread("C:\\Image\\Plam_CASIA\\Image\\940nm\\Extraction\\007_l_940_04_extraction.png", 0);
//	Mat g_utimage_template;// = imread("C:\\Image\\Plam_CASIA\\Image\\940nm\\Extraction\\001_l_940_05_extraction.png", 0);
	Mat g_utBMR_registered;
	Mat g_utBMR_template;
	compare_score1 = maximal_MPR(g_utimage_registered, g_utimage_template, g_utBMR_registered, g_utBMR_template,16,2);//尋找最大相似程度區塊
//	imwrite("BMR_registered.png", g_utBMR_registered);
//	imwrite("BMR_template.png", g_utBMR_template);
	Mat g_utout_OR = image_or_operator(g_utBMR_registered, g_utBMR_template);//or operator
//	imwrite("OR_operator.png", g_utout_OR);
	Mat g_utBMR_registered_LBP;
	Mat g_utBMR_template_LBP;
	g_utBMR_registered_LBP =main_local_binary_pattern(g_utBMR_registered, 7, 8);//LBP
	g_utBMR_template_LBP = main_local_binary_pattern(g_utBMR_template, 7, 8);
	Mat g_utMF_LBP_registered =image_multiply(g_utBMR_registered_LBP,g_utout_OR);//將前景(MF)和BMR_LBP相乘
	Mat g_utMF_LBP_template = image_multiply(g_utBMR_template_LBP,g_utout_OR);
	imwrite("MF_LBP_template.png", g_utMF_LBP_template);
	imwrite("MF_LBP_registered.png", g_utMF_LBP_registered);
	Mat hist_regi;
	Mat hist_temp;
	Mat g_uthist_registered = image_sub_region_histogram(g_utMF_LBP_registered, Size (5, 5), hist_regi);
	Mat g_uthist_template= image_sub_region_histogram(g_utMF_LBP_template, Size(5, 5), hist_temp);
	imwrite("hist_registered.png", hist_regi);
	imwrite("hist_templat.png", hist_temp);
	compare_score2 = Chi_square_distance(g_uthist_registered, g_uthist_template);
/* 
	Mat a_regi;
	Mat a_temp;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	int histSize = 256;
	calcHist(&g_utMF_LBP_registered, 1, 0, Mat(), a_regi, 1, &histSize, &histRange);
	float a_sum = sum(a_regi)[0];
	for (int i = 0; i < a_regi.rows; i++)
	{
		a_regi.at<float>(i) = a_regi.at<float>(i) / a_sum;
	}
	calcHist(&g_utMF_LBP_template, 1, 0, Mat(), a_temp, 1, &histSize, &histRange);
	a_sum = sum(a_temp)[0];
	for (int i = 0; i < a_temp.rows; i++)
	{
		a_temp.at<float>(i) = a_temp.at<float>(i) / a_sum;
	}
	double dsa=Chi_square_distance(a_regi, a_temp);*/
//	compare_score2 = dsa;
}
struct pointer_x_y
{
	int i = 0;
	int j = 0;
	double max = 0;
};

Mat drawHistImg(const Mat &src) {
	int histSize = 256;
	Mat showHistImg(256, 256, CV_8UC1, Scalar(255));
	float histMaxValue = 0;
	for (int i = 0; i<histSize; i++) {
		float tempValue = src.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	float scale = (0.9 * 256) / histMaxValue;
	for (int i = 0; i<histSize; i++) {
		int intensity = static_cast<int>(src.at<float>(i)*scale);
		line(showHistImg, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
	}
	return showHistImg;
}
	


Mat image_or_operator(Mat a_timage_in1,Mat a_timage_in2)
{
	Mat a_timage_out(a_timage_in1.size(), a_timage_in1.type(),Scalar(0));
	for (int i = 0; i<a_timage_in1.rows; i++)
	for (int j = 0; j < a_timage_in1.cols; j++)
	{
		if (a_timage_in1.at<uchar>(i, j) || a_timage_in2.at<uchar>(i, j))
		{
			a_timage_out.at<uchar>(i, j) = 255;
		}
	}
	return a_timage_out;
}

double maximal_MPR(Mat a_timage_registered, Mat a_timage_template,Mat &BMR_registered,Mat &BMR_template,int start,int step)
{
	int start_half = start / 2;
	double temple_arry[17][17];
	double temple_arry_2[17][17];
	pointer_x_y best_parameter;
	for (int a = -start; a < start; a += step)
	{
		for (int b = -start; b < start; b += step)
		{
			temple_arry[a / 2 + start_half][b / 2 + start_half] = 0;
			double reg1 = 0, reg2 = 0, reg3 = 0;
			for (int i = 0; i < a_timage_registered.rows - abs(a); i++)
			{
				for (int j = 0; j < a_timage_registered.cols - abs(b); j++)
				{
					int reg_register_i = i, reg_register_j = j;
					int reg_template_i = i, reg_template_j = j;
					if (a < 0)	reg_template_i += abs(a);
					if (a >= 0)	reg_register_i += abs(a);
					if (b < 0)	reg_template_j += abs(b);
					if (b >= 0)	reg_register_j += abs(b);
					reg1 += (double)a_timage_registered.at<uchar>(reg_register_i, reg_register_j)*a_timage_template.at<uchar>(reg_template_i, reg_template_j);
					reg2 += (double)a_timage_registered.at<uchar>(reg_register_i, reg_register_j);
					reg3 += (double)a_timage_template.at<uchar>(reg_template_i, reg_template_j);
				}
			}
			reg1 *= 2;
			reg2 += reg3;
			temple_arry[a / 2 + start_half][b / 2 + start_half] = reg1 / reg2;
			if (temple_arry[a / 2 + start_half][b / 2 + start_half] > best_parameter.max)
			{
				best_parameter.max = temple_arry[a / 2 + start_half][b / 2 + start_half];
				best_parameter.i = a;
				best_parameter.j = b;
			}			
		}
	}
	BMR_registered.create(a_timage_registered.rows - abs(best_parameter.i), a_timage_registered.cols - abs(best_parameter.j), a_timage_registered.type());
	BMR_template.create(a_timage_registered.rows - abs(best_parameter.i), a_timage_registered.cols - abs(best_parameter.j), a_timage_registered.type());
	for (int i = 0; i < BMR_registered.rows; i++)
	{
		for (int j = 0; j < BMR_template.cols; j++)
		{
			int reg_register_i = i, reg_register_j = j;
			int reg_template_i = i, reg_template_j = j;
			if (best_parameter.i < 0)	reg_template_i += abs(best_parameter.i);
			if (best_parameter.i >= 0)	reg_register_i += abs(best_parameter.i);
			if (best_parameter.j < 0)	reg_template_j += abs(best_parameter.j);
			if (best_parameter.j >= 0)	reg_register_j += abs(best_parameter.j);
			BMR_registered.at<uchar>(i, j) = a_timage_registered.at < uchar>(reg_register_i, reg_register_j);
			BMR_template.at<uchar>(i, j) = a_timage_template.at<uchar>(reg_template_i, reg_template_j);
		}
	}
	return best_parameter.max;
}

Mat main_local_binary_pattern(Mat a_timage_in, int radius, int neighborhood)
{
	Mat a_tin_padding;
	copyMakeBorder(a_timage_in, a_tin_padding, radius, radius, radius, radius, BORDER_CONSTANT);
	Mat a_timage_out(a_timage_in.size(), a_timage_in.type(),Scalar(0));
	Mat check_img(a_timage_in.size(), a_timage_in.type(), Scalar(0));
	Mat check_img_2(a_timage_in.size(), a_timage_in.type(), Scalar(0));
	for (int i = radius; i < a_tin_padding.rows- radius; i++)
	{
		for (int j = radius; j < a_tin_padding.cols- radius; j++)
		{
			double reg = 0;
			for (int sample = 0; sample < neighborhood; sample++)
			{
				double theta = 360 / neighborhood*sample;
				double new_i = i+sin(theta*PI / 180)+ radius*cos(theta*PI/180);
				double new_j = j+cos(theta*PI / 180) - radius*sin(theta*PI / 180);
			//	check_img.at<uchar>(i + new_i, j + new_j) = 255;// theta + 25;
			//	cout << "(" << new_j << "," << new_i << ")" << endl;
				if (a_tin_padding.at<uchar>(new_i, new_j) >= a_tin_padding.at<uchar>(i, j))
				{
					reg += pow(2, sample);
				}
			}
			a_timage_out.at<uchar>(i - radius, j - radius) = reg;
		}
	}
	return a_timage_out;
}

Mat image_multiply(Mat a_timage_in1, Mat a_timage_in2)
{
	Mat a_timage_out(a_timage_in1.size(), a_timage_in1.type(), Scalar(0));
	for (int i = 0; i < a_timage_in1.rows; i++)
	{
		for (int j = 0; j < a_timage_in1.cols; j++)
		{
			a_timage_out.at<uchar>(i, j) = a_timage_in1.at<uchar>(i, j)*a_timage_in2.at<uchar>(i, j);
		}
	}
	return a_timage_out;
}

Mat image_sub_region_histogram(Mat a_timage_in, Size sub_size,Mat &hist)//將圖片切成sub_size的大小，並個別計算值方圖後，水平拼接起來，回傳拼接後的圖片
{
	Mat a_timage_hist;
	int sub_row = a_timage_in.rows / sub_size.height;
	int sub_col = a_timage_in.cols / sub_size.width;
	Mat a_timage_subreg(sub_row, sub_col, a_timage_in.type(), Scalar(0));
	Mat fds;
	Mat hhist;
	Mat all_hist;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	int histSize = 256;
	int i;
	int j;
	for (int sub_counter = 0; sub_counter < sub_size.height*sub_size.width; sub_counter++)
	{
		int a = 0, b = 0;
		for (i = sub_row*(sub_counter / sub_size.height); i < sub_row*(sub_counter / sub_size.height) + sub_row; i++)
		{
			
			for (j = sub_col*(sub_counter % sub_size.width); j < sub_col*(sub_counter % sub_size.width) + sub_col; j++)
			{
				a_timage_subreg.at<uchar>(a, b) = a_timage_in.at<uchar>(i, j);
				b++;
			}
			a++;
			b = 0;
		}

		calcHist(&a_timage_subreg, 1, 0, Mat(), fds, 1, &histSize, &histRange);  
		hist = drawHistImg(fds);	
		float a_sum = sum(fds)[0];
		for (int i = 0; i < fds.rows; i++)
		{
			fds.at<float>(i) = fds.at<float>(i) / a_sum;
		}
	
		if (sub_counter == 0)
		{
			a_timage_hist = fds.clone();
			hist.copyTo(all_hist);
		}
		else
		{
			hconcat(a_timage_hist, fds, a_timage_hist);
			if (sub_counter % 5 == 0)
			{
				if (sub_counter / 5 == 1)
					hhist = all_hist.clone();
				else
					vconcat(all_hist, hhist, hhist);
				hist.copyTo(all_hist);
			}
			else
				hconcat(all_hist, hist, all_hist);		
		}
		
			
			
	}
	hist = hhist.clone();
	return a_timage_hist;
}

double Chi_square_distance(Mat a_thist_registered, Mat a_thist_templated)
{
	//因chi方法需要，因此事先做直行的累加，再做其他直方圖之間的累加
	float total = 0;
	for (int j = 0; j < a_thist_registered.cols; j++)
	{
		for (int i = 0; i < a_thist_registered.rows;i++)
		{
			double reg1 = abs(a_thist_registered.at<float>(i, j) - a_thist_templated.at<float>(i, j));
			double reg2 = a_thist_registered.at<float>(i, j) + a_thist_templated.at<float>(i, j);
			if (reg2 == 0)
			{
				continue;
			}
			else
				total += reg1 / reg2;
			
		}
	}
	return total;
}