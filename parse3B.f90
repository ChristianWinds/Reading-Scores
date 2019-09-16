program parse

        character(LEN=5000000) :: line
        integer :: filesize
        character(:), allocatable :: outline, word

        interface
         subroutine get_next_token( inline, outline, word)
          character (*) :: inline
          character, dimension(:), allocatable :: outline, word
         end subroutine get_next_token
         ! subroutine read_file( string, counter )
         ! character(:), allocatable :: string
         ! integer :: counter
         !end subroutine read_file
        end interface


        ! Read from the external file
        call read_file( line, filesize )
        print *, line
        print *, "The length of the string is ", len(line)

        ! Initialize outline to be same string as line, it will get overwritten
        ! in the subroutine, but we need it for loop control
        outline = line


        ! * Keep this loop section.
        do while (len(outline) .ne. 0)
         call get_next_token ( line, outline, word)
         print *, word
         line = outline
enddo
endprogram parse

subroutine get_next_token( inline, outline, token)
        character (*) :: inline
        character(:), allocatable :: outline, token
        integer :: i, j
        logical :: foundFirst, foundLast

        ! Initialize variables used to control loop
        foundFirst = .false.
        foundLast  = .false.
        i = 0

        ! find first non blank character
        do while ( .not. foundFirst .and. (i < len(inline)))
          if (inline(i:i) .eq. " ") then
            i = i + 1
          else
            foundFirst = .true.
          endif
        enddo


        j = i
        do while ( foundFirst .and. .not. foundLast .and. ( j < len(inline)))
          if (inline(j:j) .ne. " ") then
            j = j + 1
          else
            foundLast = .true.
          endif
        enddo

        token = trim(inline(i:j))
        outline = trim(inline(j+1:len(inline)))

end subroutine get_next_token

subroutine read_file( string, counter )

character (LEN=*) :: string
integer :: counter
character (LEN=1) :: input


open (unit=5,status="old",access="direct",form="unformatted",recl=1,file="/pub/pounds/CSC330/translations/KJV.txt")


counter=1
100 read (5,rec=counter,err=200) input
        string(counter:counter) = input
        counter=counter+1
        goto 100
200 continue
counter=counter-1


close (5)

end subroutine read_file
