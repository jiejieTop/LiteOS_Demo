#ifndef _DEBUG_H
#define _DEBUG_H
/************************************************************
  * @brief   debug.h
  * @author  jiejie
  * @github  https://github.com/jiejieTop
  * @date    2018-xx-xx
  * @version v1.0
  * @note    此文件用于打印日志信息
  ***********************************************************/
/* c 标准库 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>



/**
* @name Debug print 
* @{
*/
#define PRINTF_DEBUG_ENABLE		1	/* 打印调试信息 */
#define PRINTF_ERR_ENABLE			1 	/* 打印错误信息 */
#define PRINTF_INFO_ENABLE			1		/* 打印个人信息 */


#if PRINTF_DEBUG_ENABLE
#define PRINTF_DEBUG(fmt, args...) 	 do{(printf("\n[DEBUG] >> "), printf(fmt, ##args));}while(0)     
#else
#define PRINTF_DEBUG(fmt, args...)	     
#endif

#if PRINTF_ERR_ENABLE
#define PRINTF_ERR(fmt, args...) 	 do{(printf("\n[ERR] >> "), printf(fmt, ##args));}while(0)     
#else
#define PRINTF_ERR(fmt, args...)	       
#endif

#if PRINTF_INFO_ENABLE
#define PRINTF_INFO(fmt, args...) 	 do{(printf("\n[INFO] >> "), printf(fmt, ##args));}while(0)     
#else
#define PRINTF_INFO(fmt, args...)	       
#endif

/**@} */
	
//针对不同的编译器调用不同的stdint.h文件
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
#endif

/* 断言 Assert */
#define AssertCalled(char,int) 	printf("\nError:%s,%d\r\n",char,int)
#define ASSERT(x)   if((x)==0)  AssertCalled(__FILE__,__LINE__)
  
typedef enum 
{
	ASSERT_ERR = 0,								/* 错误 */
	ASSERT_SUCCESS = !ASSERT_ERR	/* 正确 */
} Assert_ErrorStatus;





#endif /* __DEBUG_H */

