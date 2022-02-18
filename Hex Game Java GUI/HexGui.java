import java.awt.FlowLayout;
import java.awt.GridLayout;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.text.AttributeSet.ColorAttribute;

import java.awt.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class HexGui extends JFrame implements ActionListener{
    private static final long serialVersionUID = 1L;
    private JButton playButton;
    private JTextField textField;
    private JRadioButton pvpButton,pvcButton;
    private JPanel menuPanel,gamePanel;
    private boolean isSelected=false;
    private HexGame hexGame;
    private HexButton[][] buttons;
    private JButton resetButton;
    private JButton loadButton;
    private JButton saveButton;
    private JButton undoButton;
    public HexGui(){
        super();
        hexGame=new HexGame();
        createMenuPanel();
        add(menuPanel);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(null);
        setSize(600,800);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        //setResizable(false);
    }
    public static void main(String[] args) {
        HexGui game = new HexGui();
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource()==playButton) {
            System.out.println("Size is :" + textField.getText());
            hexGame.setWidth(Integer.parseInt(textField.getText()));
            hexGame.setHeight(Integer.parseInt(textField.getText()));
            hexGame.createBoard();
            //SIZE I KONTROL ET
            if (isSelected) {
                getContentPane().removeAll();
                createGamePanel();
                getContentPane().add(gamePanel);
                repaint();
            }
        }
        if (e.getSource()==pvpButton) {
            System.out.println("pvp selected");
            isSelected=true;
            hexGame.setGameMode(1);
        }
        if (e.getSource()==pvcButton) {
            System.out.println("pvc selected");
            isSelected=true;
            hexGame.setGameMode(2);
        }
        if (e.getSource()==undoButton) {
            if (hexGame.getGameMode()==1){
                if (hexGame.undo()) {
                    updateBoard();
                }
                else{
                    JFrame tempFrame=new JFrame();
                    tempFrame.setAlwaysOnTop(true);
                    JOptionPane.showMessageDialog(tempFrame,"There Is No Move To Undo");
                }
            }
            else{
                if (hexGame.undo(5)) {
                    updateBoard();
                }
                else{
                    JFrame tempFrame=new JFrame();
                    tempFrame.setAlwaysOnTop(true);
                    JOptionPane.showMessageDialog(tempFrame,"There Is No Move To Undo");
                } 
            }
        }
        if (e.getSource()==resetButton) {
            hexGame.setcompCounter(0);
            hexGame.setCounter(0);
            hexGame.setMarkedCells(0);
            hexGame.setMoveCount(0);
            for (int i = 0; i < hexGame.getHeight(); i++) {
                for (int j = 0; j < hexGame.getWidth(); j++) {
                    hexGame.getCell(i,j).setState(CellContent.empty);
                }
            }
            updateBoard();
        }
        if (e.getSource()==saveButton) {
            String fileName=JOptionPane.showInputDialog("Enter the file name that you want to save: ");
            try {
                hexGame.saveBoard(fileName);
            } catch (IOException io) {
                io.printStackTrace();
            }
        }
        if (e.getSource()==loadButton) {
            String fileName=JOptionPane.showInputDialog("Enter the file name that you want to load: ");
            try {
                hexGame.loadBoard(fileName);
            } catch (IOException io) {
                io.printStackTrace();
            }
            getContentPane().remove(gamePanel);
            invalidate();
            createGamePanel();
            for (int i = 0; i < hexGame.getHeight(); i++) {
                for (int j = 0; j < hexGame.getWidth(); j++) {
                    if (hexGame.getCell(i,j).getState()==CellContent.empty) {
                        buttons[i][j].setEnabled(true);
                        buttons[i][j].setBackground(new JButton().getBackground());
                    }
                    else if(hexGame.getCell(i,j).getState()==CellContent.x || hexGame.getCell(i,j).getState()==CellContent.X){
                        buttons[i][j].setEnabled(false);
                        buttons[i][j].setBackground(Color.RED);
                    }
                    else if(hexGame.getCell(i,j).getState()==CellContent.o || hexGame.getCell(i,j).getState()==CellContent.O){
                        buttons[i][j].setEnabled(false);
                        buttons[i][j].setBackground(Color.YELLOW);
                    }
                }
            }
            add(gamePanel);
            validate();
            repaint();
            //updateBoard();
        }
        if (e.getSource() instanceof HexButton) {
            if (hexGame.getGameMode()==1) {
                HexButton tempButton = (HexButton) e.getSource();
                Cell tempCell =new Cell(tempButton.getRow(),tempButton.getCol());
                tempCell=hexGame.play(tempCell);
                if (tempCell.getState().equals(CellContent.x)) {
                    tempButton.setBackground(Color.RED);
                }else if(tempCell.getState().equals(CellContent.o)){
                    tempButton.setBackground(Color.YELLOW);
                }
                tempButton.setEnabled(false);
                if (hexGame.isWin(CellContent.x, CellContent.o)){
                    allButtonDisable();
                    JFrame tempFrame=new JFrame();
                    tempFrame.setAlwaysOnTop(true);
                    JOptionPane.showMessageDialog(tempFrame,"Player 1 Wins !");
                    undoButton.setEnabled(false);
                }
                else if(hexGame.isWin(CellContent.o, CellContent.x)){
                    allButtonDisable();
                    JFrame tempFrame=new JFrame();
                    tempFrame.setAlwaysOnTop(true);
                    JOptionPane.showMessageDialog(tempFrame,"Player 2 Wins !");
                    undoButton.setEnabled(false);
                }
            } 
            else{
                HexButton tempButton = (HexButton) e.getSource();
                Cell tempCell =new Cell(tempButton.getRow(),tempButton.getCol());
                tempCell=hexGame.play(tempCell);
                if (tempCell.getState().equals(CellContent.x)) {
                    tempButton.setBackground(Color.RED);
                }else if(tempCell.getState().equals(CellContent.o)){
                    tempButton.setBackground(Color.YELLOW);
                }
                tempButton.setEnabled(false);
                Cell compCell=hexGame.play();
                buttons[compCell.getRow()][compCell.getColumn()].setEnabled(false);
                buttons[compCell.getRow()][compCell.getColumn()].setBackground(Color.YELLOW);
                if (hexGame.isWin(CellContent.x, CellContent.o)){
                    allButtonDisable();
                    JFrame tempFrame=new JFrame();
                    tempFrame.setAlwaysOnTop(true);
                    JOptionPane.showMessageDialog(tempFrame,"Player 1 Wins !");
                    undoButton.setEnabled(false);
                }
                else if(hexGame.isWin(CellContent.o, CellContent.x)){
                    allButtonDisable();
                    JFrame tempFrame=new JFrame();
                    tempFrame.setAlwaysOnTop(true);
                    JOptionPane.showMessageDialog(tempFrame,"Computer Wins !");
                    undoButton.setEnabled(false);
                }
            }
        }
    }
    public void updateBoard() {
        for (int i = 0; i < buttons.length; i++) {
            for (int j = 0; j < buttons.length; j++) {
                if (hexGame.getCell(i, j).getState().status=='.') {
                    buttons[i][j].setBackground(new JButton().getBackground());
                    buttons[i][j].setEnabled(true);
                }
                if (hexGame.getCell(i, j).getState().status=='x') {
                    buttons[i][j].setBackground(Color.RED);
                    buttons[i][j].setEnabled(true);
                }
                if (hexGame.getCell(i, j).getState().status=='o') {
                    buttons[i][j].setBackground(Color.YELLOW);
                    buttons[i][j].setEnabled(true);
                }
            }
            undoButton.setEnabled(true);
        }
    }
    public void allButtonDisable() {
        for (int i = 0; i < buttons.length; i++) {
            for (int j = 0; j < buttons.length; j++) {
                buttons[i][j].setEnabled(false);
            }
        }
    }
    public void createMenuPanel() {
        menuPanel = new JPanel();
        menuPanel.setBounds(0,0,1920,1080);
        menuPanel.setBackground(Color.BLUE);
        menuPanel.setLayout(null);
        textField = new JTextField();
        textField.setBounds(750,400,80,40);
        textField.setPreferredSize(new Dimension(80,40));
        playButton= new JButton("Play Game!");
        playButton.addActionListener(this);
        playButton.setBounds(675,460,120,40);
        JLabel sizeLabel = new JLabel();
        ImageIcon sizeLogo = new ImageIcon(getClass().getResource("size.png")); 
        JLabel titleLabel = new JLabel();
        ImageIcon titleLogo = new ImageIcon(getClass().getResource("title.png")); 
        sizeLabel.setIcon(sizeLogo);
        titleLabel.setIcon(titleLogo);
        sizeLabel.setBounds(600,315, 200, 200);
        titleLabel.setBounds(400,-150, 1200, 800);
        pvpButton = new JRadioButton("Player VS Player");
        pvcButton = new JRadioButton("Player VS Computer");
        pvpButton.setBounds(600, 345,120, 20);
        pvpButton.addActionListener(this);
        pvcButton.setBounds(750, 345,180, 20);
        pvcButton.addActionListener(this);
        ButtonGroup selectionGroup = new ButtonGroup();
        selectionGroup.add(pvpButton);
        selectionGroup.add(pvcButton);
        menuPanel.add(pvpButton);
        menuPanel.add(pvcButton);
        menuPanel.add(sizeLabel);
        menuPanel.add(playButton);
        menuPanel.add(textField);
        menuPanel.add(titleLabel);
    }
    public void createGamePanel() {
        gamePanel=new JPanel();
        gamePanel.setBounds(0,0,1920,1080);
        gamePanel.setBackground(Color.BLUE);
        gamePanel.setLayout(null);
        int row=0,col=0,i;
        buttons=new HexButton[hexGame.getHeight()][hexGame.getWidth()];
        for (i = 0; i < buttons.length; i++) {
            col=25*i;
            for (int j = 0; j < buttons.length; j++) {
                buttons[i][j] = new HexButton(i,j);
                buttons[i][j].setLayout(null);
                buttons[i][j].setBounds(col,row,50,50);
                buttons[i][j].addActionListener(this);
                gamePanel.add(buttons[i][j]);
                col+=50;
            }
            row+=50;
        }
        undoButton=new JButton("UNDO");
        undoButton.setBounds(400, 550, 200, 100);
        undoButton.addActionListener(this);
        resetButton=new JButton("RESET");
        resetButton.setBounds(600, 550, 200, 100);
        resetButton.addActionListener(this);
        loadButton=new JButton("LOAD");
        loadButton.setBounds(800, 550, 200, 100);
        loadButton.addActionListener(this);
        saveButton=new JButton("SAVE");
        saveButton.setBounds(1000, 550, 200, 100);
        saveButton.addActionListener(this);

        gamePanel.add(undoButton);
        gamePanel.add(resetButton);
        gamePanel.add(loadButton);
        gamePanel.add(saveButton);
    }
    public class HexButton extends JButton {
        private static final long serialVersionUID = 1L;
        private int row;
        private int col;

        public HexButton(int row,int col){
            this.row=row;
            this.col=col;
        }
        public int getRow() {
            return this.row;
        }

        public void setRow(int row) {
            this.row = row;
        }

        public int getCol() {
            return this.col;
        }

        public void setCol(int col) {
            this.col = col;
        }
    }
}
