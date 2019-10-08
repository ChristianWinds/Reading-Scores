-- Code from Dr. Pounds,
-- "CSC 330 Request for Ada Tokenizer"
-- Accessed October 8, 2019
with Ada;
with Ada.Text_IO;
use Ada.Text_IO;
use Ada.IO_Exceptions;
with Ada.Containers.Indefinite_Vectors;
use  Ada.Containers;

package body pounds_tokenize_pack is
procedure toarray is

   In_File      : Ada.Text_IO.File_Type;
   value        : Character;
   string_array         : array (1..5000000) of Character;
   pos          : Integer;
   package String_Vector is new Indefinite_Vectors (Natural,String); use String_Vector;
   s       : String(1..5000000) := (others => Character'Val(0));
   current : Positive := s'First;
   v       : Vector;

begin

   Ada.Text_IO.Put (Item => "Done initilizing variables");
   Ada.Text_IO.Open (File => In_File, Mode => Ada.Text_IO.In_File, Name => "KJV.txt");

   pos := 0;
   while not Ada.Text_IO.End_Of_File(In_File) loop
    Ada.Text_IO.Get (File => In_File, Item => value);
    pos := pos + 1;
    string_array(pos) := value;
   end loop;
-- We know we are going to hit the end of the file, so handle the exception

   exception

   when Ada.IO_Exceptions.END_ERROR => Ada.Text_IO.Close (File => In_File);

-- Copy array to string

   for i in string_array'range loop
     s(i) := string_array(i);
   end loop;

-- Now use parser to break string array into a vector of tokens

  for i in s'range loop
    if s (i) = ' ' or i = s'last then
      v.append (s(current .. i-1));
      current := i + 1;
    end if;
   end loop;

  for s of v loop
   put(s);
   new_line;
  end loop;


   Ada.Text_IO.New_Line;

end toarray;
end pounds_tokenize_pack;
