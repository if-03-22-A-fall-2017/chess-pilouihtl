/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.c
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Implementation of basic chess functions.
 * ----------------------------------------------------------
 */
 #include <stdio.h>
 #include <stdbool.h>
 #include "general.h"
 #include "chess.h"

 #define MAX_OF_BOARD 8
 #define MIN_OF_BOARD 1

 bool 	is_piece (struct ChessPiece pc, enum PieceColor color, enum PieceType type){
   if(pc.type == type && pc.color == color){
     return true;
   }
   return false;
 }

 void 	init_chess_board (ChessBoard chess_board){
   for(int i = 0; i < MAX_OF_BOARD; i++){
     for(int a = 0; a < MAX_OF_BOARD; a++){
       chess_board[i][a].is_occupied = false;
       chess_board[i][a].piece.type = NoPiece;
     }
   }
 }

 struct ChessSquare * 	get_square (ChessBoard chess_board, File file, Rank rank){
   if(file >= 'a' && file <= 'h' && rank >= MIN_OF_BOARD && rank <= MAX_OF_BOARD){
     return &chess_board[rank - 1][file - 'a'];
   }
   return 0;
 }

 bool 	is_square_occupied (ChessBoard chess_board, File file, Rank rank){
   return chess_board[rank - 1][file - 'a'].is_occupied;
 }

 bool 	add_piece (ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece){
   bool yes_or_no = is_square_occupied(chess_board, file, rank);
   if(yes_or_no == true){
     return false;
   }
   else if(yes_or_no == false && file >= 'a' && file <= 'h' && rank >= MIN_OF_BOARD && rank <= MAX_OF_BOARD){
      chess_board[rank - 1][file - 'a'].is_occupied = true;
      chess_board[rank - 1][file - 'a'].piece = piece;
      return true;
   }
   return false;
 }

 struct ChessPiece 	get_piece (ChessBoard chess_board, File file, Rank rank){
   if(rank >= MIN_OF_BOARD && rank <= MAX_OF_BOARD && file >= 'a' && file <= 'h'){
     return chess_board[rank - 1][file - 'a'].piece;
   }
   struct ChessPiece piece_to_return;
   piece_to_return.type = NoPiece;
   return piece_to_return;
 }

 void 	setup_chess_board (ChessBoard chess_board){
   struct ChessPiece white_queen = {White, Queen};
   struct ChessPiece white_knight = {White, Knight};
   struct ChessPiece white_king = {White, King};
   struct ChessPiece white_pawn = {White, Pawn};
   struct ChessPiece white_bishop = {White, Bishop};
   struct ChessPiece white_rook = {White, Rook};
   struct ChessPiece black_queen = {Black, Queen};
   struct ChessPiece black_knight = {Black, Knight};
   struct ChessPiece black_king = {Black, King};
   struct ChessPiece black_pawn = {Black, Pawn};
   struct ChessPiece black_bishop = {Black, Bishop};
   struct ChessPiece black_rook = {Black, Rook};

   init_chess_board(chess_board);
   add_piece(chess_board, 'a', 1, white_rook);
   add_piece(chess_board, 'b', 1, white_knight);
   add_piece(chess_board, 'c', 1, white_bishop);
   add_piece(chess_board, 'd', 1, white_queen);
   add_piece(chess_board, 'e', 1, white_king);
   add_piece(chess_board, 'f', 1, white_bishop);
   add_piece(chess_board, 'g', 1, white_knight);
   add_piece(chess_board, 'h', 1, white_rook);

   add_piece(chess_board, 'a', 8, black_rook);
   add_piece(chess_board, 'b', 8, black_knight);
   add_piece(chess_board, 'c', 8, black_bishop);
   add_piece(chess_board, 'd', 8, black_queen);
   add_piece(chess_board, 'e', 8, black_king);
   add_piece(chess_board, 'f', 8, black_bishop);
   add_piece(chess_board, 'g', 8, black_knight);
   add_piece(chess_board, 'h', 8, black_rook);

   for (char i = 'a'; i <= 'h'; i++) {
     add_piece(chess_board, i, 2, white_pawn);
   }
   for (char i = 'a'; i <= 'h'; i++) {
     add_piece(chess_board, i, 7, black_pawn);
   }
 }

 bool 	remove_piece (ChessBoard chess_board, File file, Rank rank){
   if(is_square_occupied(chess_board, file, rank) && file >= 'a' && file <= 'h' && rank >= MIN_OF_BOARD && rank <= MAX_OF_BOARD){
     chess_board[rank - 1][file - 'a'].is_occupied = false;
      return true;
   }

   return false;
 }

 bool 	squares_share_file (File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   if(s1_f >= 'a' && s1_r >= MIN_OF_BOARD && s1_f == s2_f && s1_r <= s2_r && s2_f <= 'h' && s2_r <= MAX_OF_BOARD){
     return true;
   }
   return false;
 }

 bool 	squares_share_rank (File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   if(s1_f >= 'a' && s2_f <= 'h' && s1_f <= s2_f && s1_r == s2_r && s1_r >= MIN_OF_BOARD && s2_r <= MAX_OF_BOARD){
     return true;
   }
   return false;
 }

 bool 	squares_share_diagonal (File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   if(!(s1_f >= 'a' && s1_f<= 'h' && s1_r <= MAX_OF_BOARD && s1_r >= MIN_OF_BOARD && s2_f >= 'a' && s2_f <= 'h' && s2_r <= MAX_OF_BOARD && s2_r >= MIN_OF_BOARD)){
     return false;
   }
   return true;
 }

 bool 	squares_share_knights_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   int rank_check = s1_r - s2_r;
   int file_check = (s1_f-'a') - (s2_f-'a');
   if (rank_check != 0 && rank_check <= 2 && rank_check >= -2 && file_check != 0 && file_check <= 2 && file_check >= -2){
     return true;
   }
   return false;
 }
 bool is_move_from_base_line (enum PieceColor color, Rank rank){
   if(color == White && rank == 2){
     return true;
   }
   else if(color == Black && rank ==7){
     return true;
   }
   return false;
}
 bool squares_share_pawns_move (enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   if (color == White) {
     if(s1_r > s2_r || s1_r == MIN_OF_BOARD) {
       return false;
     }
     else if (s1_r != 2 && s2_r - s1_r == 2) {
       return false;
     }
   }
   else{
     if (s1_r < s2_r || s1_r == MAX_OF_BOARD) {
       return false;
     }
     else if (s1_r != 7 && s1_r - s2_r == 2) {
       return false;
     }
 }
  return true;
 }


 bool 	squares_share_queens_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   if(squares_share_diagonal(s1_f, s1_r, s2_f, s2_r)){
     return true;
   }
   else if(squares_share_rank(s1_f, s1_r, s2_f, s2_r) || squares_share_file(s1_f, s1_r, s2_f, s2_r)){
     return true;
   }
   return false;
 }

 bool 	squares_share_kings_move (File s1_f, Rank s1_r, File s2_f, Rank s2_r){
   if((s1_r - s2_r <= 1 ||s1_r - s2_r >= -1) && (s1_f - '0' - s2_f - '0' <= 1 || s1_f - '0' - s2_f - '0' >= - 1))
   {
     return true;
   }
   return false;
 }
