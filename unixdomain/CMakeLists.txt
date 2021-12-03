add_executable(unixbind unixbind.c)
target_link_libraries(unixbind nethelp)

add_executable(unixstrserv01 unixstrserv01.c ../src/sigchidwait.c ../src/ser_echo.c)
target_link_libraries(unixstrserv01 nethelp)

add_executable(unixstrcli01 unixstrcli01.c ../src/str_cil.c)
target_link_libraries(unixstrcli01 nethelp)

add_executable(mycat mycat.c myopen.c)
target_link_libraries(mycat nethelp)

add_executable(openfile openfile.c)
target_link_libraries(openfile nethelp)

