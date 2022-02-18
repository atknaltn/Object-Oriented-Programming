import java.io.BufferedReader;
import java.io.*;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class HexGame {
    private Cell[][] hexCell=null;
    private Cell[] moves=null;
    private Cell[] unsuitCells=null;
    private int unsuitCount=0;
    private int moveCount=0;
    private double score_x=0;
    private double score_o=0;
    private int tempScoreX=0;
    private int tempScoreO=0;
    private String gameName="Nameless";
    private String fName;
    private int gameMode=1;
    private int rowSize;
    private int colSize;
    private int counter=0;
    private int compCounter=0;
    private int compX=0;
    private int compY=0;
    private boolean gameEnd=false;
    private int markedCells=0;
    private static int allMarkedCells;
    private static int gameCount;
    public int getMoveCount() {
        return this.moveCount;
    }

    public void setMoveCount(int moveCount) {
		this.moveCount = moveCount;
	};
    public void createBoard(){
        int i,j;
        hexCell = new Cell[rowSize][colSize];
        for (i = 0; i < rowSize; i++)
        {
            for (j = 0; j <colSize; j++)
            {
                hexCell[i][j]= new Cell(i,j);
            }
        }
    }
    public Cell play(){
        Cell tempCell=new Cell();
        markedCells++;
        int[][] move_up={{-1,0},{-1,1}};
        int[][] move_down={{1,-1},{1,0}};
        int[][] left_rigt={{0,-1},{0,1}};
        allMoves(move_up,move_down,left_rigt); 
        tempCell.setColumn(compY);
        tempCell.setRow(compX);
        tempCell.setState(CellContent.o);
        counter++;
        compCounter++;
        moveCount++;
        addMove(tempCell);
        return tempCell;
    }
    public Cell play(Cell cell){
        markedCells++;
        if(getCounter()%2==0)
        {
            hexCell[cell.getRow()][cell.getColumn()].setState(CellContent.x);
        }
        else
        {
            hexCell[cell.getRow()][cell.getColumn()].setState(CellContent.o);
        }
        counter++;
        moveCount++;
        addMove(hexCell[cell.getRow()][cell.getColumn()]);
        return hexCell[cell.getRow()][cell.getColumn()];
    }
    public boolean undo() {
        if (!isEmpty())
        {
            counter--;
            markedCells--;
            hexCell[topMove().getRow()][topMove().getColumn()].setState(CellContent.empty);
            delMove();
            return true;
        }
        return false;
    }
    public Cell getCell(int r,int c) {
        return hexCell[r][c];
    }
    public boolean undo(int foo) {
        if (!isEmpty())
        {
            compCounter-=1;
            markedCells-=2;
            hexCell[topMove().getRow()][topMove().getColumn()].setState(CellContent.empty);
            delMove();
            hexCell[topMove().getRow()][topMove().getColumn()].setState(CellContent.empty);
            delMove();
            if (getCapacity()!=0) {
                compX=topMove().getRow();
                compY=topMove().getColumn();   
            }
            return true;
        }
        return false;
    }
    void display()
    {
        int i,j,k;
        System.out.print("GAME NAME: ");
        System.out.println(gameName);
        System.out.print(" ");
        for (i = 0; i < rowSize; i++)
        {
            System.out.printf("%c ",(char)'A'+i);
        }
        System.out.println();
        for (i = 0; i < colSize; i++)
        {
            System.out.printf("%d ",1+i);
            for (k = 0; k < i; k++)
            {
                System.out.print(" ");
            }
            for (j = 0; j < colSize; j++)
            {
                System.out.printf("%c ",hexCell[i][j].getState().status);
            }
            System.out.println();
        }
        if (gameEnd==false)
        {
            System.out.println("ENTER \"EXIT\" TO BACK TO MAIN MENU"); 
        }
    }
    public boolean isWin(CellContent safe_ch,CellContent forb_ch){
        int i,j;
        int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
        int move_col[]={0,1,-1,1,-1,0};
        int coordinate[]=new int[2];
        for (i = 0; i < colSize; i++)
        {
            if (safe_ch == CellContent.x)
            {
                if (hexCell[i][0].getState()!=CellContent.empty && hexCell[i][0].getState()!=forb_ch)
                {
                    coordinate[0]=i;
                    coordinate[1]=0;
                    if (winControl(coordinate,move_row,move_col,0,safe_ch))
                    {
                        if (safe_ch==CellContent.x)
                        {
                            hexCell[i][0].setState(CellContent.X);
                        }
                        else if (safe_ch==CellContent.o)
                        {
                            hexCell[i][0].setState(CellContent.O);
                        }                    
                        return true;
                    }
                }
            }
            else
            {
                if (hexCell[0][i].getState()!=CellContent.empty && hexCell[0][i].getState()!=forb_ch)
                {
                    coordinate[0]=0;
                    coordinate[1]=i;
                    if (winControl(coordinate,move_row,move_col,0,safe_ch))
                    {
                        if (safe_ch==CellContent.x)
                        {
                            hexCell[0][i].setState(CellContent.X);
                        }
                        else if (safe_ch==CellContent.o)
                        {
                            hexCell[0][i].setState(CellContent.O);
                        }  
                        return true;
                    }
                }
            }
        }
        return false; 
    }
    public boolean winControl(int[] coordinate,int[] move_row,int[] move_col,int count,CellContent usr_ch){
        int k;
        int next_coord[]=new int[2];
        if (usr_ch==CellContent.x && coordinate[1]==colSize-1)
            return true;
        else if (usr_ch==CellContent.o && coordinate[0]==colSize-1)
            return true;
        for (k = 0; k < 6; k++) 
        {
            next_coord[0] = coordinate[0] + move_row[k];
            next_coord[1] = coordinate[1] + move_col[k];
            if (checkSuitability(next_coord,usr_ch)) 
            {
                if (usr_ch==CellContent.x)
                    hexCell[next_coord[0]][next_coord[1]].setState(CellContent.X);
                else if (usr_ch==CellContent.o)
                    hexCell[next_coord[0]][next_coord[1]].setState(CellContent.O);
                if (winControl(next_coord,move_row,move_col,count + 1,usr_ch)==true)
                    return true;
                else
                    hexCell[next_coord[0]][next_coord[1]].setState(usr_ch); 
            }
        }
        return false;
    }
    private boolean checkSuitability(int[] coordinate,CellContent usr_ch){
        CellContent forb_ch;
        if (usr_ch==CellContent.x)
            forb_ch=CellContent.o;
        else
            forb_ch=CellContent.x;     
        return (coordinate[0] >= 0 && coordinate[0] < rowSize && coordinate[1] >= 0 && coordinate[1] < colSize && 
        hexCell[coordinate[0]][coordinate[1]].getState() == usr_ch);
    }
    private void allMoves(int[][] move_up,int[][] move_down,int[][] left_rigt){
        if (!compMove(move_down))
        {
            if (!compMove(left_rigt))
            {
                randomMove();
            }
        }   
    }
    private void randomMove(){
        boolean exit=true;
        int rand_coord[]=new int[2];
        Random randRow=new Random();
        Random randCol=new Random();
        while (exit)
        {
            rand_coord[0]=randRow.nextInt(rowSize);
            rand_coord[1]=randCol.nextInt(colSize);
            if (checkComputerMove(rand_coord))
            {
                hexCell[rand_coord[0]][rand_coord[1]].setState(CellContent.o);
                compX=rand_coord[0];
                compY=rand_coord[1];
                exit=false;
            }
        }
    }
    private boolean compMove(int moves[][]){
        if (compCounter==0)
        {
            if (hexCell[0][colSize/2].getState()==CellContent.empty)
            {
                compX=0;
                compY=colSize/2;
                hexCell[compX][compY].setState(CellContent.o);
            }
            else
            {
                compX=0;
                compY=(colSize/2)-1;
                hexCell[compX][compY].setState(CellContent.o);
            }
            return true;
        }
        else
        {
            int i;
            int[] temp_coord=new int[2];
            temp_coord[0]=compX;
            temp_coord[1]=compY;
            for (i = 0; i <2; i++)
            {
                temp_coord[0]+=moves[i][0];
                temp_coord[1]+=moves[i][1];
                if (checkComputerMove(temp_coord))
                {
                    compX+=moves[i][0];
                    compY+=moves[i][1];
                    hexCell[compX][compY].setState(CellContent.o);
                    return true;
                }
                else
                {
                    temp_coord[0]-=moves[i][0];
                    temp_coord[1]-=moves[i][1];
                }      
            }
        }
        return false;
    }
    private boolean checkComputerMove(int coord[]){
        return (coord[0] >= 0 && coord[0] < colSize && coord[1] >= 0 && coord[1] < colSize && 
        hexCell[coord[0]][coord[1]].getState() == CellContent.empty);
    }
    private void addMove(Cell move){
        int i;
        Cell[] tempMove;
        tempMove=new Cell[moveCount];
        if (moveCount==1)
        {
            moves = new Cell[moveCount];
            moves[moveCount-1]=move;
        }
        else
        {
            for (i = 0; i < moveCount-1; i++)
            {
                tempMove[i]=moves[i];
            }
            moves=null;
            moves = new Cell[moveCount];
            for (i = 0; i < moveCount; i++)
            {
                moves[i]=tempMove[i];
            }
            moves[moveCount-1]=move;
            tempMove=null;
        }
    }
    private void delMove(){
        if (isEmpty())
        {
            moves=null;
            System.out.println("No more moves to undo !");
        }
        else
        {
            int i;
            Cell[] tempMove;
            tempMove=new Cell[getCapacity()-1];   
            for (i = 0; i < getCapacity()-1; i++)
            {
                tempMove[i]=moves[i];
            }
            moves=null;
            decreaseCapacity();
            moves = new Cell[getCapacity()];
            for (i = 0; i < getCapacity(); i++)
            {
                moves[i]=tempMove[i];
            }
            tempMove=null;
        }
    }
    private Cell topMove(){
        return moves[getCapacity()-1];
    }
    private boolean isEmpty(){
        if (getCapacity()==0)
        {
            return true;
        }
        return false;
    }
    public void setGameName(String name){gameName=name;}
    public void setGameName(String name,int foo){gameName=name;}
    public String getGameName() {return gameName;}
    public int getWidth(){return rowSize;}
    public int getHeight(){return colSize;}
    public void setWidth(int width){colSize=width;}
    public void setHeight(int height){rowSize=height;}
    public boolean isEnd(){return gameEnd;}
    public int getMarkedCells(){return markedCells;}
    public void setMarkedCells(int set) {markedCells=set;}
    public void findMarkedCells(){
        int i,j,num=0;
        for (i = 0; i <rowSize; i++)
        {
            for (j = 0; j < colSize; j++)
            {
                if (hexCell[i][j].getState()!=CellContent.O)
                    num++;
            }
        }
        allMarkedCells+=num;
    }
    public static int numMarkedCells(){return allMarkedCells;}
    public static void setNumMarkedCells(int num){allMarkedCells=num;}
    public static int numGames(){return gameCount;}
    public static void setNumGames(int num){gameCount=num;}
    public void loadBoard(String fileName) throws IOException{
        BufferedReader file = new BufferedReader(new FileReader(fileName));
        int i = Integer.parseInt(file.readLine());
        if (i==1) {
            gameEnd=true;
        }else
            gameEnd=false;
        i=Integer.parseInt(file.readLine());
        System.out.println(i);
        setWidth(i);
        setHeight(i);
        setGameMode(Integer.parseInt(file.readLine()));
        setCounter(Integer.parseInt(file.readLine()));
        setcompCounter(Integer.parseInt(file.readLine()));
        setCompX(Integer.parseInt(file.readLine()));
        setCompY(Integer.parseInt(file.readLine()));
        createBoard();
        char tempChar;
        for (int j = 0; j < getHeight(); j++) {
            for (int j2 = 0; j2 < getWidth(); j2++) {
                tempChar=(char)file.read();
                if (tempChar==CellContent.x.status) {
                    hexCell[j][j2].setState(CellContent.x);   
                }
                else if (tempChar==CellContent.o.status) {
                    hexCell[j][j2].setState(CellContent.o);   
                }
                else if (tempChar==CellContent.X.status) {
                    hexCell[j][j2].setState(CellContent.X);   
                }
                else if (tempChar==CellContent.O.status) {
                    hexCell[j][j2].setState(CellContent.O);   
                }
                else if (tempChar==CellContent.empty.status) {
                    hexCell[j][j2].setState(CellContent.empty);   
                }
            }
        }
        file.readLine();
        setCapacity(Integer.parseInt(file.readLine()));
        moves=null;
        moves=new Cell[getCapacity()];
        for (int j = 0; j < getCapacity(); j++) {
            moves[j]=new Cell();
        }
        for (int j = 0; j < getCapacity(); j++) {
            moves[j].setRow(file.read()-'0');
            file.skip(1);
            moves[j].setColumn(file.read()-'0');
            file.skip(1);
            tempChar=(char)file.read();
            file.skip(2);
            if (tempChar==CellContent.x.status) {
                moves[j].setState(CellContent.x);   
            }
            else if (tempChar==CellContent.o.status) {
                moves[j].setState(CellContent.o);   
            }
            else if (tempChar==CellContent.X.status) {
                moves[j].setState(CellContent.X);   
            }
            else if (tempChar==CellContent.O.status) {
                moves[j].setState(CellContent.O);   
            }
            else if (tempChar==CellContent.empty.status) {
                moves[j].setState(CellContent.empty);   
            }
        }
	for(int j=0;j<getCapacity();j++){
	System.out.println("x: "+moves[j].getRow()+" y: "+moves[j].getColumn()+" State: "+moves[j].getState().status);
}
        file.close();
    }
    //public int loadBoard(String fileName,int foo);
    public void saveBoard(String fileName) throws IOException{
        FileWriter file = new FileWriter(fileName);
        System.out.println(fileName);
        if (gameEnd) {
            file.write(1+"\n");
        }
        else
            file.write(0+"\n");

        file.write(getWidth()+"\n");
        file.write(getGameMode()+"\n");
        file.write(getCounter()+"\n");
        file.write(getcompCounter()+"\n");
        file.write(compX+"\n");
        file.write(compY+"\n");
        for (int i = 0; i < getHeight(); i++) {
            for (int j = 0; j < getWidth(); j++) {
                file.write(hexCell[i][j].getState().status);
            }
        }
        file.write("\n");
        file.write(getCapacity()+"\n");
        for (int i = 0; i <getCapacity(); i++) {
            file.write(moves[i].getRow()+" ");
            file.write(moves[i].getColumn()+" ");
            file.write(moves[i].getState().status.toString()+" ");
            file.write("\n");
        }
        file.close();
    }
    public String cellToStr(Cell cell) {
        if (cell.getState().status=='x') {
            return "x";
        }
        else if (cell.getState().status=='X') {
            return "X";
        }
        else if (cell.getState().status=='o') {
            return "o";
        }
        else if (cell.getState().status=='O') {
            return "O";
        }
        return ".";
    }
    public int getCounter(){return counter;}
    public void setCounter(int count){counter=count;}
    public int getcompCounter(){return compCounter;}
    public void setcompCounter(int compCount){compCounter=compCount;}
    public int getGameMode(){return gameMode;}
    public void setGameMode(int gM){gameMode=gM;}
    public void setEnd(boolean end) {gameEnd=end;}
    public void setFName(String name){fName=name;}
    public String getFName(){return fName;}
    public void increaseCapacity(){moveCount++;}
    public void decreaseCapacity(){moveCount--;}
    public int getCapacity(){return moveCount;}
    public void setCapacity(int size){moveCount=size;}
    public int getCompX(){return compX;}
    public int getCompY(){return compY;}
    public void setCompX(int x){compX=x;}
    public void setCompY(int y){compY=y;} 
    public void findScoreX(int x,int y){
        int i;
        int[] move_row={-1,-1,0,0,1,1};//These are the 6 different direction in the game
        int[] move_col={0,1,-1,1,-1,0};
        int[] coordinate =new int[2];
        unsuitCount++;
        Cell tempCell=new Cell(x,y);
        addUnsuit(tempCell);
        for (i = 0; i < 6; i++)
        {
            coordinate[0] = x + move_row[i];
            coordinate[1] = y + move_col[i];
            if (checkSuitability(coordinate,CellContent.x))
            {   
                if (isUnsuit(coordinate[0],coordinate[1]))
                {
                    if (i==1 || i==3)
                    {
                        tempScoreX++;
                    }
                    findScoreX(coordinate[0],coordinate[1]);
                }
            }
        }
    }
    public void scoreX(){
        int i;
        for (i = 0; i <getCapacity(); i+=2)
        {
            unsuitCount=0;
            unsuitCells=null;
            tempScoreX=0;
            findScoreX(moves[i].getRow(),moves[i].getColumn());
            if (tempScoreX>score_x)
                score_x=tempScoreX;
        }
    }
    public void findScoreO(int x,int y){
        int i;
        int move_row[]={-1,-1,0,0,1,1};//These are the 6 different direction in the game
        int move_col[]={0,1,-1,1,-1,0};
        int[] coordinate = new int[2];
        unsuitCount++;
        Cell tempCell=new Cell(x,y);
        addUnsuit(tempCell);
        for (i = 0; i < 6; i++)
        {
            coordinate[0] = x + move_row[i];
            coordinate[1] = y + move_col[i];
            if (checkSuitability(coordinate,CellContent.o))
            {   
                if (isUnsuit(coordinate[0],coordinate[1]))
                {
                    if (i==4 || i==5)
                    {
                        tempScoreO++;
                    }
                    findScoreO(coordinate[0],coordinate[1]);
                }
            }
        }
    }
    public void scoreO(){
        int i;
        for (i = 1; i <getCapacity(); i+=2)
        {
            unsuitCount=0;
            unsuitCells=null;
            tempScoreO=0;
            findScoreO(moves[i].getRow(),moves[i].getColumn());
            if (tempScoreO>score_o)
                score_o=tempScoreO;
        }
    }
    public void setTempScoreX(int x){tempScoreX=x;}
    public void setTempScoreO(int o){tempScoreO=o;}
    public void setScoreX(int x){score_x=x;}
    public void setScoreO(int o){score_o=o;}
    public double getScoreX(){return score_x;}
    public double getScoreO(){return score_o;}
    public int getConnectedX(){return tempScoreX;}
    public int getConnectedO(){return tempScoreO;}
    public boolean isUnsuit(int x,int y){
        int i;
        for (i = 0; i < unsuitCount; i++)
        {
            if (unsuitCells[i].getRow()==x && unsuitCells[i].getColumn()==y)
            {
                return false;
            }
        }
        return true;
    }
    public void addUnsuit(Cell unsuit){
        int i;
        Cell[] tempCell;
        if (unsuitCount==1)
        {
            unsuitCells = new Cell[unsuitCount];
            unsuitCells[unsuitCount-1]=unsuit;
        }
        else
        {
            tempCell=new Cell[unsuitCount];
            for (i = 0; i < unsuitCount-1; i++)
            {
                tempCell[i]=unsuitCells[i];
            }
            unsuitCells=null;
            unsuitCells = new Cell[unsuitCount];
            for (i = 0; i < unsuitCount; i++)
            {
                unsuitCells[i]=tempCell[i];
            }
            unsuitCells[unsuitCount-1]=unsuit;
            tempCell=null;
        }
    }
    public int getUnsuitCellCount(){return unsuitCount;}
    public void setUnsuitCellCount(int count){unsuitCount=count;}

    HexGame()
    {
        colSize=5;
        rowSize=5;
        gameCount++;
        createBoard();
    }
    //IT CREATES AN OBJECT WITH SIZE PARAMATERS
    HexGame(int width,int height)
    {
        gameCount++;
        rowSize=height;
        colSize=width;
        createBoard();
    }
    
}
