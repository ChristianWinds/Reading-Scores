-- Code from Rosetta Code,
-- https://www.rosettacode.org/wiki/File_input/output#Ada
-- Accessed Monday, September 30th, 2019
with Ada.Command_Line, Ada.Text_IO; use Ada.Command_Line, Ada.Text_IO;
procedure flesch is
-- Code from The Craft of Coding,
-- https://craftofcoding.wordpress.com/2018/04/04/coding-ada-reading-lines-from-files/
-- Accessed Tuesday, October 1st, 2019
   infp : file_type;
   sline : unbounded_string;
   fname : unbounded_string;
   nameOK : boolean := false;
begin
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
end flesch;
