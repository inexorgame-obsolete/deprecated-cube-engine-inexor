// versioncontrol.cpp: control the management of map versioning, merging and branching

#include "inexor/versioncontrol/versioncontrol.h"

#define NUM_VC_CMDS 4

const char * vc_commands[NUM_VC_CMDS] = { "snap", "commit", "pull", "push" };

void vc_snap(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc_snap");
}

void vc_commit(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc_commit");
}

void vc_pull(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc_pull");
}

void vc_push(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc_push");
}

ICOMMAND(vc, "V", (tagval *args, int numargs),
{
	if (editmode)
	{
		if (numargs == 0)
		{
			const char *str = "";
			loopi(NUM_VC_CMDS)
				str = tempformatstring((i == NUM_VC_CMDS -1) ? "%s\fs\f3%s\fr" : "%s\fs\f3%s\fr, ", str, vc_commands[i]);

			conoutf(CON_INFO, "Version control commands are: %s", str);
		}
		else if (!strcmp(args[0].getstr(), "snap")) vc_snap(args, numargs);
		else if (!strcmp(args[0].getstr(), "commit")) vc_commit(args, numargs);
		else if (!strcmp(args[0].getstr(), "pull")) vc_pull(args, numargs);
		else if (!strcmp(args[0].getstr(), "push")) vc_push(args, numargs);
		else conoutf(CON_INFO, "Version control command \fs\f3%s\fr not found.", args[0].getstr());
	}
	else conoutf(CON_INFO, "You need to be in edit mode to use version control.");
});