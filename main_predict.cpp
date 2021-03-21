#include"Palm_ROI.h"
#include"BMR+LBP+score(best_match_region).h"

int main()
{
	char filename[100];
	char ROI_savename[100];
	char extraction_savename[100];
	char Hand_Region[100];
	char rand_Postive[100];
	int quantity_num = 100;
	int finger_count = 1;
	int finger_image_num = 3;
	string hand_check = "l";
	string sdf;
	int spectrum = 940;

	//#pragma omp parallel for 
	srand(11);
	float response = 0;
	int counter = 0;
	/********************************************副樣本**************************************************************/
	for (int Z = 0; Z < quantity_num; Z++)
	{
		for (int a = 0; a < 2; a++)
		{
			int Y;
			Mat predict_image(1, 2, CV_32F);
			for (Y = 0; Y < finger_image_num; Y++)
			{
				int rand_Z = (int)((rand() / (RAND_MAX + 1.0))*quantity_num);
				int rand_Y = (int)((rand() / (RAND_MAX + 1.0))*finger_image_num);
				while (rand_Z == Z)
				{
					rand_Z = (int)((rand() / (RAND_MAX + 1.0))*quantity_num);
					rand_Y = (int)((rand() / (RAND_MAX + 1.0))*finger_image_num);
				}
				if (a == 0)
				{
					hand_check = "r";
					if (Z < 9)
					{
						sprintf_s(filename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\00%d_r_%d_0%d.jpg", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\00%d_r_%d_0%d_ROI.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(extraction_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_r_%d_0%d_extraction.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(Hand_Region, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Hand_Region\\00%d_r_%d_0%d_Hand_Region.png", spectrum, Z + 1, spectrum, Y + 1);
					}
					else if (Z >= 9 && Z < 99)
					{
						sprintf_s(filename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\0%d_r_%d_0%d.jpg", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\0%d_r_%d_0%d_ROI.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(extraction_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_r_%d_0%d_extraction.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(Hand_Region, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Hand_Region\\0%d_r_%d_0%d_Hand_Region.png", spectrum, Z + 1, spectrum, Y + 1);

					}
					else if (Z >= 99)
					{
						sprintf_s(filename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\%d_r_%d_0%d.jpg", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\%d_r_%d_0%d_ROI.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(extraction_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\%d_r_%d_0%d_extraction.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(Hand_Region, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Hand_Region\\%d_r_%d_0%d_Hand_Region.png", spectrum, Z + 1, spectrum, Y + 1);

					}
					if (rand_Z < 9)	sprintf_s(rand_Postive, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_r_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1 + finger_image_num);
					else if (rand_Z >= 9 && rand_Z < 99)	sprintf_s(rand_Postive, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_r_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1 + finger_image_num);
					else if (rand_Z >= 99) sprintf_s(rand_Postive, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\%d_r_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1 + finger_image_num);
				}
				if (a == 1)
				{
					hand_check = "l";
					if (Z < 9)
					{
						sprintf_s(filename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\00%d_l_%d_0%d.jpg", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\00%d_l_%d_0%d_ROI.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(extraction_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_l_%d_0%d_extraction.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(Hand_Region, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Hand_Region\\00%d_l_%d_0%d_Hand_Region.png", spectrum, Z + 1, spectrum, Y + 1);
					}
					else if (Z >= 9 && Z < 99)
					{
						sprintf_s(filename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\0%d_l_%d_0%d.jpg", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\0%d_l_%d_0%d_ROI.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(extraction_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_l_%d_0%d_extraction.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(Hand_Region, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Hand_Region\\0%d_l_%d_0%d_Hand_Region.png", spectrum, Z + 1, spectrum, Y + 1);
					}
					else if (Z >= 99)
					{
						sprintf_s(filename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\%d_l_%d_0%d.jpg", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\%d_l_%d_0%d_ROI.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(extraction_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\%d_l_%d_0%d_extraction.png", spectrum, Z + 1, spectrum, Y + 1);
						sprintf_s(Hand_Region, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Hand_Region\\%d_l_%d_0%d_Hand_Region.png", spectrum, Z + 1, spectrum, Y + 1);
					}
					if (rand_Z < 9)	sprintf_s(rand_Postive, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1 + finger_image_num);
					else if (rand_Z >= 9 && rand_Z < 99)	sprintf_s(rand_Postive, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1 + finger_image_num);
					else if (rand_Z >= 99) sprintf_s(rand_Postive, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0 % d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1 + finger_image_num);
				}

				/*************************************************************ROI*************************************************************/
				Mat g_utimage_ROI = imread(ROI_savename, 0);//檢查是否有已經做過的ROI圖像，沒有這張圖才繼續做
				if (g_utimage_ROI.empty() == 1)
					g_utimage_ROI = preprocess_ROI(filename, ROI_savename, Hand_Region, hand_check);
				/**********************************************************extraction*******************************************************/
				Mat g_utextraction_registered = imread(extraction_savename, 0);//檢查是否有已經做過的ROI圖像，沒有這張圖才繼續做
				if (g_utextraction_registered.empty() == 1)
					g_utextraction_registered = preprocess_principal_curvature(g_utimage_ROI, extraction_savename);

				Mat g_utextraction_templated = imread(rand_Postive, 0);
				if (g_utextraction_templated.empty() == 1)
				{
					cout << "No read image" << endl;
					waitKey(0);
				}
				double svm_score1, svm_score2;
				Post_processing(g_utextraction_registered, g_utextraction_templated, svm_score1, svm_score2);
				predict_image.at<float>(0) = svm_score1;
				predict_image.at<float>(1) = svm_score2;
				string svm_savename = "SVM/svm_";
				string reg;
				stringstream ZZ;
				ZZ << Z + 1;
				ZZ >> reg;
				svm_savename += hand_check + "_" + reg + ".sav";
				Ptr<SVM> svm = Algorithm::load<SVM>(svm_savename);
		//		char svmchar[100] = "C:\\專題\\Palm_curvature_W-Kang\\Palm_curvature_W-Kang\\SVM\\svm_r_1.sav";
				
		//		svm->load(svm_savename);
				bool dsaddd = svm->empty();
				Mat out;//月光寶盒
				Mat sampleMat = (Mat_<float>(1, 2) << svm_score1, svm_score2);
				response += svm->predict(sampleMat);
				counter++;
			}
		}
	}
	float fdsssssss = response / counter;

}