// Dance of the knight -- Knight's tour algorithm (Working with EF the Great)
// ~~~~~~~~~~~~~~~~~~~~~~~
 
// 
// Allocate a 2-dimensional array (8x8, board) - "int board[8][8];"
// Create a function that 'prints' the board
// The board - 8 line of symbols --  '1' if the array value is 1, and "O" if the array value is 0. Use Serial.print().
// Make sure the board printing routine works by hard-coding some 0s and 1s
// No need for black and white at this stage)
// From the starting point, which will be parametrically set, go like a horse, and MARK WHERE YOU WENT WITH A 1. 
// (Structure and Interpretation of Computer Programs - Book to buy)
 
 
 
#define y_size 8
#define x_size 8 
 
int chessBoard[y_size][x_size]={
 
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0 },
     
};
 
 
 
void setup()
{   Serial.begin(9600);
}
/*
int horse_step_ur(int y0, int x0) Sophie - First draft  
{
    //1. Should put the value of 1 at cell x0, y0
    //2. Should put the value 2 at cell (according to horse's jump) 
    //3. Should NOT do (2) if the landing site is outside the board
    //4. Should "return 1" if all good, and "return 0" if landing is outside the board.
 
    chessBoard[y0][x0] = 1; //horse - start position
     
    if ((y0==0 || y0==1) && x0==7) // Making sure the horse stays inside the board
    {
        chessBoard[y0-2][x0+1] = 2; // horse - jumped to square
        return 1;
    }
 
    return 0;   
}
*/
 
/*int horse_step_ur2(int y0, int x0) // Eugene - Edit
{
    //1. Should put the value of 1 at cell x0, y0
    //2. Should put the value 2 at cell (according to horse's jump) 
    //3. Should NOT do (2) if the landing site is outside the board
    //4. Should "return 1" if all good, and "return 0" if landing is outside the board.
 
    chessBoard[y0][x0] = 1; //horse - start position
 
    int y2 = y0 - 2;
    int x2 = x0 + 1;
 
    if( x2 < 0 || x2 > 7 )
    { return 0;
    }
 
    if( y2 < 0 || y2 > 7 )
    {
    return 0;
    }
     
 
    chessBoard[y2][x2] = 2; // horse - jumped to square
 
    return 1;
} */
 
int g_x=0, g_y=0;
 
int horse_step_check (int y0, int x0, int dir) //Check to see that the knight is landing on a square that is 0
{
    int x2 = 0;
    int y2 = 0;
  
         if (dir == 0)  {       y2 = y0 - 2;        x2 = x0 + 1;    }
    else if (dir == 1)  {       y2 = y0 - 1;        x2 = x0 + 2;    }
    else if (dir == 2)  {       y2 = y0 + 1;        x2 = x0 + 2;    }
    else if (dir == 3)  {       y2 = y0 + 2;        x2 = x0 + 1;    }
    else if (dir == 4)  {       y2 = y0 + 2;        x2 = x0 - 1;    }
    else if (dir == 5)  {       y2 = y0 + 1;        x2 = x0 - 2;    }
    else if (dir == 6)  {       y2 = y0 - 1;        x2 = x0 - 2;    }
    else                {       y2 = y0 - 2;        x2 = x0 - 1;    }
 
    if( x2 < 0 || x2 > 7 )  
        return 0;
 
    if( y2 < 0 || y2 > 7 )
        return 0;   
 
    if (chessBoard [y2] [x2] != 0)  
        return 0; 
 
    g_x = x2;
    g_y = y2;
 
     
    return 1; // All three conditions above are exceptions, this is the correct scenario
 
}
 
int horse_step_dir(int y0, int x0, int dir) // dir - Basically one of the eight possible directions. Argument = 0 to 7 any number
{
    //1. Should put the value of 1 at cell x0, y0
    //2. Should put the value 2 at cell (according to horse's jump) 
    //3. Should NOT do (2) if the landing site is outside the board
    //4. Should "return 1" if all good, and "return 0" if landing is outside the board.
 
    if (horse_step_check (y0, x0, dir) == 0)
        return 0;
 
    chessBoard[y0][x0] = 1; //horse - start position
 
    chessBoard[g_y][g_x] = 2; // horse - jumped to square
 
    return 1;
 
}
 
int horse_step_any_dir(int y0, int x0)
{
    chessBoard[y0][x0] = 1; //horse - start position
 
    int ef = 0; 
 
    for ( ef=0; ef<8; ef++)
    {
        int res = horse_step_dir(g_y,g_x,ef); //Iterating from positions 0 to 7 clockwise
    }   
}
 
void loop()
{   int y = 0; //Remember: (y,x)
    int x = 0;
     
          
    for ( y=0; y<8; y++ )  
    {   for ( x=0; x<8; x++ )
        {   
             Serial.print ( chessBoard[y][x] ); 
             Serial.print(" ");
             delay(300);
        }   
             
        Serial.println(""); 
//          chessBoard [h2][h1] = {1}; //horse - start position
//      chessBoard[h2-2][h1+1]={1}; ////horse - move - up and right
//      Serial.print ( chessBoard[h2-2][h1+1]); //Printing moved horse
//      Serial.print( chessBoard[h2][h1] ); //Printing start position of the horse
    }
 
//Printing two blank lines between boards
    Serial.println("");
    Serial.println("");
 
// Run 
 
    int ef = 0; 
 
    for ( ef=0; ef<8; ef++)
    {
        int res = horse_step_dir(4,3,ef); //Iterating from positions 0 to 7 clockwise
 
        if( res == 0 )
            Serial.println ("The horse is either out of the board or landing in a non-empty square.");
         
    } 
    Serial.println(" ");
    Serial.println(" ");
}
