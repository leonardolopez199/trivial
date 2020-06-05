#include "../inc/view.h"

	/*Player*/
CONTROLINT rendersMainMenu(void)
{
	CONTROLINT choice;
	char mainMenu[][MAX_OPTION_MENU_SIZE]={"1 - JOGAR","2 - CADASTRAR USU�RIO", "3 - TOP 10", "4 - HIST�RICO", "5 - MINHA CONTA", "0 - SAIR"};
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("MENU PRINCIPAL",mainMenu,TOTAL_OPTION_MAIN_MENU);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,0,5,CLOSED_RANGE));
	
	
	return choice;
}


CONTROLINT rendersGetGameMode(void)
{
	CONTROLINT choice;
	char menuGameMode[][MAX_OPTION_MENU_SIZE]={"1 - PEQUENO (4 perguntas)", "2 - M�DIO (8 perguntas)", "3 - GRANDE (16 perguntas)"};
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("MODO DE JOGO",menuGameMode,3);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,3,CLOSED_RANGE));
	
	return choice;
}

CONTROLINT rendersGetTotalPlayers(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("TOTAL DE JOGADORES","O jogo suporta de 2 a 6 jogadores. Com quantos amigos gostaria de se divertir?","Pressione o n�mero de jogadores para continuar..",STANDARD_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,2,6,CLOSED_RANGE));
	
	return choice;
}

void rendersMaxAttempts(void)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ALERTA","Voc� atingiu o m�ximo de tentativas. N�o � poss�vel continuar tentando.","Pressione qualquer tecla para retornar ao menu principal...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

CONTROLINT rendersInvalidUsername(CONTROLINT attempts)
{
	CONTROLINT choice;
	//pode colocar qual � a tentativa atual (n�mero) na mensagem.
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("USU�RIO INV�LIDO","O usu�rio informado n�o foi encontrado em nossa base de dados. Voc� pode tentar novamente ou simplesmente se cadastrar agora.","Pressione [1] para se cadastrar ou [2] para tentar novamente.",STANDARD_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}

void rendersInvalidPassword(CONTROLINT attempts)
{
	//pode colocar qual � a tentativa atual (n�mero) na mensagem.
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("SENHA INV�LIDA","A senha informada n�o corresponde com a cadastrada. Voc� ainda pode tentar outra vez.","Pressione qualquer tecla para tentar novamente...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

void rendersGetUsername(char * username)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe o seu nome de usu�rio.","Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USER_NAME_SIZE,username);
}

void rendersGetPassword(char * password)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("LOGIN","Informe a palavra passe do seu usu�rio.","Password:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	catchPassword(password,MAX_PASSWD_SIZE);
}

CONTROLINT rendersGetTheme(char themesName[][MAX_SIZE_THEME_NAME],const CONTROLINT totalThemes)
{
	CONTROLINT i, choice;
	char listaThemes[totalThemes][MAX_OPTION_MENU_SIZE];
	
	for(i=0;i<settings.totalThemes;i++)
		sprintf(listaThemes[i],"%d - %s",i+1,themesName[i]);
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	menuBox("TEMAS",listaThemes,totalThemes);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,totalThemes,CLOSED_RANGE));
	
	
	return choice;
}

CONTROLINT rendersGetAnswer(QUESTION mountedQuestion, USER player, CONTROLINT gameMode)
{
	CONTROLINT choice;	
	
	clearScreen();
	placarBox(player, gameMode);
	verticalPadding(VERTICAL_PADDING_STANDARD);
	cardFrame(mountedQuestion.title,mountedQuestion.answers);
	putchar('\n');
	simpleInstructionBox("Pressione o n�mero correspondente a resposta correta.",STANDARD_BOX);
	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,4,CLOSED_RANGE) );
	
	return choice;
}

void rendersResultQuestion(QUESTION mountedQuestion, CONTROLINT choice, CONTROLINT correct)
{
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	cardFrameContrast(mountedQuestion.title,mountedQuestion.answers,correct,choice);
	putchar('\n');
	simpleInstructionBox("Pressione qualquer tecla para continar...",STANDARD_BOX);

	wait();	
}

/*Register*/
void rendersGetNameForRegister(char * name)
{
	char message[100];
	sprintf(message,"Informe o seu nome com at� %d letras.",MAX_NAME_SIZE);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,1,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Nome:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,29,STANDARD_BOX);
	getString(MAX_NAME_SIZE-1,name);	
}

void rendersGetUsernameForRegister(char * username)
{
	char message[150];
	sprintf(message,"Informe o seu 'username' com at� %d letras. Ele deve ser �nico e sera usado para se logar no sistema.",MAX_USER_NAME_SIZE);
	clearScreen();	
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Username:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_USER_NAME_SIZE-1,username);	
}

void rendersGetNickname(char * nickname)
{
	char message[150];
	sprintf(message,"Informe o seu 'nickname' com at� %d letras. Ele deve ser �nico. � atrav�s dele que voc� ser� reconhecido por todos.",MAX_NICKNAME_SIZE);
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,3,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE USU�RIO",message,"Nickname:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_NICKNAME_SIZE-1,nickname);	
}

void rendersGetPasswordForRegister(char * password, CONTROLINT attempt)
{
	char message[150];

	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,5,4,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	if(attempt == GET_PASSWORD)
	{
		sprintf(message,"Informe a sua 'password'. Ela deve ter exatamente %d caracteres. S�o aceitos letras, n�meros e caracteres especiais.",MAX_PASSWD_SIZE-1);		
	}
	else
	{
		strcpy(message,"Digite novamente a sua 'password' para que possamos ter a certeza que a digitou corretamente.");		
	}
	instructionBox("CADASTRO DE USU�RIO",message,"Password:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	catchPassword(password,MAX_PASSWD_SIZE);
}

CONTROLINT rendersFullRegister(USER temporaryUser)
{
	CONTROLINT choice;
	char listaTempUser[3][100];
	char title[100] = "Valide a informa��o do cadastro.";
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX,5,5,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	//Imprime os dados do usu?rio	
	
	sprintf(listaTempUser[0],"Nome: %s",temporaryUser.name);
	sprintf(listaTempUser[1],"Username: %s",temporaryUser.username);
	sprintf(listaTempUser[2],"Nickname: %s",temporaryUser.nickname);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"DADOS DO CADASTRO", TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','*',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);	
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT, listaTempUser[0], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT,listaTempUser[1], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineBuilder(' ',' ',' ',PADDING_INTERNAL,PADDING_NULL,STANDARD_BOX_SIZE,ALIGN_LEFT,listaTempUser[2], TEXT_STANDARD, BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD, BAKGROUND_STANDARD);
	putchar('\n');	

	//Imprime os dados do usu�rio
	instructionBox("CADASTRO DE USU�RIO","Verifique se todos os dados est�o corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,2,CLOSED_RANGE) );
	
	return choice;
}

CONTROLINT rendersPasswordsDoNotMatch(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("PASSWORD N�O COINCIDE","As passwords informadas n�o s�o iguais. Voc� pode tentar redigit�-las ou simplesmente desistir do seu cadastro.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;	
}

CONTROLINT rendersInvalidNickname(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("NICKNAME N�O DISPON�VEL","O 'nickname' informado j� est� sendo utilizado por outro usu�rio. Escolha outro apelido para lhe representar.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}

CONTROLINT rendersUsernameAlreadyExists(void)
{
	CONTROLINT choice;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("USERNAME N�O DISPON�VEL","O 'username' informado j� est� sendo utilizado por outro usu�rio. Escolha outro nome de acesso ao sistema.","Pressione [1] para tentar novamente ou [2] para desistir.",ERROR_BOX,INSTRUCTION_BOX);
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,REGISTER_USER,2,CLOSED_RANGE));
	
	return choice;
}


void rendersDesistRegistering(void)
{	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("ALERTA","Voc� desistiu do seu registro de usu�rio. Dever� tentar se logar outra vez.","Pressione qualquer tecla para tentar logar novamente...",ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

/* ADM */

void rendersGetQuestionTitle(char * title)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,1,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe o t�tulo da pergunta, ou seja, a pergunta propriamente dita.","T�tulo:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,32,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,title);	
}

void rendersGetQuestionRightAnswer(char * correctAnswer)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,2,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe a resposta CORRETA para a quest�o anteriormente inserida.","Resposta CORRETA:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,42,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,correctAnswer);	
}

void rendersGetQuestionAnswer(char * answer, CONTROLINT progressBarPosition)
{		
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,progressBarPosition,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);
	instructionBox("CADASTRO DE PERGUNTA","Informe outra op��o de resposta para a quest�o anteriormente inserida.","Resposta:",STANDARD_BOX,QUESTION_BOX);
	positionCursor(2,34,STANDARD_BOX);
	getString(MAX_TITLE_SIZE,answer);	
}

CONTROLINT rendersConfirmationQuestion(QUESTION question)
{
	CONTROLINT choice;	
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	cardFrame(question.title,question.answers);
	putchar('\n');
	
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	progressBar(STANDARD_BOX_SIZE,6,6,BAKGROUND_COMPLETED,BAKGROUND_NOT_COMPLETED);	
	
	instructionBox("CADASTRO DE PERGUNTA","Verifique se todos os dados est�o corretos.","Pressione [1] para reiniciar o cadastro ou [2] para confirmar.",STANDARD_BOX,INSTRUCTION_BOX);	
	do
	{
		choice = getChoiceMenu();
	}
	while(!inRange(choice,1,RECORD_QUESTION,CLOSED_RANGE) );
	
	return choice;
}



/*History*/

void rendersHistory(NODE ** history)
{
	char messageEmptyList[] = "Infelizmente nenhum jogador ainda se aventurou no fant�stico mundo do TRIVIAL. Que tal voc� come�ar esta proeza!?";
	char * userLine = (char * ) allocateMemory(MAX_NICKNAME_SIZE+10,sizeof(char));
	USER temporaryUser; //apagar casou use o vetor de users
	//USER * playerList = (USER *) allocateMemory(settings.historySize,sizeof(USER));
	CONTROLINT i;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	/*header*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"HIST�RICO",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"| Listagem dos �ltimos 15 jogadores |",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*content*/
	if(settings.historySize > 0)
	{
		
		for(i=0;i<settings.historySize;i++)
		{
			/*
			historyForPrint(historyPlayers,playerList,settings.historySize);
			sprintf(userLine,"%d - %s",i+1,playerList[i].nickname);	
			*/
			temporaryUser = returnsLastPlayersOneByOne(history);	
			sprintf(userLine,"%d - %s",i+1,temporaryUser.nickname);				
			alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
			lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_LEFT,userLine,TEXT_STANDARD,BAKGROUND_STANDARD);
		}		
	}
	else
	{
		alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
		emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
		textFrame(' ',PADDING_INTERNAL,STANDARD_BOX_SIZE,ALIGN_CENTER,ALIGN_CENTER, messageEmptyList,TEXT_STANDARD,BAKGROUND_STANDARD);
	}
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
			
	/*footer*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"Pressione qualquer tecla para retornar ao menu principal...",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	wait();
}

void redersHistoryFatalError(void)

{
	char message[] = "Algo terr�vel aconteceu durante o carregamento do programa que impediu a inicializa��o do hist�rico de jogadores. Tente reinstalar o jogo, caso isto n�o funcione contate o suporte. O TRIVIAL precisa ser encerrado, lamentamos este inconveniente.";
	char instruction[] = "Pressione qualquer tecla para finalizar o programa.";
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("FALHA AO CARREGAR HIST�RICO",message,instruction,ERROR_BOX,INSTRUCTION_BOX);
	wait();
}

/*Top 10*/
	
void redersTop10FatalError(void)
{
	char message[] = "Algo terr�vel aconteceu durante o carregamento do programa que impediu a inicializa��o da lista dos 10 melhores jogadores. Tente reinstalar o jogo, caso isto n�o funcione contate o suporte. O TRIVIAL precisa ser encerrado, lamentamos este inconveniente.";
	char instruction[] = "Pressione qualquer tecla para finalizar o programa.";
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	instructionBox("FALHA AO CARREGAR HIST�RICO",message,instruction,ERROR_BOX,INSTRUCTION_BOX);
	wait();
	
}

void rendersTopPlayers(NODE ** bestPlayers)
{
	char messageEmptyList[] = "Infelizmente nenhum jogador ainda se aventurou no fant�stico mundo do TRIVIAL. Que tal voc� come�ar esta proeza!?";
	char templates[] = "%d� - %s  com %2.f %% de acertos";
	char * userLine = (char * ) allocateMemory(MAX_NICKNAME_SIZE+strlen(templates)+2,sizeof(char));
	USER temporaryUser;
	CONTROLINT i;
	
	clearScreen();
	verticalPadding(VERTICAL_PADDING_STANDARD);
	
	/*header*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"MELHORES JOGADORES",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"| Listagem dos 10 melhores jogadores de todos os tempos |",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	
	/*content*/
	if(settings.topSize > 0)
	{
		
		for(i=0;i<settings.historySize;i++)
		{
			temporaryUser = returnsTopPlayersOneByOne(bestPlayers);	
			sprintf(userLine,templates,i+1,temporaryUser.nickname,temporaryUser.percentageCorrect);				
			alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
			lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_LEFT,userLine,TEXT_STANDARD,BAKGROUND_STANDARD);
		}		
	}
	else
	{
		alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
		emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
		textFrame(' ',PADDING_INTERNAL,STANDARD_BOX_SIZE,ALIGN_CENTER,ALIGN_CENTER, messageEmptyList,TEXT_STANDARD,BAKGROUND_STANDARD);
	}
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
			
	/*footer*/
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	bottomLine(' ','-',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	lineTitle(' ',' ',STANDARD_BOX_SIZE,ALIGN_CENTER,"Pressione qualquer tecla para retornar ao menu principal...",TEXT_STANDARD,BAKGROUND_STANDARD);
	alignmentPadding(STANDARD_BOX_SIZE,ALIGN_CENTER);
	emptyLine(' ',STANDARD_BOX_SIZE,TEXT_STANDARD,BAKGROUND_STANDARD);
	wait();
}
