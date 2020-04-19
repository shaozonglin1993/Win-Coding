#ifndef _TYPE_CONVERSION_H
#define _TYPE_CONVERSION_H

/*static_cast*/
void staticCast(void);

/*reinterpret_cast*/
typedef void (* FUNC)(void);
void reinterpretCast(void);

/*const_cast*/
void constCast(void);
void constCastTest1(void);
void constCastTest2(void);

/*dynamic_cast*/
void dynamicCast(void);

/*explicit¹Ø¼ü×Ö*/
void ExplicitTest(void);


#endif	/*end of file*/