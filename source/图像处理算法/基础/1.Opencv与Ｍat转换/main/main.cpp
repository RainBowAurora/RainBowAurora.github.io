#include <opencv2/opencv.hpp>
#include <iostream>

/***
 * 函数功能: Mat转一维vector
 * 参数:
 *      mat - 输入mat
 * 输出:
 *      一维数组
 **/
template<class _Tp>
std::vector<_Tp> Mat2vector(const cv::Mat &mat)
{
    return (std::vector<_Tp>)mat.reshape(1, 1);
}

/***
 * 函数功能: vector转Ｍat
 * 参数:
 *      vec - 一维数组
 *      channel - 图片的通道数
 * 　　　rows - 图像的行数
 * 输出:
 *      mat二维图
 **/

template<class _Tp>
cv::Mat vector2Mat(std::vector<_Tp> vec, int channel, int rows)
{
    cv::Mat mat = cv::Mat(vec, true);
    //必须拷贝一份否则会出错
    cv::Mat dst = mat.reshape(channel, rows).clone();
    return dst;
}


/***
 * 函数功能: 数组转Ｍat
 * 参数:
 *      arry - 输入数组
 *      rows - 图像行数
 *      cols - 图像列数
 *      type - 图像类型
 * 输出:
 *      数组
 **/
cv::Mat array2Mat(void *arry, int rows, int cols, int type)
{
    cv::Mat dst = cv::Mat(rows, cols, type, (void*)arry);
    return dst.clone();
}

/***
 * 函数功能: Mat转一维数组
 * 参数:
 *      mat - 输入mat
 * 输出:
 *      一维数组
 **/
template<class _Tp>
_Tp * Mat2array(const cv::Mat &mat)
{
    _Tp *array = new _Tp[mat.total()];
    if(mat.isContinuous()){
        array = mat.data;
    }
    return array;
}


int main(int argc, char **argv)
{
    //创建Ｍat数据
    cv::Mat src_Mat = (cv::Mat_<uchar>(3, 3) << 1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9);
    //原始数据
    std::cout << "src_Mat = " << std::endl << src_Mat << std::endl;

    //测试Mat->vector
    std::vector<uchar> vec;
    vec = Mat2vector<uchar>(src_Mat);
    cv::Mat test_Mat;
    test_Mat = vector2Mat<uchar>(vec, 1, 3);
    std::cout << "test_Mat = " << std::endl << test_Mat<< std::endl;

    //测试vector->Mat
    std::cout << "vec = " << std::endl;
    for(size_t i = 0; i < test_Mat.total(); i++){
        std::cout  << (uint)vec[i] << " ";
    }
    std::cout << std::endl;

    //测试Mat->array
    uchar *array;
    array = Mat2array<uchar>(src_Mat);
    std::cout << "array = " << std::endl;
    for(size_t i = 0; i <src_Mat.total(); i++){
        std::cout << (uint)array[i] << " ";
    }
    std::cout << std::endl;

    //测试array->Mat
    cv::Mat test_Mat2;
    test_Mat2 = array2Mat(array, 3, 3, CV_8UC1);
    std::cout << "test_Mat2 = " << std::endl << test_Mat2 << std::endl;
    return 0;
}
