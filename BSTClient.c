 //Sidney Robinson
//simrobin 1643731
//CMPS12B/M
//---------------------------------------------------------------------
// BSTClient.c
// Input oriented Test client for Binary Search Tree ADT
// see file BSTUI.h for definition of commands and acceptable input details.
// 
//---------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "BST.h"
#include "BSTUI.h"		


/******************  function prototypes  *****************************/

void doQuit();
void showHelp();
void doErase( BSTObj **ptrT);
void doHeight( BSTObj *T);
void doHeight();
void doInsert(BSTObj **ptrT, char *arg);
void doPrint(BSTObj *T, char *order);
void doFind(BSTObj *T, char *term);
void doDelete(char* term, BSTObj**T);
int inputLengthOK(char *inputStr);

/*
 * parseInput 
 *    Processes the text string input and divides the input into words that are 
 *    returned on w1, w2, w3
 *    This supports commands that have at most one argument:
 *    return the command in w1, first argument in w2, w3 for trailing junk
 *
 *    Return value indicates the outcome of parsing. Could be OK result which is command that
 *    was detected, e.g.
 *	  CMD_HELP
 *    of it could be an error was detected, e.g.
 *	  NO_ARGS_NEEDED	  
 *
 */
int parseInput(char *input, char *w1, char *w2, char *w3){
    int	    numArgs;

    /*
     * take the raw input string and read the contents to determine the action
     * fill in the argument if the command requires one.
     */
    
    // break the request up into words separated by whitespace
 
    numArgs = sscanf(input, "%s %s %s", w1, w2, w3);
    //printf("numArg = %d from sscanf w1 = %s, w2= %s, w3= %s\n",numArgs, w1, w2, w3);

	//constant if cases for checking what to call and return within the function, All commands explained in BSTUI.h
    if (numArgs == EOF ) {
	// no words, tell the user they can get help
        return CMD_NONE;
    }

    if (numArgs == 0 ) {
	// no words, tell the user they can get help
        return CMD_NONE;
    }
  
    if (strcasecmp(CMD_HELP_STR, w1) == 0) {
        if (numArgs > 1) {
	    return NO_ARGS_NEEDED;
        }
        else {
	    return(CMD_HELP);
        }
    }

    if (strcasecmp(CMD_ERASE_STR, w1) == 0) {
	if(numArgs > 1)
	{
		return NO_ARGS_NEEDED;
	}
	else
	{
		return(CMD_ERASE);
	}
    }
	

    if (strcasecmp(CMD_QUIT_STR, w1) == 0) {
	if(numArgs > 1)
	{
		return NO_ARGS_NEEDED;
	}
	else
	{
		return(CMD_QUIT);
	}
    }

    if (strcasecmp(CMD_HEIGHT_STR, w1) == 0) {
	if (numArgs >1)
	{
		return NO_ARGS_NEEDED;
	}
	else
	{
		return(CMD_HEIGHT);
	}
    }
    
    if (strcasecmp(CMD_INSERT_STR, w1) == 0) {
		if (numArgs >2)
	{
		return (EXTRA_ARG);
	}
		if (numArgs <2)
		{
			return(NEED_MORE_ARG);
		}
		return(CMD_INSERT);
 
    }

    if (strcasecmp(CMD_PRINT_STR, w1) == 0) {
		 return(CMD_PRINT);
    }

    if (strcasecmp(CMD_FIND_STR, w1) == 0) {
		return(CMD_FIND);
    }
	
	if (strcasecmp(CMD_DELETE_STR, w1) == 0)
	{
		return(CMD_DELETE);
	}
    // don't know what this is, doesn't match any commands
    
    return CMD_UNK;
}

/*
 * Parse the input, do the command or generate and error
 */
int main(int argc, char* argv[]){

    BSTObj  *T;
    char    str[MAX_INPUT_LENGTH+3];	// one more for one character over and null
    char    cmdStr[MAX_INPUT_LENGTH +1];
    char    arg1[MAX_INPUT_LENGTH +1];
    char    arg2[MAX_INPUT_LENGTH +1];
    char   *inputStr;
    int     action;
    int     input_from_terminal;
    
    T = NULL;

    input_from_terminal = isatty(fileno(stdin));
    
    if (input_from_terminal)
	printf(COMMAND_PROMPT);

    // note that fgets reads the newline character "\n" and includes this in the string
    while ( (inputStr  = fgets(str,  MAX_INPUT_LENGTH + 2, stdin)) != NULL) {
 
        //printf("fgets returned %s\n", inputStr);
	
        // check input line length
	if(!inputLengthOK(inputStr)) { 
	   action = INPUT_TOO_LONG; 	// too big!
	}
        else {
            //printf("got request |%s|\n", inputStr);
            action = parseInput(inputStr, cmdStr, arg1, arg2);
            //printf("got action = %d\n", action);
	}

	switch(action) {
        
            case CMD_NONE:
		break;
	    case INPUT_TOO_LONG:
		printf(ERR_TOO_LONG, MAX_INPUT_LENGTH);
		break;
            case EXTRA_ARG:
		printf(ERR_EXTRA_ARG, arg1);
		break;
  	    case NEED_MORE_ARG:
		printf(ERR_NEED_ARG);
		break;
  	    case NO_ARGS_NEEDED:
		printf(ERR_NO_ARGS_NEEDED, cmdStr);
		break;
	    case CMD_HELP:
		showHelp();
		break;
	    case CMD_ERASE:
		doErase(&T);
		break;
	    case CMD_QUIT:
		doQuit();
		break;
	    case CMD_HEIGHT:
		doHeight(T);
		break;
	    case CMD_INSERT:
		doInsert(&T, arg1);
		break;
	    case CMD_PRINT:
		doPrint(T, arg1);
                break;
            case CMD_FIND:
		doFind(T, arg1);
   		break;
		case CMD_DELETE:
		doDelete(arg1, T);
		break;
		
            case CMD_UNK:
		printf(ERR_UNK_CMD, cmdStr);
                break;
	    default:
		fprintf(stderr, "at default statement\n");
        }
        *arg1 = '\0';
        *arg2 = '\0';
        *cmdStr = '\0';

        if (input_from_terminal )
           printf(COMMAND_PROMPT);
    }
   
    exit(1);
}


/***************************************************************************************
 *
 * the functions that actually do the command requested by the user
 */
//quits
void doQuit() {
    printf("\n");
    exit(0);
}
//displays help message
void showHelp() {
    printf(HELP_MESSAGE);
}
//empties the binary tree
void doErase( BSTObj **ptrT) {
 // your code here
 makeEmpty(&*ptrT);
}
//calls the tree Height command allowing for the height of the tree to be calculated
void doHeight( BSTObj *T) {
 // your code here
 printf(MSG_HEIGHT,treeHeight(T,0));
}

// insert the argument into the tree
void doInsert(BSTObj **ptrT, char *arg) {

 //insert(arg, &(*ptrT));
int length = strlen(arg);
int i;

for(i = 0; i<length; i++)
{
if (isgraph(arg[i]) == 0)
{
	printf(ERR_BAD_STR,(int)arg[i]);
	return NULL;
}	
} 
 if (insert(arg, &(*ptrT)) == 0)
 {
	 printf(MSG_NONE);
 }else 
 {
	printf(ERR_DUPLICATE, arg);
 }

}

// figure out which print the user wanted and do it
// if there is no ordering then use inorder as the default
void doPrint(BSTObj *T, char *order) {
    
	 if(strcasecmp(order) == strcasecmp("postorder"))
	 {
		 postorderTraverse(stdout, T);
		 //printf("CHECK2");
		 return;
	 }
	 
	 if(strcasecmp(order) == strcasecmp("preorder"))
	 {
		 preorderTraverse(stdout, T);
		 //printf("CHECK3");
		 return;
	 }
	 
	 if(strcasecmp(order) == strcasecmp("inorder"))
	 {
	 inorderTraverse(stdout, T);
	 //printf("CHECK4");
	 return;
	 }
	 
	 if(strcasecmp(order) == strcasecmp(""))
	 {
	 inorderTraverse(stdout, T);
	 //printf("CHECK NULL");
	 return;
	 }
	 
	 
	 
	    printf(ERR_UNK_ARG, order);
		//printf("%s" , order);
		return;
	 
	
		
}
//finds a specific term in a linked list
void doFind(BSTObj *T, char *term) {
    
 BSTObj * node = find(term,T);	
 if(find(term,T) != NULL)
 {
	 printf(MSG_FOUND, node->term);
 }else
 {
	 printf(ERR_NOT_FOUND,term);
 }
 
}

//check if we have read past the allowed max, not that fgets passes the newline character in a string
//fgets does a read of MAX_INPUT_LENGTH + 1
int inputLengthOK(char *inputStr) {
    
    int  length;

    length = strlen(inputStr);


    if(length>MAX_INPUT_LENGTH)
	{
		scanf("%s", inputStr);
		return FALSE;
	}
   return TRUE;
}

//deletes a specific node in the function
void doDelete(char* term, BSTObj**T)
{
	int delete = deleteItem(term, T);
	if(delete == 1){
		printf(MSG_DELETED, term);
	}else
	{
		printf(ERR_NOT_FOUND_DELETE, term);
	}

}