/*!
  * @file     LQ_BMP.h
  *
  * @brief    ͼƬBMP��ʽ����
  *
  * @author   ��ֲ����ԭ��
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

//ͼ������ѹ��������
#define BI_RGB	 		0  //û��ѹ��.RGB 5,5,5.
#define BI_RLE8 		1  //ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��
#define BI_RLE4 		2  //ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
#define BI_BITFIELDS 	3  //ÿ�����صı�����ָ������������� 

/*!
  * @brief    BMP �ļ�ͷ
  *
  * @note     
  */ 
typedef __packed struct
{
    uint32_t biSize ;		   	//˵��BITMAPINFOHEADER�ṹ����Ҫ��������
    long  biWidth ;		       	//˵��ͼ��Ŀ�ȣ�������Ϊ��λ 
    long  biHeight ;	     	//˵��ͼ��ĸ߶ȣ�������Ϊ��λ 
    uint16_t  biPlanes ;	   	//ΪĿ���豸˵��λ��������ֵ�����Ǳ���Ϊ1 
    uint16_t  biBitCount ;	   	//˵��������/���أ���ֵΪ1��4��8��16��24����32
    uint32_t biCompression ;  	//˵��ͼ������ѹ�������͡���ֵ����������ֵ֮һ��
	//BI_RGB��û��ѹ����
	//BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)��  
    //BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����
  	//BI_BITFIELDS��ÿ�����صı�����ָ�������������
    uint32_t biSizeImage ;		//˵��ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0  
    long  biXPelsPerMeter ;	    //˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ
    long  biYPelsPerMeter ;	    //˵����ֱ�ֱ��ʣ�������/�ױ�ʾ
    uint32_t biClrUsed ;	  	//˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
    uint32_t biClrImportant ; 	//˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ�������0����ʾ����Ҫ�� 
}BITMAPINFOHEADER ;
//BMPͷ�ļ�
typedef __packed struct
{
    uint16_t  bfType ;          //�ļ���־.ֻ��'BM',����ʶ��BMPλͼ����
    uint32_t  bfSize ;	        //�ļ���С,ռ�ĸ��ֽ�
    uint16_t  bfReserved1 ;     //����
    uint16_t  bfReserved2 ;     //����
    uint32_t  bfOffBits ;       //���ļ���ʼ��λͼ����(bitmap data)��ʼ֮��ĵ�ƫ����
}BITMAPFILEHEADER ;
//��ɫ�� 
typedef __packed struct 
{
    uint8_t rgbBlue ;    //ָ����ɫǿ��
    uint8_t rgbGreen ;	 //ָ����ɫǿ�� 
    uint8_t rgbRed ;	 //ָ����ɫǿ�� 
    uint8_t rgbReserved ;//����������Ϊ0 
}RGBQUAD ;
//λͼ��Ϣͷ
typedef __packed struct
{ 
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;  
#ifdef LQOV7725RGB
	uint32_t RGB_MASK[3];			//��ɫ�����ڴ��RGB����.
    
#else
	RGBQUAD bmiColors[256]; 
#endif
	 
}BITMAPINFO; 
typedef RGBQUAD * LPRGBQUAD;       //��ɫ��  


/*!
  * @brief    ���һ��ͼƬͷ��Ϣ
  *
  * @param    height    :ͼƬ�߶�
  * @param    width     :ͼƬ���
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/28 ������
  */
void BMP_GetHead(uint16_t height, uint16_t width);


/*!
  * @brief    BMP��ͼ��ʼ��
  *
  * @param    filename  :ͼƬ����
  * @param    height    :ͼƬ�߶�
  * @param    width     :ͼƬ���
  *
  * @return   
  *
  * @note     ͼƬ���ҪΪ4�ı���
  *
  * @see      
  *
  * @date     2019/8/29 ������
  */
void BMP_Init(uint16_t height, uint16_t width);


/*!
  * @brief    ����һ��λͼ
  *
  * @param    data  ��ͼƬ���ݵ��׵�ַ
  *
  * @return   
  *
  * @note     ͼƬ���ҪΪ4�ı���
  *
  * @see      
  *
  * @date     2019/8/29 ������
  */
uint8_t BMP_Save(uint8_t *data);



#endif





