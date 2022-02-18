public enum CellContent
{
    empty('.'),x('x'),o('o'),X('X'),O('O');
    public Character status;
    CellContent(Character st){
        this.status=st;
    }
}