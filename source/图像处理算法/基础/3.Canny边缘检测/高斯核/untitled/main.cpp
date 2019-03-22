#include <iostream>
#include <cmath>

void getOneGuassionArray(int size, double sigma, double **gauss);
int main(int argc, char **argv)
{
    int size = 3;
    double sigma = 0.6;

    //动态数组生成
    double **gauss_kernel = new double*[size];
    for(int i = 0; i < size; i++){
        gauss_kernel[i] = new double[size];
    }

    getOneGuassionArray(size, sigma, gauss_kernel);

    std::cout << "gauss_kernel = " << std::endl;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << gauss_kernel[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout  << std::endl;

    return 0;
}

/**
* 功能: 求解高斯核
* 参数:
*      sigma - σ(标准差)
*      size - 高斯矩阵大小(只能是奇数)
**/
//高斯卷积核生成
void getOneGuassionArray(int size, double sigma, double **gauss)
{
    double pi = 3.1415927;
    int center = size/2;
    double sum = 0.0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
        gauss[i][j] = exp(-(pow((i-center),2) + pow((j-center),2))/(2*pow(sigma,2))) / (2*pi*pow(sigma,2));
        sum += gauss[i][j];
        }
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            gauss[i][j] = gauss[i][j] / sum;
        }
    }
}
