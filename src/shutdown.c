#include "../inc/shutdown.h"

void turnOff()
{
	saveSettings();
	quitTopList();
	quitHistoryList();	
}

static void quitTopList(void)
{
	deleteList(topPlayers);
}

static void quitHistoryList(void)
{	
	deleteQueue(historyPlayers);
}

void saveSettings(void)
{
	FILE * file = openFile(SETTING_FILE_NAME,BINARY_WRITING);
	
	writeData(&settings,sizeof(SETTINGS),1,file);	
	fclose(file);
}
