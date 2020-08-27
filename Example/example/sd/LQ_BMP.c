/*!
  * @file     LQ_BMP.c
  *
  * @brief    图片BMP格式编码
  *
  * @author   LQ-005
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
#include "fsl_sd.h"
#include "fsl_debug_console.h"
#include "ff.h"
#include "stdio.h"
#include "LQ_BMP.h"
#include "LQ_SDCard.h"
#include "stdlib.h"



/**  @brief    位图信息头  */
BITMAPINFO hbmp;
	     		
static FIL f_bmp;

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
void BMP_GetHead(uint16_t height, uint16_t width)
{
    
    uint16_t bmpheadsize;			//bmp头大小
    
    bmpheadsize = sizeof(BITMAPINFO);//得到bmp文件头的大小   
	memset((uint8_t*)&hbmp,0,sizeof(BITMAPINFO));//置零空申请到的内存.	    
	hbmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);//信息头大小
	hbmp.bmiHeader.biWidth=width;	 	//bmp的宽度
	hbmp.bmiHeader.biHeight=height; 	//bmp的高度
	hbmp.bmiHeader.biPlanes=1;	 		//恒为1
#ifdef LQOV7725RGB
	hbmp.bmiHeader.biBitCount=16;	 	//bmp为16位色bmp
    hbmp.RGB_MASK[0]=0X00F800;	 		//红色掩码
	hbmp.RGB_MASK[1]=0X0007E0;	 		//绿色掩码
	hbmp.RGB_MASK[2]=0X00001F;	 		//蓝色掩码
    hbmp.bmiHeader.biCompression=BI_BITFIELDS;//每个象素的比特由指定的掩码决定。
	
#else
    hbmp.bmiHeader.biBitCount=8;	 	//bmp为8位色bmp
    hbmp.bmiHeader.biCompression=BI_BITFIELDS;//每个象素的比特由指定的掩码决定。
    for(int i=0;i<256;i++)
    {
        hbmp.bmiColors[i].rgbBlue=i;
        hbmp.bmiColors[i].rgbGreen=i;
        hbmp.bmiColors[i].rgbRed=i;
        hbmp.bmiColors[i].rgbReserved=0;
    } 
#endif
	
 	hbmp.bmiHeader.biSizeImage=hbmp.bmiHeader.biHeight*hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;//bmp数据区大小
 				   
	hbmp.bmfHeader.bfType=((uint16_t)'M'<<8)+'B';//BM格式标志
	hbmp.bmfHeader.bfSize=bmpheadsize+hbmp.bmiHeader.biSizeImage;//整个bmp的大小
   	hbmp.bmfHeader.bfOffBits=bmpheadsize;   //到数据区的偏移
  
}


/*!
  * @brief    创建一幅图片
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/29 星期四
  */
FRESULT BMP_OpenPicture(void)
{
    char name[32];
    /* 创建图片文件 */				 
	static uint16_t index = 0;
    FRESULT error;
	while(index<0XFFFF)
	{
        /* 默认文件名 */
		sprintf((char*)name,"/PICTURE/PIC%05d.bmp",index);
		error=f_open(&f_bmp,(const char*)name, FA_READ);  //尝试打开这个文件
		if(error == FR_NO_FILE)
        {
            PRINTF("文件名： %s\r\n", name);
            error = f_open(&f_bmp,(const char*)name, (FA_WRITE | FA_READ | FA_CREATE_NEW));  //创建文件
            return error;
        }
        f_close(&f_bmp);
		index++;     
	}
    return FR_DISK_ERR;
}


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
void BMP_Init(uint16_t height, uint16_t width)
{
    SCB_DisableDCache();
    
    /* 填充位图数据头信息 */
    BMP_GetHead(height, width);
    
    /* SD卡初始化 */
	SDCARD_Init();
    
    PRINTF("\r\n新建文件夹 PICTURE......\r\n");
    FRESULT error = f_mkdir(_T("/PICTURE"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("文件夹创建成功\r\n");
        }
        else
        {
            PRINTF("文件夹创建失败\r\n");
        }
    }
    
    SCB_EnableDCache();
}

#ifdef LQOV7725YUV
/*!
  * @brief    将OV7725的YUV数据保存为灰度数据
  *
  * @param    data  ：原始图片数据的首地址
  * @param    buff  ：输出图片数据的首地址
  *
  * @return   
  *
  * @note     图片宽高要为4的倍数
  *
  * @see      
  *
  * @date     2019/8/29 星期四
  */
void YUV_ToGray(uint8_t *data, uint8_t *buff)
{
	data ++;
	for(int i = 0; i < APP_CAMERA_HEIGHT; i++)
	{
		for(int j = 0; j < APP_CAMERA_WIDTH; j++)
		{
			*buff++ = *data;
			data += 2;
		}
	}

}
#endif

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
uint8_t BMP_Save(uint8_t *data)
{
    SCB_DisableDCache();
    UINT bytesWritten;
    
    FRESULT error = BMP_OpenPicture();
    
    if(error == FR_OK)
    {
        error = f_write(&f_bmp, (uint8_t *)&hbmp, hbmp.bmfHeader.bfOffBits, &bytesWritten);
    }
    else
    {
        PRINTF("图片创建失败\r\n");
        return 1;
    }
    uint32_t temp = hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;
#ifdef LQOV7725YUV
	SDK_ALIGN(uint8_t temp_data[APP_CAMERA_WIDTH][APP_CAMERA_HEIGHT], 4);
	uint8_t *p = (uint8_t *)temp_data;
	YUV_ToGray(data, (uint8_t *)p);
	/* 写入数据 */
    for(int i = 0; i < hbmp.bmiHeader.biHeight; i++)
    {
        f_write(&f_bmp,(uint8_t *)p, temp, &bytesWritten);//写入数据
        p += temp;
    }
#else
    /* 写入数据 */
    for(int i = 0; i < hbmp.bmiHeader.biHeight; i++)
    {
        f_write(&f_bmp,(uint8_t *)data, temp, &bytesWritten);//写入数据
        data += temp;
    }
#endif
    f_close(&f_bmp);
    
    SCB_EnableDCache();
    return 0;

}




