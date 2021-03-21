#include"Palm_ROI.h"
#include"BMR+LBP+score(best_match_region).h"
#define ROI 1
#define curvature 1

Mat DWT137(Mat a_timage_in);


int main()
{
	char filename[100];
	char ROI_savename[100];
	char extraction_savename[100];
	char Hand_Region[100];
	char rand_Negative[100];
	int quantity_num = 100;
	int finger_count = 1;
	int finger_image_num = 3;
	string hand_check = "l";
	string sdf;
	int spectrum = 940;
	
//#pragma omp parallel for 
	srand(11);
	
	/********************************************副樣本**************************************************************/
	for (int Z = 0; Z < quantity_num; Z++)
	{
		for (int a = 0; a < 2; a++)
		{
			Mat train_data(finger_image_num*2, 2, CV_32F, Scalar(0));
			Mat label_data(finger_image_num*2, 1, CV_32SC1, Scalar(0));
			Mat g_utpostive_1;
			Mat g_utpostive_2;
			Mat g_utpostive_3;
			int cou = finger_image_num;
			double max = 0;
			double min = 9999;
			int Y;
			for (Y = 0; Y < finger_image_num; Y++)
			{
				int rand_Z = (int)((rand() / (RAND_MAX + 1.0))*quantity_num);
				int rand_Y = (int)((rand() / (RAND_MAX + 1.0))*finger_image_num);
				while (rand_Z == Z)
				{
					rand_Z = (int)((rand() / (RAND_MAX + 1.0))*quantity_num);
			//		rand_Y = (int)((rand() / (RAND_MAX + 1.0))*finger_image_num);
				}
			//	rand_Z = Z;
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
					if (rand_Z < 9)	sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_r_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
					else if (rand_Z >= 9 && rand_Z < 99)	sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_r_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
					else if (rand_Z >= 99) sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\%d_r_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
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
					if (rand_Z < 9)	sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
					else if (rand_Z >= 9 && rand_Z < 99)	sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
					else if (rand_Z >= 99) sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
				}
				//sprintf_s(ROI_savename, "C:\\Image\\prototype\\940_0.png");
				//sprintf_s(filename, "C:\\Image\\prototype\\18.png");
				/*************************************************************ROI*************************************************************/
				Mat g_utimage_ROI = imread(ROI_savename, 0);//檢查是否有已經做過的ROI圖像，沒有這張圖才繼續做
				g_utimage_ROI = preprocess_ROI(filename, ROI_savename, Hand_Region, hand_check);
				if (g_utimage_ROI.empty() == 1)	
					g_utimage_ROI = preprocess_ROI(filename, ROI_savename, Hand_Region, hand_check);
				/**********************************************************extraction*******************************************************/
				Mat g_utextraction_registered = imread(extraction_savename, 0);//檢查是否有已經做過的ROI圖像，沒有這張圖才繼續做
				if (g_utextraction_registered.empty() == 1)	
					g_utextraction_registered = preprocess_principal_curvature(g_utimage_ROI, extraction_savename);
				
				Mat g_utextraction_templated = imread(rand_Negative, 0);
				if (g_utextraction_templated.empty() == 1)
				{
					cout << "No read image" << endl;
					cout << rand_Negative << endl;
				/*	if (a == 0)
					{
						if (rand_Z < 9)	sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\00%d_r_%d_0%d_ROI.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
						else if (rand_Z >= 9 && rand_Z < 99) sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\0%d_r_%d_0%d_ROI.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
						else if (rand_Z >= 99) sprintf_s(ROI_savename, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\ROI\\%d_r_%d_0%d_ROI.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
					}
					else
					{
						if (rand_Z < 9)	sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\00%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
						else if (rand_Z >= 9 && rand_Z < 99)	sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0%d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
						else if (rand_Z >= 99) sprintf_s(rand_Negative, "C:\\Image\\Plam_CASIA\\Image\\%dnm\\Extraction\\0 % d_l_%d_0%d_extraction.png", spectrum, rand_Z + 1, spectrum, rand_Y + 1);
					}*/
				}
				double svm_score1, svm_score2;
				Post_processing(g_utextraction_registered, g_utextraction_templated, svm_score1, svm_score2);
				train_data.at<float>(Y, 0) = svm_score1;
				train_data.at<float>(Y, 1) = svm_score2;
				label_data.at<int>(Y) = 0;//副樣本
				if (svm_score2 <= min)	min = svm_score2;

				/**********正樣本*********************/
				double sc_1, sc_2;
				if (Y == 0)	
				{
					g_utpostive_1 = g_utextraction_registered.clone();
				}
				if (Y == 1)	
				{
					g_utpostive_2 = g_utextraction_registered.clone();
					Post_processing(g_utpostive_1, g_utpostive_2, sc_1, sc_2);
					train_data.at<float>(cou, 0) = sc_1;
					train_data.at<float>(cou, 1) = sc_2;
					label_data.at<int>(cou) = 1;//副樣本
					cou++;
					if (sc_2 >= max)	
						max = sc_2;
				}
					
				if (Y == 2)
				{
					g_utpostive_3 = g_utextraction_registered.clone();
					Post_processing(g_utpostive_1, g_utpostive_3, sc_1, sc_2);
					train_data.at<float>(cou, 0) = sc_1;
					train_data.at<float>(cou, 1) = sc_2;
					label_data.at<int>(cou) = 1;//副樣本
					cou++;
					if (sc_2 >= max)	
						max = sc_2;
					Post_processing(g_utpostive_2, g_utpostive_3, sc_1, sc_2);
					train_data.at<float>(cou, 0) = sc_1;
					train_data.at<float>(cou, 1) = sc_2;
					label_data.at<int>(cou) = 1;//副樣本
					cou++;
					if (sc_2 >= max)	
						max = sc_2;
				}
			}
			//if (min < max)
//				waitKey();
			Ptr<SVM> svm = SVM::create();
			svm->setType(SVM::C_SVC);
			svm->setKernel(SVM::RBF);
      //		svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 1000, 1e-6));
			svm->trainAuto(train_data, ROW_SAMPLE, label_data);
			string svm_savename="SVM/svm_";
			string reg;
			stringstream ZZ;
			ZZ << Z+1;
			ZZ >> reg;
			svm_savename += hand_check + "_" + reg + ".sav";
			svm->save(svm_savename);
			cout << svm_savename << endl;
	/*		string sss = "C:\\Image\\Plam_CASIA\\Image\\940nm\\Extraction\\001_r_940_06_extraction.png";
			Mat test = imread(sss, 0);
			double sc1;
			double sc2;
			Post_processing(g_utpostive_1, test, sc1, sc2);
			Mat sampleMat = (Mat_<float>(1, 2) << sc1, sc2);
			float ans = svm->predict(sampleMat);
			sss = "C:\\Image\\Plam_CASIA\\Image\\940nm\\Extraction\\016_r_940_01_extraction.png";
			test = imread(sss, 0);
			Post_processing(g_utpostive_1, test, sc1, sc2);
			sampleMat = (Mat_<float>(1, 2) << sc1, sc2);
			ans = svm->predict(sampleMat);*/
		}
	}
 //	waitKey(0);
	return 0;
}

Mat DWT137(Mat a_timage_in)
{
	double La = -0.0024258914325;
	double Lb = 0;
	double Lc = 0.04269568921213;
	double Ld = -0.03796520091873;
	double Le = -0.14919232309219;
	double Lf = 0.341201629966131;
	double Lg = 0.824439203337638;

	Mat a_timage_out(a_timage_in.rows / 2 - 6, a_timage_in.cols / 2 - 6, CV_32F, Scalar(0));

	double in_min = 0, in_max = 0;
	minMaxIdx(a_timage_in, &in_min, &in_max);


	double regM = 0;
	double totalM = 0;
	for (int x = 3; x < a_timage_in.rows / 2 - 3; x++)
	{
		for (int y = 3; y < a_timage_in.cols / 2 - 3; y++)
		{

			double asdf = 0;


			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					/* Lc*Lc**/asdf += Lc*Lc*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 4 + 8 * j) +
						/*Ld*Lc	*/			/**/ Ld*Lc*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 4 + 8 * j) +
						/*Lc*Ld*/			/**/ Lc*Ld*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 3 + 6 * j) +
						/*Le*Lc*/		/**/ Le*Lc*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 4 + 8 * j) +
						/*Lc*Le*/	/**/	 Lc*Le*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 2 + 4 * j) +
						/*Lf*Lc*/	/**/	 Lf*Lc*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 4 + 8 * j) +
						/*Lc*Lf*/	/**/	 Lc*Lf*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 1 + 2 * j) +
						/*Ld*Ld*/	/**/	 Ld*Ld*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 3 + 6 * j) +
						/*Le*Ld*/	/**/	 Le*Ld*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 3 + 6 * j) +
						/*Ld*Le*/	/**/	 Ld*Le*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 2 + 4 * j) +
						/*Lf*Ld*/	/**/	 Lf*Ld*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 3 + 6 * j) +
						/*Ld*Lf	*/	/**/	 Ld*Lf*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 1 + 2 * j) +
						/*Le*Le*/	/**/	 Le*Le*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 2 + 4 * j) +
						/*Lf*Le*/	/**/	 Lf*Le*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 2 + 4 * j) +
						/*Le*Lf*/	/**/	 Le*Lf*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 1 + 2 * j) +
						/*Lf*Lf*/	/**/	 Lf*Lf*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 1 + 2 * j) +


						/*La*La*/	/**/	 La*La*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 6 + 12 * j) +
						/*Lb*La*/	/**/	 Lb*La*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 6 + 12 * j) +
						/*Lc*La*/	/**/	 Lc*La*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 6 + 12 * j) +
						/*Ld*La*/	/**/	 Ld*La*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 6 + 12 * j) +
						/*Le*La*/	/**/	 Le*La*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 6 + 12 * j) +
						/*Lf*La*/	/**/	 Lf*La*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 6 + 12 * j) +


						/*La*Lb*/	/**/	 La*Lb*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 5 + 10 * j) +
						/*Lb*Lb*/	/**/	 Lb*Lb*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 5 + 10 * j) +
						/*Lc*Lb*/	/**/	 Lc*Lb*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 5 + 10 * j) +
						/*Ld*Lb*/	/**/	 Ld*Lb*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 5 + 10 * j) +
						/*Le*Lb*/	/**/	 Le*Lb*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 5 + 10 * j) +
						/*Lf*Lb*/	/**/	 Lf*Lb*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 5 + 10 * j) +


						/*La*Lc*/	/**/	 La*Lc*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 4 + 8 * j) +
						/*Lb*Lc*/	/**/	 Lb*Lc*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 4 + 8 * j) +
						/*La*Ld*/	/**/	 La*Ld*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 3 + 6 * j) +
						/*Lb*Ld*/	/**/	 Lb*Ld*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 3 + 6 * j) +
						/*La*Le*/	/**/	 La*Le*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 2 + 4 * j) +
						/*Lb*Le*/	/**/	 Lb*Le*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 2 + 4 * j) +
						/*La*Lf*/	/**/	 La*Lf*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 1 + 2 * j) +
						/*Lb*Lf*/	/**/	 Lb*Lf*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 1 + 2 * j);
				}
			}
			for (int i = 0; i < 2; i++)
			{
				/*La*Lg*/		/*		 La*Lg**/asdf += La*Lg*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y) +
					/*Lb*Lg*/		/**/	 Lb*Lg*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y) +
					/*Lc*Lg*/		/**/	 Lc*Lg*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y) +
					/*Ld*Lg*/		/**/	 Ld*Lg*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y) +
					/*Le*Lg*/		/**/	 Le*Lg*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y) +
					/*Lf*Lg*/		/**/	 Lf*Lg*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y);
			}
			for (int j = 0; j < 2; j++)
			{
				/*Lg*La*/		/*		 Lg*La**/asdf += Lg*La*a_timage_in.at<uchar>(2 * x, 2 * y - 6 + 12 * j) +
					/*Lg*Lb*/		/**/	 Lg*Lb*a_timage_in.at<uchar>(2 * x, 2 * y - 5 + 10 * j) +
					/*Lg*Lc*/		/**/	 Lg*Lc*a_timage_in.at<uchar>(2 * x, 2 * y - 4 + 8 * j) +
					/*Lg*Ld*/		/**/	 Lg*Ld*a_timage_in.at<uchar>(2 * x, 2 * y - 3 + 6 * j) +
					/*Lg*Le*/		/**/	 Lg*Le*a_timage_in.at<uchar>(2 * x, 2 * y - 2 + 4 * j) +
					/*Lg*Lf*/		/**/	 Lg*Lf*a_timage_in.at<uchar>(2 * x, 2 * y - 1 + 2 * j);
			}
			asdf += (Lg*Lg*a_timage_in.at<uchar>(2 * x, 2 * y));
			a_timage_out.at<float>(x - 3, y - 3) = asdf;
		}
	}
	double out_min = 0, out_max = 0;
	minMaxIdx(a_timage_out, &out_min, &out_max);
	double Conversion = (in_max - in_min) / (out_max - out_min);

	Mat change_image(a_timage_out.rows, a_timage_out.cols, CV_8U, Scalar(0));
	for (int i = 0; i < a_timage_out.rows; i++)
	{
		for (int j = 0; j < a_timage_out.cols; j++)
		{
			change_image.at<uchar>(i, j) = (a_timage_out.at<float>(i, j) - out_min) *Conversion + in_min;

		}
	}

	return change_image;
	/*	double LL_band_M = 0.0;

	for (int x = 3; x < a_timage_in.rows / 2 - 3; x++)
	{
	for (int y = 3; y < a_timage_in.cols / 2 - 3; y++)
	{
	for (int i = 0; i < 2; i++)
	{
	for (int j = 0; j < 2; j++)
	{
	LL_band_M = LL_band_M + La*La*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + La*Lb*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + La*Lc*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + La*Ld*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + La*Le*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + La*Lf*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y - 1 + 2 * j);

	LL_band_M = LL_band_M + Lb*La*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + Lb*Lb*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + Lb*Lc*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + Lb*Ld*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + Lb*Le*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + Lb*Lf*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y - 1 + 2 * j);

	LL_band_M = LL_band_M + Lc*La*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + Lc*Lb*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + Lc*Lc*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + Lc*Ld*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + Lc*Le*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + Lc*Lf*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y - 1 + 2 * j);

	LL_band_M = LL_band_M + Ld*La*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + Ld*Lb*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + Ld*Lc*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + Ld*Ld*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + Ld*Le*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + Ld*Lf*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y - 1 + 2 * j);

	LL_band_M = LL_band_M + Le*La*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + Le*Lb*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + Le*Lc*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + Le*Ld*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + Le*Le*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + Le*Lf*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y - 1 + 2 * j);

	LL_band_M = LL_band_M + Lf*La*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + Lf*Lb*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + Lf*Lc*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + Lf*Ld*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + Lf*Le*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + Lf*Lf*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y - 1 + 2 * j);


	}
	}
	for (int i = 0; i < 2; i++)
	{
	LL_band_M = LL_band_M + La*Lg*a_timage_in.at<uchar>(2 * x - 6 + 12 * i, 2 * y);
	LL_band_M = LL_band_M + Lb*Lg*a_timage_in.at<uchar>(2 * x - 5 + 10 * i, 2 * y);
	LL_band_M = LL_band_M + Lc*Lg*a_timage_in.at<uchar>(2 * x - 4 + 8 * i, 2 * y);
	LL_band_M = LL_band_M + Ld*Lg*a_timage_in.at<uchar>(2 * x - 3 + 6 * i, 2 * y);
	LL_band_M = LL_band_M + Le*Lg*a_timage_in.at<uchar>(2 * x - 2 + 4 * i, 2 * y);
	LL_band_M = LL_band_M + Lf*Lg*a_timage_in.at<uchar>(2 * x - 1 + 2 * i, 2 * y);
	}
	for (int j = 0; j < 2; j++)
	{
	LL_band_M = LL_band_M + Lg*La*a_timage_in.at<uchar>(2 * x, 2 * y - 6 + 12 * j);
	LL_band_M = LL_band_M + Lg*Lb*a_timage_in.at<uchar>(2 * x, 2 * y - 5 + 10 * j);
	LL_band_M = LL_band_M + Lg*Lc*a_timage_in.at<uchar>(2 * x, 2 * y - 4 + 8 * j);
	LL_band_M = LL_band_M + Lg*Ld*a_timage_in.at<uchar>(2 * x, 2 * y - 3 + 6 * j);
	LL_band_M = LL_band_M + Lg*Le*a_timage_in.at<uchar>(2 * x, 2 * y - 2 + 4 * j);
	LL_band_M = LL_band_M + Lg*Lf*a_timage_in.at<uchar>(2 * x, 2 * y - 1 + 2 * j);
	}
	LL_band_M+=Lg*Lg*(a_timage_in.at<uchar>(2 * x, 2 * y));

	a_timage_out.at<float>(x-3 , y-3 ) = LL_band_M;
	}
	}


	minMaxIdx(a_timage_out, &out_min, &out_max);
	Conversion = (in_max - in_min) / (out_max - out_min);


	for (int i = 0; i < a_timage_out.rows; i++)
	{
	for (int j = 0; j < a_timage_out.cols; j++)
	{
	change_image.at<uchar>(i, j) = (a_timage_out.at<float>(i, j) - out_min) *Conversion + in_min;

	}
	}*/
}

