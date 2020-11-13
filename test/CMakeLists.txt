add_executable(test_dt dt.c)
target_link_libraries(test_dt mc)

add_executable(test_log log.c)
target_link_libraries(test_log mc)

add_executable(test_mem mem.c)
target_link_libraries(test_mem mc)

add_executable(test_list list.c)
target_link_libraries(test_list mc)

add_executable(test_arr arr.c)
target_link_libraries(test_arr mc)

