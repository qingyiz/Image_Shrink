# 2.后台功能

## 1.实现一个后台功能，支持用户上传图片，后台用opencv对图片缩放后返回处理后的图片；
## 2.图片处理的耗时存到数据库，可供未来统计平均耗时；
## 3.图片等比例缩放为100x100像素, 其中未被图片覆盖的位置用黑色填充。
## 4.要求在Linux下实现，附上Readme文件

## 首先你得保证你的linux里有opencv
## 如果没有可以找度娘
## 本人环境为ubuntu16.04 + opencv-3.4.0
## 进入到该目录后

### cmake .
### make
### ./Image_Shrink 1.jpg

## 但是以上步骤是没有使用mysql数据库的

## 执行以下命令

### sudo service mysql start //启动MySQL
### mysql -u root -p  //然后输入你的密码，root密码

##  进入到mysql界面后  
### create database handle_image;   //创建数据库
### use handle_image;          //进入到该数据库
### create table usetime(filename varchar(30),usetime float); //创建表

## 到此为止，数据库表已经创建好了

## 重新启动一个终端,进入该目录

###  g++ test.cpp mmysql.cpp -o test -lmysqlclient
###  ./test

## 然后再进入刚刚那个mysql界面

### select * from usetime;

## 然后会多一条刚刚录入的信息，表明数据库操作也是没有问题的

## 现在就是只需要把两个模块整合起来即可

### cd handle_image/
### g++ ./src/*.cpp -o handle `pkg-config --cflags --libs opencv` -lmysqlclient
### ./handle 1.jpg
## 然后就会输出一个out.jpg文件，并在相应的数据库中保存使用时间


