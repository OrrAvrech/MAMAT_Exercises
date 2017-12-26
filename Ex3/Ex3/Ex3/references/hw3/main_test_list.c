//#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
	typedef struct _BOOK
	{

		char szCode[11];
		char* pszTitle;
	} BOOK, *PBOOK;

	void destroyBook(PElem pElem)
	{
		PBOOK pBook = (PBOOK)pElem;
		free(pBook->pszTitle);
		free(pBook);

	}

	PElem cloneBook(PElem pElem)
	{
		PBOOK pBook = (PBOOK)pElem;

		PBOOK pNewBook;
		if ((pNewBook = (PBOOK)malloc(sizeof(BOOK))) == NULL)
		{
			return NULL;
		}

		((pNewBook->pszTitle = (char*)malloc(sizeof(char) * 20)));

		int i;
		for (i = 0; i < 11; i++)
		{
			pNewBook->szCode[i] = 0;
		}



		strcpy(pNewBook->pszTitle, pBook->pszTitle);
		strncpy(pBook->szCode, pNewBook->szCode, 11);

		return (PElem)pNewBook;
	}

	PBOOK CreateBook(char* szTitle, char* szCode) {
		PBOOK pBook;
		if ((pBook = (PBOOK)malloc(sizeof(BOOK))))
		{
			strcpy(pBook->szCode, szCode);
			if (!(pBook->pszTitle = (char*)malloc(1 + strlen(szTitle)))) {
				free(pBook);
				return NULL;
			}
			strcpy(pBook->pszTitle, szTitle);
		}
		return pBook;
	}




	int main()
	{

		PList PBookList = ListCreate(cloneBook, destroyBook);

		PBOOK FirstBook = CreateBook("Harry Potter 13", "ABC-24U-QA");
		PBOOK SecondBook = CreateBook("Intro to C", "ABC-34W-YT");
		PBOOK ThirdBook = CreateBook("Intro to C++", "AAA-34W-YT");
		PBOOK ForthBook = CreateBook("Intro to Csharp", "vvv-34W-YT");


		Result fOrS1 = ListAdd(PBookList, FirstBook);
		Result fOrS2 = ListAdd(PBookList, SecondBook);
		Result fOrS3 = ListAdd(PBookList, ThirdBook);
		Result fOrS4 = ListAdd(PBookList, ForthBook);


		PBOOK thisIsTheForth = ListGetFirst(PBookList);
		Result resofRemove1 = ListRemove(PBookList);
		thisIsTheForth = ListGetFirst(PBookList);
		PBOOK thisIsTheThird = ListGetNext(PBookList);
		Result resofRemove2 = ListRemove(PBookList);
		thisIsTheForth = ListGetFirst(PBookList);
		PBOOK thisIsTheSecond = ListGetNext(PBookList);
		Result resofRemove3 = ListRemove(PBookList);
		PBOOK thisIsTheFirst = ListGetFirst(PBookList);
		Result resofRemove4 = ListRemove(PBookList);
		
		

		int size = ListGetSize(PBookList);

		ListDestroy(PBookList);

		destroyBook(FirstBook);
		destroyBook(SecondBook);
		destroyBook(ThirdBook);
		destroyBook(ForthBook);

		return 0;

	}