set(mpu9250_srcs "src/mpu9250.c" "src/mpu9250_iic.c" "src/Pedometer.c" "src/WIFINetwork.c")

idf_component_register(SRCS "${mpu9250_srcs}"
                       INCLUDE_DIRS "include"
					   REQUIRES GeekSHELL)
