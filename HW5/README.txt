THE USER CAN PRODUCE AS MANY OBJECTS AS HE/SHE WANT IN ANY TYPE OF CLASS.
HEXARRAY1D INCLUDES BIG THREE AND HEXADAPTER CLASS CAN TAKE VECTOR AND DEQUE.
THERE IS BROKENGAME.TXT TO TEST 9. OPTION
THE GAME HAS A MAIN MENU. THIS MAIN MENU HAS 10 OPTIONS:
1-NEW GAME:
	THIS OPTION CREATES A NEW GAME.IT ASKS TO USER TO ENTER THE GAME NAME.EACH GAME HAS A UNIQUE NAME.
THEN IT ASKS TO USER TO SELECT BOARD REPRESENTATION CLASS. USER CAN CHOOSE HexVector,HexArray1D AND HexAdapter.
IF USER CHOOSES HEXADAPTER, THEN PROGRAM ASKS IT WILL BE VECTOR OR DEQUE (STL CLASSES WITH RANDOM ITERATORS).
AFTER THE USER SELECT BOARD REPRESENTATION, GAME WILL BE START.
IF THE USER ENDS THE GAME OR ENTER THE EXIT COMMAND THEN PROGRAM WILL ASK THE USER TO SAVE THE GAME OR NOT. 
IF THE USER CHOOSE TO SAVE GAME THEN PROGRAM EXPECTS TO USER TO ENTER THE FILE NAME. IF THE FILE CANNOT BE CREATED, 
THEN IT THROWS AN EXCEPTION.IF THE USER DO NOT SAVE THE GAME THEN THE GAME WILL BE DELETED. AFTER THESE OPERATIONS 
THE GAME WILL BE SAVED TO BOTH FILE AND OBJECT. ALL LIVING GAMES ARE STORED IN THE VECTOR WHICH TAKES ABSTRACTHEX POINTERS.

2-LOAD GAME:
	THIS OPTION LISTS THE ACTIVE GAMES WHICH ARE CURRENT ABSTRACTHEX CLASS OBJECTS, THEN ASK TO USER TO
CHOOSE ONE GAME. SELECTED GAME WILL START WHERE IT LEFT OFF. AFTER THE GAME ENDED OR EXIT COMMAND 
HAS BEEN INPUTTED PROGRAM WILL ASK THE USER TO SAVE THE GAME OR NOT. IF THE USER SAVES THE GAME, PROGRAM  
SAVES THE GAME BUT THIS TIME WILL NOT ASK THE USER FOR THE FILE NAME BECAUSE EACH OBJECT'S FILE PATH
WAS SAVED IN THEIR PRIVATE DATAS.

3-LOAD GAME FROM FILE:
	THIS OPTION FIRST ASK THE USER TO ENTER THE GAME NAME, THEN ASK THE USER TO ENTER THE FILE PATH.
IF THE FILE CANNOT BE OPENED, PROGRAM WILL BE THROW AN EXCEPTION.AFTER THEN PROGRAM ASKS THE USER TO SELECT BOARD REPRESENTATION CLASS. 
AFTER SELECTION GAME DATAS WILL BE LOADED INTO CORRESPONDING BOARD REPRESENTATION CLASS. THESE CLASSES ARE HEXVECTOR, 
HEXARRAY1D AND HEXADAPTER.IF THE FILE CAN BE OPENED, PROGRAM WILL CREATE AN SELECTED CLASS'S OBJECT AND STARTS THE GAME.
THE PROGRAM SAVE THE DATAS IN THIS OBJECT.

4-LAST MOVE OF THE BOARD
	THIS OPTION LIST THE ALL GAMES THEN ASKS TO USER TO SELECT A GAME TO PRINT ITS LAST MOVE.
IT PRINTS COORDINATES AND WHO MADE THE MOVE. IF THERE IS NO MOVE IN THE GAME IT WILL THROW AN EXCEPTION

5-CHANGE SIZE OF THE GAME BOARD
	THIS OPTION LIST THE ALL GAMES THEN ASKS TO USER TO SELECT A GAME TO RESIZE BOARD. IF THE BOARD
SIZE AREN'T INPUTTED CORRECTLY IT THROWS AN EXCEPTION. AFTER THE RESIZING PROCESS BOARD WILL BE RESETTED.

6-RESET
	THIS OPTION LIST THE ALL GAMES THEN ASKS TO USER TO SELECT A GAME TO RESET. AFTER THIS OPERATION
ALL MOVES IN THE GAME WILL BE DELETED.

7-COMPARE TWO GAMES
	THIS OPERATION USES OPERATOR OVERLOADING FUNCTIONS TO COMPARE 2 GAME BOARDS ARE SAME OR NOT.
TO USE THIS OPERATION THERE MUST BE AT LEAST TWO OPEN GAMES.

8-SHOW CURRENT GAME'S STATUS:
	THIS OPTION SHOWS THE ALL ACTIVE GAMES'S SIZE,NUMBER OF MOVES,GAME MODE AND GAME IS FINISHED
OR NOT.

9-CONTROL VALIDITY
	THIS OPTION CALLS A GLOBAL FUNCTION THAT TAKES AN ARRAY OF ABSTRACTHEX POINTERS AND CHECKS ALL GAMES.
IF THERE IS A NOT PROPER BOARD IN ANY GAME, IT PRINTS GAME NAME AND ERROR MESSAGE. TO USE THIS OPERATION 
THERE MUST BE AT LEAST ONE OPEN GAMES. IF CORRESPONDING CELL DOES NOT EXIST IN THE GAME IT THROWS AN EXCEPTION.

10-EXIT
	TERMINATES THE PROGRAM.