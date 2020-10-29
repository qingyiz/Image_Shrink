#include <iostream> 
#include <string> 
#include <stack> 
#include <algorithm> 
#include <sstream> 
#include "mysql/mysql.h"
#include <unistd.h> 
#include "../include/mmysql.h"

using namespace std; 

string FloatToStr(float num)
{ 
    stringstream ss; 
    ss.clear(); 
    ss << num; 
    return ss.str();

}
void Add(MYSQL* mysql,string imagename,double usetime) 
{ 
    string sql = "INSERT INTO usetime values('"+imagename+"',"+FloatToStr(usetime)+");";
    cout<<sql<<endl;
    //string sql1 = "INSERT INTO usetime values('fffff',0.618);";
    mysql_query(mysql,sql.c_str());
}

