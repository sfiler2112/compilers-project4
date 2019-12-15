// Compiler Theory and Design
// Duane J. Jarc

// This file contains the bodies of the type checking functions

// Edited by Sean Filer on 12/13/2019

#include <string>
#include <vector>
#include <cstdio>

using namespace std;

#include "types.h"
#include "listing.h"

void checkAssignment(Types lValue, Types rValue, string message)
{
	if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
	{
		if(lValue == INT_TYPE && rValue == REAL_TYPE)
		{
			appendError(GENERAL_SEMANTIC, "Illegal Narrowing " + message);
		} else if (lValue != REAL_TYPE && rValue != INT_TYPE) {
			appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
		}
	}
}

Types checkArithmetic(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == BOOL_TYPE || right == BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Numeric Type Required");
		return MISMATCH;
	}
	if (left == REAL_TYPE || right == REAL_TYPE)
	{
		printf("\nconverting arithmetic expression to real type! \n");
		return REAL_TYPE;
	} else {
		return INT_TYPE;
	}
}


Types checkLogical(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left != BOOL_TYPE || right != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required");
		return MISMATCH;
	}	
		return BOOL_TYPE;
	return MISMATCH;
}

Types checkRelational(Types left, Types right)
{
	if (checkArithmetic(left, right) == MISMATCH)
		return MISMATCH;
	return BOOL_TYPE;
}

Types checkRemainder(Types left, Types right)
{
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left != INT_TYPE || right != INT_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Integer Type Required For Remainder Operator");
		return MISMATCH;
	}	
		return INT_TYPE;
	return MISMATCH;
}

Types checkIfStatement(Types condition, Types thenType, Types elseType)
{
	if(condition == MISMATCH)
		return MISMATCH;
	if(condition != BOOL_TYPE)
	{
		appendError(GENERAL_SEMANTIC, "Boolean Type Required For If Condition");
		return MISMATCH;
	}
	
	if(thenType != elseType)
	{
		appendError(GENERAL_SEMANTIC, "If Statements Require Matching Types");
		return MISMATCH;
	}
		return thenType;
		
	return MISMATCH;
}
