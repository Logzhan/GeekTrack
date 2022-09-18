set(esp32shell_srcs "src/geek_shell.c" 
                    "src/geek_shell_cmd_list.c" 
					"src/geek_shell_companion.c" 
					"src/geek_shell_ext.c" 
					"src/geek_shell_api")

idf_component_register(SRCS "${esp32shell_srcs}"
                       INCLUDE_DIRS "include")
