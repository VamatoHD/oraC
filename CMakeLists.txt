cmake_minimum_required(VERSION 3.10)
project(MyMainProject LANGUAGES C)

#Adiciona a pasta do submódulo oraC
#Mudar dependendo da localização do submódulo
add_subdirectory(oraC) 

#Adiciona o executável principal do projeto
add_executable(MyApplication main.c)

#Linka a biblioteca oraC
target_link_libraries(MyApplication PRIVATE oraC::oraC)