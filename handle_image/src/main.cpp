#include <math.h>
#include <sys/time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream> 
#include "mysql/mysql.h"
#include <unistd.h> 
#include "../include/Image_Shrink.h"
#include "../include/mmysql.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("eg: ./a.out port\n");
        exit(1);

    }

    MYSQL mysql; 
    mysql_init(&mysql);
    if(mysql_real_connect(&mysql,"localhost","root","0000","handle_image",0,NULL,0) == NULL){
        cout<<"connect fail"<<endl;
        return -1;

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
    //std::cout << "usetime:"<< timeuse <<" ms" <<std::endl;
    Add(&mysql,filename,timeuse);/*添加数据*/
    std::cout << "effectiave area: (" << res_area.x << ", " << res_area.y << ", " << res_area.width << ", " << res_area.height << ")" << std::endl;
    imshow("100*100",dst);
    return 0;
}
