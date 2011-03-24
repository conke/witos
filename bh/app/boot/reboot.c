#include <g-bios.h>

__WEAK__ void reboot(void);

int main(int argc, char *argv[])
{
	if (reboot)
		reboot();

	printf("reboot not supported!\n");

	return -EFAULT;
}
