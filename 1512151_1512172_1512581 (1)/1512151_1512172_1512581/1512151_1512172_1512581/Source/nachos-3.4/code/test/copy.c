#include "syscall.h"
#define MAX 20
int main()
{	
	char buf[MAX+1];
	char filenameSource[MAX+1], filenameDest[MAX+1];
	OpenFileId ids, idd;//id source, id dest
	int stat, l1, l2, i;
	int stop;
	PrintString("Nhap ten file nguon (vi du: da2.source): ");
	l1 = Read(filenameSource, MAX, 0);
	PrintString("Nhap ten file dich (vi du: da2.dest): ");
	l2 = Read(filenameDest, MAX, 0);
	ids = Open(filenameSource, 1);//read only
	
	if (l1 == 0 || l2 == 0) {
		PrintString("Chua nhap dest hoac source\n");
	} else if (l1 == l2) {
		stop = 1;
		for (i = 0; i <= l2; i++)
			if (filenameSource[i] != filenameDest[i]) {
				stop = 0;
				break;
			}
		if (stop == 1) {
			PrintString("Khong the thuc hien\n");
			Halt();
		}
	}
	
	if (ids != -1) {
		stat = CreateFile(filenameDest);
		if (stat == -1) {
			PrintString("Khong tao file moi duoc");
			Halt();
		}
		idd = Open(filenameDest, 0);
		do {
			stat = Read(buf, MAX, ids);
			if (stat <= 0)
				break;
			Write(buf, stat, idd);
			buf[0] = '\0';
		} while (1);
		PrintString("Da copy xong.\n");
		CloseFile(idd);CloseFile(ids);
	} else
		PrintString("Khong mo duoc file!");
	Exit(0);
}
