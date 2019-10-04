-- Code from Rosetta Code,
-- https://www.rosettacode.org/wiki/File_input/output#Ada
-- Accessed Monday, September 30th, 2019
with Ada.Command_Line, Ada.Text_IO; use Ada.Command_Line, Ada.Text_IO;
procedure flesch is
   Read_From : constant String := "/pub/pounds/CSC330/dalechall/wordlist1995.txt";
   Write_To  : constant String := "output.txt";
 
   Input, Output : File_Type;

-- Code from The Craft of Coding,
-- https://craftofcoding.wordpress.com/2018/04/04/coding-ada-reading-lines-from-files/
-- Accessed Tuesday, October 1st, 2019
   infp : file_type;
   sline : unbounded_string;
   fname : unbounded_string;
   nameOK : boolean := false;
-- Code from Rosetta Code,
-- https://www.rosettacode.org/wiki/File_input/output#Ada
-- Accessed Monday, September 30th, 2019
begin
   begin
      Open (File => Input,
            Mode => In_File,
            Name => Read_From);
   exception
      when others =>
         Put_Line (Standard_Error,
                   "Can not open the file '" & Read_From & "'. Does it exist?");
         Set_Exit_Status (Failure);
         return;
   end;
 
   begin
      Create (File => Output,
              Mode => Out_File,
              Name => Write_To);
   exception
      when others =>
         Put_Line (Standard_Error,
                   "Can not create a file named '" & Write_To & "'.");
         Set_Exit_Status (Failure);
         return;
   end;

-- Code from The Craft of Coding,
-- https://craftofcoding.wordpress.com/2018/04/04/coding-ada-reading-lines-from-files/
-- Accessed Tuesday, October 1st, 2019
put_line ("Enter the filename: ");
loop
   exit when nameOK;
   get_line(fname);
   nameOK := exists(to_string(fname));
end loop;

open(infp, in_file, to_string(fname));

loop
   exit when end_of_file(infp);
   -- Process each line from the file
   get_line(infp,sline);
   -- do something with the line of text
   end loop;
   
 
   loop
      declare
         Line : String := Get_Line (Input);
      begin
         -- You can process the contents of Line here.
         Put_Line (Output, Line);
      end;
   end loop;
   Close (Input);
   Close (Output);
exception
   when End_Error =>
      if Is_Open(Input) then 
         Close (Input);
      end if;
      if Is_Open(Output) then 
         Close (Output);
      end if;
end flesch;
