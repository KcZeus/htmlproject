/*
 ============================================================================
 Name        : p.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getCount(char *);
void getTag(char *);
void getUrl(char *);
void countFreq(char *);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char line[BUFSIZ + 1];
	char curl[BUFSIZ + 1];
	char htmlSource[256 * 1024];
	char usrIn[BUFSIZ + 1];
	//"http://wfs.sbcc.edu/staff/nfguebels/web/cs137/html_src_list/simple.html"
	FILE* fpCurl;

	strcpy(curl, " curl -s "); // appends (curl -s) to the front of the array curl
	printf("URL:\n");
	gets(line);
	strcat(curl, line);
	fpCurl = popen(curl, "r");
	htmlSource[0] = '\0';
	while (fgets(line, BUFSIZ, fpCurl) != NULL) { // grabs each individual line of html while fgets is reading something
		strcat(htmlSource, line);
	}

	while (usrIn[0] != 'q') {
		printf("Ready\n");
		fgets(usrIn, BUFSIZ, stdin);

		switch (usrIn[0]) {
		case 'c':
			printf("%d\n", getCount(htmlSource));
			break;
		case 't':
			getTag(htmlSource);
			break;

		case 'f':
			countFreq(htmlSource);
			break;

		case 'u':
			getUrl(htmlSource);
			break;
		case 'q':
			//user input q --> quits loop
			break;
		}
	}
	pclose(fpCurl);
	printf("Complete\n");
	return (0);
}
//function that counts the number of source attributes
int getCount(char* html) {

	int count = 0;
	char* cp = html;

	while ((cp = strstr(++cp, "src=\"")) != NULL) { //count the whitespaces---> number of source attributes
		if (isspace(*(cp - 1)))
			count++;
	}
	return count;
}
//function that finds all of the tags
void getTag(char *html) {

	char *pSrc = html;
	char tag[BUFSIZ + 1];
	char *ptagend, *ptag;

	while ((pSrc = strstr(++pSrc, "src=\"")) != NULL) {
		if (isspace(*(pSrc - 1))) {
			ptag = pSrc;

			while (*ptag != '<')
				ptag--;
			ptag++;
			ptagend = ptag;
			while (!isspace(*ptagend))
				ptagend++;
			strncpy(tag, ptag, ptagend - ptag);
			tag[ptagend - ptag] = '\0';
			printf("%s\n", tag);

		}
	}
}
// function that finds all of the URLs
void getUrl(char *html) {
	char url[BUFSIZ + 1];
	char *pUrlend, *pUrl;
	char *pSrc = html;

	while ((pSrc = strstr(++pSrc, "src=\"")) != NULL) {
		if (isspace(*(pSrc - 1))) {
			pUrl = pSrc;

			while (*pUrl != '\"') // while pointer isn't quote character move the pointer up
				pUrl++;

			pUrl++;
			pUrlend = pUrl;

			while (*pUrlend != '\"') // while pointer isn't quote character move the pointer up
				pUrlend++;

			strncpy(url, pUrl, pUrlend - pUrl);
			url[pUrlend - pUrl] = '\0';
			printf("%s\n", url);

		}
	}
}

/*
 * function that takes in a pointer of the first given word and returns number of reoccurance.
 */

void countFreq(char *html) {
	/*
	 * finding all the tags...easier to copy and paste than call the function in this case
	 */
	char *pSrc = html;
	char tag[BUFSIZ + 1];
	char *ptagend, *ptag;

	while ((pSrc = strstr(++pSrc, "src=\"")) != NULL) {
		if (isspace(*(pSrc - 1))) {
			ptag = pSrc;

			while (*ptag != '<')
				ptag--;
			ptag++;
			ptagend = ptag;
			while (!isspace(*ptagend))
				ptagend++;
			strncpy(tag, ptag, ptagend - ptag);
			tag[ptagend - ptag] = '\0';
			printf("%s\n", tag); //all the tags are in the array ((tag))
		}
	}

	int count = 0;
	int i;
	char tag[i];

	if (html != NULL) {
		for (i = 0; i <= 2; i++) {
			html = tag[i];
			while (html = strstr(html, tag[i])) {
				count++;
				i++;
				printf("%s\t%d", *html, count);
			}
		}
		printf("%s\t%d", *html, count);
	}
}
