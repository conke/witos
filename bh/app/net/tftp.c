#include <getopt.h>
#include <sysconf.h>
#include <net/tftp.h>

static void usage(int argc, char *argv)
{
#if 0

Usage: tftp <command> [<args>]

command list:
	get         download file
    put         upload file

See 'disk <command> -h' for more information on a specific command.

generic options:
	-r <URL>     remote URL, i.e. "10.0.0.2:69/g-bios-bh.bin".
	-l <path>    local path.
	-m <mode>    transfer mode: text or binary (default is binary).
    -v           verbose.
    -h           this help

<get> options:
    -a <addr>    only load to the memory address <addr>,
                 without writing to stoarge.

#endif

	printf("Usage: tftp [option <value>] [-f] <filename>\n"
		"\noptions:\n"
		"  -a   \tmemory address [needed in few cases]\n"
		"  -m   \tonly download to memory, without writing to storage\n"
		"  -f   \tfile name for download\n"
		"  -s   \ttftp server ip\n"
		"  -h   \tthis help\n");
}

int main(int argc, char *argv[])
{
	int ret, ch;
	struct tftp_opt dlopt;
	BOOL mem_only = FALSE;
	int opt_idx;

	memset(&dlopt, 0x0, sizeof(dlopt));
	net_get_server_ip(&dlopt.server_ip);

	while ((ch = getopt(argc, argv, "a:ms:f:")) != -1)
	{
		switch(ch)
		{
		case 'a':
			ret = string2value(optarg, (u32 *)&dlopt.load_addr);

			if (ret < 0)
			{
				usage(argc, argv);
				return ret;
			}

			break;

		case 'm':
			mem_only = TRUE;
			break;

		case 's':
			ret = str_to_ip((u8 *)&dlopt.server_ip, optarg);
			if (ret < 0)
			{
				printf("Invalid IP: %s!\n", optarg);
				return ret;
			}
			break;

		case 'f':
			strncpy(dlopt.file_name, optarg, MAX_FILE_NAME_LEN);
			dlopt.file_name[MAX_FILE_NAME_LEN - 1] = '\0';
			break;

		case 'h':
		default:
			usage(argc, argv);
			return -EINVAL;
		}
	}

	if (FALSE == mem_only)
	{
	}

	opt_idx = getopt_idx();

	if (opt_idx < argc)
	{
		if (opt_idx + 1 == argc && !dlopt.file_name[0])
		{
			strncpy(dlopt.file_name, argv[opt_idx], MAX_FILE_NAME_LEN);
			dlopt.file_name[MAX_FILE_NAME_LEN - 1] = '\0';
		}
		else
		{
			usage(argc, argv);
			return -EINVAL;
		}
	}

	if (!dlopt.file_name[0])
	{
	}

	ret = net_tftp_load(&dlopt);

	if (FALSE == mem_only)
	{
		if (ret > 0)
		{
			sysconf_save();
		}
	}

	return ret;
}

