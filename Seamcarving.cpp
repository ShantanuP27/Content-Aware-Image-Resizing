#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void returnVerticalSeam(int res[],int** energy,int h,int w){

	int mini = INT_MAX;
	int index = 0;
	int y=h-1;
	for(int x=0;x<w;x++){
		if(mini>energy[y][x]){
			mini=energy[y][x];
			index=x;	
		}
	}
	res[h-1] = index;
	int x=index;
	for(int y = h-1; y>0; y--){
		if(x==w-1){
			if((min(energy[y-1][x],energy[y-1][x-1]))==energy[y-1][x-1]){
				res[y-1]=x-1;
				x=x-1;
			}else{
				res[y-1]=x;
			}
		}else if(x==0){
			if((min(energy[y-1][x],energy[y-1][x+1]))==energy[y-1][x+1]){
				res[y-1]=x+1;
				x=x+1;
			}else{
				res[y-1]=x;
			}
		}else {
			int k = min(energy[y-1][x],min(energy[y-1][x+1],energy[y-1][x-1]));
			if(k==energy[y-1][x+1]){
				res[y-1]=x+1;
				x=x+1;
			}else if(k==energy[y-1][x-1]){
				res[y-1]=x-1; 
				x=x-1;
			}else
				res[y-1]=x;
		}
	}
}
void returnHoriSeam(int res[],int** energy,int h,int w){

	int mini = INT_MAX;
	int index = 0;
	int x=w-1;
	for(int y=0;y<h;y++){
		if((energy[y][x])<mini){
			mini=energy[y][x];
			index=y;	
		}
	}
	res[w-1] = index;
	int y=index;
	for(int x = w-1; x>0; x--){
		if(y==h-1){
			if((min(energy[y-1][x-1],energy[y][x-1]))==energy[y-1][x-1]){
				res[x-1]=y-1;
				y=y-1;
			}else{
				res[x-1]=y;
			}
		}else if(y==0){
			if((min(energy[y][x-1],energy[y+1][x-1]))==energy[y+1][x-1]){
				res[x-1]=y+1;
				y=y+1;
			}else{
				res[x-1]=y;
			}
		}else {
			int k = min(energy[y][x-1],min(energy[y+1][x-1],energy[y-1][x-1]));
			if(k==energy[y+1][x-1]){
				res[x-1]=y+1;
				y=y+1;
			}else if(k==energy[y-1][x-1]){
				res[x-1]=y-1; 
				y=y-1;
			}else
				res[x-1]=y;
		}
	}
}

void calculateemVerti(Mat& img,int **energy,int height,int width){

	for(int r=0; r<height; r++){
		for(int c=0; c<width; c++){
			int row=r,col=c;
			if(c==0) col=width;
		        cv::Vec3b pixel1 = img.at<cv::Vec3b>(row, col-1);
        // Extract RGB values
		        int bx1 = pixel1[0];
        		int gx1 = pixel1[1];
        		int rx1 = pixel1[2];
        		col=c;
        		
        		if(c==width-1)	col=-1;
        		cv::Vec3b pixel2 = img.at<cv::Vec3b>(row, col+1);
        // Extract RGB values
		        int bx2 = pixel2[0];
        		int gx2 = pixel2[1];
        		int rx2 = pixel2[2];
        		col=c;
        		
        		if(r==0) row=height;
        		cv::Vec3b pixel3 = img.at<cv::Vec3b>(row-1, col);
        // Extract RGB values
		        int by1 = pixel3[0];
        		int gy1 = pixel3[1];
        		int ry1 = pixel3[2];
        		row=r;
        		
        		if(row==height-1)  row=-1;
        		cv::Vec3b pixel4 = img.at<cv::Vec3b>(row+1, col);
        // Extract RGB values
		        int by2 = pixel4[0];
        		int gy2 = pixel4[1];
        		int ry2 = pixel4[2];
        		row=r;
        		
        		double x = (bx1-bx2)*(bx1-bx2) + (gx1-gx2)*(gx1-gx2) + (rx1-rx2)*(rx1-rx2);
 		        double y = (by1-by2)*(by1-by2) + (gy1-gy2)*(gy1-gy2) + (ry1-ry2)*(ry1-ry2);
 		        
 		        energy[row][col] = sqrt(x+y);
		}
	}
	
	for(int y=1; y<height; y++){
		for(int x=0; x<width; x++){	
			if(x==0)
				energy[y][x]= energy[y][x]+min(energy[y-1][x],energy[y-1][x+1]);
			else if (x==width-1)
				energy[y][x]= energy[y][x]+min(energy[y-1][x],energy[y-1][x-1]);
			else
				energy[y][x]= energy[y][x]+min(energy[y-1][x],min(energy[y-1][x+1],energy[y-1][x-1]));
		}
	}	
	
}

void calculateemHori(Mat& img,int **energy,int height,int width){

	for(int r=0; r<height; r++){
		for(int c=0; c<width; c++){
			int row=r,col=c;
			if(c==0) col=width;
		        cv::Vec3b pixel1 = img.at<cv::Vec3b>(row, col-1);
        // Extract RGB values
		        int bx1 = pixel1[0];
        		int gx1 = pixel1[1];
        		int rx1 = pixel1[2];
        		col=c;
        		
        		if(c==width-1)	col=-1;
        		cv::Vec3b pixel2 = img.at<cv::Vec3b>(row, col+1);
        // Extract RGB values
		        int bx2 = pixel2[0];
        		int gx2 = pixel2[1];
        		int rx2 = pixel2[2];
        		col=c;
        		
        		if(r==0) row=height;
        		cv::Vec3b pixel3 = img.at<cv::Vec3b>(row-1, col);
        // Extract RGB values
		        int by1 = pixel3[0];
        		int gy1 = pixel3[1];
        		int ry1 = pixel3[2];
        		row=r;
        		
        		if(row==height-1)  row=-1;
        		cv::Vec3b pixel4 = img.at<cv::Vec3b>(row+1, col);
        // Extract RGB values
		        int by2 = pixel4[0];
        		int gy2 = pixel4[1];
        		int ry2 = pixel4[2];
        		row=r;
        		
        		double x = (bx1-bx2)*(bx1-bx2) + (gx1-gx2)*(gx1-gx2) + (rx1-rx2)*(rx1-rx2);
 		        double y = (by1-by2)*(by1-by2) + (gy1-gy2)*(gy1-gy2) + (ry1-ry2)*(ry1-ry2);
 		        
 		        energy[row][col] = sqrt(x+y);
		}
	}

	for(int x=1; x<width; x++){
		for(int y=0; y<height; y++){	
			if(y==0)
				energy[y][x]= energy[y][x]+min(energy[y][x-1],energy[y+1][x-1]);
			else if (y==height-1)
				energy[y][x]= energy[y][x]+min(energy[y][x-1],energy[y-1][x-1]);
			else
				energy[y][x]= energy[y][x]+min(energy[y-1][x-1],min(energy[y+1][x-1],energy[y][x-1]));
		}
	}
		
}


int main(int argc, char* argv[]){

	Mat img = imread(argv[1]);
	if(img.empty()){
		std::cout<<"Enter a valid image naming which exists\n";
		return 0;
	}else{
		std::cout<<"Image opened successfully \n";
	}
	int fw,fh;
	cout<<"Please enter desired FINAL desired pixel values to resize the image upto (ie the final resolution image should have) enter height and width respectively : ";
	cin>>fh>>fw;
	cout<<endl;
	int height = img.rows;
	int width = img .cols;
	
	//for vertical seam that is reduce width
	for(int j=1;j<=width-fw;j++){
		int **energy = new int *[height];
		for (int i = 0; i < height; i++) {
  			energy[i] = new int[width];
		}
		int *res = new int[height];
		calculateemVerti(img,energy,height,width);
		returnVerticalSeam(res,energy,height,width);
		
		for(int i=0;i<height;i++){
			img.at<cv::Vec3b>(i, res[i]) = cv::Vec3b(0, 0, 255);
		}
		imshow("Output_Image", img);
		waitKey(15);
		for(int i=0;i<height;i++){
			for(int z=res[i]; z<width-1; z++){
				img.at<cv::Vec3b>(i, z) = img.at<cv::Vec3b>(i, z+1);	
			}
		}
		width = width-1;
		for (int i = 0; i < height; i++) {
		    delete[] energy[i];
		}
		delete[] energy;
		delete[] res;
		img.cols--;
		
	}
	//for horizontal seam to reduce height
	for(int j=1;j<=height-fh;j++){
		int **energy = new int *[height];
		for (int i = 0; i < height; i++) {
  			energy[i] = new int[width];
		}
		int *res = new int[width];
		calculateemHori(img,energy,height,width);
		returnHoriSeam(res,energy,height,width);
		
		for(int i=0;i<width;i++){
			img.at<cv::Vec3b>(res[i], i) = cv::Vec3b(0, 0, 255);
		}
		imshow("Output_Image", img);
		waitKey(15);
		for(int i=0;i<width;i++){
			for(int z=res[i]; z<height-1; z++){
				img.at<cv::Vec3b>(z, i) = img.at<cv::Vec3b>(z+1, i);	
			}
		}
		for (int i = 0; i < height; i++) {
		    delete[] energy[i];
		}
		height = height-1;
		delete[] energy;
		delete[] res;
		img.rows--;	
	}	
	
	imshow("Output_Image", img);
	waitKey(1000);
	imwrite("final_output.jpeg",img);
}














