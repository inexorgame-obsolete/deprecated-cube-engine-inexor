// versioncontrol.cpp: control the management of map versioning, merging and branching

#include "inexor/versioncontrol/versioncontrol.h"

#define VERSION_CONTROL_COMMANDS_ARE "Version control commands are: \fs\f2help commit diff merge pull push log\fr"

void help(tagval *args, int numargs)
{
	if (numargs == 0)
	{
		conoutf(CON_INFO, VERSION_CONTROL_COMMANDS_ARE);
		conoutf(CON_INFO, "Type \fs\f2/vc help <command>\fr to find out more about a specific command.");
	}
	else
	{
		if (!strcmp(args[0].getstr(), "help"))
			conoutf(CON_INFO, "Type \fs\f2/vc help <command>\fr to find out more about a specific command.");
		else if (!strcmp(args[0].getstr(), "commit"))
			conoutf(CON_INFO, "Info about the commit command");
		else if (!strcmp(args[0].getstr(), "diff"))
			conoutf(CON_INFO, "Info about the diff command");
		else if (!strcmp(args[0].getstr(), "merge"))
			conoutf(CON_INFO, "Info about the diff command");
		else if (!strcmp(args[0].getstr(), "pull"))
			conoutf(CON_INFO, "Info about the pull command");
		else if (!strcmp(args[0].getstr(), "push"))
			conoutf(CON_INFO, "Info about the push command");
		else if (!strcmp(args[0].getstr(), "log"))
			conoutf(CON_INFO, "Info about the log command");
		else
			conoutf(CON_INFO, VERSION_CONTROL_COMMANDS_ARE);
	}
}

void commit(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc commit");
	vc_commit();
}

void diff(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc diff");
	vc_diff();
}

void merge(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc merge");
}

void pull(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc pull");
}

void push(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc push");
}

void log(tagval *args, int numargs)
{
	conoutf(CON_INFO, "vc log");
}

ICOMMAND(vc, "V", (tagval *args, int numargs),
{
	if (!editmode) conoutf(CON_INFO, "You need to be in edit mode to use version control.");
	else
	{
		if (numargs == 0) conoutf(CON_INFO, VERSION_CONTROL_COMMANDS_ARE);
		else if (!strcmp(args[0].getstr(), "help"))   help(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "commit")) commit(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "diff"))   diff(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "merge"))  merge(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "pull"))   pull(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "push"))   push(args++, numargs--);
		else if (!strcmp(args[0].getstr(), "log"))    log(args++, numargs--);
		else conoutf(CON_INFO, "Version control command \fs\f3%s\fr not found.", args[0].getstr());
	}
});
