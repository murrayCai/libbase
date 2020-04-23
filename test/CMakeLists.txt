add_executable(test_dt dt.c)
target_link_libraries(test_dt base)

add_executable(test_log log.c)
target_link_libraries(test_log base)

add_executable(test_mem mem.c)
target_link_libraries(test_mem base)

add_executable(test_list list.c)
target_link_libraries(test_list base)

