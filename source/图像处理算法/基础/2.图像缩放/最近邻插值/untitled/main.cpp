#include <opencv2/opencv.hpp>
#include <iostream>

#define ZOOM_SIZE 512

double distance_checkerboard(double x0, double y0, double x1, double y1);
double distance_manhattan(double x0, double y0, double x1, double y1);
double distance_euclid(double x0, double y0, double x1, double y1);

void nearestScaler(cv::Mat &input_image, cv::Mat &output_image, cv::Size Size, int distance_type);

int main()
{
    cv::Mat srcImage;
    cv::Mat dstImage;
    srcImage = cv::imread("../../../../../../image/1.jpg");

    if(srcImage.empty()){
        std::cout << "图片不存在请检查图片" << std::endl;
        return -1;
    }
            cv::imshow("原始图", srcImage);

    //计算缩放尺寸
    int scalar_rows = (int)ZOOM_SIZE;
    int scalar_cols = (int)(ZOOM_SIZE * srcImage.rows/(double)srcImage.cols);

    cv::cvtColor(srcImage, srcImage, CV_BGR2GRAY);

   nearestScaler(srcImage, dstImage, cv::Size(scalar_rows, scalar_cols), 1);


    cv::imshow("最近邻插值", dstImage);
    cv::waitKey(0);
    return 0;
}


/**
* 函数功能:使用最近邻插值方法缩放图像
* 参数:
*      input_image - 输入图像(单色图像)
*      output_image - 输出图像
*      size -输出图像大小(像素)
*      distance_type - 计算距离方法 0 欧式距离 1 曼哈顿距离 2 切比雪夫距离
**/
void nearestScaler(cv::Mat &input_image, cv::Mat &output_image, cv::Size size, int distance_type)
{
  //拷贝输入图像
  cv::Mat temp_image = input_image.clone();
  output_image = cv::Mat(size, temp_image.type());
  //计算缩放比例
  double scale_row = static_cast<double>(temp_image.rows)/size.height;
  double scale_col = static_cast<double>(temp_image.cols)/size.width;
  //遍历图像
  for(int rows = 0; rows < size.height; rows++){
    for(int cols = 0; cols < size.width; cols++){
      //计算缩放后原始图坐标
      double x = (rows + 0.5) * scale_row + 0.5;
      double y = (cols + 0.5) * scale_col + 0.5;
      //找出坐标周围的四个点
      int x0 = static_cast<uint>(x);
      if(x0 > temp_image.rows - 1) x0 = temp_image.rows - 1;
      int x1 = x0 + 1;
      int y0 = static_cast<uint>(y);
      if(y0 > temp_image.cols - 1) y0 = temp_image.cols - 1;

      int y1 = y0 + 1;
        //使用距离度量公式找出最小距离
        std::vector<double>dist(4);
        switch(distance_type){
          case 0://欧氏距离
            dist[0] = distance_euclid(x, y, x0, y0);
            dist[1] = distance_euclid(x, y, x1, y0);
            dist[2] = distance_euclid(x, y, x0, y1);
            dist[3] = distance_euclid(x, y, x1, y1);
            break;
          case 1://曼哈顿距离
            dist[0] = distance_manhattan(x, y, x0 ,y0);
            dist[1] = distance_manhattan(x, y, x1 ,y0);
            dist[2] = distance_manhattan(x, y, x0 ,y1);
            dist[3] = distance_manhattan(x, y, x1 ,y1);
            break;
          case 2://棋盘距离
            dist[0] = distance_checkerboard(x, y, x0, y0);
            dist[1] = distance_checkerboard(x, y, x1, y0);
            dist[2] = distance_checkerboard(x, y, x0, y1);
            dist[3] = distance_checkerboard(x, y, x1, y1);
            break;
          default:
            break;
           }

          //找出最小距离对因的下标
          auto smallest = min_element(std::begin(dist), std::end(dist));
          int min_index = distance(std::begin(dist), smallest);
          //图像插值
          switch(min_index){
            case 0:
               output_image.at<uchar>(rows, cols) = temp_image.at<uchar>(x0, y0);
               break;
            case 1:
               output_image.at<uchar>(rows, cols) = temp_image.at<uchar>(x1, y0);
               break;
            case 2:
               output_image.at<uchar>(rows, cols) = temp_image.at<uchar>(x0, y1);
               break;
            case 3:
               output_image.at<uchar>(rows, cols) = temp_image.at<uchar>(x1, y1);
               break;
            default:
               break;

          }
      }
   }
}

double distance_euclid(double x0, double y0, double x1, double y1)
{
  double distance = sqrt(pow((x0 - x1), 2)+ pow((y0 - y1), 2));
  return distance;
}

double distance_manhattan(double x0, double y0, double x1, double y1)
{
  double distance = fabs(x0 - x1)+fabs(y0 - y1);
  return distance;
}

double distance_checkerboard(double x0, double y0, double x1, double y1)
{
  double distance = fabs(x0 - x1) > fabs(y0 - y1)?fabs(x0 - x1):fabs(y0 - y1);
  return distance;
}
