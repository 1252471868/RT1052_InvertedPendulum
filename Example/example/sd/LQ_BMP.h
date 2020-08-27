/*!
  * @file     LQ_BMP.h
  *
  * @brief    图片BMP格式编码
  *
  * @author   移植正点原子
  *
  * @note     
  *
  * @version  
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     
  */ 
#ifndef __LQ_BMP_H
#define __LQ_BMP_H

#include "stdint.h"
#include "include.h"

//图象数据压缩的类型
#define BI_RGB	 		0  //没有压缩.RGB 5,5,5.
#define BI_RLE8 		1  //每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；
#define BI_RLE4 		2  //每个象素4比特的RLE压缩编码，压缩格式由2字节组成
#define BI_BITFIELDS 	3  //每个象素的比特由指定的掩码决定。 

/*!
  * @brief    BMP 文件头
  *
  * @note     
  */ 
typedef __packed struct
{
    uint32_t biSize ;		   	//说明BITMAPINFOHEADER结构所需要的字数。
    long  biWidth ;		       	//说明图象的宽度，以象素为单位 
    long  biHeight ;	     	//说明图象的高度，以象素为单位 
    uint16_t  biPlanes ;	   	//为目标设备说明位面数，其值将总是被设为1 
    uint16_t  biBitCount ;	   	//说明比特数/象素，其值为1、4、8、16、24、或32
    uint32_t biCompression ;  	//说明图象数据压缩的类型。其值可以是下述值之一：
	//BI_RGB：没有压缩；
	//BI_RLE8：每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)；  
    //BI_RLE4：每个象素4比特的RLE压缩编码，压缩格式由2字节组成
  	//BI_BITFIELDS：每个象素的比特由指定的掩码决定。
    uint32_t biSizeImage ;		//说明图象的大小，以字节为单位。当用BI_RGB格式时，可设置为0  
    long  biXPelsPerMeter ;	    //说明水平分辨率，用象素/米表示
    long  biYPelsPerMeter ;	    //说明垂直分辨率，用象素/米表示
    uint32_t biClrUsed ;	  	//说明位图实际使用的彩色表中的颜色索引数
    uint32_t biClrImportant ; 	//说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。 
}BITMAPINFOHEADER ;
//BMP头文件
typedef __packed struct
{
    uint16_t  bfType ;          //文件标志.只对'BM',用来识别BMP位图类型
    uint32_t  bfSize ;	        //文件大小,占四个字节
    uint16_t  bfReserved1 ;     //保留
    uint16_t  bfReserved2 ;     //保留
    uint32_t  bfOffBits ;       //从文件开始到位图数据(bitmap data)开始之间的的偏移量
}BITMAPFILEHEADER ;
//彩色表 
typedef __packed struct 
{
    uint8_t rgbBlue ;    //指定蓝色强度
    uint8_t rgbGreen ;	 //指定绿色强度 
    uint8_t rgbRed ;	 //指定红色强度 
    uint8_t rgbReserved ;//保留，设置为0 
}RGBQUAD ;
//位图信息头
typedef __packed struct
{ 
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;  
#ifdef LQOV7725RGB
	uint32_t RGB_MASK[3];			//调色板用于存放RGB掩码.
    
#else
	RGBQUAD bmiColors[256]; 
#endif
	 
}BITMAPINFO; 
typedef RGBQUAD * LPRGBQUAD;       //彩色表  


/*!
  * @brief    填充一幅图片头信息
  *
  * @param    height    :图片高度
  * @param    width     :图片宽度
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/28 星期三
  */
void BMP_GetHead(uint16_t height, uint16_t width);


/*!
  * @brief    BMP存图初始化
  *
  * @param    filename  :图片名字
  * @param    height    :图片高度
  * @param    width     :图片宽度
  *
  * @return   
  *
  * @note     图片宽高要为4的倍数
  *
  * @see      
  *
  * @date     2019/8/29 星期四
  */
void BMP_Init(uint16_t height, uint16_t width);


/*!
  * @brief    保存一幅位图
  *
  * @param    data  ：图片数据的首地址
  *
  * @return   
  *
  * @note     图片宽高要为4的倍数
  *
  * @see      
  *
  * @date     2019/8/29 星期四
  */
uint8_t BMP_Save(uint8_t *data);



#endif





