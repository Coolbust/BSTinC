
#define COMMAND_PROMPT "BST> "
#define HELP_PROMPT "Enter \"help\" for description of each command\n" 
#define HELP_MESSAGE \
	"Available commands are:\n" \
	"erase                  -- erase the current tree\n" \
	"find <string>          -- see if <string> is in the tree\n" \
	"height                 -- print the height of the tree\n" \
	"help                   -- print this list of commands\n" \
	"insert <string>        -- insert <string> into the tree\n" \
	"print [inorder|preorder|postorder]    -- print tree in specified order\n" \
	"delete					-- removes a specified node from the tree\n" \
	"quit                   -- quit the program\n"
	

#define MSG_NONE	"OK\n"
#define MSG_FOUND	"Found \"%s\"\n"
#define MSG_HEIGHT	"Height = %d\n"
#define MSG_DELETED "Deleted \"%s\"\n"

#define ERR_BAD_STR	"Invalid character (decimal value %d) in string\n"
#define ERR_DUPLICATE	"Duplicate string \"%s\"\n"
#define ERR_EXTRA_ARG	"Unexpected text after \"%s\" argument. \n" HELP_PROMPT
#define ERR_NO_ARGS_NEEDED "Unexpected text after \"%s\" command. \n" HELP_PROMPT
#define ERR_NEED_ARG	"Command requires an argument\n" HELP_PROMPT
#define ERR_NOT_FOUND	"Could not find \"%s\"\n"
#define ERR_NOT_FOUND_DELETE	"Could not find \"%s\" to delete \n"
#define ERR_TOO_LONG	"Input line too long; length must not exceed %d characters\n"
#define ERR_UNK_ARG	"Unrecognized argument \"%s\"\n" HELP_PROMPT
#define ERR_UNK_CMD	"Unrecognized command \"%s\"\n" HELP_PROMPT
#define MAX_INPUT_LENGTH 150


#define	INPUT_TOO_LONG   2
#define NEED_MORE_ARG    3
#define EXTRA_ARG	 5
#define NO_ARGS_NEEDED   7
#define CMD_HELP	10
#define CMD_ERASE	20
#define CMD_QUIT 	30
#define CMD_HEIGHT 	40
#define CMD_INSERT	50
#define CMD_PRINT    	60
#define CMD_FIND	70
#define CMD_UNK		80
#define CMD_NONE	90
#define CMD_DELETE  100
 
#define CMD_HELP_STR    "help"
#define CMD_ERASE_STR   "erase"
#define CMD_QUIT_STR    "quit"
#define CMD_HEIGHT_STR  "height"
#define CMD_INSERT_STR	"insert"
#define CMD_PRINT_STR   "print"
#define CMD_PREORDER    "preorder"
#define CMD_INORDER     "inorder"
#define CMD_POSTORDER   "postorder"
#define CMD_FIND_STR    "find"
#define CMD_DELETE_STR  "delete"
 
