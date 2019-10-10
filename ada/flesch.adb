-- Programmer Name: Christian Winds
-- Course: CSC330 Organization of Programming Languages
-- School Year: 2019-2020 School Year

with Ada.Text_IO;  use Ada.Text_IO;
with pounds_tokenize_pack;
use pounds_tokenize_pack;
 
procedure flesch is
   total_words	: Integer := 0;
   syllables	: Integer := 0;
   sentences	: Integer := 0; 
begin
   toarray(total_words, syllables, sentences);
end flesch;
