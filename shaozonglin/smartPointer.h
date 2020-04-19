#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

void SharedSmartPointer(void);
void uniqueSmartPointer(void);
void WeakSmartPointer(void);

class Child;
class Parent;
void ReferenceLoop(void);

template<typename T>
class SmartPointer;
void SmartPointerDemo(void);

#endif	/*end of file*/