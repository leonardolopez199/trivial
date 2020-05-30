#include "../inc/boot.h"

void boot(void)
{
	
	#ifdef _WIN32
		SetConsoleOutputCP(1252);
		SetConsoleCP(1252);
	#endif
	setlocale(LC_ALL,"");
	system("color");
	
	loadUsers();
	loadTopList();
	loadHistoryList();
	loadThemes();
	
	
	//�ltima sempre
	loadSettings();
}

static void startFileInf(FILEINF info)
{
	info.size=0;
	info.trash=0;
}

static void loadUsers(void)
{
	FILEINF info;
	startFileInf(info);
	info.size=1;
	
	USER sudo = createSUDO();
	FILE * pointer = fopen(USERS_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(USERS_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,pointer);
		writeData(&sudo,sizeof(USER),1,pointer);
		settings.totalUsers=info.size;
		settings.lastIdUsedForUser=1;
	} 
	else
	{ 
		fread(&info,sizeof(FILEINF),1,pointer);
		settings.totalUsers = info.size;		
	}
	
	fclose(pointer);
}

static USER createSUDO(void)
{
	USER sudo;	
	
	sudo.id=1;
	sudo.currentScore[0] = 0;
	sudo.currentScore[1] = 0;
	sudo.currentScore[2] = 0;
	sudo.currentScore[3] = 0; //gambiarra corrigir
	sudo.percentageCorrect = 0.0;
	sudo.userType = ADMIN_USER;
	sudo.totalAnswered = 0;
	strcpy(sudo.password,"admin");
	strcpy(sudo.username,"admin");
	strcpy(sudo.name,"SUDO");	
	
	return sudo;
}

static void loadTopList(void)
{
	FILEINF info;
	startFileInf(info);
	
	FILE * pointer = fopen(TOP_LIST_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(TOP_LIST_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,pointer);		
		settings.topSize=info.size;
	} 
	else
	{
		fread(&info,sizeof(FILEINF),1,pointer);
		settings.topSize = info.size;	
	}
	if(settings.topSize != 0)
		topPlayers = (USER *) allocateMemory(settings.topSize,sizeof(USER));
	else
		topPlayers = NULL;
		
	fclose(pointer);
}

static void loadHistoryList(void)
{
	FILEINF info;
	startFileInf(info);
	
	FILE * pointer = fopen(HISTORY_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(HISTORY_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,pointer);		
		settings.historySize=info.size;
		//settings.lastIdUsedForThema=total; //apagar
	} 
	else
	{
		fread(&info,sizeof(FILEINF),1,pointer);		
		settings.historySize = info.size;
	}
	if(settings.historySize != 0)
		historyPlayers = (USER *) allocateMemory(settings.historySize,sizeof(USER));
	else
		historyPlayers = NULL;
		
	fclose(pointer);
}

static void loadThemes(void)
{
	FILEINF info;
	startFileInf(info);
	
	FILE * pointer = fopen(THEMES_FILE_NAME, BINARY_READING);
	if(pointer == NULL)
	{
		pointer = openFile(THEMES_FILE_NAME,BINARY_WRITING);		
		writeData(&info,sizeof(FILEINF),1,pointer);		
		settings.totalThemes=info.size;
	} 
	else
	{
		readData(&info,sizeof(FILEINF),1,pointer);
		settings.totalThemes = info.size;
	}
			
	fclose(pointer);
}



static void loadSettings(void)  //deve ser a �ltima a carregar.
{
	SETTINGS setts;
	FILE * file = fopen(SETTING_FILE_NAME, BINARY_READING);
	if(file == NULL)
	{
		file = fopen(SETTING_FILE_NAME, BINARY_WRITING);	
	
		settings.totalRoundsGlobal=0;		
		settings.averageGlobalErrorAnswer=0.0;
		settings.defragRate=0.5;		
		writeData(&settings,sizeof(SETTINGS),1,file);
	}
	else
	{
		readData(&setts,sizeof(SETTINGS),1,file);
		settings.totalRoundsGlobal= setts.totalRoundsGlobal;		
		settings.averageGlobalErrorAnswer=setts.averageGlobalErrorAnswer;
		settings.defragRate=setts.defragRate;
	}
	fclose(file);
}




