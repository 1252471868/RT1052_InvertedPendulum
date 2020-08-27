/*!
  * @file     LQ_BMP.c
  *
  * @brief    ͼƬBMP��ʽ����
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



/**  @brief    λͼ��Ϣͷ  */
BITMAPINFO hbmp;
	     		
static FIL f_bmp;

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
void BMP_GetHead(uint16_t height, uint16_t width)
{
    
    uint16_t bmpheadsize;			//bmpͷ��С
    
    bmpheadsize = sizeof(BITMAPINFO);//�õ�bmp�ļ�ͷ�Ĵ�С   
	memset((uint8_t*)&hbmp,0,sizeof(BITMAPINFO));//��������뵽���ڴ�.	    
	hbmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);//��Ϣͷ��С
	hbmp.bmiHeader.biWidth=width;	 	//bmp�Ŀ��
	hbmp.bmiHeader.biHeight=height; 	//bmp�ĸ߶�
	hbmp.bmiHeader.biPlanes=1;	 		//��Ϊ1
#ifdef LQOV7725RGB
	hbmp.bmiHeader.biBitCount=16;	 	//bmpΪ16λɫbmp
    hbmp.RGB_MASK[0]=0X00F800;	 		//��ɫ����
	hbmp.RGB_MASK[1]=0X0007E0;	 		//��ɫ����
	hbmp.RGB_MASK[2]=0X00001F;	 		//��ɫ����
    hbmp.bmiHeader.biCompression=BI_BITFIELDS;//ÿ�����صı�����ָ�������������
	
#else
    hbmp.bmiHeader.biBitCount=8;	 	//bmpΪ8λɫbmp
    hbmp.bmiHeader.biCompression=BI_BITFIELDS;//ÿ�����صı�����ָ�������������
    for(int i=0;i<256;i++)
    {
        hbmp.bmiColors[i].rgbBlue=i;
        hbmp.bmiColors[i].rgbGreen=i;
        hbmp.bmiColors[i].rgbRed=i;
        hbmp.bmiColors[i].rgbReserved=0;
    } 
#endif
	
 	hbmp.bmiHeader.biSizeImage=hbmp.bmiHeader.biHeight*hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;//bmp��������С
 				   
	hbmp.bmfHeader.bfType=((uint16_t)'M'<<8)+'B';//BM��ʽ��־
	hbmp.bmfHeader.bfSize=bmpheadsize+hbmp.bmiHeader.biSizeImage;//����bmp�Ĵ�С
   	hbmp.bmfHeader.bfOffBits=bmpheadsize;   //����������ƫ��
  
}


/*!
  * @brief    ����һ��ͼƬ
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @see      
  *
  * @date     2019/8/29 ������
  */
FRESULT BMP_OpenPicture(void)
{
    char name[32];
    /* ����ͼƬ�ļ� */				 
	static uint16_t index = 0;
    FRESULT error;
	while(index<0XFFFF)
	{
        /* Ĭ���ļ��� */
		sprintf((char*)name,"/PICTURE/PIC%05d.bmp",index);
		error=f_open(&f_bmp,(const char*)name, FA_READ);  //���Դ�����ļ�
		if(error == FR_NO_FILE)
        {
            PRINTF("�ļ����� %s\r\n", name);
            error = f_open(&f_bmp,(const char*)name, (FA_WRITE | FA_READ | FA_CREATE_NEW));  //�����ļ�
            return error;
        }
        f_close(&f_bmp);
		index++;     
	}
    return FR_DISK_ERR;
}


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
void BMP_Init(uint16_t height, uint16_t width)
{
    SCB_DisableDCache();
    
    /* ���λͼ����ͷ��Ϣ */
    BMP_GetHead(height, width);
    
    /* SD����ʼ�� */
	SDCARD_Init();
    
    PRINTF("\r\n�½��ļ��� PICTURE......\r\n");
    FRESULT error = f_mkdir(_T("/PICTURE"));
    if (error)
    {
        if (error == FR_EXIST)
        {
            PRINTF("�ļ��д����ɹ�\r\n");
        }
        else
        {
            PRINTF("�ļ��д���ʧ��\r\n");
        }
    }
    
    SCB_EnableDCache();
}

#ifdef LQOV7725YUV
/*!
  * @brief    ��OV7725��YUV���ݱ���Ϊ�Ҷ�����
  *
  * @param    data  ��ԭʼͼƬ���ݵ��׵�ַ
  * @param    buff  �����ͼƬ���ݵ��׵�ַ
  *
  * @return   
  *
  * @note     ͼƬ���ҪΪ4�ı���
  *
  * @see      
  *
  * @date     2019/8/29 ������
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
        PRINTF("ͼƬ����ʧ��\r\n");
        return 1;
    }
    uint32_t temp = hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;
#ifdef LQOV7725YUV
	SDK_ALIGN(uint8_t temp_data[APP_CAMERA_WIDTH][APP_CAMERA_HEIGHT], 4);
	uint8_t *p = (uint8_t *)temp_data;
	YUV_ToGray(data, (uint8_t *)p);
	/* д������ */
    for(int i = 0; i < hbmp.bmiHeader.biHeight; i++)
    {
        f_write(&f_bmp,(uint8_t *)p, temp, &bytesWritten);//д������
        p += temp;
    }
#else
    /* д������ */
    for(int i = 0; i < hbmp.bmiHeader.biHeight; i++)
    {
        f_write(&f_bmp,(uint8_t *)data, temp, &bytesWritten);//д������
        data += temp;
    }
#endif
    f_close(&f_bmp);
    
    SCB_EnableDCache();
    return 0;

}




