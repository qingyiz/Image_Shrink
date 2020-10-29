#include "mmysql.h"
#include <unistd.h> 
#include "mysql/mysql.h"
#include <iostream>
using namespace std;
int main()
{
    MYSQL mysql; 
    mysql_init(&mysql);
    if(mysql_real_connect(&mysql,"localhost","root","0000","handle_image",0,NULL,0) == NULL){
        cout<<"connect fail"<<endl;
        return -1;
    }
    Add(&mysql,"image1",0.622);
    mysql_close(&mysql);
    return 0;
}
