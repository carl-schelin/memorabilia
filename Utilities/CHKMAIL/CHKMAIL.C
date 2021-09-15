/*-------------------------------------------
	CHKMAIL.C -- Check for new mail
					(c) Carl Schelin 1996
  -------------------------------------------*/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <errno.h>

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
						 LPSTR lpszCmdLine, int nCmdShow)
{
	static char	szMsg[] = "ChkMail";
	LPSTR			lpszFileOne = '\0';
	LPSTR			lpszFileTwo = '\0';
	int			j;

	lpszFileOne = lpszCmdLine;
	for (j = 0; j < lstrlen(lpszCmdLine); j++)
		if (lpszCmdLine[j] == ' ')
			{
			lpszCmdLine[j] = '\0';
			lpszFileTwo = (LPSTR)(lpszCmdLine + j + 1);
			}

	if (lpszFileOne != NULL && lpszFileTwo != NULL)
		{
		j = rename(lpszFileOne, lpszFileTwo);
		if (j != 0)
			{
			if (errno == EACCES)
				MessageBox(NULL, "Permission Denied", szMsg, MB_OK);
			else if (errno == ENOENT)
				MessageBox(NULL, "No such file or directory", szMsg, MB_OK);
			else if (errno == ENOTSAM)
				MessageBox(NULL, "Not same device", szMsg, MB_OK);
			}
		}

	return FALSE;
}
