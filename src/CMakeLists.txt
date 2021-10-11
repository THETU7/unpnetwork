add_executable(service server.c)
add_library(sigchidwait STATIC sigchidwait.c)
target_link_libraries(service nethelp sigchidwait)
add_executable(client client.c)
target_link_libraries(client nethelp)

#add_library(serecho1 STATIC ser_echo.c)
#add_library(cli STATIC str_cil.c)
add_executable(service1 server1.c ser_echo.c)
target_link_libraries(service1 nethelp sigchidwait)
add_executable(client1 client1.c str_cil.c)
target_link_libraries(client1 nethelp) 

install(TARGETS service client service1 client1 DESTINATION bin)
