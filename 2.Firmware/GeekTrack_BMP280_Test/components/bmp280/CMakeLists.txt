set(bmp280_srcs "src/bmp280.c" "src/i2cdev.c")

idf_component_register(SRCS "${bmp280_srcs}"
                       INCLUDE_DIRS "include"
		    REQUIRES driver freertos)
