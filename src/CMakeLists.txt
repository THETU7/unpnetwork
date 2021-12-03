add_executable(service server.c)
add_library(sigchidwait STATIC sigchidwait.c)
target_link_libraries(service nethelp sigchidwait)
add_executable(client client.c)
target_link_libraries(client nethelp)

add_executable(service1 server1.c ser_echo.c)
target_link_libraries(service1 nethelp sigchidwait)
add_executable(client1 client1.c str_cil.c)
target_link_libraries(client1 nethelp) 

add_executable(client2 client2.c strcliselect01.c)
target_link_libraries(client2 nethelp)
add_executable(service2 server2.c)
target_link_libraries(service2 nethelp)

#add_executable(service3 tcpservepoll01.c)
#target_link_libraries(service3 nethelp)

add_executable(service4 udpserver2.c sigchidwait.c)
target_link_libraries(service4 nethelp)

add_executable(daytime1 tcpserver1.c)
target_link_libraries(daytime1 nethelp)

add_executable(tcpc1 tcpclient1.c)
target_link_libraries(tcpc1 nethelp)

add_executable(udpc1 daytimeudpcli1.c)
target_link_libraries(udpc1 nethelp)

add_executable(udps1 daytimeudps.c)
target_link_libraries(udps1 nethelp)

install(TARGETS service client service1 client1 client2 DESTINATION bin)
