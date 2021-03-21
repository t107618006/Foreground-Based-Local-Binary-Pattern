#include<iostream>
#include <opencv2/opencv.hpp>
#include"BMR+LBP+score(best_match_region).h"

using namespace cv;
using namespace std;

int main()
{
	String pattern = "C:\\Image\\Plam_CASIA\\Image\\850nm\\norm\\ROI\\";
	vector<String> fn;
	glob(pattern, fn, false);
	String output_path = "C:\\Image\\Plam_CASIA\\Image\\850nm\\norm\\feature\\principal_curvature\\";

	size_t count = fn.size();
	for (size_t i = 0; i < count; i++)
	{
		size_t head = fn[i].find("ROI_", 0);
		size_t foot = fn[i].find(".png", 0);
		string name = fn[i].substr(head+4,foot-head-4);// +(foot - head - 6));
		Mat g_utimage_ROI = imread(fn[i], 0);	
		string extraction_savename = { output_path + "norm_PC_" + name+".png" };
		Mat che = imread(extraction_savename, 0);
		if (che.empty() == 0)
		{
			//continue;
			waitKey(10);
		}
		cout << extraction_savename << endl;
		resize(g_utimage_ROI, g_utimage_ROI, Size(140, 140));
		Mat g_utextraction_registered = preprocess_principal_curvature(g_utimage_ROI, extraction_savename);
	}
}