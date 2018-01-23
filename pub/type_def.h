
#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

/* Definition for tpyes */
typedef unsigned char         uint8;       
typedef unsigned short int    uint16;      
typedef unsigned int          uint32;      

typedef signed char           int8;        
typedef signed short int      int16;       
typedef signed int            int32;       

#ifndef BIT
#define BIT(x)	(1 << (x))
#endif

#ifndef NULL
#define NULL              		(0)         /* Value for NULL pointer */
#endif
	
#ifndef TRUE
#define TRUE					(1)
#endif

#ifndef FALSE
#define FALSE					(0)
#endif

#endif /* _TYPE_DEF_H_ */

/* End of file */

