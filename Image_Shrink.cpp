#include <math.h>
#include <sys/time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct object_rect {
    int x;      /*左上角x*/
    int y;      /*左上角y*/
    int width;  /*长度*/
    int height; /*宽度*/
};
/*函数名：	resize_uniform()
 *函数功能：等比例缩放函数
 *参数：src 原始图像
 *		dst 输出目标图像
 *		dst_size 目标图像的大小
 *		effect_area 有效区域，就是非黑色区域
 */
int resize_uniform(Mat &src, Mat &dst, Size dst_size, object_rect &effect_area)
{
    int w = src.cols;
    int h = src.rows;
    int dst_w = dst_size.width;
    int dst_h = dst_size.height;
    std::cout << "src: (" << h << ", " << w << ")" << std::endl;
    dst = Mat(Size(dst_w, dst_h), CV_8UC3, Scalar(0));

    float ratio_src = w*1.0 / h;
    float ratio_dst = dst_w*1.0 / dst_h;

    int tmp_w=0;
    int tmp_h=0;
    if (ratio_src > ratio_dst) {
        tmp_w = dst_w;
        tmp_h = floor((dst_w*1.0 / w) * h);
    } else if (ratio_src < ratio_dst){
        tmp_h = dst_h;
        tmp_w = floor((dst_h*1.0 / h) * w);
    } else {
        resize(src, dst, dst_size);
        effect_area.x = 0;
        effect_area.y = 0;
        effect_area.width = dst_w;
        effect_area.height = dst_h;
        return 0;
    }

    std::cout << "tmp: (" << tmp_h << ", " << tmp_w << ")" << std::endl;
    Mat tmp;
    resize(src, tmp, Size(tmp_w, tmp_h));

    if (tmp_w != dst_w) { //高对齐，宽没对齐
        int index_w = floor((dst_w - tmp_w) / 2.0);
        std::cout << "index_w: " << index_w << std::endl;
        for (int i=0; i<dst_h; i++) {
            memcpy(dst.data+i*dst_w*3 + index_w*3, tmp.data+i*tmp_w*3, tmp_w*3);
        }
        effect_area.x = index_w;
        effect_area.y = 0;
        effect_area.width = tmp_w;
        effect_area.height = tmp_h;
    } else if (tmp_h != dst_h) { //宽对齐， 高没有对齐
        int index_h = floor((dst_h - tmp_h) / 2.0);
        std::cout << "index_h: " << index_h << std::endl;
        memcpy(dst.data+index_h*dst_w*3, tmp.data, tmp_w*tmp_h*3);
        effect_area.x = 0;
        effect_area.y = index_h;
        effect_area.width = tmp_w;
        effect_area.height = tmp_h;
    } else {
        printf("error\n");
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("eg: ./a.out port\n");
        exit(1);

    }

    string filename = argv[1];
    timeval starttime,endtime;/*开始时间，结束时间*/
    Mat img = imread(filename, 3);
    Mat dst;
    object_rect res_area;

    gettimeofday(&starttime,0);/*开始时间*/

    (void)resize_uniform(img, dst, Size(100, 100), res_area);
    imwrite("out.jpg", dst);

    gettimeofday(&endtime,0);/*结束时间*/
    double timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) 
        + endtime.tv_usec - starttime.tv_usec;
    /*除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，
     * 如果除以1则进行微妙级别计时*/
    timeuse /=1000;
    std::cout << "usetime:"<< timeuse <<" ms" <<std::endl;
    std::cout << "effectiave area: (" << res_area.x << ", " << res_area.y << ", " << res_area.width << ", " << res_area.height << ")" << std::endl;
    imshow("100*100",dst);
    return 0;
}
