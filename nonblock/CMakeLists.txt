add_executable(nonblockcli web.c start_connect.c write_get_cmd.c home_page.c)
target_link_libraries(nonblockcli nethelp)
