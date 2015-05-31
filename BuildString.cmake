set(DELIMITER "")

set(SOURCE ${CMAKE_ARGV1})
set(BUILD ${CMAKE_ARGV2})
set(PATH ${CMAKE_ARGV3})

file(READ ${SOURCE}/${PATH} STRING)
# add semicolons back into string
string(REGEX REPLACE ";" "\\\\;" STRING "${STRING}")
file(WRITE ${BUILD}/${PATH}.txt R\"${DELIMITER}\(${STRING}\)${DELIMITER}\")
