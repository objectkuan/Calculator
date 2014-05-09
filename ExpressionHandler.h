#ifndef __EXPRESSIONTOKEN_HJQ__
#include "ExpressionToken.h"
#endif
#ifndef __STACK__HJQ__
#include "Stack.h"
#endif
#ifndef  __EXPRESSIONEXCEPTION_HJQ__
#include "ExpressionException.h"
#endif
#ifndef __QUEUE_HJQ__
#include "Queue.h"
#endif
#include <iostream>
#include <math.h>

#ifndef __EXPRESSIONHANDLER_HJQ__
#define __EXPRESSIONHANDLER_HJQ__

#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923

class ArithmeticException{};
class ExpressionHandler {
public:
	ExpressionHandler();
	ExpressionHandler(CString exp);
	CString calculate(CString exp) throw(ArithmeticException,StackEmptyException,TokenException);
private:
	CString exp1,exp2;
	CString convertToFormalExpression(CString exp);
	bool isInteger(double n);
	bool isInOperandBefore(wchar_t c);
	bool isAtTheEndOfOperand(wchar_t c);
	Queue<CString> convertToQueue(CString exp);
	ExpressionTokenType belongingOf(wchar_t c);
	Queue<ExpressionToken> convertToInversed(Queue<CString> l) throw(StackEmptyException,TokenException);
};

#endif
