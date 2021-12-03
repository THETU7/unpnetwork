add_executable(udpserveice udpserver1.c)
target_link_libraries(udpserveice nethelp)

add_executable(udpclient udpclient1.c)
target_link_libraries(udpclient nethelp)


add_executable(udpclient2 udpclient2.c)
target_link_libraries(udpclient2 nethelp)
