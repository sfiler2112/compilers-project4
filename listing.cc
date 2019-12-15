// Compiler Theory and Design
// Dr. Duane J. Jarc

// This file contains the bodies of the functions that produces the compilation
// listing

// Edited by Sean Filer on 12/13/2019

#include <cstdio>
#include <string>
#include <queue>

using namespace std;

#include "listing.h"

static int lineNumber;
static string error = "";
static int totalErrors = 0;
static int lexicalErrors = 0;
static int semanticErrors = 0;
static int syntacticErrors = 0;

static std:: queue<string> errorQueue;

static void displayErrors();

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine()
{
	printf("\r");
	displayErrors();
	printf("     \n");
	if(totalErrors == 0){
		printf("Compiled Successfully!");
	} else {
		printf("Total errors: %d\n", totalErrors);
		printf("Lexical errors: %d\n", lexicalErrors);
		printf("Syntactic errors: %d\n", syntacticErrors);
		printf("Semantic errors: %d\n", semanticErrors);
	}
	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate Identifier: ",
		"Semantic Error, Undeclared " };

	error = messages[errorCategory] + message;
	switch(errorCategory){
		case LEXICAL:
			lexicalErrors++;
			break;
		case SYNTAX:
			syntacticErrors++;
			break;
		case GENERAL_SEMANTIC:
			semanticErrors++;
			break;
		case DUPLICATE_IDENTIFIER:
			semanticErrors++;
			break;
		default:
			break;
	}
	errorQueue.push(error);
	totalErrors++;
}

void displayErrors()
{
	error = "";
	while(!errorQueue.empty()){
		error = errorQueue.front();
		errorQueue.pop();
		printf("%s\n", error.c_str());
	}
}
